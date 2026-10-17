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
