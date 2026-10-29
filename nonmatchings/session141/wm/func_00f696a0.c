/* Round 42 wwm2: score 35 -> 31, store order from r42/hill3o.py (score-ranked, dependency-safe, distinct array elements may swap): ws[1] and ys[3] before xs[0], xs[new_var] last. The float-store block (us/vs) gave nothing in 300 iterations. Earlier header below. */
/* Round 41 wwm2: score 166 -> 35, port.py of the gb twin func_00f425a8 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* Round 36 (wwm2): wm.x func_00f696a0 near miss: score 178 -> 166 (173 -> 175 words, 760 vs 752); statement order from the score-ranked dependency-safe hill3 (r35/hill3.py, 120 s, seed 362). Earlier header below. */
extern s32 D_0108F248;
extern s32 D_0108F25C;
s32 func_00f69278(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f68ec0(s32 *, s32 *, s32 *, s32 *, s32, s32, f32 *, f32 *, s32, s32, s32, u64, s32, u64);
void func_00f696a0(s32 tex0, s32 tex1, s32 x, s32 y, s32 w, s32 h, s32 psm, s32 a7, f32 s, s32 flip, u64 a9, s32 a10, u64 a11)
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
      a = 2;
      b = 8;
      c = (w * h) / 128;
      k = 20;
      break;

    case 8:
      k = 19;
      b = 16;
      a = 16;
      c = (w * h) / 64;
      break;

    default:
      c = 0;
      k = (b = 0);
      a = 0;
      break;

  }

  if (tex0)
  {
    D_0108F248 = func_00f69278(D_0108F248, tex0, 0, 0, w, h, D_0108F25C, k, w / 64, psm);
  }
  if (tex1)
  {
    D_0108F248 = func_00f69278(D_0108F248, tex1, 0, 0, b, a, D_0108F25C + c, 0, 1, 32);
  }
  x += 1792;
  x <<= 4;
  y += 1856;
  y <<= 4;
  new_var = 2;
  d = (s32) (s * w);
  if (flip == 0)
  {
    xs[3] = x;
    d = x + (d << 4);
  }
  else
  {
    xs[3] = x;
    d = x - (d << 4);
  }
  new_var2 = ((s32) (s * h)) << 4;
  ws[1] = 1;
  ys[3] = y;
  xs[0] = d;
  ys[1] = y;
  xs[1] = d;
  ws[0] = 1;
  ws[3] = 1;
  e = y + new_var2;
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
  us[0] = 1.0f;
  vs[1] = 0.0f;
  func_00f68ec0(xs, ys, zs, ws, w, p, us, vs, k, c, a7, a9, a10, a11);
}
