/* 59 words / score 100 (1048 = 1048). Logic complete (box outline: for 3 axes x 2 faces, a GIF tag + colour, then 10 sceVu0RotTransPers writes straight into the packet, offset by D_00F616C0 on the two other axes; then q[n][2] += 256, q[n][3] = 16). Needs a 16-byte aligned struct for the vector copies (ld/sd pairs). Left: q = p is set right after the % 3 divides in the original (ours after the vector copy), operand order of b + k*4 adds, and f0/f1 swaps in the mixed +=/-= offset pairs (the 10th corner uses f1 for i1 while the 2nd uses f0). Swapping the mixed pairs made it worse (128). Permuter run at hand-off. */
typedef struct { f32 f[4]; } __attribute__((aligned(16))) V4;
extern f32 D_00F616C0;
void sceVu0RotTransPers(int *v0, float (*m0)[4], float *v1, int mode);

u64 *func_00f367e8(f32 *a, f32 *b, u64 color, f32 (*mtx)[4], u64 *p) {
    V4 u;
    V4 w;
    V4 v;
    s32 k, j, n, i1, i2;
    s32 (*q)[4];
    a[3] = 1.0f;
    b[3] = 1.0f;
    for (k = 0; k < 3; k++) {
        for (j = 0; j < 2; j++) {
            p[0] = 0xB062400000000001;
            p[1] = 0x4444444444E;
            p += 2;
            p[1] = 1;
            p[0] = color;
            p += 2;
            if (j == 0) {
                v = *(V4 *)a;
            } else {
                v.f[k] = b[k];
            }
            i1 = (k + 1) % 3;
            i2 = (k + 2) % 3;
            q = (s32 (*)[4])p;
            u = v;
            sceVu0RotTransPers((s32 *)p, mtx, u.f, 0);
            p += 2;
            w = u;
            w.f[i1] += D_00F616C0;
            w.f[i2] += D_00F616C0;
            sceVu0RotTransPers((s32 *)p, mtx, w.f, 0);
            p += 2;
            u.f[i1] = b[i1];
            sceVu0RotTransPers((s32 *)p, mtx, u.f, 0);
            p += 2;
            w = u;
            w.f[i1] -= D_00F616C0;
            w.f[i2] += D_00F616C0;
            sceVu0RotTransPers((s32 *)p, mtx, w.f, 0);
            p += 2;
            u.f[i2] = b[i2];
            sceVu0RotTransPers((s32 *)p, mtx, u.f, 0);
            p += 2;
            w = u;
            w.f[i1] -= D_00F616C0;
            w.f[i2] -= D_00F616C0;
            sceVu0RotTransPers((s32 *)p, mtx, w.f, 0);
            p += 2;
            u.f[i1] = a[i1];
            sceVu0RotTransPers((s32 *)p, mtx, u.f, 0);
            p += 2;
            w = u;
            w.f[i1] += D_00F616C0;
            w.f[i2] -= D_00F616C0;
            sceVu0RotTransPers((s32 *)p, mtx, w.f, 0);
            p += 2;
            u = v;
            sceVu0RotTransPers((s32 *)p, mtx, u.f, 0);
            p += 2;
            w = u;
            w.f[i1] += D_00F616C0;
            w.f[i2] += D_00F616C0;
            sceVu0RotTransPers((s32 *)p, mtx, w.f, 0);
            p += 2;
            for (n = 0; n < 10; n++) {
                q[n][2] += 256;
                q[n][3] = 16;
            }
        }
    }
    p[0] = 0x8000;
    p[1] = 0;
    return p + 2;
}
