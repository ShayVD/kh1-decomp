/* The script VM, 0x001c08e8-0x001c4ed0 (docs/modules.md), in address order:
 *
 * - 0x001c08e8-0x001c1d20: the instruction handlers (30 of the 32 entries of
 *   D_0037A198; func_001cd208 and func_001dcad0 live far away), the helpers
 *   they call (the variable clamp, the save block accessors) and the script
 *   fetch pair func_001c1ce8 / func_001c1cf8;
 * - 0x001c1d20-0x001c4ed0: the runtime: the interpreter loops that run the
 *   handlers, the script loaders that set the VM tables up, the per-frame
 *   drivers, and the two message queues the VMs and the game talk through.
 *
 * Both halves match together in this one file (session 30), so they were
 * probably one translation unit.  Four functions need other flags and are in
 * the sibling files (docs/modules.md "Flags"): func_001c1718 in
 * script_vm.nosi.c; func_001c1980, func_001c3770, func_001c4808 and
 * func_001c48c8 in script_vm.nostrict.c. */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/script_vm.h"
#include "vm/vm_mgr.h"
#include "vm/vm_find.h"
#include "data/data_0038.h"
#include "data/data_003C.h"
#include "data/pieces/D_0038D170.h"
#include "data/pieces/D_0039A580.h"
#include "data/pieces/D_003A7990.h"
#include "data/pieces/D_003B4DA0.h"
#include "data/pieces/D_003C3A70.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_0037A21C.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00388480.h"
#include "data/pieces/D_00389C80.h"
#include "data/pieces/D_003C21A8.h"

extern VmMgr D_00389C90;
extern s32 D_0039A570, D_003A7980, D_003B4D90, D_003C21A0, D_003C54F0;
extern s32 D_002C5950[]; /* D_002C5950[2] is D_002C5958 */
extern s32 D_003F34A4, D_0037A190, D_002BCDEC;
extern volatile s32 D_002BBE04;
extern u32 D_003C39A8;
extern s8 *D_003C39AC;
extern u8 D_006297F8[];

/* func_001c1f80's copy of D_002C5AD0 */
typedef struct { u64 w[14]; } B112;
extern B112 D_002C5AD0;

typedef struct {
    u8 pad0[4];
    u32 x4;
    u32 x8;
    u8 padc[0x34];
    s32 x40[3];
    u8 pad4c[0x14];
    s32 x60[3];
} S5BB0;
extern S5BB0 D_002C5BB0;

/* The task func_001c4198 starts for func_001c3b10 (func_0011f090). */
typedef struct {
    u8 pad0[0x10];
    VmRec *vm;
    s32 n;
    s32 x18;
} VmTask;

typedef struct Actor { u8 pad[16]; f32 pos[4]; } Actor;
typedef struct { s32 x0; s32 id; } Obj;

/* The message queues: D_006257E0 (VMs -> game: func_001c4640 puts,
 * func_001c45e8 takes) and D_006277F0 (game -> VMs: func_001c4788 puts,
 * func_001c4730 takes). */
extern VmMsg D_006257E0[256], D_006277F0[256];
extern s32 D_006277E0, D_006277E4, D_006297F0, D_006297F4;

void *func_0011ef10(s32, void *);
void *func_00232cc0(s32);
VmTask *func_0011f090(void *, s32, void *);
s32 func_00123488(s32);
void func_0012cb78(Obj *, s32);
void func_0012cc38(s32, s32);
void func_0012ccb0(s32);
s32 func_00146878(void);
void func_001c5b88(void);
void func_001c6720(void);
void func_001ca800(void);
void func_001cab48(void);
void func_001cebe8(void);
void func_001cff28(void);
void func_001cfff8(void);
s32 func_001d59a0(VmRec *);
void func_001d8f38(void);
void func_001dcea8(VmRec *);
void func_001dcfd0(VmRec *);
void func_001dd1f0(s32, s32);
s32 func_001ee200(void);
void func_002675a8(void *, void *);
void srand(u32);

/* op 0: nop */
s32 func_001c08e8(void) {
    return 2;
}

/* op 2: jump by `off` */
s32 func_001c08f0(VmRec *v, s32 off) {
    v->pc += off;
    return off < 0 ? 4 : 1;
}

/* op 3: pop; jump by `off` if it was 0 */
s32 func_001c0910(VmRec *v, s32 off) {
    if (v->stk[v->sp--] == 0) {
        v->pc += off;
        return off < 0 ? 4 : 1;
    }
    return 2;
}

/* op 4: nop */
s32 func_001c0960(void) {
    return 2;
}

/* op 6: pop into variable bank slot `i` (selects it) */
s32 func_001c0968(VmRec *v, s32 i) {
    v->x270[i] = v->stk[v->sp];
    v->x2f0 = i;
    v->sp--;
    return 2;
}

/* op 7: push (selected slot == x) */
s32 func_001c09a0(VmRec *v, s32 x) {
    v->sp++;
    if (v->x270[v->x2f0] == x) v->stk[v->sp] = 1;
    else v->stk[v->sp] = 0;
    return 2;
}

/* op 26: push (selected slot < x) */
s32 func_001c09e8(VmRec *v, s32 x) {
    v->sp++;
    if (v->x270[v->x2f0] < x) v->stk[v->sp] = 1;
    else v->stk[v->sp] = 0;
    return 2;
}

/* op 27: push (selected slot <= x) */
s32 func_001c0a38(VmRec *v, s32 x) {
    v->sp++;
    if (v->x270[v->x2f0] <= x) v->stk[v->sp] = 1;
    else v->stk[v->sp] = 0;
    return 2;
}

/* op 28: push (selected slot > x) */
s32 func_001c0a88(VmRec *v, s32 x) {
    v->sp++;
    if (v->x270[v->x2f0] > x) v->stk[v->sp] = 1;
    else v->stk[v->sp] = 0;
    return 2;
}

/* op 29: push (selected slot >= x) */
s32 func_001c0ad8(VmRec *v, s32 x) {
    v->sp++;
    if (v->x270[v->x2f0] >= x) v->stk[v->sp] = 1;
    else v->stk[v->sp] = 0;
    return 2;
}

/* op 8: select the previous slot */
s32 func_001c0b28(VmRec *v) {
    v->x2f0--;
    return 2;
}

