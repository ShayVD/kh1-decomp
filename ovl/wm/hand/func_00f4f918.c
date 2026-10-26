/* wm.x func_00f4f918: matched by hand. */
#include "ovl.h"

s32 func_00f4f918(s32 arg0, s32 cur, s32 dir) {
    s32 col;
    s32 row;
    col = cur % 5;
    row = cur / 5;
    switch (dir) {
    case 16:
        row--;
        break;
    case 64:
        row++;
        break;
    case 128:
        col--;
        break;
    case 32:
        col++;
        break;
    default:
        return cur;
    }
    if (row >= 10) {
        row = 0;
    }
    if (row < 0) {
        row = 9;
    }
    if (col < 0) {
        col = 4;
    }
    if (col >= 5) {
        col = 0;
    }
    return row * 5 + col;
}
