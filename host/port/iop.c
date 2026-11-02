/* The IOP off the PS2 (docs/sound-spec.md "The IOP on the port"): the user's own sound driver
 * (LIBSSL.IRX, "Ohori_Sound_Driver", read from the disc at run time, never in the repo or the VPK)
 * run by an R3000A interpreter, with what it imports answered here:
 *
 *   - the CPU: MIPS I integer instructions with their branch delay slots (the IOP's load delay slot is
 *     not modelled: gcc never reads a register in the slot after its load), no COP0 / GTE;
 *   - the loader: the IRX's .iopmod (entry), its sections at KH1_IOP_BASE, its REL relocations
 *     (R_MIPS_32 / 26 / HI16 / LO16 as loadcore applies them), and its import tables: a stub
 *     (`jr $ra; li $zero, N`) is library N's export, answered in C when the CPU reaches it;
 *   - the kernel: threads (each its own register file, run until it blocks: the IOP's threads only
 *     switch in a kernel call, and interrupts are delivered between runs), semaphores, variable pools,
 *     one hardware timer (the driver's 240 Hz tick, kh1_iop_tick), the interrupt calls (no-ops);
 *   - SIF: the RPC server the module registers (kh1_iop_rpc calls its function as sifcmd would),
 *     sceSifGetOtherData (EE -> IOP) and sceSifSetDma (IOP -> EE): EE addresses are the port's own
 *     32-bit pointers (the game's C hands them over as the EE did);
 *   - libsd: kh1_sd_call (host/port/spu2.c).
 *
 * One caller at a time (host/port/snd.c holds its lock).  Not part of the PS2 build. */
#include "common.h"
#include "iop.h"

int printf(const char *, ...);
void *memcpy(void *, const void *, unsigned int);
void *memset(void *, int, unsigned int);
int strcmp(const char *, const char *);
int memcmp(const void *, const void *, unsigned int);

u8 kh1_iop_ram[KH1_IOP_RAM] __attribute__((aligned(16)));
u32 kh1_iop_insns;

/* where the module goes, the heap for thread stacks and pools, the interrupt stack, and the return
 * address that ends a call from C (never code) */
#define KH1_IOP_BASE 0x00040000
#define IOP_HEAP_END 0x001F0000
#define IOP_INTR_STACK 0x001FF000
#define IOP_MAGIC_RET 0x001FFFF0

/* two opcodes the R3000 does not have (primary 0x3E / 0x3F), put in RAM for run(): an import stub's
 * first word becomes OP_STUB | its index (find_imports), and the word at IOP_MAGIC_RET is OP_MAGIC, so
 * neither needs a check of the pc at every instruction */
#define OP_STUB 0xF8000000u
#define OP_MAGIC 0xFC000000u
#define OP_NATIVE 0xF4000000u /* (primary 0x3D) a driver function run as C: natives[] below */
#define OP_REC 0xF0000000u    /* (primary 0x3C) a driver function translated to C at build time (KH1_IOP_REC) */

#define IOP_THREADS 8
#define IOP_SEMAS 16
#define IOP_VPLS 4
#define IOP_STUBS 128

typedef struct {
    u32 r[32];
    u32 hi, lo, pc, npc;
} IopCtx;

enum { TH_FREE, TH_DORMANT, TH_READY, TH_WAIT_SEMA, TH_DELAY, TH_RPC_WAIT };
typedef struct {
    IopCtx c;
    int state;
    int prio;
    int sema;    /* the semaphore it waits for */
    int in_rpc;  /* running an RPC call from kh1_iop_rpc */
    u32 entry, stack, stack_size;
} IopThread;

typedef struct {
    int used, count, max;
} IopSema;

/* a variable-length pool: first fit over a list of blocks kept in a side table.  The driver keeps every
 * bank chunk in its one pool (up to 1536 entries in its table, one block each: a room's SE bank alone is
 * 60-90), so the side table has room for more than that; at 64 the room's banks stopped loading
 * (docs/sound-spec.md "The pool's block limit") */
#define VPL_BLOCKS 2048
typedef struct {
    int used;
    u32 base, size;
    u32 at[VPL_BLOCKS], len[VPL_BLOCKS];
    int n;
} IopVpl;

typedef struct {
    u32 addr;
    const char *lib;
    int fn;
} IopStub;

static IopThread iop_th[IOP_THREADS];
static IopSema iop_sema[IOP_SEMAS];
static IopVpl iop_vpl[IOP_VPLS];
static IopStub iop_stub[IOP_STUBS];
static int iop_nstubs;
static int iop_cur = -1; /* the thread running, -1 for an interrupt or the loader */
static u32 iop_heap;
static int iop_ok;
static u32 iop_mod_end;
static int iop_log_on = -1;
static int iop_natives_on = 1; /* 0: interpret every driver function (KH1_HOST_IOP=nonative) */
static int iop_rec_on = 1;     /* 0: leave the build's translation unused (KH1_HOST_IOP=norec) */

/* the RPC server (one is enough for the sound driver) */
static u32 rpc_sid = (u32)-1, rpc_func, rpc_buf;
static int rpc_thread = -1;

/* the hardware timer */
static u32 tm_compare, tm_handler, tm_arg;
static int tm_started;
static u32 tm_count;

/* pending libsd transfer interrupts */
static u32 trans_func[2], trans_arg[2];
static int trans_pending[2];

/* why a run stopped */
enum { RUN_RET, RUN_BLOCK, RUN_BUDGET, RUN_FAULT };

char *getenv(const char *);
static int iop_log(void) {
    if (iop_log_on < 0) {
        const char *s = getenv("KH1_HOST_IOP");
        iop_log_on = s && *s && *s != '0';
        if (s && !strcmp(s, "nonative")) { iop_natives_on = 0; iop_rec_on = 0; iop_log_on = 0; }
        if (s && !strcmp(s, "norec")) { iop_rec_on = 0; iop_log_on = 0; }
    }
    return iop_log_on;
}

/* ---- memory ---- */

u8 *kh1_iop_ptr(u32 addr, u32 size) {
    addr &= 0x1FFFFFFF;
    if (addr >= KH1_IOP_RAM || size > KH1_IOP_RAM - addr) return 0;
    return kh1_iop_ram + addr;
}

static int iop_bad_reported;
static void bad_access(u32 addr, u32 pc) {
    if (iop_bad_reported < 8) {
        iop_bad_reported++;
        printf("kh1-iop: access outside RAM 0x%08x at pc 0x%05x\n", addr, pc - KH1_IOP_BASE);
    }
}

#define RAM_OK(a) (((a) & 0x1FFFFFFF) < KH1_IOP_RAM)
#define RAM(a) (kh1_iop_ram + ((a) & 0x1FFFFF))

static u32 rd32(u32 a, u32 pc) {
    if (!RAM_OK(a)) { bad_access(a, pc); return 0; }
    return *(u32 *)RAM(a & ~3u);
}
static u32 rd16(u32 a, u32 pc) {
    if (!RAM_OK(a)) { bad_access(a, pc); return 0; }
    return *(u16 *)RAM(a & ~1u);
}
static u32 rd8(u32 a, u32 pc) {
    if (!RAM_OK(a)) { bad_access(a, pc); return 0; }
    return *RAM(a);
}
static void wr32(u32 a, u32 v, u32 pc) {
    if (!RAM_OK(a)) { bad_access(a, pc); return; }
    *(u32 *)RAM(a & ~3u) = v;
}
static void wr16(u32 a, u32 v, u32 pc) {
    if (!RAM_OK(a)) { bad_access(a, pc); return; }
    *(u16 *)RAM(a & ~1u) = (u16)v;
}
static void wr8(u32 a, u32 v, u32 pc) {
    if (!RAM_OK(a)) { bad_access(a, pc); return; }
    *RAM(a) = (u8)v;
}

