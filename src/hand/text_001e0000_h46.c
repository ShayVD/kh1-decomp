#include "common.h"
#include "data/bss_0064.h"

/* Script VM (sp at +0x180, value stack at +0x184). */
typedef struct {
    s32 x0;
    void *obj;
    f32 v08[3];
    f32 f14;
    f32 f18;
    f32 f1c;
    f32 f20;
    u8 pad24[0x15c];
    s32 sp;
    s32 stk[92];
} VM;

/* Save data block returned by func_00232cc0(1) (same layout as h21's Sv). */
typedef struct {
    u8 pad0[0x34c];
    s32 a34c[7];
    s32 a368[0x5a][4];
    u8 pad[0xad1 - 0x368 - 0x5a * 16];
    u8 name[10];
    u8 pad2[8];
    u8 fl[0x20];
    u8 fl2[0x11];
    s32 tbl[32][5];
    u32 w[11];
    u8 fl3[4];
    u32 dc4;
    u8 fl5[4];
    s32 dcc;
    s32 dd0;
    u32 dd4;
} Sv;
/* Flag word at +0xad0 of the same block. */
typedef struct { u8 pad[0xad0]; u32 ad0; } SvA;
Sv *func_00232cc0(s32);

/* Party member (0x74 bytes) in the save block at D_00304BE8. */
typedef struct {
    u8 pad0[0x18];
    u8 n18;
    u8 a19[8];
    u8 n21;
    u8 a22[0x10];
    u8 b32;
    u8 pad33[0x74 - 0x33];
} Mem74;
typedef struct {
    u8 pad0[4];
    Mem74 m[10];
    u8 x48c;
    u8 x48d;
    u8 x48e[3];
    u8 x491;
} SaveM;
extern SaveM *D_00304BE8;

/* Text layout: control codes < 0x15 index a length table, 0x15-0x1f are
 * two-byte codes, >= 0x20 one byte. */
typedef struct { u8 pad[0x10]; s32 o10; s32 o14; } MsgHdr;
typedef struct { u16 code; u8 pad2[4]; u8 w; u8 pad7; } Glyph;

typedef struct Nd {
    u8 pad0[0xc];
    struct Nd *x0c;
    struct Nd *x10;
    u8 pad14[0x8c - 0x14];
    s32 x8c;
} Nd;

typedef struct {
    u8 pad0[0xce];
    s16 ce;
    s16 d0;
    s16 d2;
    u8 pad_d4[8];
    u8 dc[1];
} Fade;

/* Pad state: x8 = trigger, x10 = repeat. */
typedef struct { u8 pad0[8]; s32 x8; s32 xc; s32 x10; } Pad8;
extern Pad8 *D_00425BC8;
typedef struct { u8 pad0[0x24]; s32 cur[1]; } Menu24;

typedef struct { u8 pad0[0xd8]; s16 d8; } Obj203;
typedef struct { u8 pad0[0x94]; f32 f94; } Obj207;
typedef struct { u8 pad0[0xbe]; s16 be; s16 c0; s16 c2; s16 c4; s16 c6; } Obj207a;
typedef struct { s32 a; s32 pad[3]; s32 x10; } E20;

typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    u8 padc[0xa0 - 0xc];
    f32 fa0, fa4, fa8;
    u32 ac;
    s32 pad_b0;
    s32 b4;
    s16 pad_b8;
    s16 ba;
} Txt;
typedef struct { u8 pad0[0x70]; u32 x70; u8 pad74[0x14]; s32 x88; } Win46;

extern s32 D_00635640[][8]; /* src/data/bss_0063.c: s32 D_00635640[1024][8] */
extern s32 D_003E3CB0;
extern char D_00490928[];
extern s32 D_00633640; /* src/data/bss_0063.c: u32 D_00633640[2048] */
extern u8 D_003E3C88[];
#include "data/pieces/D_003E3D68.h"
#include "data/pieces/D_003E3D6C.h"
typedef struct { u8 b[0xe4]; } E228;
extern E228 D_003E3D70[];
extern u8 D_003E8D28[];
extern Glyph *D_003E8E28;
extern u8 D_003F2270[];
extern s32 D_0063F74C;
extern s32 D_003F1A60;
extern s32 D_00640DE0;
extern s32 D_00640DE4;
extern s32 D_00640DE8;
extern s32 D_00640DEC;
extern s32 D_00640DF0;
extern s32 D_00640DF4;
extern s32 D_00640DF8;
extern f32 D_002BBDFC;
extern s32 D_003F2F10[];
extern E20 D_003F2C40[];

