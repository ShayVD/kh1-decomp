#include "common.h"
extern u8 *D_006431F0[3];
extern s32 D_00643200[3];
extern s32 D_00643278[3];
extern u8 D_00643128[];
extern u8 D_00643160[];
extern u8 D_006431B0[];
extern u8 D_00643210[];
extern s32 D_003F50E0[];
extern s32 D_003F5C38;
s32 func_0021dc08(s32);
char *func_0021dc20(s32);
s32 func_001eb038(s32);
s32 func_00131c30(s32);
s32 func_00207180(s32);
void func_00207000(s32);
void func_00207048(s32);
s32 func_00207088(s32);
void func_002072e0(s32);
void func_00207298(s32);
s32 strcmp(const char *, const char *);

void func_0021dc40(void) {
    s32 i, j;
    s32 *c;
    char *p, *s;
    c = D_00643200;
    D_006431F0[0] = D_00643128;
    c[0] = 0;
    for (i = 0; i < 49; i++) {
        if (func_001eb038(func_0021dc08(i))) { s32 n = D_00643200[0]; D_00643200[0] = n + 1; D_00643128[n] = i; }
    }
        D_006431F0[1] = D_00643160;
    D_00643200[1] = 0;
    c = D_00643200;
    for (; i < 127; i++) {
        if (func_001eb038(func_0021dc08(i))) { s32 n = c[1]; c[1] = n + 1; D_00643160[n] = i; }
    }
    D_006431F0[2] = D_006431B0;
    D_00643200[2] = 0;
    for (; i < 184; i++) {
        if (func_001eb038(func_0021dc08(i)) || func_00131c30(D_003F50E0[i])) D_00643210[D_00643200[2]] = 1;
        else D_00643210[D_00643200[2]] = 0;
        D_006431B0[D_00643200[2]] = i;
        D_00643200[2]++;
    }
    for (j = D_00643200[0] - 1; j >= 0; j--) {
        if (!func_00207180(func_0021dc08(D_00643128[j]))) {
            func_00207000(0);
            goto l1;
        }
    }
    func_00207048(0);
l1:
    for (j = D_00643200[1] - 1; j >= 0; j--) {
        if (!func_00207180(func_0021dc08(D_00643160[j]))) {
            func_00207000(1);
            goto l2;
        }
    }
    func_00207048(1);
l2:
    for (j = D_00643200[2] - 1; j >= 0; j--) {
        if (!func_00207180(func_0021dc08(D_006431B0[j])) && D_00643210[j]) {
            func_00207000(2);
            goto l3;
        }
    }
    func_00207048(2);
l3:
    if (func_00207088(0) && func_00207088(1) && func_00207088(2)) {
        func_002072e0(2);
    } else {
        func_00207298(2);
    }
    s = func_0021dc20(0);
    for (i = 1; i < 49; i++) {
        p = s;
        s = func_0021dc20(i);
        if (i != 38 && strcmp(p, s) && !func_001eb038(func_0021dc08(i - 1))) goto z0;
    }
    if (!func_001eb038(func_0021dc08(48))) { z0: D_00643278[0] = 0; }
    else D_00643278[0] = 1;
    s = func_0021dc20(49);
    for (i = 50; i < 127; i++) {
        p = s;
        s = func_0021dc20(i);
        if (strcmp(p, s) && !func_001eb038(func_0021dc08(i - 1))) goto z1;
    }
    if (!func_001eb038(func_0021dc08(126))) { z1: D_00643278[1] = 0; }
    else D_00643278[1] = 1;
    for (i = 127; i < 184; i++) {
        if (!func_001eb038(func_0021dc08(i)) && !func_00131c30(D_003F50E0[i])) { D_00643278[2] = 0; goto e2; }
    }
    D_00643278[2] = 1;
e2:
    if (D_00643278[0] && D_00643278[1] && D_00643278[2]) D_003F5C38 = 1;
    else D_003F5C38 = 0;
}
