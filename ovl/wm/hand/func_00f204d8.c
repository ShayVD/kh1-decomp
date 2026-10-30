/* wm.x func_00f204d8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[1348]; s32 a; s32 b; u8 pad2[2772 - 1356]; s32 c; s32 d; } T204d8;
s32 func_001bb500(s32, s32);
extern T204d8 D_00F86500;
extern s32 D_00F87030;
extern s32 D_00F87028;
extern s32 D_00F87038;
extern s32 D_00F87034;
extern s32 D_00F8702C;
extern s32 D_00F87060;
extern s32 D_00F87064;
extern s32 D_00F87044;
extern s32 D_00F8703C;
extern s32 D_00F87040;
extern s32 D_00FBA838;
extern s32 D_00FBA83C;
extern s32 D_00F87058;
extern s32 D_00F8705C;
extern s32 D_00F87048;
extern s32 D_00F87050;

static inline void alloc204d8(s32 *p, s32 size, s32 align) {
    *p = func_001bb500(size, align);
}

void func_00f204d8(void) {
    alloc204d8(&D_00F87030, 0x90000, 128);
    D_00F86500.a = func_001bb500(0x32000, 128);
    D_00F86500.c = func_001bb500(0x32000, 128);
    D_00F86500.b = func_001bb500(0x14000, 128);
    D_00F86500.d = func_001bb500(0x14000, 128);
    alloc204d8(&D_00F87028, 0x40000, 128);
    alloc204d8(&D_00F87038, 0x40000, 128);
    alloc204d8(&D_00F87034, 0x8000, 128);
    alloc204d8(&D_00F8702C, 0x40000, 128);
    D_00F87060 = func_001bb500(0x8000, 128);
    D_00F87064 = func_001bb500(0x8000, 128);
    alloc204d8(&D_00F87044, 0x80000, 128);
    alloc204d8(&D_00F8703C, 0x34000, 128);
    alloc204d8(&D_00F87040, 8192, 128);
    alloc204d8(&D_00FBA838, 0x100000, 128);
    alloc204d8(&D_00FBA83C, 0x80000, 128);
    alloc204d8(&D_00F87058, 0x87000, 128);
    D_00F8705C = func_001bb500(8192, 128);
    alloc204d8(&D_00F87048, 0xCD000, 128);
    D_00F87050 = func_001bb500(0x200000, 256);
}