static u32 iop_alloc(u32 size) {
    u32 at = (iop_heap + 15) & ~15u;
    if (at + size > IOP_HEAP_END) return 0;
    iop_heap = at + size;
    return at;
}

/* ---- the CPU ---- */

static int hle(IopCtx *c, const IopStub *s);
static void rec_dispatch(IopCtx *c, u32 k);

#define RS ((op >> 21) & 31)
#define RT ((op >> 16) & 31)
#define RD ((op >> 11) & 31)
#define SA ((op >> 6) & 31)
#define IMM ((u32)(s32)(s16)op)
#define IMMU (op & 0xFFFF)

/* ---- the driver's hottest small functions as C ----
 * LIBSSL.IRX's per-tick voice loop calls three leaf functions for every voice: each sets or clears a
 * voice's bit in pairs of "registers to send to the SPU2" masks (two words each, voices 0-23 and
 * 24-47, the top bit a dirty flag).  They are about a third of the driver's instructions, so once the
 * module is loaded each one whose words match the known driver (an FNV-1a of the relocated function)
 * has its first word replaced by OP_NATIVE and runs here; any other driver is left to the
 * interpreter.  The masks are module data at the module's base + the offsets below. */
#define MOD_U32(off) (*(u32 *)RAM(KH1_IOP_BASE + (off)))

static u32 native_bit(u32 voice, u32 *word) {
    s32 v = (s32)voice;
    *word = v >= 24 ? 4 : 0;
    return 1u << ((u32)(v % 24) & 31);
}

/* func_00150(voice, a, b): a and b each 0 (set the first mask, clear the second), 1 (the other way
 * round) or 2 (set both); a for the masks at 0xF4E0 / 0xF530, b for 0xF540 / 0xF4C8 */
static void native_00150(IopCtx *c) {
    u32 w, bit = native_bit(c->r[4], &w), a = c->r[5], b = c->r[6];
    if (a == 0) { MOD_U32(0xF4E0 + w) |= bit; MOD_U32(0xF530 + w) &= ~bit; }
    else if (a == 1) { MOD_U32(0xF4E0 + w) &= ~bit; MOD_U32(0xF530 + w) |= bit; }
    else if (a == 2) { MOD_U32(0xF4E0 + w) |= bit; MOD_U32(0xF530 + w) |= bit; }
    if (b == 0) { MOD_U32(0xF540 + w) |= bit; MOD_U32(0xF4C8 + w) &= ~bit; }
    else if (b == 1) { MOD_U32(0xF540 + w) &= ~bit; MOD_U32(0xF4C8 + w) |= bit; }
    else if (b == 2) { MOD_U32(0xF540 + w) |= bit; MOD_U32(0xF4C8 + w) |= bit; }
    MOD_U32(0xF4E0 + w) |= 0x80000000u;
    MOD_U32(0xF540 + w) |= 0x80000000u;
    MOD_U32(0xF530 + w) |= 0x80000000u;
    MOD_U32(0xF4C8 + w) |= 0x80000000u;
}

/* func_00434 / func_004f0(voice, on): set or clear the voice's bit in one mask */
static void native_mask(IopCtx *c, u32 off) {
    u32 w, bit = native_bit(c->r[4], &w);
    if (c->r[5] == 0) MOD_U32(off + w) &= ~bit;
    else MOD_U32(off + w) |= bit;
    MOD_U32(off + w) |= 0x80000000u;
}
static void native_00434(IopCtx *c) { native_mask(c, 0xF488); }
static void native_004f0(IopCtx *c) { native_mask(c, 0xF520); }

/* an import called from a native function: the stub at the module's base + off (its library and
 * number checked by patch_natives), with two arguments; its v0 */
static u32 native_import(IopCtx *c, u32 off, u32 a0, u32 a1) {
    IopCtx t = *c;
    int i;
    for (i = 0; i < iop_nstubs; i++)
        if (iop_stub[i].addr == KH1_IOP_BASE + off) {
            t.r[4] = a0;
            t.r[5] = a1;
            t.pc = iop_stub[i].addr;
            t.npc = t.pc + 4;
            hle(&t, &iop_stub[i]);
            return t.r[2];
        }
    return 0;
}

/* func_0d8dc(kind, id, sub, size, x, y): the driver's table of bank chunks in its pool (1536 entries of
 * 24 bytes at +0xCADF0: s16 kind, s16 id, sub, address, size, x, y).  An entry with the same kind, id
 * and sub and the same size is the answer; one with another size is freed (FreeVpl, the stub at
 * +0xE59C) and its entry cleared.  Without an answer, the first free entry (kind -1) gets a new block
 * (pAllocateVpl, +0xE594) of the size; 0 when there is none.  The pool's id is at +0xF460, the count
 * of entries in use at +0xF5B4.  The scan of the whole table for every chunk is about half of the
 * driver's work while the game loads banks. */
static void native_0d8dc(IopCtx *c) {
    s32 kind = (s32)c->r[4], id = (s32)c->r[5];
    u32 sub = c->r[6], size = c->r[7], i;
    u8 *e;
    for (i = 0, e = RAM(KH1_IOP_BASE + 0xCADF0); i < 1536; i++, e += 24) {
        if (*(s16 *)e != kind || *(s16 *)(e + 2) != id || *(u32 *)(e + 4) != sub) continue;
        if (*(u32 *)(e + 12) == size) { c->r[2] = *(u32 *)(e + 8); return; }
        if (native_import(c, 0xE59C, MOD_U32(0xF460), *(u32 *)(e + 8)) == 0) {
            *(s16 *)e = -1;
            *(s16 *)(e + 2) = -1;
            *(u32 *)(e + 4) = *(u32 *)(e + 8) = *(u32 *)(e + 12) = *(u32 *)(e + 16) = *(u32 *)(e + 20) = 0xFFFFFFFFu;
            MOD_U32(0xF5B4) -= 1;
        }
    }
    c->r[2] = 0;
    for (i = 0, e = RAM(KH1_IOP_BASE + 0xCADF0); i < 1536; i++, e += 24) {
        u32 at;
        if (*(s16 *)e != -1) continue;
        at = native_import(c, 0xE594, MOD_U32(0xF460), size);
        if ((s32)at <= 0) return;
        *(s16 *)e = (s16)kind;
        *(u32 *)(e + 8) = at;
        *(s16 *)(e + 2) = (s16)id;
        *(u32 *)(e + 4) = sub;
        *(u32 *)(e + 12) = size;
        *(u32 *)(e + 16) = rd32(c->r[29] + 16, 0);
        *(u32 *)(e + 20) = rd32(c->r[29] + 20, 0);
        MOD_U32(0xF5B4) += 1;
        c->r[2] = at;
        return;
    }
}

typedef struct {
    u32 off, size, hash; /* in the module's text; the hash of its words once relocated */
    void (*fn)(IopCtx *c);
} IopNative;
static const IopNative natives[] = {
    { 0x150, 0x2E4, 0x381F6730u, native_00150 },
    { 0x434, 0x0BC, 0x58CDFB82u, native_00434 },
    { 0x4F0, 0x0BC, 0x289775EDu, native_004f0 },
    { 0xD8DC, 0x1BC, 0x5424A589u, native_0d8dc },
};
#define N_NATIVES ((int)(sizeof natives / sizeof natives[0]))

