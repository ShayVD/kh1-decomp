#include "common.h"

/* Hand-matched functions 0x0012b7a8-0x0012fcd0 (session 6, worker 05). Nostrict region. */

/* ---- shared types ---- */

/* 0x730-byte pool node (D_004F8310[64]). */
typedef struct Node {
    union {
        u64 flags;
        struct { s32 w0; s32 f4; } w;
    };
    s32 f8;
    s32 *cur;
    s32 *f10;
    u8 pad014[0xc];
    s32 l20[0x100];
    s32 l420[0xc0];
    struct Node *next;
    s16 h724[6];
} Node;

/* 0x38-byte menu cursor block (D_002E2FD8[7]); D_002E3170 is a stack of them. */
typedef struct Q8 { s32 f0, f4; u32 f8; s32 fc; s32 n; u8 ids[0x20]; s32 f34; } Q8;

/* Menu item (func_001478c8 result). */
typedef struct O8 { u16 f0; u8 p2[4]; u8 f6; s8 f7; s8 f8; s8 f9; s8 fa; s8 fb; u16 f0c; u16 f0e; } O8;

typedef struct T23 { u8 b0; u8 pad[19]; } T23;
typedef struct Info { u8 pad[4]; u32 f4; u8 pad8[0x57]; u8 f5f; } Info;
typedef struct Info2 { u8 pad[7]; u8 f7; u8 pad8[0x14]; T23 *f1c; } Info2;
typedef struct Ent {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0x24];
    struct Ent *f98;
    u8 pad9c[0x130 - 0x9c];
    Info *f130;
    Info2 *f134;
    u8 pad138[0x164 - 0x138];
    s32 f164;
    u8 pad168[4];
    f32 f16c;
    u8 pad170[0x370 - 0x170];
    u64 f370;
    u8 pad378[0x3ac - 0x378];
    u32 f3ac;
    u8 pad3b0[0x440 - 0x3b0];
    u64 f440;
} Ent;

typedef struct V8 { Ent *a; s32 b; } V8;
typedef struct Hit { s32 f0; Ent *e; } Hit;
typedef struct Sv { u8 pad[0x844]; s32 f844[3]; u8 pad850[0x24]; s32 f874; } Sv;
typedef struct S88 { u32 f0; u8 pad[28]; } S88;

/* ---- data ---- */
extern Node D_004F8310[64];
extern Q8 D_002E2FD8[7];
extern Q8 *D_002E3170[8];
extern Q8 **D_00524F40;
extern O8 *D_002E319C;
extern O8 *D_002E31A0;
extern Ent *D_002E26A0;
extern s32 D_002E31A8;
extern s32 D_002E31B8;
extern V8 D_002E31B0;
extern s32 D_002E31BC;
extern Sv *D_00304BE8;
extern u32 D_00524F44;
extern s32 D_00524F48;
extern s32 D_00524F4C;
extern void (*D_00524F74)(void);
extern f32 D_00524F78;
extern u32 D_002C5958;
extern f32 D_002BBDFC;
extern u32 D_002C5BB8;
extern S88 D_00350D88[];
extern s32 D_0052528C;
extern V8 D_00524F80[];
extern V8 *D_00525288;
extern f32 D_002E2780[];

/* ---- functions ---- */
extern void func_0012cb40(Q8 *, s32, u8);
extern void func_0012fc58(void);
extern s32 func_00137330(Ent *, Ent *, s32);
extern Hit *func_00122048(s32, s32);
extern s32 func_0012cf48(Ent *, Hit *);
extern void func_001220b8(Hit *);
extern void func_00245238(s32, Ent *);
extern void func_0012fb20(V8 *, s32);
extern void func_00158960(void);
extern s32 func_00130030(Ent *);
extern s32 func_001443a8(Ent *);
extern s32 func_0013db30(Ent *);
extern s32 func_0012e4b0(void);
extern void func_0012e970(void);
extern s32 func_0011ef38(void *);
extern void func_0011ef10(s32, void *);
extern void func_001315c0(Ent *, s32, f32 *, f32);
extern s32 func_0012ee70(Ent *, s32);
extern Ent *func_001230a0(Ent *);
extern s32 func_00123368(Ent *);
extern f32 func_0012ed88(Ent *, V8 *, f32 *, f32 *);
extern f32 func_00121b38(f32 *, f32 *);
extern s32 func_0012f0f8(f32 *, f32 *, s32);
extern s32 func_0012eaf8(Ent *);
extern f32 func_0012ec60(Ent *, s32, f32 *);
extern f32 func_00120bf8(f32 *);
extern void func_00267530(f32 *, f32 *, f32 *);
extern s32 func_00219288(void);
extern void func_0017eff8(void);
extern void func_0012fc20(void);
extern void func_00123030(Ent *, s32, s32);
extern float fabsf(float);

