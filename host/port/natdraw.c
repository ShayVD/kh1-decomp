/* The native renderer's CPU side (include/platform/natdraw.h, docs/native-renderer.md): a run's strips as GPU
 * triangles, and the run's matrices folded with the screen mapping.  Plain C with no libc but memcpy (the Vita
 * build compiles host/port/).  Not part of the PS2 build. */
#include "common.h"
#include "platform/natdraw.h"
#include "platform/depth.h"

void *memcpy(void *, const void *, __SIZE_TYPE__);
int memcmp(const void *, const void *, __SIZE_TYPE__);

static f32 nf(u32 v) {
    union { u32 u; f32 f; } x;
    x.u = v;
    return x.f;
}

static void put(KH1GpuVert *o, const u32 *v, u32 rgba, u32 f) {
    o->x = nf(v[0]);
    o->y = nf(v[1]);
    o->z = nf(v[2]);
    o->s = nf(v[4]);
    o->t = nf(v[5]);
    o->q = nf(v[6]);
    o->rgba[0] = (u8)rgba;
    o->rgba[1] = (u8)(rgba >> 8);
    o->rgba[2] = (u8)(rgba >> 16);
    o->rgba[3] = (u8)(rgba >> 24);
    o->f = (u8)f;
    o->pad[0] = (u8)v[3];
    o->pad[1] = o->pad[2] = 0;
}

/* 2026-11-01 (native-plan.md stage 1, the GPU thread's recording): each strip vertex goes to the GPU's form once
 * (put / put0 into sv) and its triangles are copies of those (32 bytes each), where it was converted again for each of
 * the up to 3 triangles it is in.  The same vertices out, in the same order.  kh1_nat_once 0 (config.txt recfast=0,
 * host KH1_HOST_RECFAST=0) converts per triangle as before */
int kh1_nat_once = 1;
#define SV_MAX 512
static KH1GpuVert sv[SV_MAX];

u32 kh1_nat_tris(const u32 *data, u32 nrec, u32 nmat, u32 rgba, u32 f, KH1GpuVert *out, u32 max, u32 *lost) {
    u32 r, j, n = 0;
    *lost = 0;
    for (r = 0; r < nrec; r++) {
        u32 nv = data[2], par = data[3];
        const u32 *v = data + 4;
        if (par & (KH1_NAT_SKIN | KH1_NAT_VB)) { /* 2026-11-01: kh1_nat_tris_skin's; 2026-11-02: a cached record's */
            data += KH1_NAT_REC_QW(data) * 4;
            continue;
        }
        if (kh1_nat_once && nv <= SV_MAX) {
            u32 bad = 0; /* bit k of the last 3: vertex j - 2 + k's matrix index past the run's */
            for (j = 0; j < nv; j++) put(&sv[j], v + j * 8, rgba, f);
            for (j = 0; j < nv; j++) {
                bad = (bad >> 1) | (v[j * 8 + 3] >= nmat) << 2;
                if (j < 2 || bad) continue;
                if (n + 3 > max) { (*lost)++; continue; }
                if ((par + j) & 1) {
                    out[n] = sv[j - 2];
                    out[n + 1] = sv[j - 1];
                } else {
                    out[n] = sv[j - 1];
                    out[n + 1] = sv[j - 2];
                }
                out[n + 2] = sv[j];
                n += 3;
            }
            data += 4 + nv * 8;
            continue;
        }
        for (j = 2; j < nv; j++) {
            const u32 *a = v + (j - 2) * 8, *b = v + (j - 1) * 8, *c = v + j * 8;
            if (a[3] >= nmat || b[3] >= nmat || c[3] >= nmat) continue;
            if (n + 3 > max) { (*lost)++; continue; }
            if ((par + j) & 1) { /* odd: kept as it is when its area >= 0 */
                put(&out[n], a, rgba, f);
                put(&out[n + 1], b, rgba, f);
            } else { /* even: P18's operands swapped, so its mirror */
                put(&out[n], b, rgba, f);
                put(&out[n + 1], a, rgba, f);
            }
            put(&out[n + 2], c, rgba, f);
            n += 3;
        }
        data += 4 + nv * 8;
    }
    return n;
}

