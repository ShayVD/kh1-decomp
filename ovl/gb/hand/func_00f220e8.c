/* gb.x func_00f220e8: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; void * b; s32 c; s32 d; s32 e; } C491e0;
typedef struct { C491e0 c; s32 pad; } E491e0;
typedef struct { u8 pad[0x10]; E491e0 ent[5]; s32 pad88; s32 idx; } W491e0;
typedef struct { u64 d; u64 r; } GP491e0;
void func_00f3c168(C491e0 *);
s32 func_00f3f9d0(s32);
s32 func_00f3f9e8(GP491e0 *);
GP491e0 *func_00f3fa80(s32);
void func_00f3fa98(GP491e0 *);
void func_00f3fe80(s32, void *);
extern W491e0 *D_00F56DC0;
extern u8 D_00F60C00[];

E491e0 *func_00f220e8(C491e0 *arg0)
{
  int new_var;
  s32 t0;
  void * t1;
  s32 t2;
  s32 t3;
  E491e0 *e;
  s32 new_var2;
  GP491e0 *p;
  e = &D_00F56DC0->ent[D_00F56DC0->idx];
  func_00f3fe80(10000, D_00F60C00);
  t2 = e->c.c;
  t0 = e->c.a;
  arg0->c = t2;
  t1 = e->c.b;
  t3 = e->c.d;
  arg0->a = t0;
  arg0->d = t3;
  arg0->b = t1;
  arg0->e = e->c.e;
  func_00f3c168(arg0);
  p = func_00f3fa80(func_00f3f9d0(arg0->a));
  p->d = 0x740000007000;
  p->r = 0x18;
  p++;
  p->d = 0x30000;
  p->r = 0x47;
  p++;
  func_00f3fa98(p);
  func_00f3fe80(10000, (void *) func_00f3f9e8(p));
  p = func_00f3fa80(func_00f3f9d0((s32) p));
  p->d = 0x740000007000;
  p->r = 0x18;
  p++;
  p->d = 0x5000D;
  p->r = 0x47;
  p++;
  p->d = 0x44;
  p->r = 0x42;
  p++;
  func_00f3fa98(p);
  func_00f3fe80(11840, (void *) func_00f3f9e8(p));
  p = func_00f3fa80(func_00f3f9d0((s32) p));
  p->d = 0x740000007000;
  p->r = 0x18;
  p++;
  if (2 != (*((s16 *) (((u8 *) D_00F56DC0) + 0x76))))
  {
    new_var = 0x30003;
    p->d = new_var;
    p->r = 0x47;
    p++;
    p->d = 0x46;
    p->r = 0;
    p++;
    p->d = (u64) 0x3F800000;
    p->d = p->d << 32;
    p->r = 1;
    p++;
    p->d = 0x74007000;
    p->r = 5;
    p++;
    p->d = 0x8C009000;
    p->r = 5;
    p++;
  }
  p->d = 0x5000D;
  p->r = 0x47;
  p++;
  func_00f3fa98(p);
  func_00f3fe80(12560, (void *) func_00f3f9e8(p));
  arg0->a = (s32) p;
  return e;
}
