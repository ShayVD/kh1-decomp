/* wm.x func_00f203c8: matched by hand. */
#include "ovl.h"

typedef struct { void *a; void *b; void *c; void *d; void *e; s32 pad; } B203c8;
extern void *D_00FBA940;
extern u8 *D_00F85160;
extern B203c8 D_00FBA808[2];
void *func_001bb500(s32, s32);
void func_001be820(void *, s32);

void func_00f203c8(void) {
    s32 i;
    void **p = &D_00FBA940;
    u8 **q;
    *p = func_001bb500(0x9A60, 16);
    q = &D_00F85160;
    func_001be820(*q = func_001bb500(3980, 128), 3980);
    *(s32 *)(*q + 3976) = 0;
    for (i = 0; i < 2; i++) {
        D_00FBA808[i].a = func_001bb500(0x40000, 128);
        func_001be820(D_00FBA808[i].b = func_001bb500(0x80000, 128), 0x80000);
        func_001be820(D_00FBA808[i].c = func_001bb500(0x10000, 128), 0x10000);
        func_001be820(D_00FBA808[i].d = func_001bb500(0x8000, 128), 0x8000);
        func_001be820(D_00FBA808[i].e = func_001bb500(0x40000, 128), 0x40000);
    }
}