/* 2026-11-01: a KH1_NAT_SKIN record's vertex (natdraw.h) */
static void put_sk(KH1GpuVertSk *o, const u32 *v, u32 rgba, u32 f, u32 lin) {
    o->x = nf(v[0]);
    o->y = nf(v[1]);
    o->z = nf(v[2]);
    o->w = nf(v[7]);
    o->s = nf(v[4]);
    o->t = nf(v[5]);
    o->q = nf(v[6]);
    o->rgba[0] = (u8)rgba;
    o->rgba[1] = (u8)(rgba >> 8);
    o->rgba[2] = (u8)(rgba >> 16);
    o->rgba[3] = (u8)(rgba >> 24);
    o->f = (u8)f;
    o->mi = (u8)(v[3] | lin);
    o->mi2 = (u8)(v[3] >> 16);
    o->pad = 0;
    o->x2 = nf(v[8]);
    o->y2 = nf(v[9]);
    o->z2 = nf(v[10]);
    o->w2 = nf(v[11]);
}

u32 kh1_nat_tris_skin(const u32 *data, u32 nrec, u32 nmat, u32 rgba, u32 f, u32 lin, KH1GpuVertSk *out, u32 max, u32 *lost) {
    u32 r, j, n = 0;
    *lost = 0;
    for (r = 0; r < nrec; r++) {
        u32 nv = data[2], par = data[3] & 0xFFFF, vq = data[3] & KH1_NAT_SKIN ? 12 : 8;
        const u32 *v = data + 4;
        if (data[3] & KH1_NAT_VB) { /* 2026-11-02: a cached record (natvb) */
            data += KH1_NAT_REC_QW(data) * 4;
            continue;
        }
        for (j = 2; j < nv; j++) {
            const u32 *a = v + (j - 2) * vq, *b = v + (j - 1) * vq, *c = v + j * vq;
            if (vq != 12 || (a[3] & 0xFFFF) >= nmat || (b[3] & 0xFFFF) >= nmat || (c[3] & 0xFFFF) >= nmat ||
                a[3] >> 16 >= nmat || b[3] >> 16 >= nmat || c[3] >> 16 >= nmat)
                continue;
            if (n + 3 > max) { (*lost)++; continue; }
            if ((par + j) & 1) {
                put_sk(&out[n], a, rgba, f, lin);
                put_sk(&out[n + 1], b, rgba, f, lin);
            } else {
                put_sk(&out[n], b, rgba, f, lin);
                put_sk(&out[n + 1], a, rgba, f, lin);
            }
            put_sk(&out[n + 2], c, rgba, f, lin);
            n += 3;
        }
        data += 4 + nv * vq;
    }
    return n;
}

/* P0's vertex: (x, y, z, flags), (s, t, 1, rgba) */
static void put0(KH1GpuVert *o, const u32 *v, u32 f) {
    o->x = nf(v[0]);
    o->y = nf(v[1]);
    o->z = nf(v[2]);
    o->s = nf(v[4]);
    o->t = nf(v[5]);
    o->q = nf(v[6]);
    o->rgba[0] = (u8)v[7];
    o->rgba[1] = (u8)(v[7] >> 8);
    o->rgba[2] = (u8)(v[7] >> 16);
    o->rgba[3] = (u8)(v[7] >> 24);
    o->f = (u8)f;
    o->pad[0] = 0x80; /* matrix 0, z not clamped (shadergen.c: the GPU clips it at P0's near and far planes) */
    o->pad[1] = o->pad[2] = 0;
}
/* 2026-10-31: P0's records (natdraw.h): the triangle ending at vertex j is drawn when its flag word's low half is
 * not 0; with bit 0x20 (the Z sign flag of P0's cross product times the flag as a float) it is dropped when the
 * product is negative.  P0's product is -cross(p1 - p0, p2 - p0) in screen space (y down), so with a positive flag
 * the triangle is kept when that cross is <= 0 (listed with its first two vertices swapped, to the one winding rule
 * the cull mode keeps), with a negative flag when >= 0 (as it is).  Without 0x20 (0x02: only a zero product, a
 * triangle with no area, which draws nothing anyway) it is not culled.  culled 1 lists the first kind, 0 the
 * second */
