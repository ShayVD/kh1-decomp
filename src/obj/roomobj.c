/* The room's object lists: D_00525298 and the lists D_005252C8 / D_005252F8
 * / D_00525328 (func_00132c70 builds a room's list for the world / room /
 * area D_002BC128 / D_002BC130 / D_002BC134, func_00131e40 loads its objects
 * one by one, func_001320a8 finds a record by id, func_00132040 walks the
 * live entries), and the callbacks D_00525290 (defined here) and D_00525364.
 * Flag mode: default (the other modes are in the sibling files). Read from
 * the code, not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003044D8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304B78.h"
#include "data/types/text_00130000_h32.h"
#include "m2c.h"
#include "data/pieces/D_002E26A0.h"
#include "actor.h"
#include "vm/script_vm.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E31A8.h"

/* func_00131de0 (from hand/text_00130000_h6.c). */
typedef struct {
    s32 id;
    u8 pad04[0x4E - 0x4];
    u16 key;
    u8 pad50[0x5B - 0x50];
    u8 group;
    u8 pad5c[0x78 - 0x5C];
} W6Rec;
typedef struct {
    u8 pad00[0xC];
    s32 n;
    W6Rec *recs;
} W6RecTbl;
extern W6RecTbl D_00525298;
s32 func_00131de0(s32 id, s32 key) {
    W6Rec *r = D_00525298.recs;
    s32 i;
    for (i = 0; i < D_00525298.n; i++, r++) {
        if (id == -1) {
            if (r->key == key) {
                return r->id;
            }
        } else if (r->id == id) {
            id = -1;
        }
    }
    return -1;
}

/* func_00131e40 (from hand/text_00130000_h32.c). */
extern W32Rec *D_00525354;
extern void (*D_00525360)(void);
s32 func_001560f8(s32 a, void *b);
extern W32Tbl D_00525298_00131e40 __asm__("D_00525298");
#define D_00525298 D_00525298_00131e40
void func_00131e40(s32 a) {
    while (D_00525354 < D_00525298.recs + D_00525298.n) {
        if (D_00525354->x58 == D_0052535C && func_001560f8(D_00525354->id, func_00131e40)) {
            D_00525354++;
            return;
        }
        D_00525354++;
    }
    if (D_00525360) D_00525360();
}
#undef D_00525298

/* func_00131f40 (from hand/text_00130000_h6.c). */
extern s32 D_00525360_00131f40 __asm__("D_00525360");
#define D_00525360 D_00525360_00131f40
extern s32 D_00525354_00131f40 __asm__("D_00525354");
#define D_00525354 D_00525354_00131f40
#define func_00131e40 ((s32 (*)(s32 a)) func_00131e40)
s32 func_00131f40(s32 a, s32 b) {
    D_0052535C = a;
    D_00525354 = D_005252A8;
    D_00525360 = b;
    return func_00131e40(-1);
}
#undef D_00525360
#undef D_00525354
#undef func_00131e40

/* func_00131f78 (from hand/text_00130000_h6.c). */
s32 func_00123488(s32 id);
s32 func_00131f78(s32 key) {
    W6Rec *r = D_00525298.recs;
    s32 i;
    for (i = 0; i < D_00525298.n; i++, r++) {
        if (r->key == key && func_00123488(r->id) == 0) {
            return r->id;
        }
    }
    return -1;
}

/* func_00132008 (from auto/text_00130000_13.c). */
#define func_00123488 ((M2C_UNK (*)(s32, void *)) func_00123488)
void func_00132008(void *arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x130);
    func_00123488(*(M2C_UNK *)((s32) ((M2C_FIELD(temp_a1, s16 *, 0x52) * 0x78)) + (s32) D_005252A8), temp_a1);
}
#undef func_00123488

/* func_00132040 (from hand/text_00130000_h6.c). */
W6Rec *func_00132040(W6Rec *p) {
    s32 i;
    s32 g;
    if (p == 0) {
        g = 0;
    } else {
        g = p->group + 1;
    }
    p = D_00525298.recs;
    for (i = 0; i < D_00525298.n; i++, p++) {
        if (p->group == g) {
            return p;
        }
    }
    return 0;
}

