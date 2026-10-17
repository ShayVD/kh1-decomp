#include "common.h"
typedef struct { u64 a, b; } Q;
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
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
Q *func_00122048(s32, s32);
s32 func_001f4570(Ob *);
s32 func_001f45e0(Ob *);
s32 sceGsSyncPath(s32, u16);
void func_001220b8(void *);
Q *func_0011fb38(s32 reg, u64 val, Q *p);

void func_001f86e0(Ob *o, s32 x, s32 y, s32 w, s32 h) {
    s32 x0, y0, x1, y1, cx, cy, t;
    Q *buf, *e, *p;
    void *ub;
    x0 = x + ((o->xb0 - 0x7000) >> 4);
    y0 = y + ((o->xb4 - 0x7400) >> 4);
    x1 = x0 + w - 1;
    y1 = y0 + h - 1;
    if (o->flags & 1) {
        cx = (func_001f4570(o) - 0x7000) >> 4;
        cy = (func_001f45e0(o) - 0x7400) >> 4;
        x0 = cx + (x0 - cx) * o->sx;
        x1 = cx + (x1 - cx) * o->sx;
        y0 = cy + (y0 - cy) * o->sy;
        y1 = cy + (y1 - cy) * o->sy;
        if (x1 < x0) { t = x0; x0 = x1; x1 = t; }
        if (y1 < y0) { t = y0; y0 = y1; y1 = t; }
    }
    if (x0 < 512 && y0 < 384 && x1 >= 0 && y1 >= 0) {
        if (x1 >= 512) x1 = 511;
        if (x0 < 0) x0 = 0;
        if (y0 < 0) y0 = 0;
        if (y1 >= 384) y1 = 383;

        p = func_00122048(1024, 128);
        buf = p;
        p = buf + 1;
        ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
        p->a = 0x1000000000008001;
        p->b = 14;

        e = func_0011fb38(64, (u64)x0 | ((u64)x1 << 16) | ((u64)y0 << 32) | ((u64)y1 << 48), p + 1);
        buf->a = ((e - buf) - 1) | 0x70000000;
        func_00266f38(func_00266c08(2), ub);
        sceGsSyncPath(0, 0);
        func_001220b8(buf);
    }
}

void func_001f8950(Ob *o, s32 x0, s32 y0, s32 w, s32 h) {
    s32 x1, y1, cx, cy, t;
    Q *buf, *e, *p;
    void *ub;
    x1 = x0 + w - 1;
    y1 = y0 + h - 1;
    if (o->flags & 1) {
        cx = (func_001f4570(o) - 0x7000) >> 4;
        cy = (func_001f45e0(o) - 0x7400) >> 4;
        x0 = cx + (x0 - cx) * o->sx;
        x1 = cx + (x1 - cx) * o->sx;
        y0 = cy + (y0 - cy) * o->sy;
        y1 = cy + (y1 - cy) * o->sy;
        if (x1 < x0) { t = x0; x0 = x1; x1 = t; }
        if (y1 < y0) { t = y0; y0 = y1; y1 = t; }
    }
    if (x0 < 512 && y0 < 384 && x1 >= 0 && y1 >= 0) {
        if (x1 >= 512) x1 = 511;
        if (x0 < 0) x0 = 0;
        if (y0 < 0) y0 = 0;
        if (y1 >= 384) y1 = 383;

        p = func_00122048(1024, 128);
        buf = p;
        p = buf + 1;
        ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
        p->a = 0x1000000000008001;
        p->b = 14;

        e = func_0011fb38(64, (u64)x0 | ((u64)x1 << 16) | ((u64)y0 << 32) | ((u64)y1 << 48), p + 1);
        buf->a = ((e - buf) - 1) | 0x70000000;
        func_00266f38(func_00266c08(2), ub);
        sceGsSyncPath(0, 0);
        func_001220b8(buf);
    }
}

void func_001f8ba8(Ob *o) {
    s32 x0, y0, x1, y1, cx, cy, t;
    f32 fsx, fsy;
    Q *buf, *e, *p;
    void *ub;
    x0 = (o->xb0 - 0x7000) >> 4;
    y0 = (o->xb4 - 0x7400) >> 4;
    x1 = x0 + (o->wb8 >> 4) - 1;
    y1 = y0 + (o->hba >> 4) - 1;
    if (o->flags & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        fsx = o->sx; fsy = o->sy;
        y0 = cy + (y0 - cy) * fsy;
        y1 = cy + (y1 - cy) * fsy;
        x0 = cx + (x0 - cx) * fsx;
        x1 = cx + (x1 - cx) * fsx;

        if (x1 < x0) { t = x0; x0 = x1; x1 = t; }
        if (y1 < y0) { t = y0; y0 = y1; y1 = t; }
    }
    if (x0 < 512 && y0 < 384 && x1 >= 0 && y1 >= 0) {
        if (x1 >= 512) x1 = 511;
        if (x0 < 0) x0 = 0;
        if (y0 < 0) y0 = 0;
        if (y1 >= 384) y1 = 383;

        p = func_00122048(1024, 128);
        buf = p;
        p = buf + 1;
        ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
        p->a = 0x1000000000008001;
        p->b = 14;

        e = func_0011fb38(64, (u64)x0 | ((u64)x1 << 16) | ((u64)y0 << 32) | ((u64)y1 << 48), p + 1);
        buf->a = ((e - buf) - 1) | 0x70000000;
        func_00266f38(func_00266c08(2), ub);
        sceGsSyncPath(0, 0);
        func_001220b8(buf);
    }
}
