/* Hand-matched functions (worker 2). Grouped by address; the original
 * translation units are not known yet. */
#include "common.h"
#include "data/bss_0049.h"
#include "data/bss_004D.h"

/* 4x4 matrix pair: a[] from the caller's matrix, b[] from D_002BC170. */
typedef struct {
    s32 pad[2];
    s32 a[16];
    s32 b[16];
} MatPair;

extern s32 D_002BC170[4][4];

void func_00108be8(s32 unused, s32 m[4][4], MatPair *d) {
    s32 i, j, k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            d->a[k] = m[i][j];
            d->b[k] = D_002BC170[i][j];
            k++;
        }
    }
}

void func_00108c58(s32 m[4][4], MatPair *d) {
    s32 i, j, k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            d->a[k] = m[i][j];
            d->b[k] = D_002BC170[i][j];
            k++;
        }
    }
}

void iFlushCache(s32);

/* Restart the VIF1 DMA channel on the chain at arg+0x10. */
s32 func_00108d90(void *arg) {
    *(volatile u32 *)0x10009020 = 0;
    *(volatile u32 *)0x10009030 = *(u32 *)((u8 *)arg + 0x10) & 0x0FFFFFFF;
    *(volatile u32 *)0x1000E010 = 2;
    iFlushCache(0);
    *(volatile u32 *)0x10009000 = 0x145;
    return 2;
}

/* sceGsLoadImage / sceGsStoreImage packets (0x70 bytes). */
#include "data/types/text_00100000_h2.h"

void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
void func_002660c0(GsImagePacket *, s16, s16, s16, s16, s16, s16, s16);
s32 sceGsExecStoreImage(GsImagePacket *, void *);
void *func_001559f0(s32, s32);

#include "data/pieces/D_002B677C.h"

s32 func_0010a058(void) {
    GsImagePacket si;
    void **p;

    func_002660c0(&si, 0x1a00, 8, 1, 0, 0, 512, 384);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    p = &D_002B677C;
    *p = func_001559f0(62, 2);
    sceGsExecStoreImage(&si, *p);
    return 4;
}

#include "data/pieces/D_002BC070.h"
extern s32 D_002B6774;
void func_001038b0(s32);
s32 func_0011ef10(s32, s32 (*)(void));
s32 func_0010a058(void);

s32 func_0010a0d8(void) {
    D_002B6774 = 1;
    if ((*(s32 *)&D_002BC070) != 128) func_001038b0(1);
    return func_0011ef10(0x2e630, func_0010a058);
}

void func_00106b18(void *);
void *func_00121e28(s32, void **);
extern u8 D_002B6760[];
#include "data/pieces/D_002B6778.h"
void func_0010a3e8(void) {
    GsImagePacket si;
    func_00106b18(D_002B6760);
    func_002660c0(&si, 0x3600, 4, 1, 0, 0, 256, 192);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    (*(void **)&D_002B6778) = func_00121e28(0x24000, ((void **)&D_002B6778));
    sceGsExecStoreImage(&si, ((void *)D_002B6778));
}
extern u64 D_002B70B0[];
extern s32 D_00495250;
void func_0010a4d8(u64 *, s32, s32, s32, s32, s32, s32);
s32 func_0010a550(u64 *p, s32 a1, s32 a2, s32 a3, s32 a4, s32 idx, s32 a6) {
    p[0] = D_002B70B0[idx];
    p[1] = 0;
    p += 2;
    func_0010a4d8(p, a2, a6, a4, 4, a3, D_00495250);
    ((s32 *)p)[7] = 0x8000;
    ((s32 *)p)[19] = 0x8000;
    return a1 + 13;
}
extern u8 D_00495210[];
void func_00267b08(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_0010b190(u8 *p) {
    func_00267b08(D_00495210, 512.0f, 1.0f, 1.0f,
                  *(f32 *)(p + 0x30) + 2048.0f, *(f32 *)(p + 0x34) + 2048.0f,
                  1.0f, 16777000.0f, 2.0f, 4000000.0f);
}

/* Callbacks run by the semaphore-driven thread func_0010c0c8. */
#include "data/types/text_00100000_h2_p.h"
#include "data/pieces/D_002B75A0.h"
extern s32 D_00495260;
s32 WaitSema(s32);
void func_0010c0c8(void) {
    s32 i;
    for (;;) {
        WaitSema(D_00495260);
        for (i = 0; i < 2; i++) {
            if (D_002B75A0[i].fn) {
                D_002B75A0[i].fn(D_002B75A0[i].arg);
                D_002B75A0[i].done = 1;
            }
        }
    }
}
void func_0010c170(void (*fn)(s32), s32 arg) {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (!D_002B75A0[i].fn) {
            D_002B75A0[i].fn = fn;
            D_002B75A0[i].arg = arg;
            D_002B75A0[i].done = 0;
            return;
        }
    }
}
void func_0010c1b8(void (*fn)(s32)) {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (fn == D_002B75A0[i].fn) {
            D_002B75A0[i].fn = 0;
            D_002B75A0[i].arg = 0;
            D_002B75A0[i].done = 0;
            return;
        }
    }
}

