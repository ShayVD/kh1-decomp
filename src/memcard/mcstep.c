/* The memory card request steps (docs/modules.md "Session 44"),
 * 0x00234910-0x00236618 (include/memcard/mcreq.h).  func_002365e0 runs
 * D_00425BD0[D_00647FB0] once a frame: func_00234910 (0, idle) takes the
 * next request off the queue (or, with the poll on, a card-info request
 * every D_00647FD4 frames) into D_00647FB0 (the kind), D_00647FC4 (its id),
 * D_00425C10 / D_00425C14 (port, slot), D_00648020 (a name), D_00648028 /
 * D_0064802C (a buffer and its size) or D_00425CA8 / D_00425CAC (a table
 * and its length), D_00648024 and the hook D_00648034; then each step
 * calls libmc, waits for sceMcSync (D_00647FC8 the result) step by step in
 * D_00647FB4, writes its answer code, goes back to 0 and calls the hook.
 * The libmc functions, named by their mcserv RPC numbers (docs/sdk.md):
 * func_002716d8 sceMcGetInfo (1), func_00270f00 sceMcOpen (2),
 * func_00271070 sceMcClose (3), func_00271290 sceMcRead (5),
 * func_002713b0 sceMcWrite (6), func_00271ab0 sceMcChdir (12),
 * func_002718d0 sceMcGetDir (13), func_00272080 sceMcSetFileInfo (14),
 * func_00271cc8 sceMcDelete (15), func_00271c00 sceMcFormat (16),
 * func_002721e8 sceMcUnformat (17), func_00271038 sceMcMkdir (sceMcOpen
 * with mode 0x40), func_002715a0 sceMcSync (no RPC).  Open modes: 1 read,
 * 2 write, 0x203 create + read / write.  A format or unformat that fails is
 * tried again after 60 frames while D_00647FCC lasts. */
#include "common.h"
#include "memcard/mcreq.h"
#include "data/pieces/D_00425C1C.h"
#include "data/pieces/D_00425C28.h"
#include "data/pieces/D_00425C48.h"
#include "data/pieces/D_00425C68.h"
#include "data/pieces/D_00425C88.h"
#include "data/pieces/D_00425C10.h"
#include "data/pieces/D_00425C14.h"
#include "data/pieces/D_00425CA8.h"
#include "data/pieces/D_00425CAC.h"

extern McCmd D_006477B0[64];
extern s32 D_00425C18, D_00425C20;
extern s32 D_00425CB0;
extern s32 D_006477A8;
extern s32 D_00647FB0, D_00647FB4, D_00647FB8, D_00647FBC, D_00647FC4, D_00647FC8;
extern s32 D_00647FCC, D_00647FD0, D_00647FD4, D_00647FD8, D_00647FDC, D_00647FE0;
extern s32 D_00647FE8[];
extern s32 D_00647FF0, D_00647FF4, D_00647FF8, D_00647FFC, D_00648000, D_00648004;
extern s32 D_00648008, D_0064800C, D_00648010, D_00648014, D_00648018, D_0064801C;
extern s32 D_00648020, D_00648024, D_00648028, D_0064802C, D_00648030;
extern s32 (*D_00648034)(s32);

s32 func_00270f00(s32, s32, s32, s32);
s32 func_00271038(s32, s32, s32);
s32 func_00271070(s32);
s32 func_00271290(s32, s32, s32);
s32 func_002713b0(s32, s32, s32);
s32 func_002715a0(s32, s32, s32 *);
s32 func_002716d8(s32, s32, s32 *, s32 *, s32 *);
s32 func_002718d0(s32, s32, s32, s32, s32, s32);
s32 func_00271ab0(s32, s32, s32, s32 *);
s32 func_00271c00(s32, s32);
s32 func_00271cc8(s32, s32, s32);
s32 func_00272080(s32, s32, s32, s32);
s32 func_002721e8(s32, s32);