/* op 5: return: drop this return level, resume at the next one set */
s32 func_001c0b40(VmRec *v) {
    s32 i;
    if (v->rsp == 7) {
        v->fl.x |= 8;
        return 4;
    }
    v->ret[v->rsp] = -1;
    for (i = v->rsp + 1; i < 8; i++) {
        s32 r = v->ret[i];
        if (r != -1) {
            v->pc = r;
            v->rsp = i;
            break;
        }
    }
    return 4;
}

s64 func_001c0bf0(s64 x, u32 type) {
    switch (type) {
    case 0:
    case 1:
        x &= 1;
    case 2:
        if (x < -128) x = -128;
        else if (x >= 127) x = 127;

        break;
    case 3:
        if (x < -32768) x = -32768;
        else if (x >= 32767) x = 32767;

        break;
    case 4:
        if (x < -0x800000) x = -0x800000;
        else if (x >= 0x7fffff) x = 0x7fffff;
        break;
    case 5:
        if (x < 0) x = 0;
        else if (x >= 255) x = 255;

        break;
    case 6:
        if (x < 0) x = 0;
        else if (x >= 0xffff) x = 0xffff;

        break;
    case 7:
        if (x < 0) x = 0;
        else if (x >= 0xffffff) x = 0xffffff;
        break;
    }
    return x;
}

/* op 9: push the argument clamped to s24 */
s32 func_001c0d20(VmRec *v, s32 arg) {
    s32 x = func_001c0bf0(arg, 4);
    v->stk[++v->sp] = x;
    return 2;
}

/* op 10: push register `i` */
s32 func_001c0d70(VmRec *v, s32 i) {
    v->sp++;
    v->stk[v->sp] = v->var[i];
    return 2;
}

void func_001c0da0(s32 off, s32 size, void *dst) {
    u8 *p = func_00232cc0(2);
    switch (size) {
    case 1: *(u8 *)dst = *(u8 *)(p + off); break;
    case 2: *(u16 *)dst = *(u16 *)(p + off); break;
    case 4: *(u32 *)dst = *(u32 *)(p + off); break;
    }
}

s32 func_001c0e50(s32 off) {
    return (s32)func_00232cc0(2) + off;
}

void func_001c0e80(s32 off, s32 size, void *src) {
    s32 p = (s32)func_00232cc0(2);
    switch (size) {
    case 1:
        *(s8 *)(p + off) = *(s32 *)src;
        return;
    case 2:
        *(s16 *)(p + off) = (u16)*(s32 *)src;
        break;
    case 4:
        *(s32 *)(p + off) = *(s32 *)src;
        break;
    }
}

/* op 12: push s8 variable `idx` */
s32 func_001c0f30(VmRec *v, s32 idx) {
    s8 *a = func_00232cc0(1);
    s8 *b = func_00232cc0(2);
    v->stk[32] = idx;
    if (idx < 0x800) {
        v->stk[++v->sp] = a[idx];
    } else if (idx < 0x900) {
        v->stk[++v->sp] = a[idx];
    } else if (idx < 0xb00) {
        idx -= 0x900;
        if ((s32)(v->fl.x >> 5) & 1) {
            v->stk[++v->sp] = D_0038B4C4[idx];
        } else {
            v->stk[++v->sp] = D_0038ACC4[idx];
        }
    } else if (idx < 0xc80) {
        v->stk[++v->sp] = *(u8 *)(idx + (u32)a - 0x200);
    } else if (idx < 0xcc0) {
        v->stk[++v->sp] = D_003C2D30[idx];
    } else if (idx < 0xd00) {
        v->stk[++v->sp] = D_003C2D30[idx];
    } else if (idx < 0xd40) {
        v->stk[++v->sp] = D_003C2D30[idx];
    } else {
        v->stk[++v->sp] = *(s8 *)(idx + (u32)b - 0xd40);
    }
    return 2;
}

/* op 14: push s16 variable `a` */
s32 func_001c1118(VmRec *v, s32 a) {
    u8 *p1 = func_00232cc0(1);
    u8 *p2 = func_00232cc0(2);
    s16 x;
    v->stk[32] = a;
    if (a < 2048) {
        v->sp++;
        v->stk[v->sp] = *(s16 *)(p1 + a);
        return 2;
    }
    if (a < 2304) {
        v->sp++;
        v->stk[v->sp] = *(s16 *)(a + (s32)p1);
    } else {
        v->sp++;
        v->stk[v->sp] = *(s16 *)(a + (s32)p2 - 3392);
    }
    return 2;
}

/* op 16: push s32 variable `a` */
s32 func_001c11d8(VmRec *v, s32 a) {
    u8 *p1 = func_00232cc0(1);
    u8 *p2 = func_00232cc0(2);
    v->stk[32] = a;
    if (a < 2048) {
        v->sp++;
        v->stk[v->sp] = *(s32 *)(p1 + a);
    } else if (a < 2304) {
        v->sp++;
        v->stk[v->sp] = *(s32 *)(a + (s32)p1);
    } else if (a < 2816) {
        a -= 2304;
        if ((s32)(v->fl.x >> 5) & 1) {
            v->sp++;
            v->stk[v->sp] = D_0038B4C4[a];
        } else {
            v->sp++;
            v->stk[v->sp] = D_0038ACC4[a];
        }
    } else {
        v->sp++;
        v->stk[v->sp] = *(s32 *)(a + (s32)p2 - 3392);
    }
    return 2;
}

/* op 18: nop */
s32 func_001c1318(void) {
    return 2;
}

/* op 19: nop */
s32 func_001c1320(void) {
    return 2;
}

/* op 20: nop */
s32 func_001c1328(void) {
    return 2;
}

/* op 30: push bit variable `a` */
s32 func_001c1330(VmRec *v, s32 a) {
    u8 *p1 = func_00232cc0(1);
    u8 *p2 = func_00232cc0(2);
    s32 bit = a % 8;
    s32 q = a / 8;
    a = q - 3392;
    v->stk[++v->sp] = (*(s8 *)(p2 + a) >> bit) & 1;
    return 2;
}

/* op 11: pop into register `i` */
s32 func_001c13b8(VmRec *v, s32 i) {
    v->var[i] = v->stk[v->sp--];
    return 2;
}

