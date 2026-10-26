/* gb.x func_00f29870: matched by hand. */
#include "ovl.h"

typedef struct { s32 x0, x4; } Pad;
typedef struct { u16 h0; u16 h2; u16 h4; u16 h6; u16 h8; u16 h10; } T12;
typedef struct { u8 pad[72]; T12 t; u8 pad84[12]; u16 h96; u8 pad98[18]; u16 h116; } G;
extern G *D_00F56DC0;
extern s32 D_00F56DC4;
Pad *func_001ba488(s32);
s32 func_00f299c8(void);
void func_001bfac8(void);
void func_00f29f10(void);
s32 func_00f291f0(void);
void func_00f291c0(s32);
void func_0011d768(s32);
void func_00f24680(T12 *);
void func_00f23e30(s32);
void func_00f24780(s32);
void func_00f24240(s32, s32);
void func_00f29870(void) {
    Pad *p;
    s32 r, v;
    T12 t;
    if (func_001ba488(0)->x4 & 0x2000) {
        do {
            p = func_001ba488(0);
            if (p->x4 & 0xF0) r = func_00f299c8();
            else if (D_00F56DC0->h116 & 2) {
                func_00f29f10();
                return;
            }
            func_001bfac8();
        } while (p->x4 & 0x2000);
    }
    if (r == 0) return;
    if ((u16)(D_00F56DC0->h116 & 1)) return;
    v = func_00f291f0();
    if (v == 0) {
        func_0011d768(2);
        t = D_00F56DC0->t;
        t.h0 = D_00F56DC0->h96;
        func_00f24680(&t);
        func_00f23e30(t.h4 - 1);
        func_00f24780(D_00F56DC4);
        func_00f24240(D_00F56DC4, 0);
    } else {
        func_00f291c0(v);
    }
}
