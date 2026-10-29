/* 135 words by address but about 8 after alignment (round 13). Logic is complete. Keys: func_00f62ea0 is (f32 t, f32 *out, s32 id) and takes k->f0; the visibility vector is m[3] (sp80), not its own local; the function ends with func_00f3bde8(). Left: delay-slot fill in the second switch (target puts move t0,s6 in the beqz-to-case-0 slot and its continue path is b L424; lw n), one bne vs bnel at the (u16)(q->h2 - 3) < 2 test, and the order of the func_00f35398 call. Tried: case 0 passing k->kind, a default: continue, continue instead of break. */
typedef struct { s32 id; s32 a; s32 b; f32 val; f32 v2; s32 dir; } Sub;
typedef struct { f32 m0[4][4]; f32 m1[4][4]; f32 m2[4][4]; f32 m3[16][4][4]; f32 m4[2][4][4]; Sub s; u8 pad2[0x590 - 0x558]; } W;
typedef struct { f32 f0; u8 kind; u8 pad5; u16 flag; f32 f8; f32 f12; f32 f16; f32 f20; f32 f24; f32 f28; u16 h32; u16 pad34; f32 pad36; f32 f40; f32 f44; f32 f48; f32 f52; f32 f56; f32 f60; } K;
typedef struct { u16 h0; u16 h2; u16 h4; u16 h6; } Q;
extern W *D_00F864C0;
extern s32 D_00F9B2D4, D_00F9B2D8, D_00F85098, D_00F8C23C;
extern f32 D_00F9A540[4][4];
extern f32 D_00F9A580[4][4];
s32 func_00f43d88(s32);
K *func_00f3f260(s32, s32);
s32 func_00f37170(K *);
Q *func_00f62c78(s32, s32);
s32 func_00f3b370(void);
f32 (*func_00f3bc48(s32))[4];
void func_00f3b118(s32, s32, s32, Q *, f32 (*)[4], f32 *);
void func_00f62ea0(f32, f32 *, s32);
void func_00f62c98(f32 *, s32, s32, f32);
void func_001becb8(f32 (*)[4], f32 *, s32);
s32 func_00f3c4d8(f32 *);
void func_00f35398(void);
void func_00f41410(s32, s32);
void func_00f3bde8(void);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0TransMatrix(f32 (*)[4], f32 (*)[4], f32 *);
void sceVu0RotMatrixX(f32 (*)[4], f32 (*)[4], f32);
void sceVu0RotMatrixY(f32 (*)[4], f32 (*)[4], f32);
void sceVu0RotMatrixZ(f32 (*)[4], f32 (*)[4], f32);

void func_00f3be50(void) {
    f32 v[4];
    f32 w[4];
    f32 m[4][4];
    f32 t[4][4];
    f32 u[4];
    s32 n;
    s32 i;
    s32 vis;
    K *k;
    Q *q;
    f32 (*o)[4];
    f32 d;

    n = func_00f43d88(D_00F864C0->s.id);
    for (i = 0; i < n; i++) {
        k = func_00f3f260(i, D_00F864C0->s.id);
        if (k == NULL) continue;
        if (k->f0 < (f32)D_00F9B2D4) continue;
        if ((f32)D_00F9B2D8 < k->f0) continue;
        if (func_00f37170(k)) continue;
        if ((u16)(k->flag & 1)) continue;
        if ((u8)(k->kind - 2) < 2) {
            q = func_00f62c78(k->h32, D_00F864C0->s.id);
            if (q->h2 == 2 && func_00f3b370() == 1) {
                sceVu0CopyMatrix(m, D_00F9A540);
                if (vis && q->h2 == 1 && (o = func_00f3bc48(i)) != NULL) {
                    sceVu0MulMatrix(m, D_00F9A540, &o[4]);
                    sceVu0MulMatrix(m, m, D_00F9A580);
                    sceVu0CopyMatrix(o, m);
                }
                func_00f3b118(1, k->kind, i, q, m, NULL);
                continue;
            }
        }
        d = k->f0 - D_00F864C0->s.val;
        if (D_00F864C0->s.dir) d = -d;
        if (k->kind == 1 && -1000.0f < d && d < 1000.0f) d = 0.0f;
        if (!(-200.0f < d)) continue;
        if (!(d < 1000.0f)) continue;
        switch (k->kind) {
        case 0:
        case 1:
            v[0] = k->f40;
            v[1] = k->f44;
            v[2] = k->f48;
            v[3] = 1.0f;
            sceVu0UnitMatrix(t);
            sceVu0TransMatrix(t, t, v);
            sceVu0MulMatrix(m, m, t);
            break;
        case 2:
        case 3:
            if (k->h32 == 0xFFFF) continue;
            sceVu0UnitMatrix(t);
            if (q->h2 != 0 && D_00F864C0->s.dir != 0) {
                sceVu0RotMatrixY(t, t, 3.1415927f);
            }
            sceVu0RotMatrixX(t, t, k->f20);
            sceVu0RotMatrixY(t, t, k->f24);
            sceVu0RotMatrixZ(t, t, k->f28);
            v[0] = k->f8;
            v[1] = k->f12;
            v[2] = k->f16;
            v[3] = 1.0f;
            sceVu0TransMatrix(t, t, v);
            break;
        }
        func_00f62ea0(k->f0, v, D_00F864C0->s.id);
        func_00f62c98(w, 1, D_00F864C0->s.id, k->f0);
        func_001becb8(m, w, 1);
        sceVu0TransMatrix(m, m, v);
        sceVu0MulMatrix(m, m, t);
        sceVu0MulMatrix(m, D_00F864C0->m0, m);
        vis = func_00f3c4d8(m[3]) >= 0;
        switch (k->kind) {
        case 0:
            func_00f3b118(1, 0, i, NULL, m, NULL);
            break;
        case 1:
            u[0] = k->f52;
            u[1] = k->f56;
            u[2] = k->f60;
            func_00f3b118(1, k->kind, i, NULL, m, u);
            break;
        case 2:
        case 3:
            if ((u16)(q->h2 - 3) < 2 && D_00F85098 != 0) break;
            if (q->h2 == 2) {
                if (func_00f3b370()) break;
                if (q->h2 == 2) sceVu0MulMatrix(m, m, D_00F9A580);
            }
            if (D_00F8C23C == 0 && q->h2 == 2 && 0.0f < m[3][2]) {
                if (m[3][2] < 16000.0f) func_00f35398();
                if (m[3][2] < 8000.0f) func_00f41410(q->h6, i);
            }
            if (!vis) break;
            if (q->h2 == 1 && (o = func_00f3bc48(i)) != NULL) {
                sceVu0MulMatrix(m, m, &o[4]);
                sceVu0CopyMatrix(o, m);
            }
            func_00f3b118(1, k->kind, i, q, m, NULL);
            break;
        }
    }
    func_00f3bde8();
}
