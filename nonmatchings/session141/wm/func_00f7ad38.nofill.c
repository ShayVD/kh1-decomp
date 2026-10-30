/* Round 44 wwm2: score 628 -> 616 under the nofill build mode (r44/modescan.py). Earlier header below. */
/* score 524 (3200 vs 3176 bytes). Sibling of f7a350: the same 3-pack texture upload, then each kind 3/4 entry is filtered by id (66..70 skipped; >= 100 are map markers for sel/D_00FB6498.x94, with dim set when they differ; 2..64 need f[id] & 1 and not & 2; 72..97 need f[id-70] & 2; D_00FB649C.f is the flag array, addressed from D_00FB649C+16 as the original does). It is then lifted by func_00f787b0, projected per vertex (skipped when z is invalid), coloured by the D_0108F7C0/830/8A0 fades and the pack-k switch, and ids 21..26 are drawn 4 times rotated by D_0108F918 (the original reuses the id-21 index variable as the inner loop counter; kept). Colour bytes need (s32) truncation (u8 from float gives the 0x4f000000 sequence). u32 id gives the sltiu compares. Left: 24 bytes: the texture-upload argument order, the s4/s5 and t5/t6 register numbering, the double col[3] store, and the blend=72 merge in the k switch. hill2 found nothing (the word count is dominated by misalignment). Round 18 (wwm1): 732 words with CONTEXT_ONLY definitions of cosf and sinf (ctx2.py). Round 19 (wwm1): score 675 -> 628 with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). */
typedef struct { s32 n; s32 grp; s32 tex; } Hdr;
typedef struct { s32 n; s32 off; } Grp;
typedef struct { s32 w; s32 h; s32 fmt; s32 off; } Tex;
typedef struct { s32 tex; s32 kind; u32 id; f32 px[4]; f32 py[4]; f32 pz[4]; s32 x3c[4]; s32 x4c[4]; } Ent;
typedef struct { u8 pad[12]; s32 xc; u8 pad2[132]; s32 x94; } St;
typedef struct { u8 pad[16]; u8 f[1]; } S9C;
extern f32 D_00FB5BB8;
extern f32 D_00FB5BBC;
extern f32 D_00FB5BC0;
extern f32 D_00FB5BC4;
extern St D_00FB6498;
extern S9C D_00FB649C;
extern u8 D_00FB64AC[];
extern u8 D_0108F580, D_0108F584, D_0108F588, D_0108F58C;
extern u8 D_0108F590, D_0108F594, D_0108F598;
extern s32 D_0108F59C;
extern u8 *D_0108F6B8[3];
extern s32 D_0108F6E0;
extern s32 D_0108F6E4;
extern f32 D_0108F6F0[4][4];
extern s32 D_0108F730[2];
extern f32 D_0108F7C0[];
extern f32 D_0108F830[];
extern f32 D_0108F8A0[];
extern f32 D_0108F918[];
extern kh1_u128 *D_0108FA60;
f32 cosf(f32);
CONTEXT_ONLY f32 cosf() { return 0; }
f32 sinf(f32);
CONTEXT_ONLY f32 sinf() { return 0; }
f32 func_00f787b0(s32);
void func_00f792c8(s32 *, s32 *, s32 *, s32 *, s32, s32, s32 *, s32 *, s32, s32, u8 *, u64, s32, u64, s32);
kh1_u128 *func_00f79700(kh1_u128 *, u8 *, s32, s32, s32, s32, s32, s32, s32, s32);
void sceVu0RotTransPers(s32 *, f32 (*)[4], f32 *, s32);

