#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0064.h"
#include "data/types/text_00200000_h70.h"
extern f32 D_002BBDFC;

typedef W606Mem_304be8 T74;
typedef Save_304be8 G4BE8;
typedef struct { u8 pad[0x24]; f32 x24; u8 pad28[0x68]; s32 x90; } Pa758;
extern f32 D_002BBDFC;
extern s32 D_00641224, D_00641228, D_00641230, D_00641234;

extern s32 D_00641228, D_00641234;

typedef struct { u8 pad[0x24]; f32 x24; } P1840;
extern s32 D_003F34C0, D_003F34C8, D_00641BA8, D_00641C00, D_00641C04, D_00641C08;
extern s32 D_00641BE0[];
void func_0020a728(s32, P1840 *);
void func_0020a6c0(s32, P1840 *);
void func_00211718(void);
void func_00149f10(s32, void (*)(void));
void func_00211840(P1840 *o) {
    s32 s;
    if (D_003F34C0 & 1) return;
    if (!D_00641C00) return;
    s = D_00641C08;
    switch (s) {
    case 0:
        o->x24 += D_002BBDFC;
        func_0020a758((Pa758 *)o, D_00641BA8, 10, 50);
        return;
    case 1:
        func_0020a728(D_00641BA8, o);
        D_003F34C8++;
        D_00641C04 = s;
        D_00641C08 = 2;
        func_00149f10(D_00641BE0[D_00641BA8], func_00211718);
        return;
    case 2:
        if (!D_00641C04) D_00641C08 = 3;
        break;
    case 3:
        func_0020a6c0(D_00641BA8, o);
        D_00641C08 = 0;
        break;
    }
}

extern s32 D_00642418[], D_00642818[], D_00642C18;
s32 func_001ef370(s32);
s32 func_001ef0c0(s32);
void func_0020f290(s32 *, s32, s32);

void func_002127e0(void) {
    s32 i, v;
    D_00642818[0] = 0;
    D_00642C18 = 1;
    D_00642418[0] = 0;
    for (i = 1; i < 256; i++) {
        if (D_00304BE8->items[i] && func_001ef370(i) && func_001ef0c0(i) > 0) {
            s32 n = D_00642C18;
            D_00642C18 = n + 1;
            D_00642418[n] = i;
        }
    }
    if (D_00642C18 < 2) return;
    func_0020f290(&D_00642418[1], 0, D_00642C18 - 2);
    for (i = 1; i < D_00642C18; i++) {
        v = func_001ef0c0(D_00642418[i]);
        if (v > 0) D_00642818[i] = v;
    }
}

typedef u32 (*KF3de0)(s32);
extern KF3de0 D_003F3DE0[];
void func_00213e50(u8 *a, s32 lo, s32 hi, s32 k) {
    s32 i, j;
    u32 p;
    u8 t;
    i = lo;
    j = hi;
    p = D_003F3DE0[k](a[(lo + hi) / 2]);
    for (;;) {
        while (D_003F3DE0[k](a[i]) < p) i++;
        while (p < D_003F3DE0[k](a[j])) j--;
        if (i >= j) break;
        t = a[i]; a[i++] = a[j]; a[j--] = t;
    }
    if (lo < i - 1) func_00213e50(a, lo, i - 1, k);
    if (j + 1 < hi) func_00213e50(a, j + 1, hi, k);
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
void func_00213d80();
void func_00213db8();
void func_00213e18();
KF3de0 D_003F3DE0[0x4] ALIGNED(16) = {
    (void *)func_00213d80, (void *)func_00213db8, (void *)func_00213e18, 0,
};
#include "data/data_003F.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_003F34C8.h"
