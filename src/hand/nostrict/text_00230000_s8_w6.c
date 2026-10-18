#include "common.h"
typedef int u128 __attribute__((mode(TI)));
typedef f32 V4f[4] __attribute__((aligned(16)));
typedef struct { u128 q[7]; } Ent70;
void sceVu0CopyMatrix(V4f *, V4f *);
void func_002672f8(f32 *, V4f *, u128 *);
void func_002674d0(f32 *, f32 *, f32);
s32 func_00267ef0(f32 *, f32 *, f32 *);
void func_00267da0(V4f *, V4f *, u128 *, s32, s32);
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
    sceVu0CopyMatrix(mat, m);
    tag = (n | 0x8000) | ((u64)0x6005C000 << 32);
    h = buf + 1;
    cnt = 0;
    *h = 0;
    ((u64 *)h)[0] = tag;
    ((u64 *)h)[1] = 0x414141;
    k = 2;
    for (i = 0; i < n; i++, src++) {
        func_002672f8(v1, mat, &src->q[1]);
        func_002672f8(v2, mat, &src->q[2]);
        func_002672f8(v3, mat, &src->q[3]);
        func_002674d0(v1, v1, v1[3]);
        func_002674d0(v2, v2, v2[3]);
        func_002674d0(v3, v3, v3[3]);
        if (func_00267ef0(v1, v2, v3) == 0) {
            cnt++;
            func_00267da0(t, mat, &src->q[1], 3, 0);
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
