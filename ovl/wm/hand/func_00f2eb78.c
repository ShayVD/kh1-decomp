/* wm.x func_00f2eb78: matched by hand. */
#include "ovl.h"

typedef struct { u8 p[6]; u16 f; u16 h; u16 pad; } N2eb78;
typedef struct { s32 n; u8 pad[0x2C]; N2eb78 ent[1]; } D2eb78;
typedef struct { s32 a; u8 pad[28]; } B2eb78;
extern D2eb78 D_00F85240;
extern B2eb78 D_00FBB5D0[];
CONTEXT_ONLY s32 func_00f2cd88(s32 a0, s32 a1, s32 a2) { return 0; }
CONTEXT_ONLY s32 func_00f2cfd8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, void *a6, void *a7, void *a8, s32 a9) { return 0; }
void func_00f2e960(s32 *);
void func_001c0310(s32, void *, s32);
void func_00f2dad0();
void func_00f2dc50();
void func_00f2dfc0();
void func_00f2e0b8();
void func_00f2e390();
void func_00f2e510();

void func_00f2eb78(s32 mask) {
    s32 buf[16];
    s32 i;
    s32 j;
    s32 t;
    s32 r;
    s32 k;

    func_00f2e960(buf);
    j = 0;
    for (i = 0; i < D_00F85240.n; i++) {
        switch (D_00F85240.ent[i].h - 1) {
        case 61:
            if (mask & 1) {
                t = 71;
                r = func_00f2cd88(i, 61, 71);
                if (buf[j] >= 0) {
                    D_00FBB5D0[buf[j]].a = 3;
                }
                k = func_00f2cfd8(r, i, 61, 71, 0, 71, 0, 0, func_00f2dad0, buf[j]);
                if (k >= 0) {
                    func_001c0310(9, func_00f2dc50, k);
                }
            }
            break;
        case 62:
            if (mask & 2) {
                t = 72;
                r = func_00f2cd88(i, 62, 72);
                if (buf[j] >= 0) {
                    D_00FBB5D0[buf[j]].a = 3;
                }
                k = func_00f2cfd8(r, i, 62, 72, 0, 72, 0, 0, func_00f2dfc0, buf[j]);
                if (k >= 0) {
                    func_001c0310(9, func_00f2e0b8, k);
                }
            }
            break;
        case 63:
            if (mask & 4) {
                t = 73;
                r = func_00f2cd88(i, 63, 73);
                if (buf[j] >= 0) {
                    D_00FBB5D0[buf[j]].a = 3;
                }
                k = func_00f2cfd8(r, i, 63, 73, 0, 73, 0, 0, func_00f2e390, buf[j]);
                if (k >= 0) {
                    func_001c0310(9, func_00f2e510, k);
                }
            }
            break;
        default:
            t = -1;
            break;
        }
        if (t >= 0) {
            j++;
        }
    }
}