/* op 13: pop into s8 variable `idx` */
s32 func_001c13e8(VmRec *v, s32 idx) {
    s8 *a = func_00232cc0(1);
    s8 *b = func_00232cc0(2);
    if (idx < 0x800) {
        a[idx] = func_001c0bf0(v->stk[v->sp], 2);
        v->sp--;
    } else if (idx < 0x900) {
        idx -= 0x800;
        *(u8 *)(idx + (u32)a + 0x800) = func_001c0bf0(v->stk[v->sp], 2);
        v->sp--;
    } else if (idx < 0xb00) {
        idx -= 0x900;
        if ((s32)(v->fl.x >> 5) & 1) {
            D_0038B4C4[idx] = v->stk[v->sp];
            v->sp--;
        } else {
            D_0038ACC4[idx] = v->stk[v->sp];
            v->sp--;
        }
    } else if (idx < 0xc80) {
        *(u8 *)(idx + (u32)a - 0x200) = v->stk[v->sp];
        v->sp--;
    } else if (idx < 0xcc0) {
        idx -= 0xc80;
        D_003C39B0[idx] = func_001c0bf0(v->stk[v->sp], 2);
        v->sp--;
    } else if (idx < 0xd00) {
        idx -= 0xcc0;
        D_003C39F0[idx] = func_001c0bf0(v->stk[v->sp], 2);
        v->sp--;
    } else if (idx < 0xd40) {
        idx -= 0xd00;
        D_003C3A30[idx] = func_001c0bf0(v->stk[v->sp], 2);
        v->sp--;
    } else {
        idx -= 0xd40;
        b[idx] = func_001c0bf0(v->stk[v->sp], 2);
        v->sp--;
    }
    return 2;
}

/* op 15: pop into s16 variable `a` */
s32 func_001c1628(VmRec *v, s32 a) {
    u8 *p1 = func_00232cc0(1);
    u8 *p2 = func_00232cc0(2);
    if (a < 2048) {
        *(u16 *)(p1 + a) = func_001c0bf0(v->stk[v->sp], 3);
        v->sp--;
    } else if (a < 2304) {
        a -= 2048;
        *(u16 *)(p1 + a + 2048) = func_001c0bf0(v->stk[v->sp], 3);
        v->sp--;
    } else {
        a -= 3392;
        *(u16 *)(p2 + a) = func_001c0bf0(v->stk[v->sp], 3);
        v->sp--;
    }
    return 2;
}

/* func_001c1718 (op 17: pop into s32 variable): script_vm.nosi.c */

/* op 31: pop into bit variable `a` */
s32 func_001c1880(VmRec *v, s32 a) {
    u8 *p1 = func_00232cc0(1);
    u8 *p2 = func_00232cc0(2);
    s32 bit = a % 8;
    s32 q = a / 8;
    u8 *p;
    if (v->stk[v->sp] >= 2) {
        v->stk[v->sp] = 1;
    } else if (v->stk[v->sp] < 0) {
        v->stk[v->sp] = 0;
    }
    a = q - 3392;
    p = p2 + a;
    *p &= ~(1 << bit);
    *p |= v->stk[v->sp] << bit;
    v->sp--;
    return 2;
}

/* op 21: push the argument */
s32 func_001c1960(VmRec *v, s32 arg) {
    v->sp++;
    v->stk[v->sp] = arg;
    return 2;
}

/* func_001c1980 (jump another VM): script_vm.nostrict.c */

/* op 22: pop VM id and level; jump that VM to its label `k` */
s32 func_001c19f8(VmRec *vm, s32 k) {
    s32 a = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    VmRec *p;
    if (b < 0) b = 0;
    else if (b >= 8) b = 7;
    p = func_001e98d0((s32)(vm->fl.x >> 5) & 1, a);
    func_001c1980(p, b, p->lbl[k]);
    return 2;
}

/* op 23: pop VM id and level; wait while that VM has the level set */
s32 func_001c1aa8(VmRec *vm) {
    s32 a = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    VmRec *p;
    if (b < 0) b = 0;
    else if (b >= 8) b = 7;
    p = func_001e98d0((s32)(vm->fl.x >> 5) & 1, a);
    if (p->ret[b] != -1) {
        vm->pc -= 2;
        return 4;
    }
    return 2;
}

/* op 25: pop VM id and level; clear that level of that VM */
s32 func_001c1b58(VmRec *v) {
    s32 id, lvl, j;
    VmRec *t;
    VmMsg m;
    id = v->stk[v->sp--];
    lvl = v->stk[v->sp--];
    if (lvl < 0) lvl = 0;
    else if (lvl >= 8) lvl = 7;
    t = func_001e98d0((s32)(v->fl.x >> 5) & 1, id);
    if (t == v) return 6;
    t->ret[lvl] = -1;
    if (lvl != t->rsp) return 2;
    for (j = lvl + 1; j < 8; j++) {
        if (t->ret[j] != -1) {
            t->pc = t->ret[j];
            t->rsp = j;
            break;
        }
    }
    if ((u32)t->fl.i[0] % 2 == 1) {
        m.type = 18;
        m.val = 0;
        m.v[0] = 0.0f;
        m.v[1] = 0.0f;
        m.v[2] = 0.0f;
        m.v[3] = 1.0f;
        m.x = t->x0;
        func_001c4640(&m);
        t->fl.x &= ~1;
    }
    return 2;
}

/* opcode of instruction `pc` */
s32 func_001c1ce8(s8 *code, s32 pc) {
    return code[pc * 4 + 3];
}

/* argument (s24) of instruction `pc` */
s32 func_001c1cf8(s8 *code, s32 pc) {
    u8 *p = (u8 *)(pc * 4 + (s32)code);
    return p[0] | (p[1] << 8) | (((s8 *)p)[2] << 16);
}

void func_001c1d20(VmRec *vm, s32 k) {
    s32 saved = vm->pc;
    s32 op, arg, r;
    vm->pc = vm->lbl[k];
    for (;;) {
        op = func_001c1ce8(vm->code, vm->pc);
        arg = func_001c1cf8(vm->code, vm->pc);
        if (op == 5) break;
        r = D_0037A198[op](vm, arg);
        if (r & 2) vm->pc++;
        if (r & 4) goto out;
        if (r & 8) goto out;
    }
out:
    vm->pc = saved;
}

s32 func_001c1df8(void) {
    if (D_003F34A4 == 1) return 0;
    D_00389C90.f3078.x &= ~0x1000;
    return 4;
}

