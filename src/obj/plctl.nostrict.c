/* The player-controlled object's move: the velocity by state
 * (func_0013e1f8), the motion events of the leader (func_0013eab0,
 * func_0013ee40), the camera-relative move func_0013f198, and the ability
 * records D_0052AE70 (func_0013f2c0). Flag mode: nostrict (the other modes
 * are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0052.h"
#include "data/types/nostrict_text_00130000_h55.h"
#include "data/pieces/D_002E26A0.h"
#include "vm/script_vm.h"
#include "data/types/nostrict_text_00130000_b03_p3.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00130000_b03_p2.h"
#include "data/types/nostrict_text_00130000_b03.h"
#include "data/pieces/D_00304DB0.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0053.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00140000_h33.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002E27C8.h"

/* func_0013e000 (from hand/nostrict/text_00130000_h55.c). */
typedef struct { u8 pad[8]; f32 x8; f32 xc; } W55Dim;
typedef struct { u8 pad[0x10]; W55Dim *x10; } W55Mdl;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x4c - 0x8]; u16 x4c; u8 pad4e[0x54 - 0x4e]; s8 x54; } W55Inf;
typedef struct { u8 pad[0xcc]; f32 xcc; } W55Mv;
typedef struct { f32 *x0; } W55Fx;
typedef struct Actor_3e000 {
    u32 x0;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    f32 pos[4];
    f32 x20[4];
    u8 pad30[0x3c - 0x30];
    f32 x3c;
    f32 x40;
    f32 x44;
    u8 pad48[0x6c - 0x48];
    W55Mv *x6c;
    u32 x70;
    u8 pad74[0x98 - 0x74];
    void *x98;
    u8 pad9c[0x120 - 0x9c];
    f32 x120[4];
    W55Inf *x130;
    W55Mdl *x134;
    u8 pad138[0x148 - 0x138];
    f32 *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x2c0 - 0x154];
    f32 x2c0;
    f32 x2c4;
    u8 pad2c8[0x2de - 0x2c8];
    u16 x2de;
    u8 pad2e0[0x30c - 0x2e0];
    u16 x30c;
    u8 pad30e[0x316 - 0x30e];
    u16 x316;
    u8 pad318[0x370 - 0x318];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b39:1; u32 hi:24; } b; } x370;
    u8 pad378[0x398 - 0x378];
    s32 x398;
    u8 pad39c[0x3c0 - 0x39c];
    f32 x3c0[4];
    u8 pad3d0[0x444 - 0x3d0];
    s32 x444;
    u8 pad448[0x488 - 0x448];
    W55Fx *x488;
    s32 x48c;
} W55Ob;
extern s32 D_0029B410;
void func_00105a30(s32 a, s32 id, f32 *v);
u32 func_00105bc0(s32 a, s32 id);
s32 func_00117bb0(s32 id, f32 *a, f32 *b, f32 *c);
W55Fx *func_00147c98(s32 a, s32 b, s32 c);
void func_00147d50(W55Fx *f, f32 *v);
s32 func_00176578(s32 a, s32 b, s32 c, s64 d);
void func_0013e000(W55Ob *o) {
    f32 v[4], w[4], pos[4], out[4];
    u32 id = o->x316;
    W55Fx *fx;
    u32 k;
    s32 h;
    s32 *gp;
    if (id == 0xffff) return;
    if (o->x0 & 0x1000080) return;
    func_00105a30(-1, id, v);
    v[1] = 0.0f;
    PlatVu0Normalize(v, v);
    PlatVu0CopyVector(pos, o->pos);
    pos[1] -= o->x134->x10->x8 * o->x44;
    pos[3] = 1.0f;
    PlatVu0ScaleVector(w, v, o->x134->x10->xc * o->x40 * -2.0f);
    w[3] = 1.0f;
    if (!func_00117bb0(id, pos, w, out)) return;
    fx = o->x488;
    if (!fx) {
        if (!D_0029B410) goto skip;
        k = func_00105bc0(-1, id);
        switch (k) {
        case 1: k = 2; break;
        case 2: k = 4; break;
        case 3: k = 8; break;
        default: k = 0; break;
        }
        gp = &D_0029B410;
        h = func_00176578(*gp, k, 0, (1 << o->x130->x4c) | 0x400);
        if (h >= 0) {
            fx = func_00147c98(*gp, h, 20000);
            o->x48c = id;
            o->x488 = fx;
        }
    } else if (o->x48c != id) fx = 0;
skip:
    if (fx) {
        PlatVu0CopyVector(fx->x0, out);
        func_00147d50(fx, v);
    }
}

