#include "common.h"

/* rodata: func_001f94f0 (s12w16), hand/nostrict, jump table at RO=00490D90 (lchkro_s10 0 words, table bytes equal), natural.
   Sibling of func_001f0148 (same if (*s < 21) switch shape). Mode switch with `case 0: default:` first;
   case 15 uses a GNU case range `case 2 ... 28:`; case 15/0 does `cx += 1440` after the func_00266f38 call;
   header and glyph store order hill-climbed (clb6_s12); `f32 fy, fx;` order gives fy f20. */
typedef struct { u16 code; u16 f2; u16 f4; u8 w; u8 f7; } Glyph;
typedef struct { u64 d0; u64 d1; u64 d2; u64 d3; s32 w[16]; } GP;
typedef struct { u64 a, b; } Q;
typedef struct {
    u8 pad0[0x48];
    s32 x48;
    u8 pad4c[0x74 - 0x4c];
    f32 x74;
    f32 x78;
    u8 pad7c[0x90 - 0x7c];
    s32 x90;
    u8 pad94[0xb0 - 0x94];
    s32 xb0;
    s32 xb4;
} Txt9;

#include "data/pieces/D_003E8E28.h"
extern s32 D_003E8E00;
extern s32 D_003E8D00[];
extern s32 D_003E8D04[];
#include "data/pieces/D_003E8E08.h"
extern s32 D_003F1A64;
#include "data/pieces/D_003F2270.h"
extern s32 D_003F2BD0;
extern s32 D_003F2BD4;
extern u8 D_003F2C54[];
u64 *func_00122048(s32, s32);
void func_001220b8(void *);
u32 func_001edd88(u32, s32);
s32 func_001efc10(s32);
s32 func_001f0148(u8 *, s32);
s32 func_001f4570(Txt9 *);
s32 func_001f45e0(Txt9 *);
s32 func_001fb428(Txt9 *, s32, s32, s32, s32, s32, s32, s32, u32);
void func_001fd070(Txt9 *, s32, s32);
void func_00201460(Txt9 *, s32, s32, s32, s32, s32, s32, u8 *, s32);
void func_00208280(Txt9 *, s32, s32, s32, s32, s32);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
s32 sceGsSyncPath(s32, s32);