extern u8 D_0048CD50[];
extern u8 D_00495280[];
s32 func_001205f0(void *, void *);
void *memcpy(void *, const void *, u32);

void *func_0010c3c0(void) {
    void *p = func_001559f0(52, 12);
    s32 n = func_001205f0(D_0048CD50, p);
    return memcpy(D_00495280, p, n);
}

extern GsImagePacket D_002BC1B0;
#include "data/pieces/D_002BD118.h"
void sceGsSetDefLoadImage(GsImagePacket *, s16, s16, s16, s16, s16, s16, s16);
s32 sceGsExecLoadImage(GsImagePacket *, void *);

s32 func_0010c4b0(void) {
    switch (D_002BD118) {
    case 5:
    case 6:
        return 0;
    }
    sceGsSetDefLoadImage(&D_002BC1B0, 0x3600, 4, 0, 0, 0, 256, 256);
    sceGsSyncPath(0, 0);
    FlushCache(0);
    sceGsExecLoadImage(&D_002BC1B0, D_00495280);
    return 0;
}

typedef struct {
    u8 pad[10];
    u16 a;
    u8 pad2[4];
} El16;

typedef struct {
    u8 pad[0x18];
    f32 add;
    u8 pad2[4];
    El16 *e;
} Fader;

/* Raise e[1..n].a by f->add, clamping at 128. */
void func_0010ce50(Fader *f, s32 n) {
    El16 *e;
    if (n <= 0) return;
    e = f->e + 1;
    do {
        if (e->a < 128) e->a = e->a + f->add;
        else e->a = 128;
        e++;
    } while (--n);
}
typedef struct {
    u8 pad[0xc];
    f32 v;
} E16;
typedef struct { u16 n; u16 pad; f32 a; f32 b; u8 pad2[4]; E16 e[1]; } Acc;
void func_0010cf38(Acc *);
s32 func_0010d0c0(Acc *p) {
    s32 i;
    f32 sum, lim;
    func_0010cf38(p);
    lim = p->b;
    if (p->a <= lim) return p->n;
    sum = 0.0f;
    for (i = 0; i < p->n; i++) {
        sum += p->e[i].v;
        if (lim <= sum) return i + 1;
    }
    return 1;
}

extern u8 D_0048CF20[];
extern u8 D_004D6B10[];

void *func_0010fc98(void) {
    void *p = func_001559f0(52, 12);
    s32 n = func_001205f0(D_0048CF20, p);
    return memcpy(D_004D6B10, p, n);
}

/* Read the little-endian s16 after buf[*pos], advancing *pos by 2. */
s16 func_0010d438(s32 *pos, u8 *buf) {
    s32 i = *pos;
    s32 lo = buf[++i];
    s32 hi = buf[++i];
    *pos = i;
    return lo + (hi << 8);
}
s32 func_0010eb78(u8 *s) {
    s32 cnt = 0, run = 1, i = 0;
    u8 c;
    do {
        c = s[i];
        if (c < 32) {
            if (c < 9) {
                if (c == 0) run = 0;
                else if (c == 4) run = 0;
            } else if (c == 15) {
                i++;
                if (s[i] == 1) cnt++;
            } else {
                i++;
            }
        }
        i++;
    } while (run);
    return cnt;
}
void func_0010f5f8(void) {
    sceGsSyncPath(0, 0);
    *(volatile u64 *)0x12000000 = 0xff03;
    *(volatile u64 *)0x12000070 = 0x11b0;
    *(volatile u64 *)0x12000080 = 0x0007f9ff020d227cUL;
}
extern f32 D_002BBDEC;
extern volatile s32 D_004D90F0;
void func_0010fea0(void) {
    if (D_002BBDEC == 1.0f) D_004D90F0 = 0x14996c4;
    else D_004D90F0 = 0x112a84e;
}
typedef struct {
    u64 q[2];
    u32 w16;
    u32 pad;
    u64 q3[2];
} DispEnv;
extern DispEnv D_004D8EC0; /* src/data/bss_004D.c: s32 D_004D8EC0[0xc] */
extern s32 D_004D90FC;
void sceGsDefDispEnv(DispEnv *, s16, s16, s16, s16, s16);
void func_00265980(DispEnv *);
void func_0010fee8(s32 w, s32 h) {
    D_004D90FC = 0;
    sceGsDefDispEnv(&D_004D8EC0, 1, w, h, 0, 0);
    D_004D8EC0.w16 &= ~0x1ff;
    FlushCache(0);
    sceGsSyncPath(0, 0);
    func_00265980(&D_004D8EC0);
}
extern u64 D_002BC918;
extern u8 D_002BC980[];
void func_0010fee8(s32, s32);
void func_0010ff60(s32 a) {
    D_002BC918 = (u64)a | ((u64)a << 8) | ((u64)a << 16) | ((u64)1 << 31) | ((u64)1 << 32);
    func_00106b18(D_002BC980);
    func_0010fee8(512, 447);
}
void func_00265350(s32, s32, s32, s32);
void func_0010ffe0(void) {
    func_00265350(1, 1, 2, 0);
    *(volatile u64 *)0x120000d0 = 0;
    func_00265980(&D_004D8EC0);
}
extern f32 D_002BBDEC;

