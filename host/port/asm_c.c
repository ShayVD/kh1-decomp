/* C for the hand-written assembly of src/asm/ (docs/vita-port-plan.md sections 2 and 5.1b), for
 * every port platform: functional versions read from the disassembly, not matching code.  The
 * two task switchers are in tasks.c; the VU0 packet builders of vu0_render_*.s and the GS upload
 * func_001aa1f8 are stubs that draw nothing until the renderer (section 2) takes their packets.
 * Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/vu.h"

/* func_001001d8 (crt0.s, the entry after func_001001d0's syscall 35): func_00106c10, then 0 */
void func_00106c10(void);
s32 func_001001d8(void) {
    func_00106c10();
    return 0;
}

/* func_00121f6c (src, dst, n): lq / sq in 128-byte blocks while n > 0 (whole blocks: a short
 * tail still copies 128) */
void func_00121f6c(const u8 *src, u8 *dst, s32 n) {
    do {
        __builtin_memcpy(dst, src, 128);
        n -= 128;
        src += 128;
        dst += 128;
    } while (n > 0);
}

/* func_00121fc4 (d, s): d.xyz = s.xyz / |s.xyz| and d.w = |s.xyz|; when |s.xyz|^2 is 0,
 * d = (0, 0, 1, 0) (vmr32 of vf0) */
void func_00121fc4(f32 *d, const f32 *s) {
    f32 x = s[0], y = s[1], z = s[2];
    f32 l2 = x * x + y * y + z * z;
    f32 l, q;
    if (l2 == 0.0f) {
        d[0] = 0.0f;
        d[1] = 0.0f;
        d[2] = 1.0f;
        d[3] = 0.0f;
        return;
    }
    l = PlatVu0Sqrt(l2);
    q = 1.0f / l;
    d[0] = x * q;
    d[1] = y * q;
    d[2] = z * q;
    d[3] = l;
}

/* func_00162c5c (d, a, b): row i of d = a applied to row i of b (all loads before the stores) */
void func_00162c5c(f32 (*d)[4], f32 (*a)[4], f32 (*b)[4]) {
    f32 ma[4][4], r[4][4];
    s32 i;
    __builtin_memcpy(ma, a, sizeof(ma));
    for (i = 0; i < 4; i++)
        PlatVu0Apply(r[i], ma, b[i]);
    __builtin_memcpy(d, r, sizeof(r));
}

/* The decoders of src/util/decode.c's methods 1 and 2 (func_0024e75c, func_0024e8d4): byte 0
 * the method, 1-4 the size, then codes.  0: the end.  1-125: that many literal bytes.  126 n c:
 * n + 4 copies of c.  127 lo hi c: (hi << 8 | lo) copies of c.  0x80 and up: a back reference,
 * method 1 length bits 6-3 (+3) and distance bits 2-0 and the next byte (+1), method 2 length
 * bits 6-4 and distance bits 3-0.  Within the first 2047 / 4095 bytes written a reference before
 * the start writes zeros.  Returns the bytes read; *size the bytes written. */
static s32 kh1_decode(u8 *src, u8 *dst, s32 *size, s32 lenshift, u32 lenmask, u32 distmask,
                      s32 window) {
    u8 *s = src + 5, *d = dst;
    u8 *edge = dst + window;
    for (;;) {
        u32 c = *s++;
        if (c & 0x80) {
            u32 len = ((c >> lenshift) & lenmask) + 3;
            u32 dist = (*s++ | ((c & distmask) << 8)) + 1;
            if (edge < d) {
                u8 *p = d - dist;
                do {
                    *d++ = *p++;
                } while (--len);
            } else {
                do {
                    *d = d < dst + dist ? 0 : d[-(s32)dist];
                    d++;
                } while (--len);
            }
        } else if (c == 127) {
            u32 n = s[1] << 8 | s[0];
            u8 v = s[2];
            do {
                *d++ = v;
            } while (--n);
            s += 3;
        } else if (c == 126) {
            u32 n = s[0] + 4;
            u8 v = s[1];
            do {
                *d++ = v;
            } while (--n);
            s += 2;
        } else if (c != 0) {
            do {
                *d++ = *s++;
            } while (--c);
        } else {
            *size = d - dst;
            return s - src;
        }
    }
}

s32 func_0024e75c(u8 *src, u8 *dst, s32 *size) { return kh1_decode(src, dst, size, 3, 0xF, 7, 2047); }
s32 func_0024e8d4(u8 *src, u8 *dst, s32 *size) { return kh1_decode(src, dst, size, 4, 7, 0xF, 4095); }

/* func_0024edf0 (m, p[8]): 255 when D_002BBDE0 is 3 and all eight points m p[i] lie outside one
 * clip plane (x > w, x < -w, y > w, y < -w or z < -w: vclipw, the far plane not counted), else 0 */
extern s32 D_002BBDE0;
s32 func_0024edf0(f32 (*m)[4], f32 (*p)[4]) {
    u32 all = 63;
    s32 i;
    f32 v[4];
    if (D_002BBDE0 != 3)
        return 0;
    for (i = 0; i < 8; i++) {
        PlatVu0Apply(v, m, p[i]);
        all &= PlatVu0ClipW(v);
    }
    return (all & 0x2F) ? 255 : 0;
}

/* func_0024ef88: func_00242b68(1) and (2), then for the two objects at D_002E26A0 + 4 and + 8,
 * func_00241c60(o, func_0013c318(the u16 at +0x4c of o's +0x130 record)) */
void func_00242b68(s32);
s32 func_0013c318(u32);
void func_00241c60(void *, s32);
extern s32 D_002E26A0[];
void func_0024ef88(void) {
    s32 *p = &D_002E26A0[1];
    s32 i;
    func_00242b68(1);
    func_00242b68(2);
    for (i = 0; i < 2; i++) {
        u8 *o = (u8 *)p[i];
        if (o)
            func_00241c60(o, func_0013c318(*(u16 *)(*(u8 **)(o + 0x130) + 0x4C)));
    }
}

/* Stubs until the renderer (section 2).  func_001aa1f8 (rows, dbw, dbp, sync) uploads 16x16
 * images to GS memory through the scratchpad and DMA channel 2; the six model packet builders
 * opdma.c's func_001aaf88 picks and keshptail's func_001b8198 return the new packet end, so
 * returning the current one (D_00616224) draws nothing. */
extern u8 *D_00616224;
s32 func_001aa1f8(s32 rows, u8 dbw, u16 dbp, s32 sync) { return 0; }
u8 *func_001ab0e0(void *m, void *p) { return D_00616224; }
u8 *func_001ae010(void *m, void *p) { return D_00616224; }
u8 *func_001afac0(void *m, void *p) { return D_00616224; }
u8 *func_001b1ab8(void *m, void *p) { return D_00616224; }
u8 *func_001b3870(void *m, void *p) { return D_00616224; }
u8 *func_001b6910(void *m, void *p) { return D_00616224; }
u8 *func_001b8198(void *src, void *p, s32 n) { return D_00616224; }