extern void (*D_00425BD0[])(void);
void func_00234910(void) {
    if (D_00647FB8 != D_00647FBC) {
        switch (D_006477B0[D_00647FBC].type) {
        case 1:
            D_00647FB0 = 1;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648034 = (void *)D_006477B0[D_00647FBC].a[2];
            D_00647FC4 = D_006477B0[D_00647FBC].id;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 2:
            D_00647FB0 = 2;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00425CA8 = D_006477B0[D_00647FBC].a[2];
            D_00425CAC = D_006477B0[D_00647FBC].a[3];
            D_00648034 = (void *)D_006477B0[D_00647FBC].a[4];
            D_00647FC4 = D_006477B0[D_00647FBC].id;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 3:
            D_00647FB0 = 3;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00425CA8 = D_006477B0[D_00647FBC].a[3];
            D_00425CAC = D_006477B0[D_00647FBC].a[4];
            D_00648034 = (void *)D_006477B0[D_00647FBC].a[5];
            D_00647FC4 = D_006477B0[D_00647FBC].id;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 4:
            D_00647FB0 = 4;
            D_00647FB4 = 0;
            D_00647FCC = 0;
            D_00647FD0 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648034 = (void *)D_006477B0[D_00647FBC].a[2];
            D_00647FC4 = D_006477B0[D_00647FBC].id;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 5:
            D_00647FB0 = 5;
            D_00647FB4 = 0;
            D_00647FCC = 0;
            D_00647FD0 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648034 = (void *)D_006477B0[D_00647FBC].a[2];
            D_00647FC4 = D_006477B0[D_00647FBC].id;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 6:
            D_00647FB0 = 6;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648034 = (void *)D_006477B0[D_00647FBC].a[3];
            D_00647FC4 = D_006477B0[D_00647FBC].id;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 7:
            D_00647FB0 = 7;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648034 = (void *)D_006477B0[D_00647FBC].a[3];
            D_00647FC4 = D_006477B0[D_00647FBC].id;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 8:
            D_00647FB0 = 8;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648028 = D_006477B0[D_00647FBC].a[3];
            D_0064802C = D_006477B0[D_00647FBC].a[4];
            D_00648034 = (void *)D_006477B0[D_00647FBC].a[5];
            D_00647FC4 = D_006477B0[D_00647FBC].id;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 9:
            D_00647FB0 = 9;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648034 = (void *)D_006477B0[D_00647FBC].a[3];
            D_00647FC4 = D_006477B0[D_00647FBC].id;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 10:
            D_00647FB0 = 10;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648028 = D_006477B0[D_00647FBC].a[3];
            D_0064802C = D_006477B0[D_00647FBC].a[4];
            D_00648034 = (void *)D_006477B0[D_00647FBC].a[5];
            D_00647FC4 = D_006477B0[D_00647FBC].id;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 11:
            D_00647FB0 = 11;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648028 = D_006477B0[D_00647FBC].a[3];
            D_0064802C = D_006477B0[D_00647FBC].a[4];
            D_00648034 = (void *)D_006477B0[D_00647FBC].a[5];
            D_00647FC4 = D_006477B0[D_00647FBC].id;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 12:
            D_00647FB0 = 12;
            D_00647FB4 = 0;
            D_00425C10 = D_006477B0[D_00647FBC].a[0];
            D_00425C14 = D_006477B0[D_00647FBC].a[1];
            D_00648020 = D_006477B0[D_00647FBC].a[2];
            D_00648024 = D_006477B0[D_00647FBC].a[3];
            D_00648034 = (void *)D_006477B0[D_00647FBC].a[4];
            D_00647FC4 = D_006477B0[D_00647FBC].id;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        case 13:
            D_00647FB0 = 13;
            D_00648034 = (void *)D_006477B0[D_00647FBC].a[0];
            D_00647FC4 = D_006477B0[D_00647FBC].id;
            D_00647FBC = (D_00647FBC + 1) & 0x3f;
            break;
        }
    } else if (D_006477A8 != 0) {
        if (D_00647FD8 != 0) {
            D_00647FD8--;
        } else {
            D_00647FB0 = 1;
            D_00647FB4 = 0;
            D_00425C10 = D_00647FDC;
            D_00425C14 = D_00647FE0;
            D_00647FD8 = D_00647FD4;
            D_00648034 = 0;
        }
    }
}

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
                D_00647FE8[1] = 0;
                ((s32 (*)[4])&D_00425C28)[D_00425C10][D_00425C14] = 0;
                break;
            case -1:
                D_00647FE8[1] = 0;
                ((s32 (*)[4])&D_00425C28)[D_00425C10][D_00425C14] = 1;
                D_00425C48[D_00425C10][D_00425C14] = 1;
                D_00425C68[D_00425C10][D_00425C14] = 1;
                break;
            case -2:
                D_00647FE8[1] = 0;
                ((s32 (*)[4])&D_00425C28)[D_00425C10][D_00425C14] = 2;
                D_00425C48[D_00425C10][D_00425C14] = 1;
                D_00425C68[D_00425C10][D_00425C14] = 1;
                break;
            default:
                ((s32 (*)[4])&D_00425C28)[D_00425C10][D_00425C14] = 3;
                if (!D_00647FE8[1]) {
                    D_00425C48[D_00425C10][D_00425C14] = 1;
                    D_00425C88[D_00425C10][D_00425C14] = 1;
                }
                D_00647FE8[1] = 1;
                break;
            }
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034) D_00648034(D_00647FC4);
        break;
    }
}

