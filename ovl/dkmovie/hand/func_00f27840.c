/* dkmovie.x func_00f27840: matched by hand. */
#include "ovl.h"

typedef struct {
    void (*f0)(void);
    void (*f4)(void);
} Vt;
void func_00f220b8(s32);
extern Vt *D_00F28468;
extern s32 D_00F2846C;
extern s32 D_00F28470;
extern s32 D_00F28474;

s32 func_00f27840(void) {
    if (D_00F28474 != 0) {
        Vt *v;
        func_00f220b8(D_00F2846C);
        D_00F2846C = 0;
        D_00F28470 = 0;
        v = D_00F28468;
        D_00F28474 = 0;
        v->f4();
        D_00F28468 = 0;
    }
    return 0;
}
