#include "common.h"
#include "data/pieces/D_002C5968.h"
/* 241948 */

/* 2433e8 */

/* 243bd8 */

/* 243da0 */
extern s32 D_00656420;

/* 243e58 */
extern s32 D_00656420;

/* 244d00 */
#include "data/types/text_00240000_s6_25.h"

/* 249a48 */
#include "data/types/text_00240000_s6_25_p.h"
void sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
s32 sceGsExecLoadImage(void *, void *);
s32 sceGsSyncPath(s32, s32);
void func_00237018(void *, s32, s32);

/* 249dc8 */
s32 sceGsExecLoadImage(void *, void *);
s32 sceGsSyncPath(s32, s32);
void sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
void func_00237018(void *, s32, s32);

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
extern Prm *D_0046A038;
#include "data/pieces/D_0046A03C.h"
#include "data/pieces/D_0046A040.h"
#include "data/pieces/D_0046A044.h"
extern s32 D_0046A048;
extern Prm *D_00669A18[8]; /* src/data/bss_0066.c: s32 D_00669A18[8] */
void func_0024e1d0(void);
void func_0024b448(s32 i) {
    s32 o40, o48, t10, t18;
    Prm *p;
    o40 = D_0046A040;
    o48 = D_0046A048;
    switch ((*(volatile Sema_2c5968 *)&D_002C5968).mode) { default: return; case 0: break; }
    p = D_00669A18[i];
    D_0046A038 = p;
    D_0046A03C = p->unkC;
    t10 = p->unk10;
    (*(s32 *)&D_0046A044) = p->unk14;
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
#include "data/pieces/D_0046A038.h"
