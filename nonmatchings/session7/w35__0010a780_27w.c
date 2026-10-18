/* func_0010a780: 27w off (hand/nostrict; session-6 draft 69w). Fixed by w35: the u32 header store written in each mode branch (cnt = ...; *(u32 *)buf = cnt * 13 + 0x70000001; in both arms) gives the original header schedule. Left: the mode==1 inner loop's merged call tail is 'la t2,D_002B67F0; jal; nop' (REG_EQUAL cross-jump of the two arms), the original has 'lui t2; jal; addiu t2,t2,lo' (split pair, slot filled), which shifts 0x10ac7c-0x10acdc by one word. Same class as func_00171078's macro-in-slot. CONTEXT_ONLY func_0010a550 included. */
#include "common.h"

typedef int u128 __attribute__((mode(TI)));
typedef struct { u8 pad[0xa]; u16 kind; u8 padc[0x34]; f32 w, h; } Win;

extern u64 D_002B70B0[];
extern s32 D_00495250;
void func_0010a4d8(u64 *, s32, s32, s32, s32, s32, s32);
CONTEXT_ONLY s32 func_0010a550(u64 *p, s32 a1, s32 a2, s32 a3, s32 a4, s32 idx, s32 a6) {
    p[0] = D_002B70B0[idx];
    p[1] = 0;
    p += 2;
    func_0010a4d8(p, a2, a6, a4, 4, a3, D_00495250);
    ((s32 *)p)[7] = 0x8000;
    ((s32 *)p)[19] = 0x8000;
    return a1 + 13;
}

extern u8 D_002B67F0[], D_002B6830[], D_002B6870[], D_002B68B0[], D_002B68F0[];
extern u8 D_002B6930[], D_002B6970[], D_002B69B0[], D_002B69F0[], D_002B6A30[], D_002B6A70[];
extern u8 D_002B6AB0[], D_002B6AF0[], D_002B6B30[], D_002B6B70[], D_002B6BB0[], D_002B6BF0[], D_002B6C30[], D_002B6C70[];
extern u8 D_002B6CB0[], D_002B6CF0[], D_002B6D30[], D_002B6D70[];
extern u8 D_002B6DB0[], D_002B6DF0[], D_002B6E30[], D_002B6E70[];
extern u8 D_002B6EB0[], D_002B6EF0[], D_002B6F30[], D_002B6F70[];
extern u8 D_002B6FB0[], D_002B6FF0[], D_002B7030[], D_002B7070[];

void func_0010a780(Win *win, void *a1, u128 *buf, s32 a3, s32 mode) {
    f32 pos[2];
    u64 *q;
    s32 nx, ny, cnt, n, i, j;

    nx = win->w;
    ny = win->h;
    *buf = 0;
    if (mode == 1) {
        cnt = (nx + 2) * (ny + 2);
        *(u32 *)buf = cnt * 13 + 0x70000001;
    } else {
        cnt = (nx + ny) * 2 + 4;
        *(u32 *)buf = cnt * 13 + 0x70000001;
    }
    q = (u64 *)(buf + 1);
    q[0] = (cnt | 0x8000) | ((u64)a3 << 47) | 0xd000400000000000;
    q[1] = 0x4124124124128;
    pos[1] = -(win->h * 0.5f * 24.0f + 12.0f);
    pos[0] = -(win->w * 0.5f * 24.0f + 12.0f);
    switch (win->kind) {
    case 3:
        n = func_0010a550((u64 *)(buf + 2), 2, (s32)a1, (s32)pos, (s32)D_002B6DB0, 10, (s32)D_002B6CB0);
        break;
    case 4:
        n = func_0010a550((u64 *)(buf + 2), 2, (s32)a1, (s32)pos, (s32)D_002B6EB0, 14, (s32)D_002B67F0);
        break;
    case 1:
        n = func_0010a550((u64 *)(buf + 2), 2, (s32)a1, (s32)pos, (s32)D_002B6FB0, 18, (s32)D_002B67F0);
        break;
    default:
        n = func_0010a550((u64 *)(buf + 2), 2, (s32)a1, (s32)pos, (s32)D_002B6830, 0, (s32)D_002B67F0);
        break;
    }
    pos[0] += 24.0f;
    for (i = 0; i < nx; i++) {
        switch (win->kind) {
        case 4:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6AF0, 28, (s32)D_002B67F0);
            break;
        case 1:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6BF0, 32, (s32)D_002B67F0);
            break;
        default:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B69F0, 6, (s32)D_002B67F0);
            break;
        }
        pos[0] += 24.0f;
    }
    switch (win->kind) {
    case 3:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6DF0, 11, (s32)D_002B6CF0);
        break;
    case 4:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6EF0, 15, (s32)D_002B67F0);
        break;
    case 1:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6FF0, 19, (s32)D_002B67F0);
        break;
    default:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6870, 1, (s32)D_002B67F0);
        break;
    }
    pos[1] += 24.0f;
    for (j = 0; j < ny; j++) {
        pos[0] = -(win->w * 0.5f * 24.0f + 12.0f);
        switch (win->kind) {
        case 4:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6AB0, 29, (s32)D_002B67F0);
            break;
        case 1:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6BB0, 33, (s32)D_002B67F0);
            break;
        default:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B69B0, 7, (s32)D_002B67F0);
            break;
        }
        pos[0] += 24.0f;
        for (i = 0; i < nx; i++) {
            if (mode == 1) {
                if (win->kind == mode) {
                    n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6970, 5, (s32)D_002B67F0);
                } else {
                    n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6930, 4, (s32)D_002B67F0);
                }
            }
            pos[0] += 24.0f;
        }
        switch (win->kind) {
        case 4:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6B30, 30, (s32)D_002B67F0);
            break;
        case 1:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6C30, 34, (s32)D_002B67F0);
            break;
        default:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6A30, 8, (s32)D_002B67F0);
            break;
        }
        pos[1] += 24.0f;
    }
    pos[0] = -(win->w * 0.5f * 24.0f + 12.0f);
    switch (win->kind) {
    case 3:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6E30, 12, (s32)D_002B6D30);
        break;
    case 4:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6F30, 16, (s32)D_002B67F0);
        break;
    case 1:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B7030, 20, (s32)D_002B67F0);
        break;
    default:
        n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B68B0, 2, (s32)D_002B67F0);
        break;
    }
    pos[0] += 24.0f;
    for (i = 0; i < nx; i++) {
        switch (win->kind) {
        case 4:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6B70, 31, (s32)D_002B67F0);
            break;
        case 1:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6C70, 35, (s32)D_002B67F0);
            break;
        default:
            n = func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6A70, 9, (s32)D_002B67F0);
            break;
        }
        pos[0] += 24.0f;
    }
    switch (win->kind) {
    case 3:
        func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6E70, 13, (s32)D_002B6D70);
        break;
    case 4:
        func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B6F70, 17, (s32)D_002B67F0);
        break;
    case 1:
        func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B7070, 21, (s32)D_002B67F0);
        break;
    default:
        func_0010a550((u64 *)(buf + n), n, (s32)a1, (s32)pos, (s32)D_002B68F0, 3, (s32)D_002B67F0);
        break;
    }
}