int printf(const char *, ...);
int sceSifCallRpc(void *, u32, u32, void *, s32, void *, s32, void *, void *);
s32 sceGsSyncPath(s32, u16);
f32 sinf(f32);
u64 *func_0011fb38(s32, u64, u64 *);
u64 *func_00122048(u32, u32);
void func_001220b8(void *);
void func_00141b10(s32, void *);
s32 func_001ee768(s32);
s32 func_001efb88(void);
u8 *func_001efbb8(s32);
u8 *func_001efc10(s32);
u8 *func_001efc68(u8 *, u8 *, s32);
s32 func_001eff50(s32);
u64 *func_001f12c0(u64 *, s32, s32, s32, s32, s32, s32);
u64 *func_001f15f0(u64 *, s32, s32, s32, s32, s32, s32);
u64 *func_001f1868(u64 *, s32, s32, s32, s32, s32, s32);
u64 *func_001f18e8(u64 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_001f3680(Nd *);
void func_001f3698(Nd *, s32);
void func_001f4778(Win46 *);
void func_001f4d10(Win46 *);
void func_001f52a8(Win46 *);
void func_001f52e8(Win46 *);
void func_001f54f8(Win46 *);
void func_001f5988(Win46 *);
s32 func_001f94f0(void *, s32, s32, s32, u8 *, s32, s32);
void func_001f9e48(s32, s32, s32, s32, s32, s32, s32);
void func_001fa8b0(s32, s32, s32, s32, s32, s32);
void func_001fade0(s32, s32, s32, s32, s32, s32);
void func_001fb248(s32, s32, s32, s32, s32, s32);
void func_001fb408(s32, s32, s32, s32, s32, s32, s32, s32);
void func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_001fc308(Obj207 *, s32, s32, s32, s32, s32, s32, u32, u32);
s32 func_001fd538(void *);
s32 func_001fd658(void *);
void func_002016b0(void *, s32, s32, s32);
void func_00201988(void *, s32, s32, s32);
void func_00201c60(void *, s32, s32, s32);
void func_00203028(Obj203 *, s32, s32, s32, s32);
void func_002053e8(Obj207 *, s32, s32, s32, s32, u32);
void func_002078f0(Obj207a *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);

u8 *func_001efcd8(MsgHdr *h, s32 a, s32 n);
u8 *func_001efd20(u8 *p, s32 n);
s32 func_001efea8(s32 id);
s32 func_001efec8(u8 *a, u8 *b, s32 i);
s32 func_001efee8(u8 *p);
void func_001fb2b8(s32 a, s32 x, s32 y, s32 d, s32 e, s32 c, s32 sc);
void func_001fb3c0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
void func_001fd708(void);
void func_001fd720(s32 m);
s32 func_001f45e0(Txt *t);
s32 func_001f4650(Txt *t);
void func_001f4658(Txt *t, s32 v);
void func_001f4660(Txt *t);
s32 func_001f4668(Txt *t);
void func_001f4670(Txt *t, s32 v);
void func_001f4678(Txt *t);
f32 func_001f4680(Txt *t);
void func_001f4688(Txt *t, f32 v);
f32 func_001f4690(Txt *t);
void func_001f4698(Txt *t, f32 v);
f32 func_001f46a0(Txt *t);
void func_001f46a8(Txt *t, f32 v);

void func_001ebca0(s32 n, s32 on) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    Sv *v = func_00232cc0(1);
    if (on) v->fl3[q] |= 1 << s;
    else v->fl3[q] &= ~(1 << s);
}

