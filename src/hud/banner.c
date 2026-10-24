/* The banner (docs/modules.md "Session 46"), 0x00248628-0x00248fb8.
 * func_00248ac8 (kind, value) queues an entry (Vec12Queue, five places in
 * D_00669700.buf) and func_00248e30, the draw hook registered by
 * func_00248ea0 (the set up), takes one when nothing shows (func_00248b28)
 * and draws it with func_00248b58: the sound 31 when it starts, about 60
 * frames (fewer when another one waits: 2 for kind 0, 6 for kind 1), then
 * for kind 0 the closing animation of D_00669760[1] until its flag 4.  The
 * banner is seven parts of 0xC0 bytes and an end part (func_002489c8) at
 * (160, 344), each one a sprite set (func_00248798) in D_00669620.  What it
 * announces is not proved by a boot. */
#include "common.h"
#include "data/types/text_00240000_h50.h"
#include "data/types/text_00240000_sw.h"
#include "data/bss_0066_typed.h"

typedef struct { s32 a, b; f32 c; } Vec12;   /* a: the kind, b: the value, c: the alpha */
typedef struct { s32 cap; Vec12 *buf; s32 wr; s32 rd; } Vec12Queue;
typedef struct {
    s32 on;           /* +0x0: 1 new, 2 shown, 3 closing, 4 done */
    Vec12 v;          /* +0x4 */
    s32 unk10;        /* +0x10: frames shown */
    Vec12Queue q;     /* +0x14 */
    Vec12 buf[5];     /* +0x24 */
} Vec12Mgr;
typedef struct { u8 pad[0x60]; Q4 q[4]; Q4 r[4]; } Panel;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0 - 0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Pkt;

Pkt D_006694B0 ALIGNED(16);
Q4 *D_00669614 ALIGNED(4);
Panel D_00669620 ALIGNED(32);
extern Vec12Mgr D_00669700;
/* D_00669700.q by its own label: cover_check needs a size for D_00669714,
 * or D_00669760 after it becomes covered (float_covered.txt). */
extern Vec12Queue D_00669714;
extern Q4 D_00351E10[];
extern s32 D_00469C94;
extern s32 D_00469C98;
extern u8 D_00467410[], D_00468220[], D_00468E10[];
extern u8 D_00469C20[], D_00469C48[], D_00469C70[];
extern u8 D_004267C0[], D_004267F0[];
void *memset(void *, s32, u32);
void func_0011d768(s32);
void func_0011ef10(s32, s32 (*)(void));
s32 func_0011ef38(s32 (*)(void));
Q4 *func_001f0638(Q4 *, s32, s32, s32, s32, s32);
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
Q4 *func_002388b8(void *, s32, Q4 *);
void func_0024aa48(void *, void *, void *);
void func_0024aac8(void *);
void func_0024ac08(void *, s32 *);
void func_0024ac68(UiObj *, s32 (*)[4]);
void func_0024ae00(void *);
void func_0024af00(void *);
void func_0024afc0(void *, void *, void *);

void func_00248628(Vec12Queue *q, s32 cap, Vec12 *buf) {
    memset(q, 0, 0x10);
    q->cap = cap;
    q->buf = buf;
}

void func_00248678(Vec12Queue *q, Vec12 *v) {
    if (q->wr != q->cap) {
        q->buf[q->wr] = *v;
        q->wr++;
    }
}

s32 func_002486c8(Vec12Queue *q, Vec12 *v) {
    if (q->wr == q->rd)
        return 0;
    *v = q->buf[q->rd];
    q->rd++;
    if (q->wr == q->rd) {
        q->rd = 0;
        q->wr = 0;
    }
    return 1;
}

s32 func_00248738(Vec12Queue *q, Vec12 *v) {
    if (q->wr == q->rd)
        return 0;
    *v = q->buf[q->rd];
    return 1;
}

void func_00248788(Vec12Queue *q) {
    q->rd = 0;
    q->wr = 0;
}

void func_00248798(void *spr, void *tex, s32 dx, s32 dy) {
    s32 i;
    Panel *d = &D_00669620;
    func_0024aa48(spr, d, tex);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    D_00669610 = func_002388b8(&D_00669620, 1, D_00669610);
}

void func_00248840(s32 show, void *spr, void *tex, s32 x, s32 y) {
    if (show) {
        func_0024ae00(spr);
    }
    func_0024af00(spr);
    func_00248798(spr, tex, x, y);
}

