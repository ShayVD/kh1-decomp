/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK free(void *);
M2C_UNK func_00248678(M2C_UNK *, void *);
M2C_UNK func_0024ae00(s32);
M2C_UNK func_0024af00(s32);
M2C_UNK func_0024b1f0();
M2C_UNK func_0024b228(M2C_UNK, s32, s32, s32);
M2C_UNK func_0024b448(M2C_UNK);
M2C_UNK func_00267518(s32, s32, void *);
M2C_UNK func_00267530(void *, s32, s32);
M2C_UNK func_002675a8(void *, s32);
M2C_UNK func_002676c0(f32);
M2C_UNK func_00267768(s32, s32, f32);
M2C_UNK func_00267810(s32, s32, f32);
M2C_UNK func_00267e90(void *, void *, f32);
#include "data/pieces/D_002E26C0.h"
extern M2C_UNK D_00469F90;
extern M2C_UNK D_00469FA0;
extern M2C_UNK D_0046A058[];
extern M2C_UNK D_00491840;
extern M2C_UNK D_004919A8;
extern M2C_UNK D_004919C8;
extern M2C_UNK D_00669714;
extern M2C_UNK D_00669A18; /* src/data/bss_0066.c: s32 D_00669A18[8] */
extern s32 D_0046A5D8;
extern s32 D_0046A688[];
s32 D_00654570[0x33d] ALIGNED(16);
extern s32 D_00668370[];
extern volatile s32 D_00668040[];
s32 func_00247388(void);
s32 func_0025daf0(M2C_UNK *);
s32 func_00267f50(M2C_UNK *, M2C_UNK *, M2C_UNK *, void *, M2C_UNK);
s32 strncmp(s32, s32, s32);
void *func_00120190(M2C_UNK *);
void func_001315c0(s32, s32, s32, f32);
void func_00247228(s32, s32, s32);
void memset(s32, s32, s32);

void func_00242ba0(void) {
    if (D_00654570[828] == 0) {
        D_00654570[828] = 1;
    }
}

void func_00246a70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_00668370[3] = arg2;
    D_00668370[4] = arg3;
    D_00668370[681] = arg0;
    D_00668370[682] = arg1;
    D_00668370[680] = 1;
    if (D_00668370[0] == 0) {
        D_00668370[0] = 1;
    }
}

void func_00246ea8(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        func_0024ae00(arg1);
    }
    func_0024af00(arg1);
}

void func_00247408(s32 arg0, s32 arg1) {
    s32 sp[4];
    s32 temp_s1;

    temp_s1 = func_00247388();
    func_001315c0(arg0, 0x8004, (s32) sp, 0.0f);
    func_00247228(temp_s1, arg1, (s32) sp);
}

void func_00248628(s32 arg0, s32 arg1, s32 arg2) {
    memset(arg0, 0, 0x10);
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
}

void func_00248ac8(s32 arg0, s32 arg1) {
    s32 sp[4];
    M2C_FIELD(sp, s32 *, 0x4) = arg1;
    M2C_FIELD(sp, s32 *, 0x0) = arg0;
    M2C_FIELD(sp, f32 *, 0x8) = 1.0f;
    func_00248678(&D_00669714, sp);
}

void func_00249370(s32 arg0, s32 arg1, void *arg2) {
    func_002676c0(M2C_FIELD(arg2, f32 *, 8));
    func_00267768(arg0, arg0, M2C_FIELD(arg2, f32 *, 0));
    func_00267810(arg0, arg0, M2C_FIELD(arg2, f32 *, 4));
}

s32 func_00249580(s32 arg0) {
    s32 sp[4];
    func_002675a8(sp, arg0);
    return func_00267f50(&D_00469F90, &D_00469FA0, (M2C_UNK *)&D_002E26C0, sp, 1) != 0;
}

void func_002498a0(f32 *arg0) {
    f32 temp_f0;
    f32 var_f1;

    var_f1 = *arg0;
    if (var_f1 < 3.141592503f) {
        temp_f0 = var_f1 + 6.28318501f;
        *arg0 = temp_f0;
        var_f1 = temp_f0;
    }
    if (var_f1 > 3.141592503f) {
        *arg0 = var_f1 + -6.28318501f;
    }
}

void func_00249988(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    s32 sp[4];
    func_00267530(sp, arg2, arg1);
    func_00267e90(sp, sp, fparg0);
    func_00267518(arg0, arg1, sp);
}

s32 func_00249da8(s32 arg0) {
    return strncmp(arg0, (s32) &D_00491840, 4);
}

void func_0024b2c8(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(0, arg0, arg1, arg2);
}

void func_0024b2f8(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(1, arg0, arg1, arg2);
}

void func_0024b328(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(2, arg0, arg1, arg2);
}

void func_0024b358(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(3, arg0, arg1, arg2);
}

void func_0024b388(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(4, arg0, arg1, arg2);
}

void func_0024b3b8(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(5, arg0, arg1, arg2);
}

void func_0024b3e8(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(6, arg0, arg1, arg2);
}

void func_0024b418(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(7, arg0, arg1, arg2);
}

void func_0024b508(void) {
    func_0024b448(0);
}

void func_0024b520(void) {
    func_0024b448(1);
}

void func_0024b538(void) {
    func_0024b448(2);
}

void func_0024b550(void) {
    func_0024b448(3);
}

void func_0024b568(void) {
    func_0024b448(4);
}

void func_0024b580(void) {
    func_0024b448(5);
}

void func_0024b598(void) {
    func_0024b448(6);
}

void func_0024b5b0(void) {
    func_0024b448(7);
}

void func_0024b5c8(s32 arg0) {
    void **temp_s0;
    void *temp_v1;

    temp_s0 = (s8 *)&D_00669A18 + (arg0 * 4);
    temp_v1 = *temp_s0;
    if (M2C_FIELD(temp_v1, s32 *, 0x24) != 0) {
        free(temp_v1);
    }
    *temp_s0 = NULL;
}

void func_0024b990(void) {
    func_0024b1f0();
}

s32 func_0024b9a8(s32 arg0) {
    return *(M2C_UNK *)((s8 *)(s8 *)&D_0046A058 + (arg0 * 4));
}

s32 func_0024cf80(void) {
    return D_0046A5D8;
}

s32 func_0024d9a0(void) {
    s32 temp_v0;

    if (D_0046A688[4] != 0) {
        temp_v0 = func_0025daf0(&D_004919A8);
        if (temp_v0 == 0) {
            D_0046A688[4] = 0;
            return temp_v0;
        }
    }
    return 1;
}

s32 func_0024dd98(s32 *arg0) {
    s32 var_s1;
    void *temp_v0;

    var_s1 = 0;
    if (arg0 != NULL) {
        *arg0 = 0;
    }
    temp_v0 = func_00120190(&D_004919C8);
    if (temp_v0 != NULL) {
        var_s1 = M2C_FIELD(temp_v0, s32 *, 0xC);
        if (arg0 != NULL) {
            *arg0 = M2C_FIELD(temp_v0, s32 *, 8);
        }
    }
    return var_s1;
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_004918B8[];
extern u8 D_004918C8[];
extern u8 D_004918D8[];
extern u8 D_004918E8[];
extern u8 D_004918F8[];
extern u8 D_00491900[];
M2C_UNK D_0046A058[0x6] ALIGNED(8) = {
    (s32)D_00491900, (s32)D_004918F8, (s32)D_004918E8, (s32)D_004918D8,
    (s32)D_004918C8, (s32)D_004918B8,
};
#include "data/data_0046.h"
#include "data/data_0049.h"
