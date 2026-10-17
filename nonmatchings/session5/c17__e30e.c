#include "common.h"

typedef struct { u8 b[192]; } Spr17;
typedef struct {
    void *x0; void *x4; u8 pad8[4]; void *xc; void *x10;
    Spr17 *x14; void *x18; void *x1c; Spr17 *x20; Spr17 *x24;
    Spr17 *x28; Spr17 *x2c; void *x30; Spr17 *x34;
    u8 pad38[0x1c0 - 0x38]; void *x1c0;
} Ob17;
typedef struct { s32 x0; s32 x4; s32 x8; s32 cur; s32 n; u8 id[16]; u8 col[16]; } Mn17;
extern f32 D_00650DD0;
extern f32 D_00650DD4;
extern s32 D_00449900;
extern s32 D_00449908[];
void func_00239778(s32, void *, void *, void *, s32, s32, f32);
void func_002399f0(s32, void *, void *, s32, s32, s32 *, f32);
void func_0024ac08(void *, s32 *);
void func_0024ac68(void *, s32 *);
void func_00239558(s32, s32, s32, s32);

void func_00239e30(s32 mode, Mn17 *m, s32 big, s32 on, Ob17 *o, s32 x, s32 y, f32 f) {
    s32 pos[4];
    s32 buf[16];
    f32 s;
    s32 i, yy, xx, on2;
    Spr17 *sel;
    D_00650DD0 = D_00650DD4 = f;
    s = 1.0f;
    if (big == 0) s = 0.5f;
    xx = x;
    yy = y;
    func_00239778(on, o->xc, o->x28, o->x0, xx, yy, s);
    if (mode == 0) {
        func_0024ac68(o->x1c0, buf);
        func_002399f0(on, o->x10, o->x4, xx, yy, buf, s);
    } else {
        func_00239778(on, o->x10, 0, o->x4, xx, yy, s);
    }
    yy = y + 20;
    for (i = 0; i < m->n - 1; i++, yy += 22) {
        if (m->cur == i) continue;
        if (o->x2c) func_00239778(on, &o->x14[i], &o->x2c[i], o->x0, x, yy, s);
        else func_00239778(on, &o->x14[i], 0, o->x0, x, yy, s);
        func_0024ac08(&o->x14[i], pos);
        func_00239558(m->id[i], x + pos[0], yy + pos[1], m->col[i]);
        if (D_00449900 && i == m->cur + 1)
            func_00239778(on, o->x1c, 0, o->x0, x + pos[0], yy + pos[1] - 22, s);
    }
    if (m->cur != m->n - 1) {
        func_00239778(on, o->x18, o->x30, o->x0, x, yy, s);
        func_0024ac08(o->x18, pos);
        func_00239558(m->id[i], x + pos[0], yy + pos[1], m->col[i]);
        if (D_00449900 && i == m->cur + 1)
            func_00239778(on, o->x1c, 0, o->x0, x + pos[0], yy + pos[1] - 22, s);
    }
    if (big) {
        xx = x + 11;
        on2 = m->cur != D_00449908[mode + 1];
        yy = y + m->cur * 22 + 18;
        sel = 0;
        for (i = 0; i < 4; i++) {
            if (o->x34) func_00239778(on2, &o->x20[i], &o->x34[i], o->x0, xx, yy, s);
            else func_00239778(on2, &o->x20[i], 0, o->x0, xx, yy, s);
        }
        switch (mode) {
        case 0:
            if (m->id[m->cur] == 1) sel = &o->x24[0];
            else if (m->id[m->cur] == 2) sel = &o->x24[1];
            else if (m->id[m->cur] == 3) sel = &o->x24[2];
            break;
        case 1:
            if (m->id[m->cur] == 6) sel = &o->x24[1];
            else sel = &o->x24[0];
            break;
        case 2:
        case 3:
            sel = &o->x24[0];
            break;
        }
        if (sel) func_00239778(on2, sel, 0, o->x4, xx, yy, s);
        func_0024ac08(&o->x20[1], pos);
        func_00239558(m->id[m->cur], xx + pos[0], yy + pos[1] + 2, m->col[m->cur]);
        D_00449908[mode + 1] = m->cur;
    }
}
