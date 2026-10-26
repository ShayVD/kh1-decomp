/* gb.x func_00f25918: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x11]; u8 idx; } P25918;
typedef struct { u8 pad[0x40]; s32 a; s32 b; u8 pad48[0x4C]; s32 mode; } W25918;
P25918 *func_001bb658(void);
extern s32 D_00379F28[];
extern W25918 *D_00F56DC0;

s32 *func_00f25918(void) {
    W25918 *w = D_00F56DC0; switch (w->mode) { case 0: default: return &D_00379F28[func_001bb658()->idx]; case 1: case 2: return &w->a; }
}
