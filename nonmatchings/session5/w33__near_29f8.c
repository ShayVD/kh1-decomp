typedef struct { f32 x, y, z, w; } V4f;
typedef struct { V4f p; V4f d; V4f hit; s16 h30; s32 w34; u8 pad38[8]; } Ray;
void func_00267560(V4f *, V4f *, f32);
s32 func_00119688(Ray *);
void func_00118648(Ray *);
void func_00118608(Ray *);
void func_002675a8(V4f *, V4f *);

s32 func_001429f8(V4f *a, V4f *b, V4f *c) {
    Ray r;
    f32 one = 1.0f;
    r.p.x = a->x;
    r.p.z = a->z;
    r.p.y = a->y + b->y;
    r.p.w = one;
    func_00267560(&r.d, b, 1.5f);
    r.d.w = one;
    r.d.y = 0;
    if (func_00119688(&r) >= 0) return 3;
    func_00118648(&r);
    if (r.h30 >= 0) return 3;
    r.p.x += b->x;
    r.p.z += b->z;
    r.d.x = 0;
    r.d.y = b->w - b->y;
    r.d.z = 0;
    func_00118608(&r);
    if (r.h30 < 0) return 3;
    func_002675a8(c, &r.hit);
    func_00118648(&r);
    if (r.h30 >= 0 && r.hit.y < c->y) return 3;
    return 0;
}
