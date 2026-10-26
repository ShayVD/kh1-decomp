/* wm.x func_00f49cf0: the twin of gb.x func_00f22bf8 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u8 pad[140]; s32 x140; } G;
extern s32 D_00F9B648, D_002C1370, D_00F9B514, D_00F9B500, D_00F9B504, D_00F9B524;
extern u8 D_00F9B548[], D_00F9B600[], D_00F9B580[];
extern G *D_00F9B540;
void func_001ba520(void);
void func_00f66ef0(void);
void func_001bfcd8(void);
void (*func_001ba920(void))(void);
void func_001ba708(s32);
void func_00f4e318(void);
void func_00f491e0(void *);
void func_001bb858(void *, void *);
void func_001bfac8(void);
s32 func_00f49cf0(void) {
    D_00F9B648 = 0;
    D_002C1370 = 1;
    func_001ba520();
    if (D_00F9B514) {
        if (D_00F9B500 == 0) {
            if (D_00F9B504 == 0) {
                func_00f66ef0();
                func_001bfcd8();
            }
            if (D_00F9B504 == 2) {
                func_001ba920()();
                func_001ba708(0);
                return 4;
            }
            D_00F9B504++;
        } else {
            func_00f4e318();
            func_00f491e0(D_00F9B548);
            func_001bb858(D_00F9B600, D_00F9B580);
            D_00F9B540->x140 ^= 1;
        }
    }
    D_00F9B524++;
    func_001bfac8();
    return 0;
}
