/* Round 41 wwm2: score 126 -> 120, port.py of the wm twin func_00f4c238 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* gb.x func_00f25140 near miss: 70 words differ, score 126; size matches (728 bytes). Resizes the world: re-centres the entity box, shifts every entity's x/z nibbles and the cursor, then stores w/d/h. A 10-minute -j1 permuter run found a zero variable used three times: wd->ents[i].y = wd->ents[i].y + (oz = 0), plus x = oz / z < oz in the cursor clamp. That suggests the original has a zero-valued y offset variable. Left: the original reuses ox/oz's registers (t6/t7) for the cursor x/z, copies the world pointer for the loop's count reload (move a2,t3), and stores h, w, d in that order. Doing the ox/oz reuse by hand (r1) made it worse (187). Bitfields: GbBox x0 as u16 and the rest as u32, plus the f29f10 GbWorld layout. */
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
extern GbWorld *D_00F56DC0;
extern GbRoom *D_00F56DC4;
void func_00f24780(GbRoom *);
void func_00f24240(GbRoom *, s32);

s32 func_00f25140(s32 w, s32 d, s32 h)
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
  if (((D_00F56DC0->w == w) && (D_00F56DC0->d == d)) && (D_00F56DC0->h == h))
  {
    return 0;
  }
  wd = D_00F56DC0;
  if (wd->count != 0)
  {
    ex = (D_00F56DC4->box.x1 - D_00F56DC4->box.x0) + 1;
    ey = (D_00F56DC4->box.y1 - D_00F56DC4->box.y0) + 1;
    ez = (D_00F56DC4->box.z1 - D_00F56DC4->box.z0) + 1;
    ox = ((w - wd->w) / 2) + D_00F56DC4->box.x0;
    oz = ((h - wd->h) / 2) + D_00F56DC4->box.z0;
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
    tx = ox - D_00F56DC4->box.x0;
    tz = oz - D_00F56DC4->box.z0;
    for (i = 0; i < wd->count; i++)
    {
      wd->ents[i].x = wd->ents[i].x + tx;
      wd->ents[i].y = wd->ents[i].y + (oz = 0);
      wd->ents[i].z = wd->ents[i].z + tz;
    }

    x = D_00F56DC0->px + tx;
    z = D_00F56DC0->pz + tz;
    if (x < 0)
    {
      x = oz;
    }
    y = D_00F56DC0->py;
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
    D_00F56DC0->px = x;
    D_00F56DC0->py = y;
    D_00F56DC0->pz = z;
  }
  D_00F56DC0->w = w;
  D_00F56DC0->d = d;
  D_00F56DC0->h = h;
  func_00f24780(D_00F56DC4);
  func_00f24240(D_00F56DC4, 0);
  return 1;
}
