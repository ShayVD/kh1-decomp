/* Object commands: the 32 command nodes D_00525A40 (func_00133868 queues
 * one), the 32 triples D_00526640 (func_001337e0), the per-frame task
 * func_00133a88 that runs them (func_00134718 resets both and installs the
 * tasks), and a node chain an object drags (func_001342c8). Flag mode:
 * nostrict_nofill (the other modes are in the sibling files). Read from the
 * code, not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"

/* func_001342c8 (from hand/nostrict_nofill/text_00120000_b02.c). */
typedef struct { f32 x, y, z, w; } V4;
typedef struct Nd11 {
    s32 f0;
    f32 f4;
    u8 p8[8];
    struct { u64 c; u8 p8[8]; V4 f10; } c;
    u8 b30[4];
    u8 b34[4];
    u8 p38[8];
    V4 f40;
    u8 p50[4];
    struct Nd11 *f54;
} Nd11;
typedef struct {
    u8 p0[0x20];
    V4 f20;
    V4 f30;
    V4 f40;
    u8 p50[0xa0 - 0x50];
    f32 fa0[4];
    u8 pb0[0x150 - 0xb0];
    f32 f150;
    u8 p154[0x440 - 0x154];
    Nd11 *f440;
} Ob11;
extern f32 D_002BBDFC;
extern f32 func_001dcb00(Ob11 *, V4 *, f32, f32);
extern void func_00133950(Ob11 *, Nd11 *);
extern f32 func_00120c88(f32);
extern void func_00137688(Ob11 *, f32);
extern void func_002675a8(V4 *, V4 *);
extern void func_002674f0(V4 *, V4 *, V4 *, f32);
extern s32 func_00135938(Ob11 *, s32);
extern void func_001358b8(Ob11 *, s32);
extern void func_001358f8(Ob11 *, s32);
extern void func_00131c08(Ob11 *, f32, f32, f32);
#define VAL(c) ((u32)((c)->c >> 8) & 0xffffff)
#define KIND(c) (*(u8 *)&(c)->c)
void func_001342c8(Ob11 *o) {
    Nd11 *n;
    Nd11 *nx;
    f32 t;
    s32 i;
    f32 a;
    typeof(n->c) *c;

    for (n = o->f440; n; n = nx) {
        n->f4 += D_002BBDFC;
        c = &n->c;
        nx = n->f54;
        switch (KIND(c)) {
        case 2:
            if (func_001dcb00(o, &c->f10, (f32)VAL(c), c->f10.w) < (f32)(s32)VAL(c) * D_002BBDFC) {
                func_00133950(o, n);
            }
            break;
        case 4:
        case 21:
        case 22:
            {
            f32 y = c->f10.y * D_002BBDFC;
            f32 x = c->f10.x;
            f32 r;
            if (__builtin_fabsf(y) < __builtin_fabsf(x)) {
                c->f10.x = x + y;
                r = -y;
            } else {
                r = x;
                func_00133950(o, n);
            }
            o->f150 = func_00120c88(*(f32 *)((u8 *)o + 0x3c) + r);
            }
            func_00137688(o, o->f150);
            func_002675a8(&o->f20, &o->f30);
            *(s32 *)((u8 *)o + 0x2c) = 0;
            break;
        case 23:
        case 44:
            if ((s32)VAL(c) > 0) t = n->f4 / (f32)(s32)VAL(c);
            else t = 1.0f;
            if (1.0f <= t) {
                t = 1.0f;
                func_00133950(o, n);
            }
            for (i = 0; i < 4; i++) {
                s32 x = (f32)n->b30[i] + (f32)(n->b34[i] - n->b30[i]) * t;
                if (x >= 256) x = 255;
                o->fa0[i] = (f32)x * 0.0078125f;
            }
            break;
        case 29:
            c->f10.x -= D_002BBDFC;
            if (c->f10.x <= 0.0f) {
                if (!func_00135938(o, VAL(c))) {
                    if (VAL(c) == 33) func_001358b8(o, 34);
                    else func_001358f8(o, VAL(c));
                }
                func_00133950(o, n);
            }
            break;
        case 30:
            a = (f32)VAL(c);
            t = n->f4 / a;
            if (t < 1.0f) {
                func_002674f0(&o->f40, &c->f10, &n->f40, t);
            } else {
                func_002675a8(&o->f40, &c->f10);
                func_00133950(o, n);
            }
            break;
        case 31:
            if (n->f0++ >= 2) {
                func_00131c08(o, c->f10.x, c->f10.y, (f32)VAL(c));
                func_00133950(o, n);
            }
            break;
        }
    }
}
#undef VAL
#undef KIND

