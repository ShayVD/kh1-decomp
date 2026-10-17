#include "common.h"

u32 func_001ee118(void);

void func_001ee230(u32 *a, u32 *b, u32 *c, u32 *d) {
    u32 t = func_001ee118();
    *a = t / 216000U;
    t = t % 216000U;
    *b = t / 3600U;
    t = t % 3600U;
    *c = t / 60U;
    *d = t % 60U;
}

typedef struct { u8 pad[0x48e]; u8 a[16]; } S4BE8;
extern S4BE8 *D_00304BE8;
extern s32 D_003E3D68;
extern u16 D_003E3CD0[];
s32 func_00149440(s32, s32);
s32 func_001ee7c8(void);
void func_001efc10(s32);

void func_001ee650(s32 a) {
    if (a > 16) a = 0;
    func_001efc10(D_003E3CD0[a]);
}

s32 func_001ee7f0(s32 a) {
    s32 n = D_003E3D68;
    s32 i = 0;
    do {
        if (func_00149440(a, D_00304BE8->a[i++])) return 1;
    } while (--n);
    return 0;
}

s32 func_001ee870(s32 a, s32 i) {
    s32 n;
    if (func_001ee7c8()) {
        i = 0;
        n = D_003E3D68;
    } else {
        n = 1;
    }
    do {
        if (func_00149440(a, D_00304BE8->a[i++])) return 1;
    } while (--n);
    return 0;
}

s32 func_001ee900(s32 a) {
    s32 v = func_00149440(a, 0);
    s32 i;
    for (i = 1; i < 7; i++) {
        if ((v >> i) & 1) return i;
    }
    return -1;
}

s32 func_001ee958(s32 a, s32 b) {
    s32 v = func_00149440(a, b);
    s32 i;
    if (v & 1) {
        for (i = 1; i < 7; i++) {
            if ((v >> i) & 1) return i;
        }
    }
    return -1;
}

s32 func_001ee768(void);
extern s32 D_003E3D20[];

s32 func_001eea00(s32 a, s32 b) {
    s32 v;
    if (a) {
        v = func_001ee768();
        if ((u32)(v - 2) < 10) {
            if (v != D_003E3D20[b]) return 0;
        }
    }
    return 1;
}

u8 *func_00147840(void);
extern s32 D_003E3D48[];

s32 func_001eea60(s32 a) {
    u32 i;
    if (a) {
        u8 k = func_00147840()[2];
        for (i = 0; i < 3; i++) {
            if (k == D_003E3D48[i]) return 1;
        }
    }
    return 0;
}
