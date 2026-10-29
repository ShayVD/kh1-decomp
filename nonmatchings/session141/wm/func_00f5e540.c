/* 79 words (420 vs 416). Structure is right (color fill, b1 {col, 0, f1E0|0}, a6 = f2F0 or f1E0, 4-pair UV copy, b0 {5,1,1}); left: scheduling of the color loads and the odd move t1,s2 / move a1,t1 copy of obj. Tried r3 a6-temp draft (80), clean versions a-e. */
typedef struct { f32 u, v, p0, p1; } UV5e540;
typedef struct { s32 x[4]; f32 c0[4]; f32 c1[4]; } Col5e540;
typedef struct {
    u8 pad[0xD0];
    Col5e540 col;
    u8 pad2[0x1E0 - 0x100];
    s32 f1E0[4];
    UV5e540 uv[16];
    s32 f2F0[4];
} Obj5e540;
typedef struct { s32 hdr[2]; f32 uv[4][2]; } Src5e540;
typedef struct { void *a; void *b; void *c; s32 d; } Blk5e540;
typedef struct { s32 a, b, c, d; } Blk05e540;
s32 func_00f4a958(s32);
void func_00f651d0(s32, Obj5e540 *, void *, Blk5e540 *, s32, Blk05e540 *, s32);
extern u8 D_00379F28[];
extern u8 D_0037A028[];
extern Src5e540 *D_0108DB8C[];

void func_00f5e540(s32 arg0, Obj5e540 *obj, s32 kind, s32 ci, s32 arg4) {
    Blk05e540 b0;
    Blk5e540 b1;
    s32 r0;
    Src5e540 *src;
    Col5e540 *col;
    void *a6;
    s32 i;

    r0 = func_00f4a958(kind - 1);
    col = &obj->col;
    src = D_0108DB8C[kind];
    col->c0[0] = D_00379F28[ci * 4];
    col->c0[1] = D_00379F28[ci * 4 + 1];
    col->c0[2] = D_00379F28[ci * 4 + 2];
    col->c0[3] = 128.0f;
    col->c1[0] = D_0037A028[ci * 4];
    col->c1[1] = D_0037A028[ci * 4 + 1];
    col->c1[2] = D_0037A028[ci * 4 + 2];
    col->c1[3] = 128.0f;
    b1.a = col;
    a6 = obj->f1E0;
    if (src != NULL) {
        b1.b = 0;
        b1.c = a6;
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
    } else {
        b1.b = 0;
        b1.c = 0;
    }
    b0.a = 5;
    b0.b = 1;
    b0.c = 1;
    func_00f651d0(arg0, obj, a6, &b1, r0, &b0, arg4);
}
