/* ppp's maths helpers (docs/modules.md "Session 49"), 0x001a8f08-0x001a9460
 * less the VU0 routines in src/hand/vu0.c, with pppmath.nostrict.c:
 * func_001a8f08 steps a 16-bit LCG (x * 2061 + 7, D_00372760);
 * func_001a8f30 a VU0 random number (0 .. 32767); func_001a8f70 intersects
 * a ray with a sphere (pppKeHitChkPxBFrame); func_001a9058 max(a, b) on VU0;
 * func_001a92f0 x to the n; func_001a9328 a square root; func_001a9350 a
 * vector's length, func_001a93b0 a distance; func_001a93e0 / func_001a9418
 * take from and build a u16 free list of ids.
 * Read from the code, not proved by a boot. */
#include "m2c.h"
#include "platform/vu.h"

extern s32 D_00372760;

void func_001a8f08(void) {
    D_00372760 = ((D_00372760 * 0x80D) + 7) & 0xFFFF;
}

typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) QV;

s32 func_001a8f30(void) {
    f32 r;
    __asm__ volatile(
        "addi $8, $0, -1\n"
        "qmtc2 $8, $vf2\n"
        "vrxor R, $vf2x\n"
        "vitof0.x $vf2x, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vadd.x $vf1x, $vf1x, $vf2x\n"
        "qmfc2 %0, $vf1\n"
        : "=r"(r) : : "$8");
    return r * 32768.0f;
}

typedef struct {
    f32 o[4];
    f32 d[4];
    f32 r;
    f32 t;
} Ray;
f32 func_001a9328(f32);

s32 func_001a8f70(Ray *s) {
    f32 a, b, c, disc;
    s32 ret = 0;
    a = s->d[0] * s->d[0];
    a += s->d[1] * s->d[1];
    a += s->d[2] * s->d[2];
    b = s->d[0] * s->o[0];
    b += s->d[1] * s->o[1];
    b += s->d[2] * s->o[2];
    b *= 2.0f;
    c = s->o[0] * s->o[0];
    c += s->o[1] * s->o[1];
    c += s->o[2] * s->o[2];
    c -= s->r * s->r;
    disc = b * b - a * 4.0f * c;
    c = -b;
    b = 2.0f * a;
    if (!(disc < 0.0f)) {
        ret = 1;
        s->t = (c - func_001a9328(disc)) / b;
    }
    return ret;
}

f32 func_001a9058(f32 a, f32 b) {
    QV r;
    r.x = a;
    r.y = b;
    __asm__ volatile(
        "lqc2 $vf1, %1\n"
        "vmaxy.x $vf1x, $vf1x, $vf1y\n"
        "sqc2 $vf1, %0\n"
        : "=m"(r) : "m"(r));
    return r.x;
}

f32 func_001a92f0(s32 arg0, f32 fparg0) {
    f32 var_f0;
    s32 var_a0;

    var_a0 = arg0;
    var_f0 = 1.0f;
    if (var_a0 > 0) {
        do {
            var_a0 -= 1;
            var_f0 *= fparg0;
        } while (var_a0 != 0);
    }
    return var_f0;
}

f32 func_001a9328(f32 a) {
    QV r;
    f32 o;
    r.y = a;
    __asm__ volatile(
        "lqc2 $vf10, %1\n"
        "vsqrt Q, $vf10y\n"
        "vwaitq\n"
        "cfc2 $2, $vi22\n"
        "mtc1 $2, %0\n"
        : "=f"(o) : "m"(r) : "$2");
    return o;
}

f32 func_001a9350(f32 *v) {
    QV r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vmove.xyz $vf9xyz, $vf10xyz\n"
        "vaddx.y $vf9y, $vf9y, $vf9x\n"
        "vaddy.z $vf9z, $vf9z, $vf9y\n"
        "vsqrt Q, $vf9z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "sqc2 $vf10, %0\n"
        : "=m"(r) : "r"(v));
    return r.x;
}


void func_001a93b0(s32 arg0, s32 arg1) {
    s32 sp[4];
    PlatVu0SubVector(sp, arg0, arg1);
    func_001a9350((f32 *)sp);
}

/* u16 free-list of ids: next[] table at +0, head id at +6 (0xffff = empty). */
typedef struct { u16 *next; u8 pad[2]; u16 cur; } IdList;

s32 func_001a93e0(IdList *l) {
    u16 c;
    if (l->cur == 0xffff) return 0xffff;
    c = l->cur;
    l->cur = l->next[l->cur];
    return c;
}

void func_001a9418(void *arg0, u16 *arg1, s32 arg2) {
  u16 *var_a1;
  u16 temp_a2;
  unsigned int new_var;
  u16 var_v1;
  var_a1 = arg1;
  var_v1 = 1;
  temp_a2 = arg2 & 0xFFFF;
  *((u16 **) (((s8 *) arg0) + 0)) = var_a1;
  new_var = 1U;
  *((s16 *) (((s8 *) arg0) + 6)) = 0;
  *((u16 *) (((s8 *) arg0) + 4)) = temp_a2;
  if (1)
  {
    if (temp_a2 > new_var)
    {
      do
      {
        *var_a1 = var_v1;
        var_v1 = (var_v1 + 1) & 0xFFFF;
        var_a1 += 1;
      }
      while (var_v1 < temp_a2);
    }
    *var_a1 = 0xFFFF;
  }
}

#include "data/data_0037.h"