static u32 fnv1a(const u8 *p, u32 n) {
    u32 h = 2166136261u, i;
    for (i = 0; i < n; i++) h = (h ^ p[i]) * 16777619u;
    return h;
}

static int stub_is(u32 off, const char *lib, int fn) {
    int i;
    for (i = 0; i < iop_nstubs; i++)
        if (iop_stub[i].addr == KH1_IOP_BASE + off) return !strcmp(iop_stub[i].lib, lib) && iop_stub[i].fn == fn;
    return 0;
}

static int patch_natives(void) {
    int i, k = 0;
    for (i = 0; i < N_NATIVES; i++) {
        const IopNative *nv = &natives[i];
        u32 h = fnv1a(RAM(KH1_IOP_BASE + nv->off), nv->size);
        if (iop_log()) printf("kh1-iop: function +0x%x hash 0x%08x\n", nv->off, h);
        if (h != nv->hash || !iop_natives_on) continue;
        if (nv->fn == native_0d8dc && !(stub_is(0xE59C, "thvpool", 9) && stub_is(0xE594, "thvpool", 7))) continue;
        *(u32 *)RAM(KH1_IOP_BASE + nv->off) = OP_NATIVE | (u32)i;
        k++;
    }
    return k;
}

/* The interpreter: direct-threaded (each handler jumps to the next instruction's through the
 * opcode tables, GNU C's labels as values), with pc, npc and the instruction count in locals that go
 * back to the context at every exit.  On the Vita the sound thread spends about half its time here.
 * Fetches mask the pc into RAM; a register jump outside RAM stops the run (the only way there). */
static __attribute__((optimize("no-gcse", "no-crossjumping"))) int run(IopCtx *c, u32 budget) {
    static void *const main_tbl[64] = {
        &&op_special, &&op_regimm, &&op_j, &&op_jal, &&op_beq, &&op_bne, &&op_blez, &&op_bgtz,
        &&op_addi, &&op_addi, &&op_slti, &&op_sltiu, &&op_andi, &&op_ori, &&op_xori, &&op_lui,
        &&op_cop0, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad,
        &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad,
        &&op_lb, &&op_lh, &&op_lwl, &&op_lw, &&op_lbu, &&op_lhu, &&op_lwr, &&op_bad,
        &&op_sb, &&op_sh, &&op_swl, &&op_sw, &&op_bad, &&op_bad, &&op_swr, &&op_bad,
        &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad,
        &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_rec, &&op_native, &&op_stub, &&op_magic,
    };
    static void *const special_tbl[64] = {
        &&op_sll, &&op_bad, &&op_srl, &&op_sra, &&op_sllv, &&op_bad, &&op_srlv, &&op_srav,
        &&op_jr, &&op_jalr, &&op_bad, &&op_bad, &&op_trap, &&op_trap, &&op_bad, &&op_bad,
        &&op_mfhi, &&op_mthi, &&op_mflo, &&op_mtlo, &&op_bad, &&op_bad, &&op_bad, &&op_bad,
        &&op_mult, &&op_multu, &&op_div, &&op_divu, &&op_bad, &&op_bad, &&op_bad, &&op_bad,
        &&op_add, &&op_add, &&op_sub, &&op_sub, &&op_and, &&op_or, &&op_xor, &&op_nor,
        &&op_bad, &&op_bad, &&op_slt, &&op_sltu, &&op_bad, &&op_bad, &&op_bad, &&op_bad,
        &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad,
        &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad, &&op_bad,
    };
    u32 *r = c->r;
    u32 xpc = c->pc, npc = c->npc, n = 0, pc, op, a;
    int k;

    *(u32 *)RAM(IOP_MAGIC_RET) = OP_MAGIC;
/* the next instruction, fetched and dispatched at the end of every handler (one indirect jump each, so
 * the branch predictor sees the opcode pairs); NEXT_B after a branch or jump also stops a run past its budget (only a loop
 * can run that long, and a loop has a branch) */
#define NEXT                                                     \
    do {                                                         \
        r[0] = 0;                                                \
        pc = xpc;                                                \
        op = *(u32 *)(kh1_iop_ram + (pc & (KH1_IOP_RAM - 4)));   \
        xpc = npc;                                               \
        npc += 4;                                                \
        n++;                                                     \
        goto *main_tbl[op >> 26];                                \
    } while (0)
#define NEXT_B goto next_b
next_b:
    if (n >= budget) { k = RUN_BUDGET; goto out; }
    NEXT;

op_magic: /* the return address of a call from C: the call is over */
    xpc = pc;
    npc = pc + 4;
    n--;
    k = RUN_RET;
    goto out;
op_native: /* the function's C, then its jr ra (natives[]: leaf functions, nothing in a delay slot) */
    natives[(op & 0xFFFF) % N_NATIVES].fn(c);
    xpc = r[31];
    npc = xpc + 4;
    NEXT_B;
op_rec: /* the function as C (it counts its own instructions, this one included), then its jr ra */
    n--;
    rec_dispatch(c, op & 0xFFFF);
    xpc = r[31];
    npc = xpc + 4;
    NEXT_B;
op_stub: {
    const IopStub *s = &iop_stub[(op & 0xFFFF) % IOP_STUBS];
    c->pc = pc;
    c->npc = pc + 4;
    k = hle(c, s);
    r[0] = 0;
    if (k != RUN_RET) { kh1_iop_insns += n; return k; } /* blocked: c->pc already points past the call */
    xpc = r[31];
    npc = xpc + 4;
    NEXT_B;
}
op_special: goto *special_tbl[op & 63];
op_sll: r[RD] = r[RT] << SA; NEXT;
op_srl: r[RD] = r[RT] >> SA; NEXT;
op_sra: r[RD] = (u32)((s32)r[RT] >> SA); NEXT;
op_sllv: r[RD] = r[RT] << (r[RS] & 31); NEXT;
op_srlv: r[RD] = r[RT] >> (r[RS] & 31); NEXT;
op_srav: r[RD] = (u32)((s32)r[RT] >> (r[RS] & 31)); NEXT;
op_jr: npc = r[RS]; goto jump_check;
op_jalr: a = r[RS]; r[RD] = pc + 8; npc = a; goto jump_check;
jump_check:
    if (!RAM_OK(npc)) {
        printf("kh1-iop: jump to 0x%08x outside RAM at 0x%05x (ra 0x%08x)\n", npc, pc - KH1_IOP_BASE, r[31]);
        k = RUN_FAULT;
        xpc = pc;
        goto out;
    }
    NEXT_B;
op_trap: /* syscall, or break (gcc's divide-by-zero trap) */
    printf("kh1-iop: %s at 0x%05x\n", (op & 63) == 0x0C ? "syscall" : "break", pc - KH1_IOP_BASE);
    k = RUN_FAULT;
    xpc = pc;
    goto out;
op_mfhi: r[RD] = c->hi; NEXT;
op_mthi: c->hi = r[RS]; NEXT;
op_mflo: r[RD] = c->lo; NEXT;
op_mtlo: c->lo = r[RS]; NEXT;
op_mult: {
    s64 p = (s64)(s32)r[RS] * (s32)r[RT];
    c->lo = (u32)p;
    c->hi = (u32)((u64)p >> 32);
    NEXT;
}
op_multu: {
    u64 p = (u64)r[RS] * r[RT];
    c->lo = (u32)p;
    c->hi = (u32)(p >> 32);
    NEXT;
}
op_div: {
    s32 nn = (s32)r[RS], d = (s32)r[RT];
    if (d == 0) { c->lo = nn >= 0 ? 0xFFFFFFFFu : 1; c->hi = (u32)nn; }
    else if (nn == (s32)0x80000000 && d == -1) { c->lo = 0x80000000u; c->hi = 0; }
    else { s32 q = nn / d; c->lo = (u32)q; c->hi = (u32)(nn - q * d); } /* one divide (the A9 has no divider) */
    NEXT;
}
op_divu: {
    u32 nn = r[RS], d = r[RT];
    if (d == 0) { c->lo = 0xFFFFFFFFu; c->hi = nn; }
    else { u32 q = nn / d; c->lo = q; c->hi = nn - q * d; }
    NEXT;
}
op_add: r[RD] = r[RS] + r[RT]; NEXT;
op_sub: r[RD] = r[RS] - r[RT]; NEXT;
op_and: r[RD] = r[RS] & r[RT]; NEXT;
op_or: r[RD] = r[RS] | r[RT]; NEXT;
op_xor: r[RD] = r[RS] ^ r[RT]; NEXT;
op_nor: r[RD] = ~(r[RS] | r[RT]); NEXT;
op_slt: r[RD] = (s32)r[RS] < (s32)r[RT]; NEXT;
op_sltu: r[RD] = r[RS] < r[RT]; NEXT;

op_regimm:
    a = pc + 4 + (IMM << 2);
    switch (RT) {
    case 0x00: if ((s32)r[RS] < 0) npc = a; NEXT_B;
    case 0x01: if ((s32)r[RS] >= 0) npc = a; NEXT_B;
    case 0x10: { int t = (s32)r[RS] < 0; r[31] = pc + 8; if (t) npc = a; NEXT_B; }
    case 0x11: { int t = (s32)r[RS] >= 0; r[31] = pc + 8; if (t) npc = a; NEXT_B; }
    default: goto op_bad;
    }
op_j: npc = (pc & 0xF0000000u) | ((op & 0x03FFFFFF) << 2); NEXT_B;
op_jal: r[31] = pc + 8; npc = (pc & 0xF0000000u) | ((op & 0x03FFFFFF) << 2); NEXT_B;
op_beq: if (r[RS] == r[RT]) npc = pc + 4 + (IMM << 2); NEXT_B;
op_bne: if (r[RS] != r[RT]) npc = pc + 4 + (IMM << 2); NEXT_B;
op_blez: if ((s32)r[RS] <= 0) npc = pc + 4 + (IMM << 2); NEXT_B;
op_bgtz: if ((s32)r[RS] > 0) npc = pc + 4 + (IMM << 2); NEXT_B;
op_addi: r[RT] = r[RS] + IMM; NEXT;
op_slti: r[RT] = (s32)r[RS] < (s32)IMM; NEXT;
op_sltiu: r[RT] = r[RS] < IMM; NEXT;
op_andi: r[RT] = r[RS] & IMMU; NEXT;
op_ori: r[RT] = r[RS] | IMMU; NEXT;
op_xori: r[RT] = r[RS] ^ IMMU; NEXT;
op_lui: r[RT] = IMMU << 16; NEXT;
op_cop0: /* mfc0 reads 0, the rest ignored */
    if (((op >> 21) & 31) == 0) r[RT] = 0;
    NEXT;
op_lb: r[RT] = (u32)(s32)(s8)rd8(r[RS] + IMM, pc); NEXT;
op_lh: r[RT] = (u32)(s32)(s16)rd16(r[RS] + IMM, pc); NEXT;
op_lwl: {
    u32 ad = r[RS] + IMM, sh = (ad & 3) * 8, w = rd32(ad, pc);
    r[RT] = (r[RT] & (0x00FFFFFFu >> sh)) | (w << (24 - sh));
    NEXT;
}
op_lw: r[RT] = rd32(r[RS] + IMM, pc); NEXT;
op_lbu: r[RT] = rd8(r[RS] + IMM, pc); NEXT;
op_lhu: r[RT] = rd16(r[RS] + IMM, pc); NEXT;
op_lwr: {
    u32 ad = r[RS] + IMM, sh = (ad & 3) * 8, w = rd32(ad, pc);
    r[RT] = (r[RT] & (0xFFFFFF00u << (24 - sh))) | (w >> sh);
    NEXT;
}
op_sb: wr8(r[RS] + IMM, r[RT], pc); NEXT;
op_sh: wr16(r[RS] + IMM, r[RT], pc); NEXT;
op_swl: {
    u32 ad = r[RS] + IMM, sh = (ad & 3) * 8, w = rd32(ad, pc);
    wr32(ad, (w & (0xFFFFFF00u << sh)) | (r[RT] >> (24 - sh)), pc);
    NEXT;
}
op_sw: wr32(r[RS] + IMM, r[RT], pc); NEXT;
op_swr: {
    u32 ad = r[RS] + IMM, sh = (ad & 3) * 8, w = rd32(ad, pc);
    wr32(ad, (w & (0x00FFFFFFu >> (24 - sh))) | (r[RT] << sh), pc);
    NEXT;
}
op_bad:
    printf("kh1-iop: unknown instruction 0x%08x at 0x%05x\n", op, pc - KH1_IOP_BASE);
    k = RUN_FAULT;
    xpc = pc;
#undef NEXT
#undef NEXT_B
out:
    c->pc = xpc;
    c->npc = npc;
    kh1_iop_insns += n;
    return k;
}

