/* score 30 (1056 bytes, same size). Map-marker sprite pass: 16 D_00FBB5D0 markers, kind >= 12 draws a GIF sprite from D_00F9B330[k] (k = 17/6/5 from flag bits), else func_00f32df0. Needs (s64) casts on the packed uv/xy words, the 0x101000070 header constant, and v read through D_00F9B338 (the original addresses it from that symbol). Left: fx/fy float register choice and the u field base (orig keeps D_00F9B330 base, ours folds +4). Tried w/h, u/v, x/y load orders, fw temp, Spr pointer (worse). Round 26 wwm2. */
typedef struct { s32 f; s32 x4; u32 kind; s32 xc; f32 x; f32 y; f32 z; f32 w; } Mk;
typedef struct { s32 x0; s32 u; s32 v; s32 w; s32 h; } Spr;
extern s32 D_00F850F4;
extern s32 D_00F9B2EC;
extern u32 D_002C5958;
extern f32 D_00F8C148;
extern u64 **D_00F85160;
extern u64 D_00F87070[];
extern Spr D_00F9B330[];
typedef struct { s32 v; s32 pad[4]; } SprV;
extern SprV D_00F9B338[];
extern Mk D_00FBB5D0[];
u64 *func_00f66ac8(u64 *, s32);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
s32 func_00f66ae0(u64 *);
void func_00f66f78(s32, s32);
u64 *func_00f32df0(u64 *, s32, s32, u32);

void func_00f33270(void)
{
    u64 col;
    s32 i;
    s32 k;
    u64 *p;
    Mk *m;
    f32 fx, fy;
    s32 x, y, u, v, w, h;
    u64 tex;

    if (D_00F850F4 == 0) {
        return;
    }
    if (D_00F9B2EC != 0 && ((D_002C5958 >> 3) & 1)) {
        return;
    }
    i = 15;
    col = ((s64)(s32)(D_00F8C148 * 128.0f) << 24) | 0x3F80000000808080LL;
    p = func_00f66b78(func_00f66ac8(*D_00F85160, 15));
    p[0] = 68;
    p[1] = 66;
    p += 2;
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 0x101000070LL;
    p[1] = 78;
    p += 2;
    p[0] = 0x30003;
    p[1] = 71;
    p += 2;
    func_00f66b90(p);
    m = D_00FBB5D0;
    do {
        if (m->f & 7) {
            fy = m->y / m->w;
            fx = m->x / m->w;
            if (m->kind >= 12) {
                if (m->f & 4) {
                    k = 17;
                } else if (m->f & 2) {
                    k = 6;
                } else if (m->f) {
                    k = 5;
                }
                w = D_00F9B330[k].w;
                h = D_00F9B330[k].h;
                v = D_00F9B338[k].v;
                u = D_00F9B330[k].u;
                x = (s32)(fx * 16.0f) - w * 8;
                y = (s32)(fy * 16.0f) - h * 8;
                tex = D_00F87070[k];
                p = func_00f66b78(p);
                p[0] = 342;
                p[1] = 0;
                p += 2;
                p[0] = col;
                p[1] = 1;
                p += 2;
                p[0] = tex;
                p[1] = 6;
                p += 2;
                p[0] = (s64)((u << 4) + 16) | ((s64)((v << 4) + 16) << 16);
                p[1] = 3;
                p += 2;
                p[0] = (s64)(x + 16) | ((s64)(y + 16) << 16);
                p[1] = 5;
                p += 2;
                p[0] = (s64)(((u + w) << 4) - 16) | ((s64)(((v + h) << 4) - 16) << 16);
                p[1] = 3;
                p += 2;
                p[0] = (s64)(x + ((w - 1) << 4)) | ((s64)(y + ((h - 1) << 4)) << 16);
                p[1] = 5;
                p += 2;
                func_00f66b90(p);
            } else {
                p = func_00f32df0(p, fx, fy, m->kind);
            }
        }
        m++;
    } while (--i >= 0);
    p = func_00f66b78(p);
    p[0] = 0x31000070;
    p[1] = 78;
    p += 2;
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 0x5000D;
    p[1] = 71;
    p += 2;
    func_00f66b90(p);
    func_00f66f78(0x13890, func_00f66ae0(p));
    *D_00F85160 = p;
}