/* func_0013e1f8 (from hand/nostrict/text_00130000_b03.c). */
extern f32 D_002BBDFC;
extern u32 D_002C5958;
void func_00130340(B3Ob *o, s32 a, f32 f);
void func_00130398(B3Ob *o, s32 a, f32 f);
void *func_00130578(B3Ob *, s32, f32);
void func_00141720(B3Ob *);
void func_0012bd98(B3Ob *, s32, u32, f32 *);
void func_00140d50(B3Ob *, f32 *);
void func_0013f6d0(B3Ob *, f32 *);
void func_00153e80(B3Ob *);
void func_00171fa0(B3Ob *);
void func_001550a0(B3Ob *, f32 *);
f32 func_00121b08(f32);
s32 func_001375d8(B3Ob *);
#define func_0013e000 ((void (*)(B3Ob *)) func_0013e000)
void func_0013e1f8(B3Ob *o, f32 *v) {
    func_00141720(o);
    PlatVu0CopyVector(v, o->x20);
    if (o->x0 & 0x400) {
        switch (o->x70) {
        case 0:
        case 30:
            switch (o->x378) {
            case 31:
                func_0012bd98(o, o->x39e, 0x80000008, o->x10);
            case 2:
            case 3:
            case 16:
            case 21:
                func_00130398(o, (o->x3d0 + 7) | 0x1000000, 0.0f);
                func_00130578(o, (o->x0 & 0x2000) ? 0x400000ab : 0x40000000, 8.0f);
                o->x148->x90 = 0xffff;
                PlatVu0CopyVector(v, o->x30);
                v[3] = 0.0f;
                break;
            case 10:
                func_00140d50(o, v);
                break;
            case 13:
                func_0013f6d0(o, v);
                break;
            case 17:
                if (o->x164 == 0x6c) {
                    func_00153e80(o);
                } else {
                    func_00130340(o, 0x40000000, 8.0f);
                }
                break;
            }
            break;
        case 2:
            func_00171fa0(o);
            func_00130398(o, 6, 8.0f);
            break;
        case 27:
            func_00130340(o, 0x10000bc, 6.0f);
            func_00130578(o, 0x400000bd, 0.0f);
            break;
        case 6:
            if (o->x378 == 2) {
                func_00130398(o, (o->x3d0 + 7) | 0x1000000, 0.0f);
                func_00130578(o, 0x400000ab, 8.0f);
                o->x148->x90 = 0xffff;
                PlatVu0CopyVector(v, o->x30);
                v[3] = 0.0f;
            }
            break;
        case 8:
            if (!((s32)(o->x440 >> 33) & 1) && !((s32)(o->x370 >> 60) & 1)) {
                func_00130398(o, 0x75, 16.0f);
            }
            break;
        }
        o->x0 &= ~0x400;
    }
    func_0013e000(o);
    func_001550a0(o, v);
    if (!(o->x0 & 4)) o->x3e8 = 0;
    o->x148->x100 = func_00121b08(o->x148->x100);
    if (o->x88 & 8) {
        o->x148->x170 -= D_002BBDFC;
        if (o->x148->x170 < 0.0f || (D_002C5958 & 0x104000) || func_001375d8(o)) {
            o->x88 &= ~8;
            o->x148->x170 = 0.0f;
        }
    }
}
#undef func_0013e000