s32 func_00235228(void) {
    s32 *pc = &D_00647FB4;
    s32 v, r;
    switch (*pc) {
    case 0:
        r = func_002718d0(D_00425C10, D_00425C14, (s32)"*", 0, D_00425CAC, D_00425CA8);
        (*pc)++;
        return r;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        v = D_00647FC8;
        if (v >= 0) {
            D_00425CAC = v;
            D_00647FF0 = 0;
        } else if (v == -2) {
            D_00425CAC = -1;
            D_00647FF0 = 1;
        } else if (v == -4) {
            D_00425CAC = -1;
            D_00647FF0 = 2;
        } else {
            D_00425CAC = -1;
            D_00647FF0 = 3;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    }
}

s32 func_002353a8(void) {
    s32 *pc = &D_00647FB4;
    s32 v, r;
    switch (*pc) {
    case 0:
        r = func_002718d0(D_00425C10, D_00425C14, D_00648020, 0, D_00425CAC, D_00425CA8);
        (*pc)++;
        return r;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        v = D_00647FC8;
        if (v >= 0) {
            D_00425CAC = v;
            D_00647FF4 = 0;
        } else if (v == -2) {
            D_00425CAC = -1;
            D_00647FF4 = 2;
        } else if (v == -4) {
            D_00425CAC = -1;
            D_00647FF4 = 3;
        } else {
            D_00425CAC = -1;
            D_00647FF4 = 4;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    }
}

void func_00235520(void) {
    s32 *pc = &D_00647FB4;
    s32 n;
    switch (*pc) {
    case 0:
        func_00271c00(D_00425C10, D_00425C14);
        (*pc)++;
        break;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        if (D_00647FC8 != 0) {
            n = D_00647FCC;
            if (n != 0) {
                D_00647FCC = n - 1;
                D_00647FD0 = 60;
                *pc = 3;
                break;
            }
            D_00647FF8 = 1;
        } else {
            D_00647FF8 = 0;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    case 3:
        if (D_00647FD0 != 0) D_00647FD0--;
        else *pc = 0;
        break;
    }
}

void func_00235688(void) {
    s32 *pc = &D_00647FB4;
    s32 n;
    switch (*pc) {
    case 0:
        func_002721e8(D_00425C10, D_00425C14);
        (*pc)++;
        break;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        if (D_00647FC8 != 0) {
            n = D_00647FCC;
            if (n != 0) {
                D_00647FCC = n - 1;
                D_00647FD0 = 60;
                *pc = 3;
                break;
            }
            D_00647FFC = 1;
        } else {
            D_00647FFC = 0;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    case 3:
        if (D_00647FD0 != 0) D_00647FD0--;
        else *pc = 0;
        break;
    }
}

s32 func_002357f0(void) {
    s32 *pc = &D_00647FB4;
    s32 r;
    switch (*pc) {
    case 0:
        r = func_00271ab0(D_00425C10, D_00425C14, D_00648020, &D_00425CB0);
        (*pc)++;
        return r;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        switch (D_00647FC8) {
        case 0:
            D_00648000 = 0;
            break;
        case -2:
            D_00648000 = 1;
            break;
        case -4:
            D_00648000 = 2;
            break;
        default:
            D_00648000 = 3;
            break;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    }
}

s32 func_00235950(void) {
    s32 *pc = &D_00647FB4;
    s32 r;
    switch (*pc) {
    case 0:
        r = func_00271038(D_00425C10, D_00425C14, D_00648020);
        (*pc)++;
        return r;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        switch (D_00647FC8) {
        case 0:
            D_00648004 = 0;
            break;
        case -2:
            D_00648004 = 1;
            break;
        case -3:
            D_00648004 = 2;
            break;
        case -4:
            D_00648004 = 3;
            break;
        default:
            D_00648004 = 4;
            break;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    }
}

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

s32 func_00235d70(void) {
    s32 *pc = &D_00647FB4;
    s32 r;
    switch (*pc) {
    case 0:
        r = func_00271cc8(D_00425C10, D_00425C14, D_00648020);
        (*pc)++;
        return r;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        switch (D_00647FC8) {
        case 0:
            D_0064800C = 0;
            break;
        case -2:
            D_0064800C = 1;
            break;
        case -4:
            D_0064800C = 2;
            break;
        case -5:
            D_0064800C = 3;
            break;
        case -6:
            D_0064800C = 4;
            break;
        default:
            D_0064800C = 5;
            break;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    }
}

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

void func_00236190(void) {

    switch (D_00647FB4) {
    case 0:
        func_00270f00(D_00425C10, D_00425C14, D_00648020, 2);
        D_00647FB4++;
        break;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        break;
    case 2: {
        s32 v = D_00647FC8;
        if (v >= 0) {
            D_00648030 = v;
            D_00647FB4++;
            break;
        }
        if (v == -2) D_00648014 = 1;
        else if (v == -3) D_00648014 = 2;
        else if (v == -4) D_00648014 = 3;
        else if (v == -5) D_00648014 = 4;
        else if (v == -7) D_00648014 = 5;
        else D_00648014 = 7;
        goto common; }
    case 3:
        func_002713b0(D_00648030, D_00648028, D_0064802C);
        D_00647FB4++;
        break;
    case 4:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        break;
    case 5: {
        s32 v = D_00647FC8;
        if (v >= 0) {
            if (v == D_0064802C) D_00648014 = 0;
            else D_00648014 = 6;
        } else {
            if (v == -2) D_00648014 = 1;
            else if (v == -3) D_00648014 = 2;
            else if (v == -4) D_00648014 = 5;
            else if (v == -5) D_00648014 = 4;
            else if (v == -8) D_00648014 = 6;
            else D_00648014 = 7;
        }
        D_00647FB4++;
        break; }
    case 6:
        func_00271070(D_00648030);
        D_00647FB4++;
        break;
    case 7:
        if (func_002715a0(1, 0, &D_00647FC8)) {
        common:
            D_00647FB0 = 0;
            D_00647FD8 = D_00647FD4;
            if (D_00648034) D_00648034(D_00647FC4);
        }
        break;
    }
}

s32 func_00236450(void) {
    s32 *pc = &D_00647FB4;
    s32 r, v;
    switch (*pc) {
    case 0:
        r = func_00272080(D_00425C10, D_00425C14, D_00648020, D_00648024);
        (*pc)++;
        return r;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8) != 0) (*pc)++;
        break;
    case 2:
        v = D_00647FC8;
        if (v == 0) {
            D_00648018 = 0;
        } else if (v == -2) {
            D_00648018 = 1;
        } else if (v == -4) {
            D_00648018 = 2;
        } else {
            D_00648018 = 3;
        }
        D_00647FB0 = 0;
        D_00647FD8 = D_00647FD4;
        if (D_00648034 != 0) D_00648034(D_00647FC4);
        break;
    }
}

void func_00236598(void) {
    D_00647FB0 = 0;
    D_00647FD8 = D_00647FD4;
    D_0064801C = D_00648034(D_00647FC4);
}

void func_002365e0(void) {
    D_00425BD0[D_00647FB0]();
}

/* The steps, by request kind (0: take the next request); the six that
 * return libmc's answer of their first call are cast. */
typedef void (*Step)(void);
void (*D_00425BD0[0xe])(void) ALIGNED(16) = {
    func_00234910, func_00234f80, (Step)func_00235228, (Step)func_002353a8,
    func_00235520, func_00235688, (Step)func_002357f0, (Step)func_00235950,
    func_00235ab0, (Step)func_00235d70, func_00235ee8, func_00236190,
    (Step)func_00236450, func_00236598,
};