s32 func_001f94f0(Txt9 *o, s32 mode, s32 x, s32 y, u8 *s, s32 sz, u32 col) {
    u64 *base;
    u32 tag;
    s32 sz16;
    u8 **a;
    u32 col0;
    u64 *p;
    u32 color;
    s32 ox, oy;
    s32 cx;
    s32 x90;
    s32 fl, ax, ay;
    f32 fy, fx;
    s32 c, k, r;
    Glyph *g;

    func_00266f38(func_00266c08(2), ((Q *)&D_003F2270));
    sz16 = sz << 4;
    base = func_00122048(1024, 128);
    p = base + 2;
    p[2] = 0;
    p[0] = 0x1000000000000003;
    p[1] = 14;
    p[3] = 63;
    p[4] = 0x4007ff8001300000;
    p[5] = 22;
    p[6] = 68;
    p[7] = 66;
    p[8] = 0x60ab400000008001;
    tag = ((u32)base & 0x0fffffff) | 0x80000000;
    p[9] = 0x4343ee;
    base[0] = 0x7000000b;
    a = ((u8 **)&D_003E8E08);
    p = base + 12;
    col0 = col;
    x90 = o->x90;
    oy = o->xb4;
    ox = o->xb0;
    y = oy + y * 16;
    color = func_001edd88(col, x90);
    switch (mode) {
    case 0:
    default:
        cx = ox + x * 16;
        break;
    case 1:
        cx = ox + (x - func_001f0148(s, sz)) * 16;
        break;
    case 2:
        cx = ox + (x - func_001f0148(s, sz) / 2) * 16;
        break;
    }
    fl = o->x48 & 1;
    if (fl) {
        ax = func_001f4570(o);
        ay = func_001f45e0(o);
        fx = o->x74;
        fy = o->x78;
    }
    for (;;) {
        if (*s < 21) {
            switch (*s) {
            case 1:
                cx += (sz << 8) / 18;
                s++;
                break;
            case 3:
                s++;
                D_003F1A64 = *s << 4;
            case 2:
                y += D_003F1A64;
                s++;
                switch (mode) {
                case 0:
                default:
                    cx = ox + x * 16;
                    break;
                case 1:
                    cx = ox + (x - func_001f0148(s, sz)) * 16;
                    break;
                case 2:
                    cx = ox + (x - func_001f0148(s, sz) / 2) * 16;
                    break;
                }
                break;
            case 4:
                s++;
                mode = 0;
                break;
            case 5:
                s++;
                mode = 1;
                break;
            case 6:
                s++;
                mode = 2;
                break;
            case 7:
                if (s[1]) {
                    col = D_003E8D04[s[1]];
                } else {
                    col = col0;
                }
                s += 2;
                color = func_001edd88(col, x90);
                break;
            case 8:
                col = s[1] | (s[2] << 8) | (s[3] << 16) | (s[4] << 24);
                s += 5;
                color = func_001edd88(col, x90);
                break;
            case 9:
                s++;
                col = (u32)*a++;
                color = func_001edd88(col, x90);
                break;
            case 10:
                if (*a) {
                    r = func_001f94f0(o, 0, (cx - ox) >> 4, (y - oy) >> 4, *a, sz, col);
                    cx = ox + r * 16;
                    y = oy + D_003F2BD4 * 16;
                }
                a++;
                s++;
                break;
            case 11:
                r = func_001fb428(o, s[1], s[2], s[3], (cx - ox) >> 4, (y - oy) >> 4, (s32)*a++, sz, col);
                s += 4;
                cx = ox + r * 16;
                y = oy + D_003F2BD4 * 16;
                break;
            case 12:
                sz = s[1];
                s += 2;
                sz16 = sz << 4;
                break;
            case 13:
                cx += (s16)(s[1] | (s[2] << 8)) * 16;
                s += 3;
                break;
            case 14:
                y += (s16)(s[1] | (s[2] << 8)) * 16;
                s += 3;
                break;
            case 15:
                k = s[1];
                switch (k) {
                case 0:
                    func_00201460(o, 2, 2, (cx - ox) >> 4, (y - oy) >> 4, 90, ((cx - ox) >> 4) + 45, D_003F2C54, func_001efc10(43));
                    func_00266f38(func_00266c08(2), ((Q *)&D_003F2270));
                    cx += 1440;
                    break;
                case 1:
                    func_001fd070(o, (cx - ox) >> 4, (y - oy) >> 4);
                    cx += 576;
                    func_00266f38(func_00266c08(2), ((Q *)&D_003F2270));
                    break;
                case 2 ... 28:
                    func_00208280(o, (cx - ox) >> 4, (y - oy) >> 4, 0, k + 25, 128);
                    func_00266f38(func_00266c08(2), ((Q *)&D_003F2270));
                    cx += 288;
                    break;
                }
                s += 2;
                break;
            case 17:
                x = (s16)(s[1] | (s[2] << 8)) - ((ox - 0x7000) >> 4);
                s += 3;
                cx = ox + x * 16;
                break;
            case 18:
                y = (s16)(s[1] | (s[2] << 8)) - ((oy - 0x7400) >> 4);
                s += 3;
                y = oy + y * 16;
                break;
            case 19:
                x = (s16)(s[1] | (s[2] << 8));
                s += 3;
                cx = ox + x * 16;
                break;
            case 20:
                y = oy + (s16)(s[1] | (s[2] << 8)) * 16;
                s += 3;
                break;
            case 0:
            case 16:
                goto end;
            default:
                s++;
                break;
            }
        } else {
            s32 w, t, adv, x1, y1;
            s32 f2, f4;
            u64 tex;
            u32 f7;
            if (*s == 24) {
                c = (s[1] << 8) - 0x1820;
                s += 2;
            } else if (*s < 32) {
                c = ((s[0] << 8) | s[1]) - 0x1820;
                s += 2;
            } else {
                c = *s - 32;
                s++;
            }
            g = &((Glyph *)D_003E8E28)[c];
            w = g->w << 4;
            f4 = g->f4;
            adv = (w + D_003E8E00) * sz / 18;
            t = w * sz / 18;
            f7 = g->f7;
            f2 = g->f2;
            tex = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
            ((GP *)p)->w[1] = f4;
            ((GP *)p)->d0 = tex;
            ((GP *)p)->d1 = 22;
            ((GP *)p)->d2 = color;
            ((GP *)p)->w[4] = cx;
            ((GP *)p)->d3 = 1;
            ((GP *)p)->w[5] = y;
            ((GP *)p)->w[7] = 0x8000;
            ((GP *)p)->w[8] = f2 + w;
            ((GP *)p)->w[6] = 0x100000;
            ((GP *)p)->w[13] = y1 = y + sz16;
            ((GP *)p)->w[12] = x1 = cx + t;
            ((GP *)p)->w[9] = f4 + 288;
            ((GP *)p)->w[15] = 0;
            ((GP *)p)->w[14] = 0x100000;
            ((GP *)p)->w[0] = f2;
            if (fl) {
                ((GP *)p)->w[4] = (s32)(ax + (cx - ax) * fx);
                ((GP *)p)->w[5] = (s32)(ay + (y - ay) * fy);
                ((GP *)p)->w[12] = (s32)(ax + (x1 - ax) * fx);
                ((GP *)p)->w[13] = (s32)(ay + (y1 - ay) * fy);
            }
            cx += adv;
            func_00266f38(func_00266c08(2), (void *)tag);
            sceGsSyncPath(0, 0);
        }
    }
end:
    func_001220b8(base);
    D_003F2BD0 = (cx - ox) >> 4;
    D_003F2BD4 = (y - oy) >> 4;
    return (cx - ox) >> 4;
}
#include "data/data_003E.h"
#include "data/data_003F.h"
#include "data/pieces/D_003E8D04.h"