s32 func_001c1e30(void) {
    f32 mn[4], mx[4], p[4];
    s32 i;
    if (D_002E26A0[0] == 0) return 0;
    func_002675a8(p, D_002E26A0[0]->pos);
    for (i = 0; i < D_00389C90.nbox; i++) {
        mn[0] = D_00389C90.u.box[i].c[0] - D_00389C90.u.box[i].s[0] * 0.5f;
        mn[1] = D_00389C90.u.box[i].c[1] - D_00389C90.u.box[i].s[1] * 0.5f;
        mn[2] = D_00389C90.u.box[i].c[2] - D_00389C90.u.box[i].s[2] * 0.5f;
        mx[0] = D_00389C90.u.box[i].c[0] + D_00389C90.u.box[i].s[0] * 0.5f;
        mx[1] = D_00389C90.u.box[i].c[1] + D_00389C90.u.box[i].s[1] * 0.5f;
        mx[2] = D_00389C90.u.box[i].c[2] + D_00389C90.u.box[i].s[2] * 0.5f;
        if (mn[0] <= p[0] && p[0] <= mx[0] && mn[1] <= p[1] && p[1] <= mx[1] && mn[2] <= p[2] && p[2] <= mx[2])
            return D_00389C90.u.box[i].id;
    }
    return 0;
}

void func_001c1f60(void) {
    D_00389C90.f3070.x = (s64) (D_00389C90.f3070.x | ((s64) 0x8000 << 0x19));
}

s32 func_001c1f80(void) {
    VmMsg m;
    B112 tmp = D_002C5AD0;
    VmMsg list[256];
    s32 n = 0;
    VmRec *vm;
    s32 *cnt;
    s32 i, j, r, k, op, arg;
    VmMsg *p;
    VmRec *v;

    if (D_00389C90.f3070.b.b40) return 4;
    if (D_00389C90.x3038 > 0) {
        if (D_00389C90.x3034 == 0) { vm = D_0038D170; cnt = &D_0039A570; }
        else { vm = D_0039A580; cnt = &D_003A7980; }
        for (i = 0; i < *cnt; i++, vm++) {
            if ((vm->fl.x & 0x14) == 4) {
                vm->x2f4 -= D_002BBDFC;
                if (!(0.0f < vm->x2f4)) vm->fl.x &= ~4;
            }
        }
        return 0;
    }
    D_0037A190 = 0;
    D_00389C90.x316c = 0;
    if ((*(Bits_37a378 *)&D_0037A378).b2) return 0;
    if (D_00389C90.f3078.b.b12 == 1) return 0;
    if (D_00389C90.f3078.b.b13 == 1) return 0;
    k = func_001c1e30();
    if (k > 0 && D_00389C90.x3034 == 0) {
        func_001c2ec8(D_00389C90.x3040, k);
        return 0;
    }
    D_002C5BB0.x4 &= D_00389C90.x3148;
    D_002C5BB0.x8 &= D_00389C90.x3148;
    if (~(D_00389C90.x3148 >> 23) & 1) {
        for (i = 0; i < 3; i++) {
            D_002C5BB0.x40[i] = 0;
            D_002C5BB0.x60[i] = 0;
        }
    }
    if (D_00389C90.f3078.b.b11) D_002C5958 &= ~0x1000;
    for (i = 0; i < 8; i++) {
        D_00389C90.u.s.e[i].obj = 0;
        D_00389C90.u.s.e[i].x4 = -1;
        D_00389C90.u.s.e[i].snd = -1;
        D_00389C90.u.s.e[i].x10 = 1;
        D_00389C90.u.s.e[i].ret = 0;
        D_00389C90.u.s.e[i].h = -1;
    }
    if (D_00389C90.x3034 == 0) { vm = D_0038D170; cnt = &D_0039A570; }
    else { vm = D_0039A580; cnt = &D_003A7980; }
    p = func_001c4730();
    while (p) {
        list[n++] = *p;
        p = func_001c4730();
    }
    if (D_00389C90.f3070.b.b43 == 1) func_001cebe8();
    if (D_00389C90.f3070.b.b38 == 1) func_001cff28();
    if (D_00389C90.f3070.b.b39 == 1) func_001cfff8();
    if (D_00389C90.f3078.b.b1 == 1) func_001d8f38();
    if (D_00389C90.f3078.b.b10) func_001ca800();
    if (D_00389C90.f3070.b.b53) return 0;
    for (i = 0; i < *cnt; i++, vm++) {
        if (vm->fl.b.b3) {
            if (i != 0) continue;
            if (D_00389C90.x3034 != 0) {
                v = D_0038D170;
                D_00389C90.x3034 = 0;
                for (j = 1, v++; j < D_0039A570; j++, v++) {
                    if ((u32)v->fl.i[0] % 2 == 1) {
                        m.type = 2;
                        m.val = (u32)v->f20;
                        m.x = v->x0;
                        m.v[0] = v->f14[0];
                        m.v[1] = v->f14[1];
                        m.v[2] = v->f14[2];
                        m.v[3] = 10.0f;
                        func_001c4640(&m);
                    }
                }
                for (i = 0; i < 512; i++) {
                    D_00389C90.a1034[i] = D_00389C90.a2034[i];
                    D_00389C90.a1834[i] = D_00389C90.a2834[i];
                }
                return 0;
            }
            if (D_002BBDE0 == 3) {
                D_002C5958 &= ~8;
                D_002C5958 &= ~4;
            }
            return 4;
        }
        if (vm->fl.b.b8) continue;
        if (vm->fl.b.b13) {
            if (!func_00146878()) continue;
            vm->fl.x &= ~0x2000;
        }
        func_001dcea8(vm);
        func_001dcfd0(vm);
        if ((vm->fl.x & 0x14) == 4) {
            vm->x2f4 -= D_002BBDFC;
            if (0.0f < vm->x2f4) continue;
            vm->fl.x &= ~4;
        }
        for (j = 0; j < n; j++) {
            p = &list[j];
            switch (p->type) {
            case 2:
                if (p->x == vm->x0) {
                    vm->fl.x &= ~1;
                    if ((*(Bits_37a378 *)&D_0037A378).b0) {
                        m.type = 3;
                        m.val = 0;
                        m.x = vm->x0;
                        m.v[0] = vm->f14[0];
                        m.v[1] = vm->f14[1];
                        m.v[2] = vm->f14[2];
                        m.v[3] = 1.0f;
                        func_001c4640(&m);
                    }
                }
                break;
            case 4:
                if (p->x == vm->x0) vm->fl.x &= ~2;
                break;
            case 21:
                if (p->x == vm->x0) vm->fl.x &= ~2;
                break;
            case 22:
                if (p->x == vm->x0) vm->fl.x &= ~2;
                break;
            }
        }
        for (;;) {
            op = func_001c1ce8(vm->code, vm->pc);
            arg = func_001c1cf8(vm->code, vm->pc);
            r = D_0037A198[op](vm, arg);
            if (r & 2) vm->pc++;
            if (r & 4) break;
            if (r & 8) {
                if (D_00389C90.f3070.b.b40) return 4;
                i = *cnt;
                break;
            }
        }
    }
    return 0;
}

