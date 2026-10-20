/* Hand-matched functions in 0x00114000-0x0011e000 (worker h3). Grouped by
 * address; the original translation units are not known yet. */
#include "common.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"

typedef int u128 __attribute__((mode(TI)));

/* Quadword copy through $6, the way the SDK's sceVu0CopyVector-style inline
 * asm does it (lq/sq plus trailing nops; the delay slot after it stays empty). */
static inline void CopyQword(void *dst, void *src) {
    __asm__ volatile("lq $6, 0(%1)\nsq $6, 0(%0)\nnop\nnop" : : "r"(dst), "r"(src) : "$6");
}

/* ---- externs ---- */
extern void *D_002BD250[];
extern s32 D_002C12C4;
extern s32 D_004D9370;
extern s32 D_002BBE0C;
extern s32 D_002C1304;

/* Entry with a 4-bit kind in the high nibble of its first byte. */
typedef struct {
    u32 lo : 4;
    u32 kind : 4;
} KindBits;

typedef struct {
    u8 pad0[0x18];
    u16 x18;
    u8 pad1a[2];
    s32 x1c;
    s32 x20;
    s32 x24;
    void *x28;
} Obj178;

/* Stack record filled before func_00118378 (0x40 bytes). */
typedef struct {
    f32 v[4];
    s32 x10;
    f32 x14;
    s32 x18;
    u8 pad1c[8];
    f32 x24;
    u8 pad28[8];
    s16 x30;
    u8 pad32[14];
} Query40;

/* 20-byte record (ten halfwords) pointed to by the D_004E2450 table. */
typedef struct {
    u16 v[10];
} Rec20;
typedef struct {
    s16 v[10];
} Rec20s;

/* 64-byte table at D_004E2430; the asm names +0x20 as D_004E2450 and +0x28
 * as D_004E2458. */
typedef struct {
    u128 *x0;
    u128 *x4;
    Rec20 *x8;
    u8 pad[52];
} Ent2450;
extern Ent2450 D_004E2450[];
typedef struct {
    Rec20 *x0;
    u8 pad[60];
} Ent2458;
extern Ent2458 D_004E2458[];

/* Sound-slot table: D_004E344C entries of 24 bytes at *D_004E3450. */
#include "data/types/text_00110000_h3.h"
extern s32 D_004E344C;
extern SndSlot *D_004E3450;
extern SndSlot D_004E3458[];
extern Slot12 *D_004E3454;
extern void (*D_004E3430)(void);
extern s32 D_004E2430[64][16];
extern s32 D_002A3F50[];
extern s32 D_002A3F44;
extern u8 D_002BCAF0[];
extern s32 D_002BC128;

/* Strings in .rodata, referenced through their data symbols so the copies
 * stay block moves without emitting new rodata: "%3d", "amusic/music",
 * ".dat", "amusic/se". */
typedef struct {
    char c[13];
} Str13;
typedef struct {
    char c[10];
} Str10;
extern char D_0048D110[];
extern Str13 D_0048D118;
extern char D_0048D128[];
extern Str10 D_0048D130;

int sprintf(char *, const char *, ...);
char *strcat(char *, const char *);
void func_00112270(s32, char *);
s32 func_001ecfd8(void);
void func_0011cf88(s32, s32, s32, s32, s32, SndSlot *, s32);
void func_0011c838(s32, s32, s32, s32, s32);
void func_0011c850(s32, s32, s32);
void func_0011c868(s32, s32, s32, s32, s32);
void func_0011c880(s32, s32, s32, s32, s32);
void func_0011d028(s32, s32);
void func_001ed320(s32, s32, s32, s32);
s32 func_001ecb08(s32, s32, s32);
void func_0011d240(s32, s32, void *, s32);
void func_0011db50(s32 *, s32 *);

typedef struct {
    s32 n;
    s32 x4[5];
    s32 off; /* byte offset of the payload from the header */
} RelHdr;
extern s32 D_004DBC28[][64][36];
extern s32 D_00351BD0;
extern s32 D_002BC170[4][4];
void func_001089d0(void *);

void func_00104f10(void *, void *);
void func_00104eb0(void *, void *);
void func_001047c8(void);
void func_00104528(void);
void func_00108fd0(s32, s32, s32, void *, s32);
s32 func_00115200(void *, void *, void *, void *, void *);
s32 func_001152c8(void *, s32, s32, s32);
void func_00116368(void *, s32);
void func_00118378(void *, s32, s32, s32);
s32 func_001191c8(void *, void *, s32);
void func_001195d8(void *, void *);
s32 func_001198c8(s32, void *, void *);
void func_0011a978(s32, s32, u128 *);
void func_0011b108(void *, s32);
void func_002675a8(void *, void *);
void func_00114820(void);
void func_0017f678(void);
void func_0022eb00(s32);
void func_0011e518(void);
void func_0011ef10(s32, void *);
void func_0011c698(void);
void func_0011d688(s32);

/* Taking &a (an ADDRESSOF that gcc later folds away) is what keeps the
 * original from turning the call into a sibcall. */
