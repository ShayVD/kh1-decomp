/* Round 41 (wgb): score 31 -> 29, statement order from hill3 (120 s, seed 41, default mode). Earlier header below. */
/* Round 42 wwm2: score 35 -> 31, port.py of the wm twin func_00f696a0 draft. Earlier header below. */
/* 25 words / score 35 (permuter round 3, from 30/39). Left: s5/s7 swap for the two zeroed counters, and the stack-store schedule of the f41dc8 argument block. Tried every assignment order, declaration order, and a hill-climb on the store schedule. */
extern s32 D_00F82A88;
extern s32 D_00F82A9C;
s32 func_00f42180(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f41dc8(s32 *, s32 *, s32 *, s32 *, s32, s32, f32 *, f32 *, s32, s32, s32, u64, s32, u64);
void func_00f425a8(s32 tex0, s32 tex1, s32 x, s32 y, s32 w, s32 h, s32 psm, s32 a7, f32 s, s32 flip, u64 a9, s32 a10, u64 a11)
{
  s32 xs[4];
  s32 ys[4];
  s32 zs[4];
  s32 ws[4];
  f32 us[4];
  s32 new_var2;
  f32 vs[4];
  s32 a;
  s32 b;
  s32 c;
  int new_var;
  s32 k;
  s32 p;
  s32 d;
  s32 e;
  switch (psm)
  {
    case 4:
      k = 20;
      a = 2;
      b = 8;
      c = (w * h) / 128;
      break;

    case 8:
      k = 19;
      c = (w * h) / 64;
      b = 16;
      a = 16;
      break;

    default:
      k = (b = 0);
      a = 0;
      c = 0;
      break;

  }

  if (tex0)
  {
    D_00F82A88 = func_00f42180(D_00F82A88, tex0, 0, 0, w, h, D_00F82A9C, k, w / 64, psm);
  }
  if (tex1)
  {
    D_00F82A88 = func_00f42180(D_00F82A88, tex1, 0, 0, b, a, D_00F82A9C + c, 0, 1, 32);
  }
  x += 1792;
  x <<= 4;
  y += 1856;
  y <<= 4;
  new_var = 2;
  d = (s32) (s * w);
  if (flip == 0)
  {
    d = x + (d << 4);
    xs[3] = x;
  }
  else
  {
    d = x - (d << 4);
    xs[3] = x;
  }
  new_var2 = ((s32) (s * h)) << 4;
  ws[1] = 1;
  ys[3] = y;
  xs[1] = d;
  xs[0] = d;
  ys[1] = y;
  ws[3] = 1;
  e = y + new_var2;
  ws[0] = 1;
  ys[0] = e;
  ys[new_var] = e;
  ws[new_var] = 1;
  xs[new_var] = x;
  for (p = new_var; p < h; p <<= 1)
  {
    ;
  }

  vs[0] = ((f32) (h - 1)) / ((f32) p);
  us[3] = 0.0f;
  vs[3] = 0.0f;
  us[new_var] = 0.0f;
  vs[new_var] = vs[0];
  us[1] = 1.0f;
  vs[1] = 0.0f;
  us[0] = 1.0f;
  func_00f41dc8(xs, ys, zs, ws, w, p, us, vs, k, c, a7, a9, a10, a11);
}