/* ---- the driver as C (KH1_IOP_REC: out/gen/iop_rec.c, made from the user's LIBSSL.IRX at build time by
 * tools/host/iop_translate.py; docs/sound-spec.md "The driver as C") ----
 * Each translated function keeps the registers it uses in locals and hands them back through the context
 * at every call and at its return; it uses the interpreter's own memory helpers and counts the same
 * instructions.  Calls to functions left to the interpreter (they can block their thread) and calls
 * through a register go through rec_interp: the interpreter, nested, with $ra the magic return address
 * for the call and given back after it.  Used only when the loaded module's text hashes to the one
 * translated; KH1_HOST_IOP=norec (or nonative) leaves it unused. */
static int rec_live;
static const IopStub *rec_stub_ptr[129];
static int rec_reports;

static void rec_report(const char *what, u32 pc) {
    if (rec_reports < 8) {
        rec_reports++;
        printf("kh1-iop: translated driver: %s at 0x%05x\n", what, pc - KH1_IOP_BASE);
    }
}

static void rec_interp(IopCtx *c, u32 t) {
    u32 ra = c->r[31], pc = c->pc, npc = c->npc;
    int k;
    c->pc = t;
    c->npc = t + 4;
    c->r[31] = IOP_MAGIC_RET;
    k = run(c, 20000000);
    if (k != RUN_RET) rec_report(k == RUN_BLOCK ? "a nested call blocked" : "a nested call faulted", t);
    c->r[31] = ra;
    c->pc = pc;
    c->npc = npc;
}

static void rec_call_ind(IopCtx *c, u32 t) {
    u32 w = RAM_OK(t) ? *(u32 *)RAM(t & ~3u) : 0;
    if ((w & 0xFC000000u) == OP_REC) rec_dispatch(c, w & 0xFFFF);
    else rec_interp(c, t);
}
#define rec_jump_out rec_call_ind

#define REC_IMPORT(k)                                               \
    do {                                                            \
        if (hle(c, rec_stub_ptr[k]) != RUN_RET) rec_report("an import blocked", c->pc); \
    } while (0)