s32 func_001c2778(void) {
    VmRec *vms;
    s32 *cnt;
    s32 i, op, arg, r;
    s32 stop = 0;
    VmRec *p;
    VmMsg m;
    if (D_002BCDEC == 0) return 0;
    if (D_00389C90.x3034 == 0) {
        p = D_0038D170;
        cnt = &D_0039A570;
    } else {
        p = D_0039A580;
        cnt = &D_003A7980;
    }
    for (i = 1, p++; i < *cnt; i++, p++) {
        p->pc = p->lbl[0];
        while (1) {
            op = func_001c1ce8(p->code, p->pc);
            arg = func_001c1cf8(p->code, p->pc);
            if (op == 5) break;
            r = D_0037A198[op](p, arg);
            if (r & 2) p->pc++;
            if (r & 8) {
                stop = 1;
                D_002C5958 &= ~8;
                D_002C5958 &= ~4;
                break;
            }
        }
        p->x78 = 1;
        p->pc = p->lbl[1];
    }
    if (stop) return 4;
    if (D_00389C90.x3034 == 0) {
        func_0011ef10(0xc352, func_001c1f80);
        return 4;
    }
    cnt = &D_0039A570;
    p = D_0038D170;
    for (i = 1, p++; i < *cnt; i++, p++) {
        if ((u32)p->fl.i[0] % 2 == 1) {
/*P*/
            m.type = 18;
            m.val = 0;
            m.v[0] = 0.0f;
            m.v[1] = 0.0f;
            m.v[2] = 0.0f;
            m.v[3] = 1.0f;
            m.x = p->x0;
/*Q*/
            func_001c4640(&m);
        }
    }
    return 4;
}

void func_001c29d8(void) {
    s32 i;

    D_00389C90.f3070.w.b32 = 0;
    D_00389C90.f3070.w.b33 = 0;
    D_00389C90.f3070.w.b34 = 0;
    D_00389C90.f3070.w.b37 = 0;
    D_00389C90.f3070.w.b38 = 0;
    D_00389C90.f3070.w.b39 = 0;
    D_00389C90.f3070.w.b40 = 0;
    D_00389C90.f3070.w.b43 = 0;
    D_00389C90.f3070.w.b46 = 0;
    D_00389C90.f3070.w.b47 = 0;
    D_00389C90.f3070.w.b48 = 0;
    D_00389C90.f3070.w.b49 = 0;
    D_00389C90.f3070.w.b50 = 0;
    D_00389C90.f3070.w.b51 = 0;
    D_00389C90.f3070.w.b52 = 0;
    D_00389C90.f3070.w.b53 = 0;
    D_00389C90.f3070.w.b54 = 0;
    D_00389C90.f3070.w.b55 = 0;
    D_00389C90.f3070.w.b56 = 0;
    D_00389C90.f3070.w.b57 = 0;
    D_00389C90.f3070.w.b59 = 1;
    D_00389C90.f3070.w.b60 = 0;
    D_00389C90.f3070.w.b61 = 0;
    D_00389C90.f3070.w.b63 = 0;
    D_00389C90.f3078.w.b0 = 0;
    D_00389C90.f3078.w.b1 = 0;
    D_00389C90.f3078.w.b2 = 0;
    D_00389C90.f3078.w.b3 = 0;
    D_00389C90.f3078.w.b4 = 0;
    D_00389C90.f3078.w.b6 = 0;
    D_00389C90.f3078.w.b7 = 0;
    D_00389C90.f3078.w.b10 = 0;
    D_00389C90.f3078.w.b11 = 0;
    D_00389C90.f3078.w.b12 = 0;
    D_00389C90.f3078.w.b13 = 0;
    D_00389C90.x3148 = -1;
    D_00389C90.x314c = 1.0f;
    D_00389C90.x3170 = 0;
    D_00389C90.x3174 = 0;
    D_00389C90.u.s.x3380 = 0;
    D_00389C90.x3140 = 0;
    for (i = 0; i < 8; i++) {
        D_00389C90.u.s.e[i].obj = 0;
        D_00389C90.u.s.e[i].x4 = -1;
        D_00389C90.u.s.e[i].snd = -1;
        D_00389C90.u.s.e[i].x10 = 1;
        D_00389C90.u.s.e[i].ret = 0;
        D_00389C90.u.s.e[i].h = -1;
    }
    (*(Bits_37a378 *)&D_0037A378).b1 = 0;
    (*(Bits_37a378 *)&D_0037A378).b5 = 0;
}

void func_001c2d20(s8 *p, s32 *cnt, s8 **tbl) {
    s32 n = *(s32 *)p;
    s32 i;
    p += 4;
    *cnt = n;
    for (i = 0; i < n; i++) {
        tbl[i] = p;
        {
            u8 c;
            for (;;) {
                s8 t = *p;
                c = *p;
                if (t == 4 || t == 0) break;
                if ((u32)(c - 5) < 3) p += 2;
                else if ((s8)c == 11) p += 3;
                else if ((s8)c == 10) { p++; if (*p == 0) p += 2; }
                else if ((s8)c == 13) p += 3;
                else p += (u32)(c - 9) < 23;
                p++;
            }
        }
        p++;
    }
}

s8 *func_001c2df0(s8 *p, s32 k) {
    s32 n = *(s32 *)p;
    s32 i;
    p += 4;
    for (i = 0; i < n; i++) {
        if (i == k) return p;
        {
            u8 c;
            for (;;) {
                s8 t = *p;
                c = *p;
                if (t == 4 || t == 0) break;
                if ((u32)(c - 5) < 3) p += 2;
                else if ((s8)c == 11) p += 3;
                else if ((s8)c == 10) { p++; if (*p == 0) p += 2; }
                else if ((s8)c == 13) p += 3;
                else p += (u32)(c - 9) < 23;
                p++;
            }
        }
        p++;
    }
    return 0;
}