u32 kh1_nat_tris0(const u32 *data, u32 nrec, u32 f, int culled, KH1GpuVert *out, u32 max, u32 *lost) {
    u32 r, j, n = 0;
    *lost = 0;
    for (r = 0; r < nrec; r++) {
        u32 nv = data[2];
        const u32 *v = data + 4;
        if (kh1_nat_once && nv <= SV_MAX) { /* each vertex converted once (kh1_nat_tris), only those a triangle uses */
            u32 done = 0; /* sv holds vertices 0 .. done - 1 */
            for (j = 2; j < nv; j++) {
                u32 fl = v[j * 8 + 3] & 0xFFFF;
                if (!fl || ((fl & 0x20) != 0) != (culled != 0)) continue;
                if (n + 3 > max) { (*lost)++; continue; }
                if (done < j - 2) done = j - 2;
                for (; done <= j; done++) put0(&sv[done], v + done * 8, f);
                if (culled && !(v[j * 8 + 3] >> 31)) {
                    out[n] = sv[j - 1];
                    out[n + 1] = sv[j - 2];
                } else {
                    out[n] = sv[j - 2];
                    out[n + 1] = sv[j - 1];
                }
                out[n + 2] = sv[j];
                n += 3;
            }
            data += 4 + nv * 8;
            continue;
        }
        for (j = 2; j < nv; j++) {
            const u32 *a = v + (j - 2) * 8, *b = v + (j - 1) * 8, *c = v + j * 8;
            u32 fl = c[3] & 0xFFFF;
            if (!fl || ((fl & 0x20) != 0) != (culled != 0)) continue;
            if (n + 3 > max) { (*lost)++; continue; }
            if (culled && !(c[3] >> 31)) {
                put0(&out[n], b, f);
                put0(&out[n + 1], a, f);
            } else {
                put0(&out[n], a, f);
                put0(&out[n + 1], b, f);
            }
            put0(&out[n + 2], c, f);
            n += 3;
        }
        data += 4 + nv * 8;
    }
    return n;
}

void kh1_nat_fold(const KH1RenderPass *p, u32 zbuf_lo, s32 xshift16, const u32 *mats, u32 nmat, f32 *out) {
    /* vertex.h's x: ((X - OFX + 8) / 16 + ox) x scale with X = 16 x gx (+ the shift), then x 2 / w - 1 */
    f32 ax = p->w ? 2.0f * p->scale / (f32)p->w : 0.0f, ay = p->h ? 2.0f * p->scale / (f32)p->h : 0.0f;
    f32 bx = ax * (((f32)(8 + xshift16 - p->ofx)) / 16.0f + p->ox) - 1.0f;
    f32 by = ay * (((f32)(8 - p->ofy)) / 16.0f + p->oy) - 1.0f;
    f32 kz = kh1_depth_f32(1, 0x30 | (zbuf_lo >> 24 & 15)); /* Z x 2^-bits */
    u32 i, k;
    for (i = 0; i < nmat; i++, mats += 16, out += 16) {
        f32 row[4][4];
        for (k = 0; k < 4; k++) { /* M's rows from its columns */
            row[0][k] = nf(mats[k * 4]);
            row[1][k] = nf(mats[k * 4 + 1]);
            row[2][k] = nf(mats[k * 4 + 2]);
            row[3][k] = nf(mats[k * 4 + 3]);
        }
        for (k = 0; k < 4; k++) {
            out[k] = ax * row[0][k] + bx * row[3][k];
            out[4 + k] = ay * row[1][k] + by * row[3][k];
            out[8 + k] = kz * row[2][k];
            out[12 + k] = row[3][k];
        }
    }
}

void kh1_nat_ref_xyz(const u32 *m, const f32 *pos, f32 out[3]) {
    f32 c[4];
    u32 k;
    for (k = 0; k < 4; k++) c[k] = nf(m[k]) * pos[0] + nf(m[4 + k]) * pos[1] + nf(m[8 + k]) * pos[2] + nf(m[12 + k]);
    out[0] = c[0] / c[3];
    out[1] = c[1] / c[3];
    out[2] = c[2] / c[3];
}


