#include "common.h"

typedef f32 C01Mat[4][4];
typedef struct {
    u8 pad000[0x40];
    f32 x40[3];
    u8 pad04c[0x50 - 0x4c];
    f32 x50;
    f32 x54;
    f32 x58;
    u8 pad05c[0xc0 - 0x5c];
    f32 xc0;
    f32 xc4;
    f32 xc8;
    u8 pad0cc[0xd0 - 0xcc];
    C01Mat xd0;
    u8 pad110[0x2c4 - 0x110];
    f32 x2c4;
    u8 pad2c8[0x2cc - 0x2c8];
    s32 x2cc;
    u8 pad2d0[0x320 - 0x2d0];
    f32 x320;
    f32 x324;
    f32 x328;
    u8 pad32c[0x370 - 0x32c];
    u64 x370;
    u8 pad378[0x410 - 0x378];
    f32 x410;
    f32 x414;
} C01Obj4;
typedef struct { f32 v[6]; u16 n; u8 pad[6]; } C01Box;
typedef struct { u8 pad[0x10]; void *x10; } C01Task;
typedef struct { u8 b[0x150]; } C01E150;
typedef struct { u8 b[0x220]; } C01E220;

extern u8 D_002BD250[];
extern u8 D_002BBFA0[];
extern C01Mat D_002C58D0;
extern s32 D_002E27E0[];
extern u8 D_002E2800[];
extern C01E150 D_004F7820[];
extern C01E220 D_004F7C10[];
extern s32 D_004F82C0;
extern s32 D_004F82C4;
void func_001274c8(void);

void func_00121620(C01Mat, f32 *, f32, f32, f32, f32);
void sceVu0MulMatrix(C01Mat, C01Mat, C01Mat);
void sceVu0CopyMatrix(C01Mat, C01Mat);
void func_00267e90(f32 *, f32 *, f32);
s32 func_0024edf0(void *, f32 (*)[4]);
void func_00114f18(C01Box *, s32);
void func_002675a8(f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267930(C01Mat, f32 *, f32 *, void *);
C01Task *func_0015ed80(s32, void (*)(void));
void func_00127b98(C01Obj4 *, C01Mat, f32);
void func_00127568(void *, s32, C01Mat, f32 *, s32, f32);

#define C01MAX(a, b) ((a) < (b) ? (b) : (a))

void func_00127c20(C01Obj4 *o, f32 *pos, f32 scale) {
    void *tex = D_002BD250;
    C01Box box;
    C01Mat m;
    C01Mat m2;
    C01Mat m3;
    f32 e[4];
    f32 dir[4];
    f32 pts[8][4];
    C01Mat m4;
    f32 dist;
    f32 t;
    f32 sz;
    f32 h;
    f32 r;
    f32 *sp;
    f32 *row;
    s32 i;
    C01Task *task;

    dist = o->x324 - o->x54;
    if (dist >= 300.0f) return;
    if (dist < 0.0f) dist = 0.0f;
    D_004F82C4 = 60000;
    func_00121620(m, pos, o->xc0, o->xc4, o->xc8, o->xc0 * o->x320 + o->xc4 * o->x324 + o->xc8 * o->x328);
    sceVu0MulMatrix(m, m, o->xd0);
    sp = o->x40;
    row = m[0];
    for (i = 0; i < 3; i++) {
        func_00267e90(row, row, *sp++);
        row += 4;
    }
    h = o->x2c4 * o->x40[1];
    r = o->x410;
/*P*/
    box.v[1] = o->x54 - h;
    box.v[4] = o->x324 + h;
    box.v[0] = o->x50 - r;
    box.v[3] = o->x50 + r;
    box.v[2] = o->x58 - r;
    box.v[5] = o->x58 + r;
/*Q*/
    for (i = 0; i < 8; i++) {
        pts[i][0] = (i & 1) ? box.v[0] : box.v[3];

        pts[i][1] = (i & 2) ? box.v[1] : box.v[4];

        pts[i][2] = (i & 4) ? box.v[2] : box.v[5];

        pts[i][3] = 1.0f;
    }
    if (func_0024edf0(D_002BBFA0, pts)) return;
    func_00114f18(&box, o->x2cc);
    if (!box.n) return;
    func_002675a8(dir, pos);
    func_002673b8(dir, dir);
    sz = C01MAX(C01MAX(o->x40[2], (o->x40[0] > o->x40[1] ? o->x40[0] : o->x40[1])), 1.0f);
    sz *= C01MAX(o->x414, o->x410 * 2.0f);
    t = dist / 300.0f;
    sz /= D_002E27E0[(s32)(o->x370 >> 40) & 3];
    sz *= t * 8.0f + 1.0f;
    func_00267560(dir, dir, sz * 32768.0f);
    func_00267530(e, &o->x50, dir);
    e[1] -= o->x414 * 0.5f;
    func_00267930(m4, e, dir, D_002E2800);
    func_00121620(m, pos, pos[0], pos[1], pos[2], pos[0] * o->x50 + pos[1] * (o->x54 - o->x414 * 0.5f) + pos[2] * o->x58);
    sceVu0CopyMatrix(m3, D_002C58D0);
    m3[3][0] = -o->x50;
    m3[3][1] = o->x414 * 0.5f - o->x54;
    m3[3][2] = -o->x58;
    sceVu0MulMatrix(m, m3, m);
    sceVu0CopyMatrix(m2, m4);
    m2[0][3] = m2[1][3] = m2[2][3] = m2[3][0] = m2[3][1] = m2[3][2] = 0.0f;
    m2[3][3] = 1.0f;
    sceVu0MulMatrix(m, m2, m);
    task = func_0015ed80(D_004F82C4 + D_004F82C0++, func_001274c8);
    task->x10 = &D_004F7820[(s32)(o->x370 >> 40) & 3];
    func_00127b98(o, m4, (s32)((1.0f - t) * 64.0f * scale));
    task = func_0015ed80(D_004F82C4 + D_004F82C0++, func_001274c8);
    task->x10 = &D_004F7C10[(s32)(o->x370 >> 40) & 3];
    func_00127568(tex, box.n, m, pos, o->x2cc, sz * 256.0f);
}