void func_001c2ec8(s8 *p, s32 a1) {
    s32 done = 0;
    VmRec *e;
    s32 h0;
    s32 *cnt;
    s32 i, j, k;
    s32 op, arg, r;
    s8 *q;
    s8 *c;
    s32 *t;
    VmOp *fn;
    s32 *fl;
    D_003C39AC = p;
    (*(Bits_37a378 *)&D_0037A378).b2 = 0;
    (*(Bits_37a378 *)&D_0037A378).b3 = 0;
    (*(Bits_37a378 *)&D_0037A378).b4 = 0;
    if (a1 == 0) {
        srand(func_001ee200());
        (*(Bits_37a378 *)&D_0037A378).b0 = 0;
        D_002C5958 |= 0xc;
        func_001c29d8();
        D_006277E0 = 0;
        D_006277E4 = 0;
        D_006297F0 = 0;
        D_006297F4 = 0;
        D_00389C90.nbox = 0;
        func_001c6720();
        func_001cab48();
    } else if (D_00389C90.x3034 == 0) {
        for (i = 0; i < 512; i++) {
            D_00389C90.a2034[i] = D_00389C90.a1034[i];
            D_00389C90.a2834[i] = D_00389C90.a1834[i];
        }
    }
    for (i = 0; i < 512; i++) {
        D_00389C90.a1034[i] = 0;
        D_00389C90.a1834[i] = 0;
    }
    h0 = ((s32 *)p)[0];
    t = (s32 *)p + 3;
    D_00389C90.x3048 = h0;
    D_00389C90.x304c = t + 1;
    D_00389C90.x3060 = t + 1 + h0;
    D_00389C90.x305c = ((s32 *)p)[1];
    D_00389C90.x3040 = p;
    q = p + *t;
    c = p + t[(a1 + (D_00389C90.x305c + h0)) + 1];
    c += 12;
    if (a1 == 0) { e = D_0038D170; cnt = &D_0039A570; }
    else { e = D_0039A580; cnt = &D_003A7980; }
    *cnt = *c++;
    for (i = 0; i < *cnt; i++, e++) {
        e->x0 = 0;
        e->obj = 0;
        e->code = c + 4;
        e->n = *c;
        e->pc = 0;
        e->sp = -1;
        e->x78 = 0;
        e->x2f0 = 0;
        e->rsp = 7;
        for (j = 0; j < 8; j++) e->ret[j] = -1;
        e->ret[7] = e->pc;
        for (j = 0; j < 26; j++) e->var[j] = 0;
        c += 4;
        e->fl.b.b0 = 0; e->fl.b.b1 = 0; e->fl.b.b2 = 0; e->fl.b.b3 = 0; e->fl.b.b4 = 0; e->fl.b.b5 = 0; e->fl.b.b6 = 0; e->fl.b.b7 = 0;
        e->fl.b.b8 = 0; e->fl.b.b9 = 0; e->fl.b.b10 = 0; e->fl.b.b11 = 0; e->fl.b.b12 = 0; e->fl.b.b13 = 0; e->fl.b.b14 = 0; e->fl.b.b15 = 0;
        k = 0;
        for (j = 0; j < e->n; j++) {
            e->lbl[j] = k;
            while (c[3] != 5) { c += 4; k++; }
            c += 4; k++;
        }
    }
    func_001c2d20(q, &D_00389C80, ((s8 **)&D_00388480));
    if (a1 == 0) e = D_0038D170;
    else e = D_0039A580;
    fn = D_0037A198;
    fl = &D_002C5950[2];
    e->pc = e->lbl[0];
    while ((op = func_001c1ce8(e->code, e->pc), arg = func_001c1cf8(e->code, e->pc), op != 5)) {
        r = fn[op](e, arg);
        if (r & 2) e->pc++;
        if (r & 8) {
            done = 1;
            *fl &= ~8;
            do { *fl &= ~4; } while (0);
            break;
        }
    }
    e->x78 = 1;
    e->pc = e->lbl[1];
    D_00389C90.x3034 = a1;
    if (!done) {
        if (a1 == 99 || D_00389C90.f3078.b.b6) {
            D_00389C90.f3078.b.b6 = 0;
            func_0011ef10(50001, func_001c2778);
            return;
        }
        func_0011ef10(50002, func_001c2778);
    }
}

s32 func_001c3408(void) {
    VmRec *e;
    s32 *cnt;
    s32 i, op, arg, r;
    s32 done;
    VmMsg *m;
    if ((s32)(D_00389C90.f3070.x >> 40) & 1) {
        D_00389C90.f3070.x &= ~0x40000000000ULL;
        return 4;
    }
    D_00389C90.x316c = 0;
    if (D_00389C90.x3038 == 0) { e = D_003A7990; cnt = &D_003B4D90; }
    else { e = D_003B4DA0; cnt = &D_003C21A0; }
    done = 0;
    m = func_001c4730();
    if (((s32)(D_00389C90.f3070.x >> 37) & 1) == 1U) func_0011ef10(99999, func_001c5b88);
    for (i = 0; i < *cnt; i++, e++) {
        if (e->fl.b.b3) {
            if (i != 0) continue;
            if (D_00389C90.x3038 != 0) {
                D_00389C90.x3038 = 0;
                D_00389C90.f3070.x &= ~0x40000000000ULL;
                if (m && !done) func_001c4788(m);
                return 4;
            } else {
                D_00389C90.f3070.x &= ~0x40000000000ULL;
                if (m && !done) func_001c4788(m);
                return 4;
            }
        }
        if (e->fl.b.b8) continue;
        if (e->fl.b.b2) {
            e->x2f4 -= D_002BBDFC;
            if (e->x2f4 > 0.0f) continue;
            e->fl.b.b2 = 0;
        }
        if (m) {
            switch (m->type) {
            case 2:
                if (m->x == e->x0) { done = 1; e->fl.b.b0 = 0; }
                break;
            case 4:
                if (m->x == e->x0) { done = 1; e->fl.b.b1 = 0; }
                break;
            case 21:
                if (m->x == e->x0) { done = 1; e->fl.b.b1 = 0; }
                break;
            case 22:
                if (m->x == e->x0) { done = 1; e->fl.b.b1 = 0; }
                break;
            }
        }
        while (1) {
            op = func_001c1ce8(e->code, e->pc);
            arg = func_001c1cf8(e->code, e->pc);
            r = D_0037A198[op](e, arg);
            if (r & 2) e->pc++;
            if (r & 4) break;
            if ((r & 8) || ((s32)(D_00389C90.f3070.x >> 40) & 1)) {
                D_00389C90.f3070.x &= ~0x40000000000ULL;
                if (m && !done) func_001c4788(m);
                return 4;
            }
        }
    }
    if (m && !done) func_001c4788(m);
    return 0;
}

