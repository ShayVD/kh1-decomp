/* ~61 words (score 41, 436 vs 432; was 60): norlo. Round 29 wwm2: testing and storing the slot as c->res[i] and reading the final (*rp)->pos through rp = &c->res[i] gives the original's second slot register (s3) and the three hoisted %hi luis (s5-s7, frame 112). Left: ours makes rp its own giv (addiu s3,s3,4) where the original copies it from the c->res[i] giv each pass (move s3,s1), and the schedule around the create calls; plain/nostrict/nogcse modes are worse (49-96). */
#include "ovl.h"

typedef struct { f32 *pos; } Res;
typedef struct { u8 pad[0xD0]; OvlMtx m; } Chr;
typedef struct { u8 pad[0x10]; f32 t; Res *res[3]; OvlVec v[2]; } Ctl;
void func_00147ed8(s32, s32, s32, f32 *);
Res *func_00147c98(s32, s32, s32);
void func_00176310(Res *);
f32 sinf(f32);
extern f32 D_002BBDFC;
extern s32 D_00F23208;
extern OvlVec D_00F23280;
extern Chr *D_00F23F90;
extern OvlMtx D_00F23FA0;

s32 func_00f225b0(Ctl *c) {
    OvlVec v;
    s32 i = 0;
    f32 t;
    OvlVec *m;
    Res **rp;

    c->t += D_002BBDFC;
    t = c->t / 100.0f;
    if (t < 1.0f) {
        for (; i < 2; i++) {
            rp = &c->res[i];
            m = D_00F23FA0;
            if (c->res[i] == NULL) {
                func_00147ed8(D_00F23208, 16, 20000, c->v[i]);
                c->res[i] = func_00147c98(D_00F23208, 17, 20000);
                c->v[i][3] = 1.0f;
                sceVu0ApplyMatrix(c->v[i], m, c->v[i]);
            }
            sceVu0InterVector(v, D_00F23280, c->v[i], t);
            v[3] = 1.0f;
            v[1] += sinf(t * 3.1415928f) * -200.0f;
            sceVu0ApplyMatrix((*rp)->pos, D_00F23F90->m, v);
        }
        return 0;
    }
    for (; i < 2; i++) {
        func_00176310(c->res[i]);
    }
    return 4;
}
