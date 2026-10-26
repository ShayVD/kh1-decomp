/* gb.x func_00f20100: matched by hand. */
#include "ovl.h"

typedef struct { s32 a, b, c, d; } S16;
void func_00f40fa8(void);
void func_001efaf0(void);
s32 func_001bb4f0(void);
void func_00113028(s32);
S16 *func_001ba980(void);
extern S16 *D_00F56DC0;
void func_00f20100(void) {
    S16 *p;
    s32 t;
    func_00f40fa8();
    func_001efaf0();
    func_00113028(func_001bb4f0());
    p = func_001ba980();
    t = p->c;
    *p = *D_00F56DC0;
    p->c = t;
}
