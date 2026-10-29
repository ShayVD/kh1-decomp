/* 6 words left (608 vs 608): a1/a2 register swap only. Tried a5 casts, prototypes, CONTEXT_ONLY callees, permuter (-j1, 10 min). */
typedef struct {
    u8 on;
    u8 a0;
    u8 pad2;
    u8 a4;
    s16 a1;
    s16 a2;
    s16 a3;
    s16 pad;
    s16 a5;
    u16 snd;
    s16 task;
    s16 f12;
    u8 pad14[0xC];
    u8 f20[0x50];
    f32 vec[4];
    s32 a9;
    u8 pad84[0xC];
} E2cfd8;
s32 func_00f2ccf8(s32, s32, s32, s32);
s32 func_00f2ccb8(void);
void func_00f2cb08(E2cfd8 *);
s32 func_00f68770(s32, s32, void *, f32 *, s32);
void func_00f68870(s32);
s32 func_001c0310(s32, void *, ...);
extern s32 D_00F87048;
extern E2cfd8 D_00FBEBC0[];

s32 func_00f2cfd8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 *a6, void *a7, void (*cb)(s32), s32 a9) {
    s32 idx;
    E2cfd8 *e;
    s32 v;
    s32 r;

    if (func_00f2ccf8(a0, a1, a2, a3) >= 0) {
        return -1;
    }
    idx = func_00f2ccb8();
    D_00FBEBC0[idx].a4 = a4;
    D_00FBEBC0[idx].on = 1;
    D_00FBEBC0[idx].a0 = a0;
    D_00FBEBC0[idx].a1 = a1;
    D_00FBEBC0[idx].a3 = a3;
    D_00FBEBC0[idx].a5 = a5 & 0xFF;
    D_00FBEBC0[idx].a2 = a2;
    D_00FBEBC0[idx].a9 = a9;
    D_00FBEBC0[idx].f12 = 0;
    if (a6 != NULL) {
        D_00FBEBC0[idx].vec[0] = a6[0];
        D_00FBEBC0[idx].vec[1] = a6[1];
        D_00FBEBC0[idx].vec[2] = a6[2];
        D_00FBEBC0[idx].vec[3] = 1.0f;
    } else {
        D_00FBEBC0[idx].vec[0] = 1.0f;
        D_00FBEBC0[idx].vec[1] = 1.0f;
        D_00FBEBC0[idx].vec[2] = 1.0f;
        D_00FBEBC0[idx].vec[3] = 1.0f;
    }
    func_00f2cb08(&D_00FBEBC0[idx]);
    v = D_00F87048;
    if (a5 >= 0) {
        if (a2 == 45 || a2 == 47) {
            D_00FBEBC0[idx].vec[0] = -D_00FBEBC0[idx].vec[0];
        }
        if (cb != NULL) {
            cb(idx);
        }
        r = func_00f68770(a5, 2000, D_00FBEBC0[idx].f20, D_00FBEBC0[idx].vec, v);
        if (r < 0) {
            D_00FBEBC0[idx].snd = -1;
            D_00FBEBC0[idx].on = 0;
        } else {
            D_00FBEBC0[idx].snd = r & 0xFF;
            func_00f68870(D_00FBEBC0[idx].snd);
        }
    } else {
        D_00FBEBC0[idx].on = 0;
        D_00FBEBC0[idx].snd = -1;
    }
    if (D_00FBEBC0[idx].on == 0) {
        return -1;
    }
    if (a7 != NULL) {
        D_00FBEBC0[idx].task = func_001c0310(9, a7, idx);
    }
    return idx;
}
