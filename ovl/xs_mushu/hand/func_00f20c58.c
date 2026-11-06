/* xs_mushu.x func_00f20c58: matched by hand. */
#include "ovl.h"

typedef struct { s32 a, b; } MuPair;
typedef struct Act {
    u8 pad0[0x10];
    OvlVec pos;
    u8 pad20[0x1c];
    f32 f3c;
    u8 pad40[0x58];
    struct Act *parent;
    u8 pad9c[0xb4];
    f32 f150;
    u8 pad154[0x10];
    s32 f164;
    u8 pad168[4];
    f32 f16c;
    u8 pad170[0x200];
    u8 b370[4];
    u8 pad374[0x12c];
    void *cb;
} Act;
extern void *D_00F21380;
extern void *D_00F21384;
extern void *D_00F21388;
extern s32 D_00F21394;
extern s32 D_00F21398;
extern f32 **D_00F21688;
extern f32 D_00F2168C;
extern u32 D_00F21690;
extern MuPair D_002E31B0;
extern f32 D_00304B7C;
extern s32 D_00304B6C;
extern f32 D_002BBDFC;
void func_00f20ba0(Act *);
void func_00137308(Act *, void *);
void func_00f20af8(void);
void func_001315c0(Act *, s32, f32 *, f32);
void func_00f20098(s32);
void func_00130340(void *, s32, f32);
void func_00130578(void *, s32, f32);
void func_00f207a0(void);
s32 func_00122ff8(s32);
#ifdef KH1_PS2
void func_0012ec60(s32, s32, f32 *);
#else /* the definition returns f32: an x86 caller that drops it unbalances the x87 stack */
f32 func_0012ec60(s32, s32, f32 *);
#endif
#ifdef KH1_PS2
void func_001376e8(Act *, f32 *);
#else /* the definition returns f32: an x86 caller that drops it unbalances the x87 stack */
f32 func_001376e8(Act *, f32 *);
#endif
void func_00f20b68(void);
void func_00147ed8(void *, s32, s32, f32 *);
void func_00135800(Act *, f32, f32);
void func_00157818(void *, s32);
void func_00137318(Act *);
f32 func_001216d8(f32, f32, f32);
void func_00137688(Act *, f32);
void func_00f20c58(Act *a) {
    OvlVec v;
    s32 i;
    if (a->cb == NULL) {
        func_00137308(a, D_00F21384);
        a->cb = func_00f20ba0;
        D_00F21688 = NULL;
        D_00F2168C = 0;
        func_00f20af8();
    }
    if (a->parent != NULL) {
        func_001315c0(a->parent, 0, a->pos, 1.6f);
        a->f150 = a->parent->f3c;
        for (i = 0; i < 4; i++) {
            a->b370[i] = a->parent->b370[i];
        }
        if (D_00F21688 != NULL) {
            PlatVu0CopyVector(*D_00F21688, a->pos);
        }
    }
    switch (D_00F21398) {
    case 0: break;
    case 1:
        if (D_00F21394 < 3 || (0.0f < D_00304B7C && D_00F21690 != 0)) {
            if (D_00F21394 == 0) {
                func_00130340(a, 200, 0.0f);
                func_00130578(a, 201, 0.0f);
                func_00130578(a, 0, 0.0f);
                func_00f207a0();
                D_00F21394++;
            } else if (a->f164 == 201 && 6.0f <= a->f16c) {
                func_00130340(a, 201, 0.0f);
                func_00130578(a, 0, 0.0f);
                func_00f207a0();
                D_00F21394++;
            }
        } else {
            D_00F21394 = 0;
            func_00f20098(0);
        }
        if (func_00122ff8(D_002E31B0.a)) {
            func_0012ec60(D_002E31B0.a, D_002E31B0.b, v);
            PlatVu0SubVector(v, v, a->pos);
            func_001376e8(a, v);
        }
        break;
    case 100:
        if (!(D_00F2168C < 30.0f)) {
            func_00f20b68();
            func_00147ed8(D_00F21380, 5, 20000, a->pos);
            func_00135800(a, 0.0f, 10.0f);
            func_00137318(a);
            D_00304B6C = 0;
        } else {
            if (D_00F2168C == 0.0f) {
                func_00130340(D_00F21388, 203, 0.0f);
                func_00157818(D_00F21388, 0);
            }
            D_00F2168C += D_002BBDFC;
        }
        break;
    case 101:
        func_00137318(a);
        D_00304B6C = 0;
        break;
    }
    func_00137688(a, func_001216d8(a->f3c, a->f150, 0.1308997f));
    D_00F21690 >>= 1;
}