void func_00f7ad38(s32 sel)
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
    s32 i, j, w, th, last, mode, t, d0, d4;
    Ent *e;
    u64 blend;
    s32 k, n, m, dim, a;
    u32 id;
    u8 *addr;
    f32 lift, cx, cy, ang, fx, fy;
    f32 *pa;

    mode = 0;
    D_0108F6E4 = 0;
    t = 0;
    blend = 0;
    if (sel >= 2 && sel < 28) {
        if ((D_00FB64AC[sel] & 1) && (D_00FB64AC[sel] & 8)) D_0108F6E4 = 1;
    }
    for (k = 2; k >= 0; k--) {
        last = -1;
        v[3] = 1.0f;
        th = 0;
        h = (Hdr *)D_0108F6B8[k];
        w = 0;
        tx = (Tex *)((u8 *)h + h->tex);
        d4 = 0;
        g = (Grp *)((u8 *)h + h->grp);
        d0 = 0;
        for (i = 0; i < h->n; i++, g++) {
            e = (Ent *)(D_0108F6B8[k] + g->off);
            for (j = 0; j < g->n; j++, e++) {
                if (e->tex != last) {
                    last = e->tex;
                    w = tx[last].w;
                    th = tx[last].h;
                    switch (tx[last].fmt) {
                    case 4:
                        t = w * th / 128;
                        d0 = 8;
                        mode = 20;
                        d4 = 2;
                        break;
                    case 8:
                        t = w * th / 64;
                        mode = 19;
                        d4 = 16;
                        d0 = 16;
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
                if (e->kind != 3 && e->kind != 4) continue;
                id = e->id;
                if (id < 71) {
                    if (id >= 66) continue;
                }
                dim = 0;
                lift = 0.0f;
                if (id >= 100) {
                    if (sel + 100 == id || (sel == 27 && id == 113)) {
                        if (D_00FB6498.x94 != sel) {
                            dim = 1;
                            goto show;
                        }
                    }
                    if (D_00FB6498.x94 + 100 == id) goto show;
                    if (D_00FB6498.x94 != 27) continue;
                    if (id != 113) continue;
                } else {
                    if (id >= 2 && id < 65) {
                        if (!(D_00FB649C.f[id] & 1)) continue;
                        if (D_00FB649C.f[id] & 2) continue;
                    }
                    if (id >= 72 && id < 98) {
                        if (!(D_00FB649C.f[id - 70] & 2)) continue;
                        if (k == 2 && id >= 30 && id < 65) {
                            if (!(D_00FB649C.f[id] & 1)) continue;
                        }
                    }
                }
            show:
                if (id >= 2 && id < 28 && !(D_00FB649C.f[id] & 2)) lift += func_00f787b0(id);
                for (n = 0; n < e->kind; n++) {
                    v[0] = e->px[n];
                    v[1] = e->py[n] + lift;
                    v[2] = e->pz[n];
                    sceVu0RotTransPers(sc, D_0108F6F0, v, 2);
                    if ((u32)(sc[2] - 1) > 0x7FFFFFFD) goto next;
                    xs[n] = sc[0];
                    ys[n] = sc[1];
                    zs[n] = sc[2];
                    q[n] = sc[3];
                }
                col[1] = 0x80;
                col[2] = 0x80;
                col[0] = 0x80;
                col[3] = 0x80;
                if (e->id >= 2 && e->id < 28) {
                    if (sel == e->id) {
                        D_0108F7C0[sel] += (128.0f - D_00FB5BBC) * 10.0f / D_00FB5BB8;
                        D_0108F8A0[sel] += (128.0f - D_00FB5BC4) * 10.0f / D_00FB5BB8;
                        D_0108F830[sel] += (128.0f - D_00FB5BC0) * 10.0f / D_00FB5BB8;
                        if (D_0108F7C0[sel] >= 128.0f) D_0108F7C0[sel] = 128.0f;
                        if (D_0108F830[e->id] >= 128.0f) D_0108F830[e->id] = 128.0f;
                        if (D_0108F8A0[e->id] >= 128.0f) D_0108F8A0[e->id] = 128.0f;
                    } else {
                        D_0108F7C0[e->id] -= (128.0f - D_00FB5BBC) * 10.0f / D_00FB5BB8;
                        if (D_0108F7C0[e->id] < D_00FB5BBC) D_0108F7C0[e->id] = D_00FB5BBC;
                        D_0108F830[e->id] -= (128.0f - D_00FB5BC0) * 10.0f / D_00FB5BB8;
                        if (D_0108F830[e->id] < D_00FB5BC0) D_0108F830[e->id] = D_00FB5BC0;
                        D_0108F8A0[e->id] -= (128.0f - D_00FB5BC4) * 10.0f / D_00FB5BB8;
                        if (D_0108F8A0[e->id] < D_00FB5BC4) D_0108F8A0[e->id] = D_00FB5BC4;
                    }
                    col[0] = (s32)D_0108F7C0[e->id];
                    col[1] = (s32)D_0108F830[e->id];
                    col[2] = (s32)D_0108F8A0[e->id];
                    if (e->id == D_00FB6498.x94) {
                        col[2] = 0x80;
                        col[1] = 0x80;
                        col[0] = 0x80;
                        col[3] = 0x80;
                    }
                }
                switch (k) {
                case 0:
                    blend = 68;
                    break;
                case 1:
                    if (dim == 0) {
                        col[0] = D_0108F580;
                        col[1] = D_0108F584;
                        col[2] = D_0108F588;
                        col[3] = D_0108F58C;
                    } else {
                        col[0] = D_0108F590;
                        col[1] = D_0108F594;
                        col[2] = D_0108F598;
                        col[3] = D_0108F59C * D_0108F6E0 / 128;
                        if (D_0108F730[0] == 0 && D_0108F730[1] == 0) col[3] = 0;
                    }
                    blend = 72;
                    break;
                case 2:
                    blend = 72;
                    col[3] = 80;
                    col[0] = 0x80;
                    col[1] = 0x80;
                    col[2] = 0x80;
                    break;
                }
                if (e->id < 27) {
                    if (e->id < 21) goto one;
                    cx = (xs[0] + xs[1] + xs[2] + xs[3]) / 4;
                    cy = (ys[0] + ys[1] + ys[2] + ys[3]) / 4;
                    a = col[3];
                    m = e->id - 21;
                    for (n = 0; n < 4; n++) {
                        pa = &D_0108F918[m * 4 + n];
                        *pa -= (n + 1) * 0.00019174743f;
                        if (*pa < 0.0f) *pa += 6.2831836f;
                        ang = *pa;
                        for (m = 0; m < 4; m++) {
                            fy = ys[m];
                            fx = xs[m];
                            fx -= cx;
                            fy -= cy;
                            xs[m] = cosf(ang) * fx - sinf(ang) * fy + cx;
                            ys[m] = sinf(ang) * fx + cosf(ang) * fy + cy;
                        }
                        col[3] = a / (4 - n);
                        col[3] = col[3] >> 1;
                        func_00f792c8(xs, ys, zs, q, w, th, e->x3c, e->x4c, mode, t, col, blend, 0, 0x5001D, e->kind);
                    }
                } else {
                one:
                    func_00f792c8(xs, ys, zs, q, w, th, e->x3c, e->x4c, mode, t, col, blend, 0, 0x5001D, e->kind);
                }
            next:;
            }
        }
    }
}
