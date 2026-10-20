/* func_00102a48: MATCH (hand). The two repeated colours are chained assignments (D[9] = D[15] = D[21] = D[27] = ...), written right after D[3]; every other store in index order. */
#include "common.h"
extern s32 *D_002B6778;
extern u64 D_002A49A0[];
extern u8 D_002A4B60[];
extern u8 D_002A4DD0[];
s32 func_0010a470(void);
void func_00106b18(void *);
#define rgba(c, a) ((u64)(c) | ((u64)(c) << 8) | ((u64)(c) << 16) | ((u64)(a) << 24) | 0x100000000)
#define xyz(x, y) ((u64)(x) | ((u64)(y) << 16) | 0x100000000)
void func_00102a48(s32 c, s32 o) {
    s32 i;
    s32 *p;
    func_0010a470();
    p = D_002B6778;
    for (i = 0; i < 0x9000; i++) {
        if (p[i] != 0) goto found;
    }
    func_00106b18(D_002A4DD0);
    return;
found:
    D_002A49A0[3] = rgba(c, 0x80);
    D_002A49A0[9] = D_002A49A0[15] = D_002A49A0[21] = D_002A49A0[27] = rgba(c, 0x40);
    D_002A49A0[33] = D_002A49A0[39] = D_002A49A0[45] = D_002A49A0[51] = rgba(c, 0x20);
    D_002A49A0[11] = xyz(0x6fe0 - o, 0x73e0 - o);
    D_002A49A0[13] = xyz(0x8fe0 - o, 0x8be0 - o);
    D_002A49A0[17] = xyz(0x6fe0 + o, 0x73e0 + o);
    D_002A49A0[19] = xyz(0x8fe0 + o, 0x8be0 + o);
    D_002A49A0[23] = xyz(0x6fe0 - o, 0x73e0 + o);
    D_002A49A0[25] = xyz(0x8fe0 - o, 0x8be0 + o);
    D_002A49A0[29] = xyz(0x6fe0 + o, 0x73e0 - o);
    D_002A49A0[31] = xyz(0x8fe0 + o, 0x8be0 - o);
    D_002A49A0[35] = xyz(0x6fe0, 0x73e0 - o);
    D_002A49A0[37] = xyz(0x8fe0, 0x8be0 - o);
    D_002A49A0[41] = xyz(0x6fe0 - o, 0x73e0);
    D_002A49A0[43] = xyz(0x8fe0 - o, 0x8be0);
    D_002A49A0[47] = xyz(0x6fe0, 0x73e0 + o);
    D_002A49A0[49] = xyz(0x8fe0, 0x8be0 + o);
    D_002A49A0[53] = xyz(0x6fe0 + o, 0x73e0);
    D_002A49A0[55] = xyz(0x8fe0 + o, 0x8be0);
    func_00106b18(D_002A4B60);
}
#include "data/data_002A.h"
