/* The party members' items and equipment against the save data D_00304BE8:
 * using a recovery item (func_00149170, func_00149440), the equipped weapon
 * (func_00149740), and the three member weapon models D_0054C1B0
 * (func_00149c80 loads one by name, func_00149f10 swaps one, the callback
 * D_0054C210). Flag mode: default (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "common.h"
#include "platform/math.h"
#include "data/bss_0054.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/text_00140000_h34.h"
#include "m2c.h"
#include "data/pieces/D_002E26A0.h"
#include "actor.h"
#include "data/pieces/D_00350D88.h"
#include "data/bss_0053.h"
#include "vm/script_vm.h"
#include "data/types/text_00140000_h8.h"
#include "data/pieces/D_0035C710.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_00350CE8.h"
#include "data/pieces/D_00304C70.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_002E27C8.h"

/* func_00148fb0 (from hand/text_00140000_h34.c). */
typedef W606Mem_304be8 W34Member;
typedef struct { u8 pad[0x3c]; s32 cur; s32 max; s32 mcur; s32 mmax; } W34St;
typedef union { u64 x; struct { u32 lo; u32 l19:19; u32 b51:1; u32 hi:12; } b; } W34F370;
typedef struct { u8 pad[0x6c]; W34St *st; u8 pad70[0x370 - 0x70]; W34F370 x370; } W34Act;
W34Act *func_00123488(u32);
void func_00141468(W34Act *, s32);
/* 0x149170: use a recovery item (needs func_00148fb0 defined above) */
s32 func_00148fb0(u32 id, s32 add) {
    W34Act *a = func_00123488(id);
    if (a) {
        if (a->st->cur < a->st->max) {
            func_00141468(a, add);
            return 1;
        }
    } else if (((id >> 16) & 0xff) == 1) {
        u32 i = id & 0xffff;
        if (i < 10) {
            W34Member *m = &D_00304BE8->m[i];
            if (m->sub.x1 < m->sub.hpmax) {
                s32 v = m->sub.x1 + add;
                m->sub.x1 = (v < m->sub.hpmax) ? v : m->sub.hpmax;
                return 1;
            }
        }
    }
    return 0;
}

/* func_00149090 (from hand/text_00140000_h34.c). */
void func_00141540(W34Act *, s32);
s32 func_00149090(u32 id, s32 add) {
    W34Act *a = func_00123488(id);
    if (a) {
        if (a->st->mcur < a->st->mmax) {
            func_00141540(a, add);
            return 1;
        }
    } else if (((id >> 16) & 0xff) == 1) {
        u32 i = id & 0xffff;
        if (i < 10) {
            W34Member *m = &D_00304BE8->m[i];
            if (m->sub.x3 < m->sub.mpmax) {
                s32 v = m->sub.x3 + add;
                m->sub.x3 = (v < m->sub.mpmax) ? v : m->sub.mpmax;
                return 1;
            }
        }
    }
    return 0;
}

/* func_00149170 (from hand/text_00140000_h34.c). */
typedef W606Mem_304be8 W34Mem8;
typedef struct { u8 pad[6]; s16 x6; } C4R;
C4R *func_00147840(s32);
s32 func_00149170(s32 a, u32 b) {
    C4R *q;
    W34Mem8 *p;
    s32 r;
    s32 v;

    q = func_00147840(a);
    p = (((b >> 16) & 0xff) == 1 && (b & 0xffff) < 10) ? &D_00304BE8->m[b & 0xffff] : 0;
    r = 0;
    switch (a) {
    case 1: case 2: case 6:
        if (func_00148fb0(b, q->x6)) r = 2;
        break;
    case 142:
        if (func_00148fb0(b, 9999)) r = 2;
        break;
    case 3: case 7:
        if (func_00149090(b, q->x6)) r = 4;
        break;
    case 143:
        r = func_00148fb0(b, 9999) ? 8 : 0;
        if (func_00149090(b, q->x6)) r |= 8;
        break;
    case 4: case 8: case 144:
        r = func_00148fb0(b, 9999) ? 8 : 0;
        if (func_00149090(b, 9999)) r |= 8;
        break;
    case 152:
        if (p && p->sub.x6 < 100) {
            p->sub.x6 = (p->sub.x6 + q->x6 > 100) ? 100 : p->sub.x6 + q->x6;
            r = 16;
        }
        break;
    case 153:
        if (p && p->sub.x7 < 100) {
            p->sub.x7 = (p->sub.x7 + q->x6 > 100) ? 100 : p->sub.x7 + q->x6;
            r = 32;
        }
        break;
    case 154:
        if (p && p->sub.x5 < 100) {
            p->sub.x5 = (p->sub.x5 + q->x6 > 100) ? 100 : p->sub.x5 + q->x6;
            r = 64;
        }
        break;
    }
    return r;
}

