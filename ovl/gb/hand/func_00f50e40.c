/* gb.x func_00f50e40: the twin of wm.x func_00f77f38 (tools/ovl/twins.py). */
#include "ovl.h"

void func_00f43350(void);
void func_00f41c98(s32, s32, s32, s32, s32);
void func_001f8f30(void);
s32 func_001f4390(s32);
void func_0011d768(s32);
void func_001f3840(s32);
extern s32 D_002C5AD8;
extern s32 D_00F829EC;
extern s32 D_00F829F0;

void func_00f50e40(s32 arg0) {
    func_00f43350();
    func_00f41c98(arg0, D_00F829F0, 3, 1, 1);
    func_001f8f30();
    if (func_001f4390(arg0) != 0) {
        if (D_002C5AD8 & 0x4000) {
            func_0011d768(3);
            D_00F829EC = 1;
            func_001f3840(arg0);
        } else if (D_002C5AD8 & 0x2000) {
            func_0011d768(2);
            D_00F829EC = 1;
            func_001f3840(arg0);
        }
    }
}
