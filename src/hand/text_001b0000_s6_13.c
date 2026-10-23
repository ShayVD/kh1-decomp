#include "common.h"
#include "data/types/vm_rec.h"
#include "data/bss_0062.h"

#include "data/pieces/D_0037A378.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11;
    u8 pad12[4];
    V4 v16;
    V4 v32;
    f32 f48;
    char name[32];
    u8 pad84[12];
} Out;
#include "data/types/text_001b0000_s6_13.h"
typedef struct { u8 pad[4]; u8 type; u8 pad5[2]; u8 b7; u8 pad8[5]; u8 b13; u8 pad14[10]; f32 f24; } ItemInfo;
extern CdEnt *D_006257D0; /* src/data/bss_0062.c: u8 *D_006257D0 */
extern CdEnt D_00621320, D_00622290;
extern Out D_00623E40[];
extern s32 D_00625640, D_00625648[], D_00623E30, D_00623228;
extern Ent D_00623230[];
void func_001bc900(CdEnt *, Out *);
s32 func_001ba3f0(s32);
void func_001ba060(CdEnt *, s32);
CdEnt *func_001ba9d8(s32);
ItemInfo *func_001bb658(s32);
s32 func_001bb740(void);
u8 func_001be5c8(s32);
u8 func_001be5d0(s32);
void func_001bd010(CdEnt *);
/* rodata */
void func_001bd470(void) {
    s32 i, k, n, t;
    ItemInfo *it;
    Ent *e = D_00623230;
    Out *o;
    Out *p = D_00623E40;
    s32 x;
    s32 buf[16];
    D_00625640 = 0;
    func_001bc900(D_006257D0, &p[0]);
    p[0].b8 = 1;
    k = 0;
    for (i = 71; i < 119; i++) {
        if (func_001ba3f0(i) > 0) {
            func_001ba060(&D_00621320, i - 71);
            func_001bc900(&D_00621320, &p[k + 1]);
            D_00625648[k] = i - 71;
            p[k + 1].b8 = 1;
            k++;
        }
    }
    D_00625640 = k;
    for (i = 0; i < 10; i++) {
        func_001bc900(func_001ba9d8(i), &p[k + 1 + i]);
        p[k + 1 + i].b8 = 0;
    }
    if (func_001ba3f0(70) > 0) D_00623E30 = k + 11;
    else if (func_001ba3f0(69) > 0) D_00623E30 = k + 6;
    else D_00623E30 = k + 2;
    it = func_001bb658(0);
    n = 0;
    o = &D_00623E40[1];
    for (i = 0; i < func_001bb740(); i++) {
        if (func_001ba3f0(i) <= 0) continue;
        e->b0 = func_001ba3f0(i);
        x = it[i].b7;
        e->b6 = i;
        { s32 a; a = (x & 3) + 1; x >>= 2; a *= (x & 3) + 1; x >>= 2; a *= (x & 3) + 1; e->b1 = a; }
        e->b2 = 0;
        e->b3 = 0;
        e->b4 = 0;
        e->b5 = it[i].type;
        e->b7 = func_001be5c8(i);
        e->b8 = func_001be5d0(i);
        if ((u32)(i - 71) < 48) {
            e->b2 = o->b6;
            e->b3 = o->b5;
            e->b4 = o->b11;
            o++;
        } else {
            switch (i) {
            case 58: e->b4 = 1; break;
            case 59: e->b4 = 2; break;
            case 61: e->b4 = 1; break;
            case 62: e->b4 = 2; break;
            case 60: case 63: e->b4 = 3; break;
            }
            if (it[i].type == 1) e->b2 = 4;
            else {
                t = it[i].f24;
                if (t <= 0) e->b2 = 0;
                else if (t < 10) e->b2 = 1;
                else if (t < 20) e->b2 = 2;
                else e->b2 = 3;
            }
            if (it[i].type == 2 || it[i].type == 6) {
                if (it[i].b13 < 100) e->b3 = 1;
                else if (it[i].b13 < 120) e->b3 = 2;
                else e->b3 = 3;
            }
        }
        e++;
        n++;
    }
    D_00623228 = n;
    func_001bd010(&D_00622290);
}

typedef struct { u16 used; u16 h2; u16 h4; u8 pad6[26]; void (*fn)(void); u8 pad36[12]; } Slot;
extern Slot *D_0037A16C;
CONTEXT_ONLY void func_001bfcd8(void) { D_0037A16C = 0; }
CONTEXT_ONLY void func_001bffa0(s32 i) {
    if (i >= 0) {
        if (D_0037A16C[i].fn) D_0037A16C[i].fn();
        D_0037A16C[i].used = 0;
        D_0037A16C[i].h2 = 0;
        D_0037A16C[i].h4 = 0;
    }
}
void func_001c0010(void) {
    s32 i;
    for (i = 1; i < 400; i++) {
        if (D_0037A16C[i].used != 0) func_001bffa0(i);
    }
    func_001bfcd8();
}

#include "data/pieces/D_003B4DA0.h"
#include "data/pieces/D_003A7990.h"
extern f32 D_002BBDFC;
#include "vm/script_vm.h"
typedef struct { u64 a, b, c, d; } MsgQ; extern s32 D_006297F0, D_006297F4; extern MsgQ D_006277F0[256];
#include "data/pieces/D_0039A580.h"
#include "data/pieces/D_0038D170.h"
CONTEXT_ONLY s32 func_001c1ce8(s8 *a, s32 b) { return a[b * 4 + 3]; }
#include "data/data_0037.h"
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003B.h"
#include "data/data_003C.h"
#include "data/pieces/D_002BBDFC.h"
