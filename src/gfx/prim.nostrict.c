/* Primitives sent at once, the nostrict part (docs/modules.md "Session 45";
 * prim.c has the list).  func_002384e0(src, n, buf, m) projects n flat
 * triangles (112-byte kind 2 nodes) with the matrix m, drops the ones the
 * screen clip rejects and sends the rest in one packet; func_00238768(src, n,
 * buf) sends n textured quads (14 qwords each: two triangle strips of three
 * vertices, STQ / RGBA / XYZ2) in one packet; prim.nostrict_nofill.c's
 * func_002388b8 is the same into a caller's buffer. */
#include "common.h"
#include "platform/vu.h"

typedef kh1_s128 u128;
typedef f32 V4f[4] __attribute__((aligned(16)));
typedef struct { u128 q[7]; } Ent70;
void func_00237018(u128 *, s32, s32);

void func_002384e0(u32 srca, s32 n, u128 *buf, V4f *m) {
    V4f mat[4];
    V4f t[3];
    V4f v1, v2, v3;
    s32 k;
    s32 cnt;
    s32 i;
    u128 *h;
    u64 tag;
    Ent70 *src = (Ent70 *)srca;
    PlatVu0CopyMatrix(mat, m);
    tag = (n | 0x8000) | ((u64)0x6005C000 << 32);
    h = buf + 1;
    cnt = 0;
    *h = KH1_Q(0);
    ((u64 *)h)[0] = tag;
    ((u64 *)h)[1] = 0x414141;
    k = 2;
    for (i = 0; i < n; i++, src++) {
        PlatVu0ApplyMatrix(v1, mat, &src->q[1]);
        PlatVu0ApplyMatrix(v2, mat, &src->q[2]);
        PlatVu0ApplyMatrix(v3, mat, &src->q[3]);
        PlatVu0DivVectorXYZ(v1, v1, v1[3]);
        PlatVu0DivVectorXYZ(v2, v2, v2[3]);
        PlatVu0DivVectorXYZ(v3, v3, v3[3]);
        if (PlatVu0ClipScreen3(v1, v2, v3) == 0) {
            cnt++;
            PlatVu0RotTransPersN(t, mat, &src->q[1], 3, 0);
            ((s32 *)t[0])[3] = 0;
            ((s32 *)t[1])[3] = 0;
            ((s32 *)t[2])[3] = 0;
            buf[k++] = src->q[4];
            buf[k++] = *(u128 *)t[0];
            buf[k++] = src->q[5];
            buf[k++] = *(u128 *)t[1];
            buf[k++] = src->q[6];
            buf[k++] = *(u128 *)t[2];
        }
    }
    if (cnt) func_00237018(buf, k, 1);
}

/* func_002386c0 is in prim.nostrict_nofill.c. */

void func_00238768(u128 *src, s32 n, u128 *buf) {
    s32 k = 2;
    u64 *e;
    s32 i;
    u64 t;
    for (i = 0; i < n; i++) {
        u128 *d = (u128 *)((k << 4) + (s32)buf);
        k += 24;
        ((u64 *)d)[0] = 0;
        ((u64 *)d)[1] = 63;
        d[1] = src[i * 14 + 0];
        d[2] = src[i * 14 + 1];
        d[3] = src[i * 14 + 2];
        d[4] = src[i * 14 + 6];
        d[5] = src[i * 14 + 10];
        d[6] = src[i * 14 + 3];
        d[7] = src[i * 14 + 7];
        d[8] = src[i * 14 + 11];
        d[9] = src[i * 14 + 4];
        d[10] = src[i * 14 + 8];
        d[11] = src[i * 14 + 12];
        e = (u64 *)&d[12];
        e[0] = 0;
        e[1] = 63;
        d[13] = src[i * 14 + 0];
        d[14] = src[i * 14 + 1];
        d[15] = src[i * 14 + 4];
        d[16] = src[i * 14 + 8];
        d[17] = src[i * 14 + 12];
        d[18] = src[i * 14 + 3];
        d[19] = src[i * 14 + 7];
        d[20] = src[i * 14 + 11];
        d[21] = src[i * 14 + 5];
        d[22] = src[i * 14 + 9];
        d[23] = src[i * 14 + 13];
    }
    buf[1] = KH1_Q(0);
    t = (n * 2) | 0x8000;
    t |= (u64)0xC0ADC000 << 32;
    ((u64 *)&buf[1])[0] = t;
    ((u64 *)&buf[1])[1] = 0x413413413EEE;
    func_00237018(buf, k, 1);
}
