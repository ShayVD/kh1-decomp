#include "common.h"
typedef struct { u64 a, b; } Q;
typedef struct { u64 tag, ad; u64 d2, d3; u64 d4, d5; s32 x0, y0, z0, w0; s32 x1, y1, z1, w1; } Pk;
typedef struct {
    u8 pad0[0x48];
    s32 flags;
    u8 pad4c[0x6c - 0x4c];
    s32 x6c;
    u8 pad70[4];
    f32 sx;
    f32 sy;
    u8 pad7c[0x90 - 0x7c];
    s32 x90;
    u8 pad94[0xb0 - 0x94];
    s32 xb0;
    s32 xb4;
    s16 wb8;
    s16 hba;
} Ob;
extern Q D_003F1A70[];
extern Q D_003F1E70[];
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
Q *func_00122048(s32, s32);
u32 func_001edd88(s32, s32);
s32 func_001f4570(Ob *);
s32 func_001f45e0(Ob *);
s32 sceGsSyncPath(s32, u16);
void func_001220b8(void *);

void func_002053e8(Ob *o, s32 px, s32 py, s32 pw, s32 ph, s32 col) {
    Q *buf;
    Pk *p;
    void *ub;
    s32 a, b, x, y;
    f32 fa, fb, sx, sy, t0, t1, t2, t3;
    func_00266f38(func_00266c08(2), D_003F1A70);
    buf = func_00122048(1024, 128);
    p = (Pk *)(buf + 1);
    ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p->tag = 0x4023400000008001;
    p->ad = 0x44ee;
    p->d2 = 68;
    p->d3 = 66;
    p->d4 = func_001edd88(col, o->x90);
    p->d5 = 1;
    p->x0 = x = o->xb0 + px * 16;
    p->y0 = y = o->xb4 + py * 16;
    p->z0 = 0x100000;
    p->x1 = x + pw * 16;
    p->w0 = 0;
    p->w1 = 0;
    p->z1 = 0x100000;
    p->y1 = y + ph * 16;
    if (o->flags & 1) {
        a = func_001f4570(o);
        b = func_001f45e0(o);
        sx = o->sx;
        sy = o->sy;
        fa = a;
        fb = b;
        t0 = fa + (p->x0 - a) * sx;
        t1 = fb + (p->y0 - b) * sy;
        t2 = fa + (p->x1 - a) * sx;
        p->x0 = t0;
        p->y0 = t1;
        t3 = fb + (p->y1 - b) * sy;
        p->y1 = t3;
        p->x1 = t2;
    }
    buf->a = 0x70000005;
    func_00266f38(func_00266c08(2), ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}

void func_00205938(Ob *o, s32 col) {
    Q *buf;
    Pk *p;
    void *ub;
    s32 a, b, x, y;
    f32 fa, fb, sx, sy, t0, t1, t2, t3;
    func_00266f38(func_00266c08(2), D_003F1A70);
    buf = func_00122048(1024, 128);
    p = (Pk *)(buf + 1);
    ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p->tag = 0x4023400000008001;
    p->ad = 0x44ee;
    p->d2 = 68;
    p->d3 = 66;
    p->d4 = func_001edd88(col, o->x90);
    p->d5 = 1;
    p->x0 = x = o->xb0;
    p->y0 = y = o->xb4;
    p->z0 = 0x100000;
    p->w0 = 0;
    p->x1 = x + o->wb8;
    p->y1 = y + o->hba;
    p->z1 = 0x100000;
    p->w1 = 0;
    if (o->flags & 1) {
        a = func_001f4570(o);
        b = func_001f45e0(o);
        sx = o->sx;
        sy = o->sy;
        fa = a;
        fb = b;
        t0 = fa + (p->x0 - a) * sx;
        t1 = fb + (p->y0 - b) * sy;
        t2 = fa + (p->x1 - a) * sx;
        p->x0 = t0;
        p->y0 = t1;
        t3 = fb + (p->y1 - b) * sy;
        p->y1 = t3;
        p->x1 = t2;
    }
    buf->a = 0x70000005;
    func_00266f38(func_00266c08(2), ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}

void func_00206130(Ob *o, s32 px, s32 py, s32 pw, s32 ph, s32 col) {
    Q *buf;
    Pk *p;
    void *ub;
    s32 a, b, x, y;
    f32 fa, fb, sx, sy, t0, t1, t2, t3;
    func_00266f38(func_00266c08(2), D_003F1E70);
    buf = func_00122048(1024, 128);
    p = (Pk *)(buf + 1);
    ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p->tag = 0x4023400000008001;
    p->ad = 0x44ee;
    p->d2 = 68;
    p->d3 = 66;
    p->d4 = func_001edd88(col, o->x90);
    p->d5 = 1;
    p->x0 = x = o->xb0 + px * 16;
    p->y0 = y = o->xb4 + py * 16;
    p->z0 = 0x100000;
    p->x1 = x + pw * 16;
    p->w0 = 0;
    p->w1 = 0;
    p->z1 = 0x100000;
    p->y1 = y + ph * 16;
    if (o->flags & 1) {
        a = func_001f4570(o);
        b = func_001f45e0(o);
        sx = o->sx;
        sy = o->sy;
        fa = a;
        fb = b;
        t0 = fa + (p->x0 - a) * sx;
        t1 = fb + (p->y0 - b) * sy;
        t2 = fa + (p->x1 - a) * sx;
        p->x0 = t0;
        p->y0 = t1;
        t3 = fb + (p->y1 - b) * sy;
        p->y1 = t3;
        p->x1 = t2;
    }
    buf->a = ((Q *)(p + 1) - buf - 1) | 0x70000000;
    func_00266f38(func_00266c08(2), ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}

/* needs make: uses rodata */
typedef struct { u8 pad[0xac]; s32 kind; s32 pos; u8 padb4[4]; s16 size; } Obj4570;
s32 func_001f4570(Ob *ob) {
    Obj4570 *o = (Obj4570 *)ob;
    switch (o->kind) {
    case 0:
    case 1:
    case 2:
    default:
        return o->pos + o->size / 2;
    case 3:
    case 5:
    case 7:
        return o->pos;
    case 4:
    case 6:
    case 8:
        return o->pos + o->size - 16;
    }
}

void func_001f52e8(Ob *o) {
    Q *buf; Pk *p; void *ub; s32 a, b, x, y; f32 fa, fb, sx, sy, t0, t1, t2, t3;
    func_00266f38(func_00266c08(2), D_003F1A70);
    buf = func_00122048(1024, 128); p = (Pk *)(buf + 1);
    ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p->tag = 0x4023400000008001; p->ad = 0x44ee; p->d2 = 68; p->d3 = 66;
    p->d4 = func_001edd88(o->x6c, o->x90); p->d5 = 1;
    p->x0 = x = o->xb0; p->y0 = y = o->xb4; p->z0 = 0x100000; p->w0 = 0;
    p->x1 = x + o->wb8 * 16; p->y1 = y + o->hba * 16; p->z1 = 0x100000; p->w1 = 0;
    if (o->flags & 1) {
        a = func_001f4570(o); b = func_001f45e0(o);
        sx = o->sx; sy = o->sy; fa = a; fb = b;
        t0 = fa + (p->x0 - a) * sx; t1 = fb + (p->y0 - b) * sy; t2 = fa + (p->x1 - a) * sx;
        p->x0 = t0; p->y0 = t1; t3 = fb + (p->y1 - b) * sy; p->y1 = t3; p->x1 = t2;
    }
    buf->a = ((Q *)(p + 1) - buf - 1) | 0x70000000;
    func_00266f38(func_00266c08(2), ub); sceGsSyncPath(0, 0); func_001220b8(buf);
}