/* func_0013e638 (from hand/nostrict/text_00130000_b03.c). */
typedef struct { u32 type:8; u32 id:16; u32 b24:1; u32 f25:1; u32 hi:6; void *x4; s32 x8; } B3Ev;
s32 func_00133000(B3Ob *o, s32 id);
void func_001333e0(B3Ob *o, s32 id, void *p);
void func_0013bb60(B3Ob *o, s32 id);
void func_0012c560(B3Ob *o, void *a, s32 id);
void func_001337e0(s32 a, void *b, s32 c);
f32 func_001376e8(B3Ob *o, f32 *q);
void func_00137330(void *a, B3Ob *o, s32 t);
void func_0014f658(B3Ob *o, s32 t);
void func_001519c0(B3Ob *o, void *a);
void func_00121fc4(f32 *, f32 *);
void func_0013e638(B3Ob *o, B3Ev *e, f32 *q) {
    f32 d;
    s32 k;
    switch (e->type) {
    case 0:
        break;
    case 2:
        if (func_00133000(o, e->id)) {
            if (!e->id) {
                func_00130340(o, 0x1000036, 0.0f);
                func_00130578(o, 61, 0.0f);
            } else {
                func_00130340(o, (e->id + 54) | 0x1000000, 0.0f);
            }
            func_00130578(o, 0x40000000, 0.0f);
            func_001333e0(o, e->id, &e->x4);
        }
        break;
    case 6:
        func_0013bb60(o, e->id);
        break;
    case 3:
        if (!e->x4 || e->x4 == o) {
            func_00130340(o, 0x100003e, 8.0f);
        } else {
            func_00130340(o, 0x100003f, 8.0f);
        }
        func_00130578(o, 0x40000000, 8.0f);
        func_0012c560(o, e->x4, e->id);
        break;
    case 4:
        o->x370 &= ~0x4000000000000ULL;
        func_00130398(o, 0x40000000, 16.0f);
        func_001337e0(0, e->x4, 0);
        PlatVu0CopyVector(o->x3c0, (*(f32 (*)[0x4])&D_002C58B0));
        break;
    case 5:
        o->x370 &= ~0x4000000000000ULL;
        func_00130398(o, 0x40000000, 16.0f);
        func_001337e0(4, e->x4, 0);
        PlatVu0CopyVector(o->x3c0, (*(f32 (*)[0x4])&D_002C58B0));
        break;
    case 28:
        func_001376e8(o, q);
        d = o->x10[1] - ((B3Ob *)e->x4)->x10[1];
        if (d < 20.0f) {
            k = 181;
        } else if (d < 80.0f) {
            k = 183;
        } else {
            k = 184;
        }
        func_00130340(o, k | 0x1000000, 8.0f);
        func_00130578(o, 0x400000b6, 0.0f);
        func_00137330(e->x4, o, 28);
        func_0014f658(o, 28);
        break;
    case 55:
        func_001519c0(o, e->x4);
        break;
    case 30:
        func_00137330(o->x98, o, e->type);
        break;
    default:
        func_001376e8(o, q);
        func_00137330(e->x4, o, e->type);
        break;
    }
    func_00121fc4(q, q);
    q[3] = 0.0f;
}

