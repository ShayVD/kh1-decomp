/* score 10 (6 words; was 15/30). Round 34 wwm2: the -dg dump showed obj (pseudo 86: 15 refs, live 300) and the s->m address (pseudo 122: 6 refs, live 75) nearly tied, with s->m winning s2. `f32 (*sm)[4] = s->m` set right after the `ok:` label makes it live longer, so obj takes s2 as in the original. Left: the original computes s+32 inside the loop (in the beqz delay slot), ours before it; setting sm again in the loop is CSE'd away and sm = 0 at ok: undoes the fix. Earlier header: 15 words left (round 12): s2/s3 swap between obj and the &s->m address. Tried 12 declaration orders, an sm pointer, ternary/else/goto-out forms, 10 min permuter (no gain). Sibling func_00f2e510 matched with the same skeleton, compare against ovl/wm/hand/func_00f2e510.c. */
typedef struct { u8 b0; u8 pad[13]; u16 h14; u16 pad2; s16 h18; u8 pad3[12]; f32 m[4][4]; u8 pad4[32]; s32 idx; } A2dc50;
typedef struct { s32 a; s32 b; u8 pad[24]; } B2dc50;
typedef struct { s32 f0; s32 f4; u8 pad[72]; f32 v80[4]; } O2dc50;
typedef struct { u8 pad[6]; u16 h6; } R2dc50;
typedef struct { u8 pad[1344]; s32 f1344; } G2dc50;
extern B2dc50 D_00FBB5D0[];
extern G2dc50 *D_00F864C0;
extern f32 D_002BBDEC;
A2dc50 *func_00f2cae8(void);
O2dc50 *func_00f3b4e0(s32);
R2dc50 *func_00f3f260(s32, s32);
s32 func_00f680c0(s32);
void func_00f68ab0(s32);
void func_00f2d608(s32);
void func_00f2cf78(s32);
void func_001bfac8(void);
f32 func_00f2d738(f32 (*)[4], f32 *, f32, f32, f32);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);

void func_00f2dc50(s32 arg) {
    f32 m[4][4];
    A2dc50 *s;
    O2dc50 *obj;
    R2dc50 *r;
    s32 idx;
    s32 id;
    s32 done;
    s32 cnt;
    s32 g;
    f32 v;
    f32 vmax;
    f32 acc;
    f32 (*sm)[4];

    s = func_00f2cae8();
    v = D_002BBDEC * 2000.0f;
    acc = D_002BBDEC * 40.0f;
    idx = s->idx;
    vmax = v;
    if (idx >= 0) {
        id = D_00FBB5D0[idx].b;
    } else {
        id = -1;
    }
    obj = NULL;
    if (id >= 0) {
        obj = func_00f3b4e0(id);
        if (obj != NULL) {
            g = D_00F864C0->f1344;
            r = func_00f3f260(obj->f4, g);
            if (r != NULL) {
                r->h6 |= 2;
                goto ok;
            }
        }
        id = -1;
        obj = NULL;
    }
ok:
    sm = s->m;
    done = 0;
    cnt = 0;
    while (func_00f680c0(s->h14)) {
        obj = NULL;
        if (id >= 0) {
            obj = func_00f3b4e0(id);
        }
        if (s->b0 == 0) {
            return;
        }
        sceVu0CopyMatrix(m, sm);
        m[0][0] = -m[0][0];
        m[0][1] = -m[0][1];
        m[0][2] = -m[0][2];
        m[2][0] = -m[2][0];
        m[2][1] = -m[2][1];
        m[2][2] = -m[2][2];
        if (obj == NULL) {
            if (v < vmax) {
                v += acc;
                if (vmax < v) {
                    v = vmax;
                }
            }
            m[3][0] += m[2][0] * vmax;
            m[3][1] += m[2][1] * vmax;
            m[3][2] += m[2][2] * vmax;
        } else {
            v = func_00f2d738(m, obj->v80, 0.17453292f, vmax, 1.0f);
            m[3][0] += m[2][0] * v;
            m[3][1] += m[2][1] * v;
            m[3][2] += m[2][2] * v;
        }
        m[0][0] = -m[0][0];
        m[0][1] = -m[0][1];
        m[0][2] = -m[0][2];
        m[2][0] = -m[2][0];
        m[2][1] = -m[2][1];
        m[2][2] = -m[2][2];
        sceVu0CopyMatrix(sm, m);
        if (s->h18 & 1) {
            func_00f68ab0(s->h14);
            while (func_00f680c0(s->h14)) {
                if (s->b0 == 0) {
                    return;
                }
                func_001bfac8();
            }
            s->h18 = 0;
            break;
        }
        if (done == 0) {
            if (cnt >= 25) {
                func_00f68ab0(s->h14);
                done = 1;
            }
            if (done == 0) {
                func_00f2d608(arg);
            }
        }
        func_001bfac8();
        cnt++;
    }
    if (obj != NULL) {
        g = D_00F864C0->f1344;
        D_00FBB5D0[idx].a &= 0xFD;
        r = func_00f3f260(obj->f4, g);
        if (r != NULL) {
            r->h6 ^= 2;
        }
    }
    func_00f2cf78(arg);
}
