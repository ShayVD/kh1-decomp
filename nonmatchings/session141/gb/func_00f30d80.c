/* 19 words / score 26; floats fixed by v[0],v[1],v[2] order with 'f32 t, fz, fx, fy' decl order. Left: the D_00F56DA8 lookup - orig hoists q*4 and q*4+8 before the d==0 test and reads x as base[q*4+8] (lb 0) and z as (base+q*4)[10]; tried (q+2)*4, s8[][4], struct table, (base+8)[q*4], q*=4, precomputed px/pz pointers (worse) */
typedef struct {
    u8 pad0[0x48];
    u8 loc[0x16];
    u16 f5e;
    u16 f60;
    u16 f62;
    u8 pad64[0x10D8 - 0x64];
    s32 ang;
} GbWorld;
extern GbWorld *D_00F56DC0;
extern s32 D_00F56DC4;
extern s8 D_00F56DA8[];
extern u8 D_00F61590[];
s32 func_001c00e8(s32, void *, kh1_u128);
void func_001c0078(s32);
void func_00f2e218(void);
f32 func_001befc8(s32, void *);
void func_00f2e538(f32 *);
void func_00f24240(s32, s32);
void func_001bfac8(void);
void func_001bbf88(void *, s32, s32);
u16 func_001bbdf0(void *);

void func_00f30d80(s32 d) {
    f32 v[3];
    s32 task;
    s32 i;
    s32 q;
    s32 x = 0;
    s32 z = 0;
    s32 y;
    f32 fx, fy, fz, t;
    task = func_001c00e8(-1, func_00f2e218, 0);
    D_00F56DC0->f60 = D_00F56DC0->f5e;
    q = D_00F56DC0->ang / 1024;
    if (d == 0) {
        z = D_00F56DA8[q * 4 + 10];
        x = D_00F56DA8[q * 4 + 8];
    }
    if (d == 1) {
        z = -D_00F56DA8[q * 4 + 10];
        x = -D_00F56DA8[q * 4 + 8];
    }
    y = (d == 2) ? -1 : 0;
    if (d == 3)
        y = 1;
    if (x | y | z) {
        fy = y;
        fx = x;
        fz = z;
        for (i = 0; i < 15; i++) {
            t = func_001befc8(i, D_00F61590);
            v[0] = fx * t * 3.1415927f / 180.0f;
            v[1] = fy * t * 3.1415927f / 180.0f;
            v[2] = fz * t * 3.1415927f / 180.0f;
            func_00f2e538(v);
            D_00F56DC0->f60 = D_00F56DC0->f5e;
            func_00f24240(D_00F56DC4, 0);
            func_001bfac8();
        }
        if (x != 0)
            func_001bbf88(D_00F56DC0->loc, 0, -x);
        if (z != 0)
            func_001bbf88(D_00F56DC0->loc, 2, -z);
        if (d == 2)
            func_001bbf88(D_00F56DC0->loc, 1, 1);
        if (d == 3)
            func_001bbf88(D_00F56DC0->loc, 1, -1);
        func_00f2e538(0);
    }
    D_00F56DC0->f62 = func_001bbdf0(D_00F56DC0->loc);
    D_00F56DC0->f60 = D_00F56DC0->f5e;
    func_00f24240(D_00F56DC4, 0);
    func_001c0078(task);
}
