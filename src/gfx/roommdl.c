/* The room's models (a guess at the name), 0x00114880-0x00114f18:
 * func_001148c8 loads the model sets D_002A6C60 ... (func_00108a60),
 * func_00114a38 sets up an object's six matrices, and func_00114c18 /
 * func_00114db0 / func_00114e50 build the draw packets of the 64 collision
 * objects (D_004D9420, D_004DBC20) that src/coll/mapcoll.c's func_00114f50
 * uses. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004D.h"
#include "data/pieces/D_002B6778.h"
#include "data/pieces/D_002BBDE0.h"
#include "m2c.h"
#include "data/pieces/D_002A6C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002B1C60.h"
#include "data/bss_004E.h"
#include "data/types/text_00110000_h3.h"
#include "data/types/text_00110000_h3_p.h"
#include "vm/script_vm.h"
#include "data/pieces/D_002BD118.h"
#include "data/pieces/D_002BBFA0.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002BBDF0.h"
#include "data/pieces/D_002BBDF4.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/types/text_00110000_h52.h"
#include "data/pieces/D_002BBF20.h"
#include "data/pieces/D_002BBEE0.h"
#include "data/pieces/D_002BBEA0.h"
#include "data/pieces/D_002BBE60.h"
#include "data/pieces/D_002BBE20.h"
#include "data/pieces/D_002BBF60.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_002BC070.h"
#include "data/types/text_00110000_h52_p.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
#include "data/types/text_00110000_h29_p.h"
#include "data/pieces/D_002A6208.h"
#include "data/types/text_00110000_h29_p3.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002BBD48.h"
#include "data/types/text_00110000_h29.h"
#include "data/pieces/D_002BCCA0.h"
#include "data/pieces/D_002BCDA0.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/pieces/D_002BCCE0.h"

/* func_00114880 (from hand/text_00110000_s6_02.c). */
extern s32 D_002BD110;
CONTEXT_ONLY void func_00113a48(void) {}
void func_00114880(void) {
    if (D_002BBDE0 == 3) { if (D_002BD110) do { func_00113a48(); } while (0); }
}

/* func_001148c8 (from auto/text_00110000_13.c). */
M2C_UNK func_00108a60(s32, M2C_UNK, void *, void *, void *);
extern M2C_UNK D_002AD460;
void func_001148c8(void) {
    s32 temp_a0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    void *temp_a2;

    D_004D936C = 0;
    D_004D9370 = 0;
    var_s0 = 0;
    var_s1 = 0;
    var_s2 = 0;
    do {
        func_00108a60(var_s1, 1, var_s2 + (s8 *)&D_002A6C60, var_s0 + (s8 *)&D_002AD460, var_s0 + ((s8 *)&D_002AD460 + 0x2400));
        temp_a0 = var_s1;
        temp_a2 = var_s2 + (s8 *)&D_002AA060;
        func_00108a60(temp_a0, 5, temp_a2, var_s0 + (s8 *)&D_002B1C60, var_s0 + ((s8 *)&D_002B1C60 + 0x2400));
        var_s2 += 0xD0;
        var_s1 += 1;
        var_s0 += 0x90;
    } while (var_s1 < 0x40);
}

/* func_001149b0 (from hand/text_00110000_h3.c). */
typedef struct {
    s32 n;
    s32 x4[5];
    s32 off; /* byte offset of the payload from the header */
} RelHdr;
void func_001089d0(void *);
void func_001149b0(RelHdr *a) {
    s32 *p = &a->off;
    RelHdr **pp = &a;
    if ((*pp)->n >= 2) func_001089d0((u8 *)a + *p);
}

/* func_001149e8 (from hand/text_00110000_h3.c). */
void func_00108fd0(s32, s32, s32, void *, s32);
s32 func_001149e8(s32 a0, u8 *a1, s32 a2, s32 a3) {
    void *p = a1 + *(s32 *)(a1 + 0x20);
    func_00108fd0(D_004D9370++, a2, a0, p, a3);
    return 1;
}