/* ------------------------------------------------------------------------------------------------------------------
 * 2026-11-02: natvb, renderer B's vertices cached by the records' address (natdraw.h).  Everything below but
 * kh1_natvb_publish runs on the game thread.  The entries' GPU data (vertices, then indices) and their CPU data (the
 * stub records a hit sends, the matrix plan) are each a ring in allocation order: the oldest entry goes first, and only
 * once the GPU has read the last record that names it (its seq <= kh1_natvb_done); an entry still in flight is dropped
 * from the lookup instead (no more hits, so its seq stops growing) and the allocation fails for now. */
int kh1_natvb = 1;
u8 *kh1_natvb_mem;
u32 kh1_natvb_bytes;
volatile u32 kh1_natvb_done;
int kh1_natvb_fenced;
u32 kh1_natvb_seq;
u32 kh1_natvb_hits, kh1_natvb_miss, kh1_natvb_made, kh1_natvb_stale, kh1_natvb_evict, kh1_natvb_noroom, kh1_natvb_bad,
    kh1_natvb_big;

void kh1_natvb_publish(u32 seq) {
    if ((s32)(seq - kh1_natvb_done) > 0) {
        __sync_synchronize(); /* the GPU's reads before the number */
        kh1_natvb_done = seq;
    }
}

#define VB_ENTRIES 4096
#define VB_BUCKETS 4096
#define VB_CAND 1024
#define VB_CPU_QW (128u * 1024) /* 2 MiB of stub records and plans */
#define VB_MAX_V 1024           /* strip vertices an entry holds (a run is at most VU1's 1024 qwords) */
#define VB_MAX_I 3072

struct KH1NatVb {
    const u32 *src;
    u32 lim, prog, rgba, f, flags;
    u32 hf[2], hs[2];            /* the hashes: every word but the matrices', and one qword in 8 */
    u32 nrec, nmat, mbody;
    s32 last[3];
    u32 gpu_off, gpu_len, cpu_off, cpu_len;
    u32 seq;                     /* the last hand-over that named it */
    s32 next;                    /* the bucket's chain, -1 the end */
    u8 live, inmap;
    KH1GpuVert *v;               /* nv vertices, then the indices */
    u16 *ix;
    u32 nv, ni;
    u32 (*stub)[4];              /* nrec x 2 qwords */
    s16 *msrc;                   /* nmat */
};
static KH1NatVb vbe[VB_ENTRIES];
static s32 vb_bucket[VB_BUCKETS];
static u32 vb_head_e, vb_n;              /* the ring of entries: the oldest at vb_head_e, vb_n of them */
static u32 vb_cand[VB_CAND];
static u32 vb_cpu[VB_CPU_QW][4];
typedef struct { u32 size, head, tail, used; } VbRing;
static VbRing vr_gpu, vr_cpu;
static int vb_ready;
static u8 *vb_mem_was;

u32 kh1_natvb_used(void) { return vr_gpu.used; }

static u32 vb_key(const u32 *src, u32 lim, u32 prog, u32 rgba, u32 f, u32 flags) {
    u32 h = (u32)(unsigned long)src * 0x9E3779B1u;
    h ^= (lim * 0x85EBCA6Bu) ^ (prog << 24) ^ flags;
    h = (h ^ (h >> 15)) * 0x2C1B3C6Du;
    h ^= rgba * 0x27D4EB2Fu ^ f * 0x165667B1u;
    return h ^ (h >> 13);
}

void kh1_natvb_reset(void) {
    u32 i;
    for (i = 0; i < VB_BUCKETS; i++) vb_bucket[i] = -1;
    for (i = 0; i < VB_ENTRIES; i++) vbe[i].live = vbe[i].inmap = 0;
    for (i = 0; i < VB_CAND; i++) vb_cand[i] = 0;
    vb_head_e = vb_n = 0;
    vr_gpu.size = kh1_natvb_bytes & ~31u;
    vr_cpu.size = VB_CPU_QW;
    vr_gpu.head = vr_gpu.tail = vr_gpu.used = 0;
    vr_cpu.head = vr_cpu.tail = vr_cpu.used = 0;
    vb_mem_was = kh1_natvb_mem;
    vb_ready = kh1_natvb_mem && vr_gpu.size;
}

static void vb_unmap(KH1NatVb *e) {
    s32 *p;
    u32 b;
    if (!e->inmap) return;
    b = vb_key(e->src, e->lim, e->prog, e->rgba, e->f, e->flags) & (VB_BUCKETS - 1);
    for (p = &vb_bucket[b]; *p >= 0; p = &vbe[*p].next)
        if (&vbe[*p] == e) {
            *p = e->next;
            break;
        }
    e->inmap = 0;
}

