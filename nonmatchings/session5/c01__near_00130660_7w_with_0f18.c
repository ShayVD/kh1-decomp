#include "common.h"

typedef f32 C01Mat[4][4];
typedef struct { u32 b0 : 1; u32 r : 31; } C01B32;
typedef struct { u8 pad[0x4c]; u16 x4c; } C01Sub130;
typedef struct {
    u32 flags0;
    u8 pad004[0x10 - 0x4];
    f32 x10[4];
    u8 pad020[0x50 - 0x20];
    f32 x50[4];
    u8 pad060[0xd0 - 0x60];
    C01Mat xd0;
    u8 pad110[0x130 - 0x110];
    C01Sub130 *x130;
    u8 pad134[0x15c - 0x134];
    s32 x15c;
    u32 b0 : 1;
    u32 b1 : 1;
    u32 b2 : 1;
    u32 b3 : 1;
    u32 b4 : 1;
    u32 b5 : 1;
    u32 b6 : 1;
    u32 b7 : 1;
    u32 b8 : 1;
    u32 b9 : 1;
    u32 b10 : 1;
    u32 b11 : 1;
    u32 rest : 20;
    s32 x164;
    s32 x168;
    f32 f16c;
    f32 f170;
    f32 f174;
    s32 x178;
    u8 pad17c[0x180 - 0x17c];
    f32 f180;
    u8 pad184[0x1cc - 0x184];
    s32 x1cc;
    u8 pad1d0[4];
    s32 *x1d4;
    u8 pad1d8[0x1f0 - 0x1d8];
    u8 x1f0[0x10];
    f32 x200[4];
    f32 x210[4];
    u8 pad220[0x230 - 0x220];
    C01Mat x230;
    f32 x270[4];
    f32 f280;
    f32 f284;
    f32 f288;
    f32 f28c;
    f32 f290;
} __attribute__((aligned(8))) C01Obj3;

extern void *D_002E31E8;
extern f32 D_002C58A0[4];

void sceVu0CopyMatrix(C01Mat, C01Mat);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_002672f8(f32 *, C01Mat, f32 *);
s32 func_0012ffd0(C01Obj3 *);
void func_00167688(s32, s32, void *);
void func_00130898(C01Obj3 *, C01Mat);
s32 func_00130e48(C01Obj3 *, C01Mat);
void func_00130c28(C01Obj3 *, f32, f32);
void func_00130660(C01Obj3 *, C01Mat, s32, f32, f32);
void func_00130210(C01Obj3 *, s32);
void func_00130598(C01Obj3 *, C01Mat, f32, f32);
void func_001655e0(C01Mat, s32, f32, s32);
s32 func_00167680(s32);
void func_001752a0(s32, void *);
void func_001676b0(s32, f32 *);
void func_00167d70(s32, f32);

typedef struct {
    u8 pad0[0x50];
    f32 x50[4];
    u8 pad60[0x15c - 0x60];
    s32 x15c;
    u64 flags;
    s32 x168;
    f32 f16c;
    f32 f170;
    f32 f174;
    u8 pad178[0x1d4 - 0x178];
    s32 *x1d4;
    u8 pad1d8[0x220 - 0x1d8];
    f32 x220[4];
    C01Mat x230;
    f32 x270[4];
    f32 f280;
    f32 f284;
} __attribute__((aligned(8))) O660;
extern f32 D_002BBDFC;
void func_00166248(C01Mat, s32, s32);
void func_00165cf8(C01Mat, s32, f32, s32);
void func_001676d8(s32, f32 *);
void func_002673f8(C01Mat, C01Mat);
void func_001675c0(s32);
s32 func_00167698(s32);
void func_00130648(C01Obj3 *);

void func_00130660(C01Obj3 *a, C01Mat m, s32 idx, f32 d, f32 e) {
    O660 *o = (O660 *)a;
    f32 v[4];
    C01Mat t;
    f32 k = D_002BBDFC * o->f284;
    s32 s = o->x1d4[idx];
    if (((s32)(o->flags >> 1) & 1) && k < e) {
        if (0.0f < o->f170) {
            func_00166248(m, o->x15c, s);
        } else {
            sceVu0CopyMatrix(t, m);
            if ((s32)(o->flags >> 12) & 1) {
                func_002675a8(t[3], o->x50);
                t[3][3] = 1.0f;
            }
            func_00165cf8(t, o->x15c, d, s);
        }
        func_001676d8(o->x15c, v);
        v[3] = 0;
        func_002673f8(t, m);
        func_002672f8(o->x270, t, v);
        o->x270[3] = 0;
        o->f170 = e;
        o->f174 = k;
        func_002675a8(v, o->x220);
        v[3] = 0;
        func_002672f8(v, o->x230, v);
        func_00267518(m[3], m[3], v);
        func_00130598(a, m, k / e, 1.0f - k / e);
    } else {
        if (0.0f < o->f170) func_001675c0(o->x15c);
        o->f170 = 0.0f;
        func_001655e0(m, o->x15c, d, s);
        o->f280 = func_00167698(s);
        if (!((s32)(o->flags >> 6) & 1)) func_00130648(a);
    }
    if (s) o->flags |= 2;
    o->x168 = idx;
    o->f16c = d;
}