/* func_00149600 (from auto/text_00140000_5.c). */
M2C_UNK func_00141e68(s32);
s32 func_0013daa8(s32);
#define func_00149170 ((M2C_UNK (*)(s32, s32)) func_00149170)
void func_00149600(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_0013daa8(arg1);
    if (temp_v0 >= 0) {
        func_00141e68(*(M2C_UNK *)((s8 *)&D_002E26A0 + (temp_v0 * 4)));
    }
    func_00149170(arg0, arg1 | 0x10000);
}
#undef func_00149170

/* func_00149660 (from auto/text_00140000_10.c). */
#define func_00149170 ((s32 (*)(s32, s32)) func_00149170)
void func_00149660(s32 arg0, s32 arg1) {
    func_00149170(arg0, M2C_FIELD(arg1, s32 *, 4));
}
#undef func_00149170

/* func_00149678 (from hand/text_00140000_h8.c). */
s32 func_00149678(void) {
    switch (D_00304BE8->m[0].sub.x32) {
    case 88:
    case 91:
    case 99:
        return 0;
    case 82:
    case 86:
    case 89:
    case 94:
    case 95:
    case 97:
    case 100:
    case 102:
        return 2;
    default:
        return 1;
    }
}

/* func_001496c8 (from hand/text_00140000_h8.c). */
typedef struct { u8 pad[6]; s16 x6; } W8H6;
typedef struct { u8 pad[88]; } W8E88;
u8 *func_001477c8(s32 a);
#define func_00147840 ((W8H6 *(*)(s32)) func_00147840)
W8E88 *func_001496c8(s32 a, s32 b) {
    s32 n;
    if (!b) return 0;
    n = func_00147840(b)->x6;
    if (!n) return 0;
    return &((W8E88 *)func_001477c8(((s32 *)&D_00350CE8)[a]))[n - 1];
}
#undef func_00147840

/* func_00149740 (from auto/text_00140000_4.c). */
#define func_001496c8 ((s32 (*)(s32, s32)) func_001496c8)
s32 func_00149740(s32 arg0) {
    return func_001496c8(arg0, (s32) M2C_FIELD(((arg0 * 0x74) + ((s32)D_00304BE8)), u8 *, 0x36));
}
#undef func_001496c8

/* func_00149780 (from hand/text_00140000_h8.c). */
typedef struct { u32 x0; s32 x4; u8 pad8[4]; s32 xc; s32 x10; u8 pad14[0xc]; } W8E32;
extern W8E32 D_0054C1B0[];
W8E32 *func_00149780(s32 a) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if ((D_0054C1B0[i].x0 & 1) && D_0054C1B0[i].x4 == a) return &D_0054C1B0[i];
    }
    return 0;
}

/* func_001497c8 (from hand/text_00140000_h8.c). */
s32 func_001497c8(s32 a) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if (D_0054C1B0[i].x10 == a) return i;
    }
    return -1;
}

/* func_00149810 (from hand/text_00140000_h8.c). */
typedef struct { u8 pad[0xc]; f32 xc; } W8Fc;
typedef struct { u8 pad[0x8]; f32 *x8; W8Fc *xc; u8 pad10[0x14 - 0x10]; u32 x14; u8 pad18[0x30 - 0x18]; s32 x30; u8 pad34[0x38 - 0x34]; s32 x38; } W8O60;
extern W8O60 D_0054C218[];
W8O60 *func_00149810(void) {
    s32 i;
    for (i = 0; i < 9; i++) {
        if (!(D_0054C434 & (1 << i))) {
            D_0054C434 |= 1 << i;
            return &D_0054C218[i];
        }
    }
    return 0;
}

