/* drafttwins.py: score 428 -> 426, port.py of the wm twin func_00f646c0 draft. Earlier header below. */
/* gb.x func_00f3d5c8 near miss: 280 words differ, score 428 (ours 1176 bytes, original 1224). Port of wm func_00f646c0's near miss (port.py), not worked further. See the wm file for notes. */
typedef struct { u8 pad[16]; s32 x10; } Ent;
typedef struct { u8 pad[16]; Ent *x10; } Tbl;
typedef struct { s16 x0; s16 x2; u16 x4; u16 x6; u16 x8; u16 pada; s32 xC; u32 x10; u32 x14[1]; } Info;
Info *func_00f3d560(s32, Ent *, s32);
u64 *func_00f3fad8(u64 *, s32, s32, s32, s32, s32, s32, s32, s32);

u64 *func_00f3d5c8(u64 *p, s32 x0, s32 y0, s32 id, s32 idx, s32 dbp, s32 w, s32 tw, s32 a8, s32 a9, u64 a10, Tbl *t)
{
    Ent *e;
    s32 e10;
    Info *in;
    s32 b, v, u, xx, yy, rows, cols, c;
    u32 bits;
    u64 *hdr;
    u32 *bp;
    s32 n, k, per, dy, src;

    e = &t->x10[idx];
    e10 = e->x10;
    in = func_00f3d560(id, e, e10);
    if (in != 0) {
    n = in->x8;
    dy = 0;
    per = tw / 32;
    src = in->xC;
    while (n > 0) {
        k = per < n ? per : n;
        n -= per;
        p = func_00f3fad8(p, src, dbp, w / 64, a8, dy, 0, 32, k * 32);
        dy += 32;
        src += k << 10;
    }
    hdr = p = func_00f3fad8(p, e10, a9, 1, 0, 0, 0, 16, 16);
    p += 2;
    *p++ = 0x1000000000000008;
    *p++ = 14;
    *p++ = 0;
    *p++ = 0x3F;
    *p++ = 0;
    *p++ = 0x18;
    *p++ = 0x307FC;
    *p++ = 0x47;
    *p++ = 0;
    *p++ = 0x49;
    *p++ = 0x44;
    *p++ = 0x42;
    *p++ = 0;
    *p++ = 0x14;
    *p++ = dbp | ((u64)1 << 61) | (((u64)(w / 64) << 14) | ((u64)1 << 34)) | (((u64)a8 << 20) | ((u64)a9 << 37)) | ((u64)0x9900 << 18);
    *p++ = 6;
    *p++ = a10;
    bits = in->x10;
    u = 0;
    b = 0;
    v = 0;
    xx = in->x0 + x0;
    bp = in->x14;
    *p++ = 1;
    for (rows = in->x4; rows != 0; rows--) {
        yy = in->x2 + y0;
        for (c = in->x6; c != 0; c--) {
            if (bits & 1) {
                *p++ = 0x10AB400000000004;
                *p++ = 14;
                *p++ = (v * 16) | ((u64)(u * 16) << 16);
                *p++ = 3;
                *p++ = (xx * 16) | ((u64)(yy * 16) << 16) | ((u64)1 << 32);
                *p++ = 5;
                *p++ = ((v + 32) * 16) | ((u64)((u + 32) * 16) << 16);
                *p++ = 3;
                *p++ = ((xx + 32) * 16) | ((u64)((yy + 32) * 16) << 16) | ((u64)1 << 32);
                u += 32;
                *p++ = 5;
                if (u >= tw) {
                    v += 32;
                    u = 0;
                }
            }
            bits >>= 1;
            yy += 32;
            if (++b >= 32) {
                bits = *bp++;
                b = 0;
            }
        }
        xx += 32;
    }
    *p++ = 0x1000000000008001;
    *p++ = 14;
    *p++ = 0x70000;
    *p++ = 0x47;
    hdr[0] = 0x70000000 | (in->x8 * 5 + 11);
    hdr[1] = 0;
    in = (Info *)p;
    }
    return (u64 *)in;
}
