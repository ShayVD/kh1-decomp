/* Round 50 wwm2: score 89 -> 87 (same size). The target reloads md->x9 for the func_00f200c8 argument (a latescan MORE hit). Reading the argument through a volatile view, ((volatile Md34 *)md)->x9, reproduces the reload. A u8 pointer read, ternary/else forms and other prototypes for the callee do not. The original probably had a real alias barrier here; this is a stand-in. Earlier header below. */
/* wm f344f0 near miss: 113 words differ, score 89 (1012 vs 1008 bytes). Logic is complete: model draw loop like f4e738, with a dead struct copy of D_00FB6FC0 and unused rot vec kept on the stack. Left: the order of the local init stores, the packet pointer temps (the original uses v0+16 and v0+32 bases), the loop invariant (the original keeps buf = sp+64 in s8, ours hoists %hi(D_00F8C224)), and the md->x9 reload. Tried: p[2]/p[3] vs q = p + 2 forms, buf types, and the tail packet form. */
typedef struct { u64 *p; u8 *w; u8 x8[1]; } Cx34;
typedef struct { u8 pad0[4]; u16 h4; u16 h6; u8 b8; u8 pad9[3]; } En34;
typedef struct {
    s32 x0;
    u8 pad4[12];
    OvlVec v10;
    u8 pad20[12];
    f32 x2C;
    u8 pad30[4];
    En34 e[1];
} A34;
typedef struct { u8 pad[8]; u8 x8; u8 x9; } Md34;
typedef struct { u64 a, b; } Q34;
extern Q34 D_00FB6FC0;
extern s32 D_00F9B1C0;
extern s32 D_00F850F4;
extern f32 D_00F8C148;
extern A34 D_00F85240;
extern f32 D_00F8C240[4][4];
extern Cx34 *D_00F85160;
extern f32 D_00F85200[4][4];
extern f32 D_00F85180[4][4];
extern f32 D_00F872C0[4][4];
extern u8 D_00FBDAB0[];
extern f32 D_00FBB850[];
extern s32 D_00F8C224;
void sceVu0UnitMatrix(OvlMtx);
void sceVu0TransMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0RotMatrixY(OvlMtx, OvlMtx, f32);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0CopyMatrix(OvlMtx, OvlMtx);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
u64 *func_00f66ae0(u64 *);
void func_00f66f78(s32, u64 *);
void func_00f5df38(s32, s32, void *);
void func_00f5de50(void *, s32);
void func_00f5e6e0(void *);
Md34 *func_001bb658(s32);
void func_001bb6d0(s32);
void func_00f5dd78(void *, void *, void *, void *, En34 *);
s32 func_00f200c8(s32);
s32 func_00f200a8(s32);
s32 func_00f35798(s32);
s32 func_00f358d8(s32, void *);
u8 *func_00f676b8(s32, void *, u8 *, s32, s32, void *, s32);
u8 *func_00f67530(s32, void *, u8 *, s32, s32, s32, s32, f32);

void func_00f344f0(s32 id) {
    OvlMtx m;
    u8 buf[64];
    OvlMtx ms;
    OvlVec rot;
    Q34 tmp;
    s32 i;
    Cx34 *cx;
    En34 *e;
    Md34 *md;
    s32 k;
    s32 a, b, c;
    f32 al;
    u64 *p;
    u64 *q;
    u64 *r;

    tmp = D_00FB6FC0;
    if (D_00F9B1C0 < 4) return;
    if (D_00F850F4 == 0) return;
    al = D_00F8C148;
    if (al <= 0.0f) return;
    if (D_00F8C240[3][2] < -D_00F85240.x2C) return;
    rot[2] = 0.0f;
    rot[1] = 3.1415925f;
    i = 0;
    rot[3] = 1.0f;
    ms[0][0] = 0.0f;
    ms[0][1] = 0.0f;
    ms[0][2] = 0.0f;
    ms[0][3] = 0.0f;
    ms[1][0] = 0.0f;
    ms[1][1] = 0.0f;
    ms[1][2] = 0.0f;
    ms[1][3] = 0.0f;
    ms[2][0] = 0.0f;
    ms[2][1] = 0.0f;
    ms[2][2] = 0.0f;
    ms[2][3] = 0.0f;
    ms[3][0] = 1.0f;
    ms[3][1] = 1.0f;
    ms[3][2] = 1.0f;
    ms[3][3] = al;
    rot[0] = 0.0f;
    cx = D_00F85160;
    sceVu0UnitMatrix(m);
    sceVu0TransMatrix(m, m, D_00F85240.v10);
    sceVu0RotMatrixY(m, m, 3.1415927f);
    sceVu0MulMatrix(m, D_00F8C240, m);
    sceVu0MulMatrix(m, D_00F85200, m);
    sceVu0MulMatrix(m, D_00F85180, m);
    cx->p = func_00f66ac8(cx->p);
    p = func_00f66b78(cx->p);
    p[1] = 24;
    p[0] = 0x0000740000007000;
    p[3] = 8;
    cx->p = p + 4;
    p[2] = 0;
    func_00f66b90(p + 4);
    func_00f66f78(id++, func_00f66ae0(cx->p));
    func_00f5df38(id, id + 1, cx->x8);
    func_00f5de50(cx->x8, 0);
    e = D_00F85240.e;
    for (; i < D_00F85240.x0; i++, e++) {
        k = e->h4 - 1;
        md = func_001bb658(k);
        func_001bb6d0(e->h4 - 1);
        if (k == 140) {
            sceVu0CopyMatrix((void *)(cx->w + 16), ms);
        } else {
            sceVu0CopyMatrix((void *)(cx->w + 16), D_00F872C0);
        }
        func_00f5dd78(cx->w + 144, cx->w + 80, m, D_00FBDAB0, e);
        a = 0;
        if (md->x9 != 255) a = func_00f200c8(((volatile Md34 *)md)->x9);
        b = func_00f200a8(md->x8);
        *(f32 *)(cx->w + 76) = al;
        c = func_00f35798(md->x8);
        if (func_00f358d8(e->h4 - 1, buf) != 0) {
            cx->w = func_00f676b8(D_00F8C224, cx->x8, cx->w, e->b8, b, buf, c);
        } else {
            cx->w = func_00f67530(D_00F8C224, cx->x8, cx->w, e->b8, b, a, c, D_00FBB850[k]);
        }
    }
    func_00f5e6e0(cx->x8);
    id += 2;
    cx->p = func_00f66ac8(cx->p);
    p = func_00f66b78(cx->p);
    p[1] = 24;
    p[0] = 0x0000740000007000;
    p += 2;
    cx->p = p;
    func_00f66b90(p);
    func_00f66f78(id, func_00f66ae0(cx->p));
}
