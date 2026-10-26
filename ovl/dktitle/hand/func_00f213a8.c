/* dktitle.x func_00f213a8: matched by hand. */
#include "ovl.h"

typedef struct { f32 v; s32 st; s32 t; } Fade;
extern Fade D_00F2C838, D_00F2C7A8, D_00F2C7B8, D_00F2C7C8, D_00F2C7E8;
extern Fade D_00F2C7D8, D_00F2C860, D_00F2C808, D_00F2C7F8, D_00F2C880, D_00F2C828, D_00F2C870, D_00F2C818;
void func_00f213a8(void) {
    switch (D_00F2C838.st) {
    case 0:
        D_00F2C838.v += 0.001f;
        if (0.17999998f <= D_00F2C838.v) { D_00F2C838.st = 1; D_00F2C838.v = 0; }
        break;
    case 1:
        D_00F2C838.v += 2.1333334f;
        if (128.0f <= D_00F2C838.v) { D_00F2C838.v = 128.0f; D_00F2C838.st = 2; }
        break;
    }
    switch (D_00F2C7A8.st) {
    case 0:
        D_00F2C7A8.v += 0.001f; D_00F2C7D8.v += 0.001f; D_00F2C860.v += 0.001f; D_00F2C808.v += 0.001f;
        if (0.11999999f <= D_00F2C7A8.v) { D_00F2C7A8.st = 1; D_00F2C7A8.v = 0; D_00F2C7D8.v = 0; D_00F2C860.v = 0; D_00F2C808.v = 0; }
        break;
    case 1:
        D_00F2C7A8.v += 0.85f; D_00F2C7D8.v += 0.85f; D_00F2C860.v += 0.85f; D_00F2C808.v += 0.85f;
        if (102.0f <= D_00F2C7A8.v) { D_00F2C7A8.v = 102.0f; D_00F2C7A8.st = 2; D_00F2C7D8.v = 0; D_00F2C860.v = 0; D_00F2C808.v = 0; }
        break;
    }
    switch (D_00F2C7C8.st) {
    case 0:
        D_00F2C7C8.v += 0.001f; D_00F2C7F8.v += 0.001f; D_00F2C880.v += 0.001f; D_00F2C828.v += 0.001f;
        if (0.11999999f <= D_00F2C7C8.v) { D_00F2C7C8.st = 1; D_00F2C7C8.v = 0; D_00F2C7F8.v = 0; D_00F2C880.v = 0; D_00F2C828.v = 0; }
        break;
    case 1:
        D_00F2C7C8.v += 2.1333334f; D_00F2C7F8.v += 2.1333334f; D_00F2C880.v += 2.1333334f; D_00F2C828.v += 2.1333334f;
        if (128.0f <= D_00F2C7C8.v) { D_00F2C7C8.v = 128.0f; D_00F2C7C8.st = 2; D_00F2C7F8.v = 128.0f; D_00F2C880.v = 128.0f; D_00F2C828.v = 128.0f; }
        break;
    }
    switch (D_00F2C7B8.st) {
    case 0:
        D_00F2C7B8.v += 0.001f;
        if (0.11999999f <= D_00F2C7B8.v) { D_00F2C7B8.st = 1; D_00F2C7B8.v = 0; }
        break;
    case 1:
        D_00F2C7B8.v += 0.85f;
        if (51.0f <= D_00F2C7B8.v) { D_00F2C7B8.v = 51.0f; D_00F2C7B8.st = 2; }
        break;
    }
    switch (D_00F2C7E8.st) {
    case 0:
        D_00F2C7E8.v += 0.001f; D_00F2C870.v += 0.001f; D_00F2C818.v += 0.001f;
        if (0.11999999f <= D_00F2C7E8.v) { D_00F2C7E8.st = 1; D_00F2C7E8.v = 0; D_00F2C870.v = 0; D_00F2C818.v = 0; }
        break;
    case 1:
        D_00F2C7E8.v += 0.43333333f; D_00F2C870.v += 0.43333333f; D_00F2C818.v += 0.43333333f;
        if (26.0f <= D_00F2C7E8.v) { D_00F2C7E8.v = 26.0f; D_00F2C7E8.st = 2; D_00F2C870.v = 26.0f; D_00F2C818.v = 26.0f; }
        break;
    }
}
