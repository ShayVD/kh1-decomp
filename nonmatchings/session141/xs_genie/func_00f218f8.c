/* xs_genie.x func_00f218f8: near miss (session 141, as in 131b), 2 words: lui s4 / move s0,sp order before the fetch loop (gcse's hoist of D_00FC1DD0's %hi). Round 3 (wwm2): for(;;)/while/&a[n]/do-while loop forms, p = a before the early return, an address temp and a block around the body all stay at 2 words or worse. */
#include "ovl.h"
typedef struct { s32 v[6]; } G24;
extern s32 D_00FC0E48;
extern u8 D_00FC1DD0[];
s32 func_00f215f8(void *, G24 *);
s32 func_00f218b8(G24 *);
void func_00f21580(void *, G24 *);
s32 func_00f218f8(void) {
    G24 a[10];
    G24 b[10];
    G24 *p;
    s32 n = 0;
    s32 m = 0;
    s32 i;
    if (D_00FC0E48 == 101)
        return 4;
    p = a;
loop:
    if (func_00f215f8(D_00FC1DD0, p++)) {
        n++;
        goto loop;
    }
    for (i = 0; i < n; i++) {
        if (func_00f218b8(&a[i])) {
            b[m] = a[i];
            m++;
        }
    }
    for (i = 0; i < m; i++)
        func_00f21580(D_00FC1DD0, &b[i]);
    return 0;
}