#define REC_BADRET(pc) rec_report("a call came back to another address", pc)
#define REC_FAULT(pc) rec_report("syscall / break", pc)
#define REC_DIV(a, b)                                                                     \
    do {                                                                                  \
        s32 nn_ = (s32)(a), d_ = (s32)(b);                                                \
        if (d_ == 0) { lo = nn_ >= 0 ? 0xFFFFFFFFu : 1; hi = (u32)nn_; }                   \
        else if (nn_ == (s32)0x80000000 && d_ == -1) { lo = 0x80000000u; hi = 0; }        \
        else { s32 q_ = nn_ / d_; lo = (u32)q_; hi = (u32)(nn_ - q_ * d_); }              \
    } while (0)
#define REC_DIVU(a, b)                                                    \
    do {                                                                  \
        u32 nn_ = (a), d_ = (b);                                          \
        if (d_ == 0) { lo = 0xFFFFFFFFu; hi = nn_; }                      \
        else { u32 q_ = nn_ / d_; lo = q_; hi = nn_ - q_ * d_; }          \
    } while (0)

#ifdef KH1_IOP_REC
#include "iop_rec.c"
#else
#define REC_N 0
#define REC_NSTUBS 0
#define REC_TEXT_OFF 0u
#define REC_TEXT_SIZE 0u
#define REC_HASH 0u
static const u32 rec_stub_addr[1] = { 0 };
static const struct { u32 addr; void (*fn)(IopCtx *c); } rec_table[1] = { { 0, 0 } };
#endif

static void rec_dispatch(IopCtx *c, u32 k) {
    if (k < REC_N) rec_table[k].fn(c);
}

/* after the loader's relocation (the hash is of the relocated text, before find_imports marks the stubs) */
static int rec_check(void) {
    rec_live = 0;
    iop_log(); /* reads KH1_HOST_IOP */
    if (!REC_N || !iop_rec_on) return 0;
    return fnv1a(RAM(KH1_IOP_BASE + REC_TEXT_OFF), REC_TEXT_SIZE) == REC_HASH;
}

/* after find_imports: each translated function's first word becomes OP_REC | its index */
static int rec_patch(void) {
    int i, j;
    for (i = 0; i < REC_NSTUBS; i++) {
        rec_stub_ptr[i] = 0;
        for (j = 0; j < iop_nstubs; j++)
            if (iop_stub[j].addr == rec_stub_addr[i]) rec_stub_ptr[i] = &iop_stub[j];
        if (!rec_stub_ptr[i]) return 0;
    }
    for (i = 0; i < REC_N; i++) *(u32 *)RAM(rec_table[i].addr) = OP_REC | (u32)i;
    rec_live = 1;
    return REC_N;
}

/* one call from C into IOP code, on the interrupt stack (an interrupt handler, the module's start) */
static u32 call_func(u32 func, u32 a0, u32 a1, u32 a2, u32 a3, u32 sp) {
    IopCtx c;
    int k, save = iop_cur;
    memset(&c, 0, sizeof c);
    c.pc = func;
    c.npc = func + 4;
    c.r[4] = a0;
    c.r[5] = a1;
    c.r[6] = a2;
    c.r[7] = a3;
    c.r[29] = sp;
    c.r[31] = IOP_MAGIC_RET;
    iop_cur = -1;
    k = run(&c, 20000000);
    iop_cur = save;
    if (k != RUN_RET) printf("kh1-iop: call to 0x%05x did not return (%d)\n", func - KH1_IOP_BASE, k);
    return c.r[2];
}

/* ---- threads ---- */

static void deliver_interrupts(void) {
    int core;
    for (core = 0; core < 2; core++)
        if (trans_pending[core]) {
            trans_pending[core] = 0;
            if (trans_func[core]) call_func(trans_func[core], (u32)core, trans_arg[core], 0, 0, IOP_INTR_STACK);
        }
}

static int pick_ready(void) {
    int i, best = -1;
    for (i = 0; i < IOP_THREADS; i++)
        if (iop_th[i].state == TH_READY && (best < 0 || iop_th[i].prio < iop_th[best].prio)) best = i;
    return best;
}

/* run the ready threads (highest priority first) until none is ready */
static void schedule(void) {
    int t, guard = 0;
    deliver_interrupts();
    while ((t = pick_ready()) >= 0 && guard++ < 10000) {
        int k;
        iop_cur = t;
        k = run(&iop_th[t].c, 20000000);
        iop_cur = -1;
        if (k == RUN_RET) {
            if (iop_th[t].in_rpc) {
                iop_th[t].in_rpc = 0;
                iop_th[t].state = TH_RPC_WAIT;
            } else {
                iop_th[t].state = TH_DORMANT; /* the thread's function returned: ExitThread */
            }
        } else if (k != RUN_BLOCK) {
            printf("kh1-iop: thread %d stopped (%s at 0x%05x)\n", t + 1, k == RUN_BUDGET ? "no block" : "fault",
                   iop_th[t].c.pc - KH1_IOP_BASE);
            iop_th[t].state = TH_DORMANT;
            iop_th[t].in_rpc = 0;
        }
        deliver_interrupts();
    }
}

static void wake_delayed(void) {
    int i;
    for (i = 0; i < IOP_THREADS; i++)
        if (iop_th[i].state == TH_DELAY) iop_th[i].state = TH_READY;
}

/* ---- the kernel and SIF ---- */

#define A(n) (c->r[4 + (n)])
/* the n-th word argument past the four in registers */
static u32 stack_arg(IopCtx *c, int n) { return rd32(c->r[29] + 16 + 4 * n, c->pc); }

static int block(IopCtx *c, int state) {
    /* resume after the call with 0 in v0 */
    c->r[2] = 0;
    c->pc = c->r[31];
    c->npc = c->pc + 4;
    if (iop_cur >= 0) iop_th[iop_cur].state = state;
    return RUN_BLOCK;
}

static void kprintf(IopCtx *c) {
    char out[256];
    const char *f = (const char *)kh1_iop_ptr(A(0), 1);
    int o = 0, n = 1;
    if (!f) return;
    while (*f && o < (int)sizeof out - 16) {
        u32 v;
        char spec[16];
        int k = 0;
        if (*f != '%') { out[o++] = *f++; continue; }
        spec[k++] = *f++;
        while (*f && k < 12 && ((*f >= '0' && *f <= '9') || *f == '-' || *f == '.' || *f == 'l')) spec[k++] = *f++;
        if (!*f) break;
        spec[k++] = *f;
        spec[k] = 0;
        if (*f == '%') { out[o++] = '%'; f++; continue; }
        v = n < 4 ? A(n) : stack_arg(c, n - 4);
        n++;
        if (*f == 's') {
            const char *s = (const char *)kh1_iop_ptr(v, 1);
            while (s && *s && o < (int)sizeof out - 16) out[o++] = *s++;
        } else {
            static const char hex[] = "0123456789abcdef";
            char tmp[12];
            int t = 0;
            if (*f == 'c') tmp[t++] = (char)v;
            else if (*f == 'x' || *f == 'X' || *f == 'p') do tmp[t++] = hex[v & 15]; while (v >>= 4);
            else {
                int neg = *f == 'd' && (s32)v < 0;
                if (neg) v = (u32)-(s32)v;
                do tmp[t++] = (char)('0' + v % 10); while (v /= 10);
                if (neg) tmp[t++] = '-';
            }
            if (*f != 'c') {
                int w = 0, i;
                for (i = 1; spec[i] >= '0' && spec[i] <= '9'; i++) w = w * 10 + spec[i] - '0';
                while (t < w && t < 11) tmp[t++] = spec[1] == '0' ? '0' : ' ';
                while (t) out[o++] = tmp[--t];
            } else out[o++] = tmp[0];
        }
        f++;
    }
    out[o] = 0;
    if (iop_log()) printf("kh1-iop: %s%s", out, o && out[o - 1] == '\n' ? "" : "\n");
}

