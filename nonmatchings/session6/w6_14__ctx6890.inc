/* CONTEXT_ONLY copy of func_001c6890 (matched in src/hand/text_001b0000_h66.c) */
typedef struct { f32 x, y, z, w; } V4_ctx;
typedef struct {
    u64 flags; u8 pad8[200]; V4_ctx v208; V4_ctx v224; V4_ctx v240; V4_ctx v256; V4_ctx v272; f32 f288; f32 f292;
} Tw_c6890;
extern V4_ctx D_002E2780, D_002E2790;
extern f32 D_002E27A0, D_002E27A4;
void *memset(void *, s32, u32);
void sceVu0UnitMatrix(f32 (*m)[4]);
void func_001e9d00(V4_ctx *d, V4_ctx *a, V4_ctx *b, f32 t);
f32 func_001e9e58(V4_ctx *a, V4_ctx *b);
void func_002675a8(void *a, void *b);
void func_00267768(f32 (*d)[4], f32 (*s)[4], f32 r);
void func_00267810(f32 (*d)[4], f32 (*s)[4], f32 r);
void func_002676c0(f32 (*d)[4], f32 (*s)[4], f32 r);
void func_002672f8(void *d, f32 (*m)[4], void *s);
#define D_003C5510 (*(Tw_c6890 *)&D_003C5510)
CONTEXT_ONLY void func_001c6890(void) {
    V4_ctx a;
    f32 m[4][4] __attribute__((aligned(16)));
    V4_ctx r;

    memset(&a, 0, 16);
    a.w = 1.0f;
    memset(&r, 0, 16);
    func_002675a8(&a, &D_002E2780);
    func_002675a8(&D_003C5510.v208, &D_002E2790);
    D_003C5510.f288 = func_001e9e58(&a, &D_003C5510.v208);
    D_003C5510.f292 = D_002E27A0;
    func_001e9d00(&r, &D_003C5510.v208, &a, D_002E27A4);
/*P*/
    D_003C5510.v256.x = 0.0f;
    D_003C5510.v256.y = 0.0f;
    D_003C5510.v256.z = 1.0f;
    D_003C5510.v256.w = 1.0f;
    D_003C5510.v272.x = 0.0f;
    D_003C5510.v272.y = 1.0f;
    D_003C5510.v272.z = 0.0f;
    D_003C5510.v272.w = 1.0f;
/*Q*/
    sceVu0UnitMatrix(m);
    func_00267768(m, m, r.x);
    func_00267810(m, m, r.y);
    func_002672f8(&D_003C5510.v256, m, &D_003C5510.v256);
    func_002672f8(&a, m, &a);
    func_002675a8(&D_003C5510.v224, &r);
    sceVu0UnitMatrix(m);
    func_00267768(m, m, r.x);
    func_00267810(m, m, r.y);
    func_002676c0(m, m, r.z);
    func_002672f8(&D_003C5510.v272, m, &D_003C5510.v272);
}
#undef D_003C5510
