/* The movie files (docs/modules.md "Session 47"), 0x0024b9a8-0x0024ba28:
 * func_0024b9a8 names one (D_0046A058: opn.dat, end.dat, end2.dat,
 * demo.dat, end3.dat, ffx2.dat; the opening, the endings, the demo and,
 * most likely, the Final Fantasy X-2 trailer), D_00669A38 the one chosen
 * and D_00669A3C a time taken with it (func_0024ba00, func_0026aaa0).  Its
 * own file by the data order (D_0046A058 after sa_task.c's tables); the
 * meanings are read from the strings, not proved by a boot. */
#include "common.h"
#include "data/bss_0066.h"
#include "data/data_0049.h"

extern char *D_0046A058[];
s32 func_0026aaa0(void);

char *func_0024b9a8(s32 i) {
    return D_0046A058[i];
}

s32 func_0024b9c0(void) {
    return D_00669A38;
}

s32 func_0024b9d0(void) {
    return D_00669A3C;
}

void func_0024b9e0(s32 arg0) {
    D_00669A38 = arg0;
}

void func_0024b9f0(s32 arg0) {
    D_00669A3C = arg0;
}

void func_0024ba00(s32 arg0) {
    D_00669A38 = arg0;
    D_00669A3C = func_0026aaa0();
}

/* The names (phase 4, tools/shift/define_ptr_tables.py). */
char *D_0046A058[0x6] ALIGNED(8) = {
    (char *)D_00491900, (char *)D_004918F8, (char *)D_004918E8, (char *)D_004918D8,
    (char *)D_004918C8, (char *)D_004918B8,
};
