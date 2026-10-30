/* drafttwins.py: score 879 -> 871, port.py of the wm twin func_00f5e8a8 draft. Earlier header below. */
/* Round 45 wwm2: score 891 -> 879, hill3o statement order under this build mode. Earlier header below. */
typedef struct { s32 w; s32 h; s32 pad[2]; } Tex;
typedef struct { u8 pad[0x258]; s16 x258; s16 pad25A; s32 x25C; s32 x260; s32 x264; s32 x268; } D61880;
extern D61880 D_00F61880;
extern Tex D_00F61B90[];
void sceVu0ApplyMatrix(OvlVec, OvlMtx, OvlVec);
void sceVu0ScaleVectorXYZ(OvlVec, OvlVec, f32);
void sceVu0FTOI4Vector(s32 *, OvlVec);
s32 func_00f36508(OvlVec *, OvlMtx, s32);

u64 *func_00f377b0(u64 alpha, s32 nx, s32 ny, s32 nz, s32 u4, s32 u5, u64 tex, s32 mask, OvlMtx m, u64 *p) {
    f32 tw, th, u0, v0;
    s32 vis[8];
    OvlVec v[4];
    OvlVec w[3];
    f32 st[2] __attribute__((aligned(8)));
    s32 n[4];
    OvlVec out;
    Tex *tx;
    f32 vv[4];
    f32 q;
    s32 s, axis, idx, a, b, c, t, i, j, k;
    s32 iv[4];
    f32 u[4];

    p[0] = 0x1000000000008006;
    p[1] = 14;
    p += 2;
    n[1] = ny;
    b = 1;
    a = 2;
    idx = 0;
    p[0] = 0x507FC;
    p[1] = 71;
    p += 2;
    p[0] = 68;
    p[1] = 66;
    p += 2;
    n[0] = nx;
    p[0] = 0x101000070;
    p[1] = 78;
    w[2][3] = 1.0f;
    p += 2;
    p[0] = tex;
    p[1] = 6;
    p += 2;
    p[1] = 1;
    c = 0;
    w[0][3] = 1.0f;
    v[0][3] = 1.0f;
    v[1][3] = 1.0f;
    v[2][3] = 1.0f;
    p[0] = (alpha << 24) | 0x3F80000000808080;
    v[3][3] = 1.0f;
    p += 2;
    w[1][3] = 1.0f;
    n[2] = nz;
    p[0] = 0x0000720000006F00;
    axis = 0;
    p[1] = 24;
    p += 2;
    for (axis = 0; axis < 3; axis++) {
        for (s = 0; s < 2; s++) {
            k = idx++;
            vis[k] = 0;
            if (!((mask >> k) & 1)) continue;
            if (mask & 0x8000) {
                vis[k] = 1;
                continue;
            }
            if (s != 0) {
                w[0][c] = n[c] * 200.0f;
            } else {
                w[0][c] = 0.0f;
            }
            w[1][c] = w[0][c];
            w[2][c] = w[0][c];
            w[0][b] = 0.0f;
            w[1][b] = 0.0f;
            w[2][b] = n[b] * 200.0f;
            w[0][a] = 0.0f;
            w[1][a] = n[a] * 200.0f;
            w[2][a] = 0.0f;
            if (func_00f36508(w, m, s) >= 0) {
                vis[k] = 1;
            }
        }
        t = c;
        c = b;
        b = a;
        a = t;
    }
    tx = &D_00F61B90[D_00F61880.x258];
    th = tx->h;
    tw = tx->w;
    u0 = D_00F61880.x25C / tw;
    v0 = D_00F61880.x260 / th;
    c = 0;
    u[2] = u[0] = u0;
    a = 2;
    b = 1;
    idx = 0;
    u[3] = u[1] = u0 + D_00F61880.x264 / tw;
    vv[1] = vv[0] = v0;
    vv[3] = vv[2] = v0 + D_00F61880.x268 / th;
    for (axis = 0; axis < 3; axis++) {
        for (s = 0; s < 2; s++) {
            if (vis[idx++] == 0) continue;
            if (s != 0) {
                v[0][c] = n[c] * 200.0f;
            } else {
                v[0][c] = 0.0f;
            }
            v[1][c] = v[0][c];
            v[2][c] = v[0][c];
            v[3][c] = v[0][c];
            for (i = 0; i < n[a]; i += 2) {
                v[0][a] = v[1][a] = i * 200.0f;
                v[2][a] = v[3][a] = (i + 2) * 200.0f;
                for (j = 0; j < n[b]; j += 2) {
                    p[0] = 0xC02A400000008001;
                    p[1] = 0xEEEEEEEEEEEE;
                    p += 2;
                    v[0][b] = j * 200.0f;
                    v[1][b] = (j + 2) * 200.0f;
                    v[2][b] = v[0][b];
                    v[3][b] = v[1][b];
                    sceVu0ApplyMatrix(out, m, v[0]);
                    q = 1.0f / out[3];
                    sceVu0ScaleVectorXYZ(out, out, q);
                    sceVu0FTOI4Vector(iv, out);
                    p[5] = 4;
                    p[0] = *(u64 *)st;
                    p[4] = (u64)iv[0] | ((u64)iv[1] << 16) | ((u64)((iv[2] >> 4) + 16) << 32);
                    st[0] = u[0] * q;
                    st[1] = vv[0] * q;
                    p[2] = (alpha << 24) | ((u64)*(u32 *)&q << 32) | 0x808080;
                    p[1] = 2;
                    p[3] = 1;
                    sceVu0ApplyMatrix(out, m, v[1]);
                    p += 6;
                    q = 1.0f / out[3];
                    sceVu0ScaleVectorXYZ(out, out, q);
                    sceVu0FTOI4Vector(iv, out);
                    p[4] = (u64)iv[0] | ((u64)iv[1] << 16) | ((u64)((iv[2] >> 4) + 16) << 32);
                    st[1] = vv[1] * q;
                    st[0] = u[1] * q;
                    p[1] = 2;
                    p[0] = *(u64 *)st;
                    p[2] = (alpha << 24) | ((u64)*(u32 *)&q << 32) | 0x808080;
                    p[5] = 4;
                    p[3] = 1;
                    sceVu0ApplyMatrix(out, m, v[2]);
                    q = 1.0f / out[3];
                    p += 6;
                    sceVu0ScaleVectorXYZ(out, out, q);
                    sceVu0FTOI4Vector(iv, out);
                    p[0] = *(u64 *)st;
                    p[1] = 2;
                    p[4] = (u64)iv[0] | ((u64)iv[1] << 16) | ((u64)((iv[2] >> 4) + 16) << 32);
                    st[0] = u[2] * q;
                    st[1] = vv[2] * q;
                    p[5] = 4;
                    p[2] = (alpha << 24) | ((u64)*(u32 *)&q << 32) | 0x808080;
                    p[3] = 1;
                    p += 6;
                    sceVu0ApplyMatrix(out, m, v[3]);
                    q = 1.0f / out[3];
                    sceVu0ScaleVectorXYZ(out, out, q);
                    sceVu0FTOI4Vector(iv, out);
                    st[0] = u[3] * q;
                    p[2] = (alpha << 24) | ((u64)*(u32 *)&q << 32) | 0x808080;
                    p[3] = 1;
                    p[5] = 4;
                    p[0] = *(u64 *)st;
                    p[4] = (u64)iv[0] | ((u64)iv[1] << 16) | ((u64)((iv[2] >> 4) + 16) << 32);
                    st[1] = vv[3] * q;
                    p[1] = 2;
                    p += 6;
                }
            }
        }
        t = c;
        c = b;
        b = a;
        a = t;
    }
    p[0] = 0x1000000000008002;
    p[1] = 14;
    p += 2;
    p[0] = 0x507FC;
    p[1] = 71;
    p += 2;
    p[0] = 0x1000070;
    p[1] = 78;
    return p + 2;
}