/* func_001c3770: script_vm.nostrict.c */

/* func_001c3b10's exits: hand the messages no VM took back to the queue, and
 * restore the script file state func_001c4198 saved. */
#define FLUSH() \
    for (i = 0; i < n; i++) { \
        if (!done[i]) func_001c4788(&msgs[i]); \
    }

#define RESTORE() \
    D_00389C90.x3040 = D_00389C90.x3044; \
    D_00389C90.x3048 = D_00389C90.x3050; \
    D_00389C90.x304c = D_00389C90.x3054; \
    D_00389C90.x305c = D_00389C90.x3064; \
    D_00389C90.x3060 = D_00389C90.x3068; \
    D_00389C80 = D_003C39A8; \
    for (i = 0; i < ((u32)D_00389C80); i++) { \
        ((s32 *)&D_00388480)[i] = ((s32 *)&D_003C21A8)[i]; \
    }

s32 func_001c3b10(VmTask *t) {
    VmMsg m;
    VmMsg msgs[256];
    s32 done[256];
    VmRec *vm;
    VmRec *w;
    VmMsg *p;
    s32 n = 0;
    s32 i, j, r, k;
    u32 c;
    s32 *pn;
    s32 *d;

    D_00389C90.x316c = t;
    D_002C5BB0.x4 &= D_00389C90.x3148;
    D_002C5BB0.x8 &= D_00389C90.x3148;
    if (~(D_00389C90.x3148 >> 23) & 1) {
        for (i = 0; i < 3; i++) {
            D_002C5BB0.x40[i] = 0;
            D_002C5BB0.x60[i] = 0;
        }
    }
    vm = t->vm;
    pn = &t->n;
    p = func_001c4730();
    while (p) {
        msgs[n++] = *p;
        p = func_001c4730();
    }
    for (i = 255; i >= 0; i--) {
        done[i] = 0;
    }
    if (D_00389C90.f3070.b.b43 == 1) func_001cebe8();
    if (D_00389C90.f3070.b.b38 == 1) func_001cff28();
    if (D_00389C90.f3070.b.b39 == 1) func_001cfff8();
    if (D_00389C90.f3078.b.b10) func_001ca800();
    if (D_00389C90.f3070.b.b53) return 0;
    for (i = 0; i < *pn; i++, vm++) {
        if ((s32)(vm->fl.x >> 3) & 1) {
            if (i != 0) continue;
            if (t->x18) {
                D_00389C90.x3034 = 0;
                w = D_0038D170;
                for (j = 1, w++; j < t->n; j++, w++) {
                    if (w->fl.b.b0 == 1) {
                        m.type = 2;
                        m.val = (u32)w->f20;
                        m.x = w->x0; m.v[0] = w->f14[0]; m.v[1] = w->f14[1]; m.v[2] = w->f14[2];
                        m.v[3] = 10.0f;
                        func_001c4640(&m);
                    }
                }
                FLUSH();
                return 0;
            }
            RESTORE();
            FLUSH();
            return 4;
        }
        if ((s32)(vm->fl.x >> 8) & 1) continue;
        func_001dcea8(vm);
        func_001dcfd0(vm);
        if ((vm->fl.x & 0x14) == 4) {
            vm->x2f4 -= D_002BBDFC;
            if (vm->x2f4 > 0.0f) continue;
            vm->fl.x &= ~4;
        }
        j = 0;
        if (n > 0) { do {
            p = &msgs[j];
            switch (p->type) {
            case 2:
                if (p->x == vm->x0) {
                    vm->fl.x &= ~1;
                    done[j] = 1;
                    break;
                }
                break;
            case 4:
                if (p->x == vm->x0) {
                    vm->fl.x &= ~2;
                    done[j] = 1;
                    break;
                }
                break;
            case 21:
                if (p->x == vm->x0) {
                    vm->fl.x &= ~2;
                    done[j] = 1;
                    break;
                }
                break;
            case 22:
                if (p->x == vm->x0) {
                    vm->fl.x &= ~2;
                    done[j] = 1;
                    break;
                }
                break;
            }
            j++;
        } while (j < n); }
        while (1) {
            k = func_001c1ce8(vm->code, vm->pc);
            r = D_0037A198[k](vm, func_001c1cf8(vm->code, vm->pc));
            if (r & 2) vm->pc++;
            if (r & 4) break;
            if (r & 8) {
                RESTORE();
                FLUSH();
                return 4;
            }
        }
    }
    FLUSH();
    return 0;
}

#undef FLUSH
#undef RESTORE