/* room for len units at the ring's head (allocations in order, freed from the tail in order); ~0u when none */
static u32 ring_at(VbRing *r, u32 len) {
    if (len > r->size) return ~0u;
    if (!r->used) r->head = r->tail = 0;
    if (r->used && r->head <= r->tail) return r->tail - r->head >= len ? r->head : ~0u;
    if (r->size - r->head >= len) return r->head;
    return r->tail >= len ? 0 : ~0u;
}

/* the oldest entry freed when the GPU is done with it (1), else dropped from the lookup (0) */
static int vb_free_oldest(void) {
    KH1NatVb *e = &vbe[vb_head_e];
    u32 done = kh1_natvb_done;
    __sync_synchronize();
    if (e->seq && (s32)(e->seq - done) > 0) {
        vb_unmap(e);
        return 0;
    }
    vb_unmap(e);
    e->live = 0;
    vb_head_e = (vb_head_e + 1) % VB_ENTRIES;
    vb_n--;
    vr_gpu.used -= e->gpu_len;
    vr_cpu.used -= e->cpu_len;
    if (vb_n) {
        vr_gpu.tail = vbe[vb_head_e].gpu_off;
        vr_cpu.tail = vbe[vb_head_e].cpu_off;
    }
    kh1_natvb_evict++;
    return 1;
}

static KH1NatVb *vb_alloc(u32 gpu_len, u32 cpu_len) {
    u32 g, c, slot;
    KH1NatVb *e;
    for (;;) {
        g = ring_at(&vr_gpu, gpu_len);
        c = ring_at(&vr_cpu, cpu_len);
        if (g != ~0u && c != ~0u && vb_n < VB_ENTRIES) break;
        if (!vb_n || !vb_free_oldest()) {
            kh1_natvb_noroom++;
            return 0;
        }
    }
    slot = (vb_head_e + vb_n) % VB_ENTRIES;
    e = &vbe[slot];
    vb_n++;
    /* the used counts take the skipped end of a wrapped ring too, so the tail moves past it */
    vr_gpu.used += (g == 0 && vr_gpu.head ? vr_gpu.size - vr_gpu.head : 0) + gpu_len;
    vr_cpu.used += (c == 0 && vr_cpu.head ? vr_cpu.size - vr_cpu.head : 0) + cpu_len;
    e->gpu_len = (g == 0 && vr_gpu.head ? vr_gpu.size - vr_gpu.head : 0) + gpu_len;
    e->cpu_len = (c == 0 && vr_cpu.head ? vr_cpu.size - vr_cpu.head : 0) + cpu_len;
    e->gpu_off = g;
    e->cpu_off = c;
    vr_gpu.head = g + gpu_len;
    vr_cpu.head = c + cpu_len;
    if (vb_n == 1) {
        vr_gpu.tail = g;
        vr_cpu.tail = c;
    }
    e->live = 1;
    e->inmap = 0;
    e->seq = 0;
    return e;
}

/* the stream's words but the matrix records' bodies: every qword (step 1) or the qwords at multiples of 8 (step 8),
 * four lanes */
static void vb_hash(const KH1NatVb *e, const u32 *src, u32 step, u32 *out) {
    u32 h0 = 0x811C9DC5u, h1 = 0x01000193u, h2 = 0x6A09E667u, h3 = 0xBB67AE85u, o = 0, m = 0, end;
    for (;;) {
        /* the next matrix body at or after o (msrc rises for the stream's matrices) */
        while (m < e->nmat && (e->msrc[m] < 0 || (u32)e->msrc[m] + e->mbody <= o)) m++;
        end = m < e->nmat ? (u32)e->msrc[m] : e->lim;
        if (step > 1) o = (o + step - 1) & ~(step - 1);
        for (; o < end; o += step) {
            const u32 *w = src + o * 4;
            h0 = (h0 ^ w[0]) * 0x01000193u;
            h1 = (h1 ^ w[1]) * 0x9E3779B1u;
            h2 = (h2 ^ w[2]) * 0x85EBCA6Bu;
            h3 = (h3 ^ w[3]) * 0xC2B2AE35u;
        }
        if (m >= e->nmat) break;
        o = (u32)e->msrc[m] + e->mbody;
        m++;
    }
    out[0] = h0 ^ (h2 << 7 | h2 >> 25);
    out[1] = h1 ^ (h3 << 13 | h3 >> 19) ^ e->lim;
}

