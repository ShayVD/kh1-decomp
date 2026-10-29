/* dktitle.x func_00f21ca0: near-miss draft (session 132), not byte-identical; the port runs it (ovl/dktitle/drafts.tsv). */
#include "ovl.h"

typedef struct { f32 v; s32 st; s32 t; } Fade;
extern s32 D_002B6478, D_00F2C700;
extern Fade D_00F2C838, D_00F2C7A8, D_00F2C7B8, D_00F2C7D8, D_00F2C7E8, D_00F2C808, D_00F2C818, D_00F2C860, D_00F2C870;
void func_00f21ca0(void) {
    D_00F2C838.v = 128.0f;
    if (D_002B6478 == 0) {
        switch (D_00F2C700) {
        case 0:
            D_00F2C7B8.v += 1.5625f;
            D_00F2C7E8.v += -1.5625f;
            D_00F2C870.v += -1.5625f;
            D_00F2C7A8.v += 6.375f;
            D_00F2C7D8.v = 0;
            D_00F2C860.v = 0;
            break;
        case 1:
            D_00F2C7B8.v += -1.5625f;
            D_00F2C7E8.v += 1.5625f;
            D_00F2C870.v += -1.5625f;
            D_00F2C7A8.v = 0;
            D_00F2C7D8.v += 6.375f;
            D_00F2C860.v = 0;
            break;
        case 2:
            D_00F2C7B8.v += -1.5625f;
            D_00F2C7E8.v += -1.5625f;
            D_00F2C870.v += 1.5625f;
            D_00F2C7A8.v = 0;
            D_00F2C7D8.v = 0;
            D_00F2C860.v += 6.375f;
            break;
        }
    } else {
        switch (D_00F2C700) {
        case 0:
            D_00F2C7B8.v += 1.5625f;
            D_00F2C7E8.v += -1.5625f;
            D_00F2C870.v += -1.5625f;
            D_00F2C818.v += -1.5625f;
            D_00F2C7A8.v += 6.375f;
            D_00F2C7D8.v = 0;
            D_00F2C860.v = 0;
            D_00F2C808.v = 0;
            break;
        case 1:
            D_00F2C7B8.v += -1.5625f;
            D_00F2C7E8.v += 1.5625f;
            D_00F2C870.v += -1.5625f;
            D_00F2C818.v += -1.5625f;
            D_00F2C7A8.v = 0;
            D_00F2C7D8.v += 6.375f;
            D_00F2C860.v = 0;
            D_00F2C808.v = 0;
            break;
        case 2:
            D_00F2C7B8.v += -1.5625f;
            D_00F2C7E8.v += -1.5625f;
            D_00F2C870.v += 1.5625f;
            D_00F2C818.v += -1.5625f;
            D_00F2C7A8.v = 0;
            D_00F2C7D8.v = 0;
            D_00F2C860.v += 6.375f;
            D_00F2C808.v = 0;
            break;
        case 3:
            D_00F2C7B8.v += -1.5625f;
            D_00F2C7E8.v += -1.5625f;
            D_00F2C870.v += -1.5625f;
            D_00F2C818.v += 1.5625f;
            D_00F2C7A8.v = 0;
            D_00F2C7D8.v = 0;
            D_00F2C860.v = 0;
            D_00F2C808.v += 6.375f;
            break;
        }
    }
    if (51.0f <= D_00F2C7B8.v) D_00F2C7B8.v = 51.0f;
    if (51.0f <= D_00F2C7E8.v) D_00F2C7E8.v = 51.0f;
    if (51.0f <= D_00F2C870.v) D_00F2C870.v = 51.0f;
    if (51.0f <= D_00F2C818.v) D_00F2C818.v = 51.0f;
    if (D_00F2C7B8.v <= 26.0f) D_00F2C7B8.v = 26.0f;
    if (D_00F2C7E8.v <= 26.0f) D_00F2C7E8.v = 26.0f;
    if (D_00F2C870.v <= 26.0f) D_00F2C870.v = 26.0f;
    if (D_00F2C818.v <= 26.0f) D_00F2C818.v = 26.0f;
    if (102.0f <= D_00F2C7A8.v) D_00F2C7A8.v = 102.0f;
    if (102.0f <= D_00F2C7D8.v) D_00F2C7D8.v = 102.0f;
    if (102.0f <= D_00F2C860.v) D_00F2C860.v = 102.0f;
    if (102.0f <= D_00F2C808.v) D_00F2C808.v = 102.0f;
}