/* func_0013e978 (from hand/nostrict/text_00140000_h33.c). */
typedef FVec4 V4f;
typedef struct Eff154 { u8 pad[0x10]; u8 *p10; u32 w14; } Eff154;
typedef struct S130 { u8 pad[0x5C]; u8 b5c; } S130;
typedef struct {
    u8 pad[0x30];
    u64 d30;
    u8 pad38[8];
    V4f p;
    f32 f50;
    f32 f54;
    u8 pad58[4];
    s32 w5c;
    u8 pad60[0x40];
    V4f va0;
    f32 fb0;
    f32 fb4;
    f32 fb8;
    f32 fbc;
    u8 padc0[0x154 - 0xC0];
    Eff154 *p154;
    f32 f158;
} Sub148;
typedef struct {
    u32 flags;
    s32 w4;
    u8 pad8[0x8];
    V4f pos;
    u8 pad20[0x88 - 0x20];
    u32 w88;
    u8 pad8c[0x130 - 0x8C];
    S130 *p130;
    u8 pad134[0x148 - 0x134];
    Sub148 *p148;
    u8 pad14c[0x1CC - 0x14C];
    u32 w1cc;
    u8 pad1d0[0x2A0 - 0x1D0];
    V4f v2a0;
    V4f v2b0;
    f32 f2c0;
    u8 pad2c4[0x2D0 - 0x2C4];
    u32 w2d0;
    u8 pad2d4[0x2F0 - 0x2D4];
    V4f v2f0;
    f32 f300;
    f32 f304;
    u8 pad308[0x314 - 0x308];
    u16 h314;
    u8 pad316[0x39E - 0x316];
    u8 b39e;
    u8 pad39f[0x3C4 - 0x39F];
    f32 f3c4;
} ObjF3;
typedef struct { u32 type:8; u32 id:16; u32 hi:8; s32 w4; } Cmd;
f32 func_0014cce0(ObjF3 *, f32);
#define func_00133000 ((s32 (*)(ObjF3 *, s32)) func_00133000)
#define func_00130340 ((void (*)(ObjF3 *, s32, f32)) func_00130340)
#define func_00130578 ((void (*)(ObjF3 *, s32, f32)) func_00130578)
#define func_001333e0 ((void (*)(ObjF3 *, s32, s32 *)) func_001333e0)
#define func_00137330 ((void (*)(s32, ObjF3 *, s32)) func_00137330)
void func_0013e978(ObjF3 *o, Cmd *c) {
    u8 t = *(u8 *)c;
    if (t != 0) {
        if (t == 2) {
            if (func_00133000(o, c->id) == 0) return;
            if (c->id == 0) {
                f32 z = 0.0f;
                func_00130340(o, 0x1000083, z);
                func_00130578(o, 0x8A, z);
            } else {
                func_00130340(o, (c->id + 0x83) | 0x1000000, 0.0f);
            }
            func_00130578(o, 0x40000006, 8.0f);
            func_001333e0(o, c->id, &c->w4);
            func_0014cce0(o, (*(Cfg_308cdc **)&D_00308CDC)->fe8);
            PlatVu0ScaleVector((V4f *)((u8 *)o + 0x3C0), (V4f *)((u8 *)o + 0x3C0), (*(Cfg_308cdc **)&D_00308CDC)->ff0);
            return;
        }
        func_00137330(c->w4, o, t);
    }
}
#undef func_00133000
#undef func_00130340
#undef func_00130578
#undef func_001333e0
#undef func_00137330

/* func_0013eab0 (from hand/nostrict/text_00130000_h55.c). */
typedef struct Actor_3eab0 {
    u32 x0;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    f32 pos[4];
    f32 x20[4];
    u8 pad30[0x3c - 0x30];
    f32 x3c;
    f32 x40;
    f32 x44;
    u8 pad48[0x6c - 0x48];
    W55Mv *x6c;
    u32 x70;
    u8 pad74[0x98 - 0x74];
    void *x98;
    u8 pad9c[0x120 - 0x9c];
    f32 x120[4];
    W55Inf *x130;
    W55Mdl *x134;
    u8 pad138[0x148 - 0x138];
    f32 *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x2c0 - 0x154];
    f32 x2c0;
    f32 x2c4;
    u8 pad2c8[0x2de - 0x2c8];
    u16 x2de;
    u8 pad2e0[0x30c - 0x2e0];
    u16 x30c;
    u8 pad30e[0x316 - 0x30e];
    u16 x316;
    u8 pad318[0x370 - 0x318];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b39:1; u32 hi:24; } b; } x370;
    u8 pad378[0x398 - 0x378];
    s32 x398;
    u8 pad39c[0x3c0 - 0x39c];
    f32 x3c0[4];
    u8 pad3d0[0x444 - 0x3d0];
    s32 x444;
    u8 pad448[0x488 - 0x448];
    W55Fx *x488;
    s32 x48c;
} W55Ob_3eab0;
typedef struct { u32 type:8; u32 id:16; u32 b24:1; u32 f25:1; u32 hi:6; void *x4; s32 x8; } W55Ev;
f32 func_0012ec60(void *a, s32 b, f32 *v);
#define func_0012c560 ((void (*)(W55Ob_3eab0 *o, void *a, s32 id)) func_0012c560)
#define func_00130340 ((void (*)(void *o, s32 a, f32 f)) func_00130340)
#define func_00130578 ((void *(*)(void *, s32, f32)) func_00130578)
#define func_00133000 ((s32 (*)(W55Ob_3eab0 *o, s32 id)) func_00133000)
#define func_001333e0 ((void (*)(W55Ob_3eab0 *o, s32 id, void *p)) func_001333e0)
void func_0013eab0(W55Ob_3eab0 *o, W55Ev *e, f32 *q) {
    f32 v[4];
    switch (e->type) {
    case 2:
        if (func_00133000(o, e->id)) {
            if (e->x4) {
                func_0012ec60(e->x4, e->x8, v);
                PlatVu0SubVector(q, v, o->pos);
                o->x6c->xcc = 0.19634955f;
            }
            if (!e->id) {
                func_00130340(o, 0x1000083, 0.0f);
                func_00130578(o, 138, 0.0f);
            } else {
                func_00130340(o, (e->id + 131) | 0x1000000, 0.0f);
            }
            func_00130578(o, 0x40000075, 8.0f);
            func_001333e0(o, e->id, &e->x4);
        }
        break;
    case 3:
        if (!e->x4 || e->x4 == o) {
            func_00130340(o, 0x100008b, 8.0f);
        } else {
            func_0012ec60(e->x4, e->x8, v);
            PlatVu0SubVector(q, v, o->pos);
            func_00130340(o, 0x100008c, 8.0f);
        }
        func_00130578(o, 0x40000075, 8.0f);
        func_0012c560(o, e->x4, e->id);
        PlatVu0ScaleVector(o->x3c0, o->x3c0, 0.7f);
        break;
    case 4:
        func_001337e0(0, e->x4, 0);
        break;
    case 5:
        func_001337e0(4, e->x4, 0);
        break;
    case 0: case 6: case 28: case 29: case 30:
        break;
    default:
        return;
    }
    func_00121fc4(q, q);
    q[3] = 0.0f;
}
#undef func_0012c560
#undef func_00130340
#undef func_00130578
#undef func_00133000
#undef func_001333e0

