/* Round 34 wwm1: score 770 -> 721 (2224 -> 2204 vs 2264 bytes): branch sequence now the same as the target. In both blip loops px = dx * 64 / r * 16 comes before the mode test, and the test is written `if (mode == 0) zz = dz * 128; else zz = dz * 64;` (target bnezl with the 64 product in the slot, 128 path falling through). Earlier header below. */
/* Round 48 wwm2: the hill3o order from 010a77bf (wm func_00f3e988 near miss, score 770 -> 750, hill3o order under the new build m) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 750 was not valid. Restored the last valid statement order: score 770. Earlier header below. */
/* Round 44 wwm2: score 776 -> 770 under the nostrict build mode (r44/modescan.py). Earlier header below. */
/* score 776 (2224 vs 2264). Minimap blips: mode = func_00f2c300(D_00F9B2EC) - 1, header packets from D_00F9B330 sprite UVs and D_00F87070 tex regs, h = 340/300 (spilled), zmin -10000 or -57599.996f, r = *func_00f3f2c0() * 0.5f * 5.0f; loop 1 over func_00f3b480() objects (func_00f3b460/func_00f3e910) coloured col.v[k-1], loop 2 over the 64 D_00F9A5C0 marks (flag & 4 = raw pos, else sceVu0ApplyMatrix by D_00F864C0) coloured col.v[3]; footer then func_00f66fb0(9). The colour table is an aggregate initializer in the original (D_00FB7150 = {0x73008cff, 0x73f4a800, 0x73f400f4, 0x7300ec9d}); drafted as a struct copy so hand.py scores it. Left: we hoist one extra FP constant (f24), mode in s5 not s8, 40 bytes short. Round 28 wwm2. */
typedef struct { s32 x0; s32 u; s32 v; s32 w; s32 h; } Spr;
typedef struct { u8 pad[0x50]; f32 x; f32 y; f32 z; } Obj;
typedef struct { s32 id; s32 pad[3]; f32 pos[4]; s32 flags; s32 pad2[3]; } Mark;
typedef struct { u32 v[4]; } C4;
extern Spr D_00F9B330[];
extern Mark D_00F9A5C0[];
extern u64 D_00F87070[];
extern C4 D_00FB7150;
extern u32 D_002C5958;
extern s32 D_00F850F4;
extern s32 D_00F9B2EC;
extern u64 **D_00F85160;
extern f32 (*D_00F864C0)[4];
s32 func_00f2c300(s32);
f32 *func_00f2c848(void);
Obj *func_00f3b460(s32);
s32 func_00f3b480(void);
s32 func_00f3e910(Obj *);
f32 *func_00f3f2c0(void);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
s32 func_00f66ae0(u64 *);
void func_00f66fb0(s32, s32);
void sceVu0ApplyMatrix(f32 *, f32 (*)[4], f32 *);

