/* 10 words left (588 vs 592): *arg0 = e->c must be word lw/sw in target order; struct copy gives ldl/sdl, memcpy/field copies reorder. ~120 manual perms + permuter (-j1, 10 min). */
typedef struct { s32 a, b, c, d, e; } C491e0;
typedef struct { C491e0 c; s32 pad; } E491e0;
typedef struct { u8 pad[0x10]; E491e0 ent[5]; s32 pad88; s32 idx; } W491e0;
typedef struct { u64 d; u64 r; } GP491e0;
void func_00f63260(C491e0 *);
s32 func_00f66ac8(s32);
s32 func_00f66ae0(GP491e0 *);
GP491e0 *func_00f66b78(s32);
void func_00f66b90(GP491e0 *);
void func_00f66f78(s32, void *);
extern W491e0 *D_00F9B540;
extern u8 D_00FA5380[];

E491e0 *func_00f491e0(C491e0 *arg0) {
    E491e0 *e;
    GP491e0 *p;

    e = &D_00F9B540->ent[D_00F9B540->idx];
    func_00f66f78(10000, D_00FA5380);
    arg0->a = e->c.a;
    arg0->b = e->c.b;
    arg0->c = e->c.c;
    arg0->d = e->c.d;
    arg0->e = e->c.e;
    func_00f63260(arg0);
    p = func_00f66b78(func_00f66ac8(arg0->a));
    p->d = 0x740000007000;
    p->r = 0x18;
    p++;
    p->d = 0x30000;
    p->r = 0x47;
    p++;
    func_00f66b90(p);
    func_00f66f78(10000, (void *)func_00f66ae0(p));
    p = func_00f66b78(func_00f66ac8((s32)p));
    p->d = 0x740000007000;
    p->r = 0x18;
    p++;
    p->d = 0x5000D;
    p->r = 0x47;
    p++;
    p->d = 0x44;
    p->r = 0x42;
    p++;
    func_00f66b90(p);
    func_00f66f78(11840, (void *)func_00f66ae0(p));
    p = func_00f66b78(func_00f66ac8((s32)p));
    p->d = 0x740000007000;
    p->r = 0x18;
    p++;
    if (*(s16 *)((u8 *)D_00F9B540 + 0x76) != 2) {
        p->d = 0x30003;
        p->r = 0x47;
        p++;
        p->d = 0x46;
        p->r = 0;
        p++;
        p->d = (u64)0x3F800000 << 32;
        p->r = 1;
        p++;
        p->d = 0x74007000;
        p->r = 5;
        p++;
        p->d = 0x8C009000;
        p->r = 5;
        p++;
    }
    p->d = 0x5000D;
    p->r = 0x47;
    p++;
    func_00f66b90(p);
    func_00f66f78(12560, (void *)func_00f66ae0(p));
    arg0->a = (s32)p;
    return e;
}
