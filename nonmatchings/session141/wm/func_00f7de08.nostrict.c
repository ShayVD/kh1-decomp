/* Round 44 wwm2: score 807 -> 805 under the nostrict build mode (r44/modescan.py). Earlier header below. */
/* score 897 (3868 vs 3792 bytes): menu panel draw: backdrop f799e0, three gradient quads, title GIF packet (f07d8) + 6 corner icons, name packet with sel==5 brightness + 6 icons, optional caption (f0868) and option list (f0ea8, null-terminated arg->list), selected-row highlight quads. Logic complete; remaining diffs are register allocation/spills (original caches a*4, a*5, a*2, a<<8 in stack slots) and statement scheduling. No gb twin (no 3792-byte gb function). Round 25 wwm2. Round 19 (wwm1): score 897 -> 855 with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). Round 19 (wwm1): score 855 -> 807 with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). */
typedef union {
    kh1_u128 q;
    u64 d[2];
    u32 w[4];
} Qw;
typedef struct { s32 x0; s32 x4; s32 list[8]; u8 *x28; s32 x2c; s32 x30; } Arg;
extern s32 D_00FB64A4;
extern Qw *D_0108FA60;
Qw *func_00f21e90(u8 *);
void func_00f21ea0(Qw *);
void func_00f66fb0(s32, Qw *);
void func_00f799e0(u8 *, u8 *, s32, s32, s32, s32, s32, u8 *, s32, u64, s32, u64);
void func_00f7a1a8(u8 (*)[4], s32 *, s32 *, u64);
void func_00f7b9a0(void); CONTEXT_ONLY void func_00f7b9a0() {}
void func_001efb18(u8 *, u8 *);
Qw *func_001f07d8(Qw *, s32, s32, u32, s32, s32, s32, s32);
Qw *func_001f0868(Qw *, s32, s32, u32, s32, s32, s32, s32);
Qw *func_001f0ea8(Qw *, s32, s32, u32, s32, s32, s32, s32);

#define RGBA(c) ((c)[0] | ((c)[1] << 8) | ((c)[2] << 16) | ((c)[3] << 24))

