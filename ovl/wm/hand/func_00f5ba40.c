/* wm.x func_00f5ba40: matched by hand. */
#include "ovl.h"

typedef struct { u16 a; u16 b; u16 c; u8 pad[6]; } E5ba;
typedef struct { u8 pad[0xA4]; u16 n; u8 pad2[0x6A]; E5ba e[1]; } W5ba;
extern W5ba *D_00F9B540;
void func_001c0310();
void func_00f5b590(void);
void func_00f5b718(void);
void func_00f5b8c8(void);

s32 func_00f5ba40(s32 mode)
{
    OvlMtx unused;
    s32 i;
    s32 r = 0;

    for (i = 0; i < D_00F9B540->n; i++) {
        switch (D_00F9B540->e[i].c - 1) {
        case 58:
            if (mode == 0) {
                func_001c0310(-1, func_00f5b590, i);
                r = 1;
            }
            break;
        case 59:
            if (mode == 1) {
                func_001c0310(-1, func_00f5b718, i, 0);
                func_001c0310(-1, func_00f5b718, i, 1);
                r = 1;
            }
            break;
        case 60:
            if (mode == 2) {
                func_001c0310(-1, func_00f5b8c8, i);
                r = 1;
            }
            break;
        }
    }
    return r;
}
