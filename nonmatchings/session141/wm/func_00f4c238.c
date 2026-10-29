/* 67 words, score 120 (was 70/126). Round 32 wwm2: hill2 moved the `D_00F9B540->h = h` store down two lines; ctx2 gives nothing. Earlier header: 70 words, score 126. Direct port of the gb twin near miss (nonmatchings/session141/gb/func_00f25140.c); wm gives exactly the same diff, so both should fall together. The wm target shows the cursor clamp reusing the ox/oz registers (t6/t7) and no zero variable in the loop; rewriting it that way (ox = px + tx, no y update) made it worse (166+ words) because the y nibble rewrite in the loop disappears. */
typedef struct {
    u16 x : 4;
    u16 y : 4;
    u16 z : 4;
    u16 r : 4;
    u8 pad2[10];
} GbEnt;
typedef struct {
    u8 pad0[0x58];
    u64 lo : 32;
    u16 px : 4;
    u16 py : 4;
    u16 pz : 4;
    u16 pr : 4;
    u16 pad5e;
    u8 pad60[0xA4 - 0x60];
    u16 count;
    u16 w;
    u16 d;
    u16 h;
    u8 padac[0x110 - 0xAC];
    GbEnt ents[1];
} GbWorld;
typedef struct {
    u16 x0 : 4;
    u32 y0 : 4;
    u32 z0 : 4;
    u32 pad : 4;
    u32 x1 : 4;
    u32 y1 : 4;
    u32 z1 : 4;
} GbBox;
typedef struct {
    u8 pad0[4];
    GbBox box;
} GbRoom;
extern GbWorld *D_00F9B540;
extern GbRoom *D_00F9B544;
void func_00f4b878(GbRoom *);
void func_00f4b338(GbRoom *, s32);

s32 func_00f4c238(s32 w, s32 d, s32 h)
{
  s32 ex;
  s32 ey;
  s32 ez;
  s32 ox;
  s32 oz;
  s32 tx;
  s32 tz;
  s32 i;
  s32 x;
  s32 y;
  s32 z;
  GbWorld *wd;
  GbEnt *e;
  if (((D_00F9B540->w == w) && (D_00F9B540->d == d)) && (D_00F9B540->h == h))
  {
    return 0;
  }
  wd = D_00F9B540;
  if (wd->count != 0)
  {
    ex = (D_00F9B544->box.x1 - D_00F9B544->box.x0) + 1;
    ey = (D_00F9B544->box.y1 - D_00F9B544->box.y0) + 1;
    ez = (D_00F9B544->box.z1 - D_00F9B544->box.z0) + 1;
    ox = ((w - wd->w) / 2) + D_00F9B544->box.x0;
    oz = ((h - wd->h) / 2) + D_00F9B544->box.z0;
    if (((w < ex) || (d < ey)) || (h < ez))
    {
      return 0;
    }
    if (ox < 0)
    {
      ox = 0;
    }
    if (oz < 0)
    {
      oz = 0;
    }
    if (w < (ox + ex))
    {
      ox = w - ex;
    }
    if (h < (oz + ez))
    {
      oz = h - ez;
    }
    tx = ox - D_00F9B544->box.x0;
    tz = oz - D_00F9B544->box.z0;
    for (i = 0; i < wd->count; i++)
    {
      wd->ents[i].x = wd->ents[i].x + tx;
      wd->ents[i].y = wd->ents[i].y + (oz = 0);
      wd->ents[i].z = wd->ents[i].z + tz;
    }

    x = D_00F9B540->px + tx;
    z = D_00F9B540->pz + tz;
    if (x < 0)
    {
      x = oz;
    }
    y = D_00F9B540->py;
    if (x > (w - 1))
    {
      x = w - 1;
    }
    if (y > (d - 1))
    {
      y = d - 1;
    }
    if (z < oz)
    {
      z = oz;
    }
    if (z > (h - 1))
    {
      z = h - 1;
    }
    D_00F9B540->px = x;
    D_00F9B540->py = y;
    D_00F9B540->pz = z;
  }
  D_00F9B540->w = w;
  D_00F9B540->d = d;
  D_00F9B540->h = h;
  func_00f4b878(D_00F9B544);
  func_00f4b338(D_00F9B544, 0);
  return 1;
}
