/* gb.x func_00f22bf8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[140]; s32 x140; } G;
extern s32 D_00F56EC8, D_002C1370, D_00F56D94, D_00F56D80, D_00F56D84, D_00F56DA4;
extern u8 D_00F56DC8[], D_00F56E80[], D_00F56E00[];
extern G *D_00F56DC0;
void func_001ba520(void);
void func_00f3fdf8(void);
void func_001bfcd8(void);
void (*func_001ba920(void))(void);
void func_001ba708(s32);
void func_00f27220(void);
void func_00f220e8(void *);
void func_001bb858(void *, void *);
void func_001bfac8(void);
s32 func_00f22bf8(void) {
    D_00F56EC8 = 0;
    D_002C1370 = 1;
    func_001ba520();
    if (D_00F56D94) {
        if (D_00F56D80 == 0) {
            if (D_00F56D84 == 0) {
                func_00f3fdf8();
                func_001bfcd8();
            }
            if (D_00F56D84 == 2) {
                func_001ba920()();
                func_001ba708(0);
                return 4;
            }
            D_00F56D84++;
        } else {
            func_00f27220();
            func_00f220e8(D_00F56DC8);
            func_001bb858(D_00F56E80, D_00F56E00);
            D_00F56DC0->x140 ^= 1;
        }
    }
    D_00F56DA4++;
    func_001bfac8();
    return 0;
}