static u32 vpl_alloc(IopVpl *p, u32 size) {
    u32 at = p->base;
    int i, j;
    size = (size + 15) & ~15u;
    if (p->n >= VPL_BLOCKS) return 0;
    /* blocks are kept in address order: find the first gap that fits */
    for (i = 0; i <= p->n; i++) {
        u32 end = i < p->n ? p->at[i] : p->base + p->size;
        if (end >= at && end - at >= size) {
            for (j = p->n; j > i; j--) { p->at[j] = p->at[j - 1]; p->len[j] = p->len[j - 1]; }
            p->at[i] = at;
            p->len[i] = size;
            p->n++;
            return at;
        }
        if (i < p->n) at = p->at[i] + p->len[i];
    }
    return 0;
}

static u32 vpl_free_bytes(IopVpl *p) {
    u32 used = 0;
    int i;
    for (i = 0; i < p->n; i++) used += p->len[i];
    return p->size - used;
}

/* The import answers.  RUN_RET: v0 set, return to $ra; RUN_BLOCK: the thread waits. */
static __attribute__((noinline)) int hle(IopCtx *c, const IopStub *s) {
    const char *lib = s->lib;
    int fn = s->fn;
    u32 *v0 = &c->r[2];
    *v0 = 0;
    if (!strcmp(lib, "libsd")) {
        u32 a[6];
        a[0] = A(0); a[1] = A(1); a[2] = A(2); a[3] = A(3);
        a[4] = stack_arg(c, 0); a[5] = stack_arg(c, 1);
        *v0 = kh1_sd_call(fn, a);
        return RUN_RET;
    }
    if (!strcmp(lib, "thbase")) {
        switch (fn) {
        case 4: { /* CreateThread(iop_thread_t *): attr, option, thread, stacksize, priority */
            u32 p = A(0);
            int i;
            for (i = 0; i < IOP_THREADS && iop_th[i].state != TH_FREE; i++)
                ;
            if (i == IOP_THREADS) { *v0 = (u32)-400; break; }
            memset(&iop_th[i], 0, sizeof iop_th[i]);
            iop_th[i].state = TH_DORMANT;
            iop_th[i].entry = rd32(p + 8, c->pc);
            iop_th[i].stack_size = rd32(p + 12, c->pc);
            iop_th[i].prio = (int)rd32(p + 16, c->pc);
            iop_th[i].stack = iop_alloc(iop_th[i].stack_size + 0x100);
            *v0 = (u32)(i + 1);
            break;
        }
        case 6: { /* StartThread(id, arg) */
            int i = (int)A(0) - 1;
            if (i < 0 || i >= IOP_THREADS || iop_th[i].state != TH_DORMANT) { *v0 = (u32)-1; break; }
            memset(&iop_th[i].c, 0, sizeof iop_th[i].c);
            iop_th[i].c.pc = iop_th[i].entry;
            iop_th[i].c.npc = iop_th[i].entry + 4;
            iop_th[i].c.r[4] = A(1);
            iop_th[i].c.r[29] = (iop_th[i].stack + iop_th[i].stack_size) & ~15u;
            iop_th[i].c.r[31] = IOP_MAGIC_RET;
            iop_th[i].c.r[28] = c->r[28];
            iop_th[i].state = TH_READY;
            break;
        }
        case 0x0E: { /* ChangeThreadPriority(id, prio) */
            int i = (int)A(0) - 1;
            if (A(0) == 0) i = iop_cur;
            if (i >= 0 && i < IOP_THREADS) iop_th[i].prio = (int)A(1);
            break;
        }
        case 0x14: *v0 = (u32)(iop_cur + 1); break; /* GetThreadId */
        case 0x21: return block(c, TH_DELAY);   /* DelayThread: wakes at the next tick */
        default: goto unknown;
        }
        return RUN_RET;
    }
    if (!strcmp(lib, "thsemap")) {
        switch (fn) {
        case 4: { /* CreateSema(iop_sema_t *): attr, option, initial, max */
            int i;
            for (i = 0; i < IOP_SEMAS && iop_sema[i].used; i++)
                ;
            if (i == IOP_SEMAS) { *v0 = (u32)-400; break; }
            iop_sema[i].used = 1;
            iop_sema[i].count = (int)rd32(A(0) + 8, c->pc);
            iop_sema[i].max = (int)rd32(A(0) + 12, c->pc);
            *v0 = (u32)(i + 1);
            break;
        }
        case 6: case 7: { /* SignalSema / iSignalSema */
            int i = (int)A(0) - 1, t;
            if (i < 0 || i >= IOP_SEMAS || !iop_sema[i].used) { *v0 = (u32)-1; break; }
            for (t = 0; t < IOP_THREADS; t++)
                if (iop_th[t].state == TH_WAIT_SEMA && iop_th[t].sema == i) break;
            if (t < IOP_THREADS) iop_th[t].state = TH_READY;
            else if (iop_sema[i].count < iop_sema[i].max) iop_sema[i].count++;
            break;
        }
        case 8: case 9: { /* WaitSema / PollSema */
            int i = (int)A(0) - 1;
            if (i < 0 || i >= IOP_SEMAS || !iop_sema[i].used) { *v0 = (u32)-1; break; }
            if (iop_sema[i].count > 0) { iop_sema[i].count--; break; }
            if (fn == 9 || iop_cur < 0) { *v0 = (u32)-419; break; }
            iop_th[iop_cur].sema = i;
            return block(c, TH_WAIT_SEMA);
        }
        default: goto unknown;
        }
        return RUN_RET;
    }
    if (!strcmp(lib, "thvpool")) {
        switch (fn) {
        case 4: { /* CreateVpl(iop_vpl_param_t *): attr, option, size */
            int i;
            u32 size = rd32(A(0) + 8, c->pc);
            for (i = 0; i < IOP_VPLS && iop_vpl[i].used; i++)
                ;
            if (i == IOP_VPLS) { *v0 = (u32)-400; break; }
            memset(&iop_vpl[i], 0, sizeof iop_vpl[i]);
            iop_vpl[i].base = iop_alloc(size);
            if (!iop_vpl[i].base) { *v0 = (u32)-400; break; }
            iop_vpl[i].size = size;
            iop_vpl[i].used = 1;
            *v0 = (u32)(i + 1);
            break;
        }
        case 5: { /* DeleteVpl: the heap is not given back (the driver makes one pool) */
            int i = (int)A(0) - 1;
            if (i >= 0 && i < IOP_VPLS) iop_vpl[i].used = 0;
            break;
        }
        case 6: case 7: case 8: { /* AllocateVpl / pAllocateVpl / ipAllocateVpl(id, size) */
            int i = (int)A(0) - 1;
            u32 at = i >= 0 && i < IOP_VPLS && iop_vpl[i].used ? vpl_alloc(&iop_vpl[i], A(1)) : 0;
            *v0 = at ? at : (u32)-427;
            break;
        }
        case 9: { /* FreeVpl(id, addr) */
            int i = (int)A(0) - 1, k;
            if (i < 0 || i >= IOP_VPLS) { *v0 = (u32)-1; break; }
            for (k = 0; k < iop_vpl[i].n && iop_vpl[i].at[k] != A(1); k++)
                ;
            if (k == iop_vpl[i].n) { *v0 = (u32)-1; break; }
            for (; k + 1 < iop_vpl[i].n; k++) { iop_vpl[i].at[k] = iop_vpl[i].at[k + 1]; iop_vpl[i].len[k] = iop_vpl[i].len[k + 1]; }
            iop_vpl[i].n--;
            break;
        }
        case 0x0B: { /* ReferVplStatus(id, iop_vpl_info_t *): attr, option, size, freeSize, numWaitThreads */
            int i = (int)A(0) - 1;
            if (i < 0 || i >= IOP_VPLS) { *v0 = (u32)-1; break; }
            wr32(A(1) + 0, 0, c->pc);
            wr32(A(1) + 4, 0, c->pc);
            wr32(A(1) + 8, iop_vpl[i].size, c->pc);
            wr32(A(1) + 12, vpl_free_bytes(&iop_vpl[i]), c->pc);
            wr32(A(1) + 16, 0, c->pc);
            break;
        }
        default: goto unknown;
        }
        return RUN_RET;
    }
    if (!strcmp(lib, "intrman")) {
        /* EnableIntr / CpuEnableIntr / CpuSuspendIntr(&state) / CpuResumeIntr: nothing interrupts a run */
        if (fn == 17 && A(0)) wr32(A(0), 0, c->pc);
        return RUN_RET;
    }
    if (!strcmp(lib, "loadcore")) return RUN_RET; /* FlushDcache */
    if (!strcmp(lib, "sysmem")) {
        switch (fn) {
        case 6: *v0 = KH1_IOP_RAM; break;                 /* QueryMemSize */
        case 7: case 8: *v0 = IOP_HEAP_END - iop_heap; break; /* QueryMaxFreeMemSize / QueryTotalFreeMemSize */
        case 14: kprintf(c); break;                        /* Kprintf */
        default: goto unknown;
        }
        return RUN_RET;
    }
    if (!strcmp(lib, "sysclib")) {
        switch (fn) {
        case 12: { /* memcpy */
            u8 *d = kh1_iop_ptr(A(0), A(2)), *sr = kh1_iop_ptr(A(1), A(2));
            if (d && sr) memcpy(d, sr, A(2));
            *v0 = A(0);
            break;
        }
        case 14: { /* memset */
            u8 *d = kh1_iop_ptr(A(0), A(2));
            if (d) memset(d, (int)A(1), A(2));
            *v0 = A(0);
            break;
        }
        case 22: { /* strcmp */
            const char *x = (const char *)kh1_iop_ptr(A(0), 1), *y = (const char *)kh1_iop_ptr(A(1), 1);
            *v0 = x && y ? (u32)strcmp(x, y) : 1;
            break;
        }
        default: goto unknown;
        }
        return RUN_RET;
    }
    if (!strcmp(lib, "sifcmd")) {
        switch (fn) {
        case 0x0E: case 0x13: break; /* sceSifInitRpc, sceSifSetRpcQueue */
        case 0x11:                   /* sceSifRegisterRpc(sd, sid, func, buf, cfunc, cbuf, qd) */
            rpc_sid = A(1);
            rpc_func = A(2);
            rpc_buf = A(3);
            if (iop_log()) printf("kh1-iop: RPC server %u: function 0x%05x, buffer 0x%05x\n", rpc_sid,
                                  rpc_func - KH1_IOP_BASE, rpc_buf - KH1_IOP_BASE);
            break;
        case 0x12: break; /* sceSifCheckStatRpc: never busy */
        case 0x16:        /* sceSifRpcLoop: the thread now answers kh1_iop_rpc */
            if (iop_cur < 0) goto unknown;
            rpc_thread = iop_cur;
            return block(c, TH_RPC_WAIT);
        case 0x17: { /* sceSifGetOtherData(rd, src (EE), dest (IOP), size, mode) */
            u32 size = A(3);
            u8 *d = kh1_iop_ptr(A(2), size);
            const u8 *src = (const u8 *)(unsigned long)A(1);
            if (d && src && size) memcpy(d, src, size);
            break;
        }
        default: goto unknown;
        }
        return RUN_RET;
    }
    if (!strcmp(lib, "sifman")) {
        switch (fn) {
        case 5: break; /* sceSifInit */
        case 7: {      /* sceSifSetDma(transfers, count): {src (IOP), dest (EE), size, attr} each */
            u32 p = A(0), n = A(1), k;
            for (k = 0; k < n; k++, p += 16) {
                u32 src = rd32(p, c->pc), size = rd32(p + 8, c->pc);
                u8 *dst = (u8 *)(unsigned long)rd32(p + 4, c->pc);
                const u8 *from = kh1_iop_ptr(src, size);
                if (dst && from && size) memcpy(dst, from, size);
            }
            *v0 = 1;
            break;
        }
        case 8: *v0 = (u32)-1; break;  /* sceSifDmaStat: done */
        case 0x1D: *v0 = 1; break;     /* sceSifCheckInit */
        default: goto unknown;
        }
        return RUN_RET;
    }
    if (!strcmp(lib, "timrman")) {
        switch (fn) {
        case 4: *v0 = 1; break; /* AllocHardTimer(source, size, prescale) */
        case 10: *v0 = tm_count; break; /* GetTimerCounter */
        case 20: /* SetTimerHandler(id, compare, handler, arg) */
            tm_compare = A(1);
            tm_handler = A(2);
            tm_arg = A(3);
            break;
        case 22: break; /* SetupHardTimer */
        case 23: tm_started = 1; break; /* StartHardTimer */
        default: goto unknown;
        }
        return RUN_RET;
    }
    if (!strcmp(lib, "cdvdman")) {
        *v0 = 0; /* the drive's status / error: nothing to report (no tray, no read error) */
        return RUN_RET;
    }
unknown:
    printf("kh1-iop: import %s %d not answered (0x%x 0x%x 0x%x 0x%x)\n", lib, fn, A(0), A(1), A(2), A(3));
    *v0 = 0;
    return RUN_RET;
}

