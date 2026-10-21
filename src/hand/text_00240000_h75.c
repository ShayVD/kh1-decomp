#include "common.h"
#include "data/bss_0066.h"

typedef struct { s32 dur; u8 pad[0xc]; f32 v[4][4]; } Frame50;
typedef struct { s32 time; s32 idx; s32 n; Frame50 *fr; } Anim50;
typedef struct { u8 pad[0x78]; Anim50 b; } UiB;
void __assert(const char *, s32, const char *);


typedef union {
    struct { u8 pad[0x60]; u64 flags; } h;
    struct { u8 pad[0x20]; s32 m[4][4]; u32 flags; } s;
} UiC;
void func_0024a0e0(UiC *, s32 *);
void func_0024a300(UiB *, s32 (*)[4]);

void func_0024ac68(UiC *u, s32 (*out)[4]) {
    s32 i, j;
    if ((u->h.flags & 10) == 10) {
        s32 t[4];
        func_0024a0e0(u, t);
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                out[i][j] = t[j];
    } else if ((u->h.flags & 0xC0) == 0xC0) {
        s32 t[4][4];
        func_0024a300((UiB *)u, t);
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                out[i][j] = t[i][j];
    } else if (u->s.flags & 0x20) {
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                out[i][j] = u->s.m[i][j];
    } else {
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                out[i][j] = u->s.m[0][j];
    }
}

extern s32 D_0046A558;
extern s32 D_0046A55C;
extern s32 D_0046A560;
extern s32 D_0046A5D8;
extern s16 D_00669A40[8]; /* src/data/bss_0066.c: s16 D_00669A40[0xc] */
extern s32 D_00669A60;
extern s32 D_00669A64;
extern s32 D_00669A7C;
void func_0024c460(void *);
void func_0024be88(void *);
void func_0024c950(void *);
void func_001f8f30(void);
s32 func_0024be58(void);
void func_0011d768(s32);
s32 func_001f3840(void *);
void func_0024cf00(void);
s32 func_001be010(s32);
void func_001be3c0(s32);

void func_0024cfa0(void *a) {
    s32 i;
    func_0024c460(a);
    func_0024be88(a);
    func_0024c950(a);
    func_001f8f30();
    if (D_0046A558 != 0 && (func_0024be58() & 0x2000)) {
        s32 *p = &D_0046A55C;
        if (*p == 0) {
            *p = 1;
            func_0011d768(2);
            func_001f3840(a);
            D_0046A5D8 = 0;
            return;
        }
    }
    if (!(func_0024be58() & 0x2000)) return;
    if (D_0046A55C != 0) return;
    if (D_0046A560 == 0) return;
    for (i = 0; i < 8; i++) {
        if (D_00669A40[i] == -1) continue;
        if (D_00669A40[i] != 0) break;
    }
    if (i == 8) {
        func_0011d768(4);
        return;
    }
    D_0046A5D8 = 1;
    D_0046A55C = 1;
    func_0011d768(2);
    func_001f3840(a);
    if (D_00669A60 < 0) return;
    func_0024cf00();
    if (D_00669A64 != 0) {
        D_00669A7C = func_001be010(D_00669A60);
        return;
    }
    func_001be3c0(D_00669A60);
}

/* needs make: uses rodata */
void func_0024a300(UiB *u, s32 (*out)[4]) {
    Anim50 *ra = &u->b;
    s32 i, j;
    if (!ra) __assert("ttlib/ui.c", 137, "ra");
    if (ra->idx < ra->n - 1) {
        f32 t = (f32)ra->time / (f32)ra->fr[ra->idx].dur;
        Frame50 *f = &ra->fr[ra->idx];
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                out[i][j] = f->v[i][j] + (f[1].v[i][j] - f->v[i][j]) * t;
    } else {
        Frame50 *f = &ra->fr[ra->idx];
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                out[i][j] = f->v[i][j];
    }
}

typedef struct { void *unk0; void *unk4; s32 unk8; u8 *unkC; u8 *unk10; u8 *unk14; s32 unk18; void *unk1C; s32 unk20; void *unk24; } Task;
extern Task *D_00669A18[8]; /* src/data/bss_0066.c: s32 D_00669A18[8] */
extern void *D_00469FF8[];
extern s32 D_00469FD8[];
extern void *D_0046A018[];
extern u8 *D_0046A03C;
extern u8 *D_0046A040;
extern u8 *D_0046A044;
extern s32 D_0046A048;
void func_0024b1e8(const char *, const char *, s32);
void func_0024e0a4(void);