void func_001149b0(RelHdr *a) {
    s32 *p = &a->off;
    RelHdr **pp = &a;
    if ((*pp)->n >= 2) func_001089d0((u8 *)a + *p);
}

s32 func_001149e8(s32 a0, u8 *a1, s32 a2, s32 a3) {
    void *p = a1 + *(s32 *)(a1 + 0x20);
    func_00108fd0(D_004D9370++, a2, a0, p, a3);
    return 1;
}

void func_00114db0(s32 a0, s32 (*a1)[4]) {
    s32 i, j, k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            D_004DBC28[D_00351BD0][a0][k] = a1[i][j];
            D_004DBC28[D_00351BD0][a0][k + 16] = D_002BC170[i][j];
            k++;
        }
    }
}

void func_001150d8(u8 *a) {
    Query40 q;
    func_002675a8(&q, a + 64);
    q.v[1] = *(f32 *)(a + 68) - 500.0f;
    q.x10 = 0;
    q.x14 = 1000000.0f;
    q.x18 = 0;
    func_00118378(&q, 6, 1, -1);
    if (q.x30 != -1) {
        *(f32 *)(a + 52) = q.x24;
    }
}

void func_001156f0(void *a0, f32 *a1) {
    f32 *v = a1 + 4;
    func_00104f10(a0, v);
    a1[8] = -v[0];
    a1[9] = -a1[5];
    a1[10] = -a1[6];
    a1[11] = 1.0f;
}

/* Fill a 4-float vector with *b (inline asm block, ends in a nop). */
void func_001158a8(f32 *a, f32 *b) {
    __asm__ volatile("lwc1 $f0, 0(%1)\nswc1 $f0, 0(%0)\nswc1 $f0, 4(%0)\nswc1 $f0, 8(%0)\nswc1 $f0, 12(%0)\nnop\nnop"
                     : : "r"(a), "r"(b) : "$f0");
}

/* List filters: append a0 to D_002BD250 when the flags at *a1 match. */
void func_00115e90(void *a0, s32 *a1) {
    if (!(*a1 & 0x106)) D_002BD250[D_002C12C4++] = a0;
}

void func_00115ed0(void *a0, s32 *a1) {
    if ((*a1 & 0x406) == 0x400) D_002BD250[D_002C12C4++] = a0;
}

void func_00115f10(void *a0, s32 *a1) {
    if ((*a1 & 0xf6) == 0x20) D_002BD250[D_002C12C4++] = a0;
}

void func_00115f50(void *a0, s32 *a1) {
    if (!(*a1 & 0xe)) D_002BD250[D_002C12C4++] = a0;
}

void func_00115f90(void *a0, KindBits *a1) {
    if (a1->kind != 7 && a1->kind != 5) D_002BD250[D_002C12C4++] = a0;
}

void func_00115fd8(void *a0, s32 *a1) {
    if (!(*a1 & 0x10006)) D_002BD250[D_002C12C4++] = a0;
}

void func_00116020(void *a0, s32 *a1) {
    if ((*a1 & 0xf6) == 0x50) D_002BD250[D_002C12C4++] = a0;
}

void func_00116060(void *a0, KindBits *a1) {
    if (a1->kind != 7 && a1->kind != 9 && a1->kind != 5) D_002BD250[D_002C12C4++] = a0;
}

void func_001160b0(void *a0, KindBits *a1) {
    if (a1->kind == 9) D_002BD250[D_002C12C4++] = a0;
}

void func_001160f0(void *a0, u32 *a1) {
    if (!((*a1 >> 17) & 1)) D_002BD250[D_002C12C4++] = a0;
}

void func_001178d0(Obj178 *a) {
    s32 r = 0;
    a->x1c = 0;
    func_00116368(a, 1);
    if (a->x18 != 0) {
        a->x28 = D_002BD250;
        a->x24 = -1;
        a->x1c++;
        r = 1;
        a->x20 = a->x18;
    }
    func_0011b108(a, r);
}

s32 func_00117bb0(void *a0, s32 a1, s32 a2, void *a3) {
    if (func_001152c8(a0, a1, a2, (s32)a3) && func_001198c8(-1, a0, a3)) return 1;
    return 0;
}

s32 func_00119128(void *a0, void *a1, void *a2) {
    f32 c[4];
    f32 b[4];
    f32 a[4];
    func_00104eb0(a0, a);
    func_00104f10(a0, b);
    if (func_00115200(a1, a2, a, b, c) && func_001198c8(-1, a0, c)) return 1;
    return 0;
}

s32 func_00119788(void *a0) {
    u8 buf[32];
    s32 r;
    func_001047c8();
    func_001195d8(a0, buf);
    r = func_001191c8(buf, a0, 11);
    func_00104528();
    return r != -1 ? 1 : -1;
}

/* Clear word 12 of each of the 64 table entries. */
s32 func_0011a068(void) {
    s32 i;
    for (i = 0; i < 64; i++) D_004E2430[i][12] = 0;
    return 0;
}

s32 func_0011a7c0(s32 a0, s32 a1, u16 *a2) {
    Rec20 *t = D_004E2458[a0].x0;
    a2[0] = t[a1].v[0];
    a2[1] = t[a1].v[1];
    a2[2] = t[a1].v[2];
    a2[3] = t[a1].v[3];
    return a2[3] == 0xffff ? 3 : 4;
}

