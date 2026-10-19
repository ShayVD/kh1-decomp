/*
 * SHIFT BUILD ONLY (KH1_OVL_FIXUPS): load-time fixups for the EE overlays.
 * Never part of `make` (nothing under shift/ is built by it); linked only into
 * the relaid-out shift builds (M1/M2) by tools/shift/shift_ld.py, together with
 * the table tools/shift/overlay_relocs.py generates (out/shift/<mode>/ovl_fixups.s).
 * See docs/shiftable-plan.md, "Session 13: overlay fixups".
 *
 * Every overlay (.x, loaded at 0x00F20000) is linked against the main ELF's
 * original absolute addresses. When the main ELF moves, the loader calls
 * kh1_ovl_flush0() right after a file is in memory (in place of its
 * FlushCache(0), before the instruction cache is flushed and before anything
 * runs the file), and the table entry for that file rewrites each reference
 * to its new address: jal/j fields, %hi/%lo pairs, data words.
 *
 * Portable: no EE instructions, no alignment or endianness assumptions (the
 * table and the overlay are read and written as little-endian bytes), so the
 * same file runs in the static proof on the build host (tools/shift/ovl_proof.py)
 * and in a future native port.
 *
 * Table (little-endian u32 words, offsets in bytes from the table start):
 *   'KHOF' (0x464F484B), version 1, n_overlays
 *   n_overlays x { hash, size, n_entries, entries_offset, n_targets, targets_offset }
 *   entries: kind << 30 | target index << 18 | word offset in the overlay
 *            kind 0 J26, 1 WORD, 2 HI16, 3 LO16 (+ one word: the word offset of its lui)
 *   targets: { new address, original address } per index
 * HI16 entries come before the LO16 entries of the same overlay: a LO16 is
 * computed against its lui as already rewritten (several low halves may share
 * one lui).
 *
 * Safety: nothing is written unless every field first decodes to its original
 * address (wrong disc version, a file that is not the expected overlay, a
 * second application to the same bytes): then the overlay is left as loaded
 * and kh1_ovl_status records why.
 */

typedef unsigned int ovl_u32;  /* 32 bits on the EE and on common hosts */
typedef int ovl_s32;

#define OVL_MAGIC 0x464F484Bu
#define OVL_J26 0u
#define OVL_WORD 1u
#define OVL_HI16 2u
#define OVL_LO16 3u

/* Last result, for a debugger: { name hash, result, entries applied, loads fixed }. */
volatile ovl_s32 kh1_ovl_status[4];

static ovl_u32 rd32(const unsigned char *p) {
    return (ovl_u32)p[0] | ((ovl_u32)p[1] << 8) | ((ovl_u32)p[2] << 16) | ((ovl_u32)p[3] << 24);
}

static void wr32(unsigned char *p, ovl_u32 v) {
    p[0] = (unsigned char)v;
    p[1] = (unsigned char)(v >> 8);
    p[2] = (unsigned char)(v >> 16);
    p[3] = (unsigned char)(v >> 24);
}

/* The game's file-name hash (func_001200f8): h = (h << 1) ^ ((c << 16) % 0x11021),
   c a signed char, C remainder (truncating). */
ovl_u32 kh1_ovl_hash(const char *name) {
    ovl_u32 h = 0;
    while (*name) {
        ovl_s32 c = (ovl_s32)(signed char)*name++;
        h = (h << 1) ^ (ovl_u32)((c * 65536) % 69665);
    }
    return h;
}

static ovl_u32 sext16(ovl_u32 v) {
    v &= 0xFFFFu;
    return (v & 0x8000u) ? v | 0xFFFF0000u : v;
}

static ovl_u32 hi16(ovl_u32 a) {
    return ((a + 0x8000u) >> 16) & 0xFFFFu;
}

/* Address a J26 field encodes for an instruction at `pc`. */
static ovl_u32 j26_target(ovl_u32 insn, ovl_u32 pc) {
    return ((pc + 4u) & 0xF0000000u) | ((insn & 0x03FFFFFFu) << 2);
}

/*
 * Apply the fixups of the overlay `name` to `buf` (`size` bytes loaded, linked
 * at `base`). Returns 0 when the table has no entry for this name, the number
 * of fields rewritten, or a negative error with nothing written:
 *   -1 bad table, -2 entry beyond the loaded size, -3 a field does not hold its
 *   original address, -4 a %lo does not fit next to its rewritten %hi (the
 *   only error after writing; the static proof rules it out).
 */
