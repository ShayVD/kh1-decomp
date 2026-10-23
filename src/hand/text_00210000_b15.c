#include "common.h"
#include "data/bss_0064.h"
#include "vm/script_vm.h"

extern s32 D_00647FB4, D_00647FC8, D_00647FD8, D_00647FD4, D_00647FB0, D_00647FC4;
typedef struct { s32 x0, x4; } S2;
extern S2 D_00647FE8;
extern void (*D_00648034)(s32);
extern s32 D_00425C10, D_00425C14, D_00425C18, D_00425C20;
#include "data/pieces/D_00425C1C.h"
#include "data/pieces/D_00425C28.h"
#include "data/pieces/D_00425C88.h"
#include "data/pieces/D_00425C68.h"
#include "data/pieces/D_00425C48.h"
s32 func_002716d8(s32, s32, s32 *, s32 *, s32 *);
s32 func_002715a0(s32, s32, s32 *);

void func_00234f80(void) {
    switch (D_00647FB4) {
    case 0:
        func_002716d8(D_00425C10, D_00425C14, &D_00425C18, &D_00425C1C, &D_00425C20);
        D_00647FB4++;
        return;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        return;
    case 2:
        if (D_00425C18 == 3) {
            ((s32 (*)[4])&D_00425C28)[D_00425C10][D_00425C14] = 3;
        } else {
            switch (D_00647FC8) {
            case 0:
                D_00647FE8.x4 = 0;
                ((s32 (*)[4])&D_00425C28)[D_00425C10][D_00425C14] = 0;
                break;
            case -1:
                D_00647FE8.x4 = 0;
                ((s32 (*)[4])&D_00425C28)[D_00425C10][D_00425C14] = 1;
                D_00425C48[D_00425C10][D_00425C14] = 1;
                D_00425C68[D_00425C10][D_00425C14] = 1;
                break;
            case -2:
                D_00647FE8.x4 = 0;
                ((s32 (*)[4])&D_00425C28)[D_00425C10][D_00425C14] = 2;
                D_00425C48[D_00425C10][D_00425C14] = 1;
                D_00425C68[D_00425C10][D_00425C14] = 1;
                break;
            default:
                ((s32 (*)[4])&D_00425C28)[D_00425C10][D_00425C14] = 3;
                if (!D_00647FE8.x4) {
                    D_00425C48[D_00425C10][D_00425C14] = 1;
                    D_00425C88[D_00425C10][D_00425C14] = 1;
                }
                D_00647FE8.x4 = 1;
                break;
            }
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034) D_00648034(D_00647FC4);
        break;
    }
}

/* needs make: uses rodata */
extern s32 D_00647FB4, D_00647FC8, D_00647FD8, D_00647FD4, D_00647FB0, D_00647FC4;
extern s32 D_00648008, D_00648020, D_00648028, D_0064802C, D_00648030;
extern void (*D_00648034)(s32);
extern s32 D_00425C10, D_00425C14;
s32 func_00270f00(s32, s32, s32, s32);
s32 func_002713b0(s32, s32, s32);
s32 func_00271070(s32);
s32 func_002715a0(s32, s32, s32 *);

void func_00235ab0(void) {
    s32 r, q;
    switch (D_00647FB4) {
    case 0:
        func_00270f00(D_00425C10, D_00425C14, D_00648020, 515);
        D_00647FB4++;
        break;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        break;
    case 2:
        r = D_00647FC8;
        if (r >= 0) {
            D_00648030 = r;
            D_00647FB4++;
            break;
        }
        if (r == -2) { D_00648008 = 1; goto tail; }
        else if (r == -3) { D_00648008 = 2; goto tail; }
        else if (r == -4) { D_00648008 = 3; goto tail; }
        else if (r == -5) { D_00648008 = 4; goto tail; }
        else if (r == -7) { D_00648008 = 5; goto tail; }
        else { D_00648008 = 7; goto tail; }
    case 3:
        func_002713b0(D_00648030, D_00648028, D_0064802C);
        D_00647FB4++;
        break;
    case 4:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        break;
    case 5:
        q = D_00647FC8;
        if (q >= 0) {
            if (q == D_0064802C) D_00648008 = 0;
            else D_00648008 = 6;
        }
        else if (q == -2) D_00648008 = 1;
        else if (q == -3) D_00648008 = 2;
        else if (q == -4) D_00648008 = 5;
        else if (q == -5) D_00648008 = 4;
        else if (q == -8) D_00648008 = 6;
        else D_00648008 = 7;
        D_00647FB4++;
        break;
    case 6:
        func_00271070(D_00648030);
        D_00647FB4++;
        break;
    case 7:
        if (func_002715a0(1, 0, &D_00647FC8)) {
        tail:
            D_00647FB0 = 0;
            D_00647FD8 = D_00647FD4;
            if (D_00648034) D_00648034(D_00647FC4);
        }
        break;
    }
}

extern s32 D_00647FB4, D_00647FC8, D_00647FD8, D_00647FD4, D_00647FB0, D_00647FC4;
extern s32 D_00648010, D_00648020, D_00648028, D_0064802C, D_00648030;
extern void (*D_00648034)(s32);
extern s32 D_00425C10, D_00425C14;
s32 func_00270f00(s32, s32, s32, s32);
s32 func_00271290(s32, s32, s32);
s32 func_00271070(s32);
s32 func_002715a0(s32, s32, s32 *);

void func_00235ee8(void) {
    s32 r, q;
    switch (D_00647FB4) {
    case 0:
        func_00270f00(D_00425C10, D_00425C14, D_00648020, 1);
        D_00647FB4++;
        break;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        break;
    case 2:
        r = D_00647FC8;
        if (r >= 0) {
            D_00648030 = r;
            D_00647FB4++;
            break;
        }
        if (r == -2) { D_00648010 = 1; goto tail; }
        else if (r == -3) { D_00648010 = 2; goto tail; }
        else if (r == -4) { D_00648010 = 3; goto tail; }
        else if (r == -5) { D_00648010 = 4; goto tail; }
        else if (r == -7) { D_00648010 = 5; goto tail; }
        else { D_00648010 = 7; goto tail; }
    case 3:
        func_00271290(D_00648030, D_00648028, D_0064802C);
        D_00647FB4++;
        break;
    case 4:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        break;
    case 5:
        q = D_00647FC8;
        if (q >= 0) {
            if (q == D_0064802C) D_00648010 = 0;
            else D_00648010 = 6;
        }
        else if (q == -2) D_00648010 = 1;
        else if (q == -3) D_00648010 = 6;
        else if (q == -4) D_00648010 = 5;
        else if (q == -5) D_00648010 = 4;
        else D_00648010 = 7;
        D_00647FB4++;
        break;
    case 6:
        func_00271070(D_00648030);
        D_00647FB4++;
        break;
    case 7:
        if (func_002715a0(1, 0, &D_00647FC8)) {
        tail:
            D_00647FB0 = 0;
            D_00647FD8 = D_00647FD4;
            if (D_00648034) D_00648034(D_00647FC4);
        }
        break;
    }
}

#include "data/data_003F.h"
#include "data/data_0042.h"
#include "data/data_003E.h"
#include "data/pieces/D_00425C10.h"
#include "data/pieces/D_00425C14.h"