void func_00f3e988(void)
{
    C4 col;
    f32 v[4];
    s32 h;
    s32 mode;
    s32 n;
    s32 su, sv;
    s32 i;
    s32 k;
    s32 px, py;
    u64 *p;
    Obj *o;
    Mark *e;
    f32 *pl;
    f32 r, zmin, dx, dz, zz, lim;

    col = D_00FB7150;
    if (D_00F9B2EC != 0 && ((D_002C5958 >> 3) & 1)) return;
    if (D_00F850F4 == 0) return;
    mode = func_00f2c300(D_00F9B2EC);
    if (mode == 0) return;
    mode--;
    p = func_00f66ac8(*D_00F85160);
    if (mode == 0) {
        n = 9;
        sv = D_00F9B330[9].v;
        su = D_00F9B330[9].u;
    } else {
        n = 10;
        sv = D_00F9B330[10].v;
        su = D_00F9B330[10].u;
    }
    h = 340;
    p = func_00f66b78(p);
    p[0] = 0x30003;
    p[1] = 71;
    p += 2;
    p[0] = 0x60;
    p[1] = 20;
    p += 2;
    p[0] = 0;
    p[1] = 24;
    p += 2;
    p[0] = 68;
    p[1] = 66;
    p += 2;
    p[0] = 0x156;
    p[1] = 0;
    p += 2;
    p[0] = 0x3F8080808080LL;
    p[1] = 1;
    p += 2;
    p[0] = D_00F87070[n];
    p[1] = 6;
    p += 2;
    p[0] = (s64)((su * 16) | ((s64)(sv * 16) << 16));
    p[1] = 3;
    p += 2;
    p[0] = 0x0F4000C0;
    p[1] = 5;
    p += 2;
    p[0] = (s64)((su * 16 + 0x800) | ((s64)(sv * 16 + 0x800) << 16));
    p[1] = 3;
    p += 2;
    p[0] = 0x174008C0;
    p[1] = 5;
    p += 2;
    lim = 57599.996f;
    func_00f66b90(p);
    sv = D_00F9B330[11].v + 1;
    su = D_00F9B330[11].u + 1;
    if (mode != 0) h = 300;
    zmin = -10000.0f;
    p = func_00f66b78(p);
    p[0] = 0x156;
    p[1] = 0;
    p += 2;
    p[0] = 0x3F8080B3B300LL;
    p[1] = 1;
    p += 2;
    p[0] = D_00F87070[11];
    p[1] = 6;
    p += 2;
    p[0] = (s64)((su * 16) | ((s64)(sv * 16) << 16));
    p[1] = 3;
    p += 2;
    p[0] = ((s64)(h + 1) << 20) | 0x450;
    p[1] = 5;
    p += 2;
    p[0] = (s64)((su * 16 + 0xF0) | ((s64)(sv * 16 + 0xF0) << 16));
    p[1] = 3;
    p += 2;
    p[0] = ((s64)(h + 15) << 20) | 0x530;
    p[1] = 5;
    p += 2;
    p[0] = 0x8000000048LL;
    p[1] = 66;
    p += 2;
    p[0] = 0x01670101007F0019LL;
    p[1] = 64;
    p += 2;
    func_00f66b90(p);
    sv = D_00F9B330[12].v;
    su = D_00F9B330[12].u;
    r = *func_00f3f2c0() * 0.5f * 5.0f;
    if (mode != 0) zmin = -lim;
    pl = func_00f2c848();
    for (i = 0; i < func_00f3b480(); i++) {
        o = func_00f3b460(i);
        k = func_00f3e910(o);
        if (k == 0) continue;
        dx = o->x - pl[0];
        dz = o->z - pl[2];
        if (dx <= r && -r <= dx && dz <= lim && zmin <= dz) {
            px = (s32)(dx * 64.0f / r * 16.0f);
            if (mode == 0) {
                zz = dz * 128.0f;
            } else {
                zz = dz * 64.0f;
            }
            py = h * 16 - (s32)(zz / lim * 16.0f);
            p = func_00f66b78(p);
            p[0] = 0x156;
            p[1] = 0;
            p += 2;
            p[0] = col.v[k - 1] | 0x3F80000000000000LL;
            p[1] = 1;
            p += 2;
            p[0] = D_00F87070[12];
            p[1] = 6;
            p += 2;
            p[0] = (s64)(((su + 1) * 16) | ((s64)((sv + 1) * 16) << 16));
            p[1] = 3;
            p += 2;
            p[0] = (s64)((px + 0x450) | ((s64)(py + 16) << 16));
            p[1] = 5;
            p += 2;
            p[0] = (s64)(((su + 15) * 16) | ((s64)((sv + 15) * 16) << 16));
            p[1] = 3;
            p += 2;
            p[0] = (s64)((px + 0x530) | ((s64)(py + 0xF0) << 16));
            p[1] = 5;
            p += 2;
            func_00f66b90(p);
        }
    }
    for (i = 63, e = D_00F9A5C0; i >= 0; i--, e++) {
        if (e->id < 0) continue;
        if (e->flags & 4) {
            v[0] = e->pos[0];
            v[1] = e->pos[1];
            v[2] = e->pos[2];
            v[3] = 1.0f;
        } else {
            sceVu0ApplyMatrix(v, D_00F864C0, e->pos);
        }
        dx = v[0] - pl[0];
        dz = v[2] - pl[2];
        if (dx <= r && -r <= dx && dz <= lim && zmin <= dz) {
            px = (s32)(dx * 64.0f / r * 16.0f);
            if (mode == 0) {
                zz = dz * 128.0f;
            } else {
                zz = dz * 64.0f;
            }
            py = h * 16 - (s32)(zz / lim * 16.0f);
            p = func_00f66b78(p);
            p[0] = 0x156;
            p[1] = 0;
            p += 2;
            p[0] = col.v[3] | 0x3F80000000000000LL;
            p[1] = 1;
            p += 2;
            p[0] = D_00F87070[12];
            p[1] = 6;
            p += 2;
            p[0] = (s64)(((su + 1) * 16) | ((s64)((sv + 1) * 16) << 16));
            p[1] = 3;
            p += 2;
            p[0] = (s64)((px + 0x450) | ((s64)(py + 16) << 16));
            p[1] = 5;
            p += 2;
            p[0] = (s64)(((su + 15) * 16) | ((s64)((sv + 15) * 16) << 16));
            p[1] = 3;
            p += 2;
            p[0] = (s64)((px + 0x530) | ((s64)(py + 0xF0) << 16));
            p[1] = 5;
            p += 2;
            func_00f66b90(p);
        }
    }
    p = func_00f66b78(p);
    p[0] = 68;
    p[1] = 66;
    p += 2;
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 0x60;
    p[1] = 20;
    p += 2;
    p[0] = 0x5000D;
    p[1] = 71;
    p += 2;
    p[0] = 0x17F01FF0000LL;
    p[1] = 64;
    p += 2;
    func_00f66b90(p);
    func_00f66fb0(9, func_00f66ae0(p));
    *D_00F85160 = p;
}
