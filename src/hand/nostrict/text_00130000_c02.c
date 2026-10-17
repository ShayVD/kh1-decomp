/* Hand-matched functions (worker c02). Built without strict aliasing. */
#include "common.h"

typedef f32 C02Vec[4];

typedef struct {
    u8 pad00[0x4C];
    u16 x4c;
    u8 pad4e[0x54 - 0x4E];
    s8 x54;
} C02Desc;

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xc;
    f32 x10;
} C02Rec;

typedef struct {
    u8 pad00[4];
    u8 x4;
    u8 pad05[0x10 - 5];
    C02Rec *recs;
} C02Info;

typedef struct {
    u8 pad00[6];
    u8 x6;
    u8 pad07[0x10 - 7];
    C02Vec pos;      /* 0x10 */
    u8 pad20[0x10];
    C02Vec rot;      /* 0x30 */
    C02Vec scale;    /* 0x40 */
    u8 pad50[0xD0 - 0x50];
    C02Vec mtx[4];   /* 0xD0 */
    u8 pad110[0x130 - 0x110];
    C02Desc *desc;   /* 0x130 */
    C02Info *info;   /* 0x134 */
    u8 pad138[0x1CC - 0x138];
    u32 x1cc;
    u8 pad1d0[0x1F0 - 0x1D0];
    C02Vec v1f0;
    u8 pad200[0x370 - 0x200];
    union {
        u64 w;
        struct {
            u64 lo : 44;
            u64 b44 : 1;
            u64 b45 : 1;
            u64 mid : 11;
            u64 b57 : 1;
            u64 hi : 6;
        } b;
    } fl;
    u8 pad378[0x3A0 - 0x378];
    void *x3a0;
    u8 pad3a4[0x450 - 0x3A4];
    C02Vec v450;
    u8 pad460[0x480 - 0x460];
    f32 x480;
} C02Obj;

typedef struct {
    C02Vec pos;
    C02Vec dir;
    C02Vec out;
    s16 hit;
    u8 pad[0xE];
} C02Ray;

extern u8 D_002C58A0[];
extern u8 D_002C58D0[];
extern u8 D_003044C0[];
extern u8 D_003044B0[];

void sceVu0CopyMatrix(void *dst, void *src);
f32 func_00120c88(f32 x);
void func_00267768(void *dst, void *src, f32 a);
void func_00267810(void *dst, void *src, f32 a);
void func_002676c0(void *dst, void *src, f32 a);
void func_002672f8(void *dst, void *m, void *v);
void func_00267530(void *dst, void *a, void *b);
void func_00267518(void *dst, void *a, void *b);
void func_00267560(void *dst, void *a, f32 s);
void func_002675a8(void *dst, void *src);
void func_00267370(void *dst, void *a, void *b);
void func_002673b8(void *dst, void *src);
void func_00118668(C02Ray *r);
s32 func_001232f0(C02Obj *o);
void func_00121958(void *dst, void *src, void *v);
void func_00136cc0(C02Obj *o);

static inline f32 c02_fabsf(f32 x) { return __builtin_fabsf(x); }

void func_00136d38(C02Obj *o)
{
    C02Vec scale;
    C02Vec pts[2];
    C02Vec dir;
    C02Ray ray;
    C02Vec save[4];
    f32 *m;
    f32 *up;
    s32 i, j;
    u16 k;

    m = o->mtx[0];
    sceVu0CopyMatrix(save, m);
    if ((s32)(o->fl.w >> 44) & 1) {
        f32 *r = o->rot;
        i = 2;
        do {
            *r = func_00120c88(*r);
            r++;
        } while (--i >= 0);
        func_00267768(m, D_002C58D0, o->rot[0]);
        func_00267810(m, m, o->rot[1]);
        func_002676c0(m, m, o->rot[2]);
        if (o->desc->x54 == 10) {
            func_002672f8(o->mtx[3], m, D_003044C0);
            func_00267530(o->mtx[3], o->pos, o->mtx[3]);
            func_00267518(o->mtx[3], o->mtx[3], D_003044C0);
            o->mtx[0][3] = 0;
            o->mtx[1][3] = 0;
            o->mtx[2][3] = 0;
            o->mtx[3][3] = 1.0f;
            return;
        }
    } else {
        if (func_001232f0(o) && o->info->x4 >= 3) {
            C02Rec *rec = o->info->recs + 1;
            for (i = 0; i < 2; i++) {
                func_00267560(dir, o->rot, rec->x4 * 100.0f);
                func_00267518(pts[i], o->pos, dir);
                func_002675a8(ray.pos, pts[i]);
/*P*/
                ray.pos[1] -= rec->x8 + rec->xc;
                ray.pos[3] = 1.0f;
                ray.dir[0] = ray.dir[2] = 0.0f;
                ray.dir[1] = rec->xc * 2.0f;
                ray.dir[3] = 1.0f;
                rec++;
/*Q*/
                func_00118668(&ray);
                if (ray.hit >= 0)
                    func_002675a8(pts[i], ray.out);
            }
            func_00267530(dir, pts[1], pts[0]);
            func_002673b8(dir, dir);
            up = dir;
        } else {
            up = o->rot;
        }
        func_00267370(m, up, D_003044B0);
        func_002673b8(m, m);
        func_00267530(o->mtx[2], D_002C58A0, up);
        func_00267370(o->mtx[1], o->mtx[2], m);
        func_002673b8(o->mtx[1], o->mtx[1]);
    }
    o->fl.w &= ~(1UL << 45);
    func_002675a8(scale, o->scale);
    scale[1] *= o->x480;
    k = o->desc->x4c;
    if (k != 0x204 && k != 0x23) {
        for (i = 0; i < 3; i++) {
            if (c02_fabsf(scale[i] - 1.0f) > 0.0001f) {
                o->fl.w |= 1UL << 45;
                break;
            }
        }
    }
    if ((s32)(o->fl.w >> 45) & 1)
        func_00121958(m, m, scale);
    func_002675a8(o->mtx[3], o->pos);
    o->mtx[0][3] = 0;
    o->mtx[3][3] = 1.0f;
    o->mtx[1][3] = 0;
    o->mtx[2][3] = 0;
    if (o->x3a0)
        func_00136cc0(o);
    if (o->x1cc & 8) {
        f32 t = o->v450[3];
        o->v450[3] = 0;
        func_002672f8(o->v1f0, m, o->v450);
        o->v1f0[3] = t;
    }
    if (o->x6 == 5) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (save[i][j] != o->mtx[i][j]) {
                    o->fl.w &= ~(1UL << 57);
                    return;
                }
            }
        }
    }
}