/* ---- the loader ---- */

static u32 le32(const u8 *p) { return p[0] | p[1] << 8 | p[2] << 16 | (u32)p[3] << 24; }
static u32 le16(const u8 *p) { return p[0] | p[1] << 8; }

static char stub_names[16][9];

static void find_imports(u32 text, u32 size) {
    u32 a;
    int nlib = 0;
    iop_nstubs = 0;
    for (a = text; a + 20 <= text + size; a += 4) {
        u32 p;
        char *name;
        if (*(u32 *)RAM(a) != 0x41E00000 || nlib == 16) continue;
        name = stub_names[nlib++];
        memcpy(name, RAM(a + 12), 8);
        name[8] = 0;
        for (p = a + 20; p + 8 <= text + size && iop_nstubs < IOP_STUBS; p += 8) {
            u32 w0 = *(u32 *)RAM(p), w1 = *(u32 *)RAM(p + 4);
            if (w0 != 0x03E00008 || (w1 & 0xFFFF0000) != 0x24000000) break;
            iop_stub[iop_nstubs].addr = p;
            iop_stub[iop_nstubs].lib = name;
            iop_stub[iop_nstubs].fn = (int)(w1 & 0xFFFF);
            *(u32 *)RAM(p) = OP_STUB | (u32)iop_nstubs; /* run() answers it from the table */
            iop_nstubs++;
        }
        a = p;
    }
}

