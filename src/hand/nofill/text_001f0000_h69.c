#include "common.h"

#include "data/types/nofill_text_001f0000_h69.h"
#include "data/pieces/D_003F1A70.h"
#include "data/pieces/D_003F1E70.h"
#include "data/pieces/D_003F2270.h"
#include "data/pieces/D_003F27D0.h"
#include "data/pieces/D_003E9660.h"
#include "data/pieces/D_003F2670.h"
#include "data/pieces/D_003F1660.h"
#include "data/pieces/D_003F2720.h"
extern s32 D_003F1A68;
void func_0011fb78(Q *, s32, Q *);
Q *func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, u32, Q *, Q *);
void func_001f3110(void);

void func_001f2eb8(void) {
    Q *p, *d;
    p = &D_003F1A70;
    d = p;
    p++;
    p->a = 0x1000000000008001;
    p->b = 14;
    p++;
    p->b = 0x47;
    p->a = 0x4000d;
    p++;
    func_0011fb78(d, 7, p);
    func_0011fbb0(0x3d7c, 4, 20, 0, 0, 256, 256, 2048, D_003E9660, D_003F2670);
    func_0011fbb0(0x3dfc, 1, 0, 0, 0, 16, 16, 64, D_003F1660, D_003F2720);
    p = &D_003F1E70;
    d = p;
    p++;
    p->a = 0x1000000000008004;
    p->b = 14;
    p++;
    p->a = 0x4000d;
    p->b = 0x47;
    p++;
    p->b = 0x3f;
    p->a = 0;
    p++;
    p->a = 0x2007bf8621413d7c;
    p->b = 6;
    p++;
    p->a = 0x61;
    p->b = 0x14;
    p++;
    func_0011fb78(d, 7, p);
    p = &D_003F2270;
    d = p;
    p++;
    p->a = 0x1000000000008004;
    p->b = 14;
    p++;
    p->a = 0x4000d;
    p->b = 0x47;
    p++;
    p->b = 0x3f;
    p->a = 0;
    p++;
    p->a = 0x2007ff8622411000;
    p->b = 6;
    p++;
    p->a = 0x61;
    p->b = 0x14;
    p++;
    func_0011fb78(d, 7, p);
    p = D_003F27D0;
    d = p;
    p++;
    p->a = 0x1000000000008001;
    p->b = 14;
    p++;
    p->b = 0x47;
    p->a = 0x5000d;
    p++;
    func_0011fb78(d, 7, p);
    D_003F1A68 = 0;
    func_001f3110();
}
#include "data/data_003E.h"
#include "data/pieces/D_003F1A68.h"