KH1NatVb *kh1_natvb_find(const u32 *src, u32 lim, u32 prog, u32 rgba, u32 f, u32 flags) {
    s32 i;
    if (!vb_ready || vb_mem_was != kh1_natvb_mem) kh1_natvb_reset();
    if (!vb_ready) return 0;
    for (i = vb_bucket[vb_key(src, lim, prog, rgba, f, flags) & (VB_BUCKETS - 1)]; i >= 0; i = vbe[i].next) {
        KH1NatVb *e = &vbe[i];
        if (e->src == src && e->lim == lim && e->prog == prog && e->rgba == rgba && e->f == f && e->flags == flags) return e;
    }
    kh1_natvb_miss++;
    return 0;
}

int kh1_natvb_same(KH1NatVb *e, const u32 *src) {
    u32 h[2];
    int ok;
    if (kh1_natvb == 2) {
        vb_hash(e, src, 8, h);
        ok = h[0] == e->hs[0] && h[1] == e->hs[1];
    } else {
        vb_hash(e, src, 1, h);
        ok = h[0] == e->hf[0] && h[1] == e->hf[1];
    }
    if (!ok) {
        kh1_natvb_stale++;
        vb_unmap(e);
    }
    return ok;
}

u32 kh1_natvb_payload(KH1NatVb *e, const u32 *src, const u32 *const *mats_reg, u32 (*ob)[4], u32 (*mats)[4][4], u32 *nmat,
                      s32 *last) {
    u32 i, rq = e->nrec * 2, seq = ++kh1_natvb_seq;
    if (!seq) seq = ++kh1_natvb_seq;
    memcpy(ob[2], e->stub, rq * 16);
    for (i = 0; i < e->nrec; i++) ob[3 + i * 2][3] = seq;
    for (i = 0; i < e->nmat; i++) {
        const u32 *m = e->msrc[i] >= 0 ? src + e->msrc[i] * 4 : mats_reg[-1 - e->msrc[i]];
        memcpy(mats[i], m, 64);
    }
    memcpy(ob[2 + rq], mats, e->nmat * 64);
    ob[0][0] = KH1_NAT_MAGIC | e->prog;
    ob[0][1] = e->nrec;
    ob[0][2] = e->nmat;
    ob[0][3] = rq;
    ob[1][0] = e->rgba;
    ob[1][1] = e->f;
    ob[1][2] = e->flags & 1;
    ob[1][3] = e->flags >> 1 & 1;
    for (i = 0; i < 3; i++) last[i] = e->last[i];
    *nmat = e->nmat;
    e->seq = seq;
    kh1_natvb_hits++;
    return 2 + rq + e->nmat * 4;
}

