#include "common.h"
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
void func_0024aac8(UiFile *buffer) {
    Ui *u;
    s32 i, n;
    Frame *fa, *fc;
    Frame50 *fb;
    if ((s32)buffer & 0xf) __assert("ttlib/ui.c", 524, "((int)buffer & 0xf)==0");
    n = buffer->ui_size / sizeof(Ui);
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
