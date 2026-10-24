/* The notice (docs/modules.md "Session 46"), 0x00243168-0x00243c10, default
 * flags part.  A queue of up to five notices (D_006561D0: a Notice is a kind
 * 0-2, an id and an alpha) shown one at a time at (160, 344): the sprite set
 * of its kind and the name of id (func_00147840 / func_00147808) in grey 0x73
 * or 0xE6.  func_00243630 queues one (alpha 1), func_00243a20 is the draw hook
 * (func_00243a90, the set up, registers it and loads the four sprite files
 * into D_00656230), func_00243668 is the HUD's step for it (clears the queue)
 * and func_00243bd8 is 1 while one is shown or queued.  Most likely the
 * "obtained" message; not proved by a boot. */
#include "common.h"

typedef struct { s32 kind; s32 id; f32 alpha; } Notice;
typedef struct {
    s32 cap;    /* +0x0 */
    Notice *buf; /* +0x4 */
    s32 wr;     /* +0x8: records written */
    s32 rd;     /* +0xC: next record to read */
} NoticeQueue;
typedef struct {
    s32 on;         /* +0x0 */
    Notice v;       /* +0x4: the one shown */
    s32 unk10;      /* +0x10: frames shown */
    NoticeQueue q;  /* +0x14 */
    Notice buf[5];  /* +0x24 */
} NoticeMgr;

extern NoticeMgr D_006561D0;
extern s32 D_006560E0;
extern s32 D_00458548, D_0045854C;
extern void *D_00656230[];
extern u8 D_00454A40[];
extern u8 D_00455A10[];
extern u8 D_004569E0[];
extern u8 D_004577D0[];
extern u8 D_00458520[];
void *memset(void *, s32, u32);
void func_0024ae00(void *);
void func_0024af00(void *);
void func_002432d8(void *, void *, s32, s32);
s32 func_001f0638(s32, s32, s32, s32, s32, s32);
void func_002436c0(s32);
void func_0024aac8(void *);
void func_0024afc0(void *, void *, void *);
s32 func_0011ef38(s32 (*)(void));
void func_0011ef10(s32, s32 (*)(void));

void func_00243168(NoticeQueue *q, s32 cap, Notice *buf) {
    memset(q, 0, 0x10);
    q->cap = cap;
    q->buf = buf;
}

void func_002431b8(NoticeQueue *q, Notice *v) {
    if (q->wr != q->cap) {
        q->buf[q->wr] = *v;
        q->wr++;
    }
}

s32 func_00243208(NoticeQueue *q, Notice *v) {
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

s32 func_00243278(NoticeQueue *q, Notice *v) {
    if (q->wr == q->rd)
        return 0;
    *v = q->buf[q->rd];
    return 1;
}

void func_002432c8(NoticeQueue *q) {
    q->rd = 0;
    q->wr = 0;
}

void func_00243380(s32 on, void *spr, void *tex, s32 x, s32 y) {
    if (on != 0) {
        func_0024ae00(spr);
    }
    func_0024af00(spr);
    func_002432d8(spr, tex, x, y);
}

void func_002433e8(s32 x, s32 y, s32 a2, s32 sel, f32 f) {
    u8 col[4];
    u8 *p;
    if (sel) {
        p = col; *p++ = 0x73; *p++ = 0x73; *p++ = 0x73;
        *p = (u32)(f * 128.0f);
    } else {
        p = col; *p++ = 0xe6; *p++ = 0xe6; *p++ = 0xe6;
        *p = (u32)(f * 128.0f);
    }
    D_006560E0 = func_001f0638(D_006560E0, 1, *(s32 *)col,
        ((((x + D_00458548) << 4) + 0x7000) >> 4) - 0x700,
        ((((y + D_0045854C) << 4) + 0x7400) >> 4) - 0x740, a2);
}

void func_00243630(s32 kind, s32 id) {
    Notice v;
    v.id = id;
    v.kind = kind;
    v.alpha = 1.0f;
    func_002431b8(&D_006561D0.q, &v);
}

void func_00243668(void) {
    D_006561D0.on = 0;
    func_002432c8(&D_006561D0.q);
}

void func_00243690(Notice *v) {
    D_006561D0.unk10 = 0;
    D_006561D0.v = *v;
    D_006561D0.on = 1;
}

s32 func_00243a20(void) {
    Notice v;
    s32 r = 0;
    NoticeMgr *s = &D_006561D0;
    if (s->on == 0) {
        if (!func_00243208(&s->q, &v)) return 0;
        func_00243690(&v);
    } else {
        r = func_00243278(&s->q, &v) != 0;
    }
    func_002436c0(r);
    return 0;
}

void func_00243a90(void) {
    memset(&D_006561D0, 0, 0x60);
    func_00243168(&D_006561D0.q, 5, D_006561D0.buf);
    D_006561D0.on = 0;
    func_0024aac8(D_00454A40);
    func_0024aac8(D_00455A10);
    func_0024aac8(D_004569E0);
    func_0024aac8(D_004577D0);
    func_0024afc0(D_00458520, &D_00656230[0], D_00454A40);
    func_0024afc0(D_00458520, &D_00656230[9], D_00455A10);
    func_0024afc0(D_00458520, &D_00656230[18], D_004569E0);
    func_0024afc0(D_00458520, &D_00656230[27], D_004577D0);
    if (func_0011ef38(func_00243a20) == 0) {
        func_0011ef10(0x29811, func_00243a20);
    }
}

s32 func_00243bd8(void) {
    Notice buf;
    if (D_006561D0.on) return 1;
    return func_00243278(&D_006561D0.q, &buf) != 0;
}
