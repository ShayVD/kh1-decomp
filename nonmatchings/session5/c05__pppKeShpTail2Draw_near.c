#include "/tmp/claude-0/s/c05/tail_hdr.h"

typedef struct {
    u8 n;          /* +0x0 */
    u8 idx;        /* +0x1 */
    u8 pad2[4];
    u16 frame;     /* +0x6 */
    u8 pad8[8];
    PppVec4 pts[1]; /* +0x10 */
} Tail2Work;

typedef struct {
    s32 frame;
    s32 id;        /* +0x04 */
    u8 pad8[4];
    f32 size;      /* +0x0C */
    f32 size2;     /* +0x10 */
    u8 c0[4];      /* +0x14 */
    u8 c1[4];      /* +0x18 */
    f32 len;       /* +0x1C */
    u16 n;         /* +0x20 */
    u8 draw;       /* +0x22 */
    u8 local;      /* +0x23 */
    u8 b24;        /* +0x24 */
    u8 b25;        /* +0x25 */
} Tail2Key;

static inline void col4(f32 *v, u8 *c, f32 al) {
    v[0] = c[0];
    v[1] = c[1];
    v[2] = c[2];
    v[3] = c[3] * al;
}

typedef struct {
    u8 pad[0xB];
    u8 a;
} TailCol;

void pppKeShpTail2Draw(PppObject *obj, Tail2Key *key, PppEntry *e) {
    PppMtx m0;
    PppMtx m1;
    PppVec4 a;
    PppVec4 b;
    PppVec4 f;
    PppVec4 ev;
    PppVec4 c;
    PppVec4 d;
    TailParam p;
    Tail2Work *w;
    u8 *src;
    PppShapeEnt *s;
    s32 n, idx, last, j, cnt;
    f32 al, fn, sz, t, step, dt, rem, len, seg;
    f32 *pa, *pe, *pf, (*pm)[4];
    PppVec4 *pts;

    if (key->id == 0xFFFF)
        return;
    pa = a;
    al = PPP_WORK(TailCol, obj, e, 1)->a * 0.0078125f;
    cnt = key->n - 1;
    fn = cnt;
    col4(c, key->c0, al);
    col4(a, key->c1, al);
    func_00267530(b, c, pa);
    func_002674b0(d, b, fn);
    s = &D_00615E64->shapes[key->id];
    w = PPP_WORK(Tail2Work, obj, e, 0);
    pm = m1;
    p.h8[3] = 0;
    p.h8[2] = 0;
    p.h8[1] = 0;
    p.h8[0] = 0;
    p.b18 = 0;
    p.p10 = pm;
    p.p1C = 0;
    if (!key->b24)
        p.flags = 128;
    else
        p.flags = 0;
    if (key->b25 == 1)
        p.flags |= 0x10;
    src = (u8 *) s->shape + s->shape->f[w->frame].off;
    sceVu0CopyMatrix(m0, D_00615E68->m);
    sceVu0UnitMatrix(pm);
    sz = key->size;
    t = key->len;
    step = (sz - key->size2) / fn;
    dt = t * (step / sz);
    n = cnt;
    if (t == 0.0f)
        n = -1;
    idx = w->idx;
    pts = w->pts;
    last = w->n - 1;
    func_002675a8(pa, pts[idx]);
    func_002675a8(b, pa);
    j = idx + 1;
    rem = t;
    if (idx == last)
        j = 0;
    pe = ev;
    func_002675a8(pe, pts[j]);
    pf = f;
    func_00267530(pf, pe, b);
    len = func_001a9350(pf);
    seg = len;
    if (!key->draw)
        goto next;
    for (;;) {
        vuFtoi0Bytes(&p.r, c);
        vuScaleXYZ(pm[0], m0[0], sz * D_003701F0[0]);
        vuScaleXYZ(m1[1], m0[1], sz * D_003701F0[1]);
        if (key->local)
            vuApply(m1[3], D_00615EB0, pa);
        else
            vuApply2(m1[3], D_00615FC0, pa);
        vuMulMatrix(pm, D_00616040, pm);
        {
            s32 *gp = &D_00616224;
            p.w14 = *gp;
            *gp = func_001b8198(src, &p, s->unk4);
        }
    next:
        if (n == 0)
            return;
        vuSub(c, c, d);
        t -= dt;
        if (t <= 0.0f)
            return;
        sz -= step;
        if (t <= len) {
            vuScale(pa, pf, rem / seg);
            vuAdd(pa, b, pa);
        } else {
            do {
                s32 k = j;
                j++;
                if (k == last)
                    j = 0;
                if (j == idx)
                    return;
                vuCopy(b, pe);
                vuCopy(ev, pts[j]);
                pe = ev;
                vuSub(pf, pe, b);
                rem -= seg;
                pf = f;
                seg = vuLen(pf);
                len += seg;
            } while (!(t <= len));
            vuScale(pa, pf, rem / seg);
            vuAdd(pa, b, pa);
        }
        rem += t;
        n--;
        len -= t;
    }
}
