/* wm f3a860 near miss: 32 words differ, score 39 (996 vs 1000 bytes; the 4-byte gap is the end padding). Logic is complete. Reading o->x4 into a temp before the int store *(s32 *)&t[2] = 0 puts the store in the beqz delay slot, and declaring func_00f3d978 as (f32, f32, OvlVec, s32) fixes the argument order. Left: instruction scheduling inside the six switch cases (*a, *b, t[2] = -6000 and the f loads). The case order affects cross-jumping and size. Tried: greedy per-case permutations (2 rounds) and consistent store orders for all cases (cross-jumping shrinks the code). */
typedef struct {
    s32 x0, x4, x8, xC;
    u8 pad10[0x14];
    s32 x24;
    u8 pad28[8];
    OvlVec v30[2];
    f32 x50;
    s32 x54;
    u8 pad58[8];
    OvlMtx m60;
    OvlMtx mA0;
} Obj3a;
extern s32 D_00F8C2FC;
extern s32 D_00FDF3D0[];
extern f32 D_00F8C350, D_00F8C354, D_00F8C358, D_00F8C360, D_00F8C364, D_00F8C368;
Obj3a *func_00f363c0(s32);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0TransMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0CopyMatrix(OvlMtx, OvlMtx);
s32 func_00f3d978(f32, f32, OvlVec, s32);
s32 func_00f3d758(OvlVec, f32);

s32 func_00f3a860(s32 *a, s32 *b) {
    OvlMtx m[2];
    OvlVec t;
    s32 i;
    s32 mode;
    s32 ret;
    Obj3a *o;
    f32 f;
    f32 d;
    s32 j, n, hit;
    s32 x;

    *a = 0;
    i = 0;
    ret = 0;
    t[3] = 1.0f;
    t[0] = 0.0f;
    t[1] = 0.0f;
    t[2] = 0.0f;
    for (; i < D_00F8C2FC; i++) {
        mode = 2;
        o = func_00f363c0(D_00FDF3D0[i]);
        if (!(o->m60[2][2] <= 0.0f)) mode = 1;
        x = o->x4;
        *(s32 *)&t[2] = 0;
        if (x != 0) {
            switch (o->x8) {
            case 33:
                *a = 1;
                *b = 1;
                f = D_00F8C350;
                break;
            case 35:
                *a = 2;
                *b = 1;
                f = D_00F8C354;
                break;
            case 37:
                f = D_00F8C358;
                *a = 3;
                *b = 1;
                break;
            case 40:
                t[2] = -6000.0f;
                f = D_00F8C360;
                *b = 2;
                *a = 1;
                break;
            case 42:
                t[2] = -6000.0f;
                *b = 2;
                *a = 2;
                f = D_00F8C364;
                break;
            case 45:
                *a = 3;
                t[2] = -6000.0f;
                *b = 2;
                f = D_00F8C368;
                break;
            }
            d = f + f;
            t[2] += d;
            sceVu0UnitMatrix(m[0]);
            sceVu0TransMatrix(m[0], m[0], t);
            sceVu0MulMatrix(m[0], o->m60, m[0]);
            t[2] -= d;
            sceVu0UnitMatrix(m[1]);
            sceVu0TransMatrix(m[1], m[1], t);
            sceVu0MulMatrix(m[1], o->m60, m[1]);
            n = 2;
            hit = 0;
            for (j = 0; j < 2; j++) {
                if (func_00f3d978(f, f * 0.5f, m[j][3], 1)) {
                    sceVu0CopyMatrix(o->mA0, m[j]);
                    hit = 1;
                    break;
                }
            }
            if (hit) {
                o->xC = 1;
                continue;
            }
        } else {
            f = o->x50;
            for (j = 0; j < o->x24; j++) {
                sceVu0UnitMatrix(m[j]);
                sceVu0TransMatrix(m[j], m[j], o->v30[j]);
                sceVu0MulMatrix(m[j], o->m60, m[j]);
            }
            n = o->x24;
            *a = o->x54;
            *b = 3;
        }
        if (ret == 0) {
            hit = 0;
            for (j = 0; j < n; j++) {
                if (func_00f3d758(m[j][3], f)) {
                    sceVu0CopyMatrix(o->mA0, m[j]);
                    hit = 1;
                    break;
                }
            }
            if (hit) {
                ret = mode;
                o->xC = 1;
            }
        }
    }
    return ret;
}
