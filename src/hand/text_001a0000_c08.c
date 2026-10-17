#include "common.h"

typedef struct { u8 id; u8 pad[3]; u32 n; } IdCnt;
extern s32 D_00625748;
extern IdCnt D_00625750[];
void func_001b9e40(s32, s32);

void func_001bdb58(void) {
    u32 a[16];
    s32 b[16];
    s32 i, j;

    for (i = 0; i < 16; i++) {
        a[i] = 0;
        b[i] = 0;
    }
    for (i = 0; i < D_00625748; i++) {
        a[D_00625750[i].id] = D_00625750[i].n;
        switch (D_00625750[i].n) {
        case 0x400: b[10] = 1; break;
        case 0x1000: b[12] = 1; break;
        case 0x2000: b[13] = 1; break;
        case 0x4000: b[14] = 1; break;
        case 0x8000: b[15] = 1; break;
        }
    }
    a[4] = a[3];
    a[7] = a[6];
    a[5] = a[3];
    a[8] = a[6];
    j = 0;
    if (a[j] == 0) {
        if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    j = 1;
    if (a[j] == 0) {
        if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    j = 2;
    if (a[j] == 0) {
        if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    j = 3;
    if (a[j] == 0) {
        if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    a[j+1] = a[j]; a[j+2] = a[j];
    j = 6;
    if (a[j] == 0) {
        if (!b[13]) { a[j] = 0x2000; b[13] = 1; }
        else if (!b[15]) { a[j] = 0x8000; b[15] = 1; }
        else if (!b[14]) { a[j] = 0x4000; b[14] = 1; }
        else if (!b[12]) { a[j] = 0x1000; b[12] = 1; }
        else if (!b[10]) { a[j] = 0x400; b[10] = 1; }
    }
    a[j+1] = a[j]; a[j+2] = a[j];
    func_001b9e40(0, a[0]);
    func_001b9e40(1, a[1]);
    func_001b9e40(2, a[2]);
    func_001b9e40(3, a[3]);
    func_001b9e40(4, a[4]);
    func_001b9e40(5, a[5]);
    func_001b9e40(6, a[6]);
    func_001b9e40(7, a[7]);
    func_001b9e40(8, a[8]);
}


typedef struct { s8 x, y, z, w; } C4;
extern C4 D_0037A130[16];
typedef struct { u16 h0; u16 r0 : 4; u16 r1 : 4; u16 r2 : 4; u16 r3 : 4; } Ori_1bbf88;

void func_001bbf88(Ori_1bbf88 *o, s32 axis, s32 dir) {
    C4 a, b, c, t;
    s32 i;

    a = D_0037A130[o->r0];
    b = D_0037A130[o->r1];
    c = D_0037A130[o->r2];
    switch (axis) {
    case 0:
        switch (dir) {
        case -1:
            t.x = a.x; t.y = -a.z; t.z = a.y; a = t;
            t.x = b.x; t.y = -b.z; t.z = b.y; b = t;
            t.x = c.x; t.y = -c.z; t.z = c.y; c = t;
            break;
        case 1:
            t.x = a.x; t.y = a.z; t.z = -a.y; a = t;
            t.x = b.x; t.y = b.z; t.z = -b.y; b = t;
            t.x = c.x; t.y = c.z; t.z = -c.y; c = t;
            break;
        }
        break;
    case 1:
        switch (dir) {
        case 1:
            t.x = -a.z; t.y = a.y; t.z = a.x; a = t;
            t.x = -b.z; t.y = b.y; t.z = b.x; b = t;
            t.x = -c.z; t.y = c.y; t.z = c.x; c = t;
            break;
        case -1:
            t.x = a.z; t.y = a.y; t.z = -a.x; a = t;
            t.x = b.z; t.y = b.y; t.z = -b.x; b = t;
            t.x = c.z; t.y = c.y; t.z = -c.x; c = t;
            break;
        }
        break;
    case 2:
        switch (dir) {
        case -1:
            t.x = -a.y; t.y = a.x; t.z = a.z; a = t;
            t.x = -b.y; t.y = b.x; t.z = b.z; b = t;
            t.x = -c.y; t.y = c.x; t.z = c.z; c = t;
            break;
        case 1:
            t.x = a.y; t.y = -a.x; t.z = a.z; a = t;
            t.x = b.y; t.y = -b.x; t.z = b.z; b = t;
            t.x = c.y; t.y = -c.x; t.z = c.z; c = t;
            break;
        }
        break;
    }
    for (i = 0; i < 6; i++) {
        if (D_0037A130[i].x == a.x && D_0037A130[i].y == a.y && D_0037A130[i].z == a.z) {
            o->r0 = i;
            break;
        }
    }
    for (i = 0; i < 6; i++) {
        if (D_0037A130[i].x == b.x && D_0037A130[i].y == b.y && D_0037A130[i].z == b.z) {
            o->r1 = i;
            break;
        }
    }
    for (i = 0; i < 6; i++) {
        if (D_0037A130[i].x == c.x && D_0037A130[i].y == c.y && D_0037A130[i].z == c.z) {
            o->r2 = i;
            break;
        }
    }
}
