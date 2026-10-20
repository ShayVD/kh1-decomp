#include "common.h"

typedef struct {
    u8 pad0[0x48];
    s32 x48;
    u8 pad4c[0x74 - 0x4c];
    f32 sx, sy;
    u8 pad7c[0x90 - 0x7c];
    s32 x90;
    f32 x94;
    u8 pad98[0xb0 - 0x98];
    s32 xb0, xb4;
    s16 xb8, xba;
} Wnd2;
extern u8 D_00642D30[];
extern u8 D_00642DE0[];
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
u64 *func_00122048(s32, s32);
s32 sceGsSyncPath(s32, s32);
void func_001220b8(void *);
s32 func_001f4570(Wnd2 *);
s32 func_001f45e0(Wnd2 *);

void func_00219598(Wnd2 *w, s32 px, s32 py) {
    u64 *buf, *p;
    s32 *q;
    u32 ub;
    s32 x, y, cx, cy;
    f32 fcx, fcy, sx, sy, t0, t1, t2, t3;
    func_00266f38(func_00266c08(2), D_00642D30);
    func_00266f38(func_00266c08(2), D_00642DE0);
    buf = func_00122048(1024, 128);
    p = buf + 2;
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    p[0] = 0x5000000000008001;
    p[1] = 0xeeeee;
    p[2] = 0x4000d;
    p[3] = 71;
    p[4] = 0;
    p[5] = 63;
    p[6] = 0x2006D005E1313600;
    p[7] = 6;
    p[8] = 97;
    p[9] = 20;
    p[10] = 68;
    p[11] = 66;
    p[12] = 0x50ab400000008001;
    p[13] = 0x4343e;
    p[14] = (u32)(w->x90 << 24 | 0x808080);
    p[15] = 1;
    q = (s32 *)p;
    q[32] = 24;
    q[33] = 24;
    q[36] = x = w->xb0 + px * 16;
    q[37] = y = w->xb4 + py * 16;
    q[38] = 0x100000;
    q[39] = 0x8000;
    q[40] = 2168;
    q[41] = 1368;
    q[44] = x + 2160;
    q[45] = y + 1360;
    q[46] = 0x100000;
    q[47] = 0;
    if (w->x48 & 1) {
        cx = func_001f4570(w);
        cy = func_001f45e0(w);
        sx = w->sx;
        sy = w->sy;
        fcx = cx;
        fcy = cy;
        t0 = fcx + (q[36] - cx) * sx;
        t1 = fcy + (q[37] - cy) * sy;
        t2 = fcx + (q[44] - cx) * sx;
        t3 = fcy + (q[45] - cy) * sy;
        q[36] = t0;
        q[37] = t1;
        q[44] = t2;
        q[45] = t3;
    }
    buf[0] = ((((s32)p - (s32)buf + 192) >> 4) - 1) | 0x70000000;
    func_00266f38(func_00266c08(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}
#include "data/bss_0064_mixed.h"
