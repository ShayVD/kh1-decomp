/* xl_limit.x func_00f20ae0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xC]; void *fC; } Res;
typedef struct { u64 flags; s32 w8; } Eff;
typedef struct { u8 pad[0x2C]; Eff *eff; } Mdl;
typedef struct { u8 pad[8]; f32 f8; } Mot;
typedef struct {
    s32 flags;
    u8 pad4[0x2C];
    OvlVec v30;
    u8 pad40[0x10C];
    Mdl *mdl;
    u8 pad150[0x270];
    OvlVec v3c0;
} LimObj;
typedef struct { f32 *pos; s32 w4; f32 *scale; } Fx;
void func_0013ecf8(LimObj *, void *, f32 *);
Mot *func_0013dc10(LimObj *, s32);
#ifdef KH1_PS2
f32 func_00f209e0(LimObj *, f32);
#else /* the definition is void: an x86 caller of an f32 one pops an empty x87 stack */
void func_00f209e0(LimObj *, f32);
#endif
void func_00130340(LimObj *, s32, f32);
Res *func_00130578(LimObj *, s32, f32);
void func_001315c0(LimObj *, s32, f32 *, f32);
s32 func_00147ed8(s32, s32, s32, f32 *);
void func_00f20940();
void func_00f20ac8();
f32 sinf(f32);
extern f32 D_002BBDFC;
extern OvlVec D_002C58B0;
extern u8 D_002E31B0[];
extern s32 D_00F23208;
extern f32 D_00F23220[];
extern s32 D_00F23480;
extern f32 D_00F23484;
extern Fx *D_00F23488;
extern s32 D_00F2348C;

/* func_00f208f8 defined above (as in the original file): bc1f, not bc1fl, before its call */
CONTEXT_ONLY void func_00f208f8(LimObj *o) {}

/* a class's 7th callback (func_0014f830): (object, pad, the facing vector out), as class15.c func_0014c5c8 */
void func_00f20ae0(LimObj *o, void *pad, f32 *dir) {
    OvlVec v;
    f32 s;
    Mot *m;
    f32 *sc;

    if (D_00F23480 < 5) {
        func_0013ecf8(o, D_002E31B0, dir);
        m = func_0013dc10(o, D_00F23480 + 54);
        o->mdl->eff->flags |= 0x800000;
        func_00f209e0(o, m->f8);
        sceVu0ScaleVectorXYZ(o->v3c0, o->v30, D_00F23220[D_00F23480]);
        func_00130578(o, 0x40000006, 8.0f);
        if (++D_00F23480 == 5) {
            o->mdl->eff->w8 = D_00F23208;
        }
    } else if (D_00F23480 == 5) {
        func_0013ecf8(o, D_002E31B0, dir);
        func_00f209e0(o, 0.0f);
        sceVu0CopyVector(o->v3c0, D_002C58B0);
        func_00130340(o, 0x008000F6, 0.0f);
        func_00130578(o, 6, 8.0f)->fC = func_00f20ac8;
        D_00F23480++;
        o->flags &= ~0x01000000;
    } else {
        func_001315c0(o, 48, v, 1.0f);
        D_00F23484 += D_002BBDFC;
        if (D_00F23484 < 10.0f) {
            return;
        }
        if (D_00F23484 < 50.0f) {
            func_00f208f8(o);
            if (D_00F23488 != NULL) {
                s = (D_00F23484 - 10.0f) / 40.0f;
                s = sinf(s * 3.1415928f * 0.5f) * 3.0f;
                sc = D_00F23488->scale;
                sc[2] = s;
                sc[1] = s;
                sc[0] = s;
                sceVu0CopyVector(D_00F23488->pos, v);
            }
        } else if (D_00F2348C == 0) {
            D_00F2348C = func_00147ed8(D_00F23208, 4, 20000, v);
            func_00f20940((s64)0x807C << 47);
        }
    }
}