/* Object at *D_002BCB60. */

typedef struct {
    u8 pad[0x30];
    s32 w[8];
    u8 pad2[0x10];
} Slot60;

typedef struct {
    Slot60 e[2];
    void *owner;
} SlotObj;

/* Header with self-relative offsets at +0x84 and +0x94. */
typedef struct {
    u8 pad[0x80];
    s32 h[8];
} SlotHdr;
extern s32 D_00351BD0;
void func_00108b60(SlotHdr *h, SlotObj *o) {
    o->e[D_00351BD0].w[0] = h->h[0];
    o->e[D_00351BD0].w[1] = h->h[1] + (s32)h;
    o->e[D_00351BD0].w[2] = h->h[2];
    o->e[D_00351BD0].w[3] = h->h[3];
    o->e[D_00351BD0].w[4] = h->h[4];
    o->e[D_00351BD0].w[5] = h->h[5] + (s32)h;
    o->e[D_00351BD0].w[6] = h->h[6];
    o->e[D_00351BD0].w[7] = h->h[7];
    o->owner = h;
}
/* Same object as *D_002BCB60 above, seen as rows of 4 floats. */

extern s32 D_004D925C, D_004D9250, D_002BCC1C, D_004D9254;
extern s32 D_002BCC1C, D_004D9260, D_002BCC20, D_004D9274, D_004D9280;
#include "vm/script_vm.h"
#include "data/types/text_00100000_h2_p2.h"

/* Saved copies of the three D_002E26A0 objects' positions. */
f32 D_004D92F0[3][4] ALIGNED(16);

/* These three only match with func_001130a0 defined above them. */
typedef struct {
    u8 pad[0xc0];
    void *owner;
    u8 pad2[0xc];
} Obj_D0;
typedef struct {
    u8 pad[0x90];
} Obj_90;
extern Obj_D0 D_00494D80[]; /* src/data/bss_0049.c: ED0 D_00494D80[0x2] */
extern Obj_90 D_00494F20[]; /* src/data/bss_0049.c: E90 D_00494F20[0x2][2] */
void func_00108a60(s32, void *, Obj_D0 *, Obj_90 *, Obj_90 *);
void func_001089f8(Obj_D0 *, void *);
void func_001089d0(void *);
void func_00108cf8(void *p, s32 i, void *q) {
    D_00494D80[i].owner = p;
    func_00108a60(i, q, &D_00494D80[i], &D_00494F20[i], &D_00494F20[i + 2]);
    func_001089f8(&D_00494D80[i], p);
    func_001089d0(p);
}

/* The 0xd0-byte object of func_00108b60/func_00108cf8 (two 0x60 slots,
 * owner at +0xc0), seen as rows of s32. */
typedef struct {
    s32 v[2][24];
} SlotRows;

#include "data/pieces/D_0048C6F0.h"

void func_00108970(SlotRows *a, s32 i, s32 j) {
    a->v[i][0] = D_0048C6F0[j].v[0];
    a->v[i][1] = D_0048C6F0[j].v[1];
    a->v[i][2] = D_0048C6F0[j].v[2];
    a->v[i][3] = D_0048C6F0[j].v[3];
}
#include "data/bss_0049_mixed.h"
#include "data/data_002B.h"
#include "data/data_0035.h"
#include "data/data_0048.h"
#include "data/pieces/D_002BC170.h"
#include "data/pieces/D_002BC1B0.h"
#include "data/pieces/D_002BBDEC.h"
#include "data/pieces/D_002BCC1C.h"