/* func_00149860 (from hand/text_00140000_h34.c). */
typedef struct { u8 pad[0x4]; s32 x4; s32 x8; } W34R10;
typedef struct {
    u32 b0:1;
    u32 cnt:2;
    u32 r:29;
    s32 x4;
    s32 x8;
    s32 xc;
    W34R10 *x10;
    s32 x14;
    s32 x18;
    void (*x1c)(s32);
} W34E32;
typedef struct { u8 pad[0x4c]; u16 x4c; } W34O130;
typedef struct { u8 pad[0x130]; W34O130 *x130; u8 pad134[0x18]; W34E3C *x14c; u8 pad150[0x370 - 0x150]; u64 x370; } W34Obj;
void func_00162110(s32, void *);
void func_00176358(s32, s32);
extern W34E3C D_0054C218_00149860[] __asm__("D_0054C218");
#define D_0054C218 D_0054C218_00149860
#define func_00149780 ((W34E32 *(*)(s32 a)) func_00149780)
void func_00149860(W34Obj *o) {
    W34E3C *e = o->x14c;
    if (e) {
        s32 i = e - D_0054C218;
        W34E32 *s;
        if (e->x0) func_00162110(e->x0, e->x8);
        s = func_00149780(o->x130->x4c);
        s->cnt--;
        if (s->cnt == 1) {
            func_00176358(s->x18, s->x10->x8 - s->x10->x4);
            s->cnt = 0;
        }
        o->x14c = 0;
        D_0054C434 &= ~(1 << i);
    }
}
#undef D_0054C218
#undef func_00149780

/* func_00149968 (from auto/text_00140000_16.c). */
#define D_0054C1B0 (*(s32 (*)) &D_0054C1B0)
void func_00149968(void) {
  s32 *var_v1;
  s32 var_a0;
  int new_var;
  new_var = ~6;
  var_v1 = &D_0054C1B0;
  var_a0 = 2;
  do
  {
    var_a0 -= 1;
    *var_v1 &= new_var;
    var_v1 += 8;
  }
  while (var_a0 >= 0);
}
#undef D_0054C1B0

/* func_001499a0 (from hand/text_00140000_h34.c). */
void func_00162070(s32, void *, s32, s32);
#define func_00149780 ((W34E32 *(*)(s32 a)) func_00149780)
#define func_00149810 ((W34E3C *(*)(void)) func_00149810)
W34E3C *func_001499a0(W34Obj *o) {
    s32 id = o->x130->x4c;
    W34E32 *s = func_00149780(id);
    if (s) {
        if (s->x8 > 0) {
            W34E3C *e;
            o->x370 |= 1LL << 36;
            e = func_00149810();
            e->x14 = s->x18;
            e->x18 = func_00149740(id);
            e->x28 = 0;
            e->x29 = 0;
            e->x2c = 0;
            e->x0 = s->x14;
            if (e->x0) func_00162070(e->x0, e->x4, 0, 0);
            s->cnt++;
            return e;
        }
    }
    return 0;
}
#undef func_00149780
#undef func_00149810

/* func_00149a88 (from hand/text_00140000_h34.c). */
typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; } W34Hdr;
void func_00162058(void *);
void func_001763f0(void *);
extern W34E32 D_0054C1B0_00149a88[] __asm__("D_0054C1B0");
#define D_0054C1B0 D_0054C1B0_00149a88
#define func_001497c8 ((s32 (*)(W34Hdr *)) func_001497c8)
void func_00149a88(s32 a, s32 b, W34Hdr *h) {
    W34E32 *e = &D_0054C1B0[func_001497c8(h)];
    u8 *p = (u8 *)h + h->x8;
    u8 *q;
    if (h->xc - h->x8 > 0) {
        e->x14 = (s32)p;
        func_00162058(p);
    } else {
        e->x14 = 0;
    }
    q = (u8 *)h + h->x4;
    if (h->x8 - h->x4 > 0) {
        e->x18 = (s32)q;
        func_001763f0(q);
    } else {
        e->x18 = 0;
    }
    if (e->x1c) e->x1c(e->x4);
}
#undef D_0054C1B0
#undef func_001497c8

/* func_00149b40 (from hand/text_00140000_h8.c). */
typedef struct { u8 pad[4]; s32 x4; s32 x8; u8 padc[4]; s32 x10; } W8Q;
extern char D_0048E410[];
extern u8 D_0048E408[];
s32 D_00350D10 ALIGNED(16) = (s32)D_0048E408;  /* moved from hand/text_00140000_h8.c (session 53) */
s32 sprintf(char *, const char *, ...);
void func_00120748(char *, s32, void *, s32);
void func_00149b40(W8Q *q) {
    char buf[32];
    u8 *base = func_001477c8(((s32 *)&D_00350CE8)[q->x4]);
    sprintf(buf, D_0048E410, &((W8E88 *)base)[q->x8 - 1], D_00350D10);
    func_00120748(buf, q->x10, func_00149a88, 0);
}

