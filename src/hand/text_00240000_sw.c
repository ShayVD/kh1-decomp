#include "common.h"
typedef struct { u64 lo, hi; } QW;
typedef struct { s32 a, b; f32 c; } V12;
typedef struct {
    s32 on;
    V12 v;
    s32 unk10;
} Mgr;
typedef struct { u8 pad[0x9C]; s32 unk9C; } UiObj;
typedef struct { UiObj *p; u8 pad[0x1C]; } UiEnt;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0 - 0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Pkt;
extern Mgr D_00669700;
extern UiEnt D_00669760[3];
Pkt D_006694B0 ALIGNED(16);
QW *D_00669614 ALIGNED(4);
extern QW *D_00669610;
extern QW D_00351E10[];
extern u8 D_004267C0[];
extern u8 D_004267F0[];
void func_002370c8(Pkt *);
void func_00237018(void *, s32, s32);
void func_0011d768(s32);
void func_0024ac68(UiObj *, s32 (*)[4]);
void func_002489c8(s32, UiObj *, void *, void *, s32, s32, s32, s32, f32);

void func_00248840(s32, s32, s32, s32, s32);
void func_002488a8(s32, s32, s32, s32, f32);
void func_0024ac08(s32, void *);
void func_002489c8(s32 arg0, UiObj *arg1, void *arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 fparg0) {
  s32 sp[8];
  s32 temp_s7;
  s32 var_a1;
  s32 var_s0;
  s32 var_s1;
  var_s0 = (s32)arg1;
  *((s32 *) (((s8 *) sp) + 0x10)) = arg7;
  var_s1 = 6;
  temp_s7 = var_s0;
  do
  {
    var_a1 = var_s0;
    var_s0 += 0xC0;
    var_s1 -= 1;
    func_00248840(arg0, var_a1, (s32)arg2, arg4, arg5);
    var_a1 = var_s0;
  }
  while (var_s1 >= 0);
  func_00248840(arg0, var_a1, (s32)arg3, arg4, arg5);
  if (arg6 != 0)
  {
    func_0024ac08(temp_s7, sp);
    func_002488a8(arg4 + (*((s32 *) (((s8 *) sp) + 0x0))), arg5 + (*((s32 *) (((s8 *) sp) + 0x4))), arg6, *((s32 *) (((s8 *) sp) + 0x10)), fparg0);
  }
}

void func_00248b58(s32 arg0) {
    s32 first = 0, done = 0;
    s32 n, fl;
    s32 buf[4][4];
    V12 *v;
    Mgr *m = &D_00669700;
    if (m->on == 0) return;
    v = &m->v;
    func_002370c8(&D_006694B0);
    D_006694B0.unkE0 = 5;
    D_006694B0.unk60 = 0x30003;
    func_00237018(&D_006694B0, 22, 1);
    D_00669614 = D_00351E10;
    D_00669610 = D_00351E10 + 1;
    switch (m->on) {
    case 1:
        m->on = 2;
        func_0011d768(31);
        first = 1;
        break;
    case 2:
        n = ++m->unk10;
        if (v->a == 0) {
            if (n < 61 && (!arg0 || n < 2)) break;
            done = 1;
            m->on = 3;
        } else {
            if (n < 61 && (!arg0 || n < 6)) break;
            done = 1;
            m->on = 3;
        }
        break;
    case 3:
        if (v->a == 0) {
            func_0024ac68(D_00669760[1].p, buf);
            v->c = (f32)buf[0][3] * 0.0078125f;
            if (v->a == 0 && (D_00669760[1].p->unk9C & 4))
                m->on++;
        } else {
            m->on = 4;
        }
        break;
    case 4:
        m->on = 0;
        return;
    }
    v = &D_00669700.v;
    switch (v->a) {
    case 0:
        if (D_00669700.on == 2)
            func_002489c8(first, D_00669760[0].p, D_004267C0, D_004267F0, 160, 344, v->b, 0, v->c);
        else
            func_002489c8(done, D_00669760[1].p, D_004267C0, D_004267F0, 160, 344, v->b, 0, v->c);
        break;
    case 1:
        func_002489c8(first, D_00669760[2].p, D_004267C0, D_004267F0, 160, 344, v->b, 0, v->c);
        break;
    }
    func_00237018(D_00669614, D_00669610 - D_00669614, 1);
}