Node *func_0012b7a8(s32 a);

void func_0012ca38(void);

s32 func_0012cc38(s32 i, s32 v);

void func_0012ccb0(s32 i);

void func_0012d930(u32 *a0);

s32 func_0012dd70(O8 *o);

typedef struct { u32 w; s32 f4; s32 f8; } St3190;
typedef struct { u32 x0; u32 x4; u32 x8; } Pad;
extern St3190 D_002E3190;
extern s32 D_002E3168;
extern Pad D_002C5BB0;
extern u32 D_002C5960;
extern s32 D_002E27A8;
extern s32 D_00524F50;
extern void *memset(void *, s32, u32);
extern s32 func_00122ff8(Ent *);
extern void func_0012dc70(void);
extern s32 func_001375d8(Ent *);
extern s32 func_0012e1b0(Pad *);
extern O8 *func_001478c8(s32);
extern s32 func_0012dea0(Q8 *, s32);
extern void func_0012e120(void);
extern void func_0012f700(Pad *);
extern void func_0011d768(s32);
extern void func_0012dce0(Q8 *);
extern Q8 *func_0012dd38(void);
s32 func_0012e1b0(Pad *pad);

s32 func_0012e4b0(void);

void func_0012ea38(void);

s32 func_00122ff8(Ent *o);

s32 func_0012f040(Ent *o, s32 i);

/* func_0012f218 (src/hand/nostrict_nofill/text_00120000_h54.c). */
typedef union { u64 x; struct { u32 lo0; u32 x32:3; u32 f35:1; u32 x36:1; u32 kind:2; u32 hi:25; } b; } F370b;
typedef struct { u8 pad[0x370]; F370b f370; } E9;
s32 func_0012f218(f32 *pos, V8 *a, s32 lim);

/* func_0012ee70 (src/hand/text_00120000_h31.c). */
s32 func_0012ee70(Ent *e, s32 i);

void func_0012f3d0(V8 *out);

void func_0012f868(V8 *out);

/* func_0012eb08, func_0012fa98 (src/hand/text_00120000_h5.c), func_0012fc58 (src/auto). */
s32 func_0012eb08(V8 *p);

void func_0012fa98(void);

void func_0012fc58(void);

/* rodata: jump tables at 0x48d550, 0x48d570 */
s32 func_0012fcd0(void);

typedef struct Ob {
    u8 pad[6];
    u8 f6;
    u8 pad7[0x160 - 7];
    u32 b0:1;
    u32 b1:1;
    u32 b2:30;
    s32 f164;
    s32 f168;
    f32 f16c;
    u8 pad170[8];
    s32 f178;
    u8 pad17c[0x1d4 - 0x17c];
    s32 *f1d4;
    u64 pad1d8;
} Ob;
extern s32 func_00130190(Ob *);
extern s32 func_00167698(s32);
extern s32 func_00130270(Ob *, s32);
extern s32 func_001302d0(Ob *, s32, f32, f32);

void func_00130398(Ob *o, s32 a1, f32 t);