s32 func_001ec0d8(VM *vm) {
    SvA *v = (SvA *)func_00232cc0(1);
    switch (vm->stk[vm->sp]) {
    case 0: v->ad0 |= 1; break;
    case 1: v->ad0 |= 2; break;
    case 2: v->ad0 |= 4; break;
    case 3: v->ad0 |= 8; break;
    }
    vm->sp--;
    return 2;
}

s32 func_001ec1a0(VM *vm) {
    SvA *v = (SvA *)func_00232cc0(1);
    switch (vm->stk[vm->sp]) {
    case 0: vm->stk[vm->sp] = (u8)v->ad0 & 1; break;
    case 1: vm->stk[vm->sp] = (v->ad0 >> 1) & 1; break;
    case 2: vm->stk[vm->sp] = (v->ad0 >> 2) & 1; break;
    case 3: vm->stk[vm->sp] = (v->ad0 >> 3) & 1; break;
    }
    return 2;
}

void func_001ed000(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h) {
    s32 *pn = &D_003E3CB0;
    s32 n = *pn;
    D_00635640[n][0] = a;
    D_00635640[n][1] = b;
    D_00635640[n][2] = c;
    D_00635640[n][3] = d;
    D_00635640[n][4] = e;
    D_00635640[n][5] = f;
    D_00635640[n][6] = g;
    D_00635640[n][7] = h;
    *pn = n + 1;
    if (n + 1 >= 1024) {
        *pn = 0;
        printf(D_00490928);
    }
}

s32 func_001edba0(void) {
    s32 i, j;
    if (D_00635640[0][0] != -1) {
        sceSifCallRpc(D_003E3C88, 30, 0, D_00635640, 0x2000, D_00635640, 0x2000, 0, 0);
        D_003E3CB0 = 0;
        for (i = 0; i < 1024; i++) {
            for (j = 7; j >= 0; j--) D_00635640[i][j] = -1;
        }
    }
    return D_00633640;
}

s32 func_001ef140(s32 i, s32 id) {
    s32 c = 0;
    Mem74 *m = &D_00304BE8->m[i];
    s32 t = func_001ee768(id);
    s32 j, n;
    if (t == 0) {
        n = m->n21;
        for (j = 0; j < n; j++) {
            if (m->a22[j] == id) c++;
        }
    } else if (t == 1) {
        n = m->n18;
        for (j = 0; j < n; j++) {
            if (m->a19[j] == id) c++;
        }
    } else if (t >= 2 && t < 12) {
        c = m->b32 == id;
    }
    return c;
}

void func_001ef830(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if (D_00304BE8->x48e[i] == 0xff) break;
    }
    D_003E3D6C = i;
    D_003E3D68 = i;
    if (D_00304BE8->x491 != 0xff) D_003E3D68 = i + 1;
    for (i = 0; i < 10; i++) func_00141b10(i, &D_003E3D70[i]);
}

u8 *func_001efcd8(MsgHdr *h, s32 a, s32 n) {
    u8 *t = (u8 *)h + h->o14;
    return func_001efd20(func_001efc68((u8 *)h + h->o10, t, a), n);
}

u8 *func_001efd20(u8 *p, s32 n) {
    if (n == 0) return p;
    for (;;) {
        if (*p < 21) {
            switch (*p) {
            case 0:
                return p;
            case 16:
                p++;
                if (--n == 0) return p;
                break;
            default:
                p += D_003E8D28[*p];
                break;
            }
        } else {
            p = (*p < 32) ? p + 2 : p + 1;
        }
    }
}

s32 func_001efdb8(u8 *p) {
    s32 n = 0;
    for (;;) {
        if (*p < 21) {
            switch (*p) {
case 0:
 return n;
case 2:
 p++;
 n++;
 break;
case 16:
 return n;
case 3:
 p += 2;
 n++;
 break;
default:
 p += D_003E8D28[*p];
 break;

            }
        } else {
            p = (*p < 32) ? p + 2 : p + 1;
        }
    }
}

s32 func_001efea8(s32 id) {
    return func_001efee8(func_001efbb8(id));
}