Task *func_0024b7a0(s32 grp, Task *t, void *arg) {
    u8 *a, *b, *c;
    s32 i, off;
    u8 *s40;
    s32 s48;
    off = grp * 0x10320;
    s40 = D_0046A040;
    s48 = D_0046A048;
    a = (u8 *)t + 40;
    if ((u32)a & 15) a = a - ((u32)a & 15) + 16;
    t->unkC = a;
    for (i = 0; i < 8; i++) if (D_00669A18[i] == NULL) break;
    if (i == 8) func_0024b1e8("i!=TASK_GRUPE_MAX", "src/sa_task.c", 257);
    b = a + off;
    c = b + 0x370;
    t->unk20 = i;
    t->unkC = a;
    D_0046A03C = a;
    t->unk10 = b;
    D_0046A040 = b;
    t->unk14 = c;
    D_0046A044 = c;
    t->unk18 = grp;
    D_0046A048 = grp;
    t->unk0 = D_00469FF8[i];
    t->unk8 = D_00469FD8[i];
    t->unk4 = D_0046A018[i];
    t->unk24 = arg;
    D_00669A18[i] = t;
    t->unk1C = NULL;
    func_0024e0a4();
    D_0046A040 = s40;
    D_0046A048 = s48;
    return t;
}

typedef struct { s32 unk0; char *(*unk4)(void); s32 unk8; s32 unkC; s32 unk10; } HddCtx;
extern HddCtx D_0046A688;
extern s32 D_0046A674;
extern s32 D_0046A614;
#include "data/pieces/D_0046A650.h"
void func_0024d9a0(void);
void func_0024d8f0(void);
s32 sprintf(char *, const char *, ...);
s32 func_0025b588(const char *, s32);
s32 func_0025c448(s32, s32, s32, s32, s32, s32);
s32 func_0025ce38(s32);
s32 func_0024dad0(const char *, s32);

#include "data/pieces/D_004919B0.h"

s32 func_0024db78(s32 size) {
    HddCtx *c = &D_0046A688;
    s32 used = 0;
    s32 fd;
    s32 flag;
    s32 n;
    char buf[64];
    flag = c->unk10;
    D_0046A674 = 0;
    if (flag) func_0024d9a0();
    D_0046A614 = 40;
    sprintf(buf, "hdd0:%s,,%s", c->unk4(), D_0046A650);
    fd = func_0025b588(buf, 1);
    if (fd >= 0) {
        used = func_0025c448(fd, 0x6803, 0, 0, 0, 0);
        if (used < 0) used = 0;
        used++;
        func_0025ce38(fd);
    }
    D_0046A614 = 50;
    n = ((((u32)(size + 0xFFFFF) >> 20) + 127) >> 7) + 1;
    if (func_0024dad0(D_004919B0, n - used) == 0) D_0046A674 = -1;
    if (flag) func_0024d8f0();
    D_0046A614 = 80;
    return D_0046A674;
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
void func_0024b508();
void func_0024b520();
void func_0024b538();
void func_0024b550();
void func_0024b568();
void func_0024b580();
void func_0024b598();
void func_0024b5b0();
void *D_00469FF8[0x8] ALIGNED(8) = {
    (void *)func_0024b508, (void *)func_0024b520, (void *)func_0024b538, (void *)func_0024b550,
    (void *)func_0024b568, (void *)func_0024b580, (void *)func_0024b598, (void *)func_0024b5b0,
};
void func_0024b2c8();
void func_0024b2f8();
void func_0024b328();
void func_0024b358();
void func_0024b388();
void func_0024b3b8();
void func_0024b3e8();
void func_0024b418();
s32 D_00469FD8[0x8] ALIGNED(8) = {
    (s32)func_0024b2c8, (s32)func_0024b2f8, (s32)func_0024b328, (s32)func_0024b358,
    (s32)func_0024b388, (s32)func_0024b3b8, (s32)func_0024b3e8, (s32)func_0024b418,
};
void func_0024b610();
void func_0024b628();
void func_0024b640();
void func_0024b658();
void func_0024b670();
void func_0024b688();
void func_0024b6a0();
void func_0024b6b8();
void *D_0046A018[0x8] ALIGNED(8) = {
    (void *)func_0024b610, (void *)func_0024b628, (void *)func_0024b640, (void *)func_0024b658,
    (void *)func_0024b670, (void *)func_0024b688, (void *)func_0024b6a0, (void *)func_0024b6b8,
};
#include "data/data_0046.h"