/* func_001320a8 (from hand/text_00130000_h32.c). */
extern W32Tbl D_005252C8;
extern W32Tbl D_005252F8;
extern W32Tbl D_00525328;
extern W32Tbl D_00525298_001320a8 __asm__("D_00525298");
#define D_00525298 D_00525298_001320a8
W32Rec *func_001320a8(u32 a) {
    W32Rec *r;
    s32 n, i;
    switch ((s32)((a >> 16) & 0xFF)) {
    case 7: r = D_005252F8.recs; n = D_005252F8.n; break;
    case 8: r = D_005252C8.recs; n = D_005252C8.n; break;
    case 12: r = D_00525328.recs; n = D_00525328.n; break;
    default: r = D_00525298.recs; n = D_00525298.n; break;
    }
    if (((a >> 16) & 0xFF) == 1) {
        for (i = 0; i < n; i++, r++) {
            if (r->key == (a & 0xFFFF)) return r;
        }
    } else {
        for (i = 0; i < n; i++, r++) {
            if (r->id == a) return r;
        }
    }
    return 0;
}
#undef D_00525298

/* func_001321a0 (from auto/text_00130000_4.c). */
void func_001623d0(s32, s32);
void func_001321a0(s32 arg0, s32 arg1) {
    s32 temp_v1;

    M2C_FIELD(arg0, s32 *, 0) = arg1;
    if (arg1 != 0) {
        func_001623d0(arg1 + M2C_FIELD(arg1, s32 *, 4), arg0 + 4);
        M2C_FIELD(arg0, s32 *, 8) = (s32) (arg1 + M2C_FIELD(arg1, s32 *, 8));
        temp_v1 = M2C_FIELD(arg1, s32 *, 0xC);
        if ((M2C_FIELD(arg1, s32 *, 0x10) - temp_v1) > 0) {
            M2C_FIELD(arg0, s32 *, 0xC) = (s32) (arg1 + temp_v1);
            return;
        }
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
        return;
    }
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
}

/* func_00132220 (from auto/text_00130000_8.c). */
s32 func_00167f68(s32, s32);
void func_00132220(s32 arg0, s32 arg1) {
    func_00167f68(arg0, arg1 + M2C_FIELD(arg1, s32 *, 4));
}

/* func_00132240 (from auto/text_00130000_9.c). */
#define func_00132220 ((M2C_UNK (*)(s32, s32)) func_00132220)
void func_00132240(void *arg0) {
    func_00132220(M2C_FIELD(arg0, s32 *, 0x15C), M2C_FIELD(arg0, s32 *, 0x1D0));
}
#undef func_00132220

/* func_00132260 (from hand/text_00130000_h32.c). */
typedef struct { s32 x0; s32 off[9]; } W32Hdr;
typedef struct {
    u8 pad00[0x68];
    s32 x68;
    u8 pad6c[0x134 - 0x6C];
    s32 x134;
    s32 x138;
    s32 x13c;
    s32 x140;
    u8 pad144[0x154 - 0x144];
    void *x154;
    s32 x158;
    s32 x15c;
    u8 pad160[0x1D0 - 0x160];
    s32 x1d0;
    s32 x1d4;
    u8 pad1d8[0x4A8 - 0x1D8];
    s32 x4a8;
} W32Obj;
void func_00162070(void *a, s32 *b, s32 *c, s32 *d);
void func_001238c0(W32Obj *o, f32 a, f32 b);
#define func_001321a0 ((void (*)(s32 *a, W32Hdr *b)) func_001321a0)
#define func_00167f68 ((void (*)(s32 a, void *b)) func_00167f68)
void func_00132260(W32Obj *o, W32Hdr *h, W32Hdr *g) {
    o->x154 = (u8 *)h + h->off[0];
    func_00162070(o->x154, &o->x158, &o->x1d4, &o->x15c);
    func_001321a0(&o->x1d0, g);
    if (h->off[2] - h->off[1] > 0) o->x68 = (s32)h + h->off[1];
    if (h->off[3] - h->off[2] > 0) o->x140 = (s32)h + h->off[2];
    if (h->off[4] - h->off[3] > 0) o->x13c = (s32)h + h->off[3];
    if (h->off[5] - h->off[4] > 0) {
        f32 *v = (f32 *)((u8 *)h + h->off[4]);
        o->x134 = (s32)v;
        func_001238c0(o, v[3], v[2]);
    }
    if (h->off[6] - h->off[5] > 0) o->x138 = (s32)h + h->off[5];
    else o->x138 = 0;
    if (h->off[8] - h->off[7] > 0) o->x4a8 = (s32)h + h->off[7];
    if (g) func_00167f68(o->x15c, (u8 *)g + g->off[0]);
}
#undef func_001321a0
#undef func_00167f68