s32 func_001efec8(u8 *a, u8 *b, s32 i) {
    return func_001efee8(func_001efc68(a, b, i));
}

s32 func_001efee8(u8 *p) {
    s32 n = 1;
    for (;;) {
        if (*p < 21) {
            switch (*p) {
            case 0:
                return n;
            case 16:
                p++;
                n++;
                break;
            default:
                p += D_003E8D28[*p];
                break;
            }
        } else {
            p = (*p < 32) ? p + 2 : p + 1;
        }
    }
}

s32 func_001f0340(u8 *p, s32 scale) {
    s32 d = 18;
    s32 x = 0;
    for (;;) {
        s32 c = *p;
        s32 k;
        if (c == 0 || c == 10) return x >> 4;
        k = c | (p[1] << 8);
        p += 2;
        if (k == 0x4081) {
            x += (scale << 8) / d;
        } else {
            Glyph *g = &D_003E8E28[func_001eff50(k)];
            x += ((g->w << 4) + func_001efb88()) * scale / d;
        }
    }
}

s32 func_001f2a50(s32 a, s32 b, s32 c, s32 d, s32 e) {
    u64 *buf;
    void *u;
    func_00266f38(func_00266c08(2), D_003F2270);
    buf = func_00122048(0x1000, 0x80);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    buf[0] = ((s32)((u8 *)func_001f12c0(buf + 2, 1, a, b, c, d, e) - (u8 *)buf) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
    return D_0063F74C;
}

s32 func_001f2b58(s32 a, s32 b, s32 c, s32 d, s32 e) {
    u64 *buf;
    void *u;
    func_00266f38(func_00266c08(2), D_003F2270);
    buf = func_00122048(0x400, 0x80);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    buf[0] = ((s32)((u8 *)func_001f15f0(buf + 2, 1, a, b, c, d, e) - (u8 *)buf) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
    return D_0063F74C;
}

s32 func_001f2c60(s32 a, s32 b, s32 c, s32 d, s32 e) {
    u64 *buf;
    void *u;
    func_00266f38(func_00266c08(2), D_003F2270);
    buf = func_00122048(0x400, 0x80);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    buf[0] = ((s32)((u8 *)func_001f1868(buf + 2, 1, a, b, c, d, e) - (u8 *)buf) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
    return D_0063F74C;
}

s32 func_001f2d68(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h) {
    u64 *buf;
    void *u;
    u64 *p;
    func_00266f38(func_00266c08(2), D_003F2270);
    p = func_00122048(0x400, 0x80);
    buf = p;
    p += 2;
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    buf[0] = ((s32)((u8 *)func_001f18e8(p, 1, a, b, c, d, e, f, g, h) - (u8 *)buf) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
    return D_0063F74C;
}

s32 func_001f3978(Nd *n, s32 skip, s32 cnt) {
    s32 i;
    if (n == 0) return -1;
    for (i = 0; i < skip && n->x0c; i++) n = n->x0c;
    i = i + cnt + 1;
    do {
        if (i <= 0) return 0;
        switch (n->x8c) {
        case 0:
        case 4:
        case 5:
            break;
        default:
            func_001f3680(n);
            break;
        }
        n = n->x10;
        i--;
    } while (n);
    return 0;
}

s32 func_001f3a30(Nd *n, s32 skip, s32 cnt, s32 arg) {
    s32 i;
    if (n == 0) return -1;
    for (i = 0; i < skip && n->x0c; i++) n = n->x0c;
    i = i + cnt + 1;
    do {
        if (i <= 0) return 0;
        switch (n->x8c) {
        case 0:
        case 4:
        case 5:
            break;
        default:
            func_001f3698(n, arg);
            break;
        }
        n = n->x10;
        i--;
    } while (n);
    return 0;
}

void func_001f8f30(void) {
    void *u;
    u64 *p = func_00122048(0x400, 0x80);
    u64 *buf = p;
    p += 2;
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p[0] = 0x1000000000008001;
    p[1] = 0xe;
    buf[0] = ((s32)((u8 *)func_0011fb38(0x40, 0x017F000001FF0000, p + 2) - (u8 *)buf) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}

s32 func_001f9438(void *a, s32 b, s32 c, s32 d, s32 id, s32 f, s32 g) {
    if (id == 0) return c;
    return func_001f94f0(a, b, c, d, func_001efbb8(id), f, g);
}

void func_001fa5b0(s32 a, s32 b, s32 x, s32 y, s32 e, s32 f, s32 c, s32 sc) {
    func_001f9e48(a, b, x - 1, y - 1, e, f, sc);
    func_001f9e48(a, b, x + 1, y - 1, e, f, sc);
    func_001f9e48(a, b, x - 1, y + 1, e, f, sc);
    func_001f9e48(a, b, x + 1, y + 1, e, f, sc);
    func_001f9e48(a, b, x, y, e, f, c);
}

void func_001facd8(s32 a, s32 x, s32 y, s32 d, s32 e, s32 c, s32 sc) {
    func_001fa8b0(a, x - 1, y - 1, d, e, sc);
    func_001fa8b0(a, x + 1, y - 1, d, e, sc);
    func_001fa8b0(a, x - 1, y + 1, d, e, sc);
    func_001fa8b0(a, x + 1, y + 1, d, e, sc);
    func_001fa8b0(a, x, y, d, e, c);
}

void func_001fb140(s32 a, s32 x, s32 y, s32 d, s32 e, s32 c, s32 sc) {
    func_001fade0(a, x - 1, y - 1, d, e, sc);
    func_001fade0(a, x + 1, y - 1, d, e, sc);
    func_001fade0(a, x - 1, y + 1, d, e, sc);
    func_001fade0(a, x + 1, y + 1, d, e, sc);
    func_001fade0(a, x, y, d, e, c);
}

void func_001fb2b8(s32 a, s32 x, s32 y, s32 d, s32 e, s32 c, s32 sc) {
    func_001fb248(a, x - 1, y - 1, d, e, sc);
    func_001fb248(a, x + 1, y - 1, d, e, sc);
    func_001fb248(a, x - 1, y + 1, d, e, sc);
    func_001fb248(a, x + 1, y + 1, d, e, sc);
    func_001fb248(a, x, y, d, e, c);
}

void func_001fb3c0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g) {
    func_001fb408(a, b, c, d, e, f, g, D_003F1A60);
}

void func_001fd708(void) {
    func_001fd720(0);
}

void func_001fd720(s32 m) {
    switch (m) {
    case 0:
        D_00640DE0 = m;
        D_00640DE4 = 0x10000010;
        D_00640DE8 = 0x40000040;
        D_00640DEC = 0x50000050;
        D_00640DF0 = 0x80000080;
        D_00640DF4 = 0x20000020;
        D_00640DF8 = 0xA00000A0;
        break;
    case 1:
        D_00640DE0 = m;
        D_00640DE4 = 0x10;
        D_00640DE8 = 0x40;
        D_00640DEC = 0x50;
        D_00640DF0 = 0x80;
        D_00640DF4 = 0x20;
        D_00640DF8 = 0xA0;
        break;
    case 2:
        D_00640DE0 = m;
        D_00640DE4 = 0x10000000;
        D_00640DE8 = 0x40000000;
        D_00640DEC = 0x50000000;
        D_00640DF0 = 0x80000000;
        D_00640DF4 = 0x20000000;
        D_00640DF8 = 0xA0000000;
        break;
    }
}

void func_001fe408(Fade *o) {
    s32 i;
    s32 n1 = o->ce + 1;
    s32 cnt = (o->d0 & 0xf) ? n1 : o->ce;
    s32 k = (o->d0 >> 4) % n1;
    s32 sel = o->d2 >> 4;
    for (i = 0; i < cnt; i++) {
        u8 *p = &o->dc[k];
        if (i == sel) {
            *p = 0x80;
        } else {
            s32 d = D_002BBDFC * 4.0f;
            if (d + 64 >= *p) *p = 64;
            else *p -= d;
        }
        k = (k + 1) % n1;
    }
}

s32 func_001fe660(Menu24 *m, s32 i, s32 n) {
    s32 r = 0;
    if (D_00425BC8->x10 & 0x10000010) {
        if (m->cur[i] > 0) {
            m->cur[i]--;
            r = 1;
        } else if (D_00425BC8->x8 & 0x10000010) {
            m->cur[i] = n - 1;
            r = 1;
        }
    } else if (D_00425BC8->x10 & 0x40000040) {
        if (m->cur[i] < n - 1) {
            m->cur[i]++;
            r = 1;
        } else if (D_00425BC8->x8 & 0x40000040) {
            m->cur[i] = 0;
            r = 1;
        }
    }
    return r;
}

s32 func_001fe7a8(Menu24 *m, s32 i, s32 n) {
    s32 r = 0;
    if (D_00425BC8->x10 & 0x80000080) {
        if (m->cur[i] > 0) {
            m->cur[i]--;
            r = 1;
        } else if (D_00425BC8->x8 & 0x80000080) {
            m->cur[i] = n - 1;
            r = 1;
        }
    } else if (D_00425BC8->x10 & 0x20000020) {
        if (m->cur[i] < n - 1) {
            m->cur[i]++;
            r = 1;
        } else if (D_00425BC8->x8 & 0x20000020) {
            m->cur[i] = 0;
            r = 1;
        }
    }
    return r;
}

s32 func_001fe8f0(Menu24 *m, s32 i, s32 n) {
    s32 r = 0;
    if (D_00425BC8->x10 & 0x80000480) {
        if (m->cur[i] > 0) {
            m->cur[i]--;
            r = 1;
        } else if (D_00425BC8->x8 & 0x80000480) {
            m->cur[i] = n - 1;
            r = 1;
        }
    } else if (D_00425BC8->x10 & 0x20000820) {
        if (m->cur[i] < n - 1) {
            m->cur[i]++;
            r = 1;
        } else if (D_00425BC8->x8 & 0x20000820) {
            m->cur[i] = 0;
            r = 1;
        }
    }
    return r;
}

void func_00203788(Obj203 *o, s32 x0, s32 y, s32 x1, s32 c) {
    s32 mid;
    if (o->d8 < 2) return;
    func_00203028(o, x0, y, x1, c);
    y--;
    mid = x0 + (x1 - x0 + 9) / 2;
    func_001fb428(o, 1, 0, 0, mid - 7, y, func_001fd538(o) + 1, 15, c);
    func_001f94f0(o, 0, mid - 7, y, func_001efc10(84), 15, c);
    func_001fb428(o, 0, 0, 0, mid + 6, y, func_001fd658(o), 15, c);
}

void func_00207428(Obj207 *o, s32 x, s32 y) {
    s32 t = o->f94;
    u32 a = (u32)(sinf((f32)(t % 64) * 0.015625f * 3.1415928f) * 128.0f) << 24;
    u32 c1 = a | 0x1e9696;
    u32 c2 = a | 0xffffff;
    u32 c3 = a | 0x0a1e1e;
    func_002053e8(o, x + 2, y + 2, 26, 8, c2);
    func_001fc308(o, x, y, 0, 0, 62, 0, c1, c3);
}

void func_00207a38(Obj207a *o) {
    s32 i;
    s32 w = o->c2 >> 4;
    s32 h = w - (o->c6 >> 4);
    s32 x = o->be >> 4;
    s32 y = o->c0 >> 4;
    s32 half = h / 2;
    s32 sel = func_001fd538(o);
    for (i = 0; i < 2; i++) {
        func_002078f0(o, i == sel, 2, 2, x, y, h, x + half, D_003F2F10[i]);
        x += w;
    }
}

void func_00207d60(void *o, s32 i, s32 b, s32 y, s32 x, s32 p, s32 h) {
    E20 *e = &D_003F2C40[i];
    func_002016b0(o, b, y + 2, e->a);
    func_001fb428(o, 1, 2, 0, x, y + (26 - h) / 2, p, h, e->x10);
}

void func_00207ec0(void *o, s32 i, s32 b, s32 y, s32 x, s32 p, s32 h) {
    E20 *e = &D_003F2C40[i];
    func_00201988(o, b, y + 3, e->a);
    func_001fb428(o, 1, 4, 0, x, y + (26 - h) / 2, p, h, e->x10);
}

void func_00208020(void *o, s32 i, s32 b, s32 y, s32 x, s32 p, s32 h) {
    E20 *e = &D_003F2C40[i];
    func_00201c60(o, b, y + 2, e->a);
    func_001fb428(o, 1, 2, 0, x, y + (26 - h) / 2, p, h, e->x10);
}

void func_002080e0(void *o, s32 i, s32 x, s32 y, s32 n) {
    E20 *e;
    if (n < 2) return;
    e = &D_003F2C40[i];
    func_002016b0(o, x, y + 2, e->a);
    y += 7;
    func_001f9438(o, 0, x + 5, y, 85, 12, e->x10);
    func_001fb428(o, 1, 2, 0, x + 37, y, n, 12, e->x10);
}

void func_002081b0(void *o, s32 i, s32 x, s32 y, s32 n) {
    E20 *e;
    if (n < 2) return;
    e = &D_003F2C40[i];
    func_00201988(o, x, y + 3, e->a);
    y += 7;
    func_001f9438(o, 0, x + 5, y, 85, 12, e->x10);
    func_001fb428(o, 1, 3, 0, x + 51, y, n, 12, e->x10);
}

/* needs make: uses rodata (switch jump tables) */
s32 func_001f45e0(Txt *t) {
    switch (t->ac) {
    case 0:
    case 3:
    case 4:
    default:
        return t->b4 + t->ba / 2;
    case 1:
    case 5:
    case 6:
        return t->b4;
    case 2:
    case 7:
    case 8:
        return t->b4 + t->ba - 16;
    }
}

s32 func_001f4650(Txt *t) { return t->x8; }

void func_001f4658(Txt *t, s32 v) { t->x8 = v; }

void func_001f4660(Txt *t) { t->x8 = 0; }

s32 func_001f4668(Txt *t) { return t->x0; }

void func_001f4670(Txt *t, s32 v) { t->x0 = v; }

void func_001f4678(Txt *t) { t->x0 = 0; }

f32 func_001f4680(Txt *t) { return t->fa0; }

void func_001f4688(Txt *t, f32 v) { t->fa0 = v; }

f32 func_001f4690(Txt *t) { return t->fa4; }

void func_001f4698(Txt *t, f32 v) { t->fa4 = v; }

f32 func_001f46a0(Txt *t) { return t->fa8; }

void func_001f46a8(Txt *t, f32 v) { t->fa8 = v; }

void func_001f46b0(Win46 *w) {
    if (!(w->x88 & 1)) return;
    switch (w->x70) {
    case 0:
        break;
    case 1:
        func_001f4778(w);
        if (w->x88 & 2) {
            func_001f54f8(w);
            return;
        }
        break;
    case 2:
        func_001f4d10(w);
        if (w->x88 & 2) {
            func_001f5988(w);
            return;
        }
        break;
    case 3:
        func_001f52e8(w);
        return;
    case 4:
        func_001f52a8(w);
        break;
    }
}

/* func_001fe5a0 only matches with func_001fe558 defined above it. */
typedef struct { u8 pad0[0xbc]; s16 bc; u8 padbe[0x12]; u64 d0; } Fade2;

s32 func_001fe558(Fade2 *o) {
    return (o->d0 & 0xffffffff00000000) != 0;
}

s32 func_001fe5a0(Fade2 *o) {
    switch (o->bc) {
    case 0:
        if (D_00425BC8->x8 & 0x2000) {
            if (func_001fe558(o)) o->bc++;
            else o->bc = 2;
        }
        break;
    case 1:
        if (!func_001fe558(o)) o->bc++;
        break;
    case 2:
        break;
    }
    if (o->bc == 2) { o->bc = 0; return 1; }
    return 0;
}
#include "data/bss_0064_mixed.h"
#include "data/data_003E.h"
#include "data/data_003F.h"
#include "data/data_0049.h"
#include "data/pieces/D_002BBDFC.h"