/* func_00149bd0 (from hand/text_00140000_h34.c). */
void func_00146928(s32);
void func_00146a68(W34Hdr *, s32, void (*)(W34E32 *), W34E32 *);
extern W34E32 D_0054C1B0_00149bd0[] __asm__("D_0054C1B0");
#define D_0054C1B0 D_0054C1B0_00149bd0
#define func_001497c8 ((s32 (*)(W34Hdr *)) func_001497c8)
#define func_00149b40 ((void (*)(W34E32 *)) func_00149b40)
void func_00149bd0(s32 n, s32 b, W34Hdr *h) {
    s32 i = func_001497c8(h);
    if (n > 0) {
        func_00146928(-3 - i);
        func_00146a68(h, -3 - i, func_00149b40, &D_0054C1B0[i]);
    } else {
        func_00149b40(&D_0054C1B0[i]);
    }
}
#undef D_0054C1B0
#undef func_001497c8
#undef func_00149b40

/* func_00149e60 (from auto/text_00140000_2.c). */
#define func_001499a0 ((s32 (*)(void *)) func_001499a0)
#define func_00123488 ((void *(*)(s32)) func_00123488)
extern s32 (*D_0054C210_49e60)() __asm__("D_0054C210");
#define D_0054C210 D_0054C210_49e60
void func_00149e60(s32 arg0) {
    void *temp_v0;

    temp_v0 = func_00123488(arg0 | 0x10000);
    M2C_FIELD(temp_v0, s32 *, 0x14C) = func_001499a0(temp_v0);
    if (D_0054C210 != NULL) {
        D_0054C210();
    }
    D_0054C210 = NULL;
}
#undef D_0054C210
#undef func_001499a0
#undef func_00123488

/* func_00149eb8 (from auto/text_00140000_16.c). */
#define func_00147840 ((s32 (*)(s32)) func_00147840)
s32 func_00149eb8(s32 arg0) {
  s32 temp_a0;
  int new_var;
  temp_a0 = (*((u8 *) (func_00147840(arg0) + 2))) - 2;
  new_var = ((s32)D_00304BE8) + (temp_a0 * 0x74);
  *((s8 *) (((s8 *) new_var) + 0x36)) = (s8) arg0;
  return temp_a0;
}
#undef func_00147840

/* func_00149f10 (from hand/text_00140000_h8.c). */
s32 func_00149c80(s32, void *);
extern void *D_0054C210;
#define func_00123488 ((s32 (*)(s32)) func_00123488)
#define func_00149860 ((void (*)(s32)) func_00149860)
void func_00149f10(s32 a, void (*cb)(void)) {
    s32 id = func_00149eb8(a);
    s32 r = func_00123488(id | 0x10000);
    if (r) {
        func_00149860(r);
        D_0054C210 = cb;
        if (!func_00149c80(id, func_00149e60)) func_00149e60(id);
    } else {
        cb();
    }
}
#undef func_00123488
#undef func_00149860

/* func_00149fa0 (from hand/text_00140000_h34.c). */
extern void (*D_0054C438)(s32);
#define func_00149c80 ((s32 (*)(s32, void (*)(void))) func_00149c80)
void func_00149fa0(void) {
    while (D_0054C43C < 3) {
        s32 c = D_00304BE8->x48e[D_0054C43C++];
        if (c != 0xff && func_00149c80(c, func_00149fa0)) return;
    }
    if (D_0054C438) D_0054C438(-1);
}
#undef func_00149c80

/* func_0014a058 (from auto/text_00140000_4.c). */
extern s32 D_0054C438_0014a058 __asm__("D_0054C438");
#define D_0054C438 D_0054C438_0014a058
#define func_00149fa0 ((s32 (*)(void)) func_00149fa0)
s32 func_0014a058(s32 arg0) {
    func_00149968();
    D_0054C438 = arg0;
    D_0054C43C = 0;
    return func_00149fa0();
}
#undef D_0054C438
#undef func_00149fa0

/* func_0014a090 (from hand/text_00140000_h8.c). */
extern u8 D_006A0000[];
extern s32 D_00350D18[];
void func_0014a090(void) {
    s32 i;
    s32 p = (s32)D_006A0000;
    for (i = 0; i < 3; i++) {
        D_0054C1B0[i].x10 = p;
        D_0054C1B0[i].x0 &= ~1;
        D_0054C1B0[i].xc = D_00350D18[i];
        p += D_00350D18[i];
    }
    D_0054C210 = 0;
    D_0054C434 = 0;
}

