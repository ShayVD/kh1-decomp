#include "common.h"
/* 241948 */
typedef struct {
    u8 pad[0x9C];
    void *unk9C;
    u8 padA0[0xA30 - 0xA0];
    s32 unkA30;
    u8 padA34[0xD00 - 0xA34];
} Ent;
typedef struct {
    s32 used[8];
    Ent ent[5];
} G;
extern G D_00651E50;
extern s32 D_00454810, D_00454814, D_00454818;
void func_002407b0(Ent *, s32);
void func_00241948(s32 i, s32 k) {

    Ent *e; s32 on = D_00651E50.used[i]; e = &D_00651E50.ent[i];
    if (e->unk9C != 0) return;
    switch (k) {
    case 0:
        func_002407b0(e, 2);
        e->unkA30 = D_00454810;
        break;
    case 1:
        func_002407b0(e, 3);
        e->unkA30 = D_00454814;
        break;
    case 2:
        func_002407b0(e, 4);
        e->unkA30 = D_00454818;
        break;
    }
}

/* 2433e8 */
extern s32 D_00458548, D_0045854C;
extern s32 D_006560E0;
s32 func_001f0638(s32, s32, s32, s32, s32, s32);
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

/* 243bd8 */
typedef struct { s32 on; u8 pad[0x10]; u8 x14[1]; } S61D0;
extern S61D0 D_006561D0;
s32 func_00243278(void *, void *);
s32 func_00243bd8(void) {
    s32 buf[4];
    if (D_006561D0.on) return 1;
    return func_00243278(D_006561D0.x14, buf) != 0;
}

/* 243da0 */
typedef struct { s32 r, g, b; } C3;
extern s32 D_00656420;
void func_00243da0(s32 x, s32 y, s32 a2, C3 *c, f32 f) {
    u8 col[4]; u8 *p;
    p = col; *p++ = c->r; *p++ = c->g; *p++ = c->b;
    *p = (u32)(f * 128.0f);
    D_00656420 = func_001f0638(D_00656420, 1, *(s32 *)col,
        (((x << 4) + 0x7000) >> 4) - 0x700,
        (((y << 4) + 0x7400) >> 4) - 0x740, a2);
}

/* 243e58 */
extern s32 D_00656420;
s32 func_001f0868(s32, s32, s32, s32, s32, s32, s32, s32);
void func_00243e58(s32 x, s32 y, s32 a2, C3 *c, f32 f) {
    u8 col[4]; u8 *p;
    p = col; *p++ = c->r; *p++ = c->g; *p++ = c->b;
    *p = (u32)(f * 128.0f);
    D_00656420 = func_001f0868(D_00656420, 1, 1, *(s32 *)col, x, y, a2, 12);
}

/* 244d00 */
#include "data/types/text_00240000_s6_25.h"
extern Obj D_0065FD80[5][10];
extern Obj D_00662300[3]; /* src/data/bss_0066.c: u8 D_00662300[0x240] */
void func_0024a568(Obj *);
void func_0024a678(Obj *);
void func_0024a0c0(Obj *);
void func_0024a088(Obj *);
void func_0024a2e0(Obj *);
void func_0024a450(Obj *);
void func_0024af00(Obj *);
void func_00244d00(s32 a, s32 b) {
    s32 i, j; Obj *o;
    if (a) {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 10; j++) {
                func_0024a568(&D_0065FD80[i][j]);
                func_0024a678(&D_0065FD80[i][j]);
            }
        }
        o = D_00662300;
        for (i = 0; i < 3; i++, o++) {
            func_0024a568(o);
            func_0024a678(o);
        }
    }
    if (b) {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 10; j++) {
                Obj *o = &D_0065FD80[i][j];
                if (o->fl & 2) { func_0024a0c0(o); func_0024a088(o); }
                if (o->fl & 0x40) { func_0024a2e0(o); func_0024a450(o); }
            }
        }
        o = D_00662300;
        for (i = 0; i < 3; i++, o++) {
            if (o->fl & 2) { func_0024a0c0(o); func_0024a088(o); }
            if (o->fl & 0x40) { func_0024a2e0(o); func_0024a450(o); }
        }
    }
    for (i = 0; i < 5; i++)
        for (j = 0; j < 10; j++)
            func_0024af00(&D_0065FD80[i][j]);
    o = D_00662300;
    for (i = 0; i < 3; i++, o++)
        func_0024af00(o);
}

