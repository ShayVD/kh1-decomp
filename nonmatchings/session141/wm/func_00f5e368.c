/* 65 words left (464 vs 472): target copies obj ptr into a separate pseudo (t3); not reproduced. Twin f5e540 same issue (80). */
typedef struct { f32 u, v, p0, p1; } UV5e368;
typedef struct { s32 x[4]; f32 c0[4]; f32 c1[4]; } Col5e368;
typedef struct {
    u8 pad[0xD0];
    Col5e368 col;
    u8 pad2[0x1E0 - 0x100];
    s32 f1E0[4];
    UV5e368 uv[16];
    s32 f2F0[4];
} Obj5e368;
typedef struct { s32 hdr[2]; f32 uv[4][2]; } Src5e368;
typedef struct { s32 a, b, c, d; } Blk5e368;
CONTEXT_ONLY s32 func_00f4a958(s32 p0) { return 0; }
CONTEXT_ONLY s32 func_00f4aa00(s32 p0) { return 0; }
void func_00f65480(s32, Obj5e368 *, void *, void *, s32, s32, void *, f32);
extern u8 D_00379F28[];
extern u8 D_0037A028[];
extern Src5e368 *D_0108DB8C[];

void func_00f5e368(s32 arg0, Obj5e368 *obj, s32 arg2, s32 arg3, s32 arg4, f32 f) {
    Blk5e368 b0;
    Blk5e368 b1;
    s32 pad[4];
    s32 r0;
    s32 r1;
    Src5e368 *src;
    Col5e368 *col;
    void *a6;
    s32 i;

    r0 = func_00f4a958(arg2 - 1);
    if (arg3 > 0) {
        r1 = func_00f4aa00(arg3 - 1);
    } else {
        r1 = 0;
    }
    col = &obj->col;
    a6 = col;
    col->c0[0] = D_00379F28[arg4 * 4];
    b1.a = (s32)a6;
    a6 = obj->f1E0;
    src = D_0108DB8C[arg2];
    col->c0[1] = D_00379F28[arg4 * 4 + 1];
    col->c0[3] = 128.0f;
    col->c0[2] = D_00379F28[arg4 * 4 + 2];
    col->c1[0] = D_0037A028[arg4 * 4];
    col->c1[1] = D_0037A028[arg4 * 4 + 1];
    col->c1[3] = 128.0f;
    col->c1[2] = D_0037A028[arg4 * 4 + 2];
    if (src != NULL) {
        b1.c = (s32)a6;
        a6 = obj->f2F0;
        {
            f32 *q = &obj->uv[0].v;
            f32 *p = &src->uv[0][1];
            for (i = 0; i < 4; i++) {
                q[-1] = p[-1];
                q[0] = p[0];
                p += 2;
                q += 4;
            }
        }
        b1.b = 0;
    } else {
        b1.b = 0;
        b1.c = 0;
    }
    b0.a = 5;
    b0.c = 1;
    b0.b = 1;
    func_00f65480(arg0, obj, a6, &b1, r0, r1, &b0, f);
}