/* func_0013ed88 (from hand/nostrict/text_00140000_h33.c). */
typedef struct { u8 id; u8 pad[3]; s32 w4; s32 w8; } Cmd8;
typedef struct { f32 x, y, z; s32 w; } V4;
u16 *func_001478c8(s32);
s32 func_0012f040(s32, s32);
void func_0013ecf8(s32, s32 *, V4 *);
void func_0013ed88(s32 o, Cmd8 *c, V4 *v) {
    if (*func_001478c8(c->id) & 2) {
        if (func_0012f040(c->w4, c->w8)) {
            func_0013ecf8(o, &c->w4, v);
            return;
        }
        if (v->x == 0.0f && v->z == 0.0f) {
            PlatVu0CopyVector((V4f *)v, (V4f *)(o + 0x30));
        }
        v->w = 0;
    }
}

/* func_0013ee40 (from hand/nostrict/text_00130000_h55.c). */
typedef struct Actor_3ee40 {
    u32 x0;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    f32 pos[4];
    f32 x20[4];
    u8 pad30[0x3c - 0x30];
    f32 x3c;
    f32 x40;
    f32 x44;
    u8 pad48[0x6c - 0x48];
    W55Mv *x6c;
    u32 x70;
    u8 pad74[0x98 - 0x74];
    void *x98;
    u8 pad9c[0x120 - 0x9c];
    f32 x120[4];
    W55Inf *x130;
    W55Mdl *x134;
    u8 pad138[0x148 - 0x138];
    f32 *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x2c0 - 0x154];
    f32 x2c0;
    f32 x2c4;
    u8 pad2c8[0x2de - 0x2c8];
    u16 x2de;
    u8 pad2e0[0x30c - 0x2e0];
    u16 x30c;
    u8 pad30e[0x316 - 0x30e];
    u16 x316;
    u8 pad318[0x370 - 0x318];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b39:1; u32 hi:24; } b; } x370;
    u8 pad378[0x398 - 0x378];
    s32 x398;
    u8 pad39c[0x3c0 - 0x39c];
    f32 x3c0[4];
    u8 pad3d0[0x444 - 0x3d0];
    s32 x444;
    u8 pad448[0x488 - 0x448];
    W55Fx *x488;
    s32 x48c;
} W55Ob_3ee40;
typedef struct { u8 x0, x1; s8 x2; } W55EvInf;
extern W55Ev D_002E3190;
extern s32 D_002E3194;
void D_00F20000(s32 a, void *b);
s32 func_001375f0(W55Ob_3ee40 *o);
void func_0013aaa0(void);
void func_00150930(W55Ob_3ee40 *o, s32 a, void *q);
void func_00157a30(W55Ob_3ee40 *o, s32 k, void *a);
void func_00158b88(W55Ob_3ee40 *o, W55Ev *e, s32 t);
#define func_00137330 ((void (*)(void *a, W55Ob_3ee40 *o, s32 t)) func_00137330)
#define func_0013e638 ((void (*)(W55Ob_3ee40 *o, W55Ev *e, void *q)) func_0013e638)
#define func_0013e978 ((void (*)(W55Ob_3ee40 *o, W55Ev *e, void *q)) func_0013e978)
#define func_0013ecf8 ((void (*)(W55Ob_3ee40 *o, void *a, void *q)) func_0013ecf8)
#define func_001478c8 ((W55EvInf *(*)(s32 t)) func_001478c8)
void func_0013ee40(W55Ob_3ee40 *o, W55Ev *e, void *q) {
    W55EvInf *inf = func_001478c8(e->type);
    if (e->f25) {
        if (inf->x2 >= 0) func_00157a30(o, inf->x2, e->x4);
        else if (e->type == 2) func_00157a30(o, e->id + 7, e->x4);
    }
    switch (e->type) {
    case 29: case 30: case 70: case 81: case 84:
        func_00137330(o->x98, o, e->type);
        return;
    case 68:
        if (o->x70 == 0 || o->x70 == 26) func_00150930(o, D_002E3194, q);
        return;
    case 71:
        if (func_001375f0(o) && D_002E3190.f25) {
            func_0013ecf8(o, &D_002E3190.x4, q);
            D_00F20000(3, 0);
        }
        func_00137330(o->x98, o, D_002E3190.type);
        return;
    case 75: case 77: case 78: case 82: case 87: case 88: case 89: case 90: case 91:
    case 94: case 95: case 96:
        func_00158b88(o, &D_002E3190, e->type);
        return;
    case 79:
        func_0013aaa0();
        return;
    case 92: case 93:
        return;
    case 100:
        func_00137330(e->x4, o, e->type);
        return;
    }
    switch (o->x70) {
    case 0: case 6: case 24:
        func_0013e638(o, e, q);
        return;
    case 2:
        func_0013e978(o, e, q);
        return;
    case 8:
        func_0013eab0(o, e, q);
        break;
    }
}
#undef func_00137330
#undef func_0013e638
#undef func_0013e978
#undef func_0013ecf8
#undef func_001478c8