typedef f32 C01Mat[4][4];
typedef struct { u32 b0 : 1; u32 r : 31; } C01B32;
typedef struct { u8 pad[0x4c]; u16 x4c; } C01Sub130;
typedef struct {
    u32 flags0;
    u8 pad004[0x10 - 0x4];
    f32 x10[4];
    u8 pad020[0x50 - 0x20];
    f32 x50[4];
    u8 pad060[0xd0 - 0x60];
    C01Mat xd0;
    u8 pad110[0x130 - 0x110];
    C01Sub130 *x130;
    u8 pad134[0x15c - 0x134];
    s32 x15c;
    u32 b0 : 1;
    u32 b1 : 1;
    u32 b2 : 1;
    u32 b3 : 1;
    u32 b4 : 1;
    u32 b5 : 1;
    u32 b6 : 1;
    u32 b7 : 1;
    u32 b8 : 1;
    u32 b9 : 1;
    u32 b10 : 1;
    u32 b11 : 1;
    u32 rest : 20;
    s32 x164;
    s32 x168;
    f32 f16c;
    f32 f170;
    f32 f174;
    s32 x178;
    u8 pad17c[0x180 - 0x17c];
    f32 f180;
    u8 pad184[0x1cc - 0x184];
    s32 x1cc;
    u8 pad1d0[4];
    s32 *x1d4;
    u8 pad1d8[0x1f0 - 0x1d8];
    u8 x1f0[0x10];
    f32 x200[4];
    f32 x210[4];
    u8 pad220[0x230 - 0x220];
    C01Mat x230;
    f32 x270[4];
    f32 f280;
    f32 f284;
    f32 f288;
    f32 f28c;
    f32 f290;
} __attribute__((aligned(8))) C01Obj3;

extern void *D_002E31E8;
extern f32 D_002C58A0[4];

void sceVu0CopyMatrix(C01Mat, C01Mat);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_002672f8(f32 *, C01Mat, f32 *);
s32 func_0012ffd0(C01Obj3 *);
void func_00167688(s32, s32, void *);
void func_00130898(C01Obj3 *, C01Mat);
s32 func_00130e48(C01Obj3 *, C01Mat);
void func_00130c28(C01Obj3 *, f32, f32);
void func_00130660(C01Obj3 *, C01Mat, s32, f32, f32);
void func_00130210(C01Obj3 *, s32);
void func_00130598(C01Obj3 *, C01Mat, f32, f32);
void func_001655e0(C01Mat, s32, f32, s32);
s32 func_00167680(s32);
void func_001752a0(s32, void *);
void func_001676b0(s32, f32 *);
void func_00167d70(s32, f32);

typedef struct {
    u8 pad0[0x50];
    f32 x50[4];
    u8 pad60[0x15c - 0x60];
    s32 x15c;
    u64 flags;
    s32 x168;
    f32 f16c;
    f32 f170;
    f32 f174;
    u8 pad178[0x1d4 - 0x178];
    s32 *x1d4;
    u8 pad1d8[0x220 - 0x1d8];
    f32 x220[4];
    C01Mat x230;
    f32 x270[4];
    f32 f280;
    f32 f284;
} __attribute__((aligned(8))) O660;
void func_00166248(C01Mat, s32, s32);
void func_00165cf8(C01Mat, s32, f32, s32);
void func_001676d8(s32, f32 *);
void func_002673f8(C01Mat, C01Mat);
void func_001675c0(s32);
s32 func_00167698(s32);
void func_00130648(C01Obj3 *);

/* func_00130660: closest draft (7 words off: f20/f21 swapped), context for func_00130f18. */
void func_00130660(C01Obj3 *a, C01Mat m, s32 idx, f32 d, f32 e) {
    O660 *o = (O660 *)a;
    f32 v[4];
    C01Mat t;
    f32 k = D_002BBDFC * o->f284;
    s32 s = o->x1d4[idx];
    if (((s32)(o->flags >> 1) & 1) && k < e) {
        if (0.0f < o->f170) {
            func_00166248(m, o->x15c, s);
        } else {
            sceVu0CopyMatrix(t, m);
            if ((s32)(o->flags >> 12) & 1) {
                func_002675a8(t[3], o->x50);
                t[3][3] = 1.0f;
            }
            func_00165cf8(t, o->x15c, d, s);
        }
        func_001676d8(o->x15c, v);
        v[3] = 0;
        func_002673f8(t, m);
        func_002672f8(o->x270, t, v);
        o->x270[3] = 0;
        o->f170 = e;
        o->f174 = k;
        func_002675a8(v, o->x220);
        v[3] = 0;
        func_002672f8(v, o->x230, v);
        func_00267518(m[3], m[3], v);
        func_00130598(a, m, k / e, 1.0f - k / e);
    } else {
        { f32 c = o->f170;
        k = 0.0f;
        if (k < c) func_001675c0(o->x15c); }
        o->f170 = k;
        func_001655e0(m, o->x15c, d, s);
        o->f280 = func_00167698(s);
        if (!((s32)(o->flags >> 6) & 1)) func_00130648(a);
    }
    if (s) o->flags |= 2;
    o->x168 = idx;
    o->f16c = d;
}

