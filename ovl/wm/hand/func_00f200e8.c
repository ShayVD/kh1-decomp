/* wm.x func_00f200e8: matched by hand. */
#include "ovl.h"

typedef struct { s16 a; s16 b; } WmPair;
void func_00176c60(s32);
void func_00f680a0(void);
s32 func_0010a0d8(void);
void func_0010a320(void);
void func_001bfac8(void);
extern s32 D_00F850D0;
extern s32 D_00F850D4;
extern WmPair D_00F8AA88[];
extern s32 D_00FBA800;
void func_00f200e8(s32 arg0) {
    func_00176c60(0);
    func_00f680a0();
    func_0010a0d8();
    func_0010a320();
    D_00F850D4 = D_00F8AA88[arg0].a;
    D_00F850D0 = D_00F8AA88[arg0].b;
    D_00FBA800 = 2;
    while (1) {
        func_001bfac8();
    }
}
