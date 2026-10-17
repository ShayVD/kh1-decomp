typedef struct { f32 x, y, z, w; } V4f;
typedef struct { u8 pad[0x30]; u64 d30; u8 pad38[8]; V4f p; f32 f50; f32 f54; u8 pad58[4]; s32 w5c; } Sub148;
typedef struct {
    u32 flags;
    u8 pad4[0xC];
    V4f pos;
    u8 pad20[0x148 - 0x20];
    Sub148 *p148;
    u8 pad14c[0x1CC - 0x14C];
    u32 w1cc;
    u8 pad1d0[0x2A0 - 0x1D0];
    V4f v2a0;
    V4f v2b0;
    f32 f2c0;
    u8 pad2c4[0x2D0 - 0x2C4];
    u32 w2d0;
    u8 pad2d4[0x2F0 - 0x2D4];
    V4f v2f0;
    f32 f300;
    f32 f304;
    u8 pad308[0x314 - 0x308];
    u16 h314;
} ObjF3;
typedef struct { V4f p; V4f d; V4f hit; s16 h30; s32 w34; u8 pad38[8]; } Ray;
s32 func_001166e8(V4f *);
void func_002673b8(V4f *, V4f *);
void func_00267e90(V4f *, V4f *, f32);
void func_00267530(V4f *, V4f *, V4f *);
s32 func_001429f8(V4f *, V4f *, V4f *);

s32 func_00143080(ObjF3 *o, V4f *v) {
    V4f t, hit;
    s32 r = 1;
    if (!func_001166e8(&o->v2a0) && !(o->w2d0 & 1)) return r;
    func_002673b8(&t, v);
    func_00267e90(&t, &t, o->f2c0 + 10.0f);
    t.y = -200.0f;
    t.w = 200.0f;
    if (func_001429f8(&o->v2a0, &t, &hit)) goto zero;
    func_00267530(&o->v2b0, &hit, &o->v2a0);
    o->v2b0.w = 1.0f;
    r = 1;
    if (!func_001166e8(&o->v2a0)) return r;
    if (o->w2d0 & 1) return 0;
    return 1;
zero:
    return 0;
}