void func_0011a818(s32 *a0, s32 *a1, u16 *a2, s32 a3) {
    *a0 = ((Rec20s *)D_004E2458[a3].x0)[a2[0]].v[a2[1]];
    *a1 = ((Rec20s *)D_004E2458[a3].x0)[a2[0]].v[a2[2]];
}

void func_0011a978(s32 a0, s32 a1, u128 *a2) {
    Ent2450 *e = &D_004E2450[a0];
    CopyQword(a2, &e->x4[((s16 *)&e->x8[a1])[4]]);
}

void func_0011a9c8(s32 a0, s32 a1, u128 *a2) {
    Ent2450 *e = &D_004E2450[a0];
    CopyQword(a2, &e->x0[((s16 *)&e->x8[a1])[0]]);
}

void func_0011aac8(s32 a0, f32 *a1, s32 a2) {
    f32 *v = a1 + 4;
    func_0011a978(a2, a0, (u128 *)v);
    a1[8] = -v[0];
    a1[9] = -a1[5];
    a1[10] = -a1[6];
    a1[11] = 1.0f;
}

void func_0011c710(void) {
    D_002BBE0C = 0;
    D_002C1304 = 1;
    func_00114820();
    func_0017f678();
    func_0022eb00(0xffff);
    func_0011e518();
    func_0011ef10(30000, func_0011c698);
    func_0011d688(120);
}

void func_0011ca68(s32 a0, char *a1) {
    char buf[80];
    sprintf(buf, D_0048D110, a0);
    if (buf[0] == ' ') {
        buf[0] = '0';
        if (buf[1] == ' ') buf[1] = '0';
    }
    *(Str13 *)a1 = D_0048D118;
    strcat(a1, buf);
    strcat(a1, D_0048D128);
}

void func_0011cb08(char *a0) {
    char buf[16];
    *(Str10 *)a0 = D_0048D130;
    func_00112270(D_002BC128, buf);
    strcat(a0, buf);
    strcat(a0, D_0048D128);
}

s32 func_0011cba0(void) {
    if (func_001ecfd8()) return 0;
    if (D_004E3430) D_004E3430();
    return 4;
}

/* Claim the first inactive slot; the extra arguments pass straight through. */
SndSlot *func_0011cfa8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->active == 0) {
            func_0011cf88(a0, a1, a2, a3, t0, e, a0 < 1000 ? 2 : -1);
            return e;
        }
    }
    return 0;
}

void func_0011d028(s32 a0, s32 a1) {
    s32 i;
    Slot12 *p = D_004E3454;
    for (i = 0; i < D_004E344C; i++, p++) {
        if (!p->x0) goto found;
    }
found:
    p->x0 = a0;
    p->x4 = a1;
    p->x8 = 2;
}

void func_0011d080(s32 a0, s32 a1) {
    func_0011c838(a0 < 1000 ? 2 : -8, a0, a1, 0x3fff, 0x3fff);
    func_0011d028(a0, a1);
}

void func_0011d0d8(s32 a0, s32 a1) {
    func_0011c850(a0 < 1000 ? 2 : -8, a0, a1);
}

void func_0011d108(s32 a0, s32 a1, s32 a2) {
    func_0011c868(a0 < 1000 ? 2 : -8, a0, a1, -1, a2);
}

void func_0011d140(s32 a0, s32 a1) {
    func_0011c838(a0 < 1000 ? 2 : -1, a0, a1, 0x3fff, 0x3fff);
}

void func_0011d178(s32 a0, s32 a1) {
    func_0011c850(a0 < 1000 ? 2 : -1, a0, a1);
}

void func_0011d1a8(s32 a0, s32 a1, s32 a2) {
    func_0011c868(a0 < 1000 ? 2 : -1, a0, a1, -1, a2);
}

void func_0011d2d0(s32 a0, s32 a1, s32 a2) {
    s32 i;
    SndSlot *e = D_004E3458;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->id == a0 && e->x10 == a1) {
            func_001ed320(e->handle, a0, a1, a2);
            return;
        }
    }
}

void func_0011d588(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        func_0011d240(D_002A3F50[i], i, D_002BCAF0, 0x3fff);
    }
}

s32 func_0011d6f0(s32 a0, s32 a1) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->id == a0 && e->x10 == a1) return func_001ecb08(e->handle, a0, a1);
    }
    return 0;
}

void func_0011d790(s32 a0, s32 a1) {
    s32 v = 0x3fff;
    if (a1) v = 0x1fff;
    func_0011c880(2, a0, 0, v, v);
}

void func_0011dba0(s32 *a0, s32 *a1, s32 a2, s32 a3) {
    if (a3 == 2 && D_002A3F44) {
        *a0 = 0;
        *a1 = 0;
        return;
    }
    if (a2 == 0x3fff) {
        *a0 = a2;
        *a1 = a2;
        return;
    }
    *a0 += a2;
    *a1 += a2;
    func_0011db50(a0, a1);
}
#include "data/bss_004E_typed.h"
