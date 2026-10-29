/* score 99 (2532 vs 2536 bytes, 58 words). Map icon pass: for each of the 3 D_0108F6B8 packs, upload each texture on change (func_00f79700, fmt 4/8), then draw kind 3/4 entries with id 0x45/0x46 (player marker, plus a func_00f799e0 overlay for maps 17/18) or 0x42..0x44 (pulsing marker, alpha from D_0108FA80), then the GIF-tagged map name. Case 0x45/0x46 must come first in the switch (575 -> 307). The order of declarations sets the spill slots (307 -> 247). Corner stores are written as chained `xs[0] = xs[1] = x;` (229 -> 135). The tail uses `sel` for the range test and the index (125 -> 107). Left: w/t are allocated to t4/t5, where the original uses t5/t6. The packet stores get rescheduled: the original keeps the sq first and the D_0108F730 load after the sd stores. nostrict mode is worse (135). Permuting the corner-store lines bottoms out at 99. */
typedef struct { s32 n; s32 grp; s32 tex; } Hdr;
typedef struct { s32 n; s32 off; } Grp;
typedef struct { s32 w; s32 h; s32 fmt; s32 off; } Tex;
typedef struct { s32 tex; s32 kind; u32 id; u8 pad[48]; s32 x3c[4]; s32 x4c[4]; } Ent;
typedef struct { u8 pad[12]; s32 xc; } St;
extern s32 D_00FB5B90, D_00FB5B94, D_00FB5B98, D_00FB5B9C;
extern s32 D_00FB5BA0, D_00FB5BA4, D_00FB5BA8, D_00FB5BAC;
extern s32 D_00FB5EC0;
extern s32 D_00FB5EC8;
extern s32 D_00FB6108;
extern s8 D_00FB6110[];
extern St D_00FB6498;
extern u8 D_00FB64AC[];
extern u8 D_0108F5A0, D_0108F5A4, D_0108F5A8, D_0108F5AC;
extern u8 D_0108F5B0, D_0108F5B4, D_0108F5B8, D_0108F5BC;
extern s32 D_0108F5C0;
extern s32 D_0108F5C4;
extern s32 D_0108F5C8;
extern s32 D_0108F5CC;
extern s32 D_0108F5D0[];
extern s32 D_0108F640[];
extern u8 *D_0108F6B8[3];
extern s32 D_0108F6C8;
extern s32 D_0108F6CC;
extern s32 D_0108F6D0;
extern s32 D_0108F6E4;
extern f32 D_0108F6F0[4][4];
extern s32 D_0108F730[2];
extern kh1_u128 *D_0108FA60;
extern s32 D_0108FA68;
extern s32 D_0108FA6C;
extern s32 D_0108FA70;
extern s32 D_0108FA80;
extern s32 D_0108FA84;
extern f32 D_0108FA88;
extern f32 D_0108FA8C;
extern f32 D_0108FA90;
u8 *func_001eb018(void);
s32 func_001ebe80(void);
void func_001efb18(s32, s32);
kh1_u128 *func_001f07d8(kh1_u128 *, s32, s32, s32, s32, s32, s32, s32);
void func_00f792c8(s32 *, s32 *, s32 *, s32 *, s32, s32, s32 *, s32 *, s32, s32, u8 *, u64, s32, u64, s32);
kh1_u128 *func_00f79700(kh1_u128 *, u8 *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f799e0(s32, s32, s32, s32, s32, s32, s32, u8 *, s32, u64, s32, u64);
void sceVu0RotTransPers(s32 *, f32 (*)[4], f32 *, s32);

#define C4(a, b, c, d) ((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))

void func_00f7a350(void)
{
    s32 xs[4];
    s32 ys[4];
    s32 zs[4];
    s32 q[4];
    f32 v[4];
    s32 sc[4];
    u8 col[4];
    Hdr *h;
    Grp *g;
    Tex *tx;
    Ent *e;
    s32 i, j, w, th, last, t, mode, d0, d4, k, x, y, sel, id, px, py, c, s;
    u8 *addr;
    kh1_u128 *p;
    kh1_u128 *r;

    t = 0;
    mode = 0;
    for (k = 2; k >= 0; k--) {
        last = -1;
        h = (Hdr *)D_0108F6B8[k];
        w = 0;
        th = 0;
        v[3] = 1.0f;
        d4 = 0;
        d0 = 0;
        g = (Grp *)((u8 *)h + h->grp);
        tx = (Tex *)((u8 *)h + h->tex);
        for (i = 0; i < h->n; i++, g++) {
            e = (Ent *)(D_0108F6B8[k] + g->off);
            for (j = 0; j < g->n; j++, e++) {
                if (e->tex != last) {
                    last = e->tex;
                    w = tx[last].w;
                    th = tx[last].h;
                    switch (tx[last].fmt) {
                    case 4:
                        mode = 20;
                        d0 = 8;
                        d4 = 2;
                        t = w * th / 128;
                        break;
                    case 8:
                        mode = 19;
                        d0 = 16;
                        d4 = 16;
                        t = w * th / 64;
                        break;
                    default:
                        mode = 0;
                        t = 0;
                        break;
                    }
                    addr = D_0108F6B8[k] + tx[last].off;
                    D_0108FA60 = func_00f79700(D_0108FA60, addr, 0, 0, w, th, D_00FB6498.xc, mode, w / 64, tx[last].fmt);
                    if (t) D_0108FA60 = func_00f79700(D_0108FA60, addr + (t << 6), 0, 0, d0, d4, D_00FB6498.xc + t, 0, 1, 32);
                }
                if (e->kind == 3 || e->kind == 4) {
                    switch (e->id) {
                    case 0x45:
                    case 0x46:
                        if (D_0108F6E4 == 0) {
                            if (e->id == 0x46) break;
                        } else if (e->id == 0x45) break;
                        if (D_00FB5EC8) break;
                        v[0] = D_0108FA88;
                        v[1] = D_0108FA8C;
                        v[2] = D_0108FA90;
                        sceVu0RotTransPers(sc, D_0108F6F0, v, 2);
                        x = (sc[0] >> 4) << 4;
                        y = (sc[1] >> 4) << 4;
                        D_0108FA68 = x;
                        D_0108FA6C = y;
                        xs[0] = xs[1] = x;
                        xs[2] = xs[3] = x - 0x1000;
                        ys[0] = ys[2] = y - 0x170;
                        ys[1] = ys[3] = y - 0x570;
                        q[3] = 1;
                        q[2] = 1;
                        q[1] = 1;
                        q[0] = 1;
                        col[0] = 0xE6;
                        col[1] = 0xE6;
                        col[2] = 0xE6;
                        col[3] = 0x80;
                        func_00f792c8(xs, ys, zs, q, w, th, e->x3c, e->x4c, mode, t, col, 68, 0, 0x5001D, e->kind);
                        if (D_00FB6108 == 17 || D_00FB6108 == 18) {
                            if (*func_001eb018() >= 63) {
                                col[2] = 0xE6;
                                last = -1;
                                col[3] = 0x80;
                                col[0] = 0xE6;
                                col[1] = 0xE6;
                                func_00f799e0(D_0108F6D0 + 0x3A00, D_0108F6D0 + 0x3C00, (x >> 4) - 1868, (y >> 4) - 1930, 32, 32, 4, col, 0, 68, 0, 0x5001D);
                            }
                        }
                        break;
                    case 0x42:
                    case 0x43:
                    case 0x44:
                        if (D_00FB5EC0 == 0) {
                            if (e->id != D_0108FA70) break;
                        } else if (e->id != 0x44 && e->id != D_0108FA70) break;
                        if (D_00FB5EC8) break;
                        v[0] = D_0108FA88;
                        v[1] = D_0108FA8C;
                        v[2] = D_0108FA90;
                        sceVu0RotTransPers(sc, D_0108F6F0, v, 2);
                        x = (sc[0] >> 4) << 4;
                        y = (sc[1] >> 4) << 4;
                        xs[1] = x - 0x400;
                        ys[2] = y + 0x400;
                        ys[3] = y - 0x400;
                        xs[3] = x + 0x400;
                        xs[0] = x - 0x400;
                        ys[0] = y + 0x400;
                        ys[1] = y - 0x400;
                        xs[2] = x + 0x400;
                        q[3] = 1;
                        q[2] = 1;
                        q[1] = 1;
                        q[0] = 1;
                        if (D_00FB5EC0 == 0) {
                            col[0] = D_0108F5A0;
                            col[1] = D_0108F5A4;
                            col[2] = D_0108F5A8;
                            col[3] = D_0108F5AC;
                        } else {
                            col[0] = D_0108F5B0;
                            col[1] = D_0108F5B4;
                            col[2] = D_0108F5B8;
                            col[3] = D_0108F5BC;
                        }
                        if (e->id == 0x44) {
                            if (D_0108FA84 == 0) {
                                if (++D_0108FA80 > D_0108F5C4) {
                                    D_0108FA80 = D_0108F5C4;
                                    D_0108FA84 = 1;
                                }
                            } else if (--D_0108FA80 < 0) {
                                D_0108FA84 = 0;
                                D_0108FA80 = 0;
                            }
                            col[3] = D_0108F5C0 * (D_0108F5C4 - D_0108FA80) / D_0108F5C4;
                        }
                        func_00f792c8(xs, ys, zs, q, w, th, e->x3c, e->x4c, mode, t, col, 72, 0, 0x5001D, e->kind);
                        break;
                    }
                }
            }
        }
    }
    sel = D_00FB6108;
    if (sel >= 2 && sel < 28) {
        if (D_00FB64AC[sel] & 2) sel = 28;
        px = (D_0108FA68 >> 4) - 1939;
        id = D_00FB6110[sel];
        py = (D_0108FA6C >> 4) - 1920;
        if (D_00FB5EC8 == 0 && id > 0) {
            p = D_0108FA60;
            *p = 0;
            r = p + 1;
            ((u64 *)r)[1] = 14;
            ((u64 *)r)[0] = ((u64)0x10000000 << 32) | 2;
            r = p + 2;
            ((u64 *)r)[1] = 0x47;
            ((u64 *)r)[0] = 27;
            r = p + 3;
            ((u64 *)r)[1] = 0x42;
            ((u64 *)r)[0] = 68;
            r = p + 4;
            if (D_0108F730[0] == 0 && D_0108F730[1] == 0) c = C4(D_00FB5BA0, D_00FB5BA4, D_00FB5BA8, D_00FB5BAC);
            else c = C4(D_00FB5B90, D_00FB5B94, D_00FB5B98, D_00FB5B9C);
            func_001efb18(D_0108F6C8, D_0108F6CC);
            r = func_001f07d8(r, 1, 2, c, px, py, id, 15);
            if (func_001ebe80() == 0) s = D_0108F5D0[D_00FB6108];
            else s = D_0108F640[D_00FB6108];
            if (s) {
                r = func_001f07d8(r, 1, 0, 0x18000000, px + D_0108F5C8 + 2, py + D_0108F5CC + 2, s + 30, 14);
                r = func_001f07d8(r, 1, 0, 0x80E6E6E6, px + D_0108F5C8, py + D_0108F5CC, s + 20, 14);
            }
            *(u32 *)p = (((u32)((u8 *)r - (u8 *)p) >> 4) - 1) | 0x10000000;
            D_0108FA60 = r;
        }
    }
}