/* 249a48 */
typedef struct {
    u32 total;
    u32 clutSize;
    u32 imageSize;
    u16 hdrSize;
    u16 clutColors;
    u8 fmt;
    u8 mip;
    u8 clutType;
    u8 imageType;
    s16 w;
    s16 h;
    u64 tex0;
    u64 tex1;
    u32 flags;
    u32 clut;
} TimPic;
typedef struct { u8 pad[0x10]; TimPic pic; u8 data[1]; } Tim;
#include "data/types/text_00240000_s6_25_p.h"
extern PsmEnt D_00469FB0[];
void sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
s32 sceGsExecLoadImage(void *, void *);
void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
void func_00237018(void *, s32, s32);

void func_00249a48(Tim *t, s32 sync) {
    u8 li[0x60];
    u64 pk[6];
    TimPic *p = &t->pic;
    u8 *img = NULL;
    u8 *clut;
    s16 psm, cpsm; u16 cbp;
    if (p->imageSize) {
        img = t->data;
        sceGsSetDefLoadImage(li, (u16)(p->tex0 & 0x3FFF), (u16)(p->tex0 >> 14 & 0x3F), (u16)((p->tex0 & 0x3F00000) >> 20), 0, 0, p->w, p->h);
        FlushCache(0);
        sceGsSyncPath(0, 0);
        sceGsExecLoadImage(li, img);
    }
    sceGsSyncPath(0, 0);
    pk[2] = 0x1000000000008001;
    pk[3] = 14;
    pk[5] = 0x3F;
    pk[4] = 0;
    func_00237018(pk, 3, 1);
    if (p->clutSize) {
        cbp = p->tex0 >> 37 & 0x3FFF;
        cpsm = D_00469FB0[p->clutType].psm;
        clut = img + p->imageSize;
        psm = D_00469FB0[p->imageType].psm;
        if (psm == 19) {
            sceGsSetDefLoadImage(li, cbp, 1, cpsm, 0, 0, 16, 16);
        } else if (psm == 20) {
            sceGsSetDefLoadImage(li, cbp, 1, cpsm, 0, 0, 8, 2);
        }
        FlushCache(0);
        sceGsSyncPath(0, 0);
        sceGsExecLoadImage(li, clut);
    }
    sceGsSyncPath(0, 0);
    pk[2] = 0x1000000000008001;
    pk[3] = 14;
    pk[5] = 0x3F;
    pk[4] = 0;
    func_00237018(pk, 3, 1);
    if (sync) sceGsSyncPath(0, 0);
}

/* 249dc8 */
typedef struct {
    u8 pad[8]; s32 x8; u8 padc[8]; s16 w; s16 h;
    u64 tex;
    u8 pad20[0x10];
} GsTexHdr;
typedef struct { u8 pad[0x10]; GsTexHdr h; u8 data[1]; } GsTex;
typedef struct { u64 a[6]; } Pkt6;
s32 sceGsExecLoadImage(void *, void *);
s32 sceGsSyncPath(s32, s32);
void sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
void func_00237018(void *, s32, s32);
void func_00249dc8(GsTex *t, s32 sync) {
    u8 li[0x60];
    Pkt6 pk;
    GsTexHdr *h = &t->h;
    u8 *d = NULL;
    if (h->x8) {
        d = t->data;
        sceGsSetDefLoadImage(li, (u16)(h->tex & 0x3fff), (u16)((h->tex >> 14) & 0x3f), (u16)((h->tex & 0x3f00000) >> 20), 0, 0, h->w, h->h);
        FlushCache(0);
        sceGsSyncPath(0, 0);
        sceGsExecLoadImage(li, d);
    }
    sceGsSyncPath(0, 0);
    pk.a[2] = 0x1000000000008001ULL;
    pk.a[3] = 0xe;
    pk.a[5] = 0x3f;
    pk.a[4] = 0;
    func_00237018(&pk, 3, 1);
    if (sync) sceGsSyncPath(0, 0);
}