/* func_00114a38 (from hand/text_00110000_s6_02.c). */
typedef struct { u8 *data; s32 *hdr; s32 pad8[2]; f32 m[4][4]; f32 pad50[3][4]; f32 v[8][4]; } Obj110;
typedef struct { u8 pad[0x18]; s32 ofs; } Hdr;
Obj110 *D_004D9368 ALIGNED(8);
extern u8 D_002BD140[];
Obj110 *func_00122048(s32, s32);
s32 func_0024edf0(f32 (*)[4], f32 (*)[4]);
void func_00106bd8(void *, s32);
void func_00108df8(s32, s32, s32, u8 *, s32);
void func_001220b8(Obj110 *);
s32 func_00114a38(s32 a, Hdr *h, s32 id, s32 d) {
    s32 r;
    Obj110 *o;
    o = func_00122048(272, 128);
    D_004D9368 = o;
    o->hdr = &h->ofs;
    o->data = (u8 *)h + h->ofs;
    r = 0;
    PlatVu0ApplyMatrix(o->v[0], a, o->data);
    PlatVu0ApplyMatrix(D_004D9368->v[1], a, D_004D9368->data + 16);
    PlatVu0ApplyMatrix(D_004D9368->v[2], a, D_004D9368->data + 32);
    PlatVu0ApplyMatrix(D_004D9368->v[3], a, D_004D9368->data + 48);
    PlatVu0ApplyMatrix(D_004D9368->v[4], a, D_004D9368->data + 64);
    PlatVu0ApplyMatrix(D_004D9368->v[5], a, D_004D9368->data + 80);
    PlatVu0ApplyMatrix(D_004D9368->v[6], a, D_004D9368->data + 96);
    PlatVu0ApplyMatrix(D_004D9368->v[7], a, D_004D9368->data + 112);
    PlatVu0MulMatrix(D_004D9368->m, D_002BBFA0, (*(f32 (*)[4][4])&D_0029B280));
    if (func_0024edf0(D_004D9368->m, (f32 (*)[4])D_004D9368->v) == 0) {
        if (id == 40000) func_00106bd8(D_002BD140, 40000);
        func_00108df8(D_004D936C++, id, a, D_004D9368->data, d);
        r = 1;
    }
    func_001220b8(D_004D9368);
    return r;
}

/* func_00114c00 (from auto/text_00110000.c). */
void func_00114c00(void) {
    D_004D936C = 0;
    D_004D9370 = 0;
}

/* func_00114c18 (from hand/text_00110000_h52.c). */
typedef struct { V4i52 a; s32 x10; void *x14; s32 x18; s32 x1c; V4i52 x20; V4i52 x30; V4i52 x40; } Ent52;
typedef struct { u8 b[0x90]; } E90_52;
extern V4i52 D_00472150;
extern V4i52 D_00486300;
extern E90_52 D_004DBC20[2][64];
void func_00114c18(Ent52 *o, s32 idx, s32 col) {
    s32 i;
    if (idx == -1) {
        o[0].x14 = D_0048C630.x14;
        o[1].x14 = D_0048C690.x14;
    } else {
        o[0].x14 = &D_004DBC20[0][idx];
        o[1].x14 = &D_004DBC20[1][idx];
    }
    o[0].x10 = D_0048C630.x10;
    o[0].x18 = D_0048C630.x18;
    o[0].x1c = D_0048C630.x1c;
    o[1].x10 = D_0048C690.x10;
    o[1].x18 = D_0048C690.x18;
    o[1].x1c = D_0048C690.x1c;
    o[0].x20.v[0] = D_0048C630.x20.v[0];
    o[0].x20.v[1] = D_0048C630.x20.v[1];
    o[0].x20.v[2] = D_0048C630.x20.v[2];
    o[0].x20.v[3] = D_0048C630.x20.v[3];
    o[1].x20.v[0] = D_0048C690.x20.v[0];
    o[1].x20.v[1] = D_0048C690.x20.v[1];
    o[1].x20.v[2] = D_0048C690.x20.v[2];
    o[1].x20.v[3] = D_0048C690.x20.v[3];
    for (i = 0; i < 2; i++) {
        o[i].a.v[0] = D_0048C6F0[col].v[0];
        o[i].a.v[1] = D_0048C6F0[col].v[1];
        o[i].a.v[2] = D_0048C6F0[col].v[2];
        o[i].a.v[3] = D_0048C6F0[col].v[3];
        o[i].x40.v[0] = D_00472150.v[0];
        o[i].x40.v[1] = D_00472150.v[1];
        o[i].x40.v[2] = D_00472150.v[2];
        o[i].x40.v[3] = D_00472150.v[3];
        o[i].x30.v[0] = D_00486300.v[0];
        o[i].x30.v[1] = D_00486300.v[1];
        o[i].x30.v[2] = D_00486300.v[2];
        o[i].x30.v[3] = D_00486300.v[3];
    }
}

/* func_00114db0 (from hand/text_00110000_h3.c). */
extern s32 D_004DBC28[][64][36];
extern s32 D_00351BD0;
extern s32 D_002BC170[4][4];
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

/* func_00114e50 (from hand/text_00110000_h29.c). */
typedef struct { s32 a, b; } W29P8;
typedef struct { W29P8 p; u8 pad[0x88]; } W29Cell;
extern const W29P8 D_0048BFD0;
typedef struct { u8 b[0x50]; } W29E50;
W29E50 D_004D9380[2] ALIGNED(64);
W29E50 D_004D9420[0x40][2] ALIGNED(32);
extern W29Cell D_004DBC20_00114e50[2][64] __asm__("D_004DBC20");
#define D_004DBC20 D_004DBC20_00114e50
#define func_00114c18 ((void (*)(void *, s32, s32)) func_00114c18)
void func_00114e50(void) {
    s32 i, j;
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 2; j++) {
            D_004DBC20[j][i].p.a = D_0048BFD0.a;
            D_004DBC20[j][i].p.b = D_0048BFD0.b;
        }
    }
    func_00114c18(D_004D9380, -1, 2);
    for (j = 0; j < 64; j++) func_00114c18(&D_004D9420[j], j, 2);
}
#undef D_004DBC20
#undef func_00114c18

