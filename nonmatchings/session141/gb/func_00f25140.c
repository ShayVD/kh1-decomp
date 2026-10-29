/* gb.x func_00f25140 near miss: 130 words differ, score 161 (ours 724 bytes, original 728). Resizes the world: re-centres the entity box, shifts every entity's x/z nibbles and the cursor, then stores w/d/h. Logic is complete. Helpful forms: oz -= z0 reuse (a permuter find, 217 -> 165), indexed wd->ents[i] with y = y + 0 (the original keeps the y re-insert), and the loop bound reading D_00F56DC0->count. Left: the original has a 5th saved reg (tz in s0 separate from oz, with s3/s4 holding the D_00F56DC0 and D_00F56DC4 hi parts) and copies the world pointer for the count reload (move a2,t3). Bitfields: GbBox x0 as u16 and the rest as u32, plus the f29f10 GbWorld layout (u64 lo:32 then u16 px/py/pz). */
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

s32 func_00f25140(s32 w, s32 d, s32 h) {
    s32 ex, ey, ez, ox, oz, tx, tz, i, x, y, z;
    GbWorld *wd;
    GbEnt *e;
    if (D_00F56DC0->w == w && D_00F56DC0->d == d && D_00F56DC0->h == h)
        return 0;
    wd = D_00F56DC0;
    if (wd->count != 0) {
        ex = D_00F56DC4->box.x1 - D_00F56DC4->box.x0 + 1;
        ey = D_00F56DC4->box.y1 - D_00F56DC4->box.y0 + 1;
        ez = D_00F56DC4->box.z1 - D_00F56DC4->box.z0 + 1;
        ox = (w - wd->w) / 2 + D_00F56DC4->box.x0;
        oz = (h - wd->h) / 2 + D_00F56DC4->box.z0;
        if (w < ex || d < ey || h < ez)
            return 0;
        if (ox < 0)
            ox = 0;
        if (oz < 0)
            oz = 0;
        if (w < ox + ex)
            ox = w - ex;
        if (h < oz + ez)
            oz = h - ez;
        tx = ox - D_00F56DC4->box.x0;
        oz -= D_00F56DC4->box.z0;
        for (i = 0; i < D_00F56DC0->count; i++) {
            wd->ents[i].x = wd->ents[i].x + tx;
            wd->ents[i].y = wd->ents[i].y + 0;
            wd->ents[i].z = wd->ents[i].z + oz;
        }
        x = D_00F56DC0->px + tx;
        z = D_00F56DC0->pz + oz;
        if (x < 0)
            x = 0;
        y = D_00F56DC0->py;
        if (x > w - 1)
            x = w - 1;
        if (y > d - 1)
            y = d - 1;
        if (z < 0)
            z = 0;
        if (z > h - 1)
            z = h - 1;
        D_00F56DC0->px = x;
        D_00F56DC0->py = y;
        D_00F56DC0->pz = z;
    }
    D_00F56DC0->h = h;
    D_00F56DC0->w = w;
    D_00F56DC0->d = d;
    func_00f24780(D_00F56DC4);
    func_00f24240(D_00F56DC4, 0);
    return 1;
}