/* 24aac8 */
typedef struct { s32 dur; u8 pad[0xc]; f32 v[4]; } Frame;
typedef struct { s32 dur; u8 pad[0x4c]; } Frame50;
typedef struct { s32 time; s32 idx; s32 n; Frame *fr; } Anim;
typedef struct { s32 time; s32 idx; s32 n; Frame50 *fr; } Anim50;
typedef union {
    struct { u8 pad[0x60]; u64 flags; } h;
    struct { u8 pad[0x60]; u32 flags; Anim a; u32 aflags; Anim50 b; u32 bflags; Anim c; u32 cflags; u8 pad2[0x20]; } s;
} Ui;
typedef struct { u8 pad[8]; s32 ui_off; u32 ui_size; s32 fa_off; u8 pad14[4]; s32 fb_off; u8 pad1c[4]; s32 fc_off; } UiFile;
void __assert(const char *, s32, const char *);
extern char D_00491848[], D_00491860[];
void func_0024aac8(UiFile *buffer) {
    Ui *u;
    s32 i, n;
    Frame *fa, *fc;
    Frame50 *fb;
    if ((s32)buffer & 0xf) __assert(D_00491848, 524, D_00491860);
    n = buffer->ui_size / sizeof(Ui);
    i = buffer->ui_size / sizeof(Frame50);
    u = (Ui *)((u8 *)buffer + buffer->ui_off);
    fa = (Frame *)((u8 *)buffer + buffer->fa_off);
    fb = (Frame50 *)((u8 *)buffer + buffer->fb_off);
    fc = (Frame *)((u8 *)buffer + buffer->fc_off);
    for (i = 0; i < n; i++, u++) {
        u32 fl = u->s.flags;
        if (fl & 2) {
            if ((s32)u->s.a.fr <= 0xfffff) u->s.a.fr = &fa[(s32)u->s.a.fr];
        }
        if (fl & 0x40) {
            if ((s32)u->s.b.fr <= 0xfffff) u->s.b.fr = &fb[(s32)u->s.b.fr];
        }
        if (fl & 4) {
            if ((s32)u->s.c.fr <= 0xfffff) u->s.c.fr = &fc[(s32)u->s.c.fr];
        }
    }
}

/* 24b448 */
typedef struct { u8 lo:3; u8 mode:2; u8 hi:3; } Bits8;
extern volatile Bits8 D_002C5968;
extern Prm *D_0046A038;
extern s32 D_0046A03C;
extern s32 D_0046A040;
extern s32 D_0046A044;
extern s32 D_0046A048;
extern Prm *D_00669A18[8]; /* src/data/bss_0066.c: s32 D_00669A18[8] */
void func_0024e1d0(void);
void func_0024b448(s32 i) {
    s32 o40, o48, t10, t18;
    Prm *p;
    o40 = D_0046A040;
    o48 = D_0046A048;
    switch (D_002C5968.mode) { default: return; case 0: break; }
    p = D_00669A18[i];
    D_0046A038 = p;
    D_0046A03C = p->unkC;
    t10 = p->unk10;
    D_0046A044 = p->unk14;
    D_0046A040 = t10;
    t18 = p->unk18;
    D_0046A048 = t18;
    p->unk1C++;
    func_0024e1d0();
    D_0046A040 = o40;
    D_0046A048 = o48;
}

/* 24ba28 */
extern s8 D_0046A070[];
s32 strlen(const char *);
s32 memcmp(const void *, const void *, s32);

s32 func_0024ba28(s32 *p, char *name, s32 idx, u8 *out) {
    s32 len = strlen(name);
    s32 n, w, type, cnt, sz;
    u8 *src, *dst;
    for (;;) {
        n = *p++;
        if (n == 0) return -1;
        w = (n + 3) / 4;
        if (len == n && memcmp(p, name, n) == 0) {
            p += w;
            type = *p++;
            cnt = *p++;
            sz = D_0046A070[type];
            if (idx >= cnt) return -1;
            src = (u8 *)p + idx * sz;
            dst = out;
            if (sz > 0) do { *dst++ = *src++; } while (--sz);
            return type;
        }
        p += w;
        type = *p++;
        cnt = *p++;
        sz = D_0046A070[type];
        w = (sz * cnt + 3) / 4;
        p += w;
    }
}
#include "data/bss_0065_mixed.h"
#include "data/data_0046.h"
#include "data/data_0045.h"
#include "data/data_0049.h"
#include "data/pieces/D_00469FB0.h"
#include "data/pieces/D_0046A038.h"