/* func_00132550 (from hand/text_00130000_h32.c). */
void func_00176838(void);
void func_0014f1b8(s32 a);
void func_00168500(s32 a);
s32 func_00142240(s32 a);
void func_00124218(s32 a);
void func_0017d9c8(s32 a);
void func_0017eb88(void);
void func_001252f8(void);
void func_00156c18(s32 a);
void func_001590a8(void);
extern f32 D_00304C40;
extern W32Tbl D_00525298_00132550 __asm__("D_00525298");
#define D_00525298 D_00525298_00132550
void func_00132550(void) {
    W32Rec *r;
    s32 i;
    func_00176838();
    func_0014f1b8(D_00525298.x18);
    func_00168500(D_00525298.x24);
    r = D_00525298.recs;
    for (i = 0; i < D_00525298.n; i++, r++) {
        if (!(r->flags & 2) && r->x8 != 0) {
            if (!(r->flags & 0x10000) || func_00142240(r->id) != 1) {
                func_00124218(r->id);
            }
        }
    }
    if (D_00525298.x20) func_0017d9c8(D_00525298.x20);
    if (D_002E26A0[0]) func_0017eb88();
    func_001252f8();
    func_00156c18(D_00525298.x28);
    func_001590a8();
    D_00304C40 = 30.0f;
}
#undef D_00525298

/* func_00132678 (from auto/text_00130000_4.c). */
void func_0015c9f8(s32);
void func_00162058(s32);
void func_001763f0(s32);
void func_00132678(s32 arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    if ((M2C_FIELD(arg0, s32 *, 8) - temp_v0) > 0) {
        func_00162058(arg0 + temp_v0);
    }
    if ((M2C_FIELD(arg0, s32 *, 0xC) - M2C_FIELD(arg0, s32 *, 8)) > 0) {
        func_00162058(arg0 + M2C_FIELD(arg0, s32 *, 8));
    }
    if ((M2C_FIELD(arg0, s32 *, 0x10) - M2C_FIELD(arg0, s32 *, 0xC)) > 0) {
        func_0015c9f8(arg0 + M2C_FIELD(arg0, s32 *, 0xC));
    }
    if ((M2C_FIELD(arg0, s32 *, 0x14) - M2C_FIELD(arg0, s32 *, 0x10)) <= 0) {
        return;
    }
    func_001763f0(arg0 + M2C_FIELD(arg0, s32 *, 0x10));
}

/* func_00132718 (from auto/text_00130000_17.c). */
void func_001149b0(void *);
#define func_0015c9f8 ((void (*)(void *)) func_0015c9f8)
#define func_001763f0 ((void (*)(void *)) func_001763f0)
void func_00132718(void *arg0) {
  s32 temp_v0;
  func_001149b0(arg0 + (*((s32 *) (((s8 *) arg0) + 4))));
  ;
  if (((*((s32 *) (((s8 *) arg0) + 0xC))) - (*((s32 *) (((s8 *) arg0) + 8)))) > 0)
  {
    func_0015c9f8(arg0 + (*((s32 *) (((s8 *) arg0) + 8))));
  }
  if (((*((s32 *) (((s8 *) arg0) + 0x10))) - (*((s32 *) (((s8 *) arg0) + 0xC)))) <= 0)
  {
    return;
  }
  func_001763f0(arg0 + (*((s32 *) (((s8 *) arg0) + 0xC))));
}
#undef func_0015c9f8
#undef func_001763f0

/* func_00132e38 (from auto/text_00130000_8.c). */
M2C_UNK func_00132790(M2C_UNK *, M2C_UNK, M2C_UNK *);
extern M2C_UNK D_002E31F0;
extern M2C_UNK D_003031F0;
#define D_005252C8 (*(M2C_UNK (*)) &D_005252C8)
#define D_005252F8 (*(M2C_UNK (*)) &D_005252F8)
void func_00132e38(void) {
    func_00132790(&D_002E31F0, 0, &D_005252C8);
    func_00132790(&D_003031F0, 0, &D_005252F8);
}
#undef D_005252C8
#undef D_005252F8

/* func_00132e78 (from auto/text_00130000_9.c). */
#define func_00132790 ((M2C_UNK (*)(s32, M2C_UNK, M2C_UNK *)) func_00132790)
#define D_00525328 (*(M2C_UNK (*)) &D_00525328)
extern M2C_UNK (*D_00525364_32e78)(s32) __asm__("D_00525364");
#define D_00525364 D_00525364_32e78
void func_00132e78(s32 arg0, s32 arg1, s32 arg2) {
    func_00132790(arg2, 0, &D_00525328);
    if (D_00525364 != NULL) {
        D_00525364(arg0);
    }
}
#undef D_00525364
#undef func_00132790
#undef D_00525328

/* func_00132ec8 (from auto/text_00130000.c). */
M2C_UNK func_00120748(M2C_UNK *, s32, M2C_UNK *, M2C_UNK);
extern M2C_UNK D_0048D628;
extern s32 D_00525364;
void func_00132ec8(s32 arg0, s32 arg1) {
    D_00525364 = arg1;
    func_00120748(&D_0048D628, arg0, &func_00132e78, 0);
}