static int relocate(const u8 *f, u32 size, u32 shoff, u32 shnum, u32 base) {
    u32 i;
    for (i = 0; i < shnum; i++) {
        const u8 *sh = f + shoff + i * 40;
        u32 k, n, off, hi_pend[64];
        int nhi = 0;
        if (le32(sh + 4) != 9) continue; /* SHT_REL */
        off = le32(sh + 16);
        n = le32(sh + 20) / 8;
        if (off + n * 8 > size) return -1;
        for (k = 0; k < n; k++) {
            u32 at = base + le32(f + off + 8 * k), type = f[off + 8 * k + 4] & 0xFF, w;
            if (!RAM_OK(at)) return -1;
            w = *(u32 *)RAM(at);
            switch (type) {
            case 2: *(u32 *)RAM(at) = w + base; break; /* R_MIPS_32 */
            case 4: /* R_MIPS_26 */
                *(u32 *)RAM(at) = (w & 0xFC000000) | ((((w & 0x03FFFFFF) << 2) + base) >> 2 & 0x03FFFFFF);
                break;
            case 5: /* R_MIPS_HI16: fixed with the LO16 that follows */
                if (nhi < 64) hi_pend[nhi++] = at;
                break;
            case 6: { /* R_MIPS_LO16 */
                u32 lo = w & 0xFFFF, j;
                for (j = 0; j < (u32)nhi; j++) {
                    u32 hw = *(u32 *)RAM(hi_pend[j]);
                    u32 v = ((hw & 0xFFFF) << 16) + (u32)(s32)(s16)lo + base;
                    *(u32 *)RAM(hi_pend[j]) = (hw & 0xFFFF0000) | (((v + 0x8000) >> 16) & 0xFFFF);
                }
                nhi = 0;
                *(u32 *)RAM(at) = (w & 0xFFFF0000) | ((lo + base) & 0xFFFF);
                break;
            }
            case 0: break;
            default:
                printf("kh1-iop: relocation type %u not handled\n", type);
                return -1;
            }
        }
    }
    return 0;
}

int kh1_iop_loaded(void) { return iop_ok; }

int kh1_iop_load(const u8 *f, u32 size) {
    u32 shoff, shnum, i, entry = 0, gp = 0, text = 0, text_size = 0, ret;
    if (size < 0x34 || memcmp(f, "\177ELF", 4) != 0) return -1;
    memset(kh1_iop_ram, 0, sizeof kh1_iop_ram);
    memset(iop_th, 0, sizeof iop_th);
    memset(iop_sema, 0, sizeof iop_sema);
    memset(iop_vpl, 0, sizeof iop_vpl);
    rpc_sid = (u32)-1;
    rpc_thread = -1;
    tm_started = 0;
    tm_handler = 0;
    trans_func[0] = trans_func[1] = 0;
    trans_pending[0] = trans_pending[1] = 0;
    iop_ok = 0;
    shoff = le32(f + 0x20);
    shnum = le16(f + 0x30);
    if (shoff + shnum * 40 > size) return -1;
    iop_mod_end = KH1_IOP_BASE;
    for (i = 0; i < shnum; i++) {
        const u8 *sh = f + shoff + i * 40;
        u32 type = le32(sh + 4), flags = le32(sh + 8), addr = le32(sh + 12), off = le32(sh + 16), sz = le32(sh + 20);
        if (type == 0x70000080 && off + 12 <= size) { /* .iopmod: module info, entry, gp */
            entry = le32(f + off + 4);
            gp = le32(f + off + 8);
        }
        if (!(flags & 2)) continue; /* SHF_ALLOC */
        if (KH1_IOP_BASE + addr + sz > IOP_HEAP_END) return -1;
        if (type == 1) { /* PROGBITS */
            if (off + sz > size) return -1;
            memcpy(RAM(KH1_IOP_BASE + addr), f + off, sz);
            if (flags & 4) { text = KH1_IOP_BASE + addr; text_size = sz; }
        }
        if (KH1_IOP_BASE + addr + sz > iop_mod_end) iop_mod_end = KH1_IOP_BASE + addr + sz;
    }
    if (!text || relocate(f, size, shoff, shnum, KH1_IOP_BASE) != 0) return -1;
    {
        int rec = rec_check(), k;
        find_imports(text, text_size);
        if (rec && (k = rec_patch()) > 0)
            printf("kh1-iop: the driver runs as C (%d functions translated at build time)\n", k);
        else if ((k = patch_natives()) > 0)
            printf("kh1-iop: %d of the driver's functions run as C\n", k);
        if (!rec_live && iop_rec_on) /* 2026-11-01: said plainly, three Vita builds ran this way unnoticed */
            printf("kh1-iop: WARNING: the driver is NOT translated (%s): it runs on the interpreter, ~2.5x the sound's "
                   "CPU\n", !REC_N ? "built without LIBSSL.IRX" : "the disc's driver does not match the build's");
    }
    iop_heap = (iop_mod_end + 0xFFF) & ~0xFFFu;
    if (iop_log()) printf("kh1-iop: module at 0x%x..0x%x, entry +0x%x, %d imports\n", KH1_IOP_BASE, iop_mod_end, entry,
                          iop_nstubs);
    ret = call_func(KH1_IOP_BASE + entry, 0, 0, 0, 0, IOP_INTR_STACK);
    (void)gp;
    if ((ret & 3) == 1) { /* NO_RESIDENT_END */
        printf("kh1-iop: the module did not stay resident (%u)\n", ret);
        return -1;
    }
    schedule();
    iop_ok = rpc_thread >= 0;
    if (!iop_ok) printf("kh1-iop: the module registered no RPC server\n");
    return iop_ok ? 0 : -1;
}

/* ---- the interfaces ---- */

int kh1_iop_rpc(u32 sid, u32 fno, const void *send, int ssize, void *recv, int rsize) {
    IopThread *t;
    u8 *buf;
    int guard;
    if (!iop_ok || sid != rpc_sid || rpc_thread < 0) return -1;
    t = &iop_th[rpc_thread];
    if (t->state != TH_RPC_WAIT) return -1;
    buf = kh1_iop_ptr(rpc_buf, (u32)ssize);
    if (buf && send && ssize > 0) memcpy(buf, send, (unsigned)ssize);
    t->c.pc = rpc_func;
    t->c.npc = rpc_func + 4;
    t->c.r[4] = fno;
    t->c.r[5] = rpc_buf;
    t->c.r[6] = (u32)ssize;
    t->c.r[31] = IOP_MAGIC_RET;
    t->in_rpc = 1;
    t->state = TH_READY;
    /* a call that waits on another thread (a delay) gets time to pass until it answers */
    for (guard = 0; guard < 64; guard++) {
        schedule();
        if (!t->in_rpc) break;
        wake_delayed();
    }
    if (t->in_rpc) {
        printf("kh1-iop: RPC %u did not finish\n", fno);
        return -1;
    }
    if (recv && rsize > 0) {
        const u8 *ans = kh1_iop_ptr(t->c.r[2], (u32)rsize);
        if (ans) memcpy(recv, ans, (unsigned)rsize);
    }
    return 0;
}

void kh1_iop_tick(void) {
    if (!iop_ok) return;
    wake_delayed();
    if (tm_started && tm_handler) {
        u32 next = call_func(tm_handler, tm_arg, 0, 0, 0, IOP_INTR_STACK);
        if (next) tm_compare = next;
        tm_count += tm_compare;
    }
    schedule();
}

u32 kh1_iop_timer_hz(void) { return tm_started && tm_compare ? 36864000u / tm_compare : 0; }

void kh1_iop_raise_trans(int core) { trans_pending[core & 1] = 1; }

void kh1_iop_set_trans_handler(int core, u32 func, u32 arg) {
    trans_func[core & 1] = func;
    trans_arg[core & 1] = arg;
}