/* func_0013f198 (from hand/nostrict/text_00140000_h33.c). */
typedef struct { u8 pad[0x54]; s8 b54; } Sub130;
typedef struct { u8 pad[0x130]; Sub130 *p130; } Obj130;
extern u32 D_002C5AD4;
s32 func_0013f108(Obj130 *);
void func_001271b0(Obj130 *, V4f *);
void func_00159978(Obj130 *, V4f *);
void func_001707d0(Obj130 *, V4f *);
void func_0013e558(Obj130 *, V4f *);
#define func_0013e1f8 ((void (*)(Obj130 *, V4f *)) func_0013e1f8)
#define func_001375d8 ((s32 (*)(Obj130 *)) func_001375d8)
void func_0013f198(Obj130 *o) {
    V4f a, b;
    func_0013e1f8(o, &a);
    if (!func_001375d8(o) && !func_0013f108(o)) {
        if (o->p130->b54 == 0) {
            func_001271b0(o, &a);
        } else if ((D_002C5958 >> 17) & 1) {
            func_00159978(o, &a);
        } else if (!(((*(u32 *)&D_002C5960) >> 3) & 1)) {
            func_001707d0(o, &a);
        } else if (D_002C5AD4 & 0x8000) {
            func_001271b0(o, &a);
        }
    }
    PlatVu0CopyVector(&b, &a);
    b.y = 0;
    PlatVu0Normalize(&b, &b);
    b.y = a.y;
    b.w = a.w;
    func_0013e558(o, &b);
}
#undef func_0013e1f8
#undef func_001375d8