void func_00f7de08(Arg *arg, s32 a, s32 sel)
{
    u8 col[4];
    s32 xs[4];
    s32 ys[4];
    u8 cols[4][4];
    u8 b;
    Qw *p;
    s32 y;
    s32 flag;
    s32 i;
    Qw *buf;
    Qw *top;
    u8 *tex;

    D_00FB64A4 = arg->x0;
    tex = arg->x28;
    buf = func_00f21e90(tex);
    col[0] = 0x80;
    col[2] = 0x80;
    col[1] = 0x80;
    col[3] = a;
    D_0108FA60 = buf;
    func_00f799e0(tex, tex + 0x20400, 0, 70, 512, 256, 8, col, 0, 68, 0, 0x5001D);

    cols[0][0] = 0;
    cols[2][0] = 0;
    cols[0][1] = 0;
    cols[2][1] = 0;
    cols[0][2] = 0;
    cols[2][2] = 0;
    cols[1][0] = 0;
    cols[3][0] = 0;
    cols[1][1] = 0;
    cols[3][1] = 0;
    cols[1][2] = 0;
    cols[3][2] = 0;
    cols[2][3] = cols[0][3] = a * 30 / 100;
    xs[3] = 311;
    xs[1] = 311;
    ys[1] = 39;
    cols[1][3] = a * 80 / 100;
    ys[0] = 39;
    cols[3][3] = a * 80 / 100;
    xs[2] = 0;
    ys[2] = 0;
    ys[3] = 0;
    xs[0] = 0;
    func_00f7a1a8(cols, xs, ys, 68);

    cols[0][0] = 0;
    cols[1][0] = 0;
    cols[2][0] = 0;
    cols[3][0] = 0;
    cols[0][1] = 0;
    cols[1][1] = 0;
    cols[2][1] = 0;
    cols[3][1] = 0;
    cols[0][2] = 0;
    cols[1][2] = 0;
    cols[2][2] = 0;
    xs[1] = 512;
    cols[3][2] = 0;
    xs[3] = 512;
    ys[3] = 39;
    xs[2] = 311;
    xs[0] = 311;
    cols[0][3] = a * 10240 / 12800;
    ys[2] = 39;
    cols[1][3] = a * 10240 / 12800;
    cols[2][3] = a * 10240 / 12800;
    ys[0] = 0;
    cols[3][3] = a * 10240 / 12800;
    ys[1] = 0;
    func_00f7a1a8(cols, xs, ys, 68);

    cols[1][0] = 0xFF;
    cols[1][1] = 0xC4;
    cols[1][2] = 0x4C;
    cols[2][0] = 0xFF;
    cols[0][0] = 0xFF;
    cols[3][0] = 0xFF;
    cols[2][1] = 0xC4;
    cols[0][1] = 0xC4;
    cols[2][2] = 0x4C;
    cols[0][2] = 0x4C;
    cols[3][1] = 0xC4;
    cols[3][2] = 0x4C;
    ys[2] = 41;
    ys[1] = 39;
    xs[3] = 512;
    ys[3] = 41;
    cols[2][3] = a * 80 / 100;
    ys[0] = 39;
    xs[1] = 512;
    cols[0][3] = a * 80 / 100;
    cols[3][3] = a * 80 / 100;
    cols[1][3] = a * 80 / 100;
    xs[0] = 0;
    xs[2] = 0;
    func_00f7a1a8(cols, xs, ys, 72);

    top = D_0108FA60;
    p = top + 1;
    top->q = 0;
    p->d[0] = 0x1000000000000002;
    p->d[1] = 14;
    p++;
    p->d[0] = 27;
    p->d[1] = 71;
    p++;
    p->d[0] = 68;
    p->d[1] = 66;
    col[0] = a * 255 / 128;
    col[1] = a * 150 / 128;
    col[3] = a * 80 / 100;
    col[2] = a * 20 / 128;
    p++;
    func_001efb18(tex + 0x21000, tex + 0x21020);
    p = func_001f07d8(p, 1, 0, RGBA(col), 336, 12, 1, 16);
    top->w[0] = ((p - top) - 1) | 0x10000000;
    col[1] = a * 150 / 128;
    col[2] = a * 20 / 128;
    col[0] = a * 255 / 128;
    col[3] = a * 77 / 128;
    flag = 1;
    D_0108FA60 = p;
    func_00f799e0(tex + 0x20000, tex + 0x20800, 301, 10, 32, 32, 4, col, flag, 72, 0, 0x5001D);
    col[3] = a * 102 / 128;
    func_00f799e0(tex + 0x20000, tex + 0x20800, 313, 10, 32, 32, 4, col, flag, 72, 0, 0x5001D);
    col[3] = a;
    func_00f799e0(tex + 0x20000, tex + 0x20800, 325, 10, 32, 32, 4, col, flag, 72, 0, 0x5001D);
    col[3] = a;
    func_00f799e0(tex + 0x20000, tex + 0x20800, 457, 10, 32, 32, 4, col, 0, 72, 0, 0x5001D);
    col[3] = a * 102 / 128;
    func_00f799e0(tex + 0x20000, tex + 0x20800, 469, 10, 32, 32, 4, col, 0, 72, 0, 0x5001D);
    col[3] = a * 77 / 128;
    func_00f799e0(tex + 0x20000, tex + 0x20800, 481, 10, 32, 32, 4, col, 0, 72, 0, 0x5001D);

    top = D_0108FA60;
    top->q = 0;
    p = top + 1;
    p->d[1] = 14;
    p->d[0] = 0x1000000000000002;
    p++;
    p->d[1] = 71;
    p->d[0] = 27;
    p++;
    p->d[0] = 68;
    p->d[1] = 66;
    col[1] = a * 255 / 128;
    col[0] = a * 111 / 128;
    col[2] = a * 100 / 128;
    p++;
    if (sel == 5) {
        b = 102;
        col[3] = a * 10240 / 12800;
    } else {
        col[3] = a * 5120 / 12800;
        b = 51;
    }
    func_001efb18(tex + 0x21000, tex + 0x21020);
    p = func_001f07d8(p, 1, 2, RGBA(col), 118, 279, 2, 15);
    col[3] = b * 77 / 128;
    top->w[0] = ((p - top) - 1) | 0x10000000;
    D_0108FA60 = p;
    func_00f799e0(tex + 0x20000, tex + 0x20800, 16, 277, 32, 32, 4, col, 0, 72, 0, 0x5001D);
    col[3] = b * 102 / 128;
    func_00f799e0(tex + 0x20000, tex + 0x20800, 28, 277, 32, 32, 4, col, 0, 72, 0, 0x5001D);
    col[3] = b;
    func_00f799e0(tex + 0x20000, tex + 0x20800, 40, 277, 32, 32, 4, col, 0, 72, 0, 0x5001D);
    col[3] = b;
    func_00f799e0(tex + 0x20000, tex + 0x20800, 194, 277, 32, 32, 4, col, 1, 72, 0, 0x5001D);
    col[3] = b * 102 / 128;
    func_00f799e0(tex + 0x20000, tex + 0x20800, 206, 277, 32, 32, 4, col, 1, 72, 0, 0x5001D);
    col[3] = b * 77 / 128;
    func_00f799e0(tex + 0x20000, tex + 0x20800, 218, 277, 32, 32, 4, col, 1, 72, 0, 0x5001D);

    if (arg->list[0] != 0 || arg->x4 != 0) {
        top = D_0108FA60;
        p = top + 1;
        top->q = 0;
        p->d[0] = 0x1000000000000002;
        p->d[1] = 14;
        p++;
        p->d[0] = 27;
        p->d[1] = 71;
        p++;
        p->d[0] = 68;
        p->d[1] = 66;
        p++;
        if (arg->x4 != 0) {
            col[2] = 230;
            col[1] = 230;
            col[3] = a;
            col[0] = 230;
            p = func_001f0868(p, arg->list[0] == 0, 2, RGBA(col), 116, 83, arg->x4, 16);
        }
        y = 122;
        flag = 0;
        for (i = 0; arg->list[i] != 0; i++) {
            if (arg->list[i + 1] == 0) {
                flag = 1;
            }
            if (i == sel) {
                col[0] = a * 255 / 128;
                col[1] = a * 196 / 128;
                col[2] = a * 76 / 128;
                col[3] = a * 10240 / 12800;
            } else {
                col[1] = a * 127 / 128;
                col[2] = 0;
                col[0] = a * 255 / 128;
                col[3] = a * 5120 / 12800;
            }
            p = func_001f0ea8(p, flag, 2, RGBA(col), 116, y, arg->list[i], 16);
            y += 32;
        }
        top->w[0] = ((p - top) - 1) | 0x10000000;
        D_0108FA60 = p;
    }
    if (arg->list[0] != 0) {
        y = 140;
        for (i = 0; i < 6; i++) {
            if (i == sel) {
                cols[2][0] = 0xFF;
                cols[0][0] = 0xFF;
                cols[2][1] = 0xC4;
                cols[2][2] = 0x4C;
                cols[0][1] = 0xC4;
                cols[0][2] = 0x4C;
                cols[3][0] = 0xFF;
                cols[1][0] = 0xFF;
                cols[3][1] = 0xC4;
                cols[1][1] = 0xC4;
                cols[3][2] = 0x4C;
                cols[1][2] = 0x4C;
                cols[2][3] = a * 80 / 100;
                cols[0][3] = a * 80 / 100;
                cols[3][3] = a * 80 / 100;
                ys[0] = y + 1;
                ys[1] = y + 1;
                cols[1][3] = a * 80 / 100;
                xs[0] = 0;
                xs[2] = 0;
                ys[2] = y + 3;
                xs[3] = 200;
                xs[1] = 200;
                ys[3] = y + 3;
                func_00f7a1a8(cols, xs, ys, 72);
                xs[0] = 0;
                ys[0] = y + 2;
                xs[1] = 200;
                ys[1] = y + 2;
                xs[2] = 0;
                ys[2] = y + 2;
                xs[3] = 200;
                ys[3] = y + 2;
                func_00f7a1a8(cols, xs, ys, 72);
                cols[2][0] = 0xFF;
                cols[2][1] = 0xC4;
                cols[0][0] = 0xFF;
                cols[0][1] = 0xC4;
                cols[0][3] = a * 80 / 100;
                cols[2][2] = 0x4C;
                ys[1] = y + 1;
                cols[0][2] = 0x4C;
                ys[3] = y + 3;
                cols[2][3] = a * 80 / 100;
                cols[3][0] = 0;
                cols[1][0] = 0;
                cols[3][1] = 0;
                cols[1][1] = 0;
                cols[3][2] = 0;
                cols[1][2] = 0;
                cols[3][3] = 0;
                cols[1][3] = 0;
                xs[0] = 200;
                ys[0] = y + 1;
                xs[1] = 280;
                xs[2] = 200;
                ys[2] = y + 3;
                xs[3] = 280;
                func_00f7a1a8(cols, xs, ys, 72);
                ys[3] = y + 2;
                xs[0] = 200;
                xs[1] = 280;
                ys[0] = y + 2;
                ys[1] = y + 2;
                xs[2] = 200;
                ys[2] = y + 2;
                xs[3] = 280;
                func_00f7a1a8(cols, xs, ys, 72);
            }
            y += 32;
        }
    }
    func_00f7b9a0();
    func_00f21ea0(D_0108FA60);
    func_00f66fb0(arg->x30, buf);
}