void func_001c4198(s8 *h, s32 a1)
{
  s32 done = 0;
  VmRec *e;
  VmRec *e2;
  s32 i;
  s32 *cnt;
  s32 *o;
  s32 *o1;
  s32 n0;
  s32 n1;
  s32 j;
  s32 k;
  s8 *p;
  s8 *q;
  s32 op;
  s64 mask;
  s32 arg;
  s32 r;
  VmTask *t;
  s32 *src;
  D_00389C90.x3044 = D_00389C90.x3040;
  D_00389C90.x3050 = D_00389C90.x3048;
  D_00389C90.x3054 = D_00389C90.x304c;
  D_00389C90.x3064 = D_00389C90.x305c;
  D_00389C90.x3068 = D_00389C90.x3060;
  D_003C39A8 = D_00389C80;
  for (i = 0; i < ((u32)D_00389C80); i++)
  {
    D_003C21A8[i] = D_00388480[i];
  }

  (*(Bits_37a378 *)&D_0037A378).b0 = 0;
  (*(Bits_37a378 *)&D_0037A378).b1 = 0;
  (*(Bits_37a378 *)&D_0037A378).b2 = 0;
  (*(Bits_37a378 *)&D_0037A378).b3 = 0;
  D_003C39AC = h;
  D_00389C90.x3148 = -1;
  D_00389C90.x314c = 1.0f;
  D_00389C90.x3140 = 0;
  func_001c6720();
  o = (s32 *) (h + 12);
  o1 = (s32 *) (h + 16);
  mask = ~8;
  n0 = ((s32 *) h)[0];
  D_00389C90.x3048 = n0;
  D_00389C90.x3040 = h;
  n1 = ((s32 *) h)[1];
  D_00389C90.x3060 = (o + n0) + 1;
  D_00389C90.x305c = n1;
  q = h + o[0];
  D_00389C90.x304c = o1;
  p = h + o[(a1 + (n1 + n0)) + 1];
  p += 12;
  e = D_003C3A70;
  cnt = &D_003C54F0;
  *cnt = *(p++);
  for (i = 0; i < (*cnt); i++, e++)
  {
    s32 m;
    e->x0 = 0;
    e->obj = 0;
    e->code = p + 4;
    e->n = *p;
    e->pc = 0;
    e->sp = -1;
    e->x78 = 0;
    e->x2f0 = 0;
    e->rsp = 7;
    for (m = 7; m >= 0; m--)
    {
      e->ret[m] = -1;
    }

    p += 4;
    e->ret[7] = e->pc;
    e->fl.b.b0 = 0;
    e2 = e;
    e2->fl.b.b1 = 0;
    e->fl.b.b2 = 0;
    e->fl.b.b3 = 0;
    e->fl.b.b4 = 0;
    e->fl.b.b5 = 0;
    e->fl.b.b6 = 0;
    e->fl.b.b7 = 0;
    e2->fl.b.b8 = 0;
    e2->fl.b.b9 = 0;
    k = 0;
    for (m = 0; m < e2->n; m++)
    {
      e2->lbl[m] = k;
      while (p[3] != 5)
      {
        p += 4;
        k++;
      }

      p += 4;
      k++;
    }

  }

  func_001c2d20(q, &D_00389C80, (s8 **)D_00388480);
  e = D_003C3A70;
  cnt = &D_003C54F0;
  for (i = 0; i < (*cnt); i++, e++)
  {
    e->pc = e->lbl[0];
    while (1)
    {
      op = func_001c1ce8(e->code, e->pc);
      arg = func_001c1cf8(e->code, e->pc);
      if (op == 5)
      {
        break;
      }
      r = D_0037A198[op](e, arg);
      if (r & 2)
      {
        e->pc++;
      }
      if (r & 8)
      {
        done = 1;

        D_002C5958 &= mask;
        D_002C5958 &= ~4;
        break;
      }
    }

    e->x78 = 1;
    e->pc = e->lbl[1];
  }

  if (done == 0)
  {
    t = func_0011f090(D_006297F8, 1, func_001c3b10);
    t->vm = D_003C3A70;
    t->n = D_003C54F0;
    t->x18 = 0;
  }
}

VmMsg *func_001c45e8(void) {
    s32 h = D_006277E0;
    VmMsg *r;
    if (h == D_006277E4) return 0;
    r = &D_006257E0[h];
    D_006277E0 = (h + 1) % 256;
    return r;
}

s32 func_001c4640(VmMsg *m) {
    VmMsg t;
    if ((D_006277E4 + 1) % 256 == D_006277E0) return -1;
    if (func_00123488(m->x) == 0 && D_0037A21C[m->type].f != 0) return 0;
    D_006257E0[D_006277E4] = *m;
    D_006277E4 = (D_006277E4 + 1) % 256;
    return 0;
}

VmMsg *func_001c4730(void) {
    s32 h = D_006297F0;
    VmMsg *r;
    if (h == D_006297F4) return 0;
    r = &D_006277F0[h];
    D_006297F0 = (h + 1) % 256;
    return r;
}

s32 func_001c4788(void *m) {
    if ((D_006297F4 + 1) % 256 == D_006297F0) return -1;
    D_006277F0[D_006297F4] = *(VmMsg *)m;
    D_006297F4 = (D_006297F4 + 1) % 256;
    return 0;
}

/* func_001c4808: script_vm.nostrict.c */

/* func_001c48c8: script_vm.nostrict.c */

void func_001c4d90(s32 arg0, s32 arg1, s32 arg2) {
    func_001dd1f0(arg1, arg2);
    func_001c4198((s8 *)arg0, 0);
    D_0037A378 |= 4;
}

s32 func_001c4de0(s32 a, s32 b) {
    VmRec *vm;
    VmMsg m;
    D_00389C90.x3170 = a;
    D_00389C90.x3174 = b;
    if (D_00389C90.x3034 == 0) vm = D_0038D170;
    else vm = D_0039A580;
    D_00389C90.x3450 = 0;
    func_001c1d20(vm, 10);
    if (b == 1) {
        func_001d59a0(vm);
        m.type = 40;
        m.val = 0;
        m.v[0] = 0.0f;
        m.v[1] = 0.0f;
        m.v[2] = 0.0f;
        m.v[3] = 1.0f;
        func_001c4640(&m);
        if (D_002BBE04 == b) D_002BBE04 = 4;
    }
    return D_00389C90.x3450;
}

s32 func_001c4ed0(Obj *o, s32 unused, s32 a2) {
    VmRec *vm;
    VmRec *t;
    s32 n, i;
    if (!((D_00389C90.f3070.x >> 59) & 1)) return 0;
    if (a2 < -1) return 0;
    if ((*(Bits_37a378 *)&D_0037A378).b2 || (D_002C5958 & 0x12000)) return 0;
    if (D_00389C90.x3034 == 0) {
        vm = D_0038D170;
        n = D_0039A570;
    } else {
        vm = D_0039A580;
        n = D_003A7980;
    }
    for (i = 0; i < n; i++) {
        if (vm[i].x0 == o->id) break;
    }
    if (i >= n) return 0;
    t = &vm[i];
    if (t->rsp != 3 || a2 >= 0) {
        if (D_0037A190 == 0) {
            if (func_001c1ce8(t->code, t->lbl[9]) != 5) {
                vm->stk[++vm->sp] = 3;
                vm->stk[++vm->sp] = i;
                func_001c19f8(vm, 9);
                D_00389C90.u.s.x3444 = a2;
            }
        }
        if (a2 != -1) D_0037A190 = 1;
    }
    for (i = 0; i < 8; i++) {
        if (D_00389C90.u.s.e[i].obj != (s32)o) continue;
        D_00389C90.u.s.e[i].obj = 0;
        if (D_00389C90.u.s.e[i].h >= 0) {
            func_0012cb78(o, D_00389C90.u.s.e[i].h);
            D_00389C90.u.s.e[i].h = -1;
        }
        if (a2 != -1) D_00389C90.u.s.e[i].snd = -1;
        if (D_00389C90.u.s.e[i].snd >= 0) {
            func_0012cc38(3, D_00389C90.u.s.e[i].snd);
            D_00389C90.u.s.e[i].snd = -1;
            if (D_00389C90.u.s.e[i].x10 == 0) func_0012ccb0(3);
            return D_00389C90.u.s.e[i].ret;
        }
    }
    return 0;
}
