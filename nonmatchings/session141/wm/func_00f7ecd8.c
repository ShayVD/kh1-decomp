/* Round 41 wwm2: score 17 -> 11 (5 words + the trailing nop). Reading x10 into v at the bottom test (test: v = D_002C5AD0.x10; } while (!(x8 & 0x2000))) and testing ((v >> 24) | v) & 0x10 at the top (v | v >> 24 gives 13). Left: srl v0,v1 (original srl v1,v0: v and the shift temp swapped), and the load sits in a plain beqz slot (filled from before the branch), where the original has beqzl with the load stolen from the loop top. Writing func_0011d768(2) before m->x34 = sel (the original's order) gives the same score. Every while/for form duplicates the exit test or hoists the D_002C5AD0 address (45-50). */
/* func_00f7ecd8: score 17, 79 words differ. loop entry beqz should be beqzl (loop notes); goto/do-while loses likely, plain while duplicates test; permuter output used */
#include "platform/thread.h"
typedef struct {
    u32 x0;
    u32 x4;
    u32 x8;
    u32 xC;
    u32 x10;
} Pad;

typedef struct {
    s32 x0;
    s32 x4;
    s32 slot[8];
    s32 x28;
    s32 x2C;
    s32 x30;
    s32 x34;
} Menu;

extern Pad D_002C5AD0;
extern u8 D_00FBA7D8[];
s32 func_00f78900(void *, s32);
void func_00f7de08(Menu *, s32, s32);
void func_001bfac8(void);
void func_0011d768(s32);

s32 func_00f7ecd8(Menu *m)
{
  s32 i;
  s32 a;
  s32 sel;
  s32 prev;
  u32 v;
  Menu *new_var;
  if (m->x2C < func_00f78900(D_00FBA7D8, (*m).x28))
  {
    asm volatile("break");
  }
  for (i = 0; i < 8; i++)
  {
    if (m->slot[i] == 0)
    {
      break;
    }
  }

  for (; i < 8; i++)
  {
    m->slot[i] = 0;
  }

  sel = 0;
  prev = 0;
  for (a = 32; a < 128; a += 32)
  {
    func_00f7de08(m, a, 0);
    func_001bfac8();
  }

  new_var = m;
  goto test;
  do
  {
    if (((v >> 24) | v) & 0x10)
    {
      sel--;
      if (sel < 0)
      {
        sel = 5;
      }
      else
        if (m->slot[sel] == 0)
      {
        i = sel;
        while (((--i) >= 0) && (new_var->slot[i] == 0))
        {
        }

        sel = i;
      }
    }
    if ((D_002C5AD0.x10 | (D_002C5AD0.x10 >> 24)) & 0x40)
    {
      if (sel == 5)
      {
        sel = 0;
      }
      else
      {
        sel++;
        if (m->slot[sel] == 0)
        {
          sel = 5;
        }
      }
    }
    func_00f7de08(m, 128, sel);
    if (sel != prev)
    {
      func_0011d768(1);
      prev = sel;
    }
    func_001bfac8();
    test:
    v = D_002C5AD0.x10;
  }
  while (!(D_002C5AD0.x8 & 0x2000));
  m->x34 = sel;
  func_0011d768(2);
  for (a = 96; a >= 0; a -= 32)
  {
    func_00f7de08(m, a, sel);
    func_001bfac8();
  }

  return 0;
}