void func_00130f18(C01Obj3 *o, f32 dt) {
    f32 a[4];
    f32 b[4];
    C01Mat m;
    f32 *t3;
    s32 fl;
    s32 has4;
    s32 did;
    s32 old;
    f32 d;
    f32 n;
    f32 h;

    D_002E31E8 = (u8 *)o->x130 + 0x68;
    if (o->b4) return;
    sceVu0CopyMatrix(m, o->xd0);
    if (o->b2) {
        t3 = o->x210;
        func_00267530(m[3], m[3], t3);
        m[3][3] = 1.0f;
    } else {
        t3 = o->x210;
    }
    func_002675a8(a, m[3]);
    fl = o->x1cc;
    if ((o->flags0 & 0x10) || o->b11) fl &= ~1;
    if (o->x130->x4c == 507) {
        has4 = fl & 4;
        fl &= ~4;
    } else {
        has4 = 0;
    }
    did = 0;
    func_00167688(o->x15c, func_0012ffd0(o) ? fl | 0x20 : fl, o->x1f0);
    o->b8 = 0;
    if (((s32 *)o)[0x160 / 4] & 1) {
        func_00130898(o, m);
        did = 1;
        func_00130e48(o, m);
        o->b0 = 0;
        o->b8 = 1;
    } else {
        dt *= o->f284;
        if (o->f170 > 0.0f) {
            n = o->f174 + dt;
            d = n - o->f170;
            o->f174 = n;
            if (!(d < 0.0f)) {
                func_00130c28(o, o->f16c, o->f16c + d);
                func_00130660(o, m, o->x168, o->f16c + d, 0.0f);
                func_00130210(o, o->x164);
            } else {
                h = n / o->f170;
                func_00130598(o, m, h, 1.0f - h);
            }
        } else if (!func_00130e48(o, m)) {
            h = o->f16c;
            n = h + dt;
            o->f16c = n;
            func_00130c28(o, h, n < o->f280 ? n : o->f280);
            d = o->f16c - o->f28c;
            if (d < 0.0f) {
                func_001655e0(m, o->x15c, o->f16c, o->x1d4[o->x168]);
            } else if (o->x178 > 0) {
                o->f180 += d;
                func_00130898(o, m);
                func_002675a8(a, m[3]);
                func_00130e48(o, m);
            } else {
                if (o->b2) {
                    func_00267518(m[3], m[3], t3);
                    func_002675a8(a, m[3]);
                    func_002675a8(t3, D_002C58A0);
                }
                if (o->b3) {
                    func_00130660(o, m, o->x168, o->f280, 0.0f);
                } else {
                    func_00130660(o, m, o->x168, o->f288 + d, o->f290);
                    func_00130c28(o, o->f288, o->f288 + d);
                }
            }
        }
    }
    fl = o->x1cc;
    o->x1cc = func_00167680(o->x15c);
    if (fl & 1) o->x1cc |= 1;
    if (o->x1cc & 0x100000) o->flags0 &= ~0x1004;
    if (has4) {
        func_001752a0(o->x15c, o->x1f0);
        o->b10 = 1;
    } else {
        o->b10 = 0;
    }
    if (o->f170 > 0.0f) {
        func_002672f8(b, m, o->x270);
        func_00267518(o->x50, o->x10, b);
    } else {
        func_001676b0(o->x15c, o->x50);
    }
    if (o->b2 && o->f170 <= 0.0f && !did) {
        func_00267530(b, o->x50, a);
        func_00267530(o->x200, b, t3);
        func_002675a8(t3, b);
    } else {
        func_002675a8(o->x200, D_002C58A0);
        func_002675a8(t3, D_002C58A0);
    }
    sceVu0CopyMatrix(o->x230, m);
    func_00167d70(o->x15c, dt);
}
