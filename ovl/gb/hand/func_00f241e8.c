/* gb.x func_00f241e8: matched by hand. */
#include "ovl.h"

typedef struct { u16 id; u8 pad[10]; } E241e8;
typedef struct { u8 pad[0xA4]; u16 n; u8 padA6[0x6A]; E241e8 e[1]; } W241e8;
extern W241e8 *D_00F56DC0;

E241e8 *func_00f241e8(s32 id) {
    s32 i;
    E241e8 *e = D_00F56DC0->e;
    for (i = 0; i < D_00F56DC0->n; i++, e++) {
        if (e->id == (u16)id) {
            return e;
        }
    }
    return 0;
}