void func_002488a8(s32 x, s32 y, s32 a2, s32 sel, f32 f) {
    u8 col[4];
    u8 *p;
    if (sel) {
        p = col; *p++ = 0x73; *p++ = 0x73; *p++ = 0x73;
        *p = (u32)(f * 128.0f);
    } else {
        p = col; *p++ = 0xe6; *p++ = 0xe6; *p++ = 0xe6;
        *p = (u32)(f * 128.0f);
    }
    D_00669610 = func_001f0638(D_00669610, 1, *(s32 *)col,
        ((((x + D_00469C94) << 4) + 0x7000) >> 4) - 0x700,
        ((((y + D_00469C98) << 4) + 0x7400) >> 4) - 0x740, a2);
}

void func_002489c8(s32 show, void *o, void *tex, void *end, s32 x, s32 y, s32 txt, s32 sel, f32 f) {
    s32 r[4];
    u8 *p = (u8 *)o;
    s32 i = 6;
    u8 *top = p;
    do {
        func_00248840(show, p, tex, x, y);
        p += 0xC0;
    } while (--i >= 0);
    func_00248840(show, p, end, x, y);
    if (txt) {
        func_0024ac08(top, r);
        func_002488a8(x + r[0], y + r[1], txt, sel, f);
    }
}

void func_00248ac8(s32 kind, s32 value) {
    Vec12 v;
    v.b = value;
    v.a = kind;
    v.c = 1.0f;
    func_00248678(&D_00669714, &v);
}

void func_00248b00(void) {
    D_00669700.on = 0;
    func_00248788(&D_00669700.q);
}

void func_00248b28(Vec12 *v) {
    D_00669700.unk10 = 0;
    D_00669700.v = *v;
    D_00669700.on = 1;
}

void func_00248b58(s32 next) {
    s32 first = 0, done = 0;
    s32 n;
    s32 buf[4][4];
    Vec12 *v;
    Vec12Mgr *m = &D_00669700;
    if (m->on == 0) return;
    v = &m->v;
    func_002370c8(&D_006694B0);
    D_006694B0.unkE0 = 5;
    D_006694B0.unk60 = 0x30003;
    func_00237018(&D_006694B0, 22, 1);
    D_00669614 = D_00351E10;
    D_00669610 = D_00351E10 + 1;
    switch (m->on) {
    case 1:
        m->on = 2;
        func_0011d768(31);
        first = 1;
        break;
    case 2:
        n = ++m->unk10;
        if (v->a == 0) {
            if (n < 61 && (!next || n < 2)) break;
            done = 1;
            m->on = 3;
        } else {
            if (n < 61 && (!next || n < 6)) break;
            done = 1;
            m->on = 3;
        }
        break;
    case 3:
        if (v->a == 0) {
            func_0024ac68(D_00669760[1].p, buf);
            v->c = (f32)buf[0][3] * 0.0078125f;
            if (v->a == 0 && (D_00669760[1].p->unk9C & 4))
                m->on++;
        } else {
            m->on = 4;
        }
        break;
    case 4:
        m->on = 0;
        return;
    }
    v = &D_00669700.v;
    switch (v->a) {
    case 0:
        if (D_00669700.on == 2)
            func_002489c8(first, D_00669760[0].p, D_004267C0, D_004267F0, 160, 344, v->b, 0, v->c);
        else
            func_002489c8(done, D_00669760[1].p, D_004267C0, D_004267F0, 160, 344, v->b, 0, v->c);
        break;
    case 1:
        func_002489c8(first, D_00669760[2].p, D_004267C0, D_004267F0, 160, 344, v->b, 0, v->c);
        break;
    }
    func_00237018(D_00669614, D_00669610 - D_00669614, 1);
}

s32 func_00248e30(void) {
    Vec12 v;
    s32 r = 0;
    Vec12Mgr *s = &D_00669700;
    if (s->on == 0) {
        if (!func_002486c8(&s->q, &v)) return 0;
        func_00248b28(&v);
    } else {
        r = func_00248738(&s->q, &v) != 0;
    }
    func_00248b58(r);
    return 0;
}

void func_00248ea0(void) {
    memset(&D_00669700, 0, 0x60);
    func_00248628(&D_00669700.q, 5, D_00669700.buf);
    D_00669700.on = 0;
    func_0024aac8(D_00467410);
    func_0024aac8(D_00468220);
    func_0024aac8(D_00468E10);
    func_0024afc0(D_00469C20, &D_00669760[0], D_00467410);
    func_0024afc0(D_00469C48, &D_00669760[1], D_00468220);
    func_0024afc0(D_00469C70, &D_00669760[2], D_00468E10);
    if (func_0011ef38(func_00248e30) == 0) {
        func_0011ef10(0x29811, func_00248e30);
    }
}
