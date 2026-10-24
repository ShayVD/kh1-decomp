/* The object scripts' second command table, default flags (docs/modules.md
 * "Session 51"): the 21 functions of D_00362340 (8-byte {fn, argc} records,
 * argc | 0x40000000 for a float result), the table after D_002E2810 in the
 * object-script descriptor D_002E2F20 (docs/renderer-spec.md): empty
 * commands, set or clear an object flag (func_001768e8), get the camera's
 * position and target (func_00176a60 / 00176a80), vector copies and
 * products, an angle from s16 units (func_00176960, in
 * objcmd2.nostrict.c), acosf, atan2f between two points (func_00176a18),
 * set the camera's view angle (func_00176aa0), start a screen shake
 * (func_00176af0 -> func_0017f580) and func_00176b80.  Each section names the
 * file its code came from.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "data/bss_0057.h"
#include "data/pieces/D_00362438.h"
#include "data/pieces/D_0035E710.h"
#include "data/pieces/D_003626C0.h"
#include "data/pieces/D_003626F0.h"
#include "data/pieces/D_00362424.h"
#include "data/pieces/D_00362428.h"
#include "data/pieces/D_0036242C.h"
#include "data/pieces/D_00362430.h"
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_0036243C.h"
#include "data/pieces/D_00362710.h"
#include "data/pieces/D_0035C710.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_0036244C.h"
#include "data/pieces/D_00362450.h"
#include "data/pieces/D_00362454.h"
#include "common.h"
#include "data/bss_0055.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/pieces/D_002BC144.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_0035BD40.h"
#include "data/types/text_00170000_h11_p4.h"
#include "data/pieces/D_00364130.h"
#include "data/types/text_00170000_h11.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_003626F8.h"

/* func_00176898 (from auto/text_00170000.c). */
void func_00176898(void) {

}

/* func_001768a0 (from auto/text_00170000.c). */
void func_001768a0(void) {

}

/* func_001768a8 (from auto/text_00170000.c). */
void func_001768a8(void) {

}

/* func_001768b0 (from auto/text_00170000.c). */
void func_001768b0(void) {

}

/* func_001768b8 (from auto/text_00170000.c). */
void func_001768b8(void) {

}

/* func_001768c0 (from auto/text_00170000.c). */
void func_001768c0(void) {

}

/* func_001768c8 (from auto/text_00170000.c). */
void func_001768c8(void **arg0) {
    void *temp_v0;

    temp_v0 = *arg0;
    if (temp_v0 != NULL) {
        *M2C_FIELD(temp_v0, s8 **, 0x10) = 1;
    }
    *arg0 = NULL;
}

/* func_001768e8 (from hand/text_00170000_h11.c). */
typedef struct { u8 pad[0x20]; u8 *p20; } Obj20;
void func_001768e8(Arg *a) {
    if (a[1].i) {
        *((Obj20 *)a[0].p)->p20 |= 1;
    } else {
        *((Obj20 *)a[0].p)->p20 &= ~1;
    }
}

/* func_00176920 (from auto/text_00170000_8.c). */
M2C_UNK func_002675a8(s32, s32);
void func_00176920(void *arg0) {
    func_002675a8(M2C_FIELD(arg0, s32 *, 4), *M2C_FIELD(arg0, s32 **, 0));
}

/* func_00176940 (from auto/text_00170000_8.c). */
void func_00176940(void *arg0) {
    func_002675a8(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 8));
}

/* func_001769f0 (from auto/text_00170000_8.c). */
M2C_UNK func_00267370(s32, s32, s32);
void func_001769f0(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    func_00267370(temp_v0, temp_v0, M2C_FIELD(arg0, s32 *, 4));
}

/* func_00176a18 (from hand/text_00170000_h11.c). */
f32 atan2f(f32, f32);
void func_00176a18(Arg *a) {
    f32 *p = a[0].p;
    f32 *q = a[1].p;
    a[0].f = atan2f(p[0] - q[0], p[2] - q[2]);
}

/* func_00176a60 (from auto/text_00170000_9.c). */
void func_00176a60(s32 *arg0) {
    func_002675a8(*arg0, ((M2C_UNK *)&D_002E2780));
}

/* func_00176a80 (from auto/text_00170000_9.c). */
void func_00176a80(s32 *arg0) {
    func_002675a8(*arg0, ((M2C_UNK *)&D_002E2790));
}

/* func_00176aa0 (from auto/text_00170000_8.c). */
M2C_UNK func_0017f178();
extern M2C_UNK D_00362660;
void func_00176aa0(void *arg0) {
    M2C_FIELD(&D_00362660, f32 *, 0) = (f32) ((M2C_FIELD(arg0, f32 *, 0) * 3.141592503f) / 180.0f);
    M2C_FIELD(&D_00362660, f32 *, 0xC) = (f32) M2C_FIELD(arg0, f32 *, 4);
    func_0017f178();
}

/* func_00176af0 (from hand/text_00170000_h11.c). */
void func_0017f580(f32, f32, f32, f32, s32);
void func_00176af0(Arg *a) {
    func_0017f580(a[0].f, a[1].f, a[2].f, a[3].f, a[4].i);
}

/* func_00176b20 (from auto/text_00170000_8.c). */
f32 acosf(f32);
void func_00176b20(f32 *arg0) {
    *arg0 = acosf(*arg0);
}

/* func_00176b50 (from auto/text_00170000_8.c). */
M2C_UNK func_00108180(s32);
void func_00176b50(s32 *arg0) {
    func_00108180(*arg0);
}

/* func_00176b68 (from auto/text_00170000_8.c). */
M2C_UNK func_001081a0(s32);
void func_00176b68(s32 *arg0) {
    func_001081a0(*arg0);
}

/* func_00176b80 (from hand/text_00170000_h11.c). */
typedef struct { u8 pad[0x3c]; s32 x3c; u8 pad40[4]; s32 x44; u8 pad48[0xbe - 0x48]; s16 xbe; } Sub6C;
void func_00176b80(Arg *a) {
    Arg *o = a[0].p;
    ((Sub6C *)o[27].p)->x3c = 1;
    ((Sub6C *)o[27].p)->x44 = 0;
    ((Sub6C *)o[27].p)->xbe = 0;
}

