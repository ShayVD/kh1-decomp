/* wm.x func_00f51bc0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u16 n; u8 pad2[2]; u8 c; } E51;
typedef struct { u8 pad[4]; s32 btn; } P51;
E51 *func_00f4b2e0(s32);
s32 func_00f4cad0(s32);
void func_00f4b878(s32);
void func_0011d768(s32);
P51 *func_001ba488(s32);
void func_001bfac8(void);
void func_00f51860(void);
extern u8 *D_00F9B540;
extern s32 D_00F9B544;

void func_00f51bc0(void) {
    s32 done = 0;
    E51 *e;
    P51 *p;

    if (*(u16 *)(D_00F9B540 + 0x74) & 2) {
        e = func_00f4b2e0(*(u16 *)(D_00F9B540 + 0x60));
        if (e != NULL) {
            if (func_00f4cad0(e->n - 1) != 0) {
                e->c = D_00F9B540[0x7E];
                func_00f4b878(D_00F9B544);
                func_0011d768(2);
            } else {
                func_0011d768(4);
            }
            done = 1;
        }
    }
    if (done == 0) {
        func_0011d768(4);
    }
    if (func_001ba488(0)->btn & 0x1000) {
        do {
            p = func_001ba488(0);
            if (p->btn & 0xF0) {
                func_00f51860();
                return;
            }
            func_001bfac8();
        } while (p->btn & 0x1000);
    }
}