void kh1_natvb_learn(const u32 *src, u32 lim, u32 prog, u32 flags, const u32 *pay, const s16 *msrc, u32 mbody,
                     const s32 *last, u32 lin) {
    u32 nrec = pay[1], nmat = pay[2], rgba = pay[4], f = pay[5], r, j, nv = 0, ni = 0, key, gl, cl, b;
    const u32 *d = pay + 8;
    KH1NatVb *e, tmp;
    u16 *ix;
    KH1GpuVert *v;
    if (!vb_ready || !nrec || !nmat) return;
    /* seen twice (the same key and words) before an entry is made: a colour that changes every frame makes none */
    key = vb_key(src, lim, prog, rgba, f, flags);
    tmp.nmat = nmat;
    tmp.msrc = (s16 *)msrc;
    tmp.mbody = mbody;
    tmp.lim = lim;
    vb_hash(&tmp, src, 1, tmp.hf);
    if (vb_cand[key & (VB_CAND - 1)] != (key ^ tmp.hf[0] ^ 1)) {
        vb_cand[key & (VB_CAND - 1)] = key ^ tmp.hf[0] ^ 1;
        return;
    }
    vb_cand[key & (VB_CAND - 1)] = 0;
    for (r = 0; r < nrec; r++) {
        u32 n = d[2];
        if (d[3] & (KH1_NAT_SKIN | KH1_NAT_VB)) return;
        nv += n;
        ni += n > 2 ? (n - 2) * 3 : 0;
        d += 4 + n * 8;
    }
    if (nv > VB_MAX_V || ni > VB_MAX_I || nv > 0xFFFF) {
        kh1_natvb_big++;
        return;
    }
    gl = (nv * 32 + ni * 2 + 31) & ~31u;
    cl = nrec * 2 + (nmat * 2 + 15) / 16; /* the stubs, then the plan (s16s) */
    e = vb_alloc(gl, cl);
    if (!e) return;
    e->src = src;
    e->lim = lim;
    e->prog = prog;
    e->rgba = rgba;
    e->f = f;
    e->flags = flags;
    e->nrec = nrec;
    e->nmat = nmat;
    e->mbody = mbody;
    for (j = 0; j < 3; j++) e->last[j] = last[j];
    e->v = v = (KH1GpuVert *)(void *)(kh1_natvb_mem + e->gpu_off);
    e->ix = ix = (u16 *)(void *)(kh1_natvb_mem + e->gpu_off + nv * 32);
    e->stub = &vb_cpu[e->cpu_off];
    e->msrc = (s16 *)(void *)&vb_cpu[e->cpu_off + nrec * 2];
    memcpy(e->msrc, msrc, nmat * 2);
    e->hf[0] = tmp.hf[0];
    e->hf[1] = tmp.hf[1];
    vb_hash(e, src, 8, e->hs);
    /* the vertices once each and kh1_nat_tris's triangles as indices, a record at a time; its stub */
    d = pay + 8;
    nv = ni = 0;
    for (r = 0; r < nrec; r++) {
        u32 n = d[2], par = d[3], i0 = ni, bad = 0;
        const u32 *w = d + 4;
        KH1GpuVert t;
        for (j = 0; j < n; j++) {
            put(&t, w + j * 8, rgba, f);
            t.pad[0] = (u8)(t.pad[0] | lin);
            memcpy(&v[nv + j], &t, sizeof t); /* one store pass into GPU memory */
        }
        for (j = 0; j < n; j++) {
            bad = (bad >> 1) | (w[j * 8 + 3] >= nmat) << 2;
            if (j < 2 || bad) continue;
            if ((par + j) & 1) {
                ix[ni] = (u16)(nv + j - 2);
                ix[ni + 1] = (u16)(nv + j - 1);
            } else {
                ix[ni] = (u16)(nv + j - 1);
                ix[ni + 1] = (u16)(nv + j - 2);
            }
            ix[ni + 2] = (u16)(nv + j);
            ni += 3;
        }
        e->stub[r * 2][0] = d[0];
        e->stub[r * 2][1] = d[1];
        e->stub[r * 2][2] = n;
        e->stub[r * 2][3] = (par & 0xFFFF) | KH1_NAT_VB;
        e->stub[r * 2 + 1][0] = (u32)(unsigned long)v;
        e->stub[r * 2 + 1][1] = (u32)(unsigned long)(ix + i0);
        e->stub[r * 2 + 1][2] = ni - i0;
        e->stub[r * 2 + 1][3] = 0;
        nv += n;
        d += 4 + n * 8;
    }
    e->nv = nv;
    e->ni = ni;
    b = key & (VB_BUCKETS - 1);
    e->next = vb_bucket[b];
    vb_bucket[b] = (s32)(e - vbe);
    e->inmap = 1;
    kh1_natvb_made++;
}

int kh1_natvb_check(const KH1NatVb *e, const u32 *pay, u32 lin) {
    static KH1GpuVert a[VB_MAX_I];
    u32 lost, n, i;
    if (pay[1] != e->nrec || pay[2] != e->nmat) return 0;
    n = kh1_nat_tris(pay + 8, pay[1], pay[2], pay[4], pay[5], a, VB_MAX_I, &lost);
    if (n != e->ni || lost) return 0;
    for (i = 0; i < n; i++) {
        KH1GpuVert t = a[i];
        t.pad[0] = (u8)(t.pad[0] | lin);
        if (memcmp(&t, &e->v[e->ix[i]], sizeof t)) return 0;
    }
    return 1;
}
