#include "common.h"

typedef int u128 __attribute__((mode(TI)));
typedef struct { u8 pad[0xa]; u16 kind; u8 padc[0x34]; f32 w, h; } Win;

s32 func_0010a550(u128 *, s32, void *, f32 *, void *, s32, void *);

extern u8 D_002B67F0[], D_002B6830[], D_002B6870[], D_002B68B0[], D_002B68F0[];
extern u8 D_002B6930[], D_002B6970[], D_002B69B0[], D_002B69F0[], D_002B6A30[], D_002B6A70[];
extern u8 D_002B6AB0[], D_002B6AF0[], D_002B6B30[], D_002B6B70[], D_002B6BB0[], D_002B6BF0[], D_002B6C30[], D_002B6C70[];
extern u8 D_002B6CB0[], D_002B6CF0[], D_002B6D30[], D_002B6D70[];
extern u8 D_002B6DB0[], D_002B6DF0[], D_002B6E30[], D_002B6E70[];
extern u8 D_002B6EB0[], D_002B6EF0[], D_002B6F30[], D_002B6F70[];
extern u8 D_002B6FB0[], D_002B6FF0[], D_002B7030[], D_002B7070[];

void func_0010a780(Win *win, void *a1, u128 *buf, s32 a3, s32 mode) {
    f32 pos[2];
    s32 nx, ny, cnt, n, i, j;

    nx = win->w;
    ny = win->h;
    *buf = 0;
    if (mode == 1) {
        cnt = (nx + 2) * (ny + 2);
    } else {
        cnt = (nx + ny) * 2 + 4;
    }
    *(u32 *)buf = cnt * 13 + 0x70000001;
    ((u64 *)buf)[2] = (cnt | 0x8000) | ((u64)a3 << 47) | 0xd000400000000000;
    ((u64 *)buf)[3] = 0x4124124124128;
    pos[1] = -(win->h * 0.5f * 24.0f + 12.0f);
    pos[0] = -(win->w * 0.5f * 24.0f + 12.0f);
    switch (win->kind) {
    case 3:
        n = func_0010a550(buf + 2, 2, a1, pos, D_002B6DB0, 10, D_002B6CB0);
        break;
    case 4:
        n = func_0010a550(buf + 2, 2, a1, pos, D_002B6EB0, 14, D_002B67F0);
        break;
    case 1:
        n = func_0010a550(buf + 2, 2, a1, pos, D_002B6FB0, 18, D_002B67F0);
        break;
    default:
        n = func_0010a550(buf + 2, 2, a1, pos, D_002B6830, 0, D_002B67F0);
        break;
    }
    pos[0] += 24.0f;
    for (i = nx; i > 0; i--) {
        switch (win->kind) {
        case 1:
            n = func_0010a550(buf + n, n, a1, pos, D_002B6BF0, 32, D_002B67F0);
            break;
        case 4:
            n = func_0010a550(buf + n, n, a1, pos, D_002B6AF0, 28, D_002B67F0);
            break;
        default:
            n = func_0010a550(buf + n, n, a1, pos, D_002B69F0, 6, D_002B67F0);
            break;
        }
        pos[0] += 24.0f;
    }
    switch (win->kind) {
    case 3:
        n = func_0010a550(buf + n, n, a1, pos, D_002B6DF0, 11, D_002B6CF0);
        break;
    case 4:
        n = func_0010a550(buf + n, n, a1, pos, D_002B6EF0, 15, D_002B67F0);
        break;
    case 1:
        n = func_0010a550(buf + n, n, a1, pos, D_002B6FF0, 19, D_002B67F0);
        break;
    default:
        n = func_0010a550(buf + n, n, a1, pos, D_002B6870, 1, D_002B67F0);
        break;
    }
    pos[1] += 24.0f;
    for (j = ny; j > 0; j--) {
        pos[0] = -(win->w * 0.5f * 24.0f + 12.0f);
        switch (win->kind) {
        case 1:
            n = func_0010a550(buf + n, n, a1, pos, D_002B6BB0, 33, D_002B67F0);
            break;
        case 4:
            n = func_0010a550(buf + n, n, a1, pos, D_002B6AB0, 29, D_002B67F0);
            break;
        default:
            n = func_0010a550(buf + n, n, a1, pos, D_002B69B0, 7, D_002B67F0);
            break;
        }
        pos[0] += 24.0f;
        for (i = nx; i > 0; i--) {
            if (mode == 1) {
                if (win->kind == mode) {
                    n = func_0010a550(buf + n, n, a1, pos, D_002B6970, 5, D_002B67F0);
                } else {
                    n = func_0010a550(buf + n, n, a1, pos, D_002B6930, 4, D_002B67F0);
                }
            }
            pos[0] += 24.0f;
        }
        switch (win->kind) {
        case 1:
            n = func_0010a550(buf + n, n, a1, pos, D_002B6C30, 34, D_002B67F0);
            break;
        case 4:
            n = func_0010a550(buf + n, n, a1, pos, D_002B6B30, 30, D_002B67F0);
            break;
        default:
            n = func_0010a550(buf + n, n, a1, pos, D_002B6A30, 8, D_002B67F0);
            break;
        }
        pos[1] += 24.0f;
    }
    pos[0] = -(win->w * 0.5f * 24.0f + 12.0f);
    switch (win->kind) {
    case 3:
        n = func_0010a550(buf + n, n, a1, pos, D_002B6E30, 12, D_002B6D30);
        break;
    case 4:
        n = func_0010a550(buf + n, n, a1, pos, D_002B6F30, 16, D_002B67F0);
        break;
    case 1:
        n = func_0010a550(buf + n, n, a1, pos, D_002B7030, 20, D_002B67F0);
        break;
    default:
        n = func_0010a550(buf + n, n, a1, pos, D_002B68B0, 2, D_002B67F0);
        break;
    }
    pos[0] += 24.0f;
    for (i = nx; i > 0; i--) {
        switch (win->kind) {
        case 1:
            n = func_0010a550(buf + n, n, a1, pos, D_002B6C70, 35, D_002B67F0);
            break;
        case 4:
            n = func_0010a550(buf + n, n, a1, pos, D_002B6B70, 31, D_002B67F0);
            break;
        default:
            n = func_0010a550(buf + n, n, a1, pos, D_002B6A70, 9, D_002B67F0);
            break;
        }
        pos[0] += 24.0f;
    }
    switch (win->kind) {
    case 3:
        func_0010a550(buf + n, n, a1, pos, D_002B6E70, 13, D_002B6D70);
        break;
    case 4:
        func_0010a550(buf + n, n, a1, pos, D_002B6F70, 17, D_002B67F0);
        break;
    case 1:
        func_0010a550(buf + n, n, a1, pos, D_002B7070, 21, D_002B67F0);
        break;
    default:
        func_0010a550(buf + n, n, a1, pos, D_002B68F0, 3, D_002B67F0);
        break;
    }
}
