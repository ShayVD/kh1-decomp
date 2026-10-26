/* xl_limit.x func_00f213d8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xC]; void *fC; } Res;
Res *func_00f21240(u32 *, void *);
extern u32 *D_002E26A0;
void func_00f21208(void);

void func_00f213d8(void) {
    f32 v[4];
    u32 *p = D_002E26A0;
    func_00f21240(p, v)->fC = func_00f21208;
    *p &= 0xFEFFFF7F;
}
