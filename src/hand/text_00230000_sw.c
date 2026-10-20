#include "common.h"
#include "data/bss_0064.h"
typedef struct { s32 type; s32 id; s32 a[6]; } Cmd;
extern Cmd D_006477B0[64];
extern s32 D_00647FB0;
extern s32 D_00647FB8;
extern s32 D_00647FBC;
extern s32 D_00647FC4;
void func_002365e0(void);
/* func_00265b28 is left undeclared on purpose (implicit declaration gives the original code). */

void func_00233db0(s32 id) {
    s32 i, x;
    if (id != 0) {
    restart:
        i = D_00647FBC;
        while (i != D_00647FB8) {
            x = D_006477B0[i].id;
            i++;
            i &= 63;
            if (x == id) {
                func_002365e0();
                func_00265b28(0);
                goto restart;
            }
        }
        if (D_00647FB0 != 0 && D_00647FC4 == id) {
            do {
                func_002365e0();
                func_00265b28(0);
            } while (D_00647FB0 != 0);
        }
    } else {
        while (D_00647FB8 != D_00647FBC || D_00647FB0 != 0) {
            func_002365e0();
            func_00265b28(0);
        }
    }
}
