/* 23 words differ, score 41 (1052 vs 1056 bytes; round 30 wgb: CONTEXT_ONLY func_00f29658 (ctx2) and parameters in the callers' order (..., f32 al, f32 sc, s32 flags), was 24/43); logic complete (frustum cull + lod switch, case 1/default shared). Left: FPU register choice in the cull block (orig rad f9, z f11, 1.0f f10, ry f8), the final lod select (orig bc1t with li 1 in delay slot, then move 0), beqz vs beqzl in the switch tree. Tried: reciprocal temps, rx/ry order, 5 lod forms, case order, store placement; 10 min permuter found the new_var cx->x8 temp (49 -> 43) */
typedef struct 
{
  s32 x0;
  u8 *x4;
  s32 x8;
  s32 xC;
  s32 x10;
} Ctx29;
extern Ctx29 *D_00F85160;
extern s32 D_00F8C23C;
extern f32 D_00F85180[4][4];
extern f32 D_00F85200[4][4];
extern f32 D_00F87280[4][4];
extern f32 D_00F872C0[4][4];
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void func_00f5df38(s32, s32, s32 *);
void func_00f5de50(s32 *, s32);
void func_00f5e6e0(s32 *);
u8 *func_00f29698(s32 *, u8 *, u8 *, s32);
CONTEXT_ONLY u8 *func_00f29658(s32 *a0, u8 *a1, u8 *a2, s32 a3) { return 0; }
u8 *func_00f296d8(s32 *, u8 *, u8 *, s32);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
u64 *func_00f66b20(s32);
s32 func_00f66b38(u64 *);
s32 func_00f667b8(s32, s32, s32);
void func_00f29dc0(s32 id, f32 (*w)[4], f32 (*b)[4], u8 *obj, f32 al, f32 sc, s32 flags)
{
  f32 t[4][4];
  f32 a[4][4];
  f32 m[4][4];
  Ctx29 *cx;
  s32 lod;
  f32 rad;
  f32 z;
  f32 d;
  f32 rx;
  f32 ry;
  f32 sx;
  f32 sy;
  u64 *p;
  s32 q;
  s32 new_var;
  s32 s;
  sceVu0MulMatrix(t, D_00F85200, w);
  sceVu0MulMatrix(m, D_00F85180, t);
  lod = 2;
  if (!(flags & 1))
  {
    lod = 1;
    if (D_00F8C23C == 0)
    {
      rad = *((f32 *) (obj + 200));
      z = t[3][2];
      if (z < ((-rad) * 0.2f))
      {
        return;
      }
      d = z - rad;
      if (1.0f < d)
      {
        d = 1.0f / d;
        rx = ((D_00F85180[0][0] * rad) * d) + 260.0f;
        ry = ((D_00F85180[1][1] * rad) * d) + 200.0f;
        d = 1.0f / z;
        sx = (m[3][0] * d) - 2048.0f;
        sy = (m[3][1] * d) - 2048.0f;
        if (sx < (-rx))
        {
          return;
        }
        if (rx < sx)
        {
          return;
        }
        if (sy < (-ry))
        {
          return;
        }
        if (ry < sy)
        {
          return;
        }
      }
      lod = 0;
      if (z < (rad * 1.5f))
      {
        lod = 1;
      }
    }
  }
  cx = D_00F85160;
  func_00f5df38(id, id + 1, &cx->x8);
  func_00f5de50(&cx->x8, 0);
  sceVu0CopyMatrix((void *) (cx->x4 + 144), m);
  if (flags & 2)
  {
    a[0][0] = 0.0f;
    a[0][1] = 0.0f;
    a[0][2] = 0.0f;
    a[0][3] = 0.0f;
    a[1][0] = 0.0f;
    a[1][1] = 0.0f;
    a[1][2] = 0.0f;
    a[1][3] = 0.0f;
    a[2][0] = 0.0f;
    a[2][1] = 0.0f;
    a[2][2] = 0.0f;
    a[2][3] = 0.0f;
    a[3][0] = 1.0f;
    a[3][1] = 1.0f;
    a[3][2] = 1.0f;
    a[3][3] = al;
    sceVu0CopyMatrix((void *) (cx->x4 + 16), a);
  }
  else
  {
    sceVu0CopyMatrix((void *) (cx->x4 + 16), D_00F872C0);
  }
  ((f32 *) (cx->x4 + 64))[0] *= sc;
  ((f32 *) (cx->x4 + 64))[1] *= sc;
  ((f32 *) (cx->x4 + 64))[2] *= sc;
  sceVu0MulMatrix((void *) (cx->x4 + 80), D_00F87280, b);
  ((f32 *) (cx->x4 + 64))[3] = al;
  switch (lod)
  {
    case 0:
      cx->x4 = func_00f29698(&cx->x8, cx->x4, obj, 0);
      break;

    case 1:

    default:
      cx->x4 = func_00f29658(&cx->x8, cx->x4, obj, 0);
      break;

    case 2:
      p = (u64 *) D_00F85160->x0;
      q = (s32) p;
      p = func_00f66b78(func_00f66b20(q));
      p[0] = 68;
      p[1] = 66;
      p += 2;
      p[0] = 0x5010D;
      p[1] = 71;
      p += 2;
      p[0] = 96;
      p[1] = 20;
      p += 2;
      p[0] = 0;
      p[1] = 8;
      p += 2;
      func_00f66b90(p);
      s = func_00f66b38(p);
      new_var = cx->x8;
      D_00F85160->x0 = (s32) p;
      cx->x8 = func_00f667b8(new_var, q, s);
      cx->xC = func_00f667b8(cx->xC, q, s);
      cx->x10 = func_00f667b8(cx->x10, q, s);
      cx->x4 = func_00f296d8(&cx->x8, cx->x4, obj, 0);
      break;

  }

  func_00f5e6e0(&cx->x8);
}