ovl_s32 kh1_ovl_apply_hash(const unsigned char *tab, ovl_u32 h, unsigned char *buf, ovl_u32 size,
                           ovl_u32 base) {
    ovl_u32 n, i, k, cnt, ent, tgt, ntg, pass;
    if (rd32(tab) != OVL_MAGIC || rd32(tab + 4) != 1u)
        return -1;
    n = rd32(tab + 8);
    for (i = 0; i < n; i++) {
        const unsigned char *hd = tab + 12 + 24 * i;
        if (rd32(hd) == h)
            break;
    }
    if (i == n)
        return 0;
    {
        const unsigned char *hd = tab + 12 + 24 * i;
        cnt = rd32(hd + 8);
        ent = rd32(hd + 12);
        ntg = rd32(hd + 16);
        tgt = rd32(hd + 20);
    }
    /* pass 0: verify every field holds its original address; pass 1: rewrite */
    for (pass = 0; pass < 2; pass++) {
        const unsigned char *e = tab + ent;
        for (k = 0; k < cnt; k++) {
            ovl_u32 w = rd32(e), kind = w >> 30, ti = (w >> 18) & 0xFFFu, off = (w & 0x3FFFFu) << 2;
            ovl_u32 hoff = 0, nv, ov, f, pc = base + off;
            e += 4;
            if (kind == OVL_LO16) {
                hoff = (rd32(e) & 0x3FFFFu) << 2;
                e += 4;
            }
            if (ti >= ntg)
                return -1;
            if (off + 4 > size || hoff + 4 > size)
                return -2;
            nv = rd32(tab + tgt + 8 * ti);
            ov = rd32(tab + tgt + 8 * ti + 4);
            f = rd32(buf + off);
            if (pass == 0) {
                ovl_u32 ok;
                if (kind == OVL_J26)
                    ok = j26_target(f, pc) == ov;
                else if (kind == OVL_WORD)
                    ok = f == ov;
                else if (kind == OVL_HI16)
                    ok = (f & 0xFFFFu) == hi16(ov);
                else
                    ok = ((rd32(buf + hoff) << 16) + sext16(f)) == ov;
                if (!ok)
                    return -3;
                continue;
            }
            if (kind == OVL_J26) {
                f = (f & 0xFC000000u) | ((nv >> 2) & 0x03FFFFFFu);
            } else if (kind == OVL_WORD) {
                f = nv;
            } else if (kind == OVL_HI16) {
                f = (f & 0xFFFF0000u) | hi16(nv);
            } else {
                ovl_u32 lo = nv - (rd32(buf + hoff) << 16); /* against the rewritten %hi */
                if (sext16(lo) != lo)
                    return -4;
                f = (f & 0xFFFF0000u) | (lo & 0xFFFFu);
            }
            wr32(buf + off, f);
        }
    }
    return (ovl_s32)cnt;
}

ovl_s32 kh1_ovl_apply(const unsigned char *tab, const char *name, unsigned char *buf, ovl_u32 size,
                      ovl_u32 base) {
    return kh1_ovl_apply_hash(tab, kh1_ovl_hash(name), buf, size, base);
}

/* ---- EE side (the game's loader); the host proof builds with -DKH1_OVL_HOST ---- */

#ifndef KH1_OVL_HOST
extern const unsigned char kh1_ovl_fixups[]; /* the table (ovl_fixups.s) */

/*
 * The loader's hook (func_00120678 and func_001205f0 under KH1_OVL_FIXUPS call
 * this in place of their FlushCache(0), so neither function grows): `req` is
 * the finished CD request (func_001204a0). The request holds no file name, so
 * the file is identified by its index entry: KINGDOM.IDX in memory
 * (D_004E4A00[D_002C5C30], {hash, flags, LSN, stored size}, LSNs made absolute
 * by func_0011fe20) has one entry with the request's LSN and size (the HDD
 * path, func_001202c0, keeps LSN - D_004F3200).
 */
typedef struct {
    ovl_u32 hash, flags, lsn, size;
} OvlIdx;
typedef struct {
    ovl_u32 w0;
    unsigned char pad[32];
    ovl_u32 lsn, size;
    unsigned char *buf;
    ovl_s32 result;
} OvlReq; /* CdReq, src/hand/text_00110000_h30.c */

extern OvlIdx D_004E4A00[];
extern ovl_s32 D_002C5C30;
extern ovl_u32 D_004F3200;
int FlushCache(int);

void kh1_ovl_flush0(void *req) {
    OvlReq *r = (OvlReq *)req;
    ovl_s32 i, n = D_002C5C30;
    if (r->result > 0) {
        for (i = 0; i < n; i++) {
            OvlIdx *e = &D_004E4A00[i];
            if (e->size == r->size && (e->lsn == r->lsn || e->lsn == r->lsn + D_004F3200)) {
                ovl_s32 res = kh1_ovl_apply_hash(kh1_ovl_fixups, e->hash, r->buf, (ovl_u32)r->result,
                                                 0x00F20000u);
                if (res != 0) {
                    kh1_ovl_status[0] = (ovl_s32)e->hash;
                    kh1_ovl_status[1] = res;
                    if (res > 0) {
                        kh1_ovl_status[2] = res;
                        kh1_ovl_status[3]++;
                    }
                }
                break;
            }
        }
    }
    FlushCache(0);
}
#endif
