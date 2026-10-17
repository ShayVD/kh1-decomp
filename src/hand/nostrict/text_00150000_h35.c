/* Hand-matched functions near 0x153000-0x15a000 (worker 35). Built without
 * strict aliasing. */
#include "common.h"

/* ---- func_00153418 ---- */
typedef union { u64 d; s32 w; struct { u32 lo; u32 x:6; u32 kind:4; u32 hi:22; } b; } F8_153418;
typedef struct { u8 pad[8]; F8_153418 f8; } Msg153418;
typedef struct { u8 pad[4]; s32 w4; s32 w8; s32 wC; } S144_153418;
typedef struct { u8 pad[0x144]; S144_153418 *p144; } Obj153418;
void func_00147138(Obj153418 *, s32);
s32 func_00153300(Obj153418 *, Msg153418 *);
void func_00153360(Obj153418 *, Msg153418 *);
void func_001533d0(Obj153418 *, Msg153418 *);
void func_00145008(Obj153418 *, s32);

void func_00153418(Obj153418 *a, Msg153418 *m) {
    s32 n;
    if (m->f8.b.kind == 1) func_00147138(a, 4);
    if (func_00153300(a, m)) {
        func_00153360(a, m);
    } else {
        n = m->f8.w;
        if (n > 0) {
            a->p144->w8 += n;
            if (a->p144->w8 >= a->p144->wC) {
                func_00145008(a, 0);
                a->p144->w4 = 6;
            } else {
                func_001533d0(a, m);
            }
        }
    }
}

/* ---- func_001538d8 ---- */
typedef struct { u8 pad[0x44]; f32 f44; f32 f48; } S144_1538d8;
typedef struct { u8 pad[0xA4]; f32 fA4; f32 fA8; u8 padac[0x98]; S144_1538d8 *p144; } Obj1538d8;
extern f32 D_002BBDFC;
f32 cosf(f32);
f32 func_00120c88(f32);
void func_00152770(Obj1538d8 *);

s32 func_001538d8(Obj1538d8 *a) {
    f32 s, c;
    a->p144->f44 -= D_002BBDFC;
    if (a->p144->f44 <= 0.0f) {
        func_00152770(a);
        return 1;
    }
    s = a->p144->f44 / 300.0f;
    s = s * -0.18849556148052216f + 0.20943952f;
    a->p144->f48 = func_00120c88(a->p144->f48 + s * D_002BBDFC);
    c = (cosf(a->p144->f48) + 1.0f) * 0.5f;
    a->fA8 = c;
    a->fA4 = c;
    return 0;
}

/* ---- func_00153c50 ---- */
typedef struct { u64 d0; u8 pad[0x28]; u8 x30[0x10]; s32 w40; } S144_153c50;
typedef struct { u8 pad[0x74]; s32 w74; u8 pad78[0xCC]; S144_153c50 *p144; } S98_153c50;
typedef struct { u8 pad[0x98]; S98_153c50 *p98; } Obj153c50;
s32 func_00130340(void *, s32, f32);
s32 func_00130578(void *, s32, f32);
void func_00152dc8(S98_153c50 *, s32);
void func_001315c0(s32, s32, void *, f32);

void func_00153c50(Obj153c50 *a, s32 b) {
    func_00130340(a, 0x010000BA, 8.0f);
    func_00130578(a, 0x40000000, 0.0f);
    a->p98->w74 = b;
    func_00152dc8(a->p98, 0);
    if (b) {
        a->p98->p144->d0 |= 2;
        func_001315c0(b, 0x8003, a->p98->p144->x30, 0.0f);
    }
    a->p98->p144->w40 = 0;
}
