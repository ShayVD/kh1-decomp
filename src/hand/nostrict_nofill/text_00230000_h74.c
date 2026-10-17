/* 0x00230000-0x0024FFFF game code by hand (batch 74). */
#include "common.h"

typedef struct Pk { struct Pk *next; s32 type; } Pk;
typedef struct { Pk *head; s32 pad; } Bk;
typedef struct { s32 bits; Bk *tbl; } Ht;
s32 *func_002378c8(Pk *, s32 *, s32);
s32 *func_00237790(Pk *, s32 *, s32);
s32 *func_00237d48(Pk *, s32 *, s32);
s32 *func_00237ec0(Pk *, s32 *, s32);
s32 *func_00266c08(s32);
void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
void func_00266f38(s32 *, s32 *);

void func_00237f20(Ht *h, s32 *b0, s32 *b1, s32 a3, s32 a4) {
    s32 *buf = b0;
    s32 n = 1 << h->bits;
    Bk *bk = h->tbl;
    s32 *r, *q;
    Pk *p;
    s32 i;
    for (i = 0; i < n; i++, bk++) {
        if (bk->head != 0) {
            p = bk->head;
            do {
                r = buf;
                if (p->type == 2) r = func_002378c8(p, buf, a4);
                else if (p->type == 1) r = func_00237790(p, buf, a4);
                else if (p->type == 3) r = func_00237d48(p, buf, a4);
                else if (p->type == 4) r = func_00237ec0(p, buf, 0);
                if (r != buf) {
                    *r |= 0x70000000;
                    q = func_00266c08(2);
                    *q |= 0x40;
                    FlushCache(0);
                    sceGsSyncPath(0, 0);
                    func_00266f38(q, buf);
                    buf = (buf == b0) ? b1 : b0;
                }
                if (p->next == 0) break;
                p = p->next;
            } while (p != 0);
        }
    }
    sceGsSyncPath(0, 0);
}

typedef struct { s32 x, y, z, w; } I4b;
typedef struct { u8 pad[0x60]; s32 c[4][4]; I4b p[4]; } Spr6;
extern Spr6 D_00648900;
extern s32 D_006488F0;
extern f32 D_00650DD0;
extern f32 D_00650DD4;
void func_0024aa48(void *, Spr6 *, void *);
s32 func_002388b8(Spr6 *, s32, s32);

void func_00239630(void *a0, void *a1, s32 dx, s32 dy, f32 s) {
    s32 i, j;
    s32 *q;
    func_0024aa48(a0, &D_00648900, a1);
    for (i = 0; i < 4; i++) {
        q = &D_00648900.p[i].y;
        q[-1] += dx * 16;
        q[0] += dy * 16;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            D_00648900.c[i][j] = D_00648900.c[i][j] * s;
        }
    }
    for (i = 0; i < 4; i++) {
        D_00648900.c[i][3] = D_00648900.c[i][3] * D_00650DD4;
    }
    D_006488F0 = func_002388b8(&D_00648900, 1, D_006488F0);
}

void func_00239860(void *a0, void *a1, s32 dx, s32 dy, f32 s, s32 scale, s32 *src, s32 all) {
    s32 i, j;
    s32 *q;
    func_0024aa48(a0, &D_00648900, a1);
    for (i = 0; i < 4; i++) {
        q = &D_00648900.p[i].y;
        q[-1] += dx * 16;
        q[0] += dy * 16;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (all || j != 3) D_00648900.c[i][j] = src[j];
            if (scale) D_00648900.c[i][j] = D_00648900.c[i][j] * s;
        }
    }
    for (i = 0; i < 4; i++) {
        D_00648900.c[i][3] = D_00648900.c[i][3] * D_00650DD4;
    }
    D_006488F0 = func_002388b8(&D_00648900, 1, D_006488F0);
}

void func_00239b90(void *a0, void *a1, s32 dx, s32 dy, f32 s, s32 scale, s32 (*src)[4], s32 all) {
    s32 i, j;
    s32 *q;
    func_0024aa48(a0, &D_00648900, a1);
    for (i = 0; i < 4; i++) {
        q = &D_00648900.p[i].y;
        q[-1] += dx * 16;
        q[0] += dy * 16;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (all || j != 3) D_00648900.c[i][j] = src[i][j];
            if (scale) D_00648900.c[i][j] = D_00648900.c[i][j] * s;
        }
    }
    for (i = 0; i < 4; i++) {
        D_00648900.c[i][3] = D_00648900.c[i][3] * D_00650DD4;
    }
    D_006488F0 = func_002388b8(&D_00648900, 1, D_006488F0);
}

typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0-0x68]; u64 unkE0; } Q;
extern Q D_00648630;
extern u8 D_00351E10[];
extern u8 *D_006488F4;
typedef struct { u8 pad[0x1C4]; s32 unk1C4; } Obj1C4;
void func_002370c8(void *);
void func_00237018(void *, s32, s32);
void func_0023bb98(s32, s32, s32, s32, Obj1C4 *, s32, s32, f32);
void func_00239e30(s32, s32, s32, s32, Obj1C4 *, s32, s32, f32);

void func_0023a318(s32 a0, s32 a1, s32 a2, s32 a3, Obj1C4 *o, s32 a5, s32 a6, f32 f) {
    func_002370c8(&D_00648630);
    D_00648630.unkE0 = 5;
    D_00648630.unk60 = 0x30003;
    func_00237018(&D_00648630, 0x16, 1);
    D_006488F4 = D_00351E10;
    *(u8 **)&D_006488F0 = D_00351E10 + 0x10;
    if (a0 == 0 && o->unk1C4 == 0) {
        func_0023bb98(0, a1, a2, a3, o, a5, a6, f);
    } else {
        func_00239e30(a0, a1, a2, a3, o, a5, a6, f);
    }
    if (f != 0.0f) {
        func_00237018(D_006488F4, (*(u8 **)&D_006488F0 - D_006488F4) >> 4, 1);
    }
}

typedef struct { s32 unk0; u32 unk4; u8 pad8[0xC]; u8 unk14[3]; } Btn;
extern u8 D_0064FD60[];
extern u8 D_00426820[];
extern u8 D_004267F0[];
void func_0024ac08(void *, s32 *);
void func_00239558(s32, s32, s32, s32);

void func_0023a490(s32 a0, Btn *b, s32 x, s32 y, f32 f) {
    s32 pos[2];
    s32 i, k;
    u8 *p;
    D_00650DD4 = D_00650DD0 = f;
    func_00239630(D_0064FD60, D_00426820, x, y, 1.0f);
    func_00239630(D_0064FD60 + 192, D_004267F0, x, y, 1.0f);
    func_00239630(D_0064FD60 + 384, D_004267F0, x, y, 1.0f);
    func_00239630(D_0064FD60 + 576, D_004267F0, x, y, 1.0f);
    func_00239630(D_0064FD60 + 768, D_004267F0, x, y, 1.0f);
    func_0024ac08(D_0064FD60, pos);
    for (k = 20, i = 0, p = b->unk14; i < 3; i++) {
        func_00239558(*p, x + pos[0], y + k + pos[1], (b->unk4 & (1 << i)) ? 115 : 230);
        p++;
        k += 22;
    }
}