void func_00130f18(C01Obj3 *o, f32 dt);

typedef struct { f32 x, y, z, w; } V4D;
typedef struct { u8 p0[0xc]; u32 fc; u8 p10[0x28 - 0x10]; s32 f28; } PD;
typedef struct { u8 p0[0x10]; V4D f10; } XD;
typedef struct {
    u32 b0:12;
    u32 k:2;
    u32 b14:9;
    u32 b23:1;
    u32 b24:8;
    s32 f4;
    s32 f8;
    u8 pc[4];
    V4D f10;
    u8 p20[0x30 - 0x20];
    union { u64 d; struct { u32 f30; XD *f34; } s; } u30;
    u8 p38[0x5c - 0x38];
    PD *f5c;
} AD;
typedef struct { u8 p0[5]; u8 f5; u8 p6[0x14 - 6]; f32 *f14; } ID;
typedef struct QD {
    u32 used:1;
    u32 b1:1;
    u32 k:2;
    u32 b4:28;
    s32 f4;
    union { struct { s32 f8; u32 fc; } w; struct { u32 lo; u32 c0:5; u32 c5:7; u32 n:4; u32 c16:16; } b; u64 d; } u8;
    V4D f10;
    s32 f20;
    s32 seq;
    u32 mask;
    PD *f2c;
    struct QD *next;
    s32 f34;
    s32 f38;
    u8 p3c[4];
} QD;
typedef struct {
    u8 p0[0x10];
    V4D f10;
    u8 p20[0x30 - 0x20];
    V4D f30;
    u8 p40[0x88 - 0x40];
    u32 f88;
    u8 p8c[0x134 - 0x8c];
    ID *f134;
    u8 p138[0x370 - 0x138];
    u64 f370;
    u8 p378[0x3e0 - 0x378];
    u32 mask;
    u8 p3e4[0x3ec - 0x3e4];
    QD *head;
} BD;
typedef struct GD { u8 p0[0x88]; u32 f88; } GD;
extern QD D_005267C0[];
extern QD D_005277C0[];
extern QD D_005297C0;
extern s32 D_00350CE0;
extern QD *func_00134f80(QD *, s32);
extern void func_00135000(BD *, QD *);
extern f32 func_00176850(void);
extern s32 func_00176578(s32, s32, s32, s32);
extern s32 func_00134ba8(AD *, BD *, u32 *);
extern void func_00121fc4(V4D *, V4D *);
QD *func_001350d8(AD *a, u32 mask, BD *b);

typedef struct { u64 f0; u8 p8[8]; f32 f10[2]; f32 f18; } E39;
typedef struct { u8 p0[0x20]; f32 f20[3]; f32 f2c; f32 f30[4]; u8 p40[0x88-0x40]; u32 f88; u8 p8c[0x150-0x8c]; f32 f150; u8 p154[0x3e4-0x154]; f32 f3e4; u8 p3e8[2]; u16 f3ea; } O39;
extern s32 func_0014f600(O39 *);
extern s32 func_00130040(O39 *, s32);
extern void func_00139170(O39 *, E39 *);
extern f32 func_00267390(f32 *, f32 *);
extern s32 func_00130340(O39 *, s32, f32);
extern void *func_00130578(O39 *, s32, f32);
extern f32 atan2f(f32, f32);
extern void func_00137688(O39 *, f32);
extern void func_00138a20(O39 *, f32, f32 *);
void func_00139240(O39 *o, E39 *e, s32 k, f32 a, f32 b, f32 c);
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"
