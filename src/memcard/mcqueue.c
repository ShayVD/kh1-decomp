/* The memory card request queue (docs/modules.md "Session 44"),
 * 0x00233a80-0x00234910 (include/memcard/mcreq.h).  func_00233a80 starts
 * libmc (sceMcInit) and clears the queue; func_00233ac8 resets the state
 * and reads each port's card info once (func_00270e40: most likely
 * sceMcGetSlotMax, RPC 21).  D_00425C28[port][slot] is the card's state (0
 * the same card, 1 / 2 a new card (formatted / not), 3 none),
 * D_00425C48 / 68 / 88 are "changed" flags func_00233f40 / 88 / d0 read
 * and clear (func_00233f68 / b0 / f8 clear).  func_00233ef8(n) /
 * func_00233f18 / func_00233ee8: an automatic card-info poll every n frames
 * on the port and slot func_00233f28 sets (D_00647FDC / D_00647FE0). */
#include "common.h"
#include "memcard/mcreq.h"
#include "data/pieces/D_00425C1C.h"
#include "data/pieces/D_00425C28.h"
#include "data/pieces/D_00425C48.h"
#include "data/pieces/D_00425C68.h"
#include "data/pieces/D_00425C88.h"

extern McCmd D_006477B0[64];
extern s32 D_00425CD0[];
extern s32 D_00425C08[];
extern s32 D_00425C10, D_00425C14, D_00425C18, D_00425C20;
extern s32 D_006477A8;
extern s32 D_00647FB0, D_00647FB4, D_00647FB8, D_00647FBC, D_00647FC0, D_00647FC4, D_00647FC8;
extern s32 D_00647FD4, D_00647FD8, D_00647FDC, D_00647FE0;
extern s32 D_00647FE8[];
extern s32 D_00647FEC, D_00647FF0, D_00647FF4, D_00647FF8, D_00647FFC, D_00648000, D_00648004;
extern s32 D_00648008, D_0064800C, D_00648010, D_00648014, D_00648018, D_0064801C;

s32 sceMcInit();
s32 func_00270e40(s32);
s32 func_002715a0(s32, s32, s32 *);
s32 func_002716d8(s32, s32, s32 *, s32 *, s32 *);
void func_00233ac8(void);
void func_002365e0(void);
/* func_00265b28 is left undeclared on purpose (implicit declaration gives the original code). */

void func_00233a80(void) {
    s32 var_v0;
    s64 *var_v1;

    sceMcInit();
    var_v1 = (s64 *)D_006477B0;
    var_v0 = 0x100;
    do {
        var_v0 -= 1;
        *var_v1 = 0;
        var_v1 += 1;
    } while (var_v0 > 0);
    func_00233ac8();
}

void func_00233ac8(void) {
    s32 i, j;
    s32 *p, *q;
    for (i = 0; i < 2; i++) {
        D_00425CD0[i] = 1;
        D_00425C08[i] = func_00270e40(i);
    }
    D_00647FB0 = 0;
    D_00647FB4 = 0;
    D_00647FB8 = 0;
    D_00647FBC = 0;
    D_00647FC0 = 1;
    D_00647FC4 = 1;
    D_00425C10 = 0;
    D_00425C14 = 0;
    D_006477A8 = 0;
    D_00647FD4 = 300;
    D_00647FD8 = 300;
    for (i = 0; i < 14; i++) D_00647FE8[i] = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            (*(s32 (*)[2][4])&D_00425C28)[i][j] = 3;
            D_00425C48[i][j] = 0;
            D_00425C68[i][j] = 0;
            D_00425C88[i][j] = 0;
        }
    }
    q = &D_00647FC8;
    p = D_00425C48[-2];
    for (i = 0; i < 2; p += 4) {
        func_002716d8(i++, 0, &D_00425C18, &D_00425C1C, &D_00425C20);
        func_002715a0(0, 0, q);
        switch (*q) {
        case 0: *p = 0; break;
        case -1: *p = 1; break;
        case -2: *p = 2; break;
        default: *p = 3; break;
        }
    }
}

s32 func_00233d08(s32 id) {
    s32 i, x;
    if (id != 0) {
        i = D_00647FBC;
        while (i != D_00647FB8) {
            x = D_006477B0[i].id;
            i++;
            i &= 63;
            if (x == id) {
                goto found;
            }
        }
        if (D_00647FB0 == 0 || D_00647FC4 != id) {
            goto none;
        }
    found:
        return 1;
    }
    if (D_00647FB8 != D_00647FBC || D_00647FB0 != 0) {
        goto found;
    }
none:
    return 0;
}

void func_00233db0(s32 id) {
    s32 i, x;
    if (id != 0) {
    restart:
        i = D_00647FBC;
        while (i != D_00647FB8) {
            x = D_006477B0[i].id;
            i++;
            i &= 63;
            if (x == id) {
                func_002365e0();
                func_00265b28(0);
                goto restart;
            }
        }
        if (D_00647FB0 != 0 && D_00647FC4 == id) {
            do {
                func_002365e0();
                func_00265b28(0);
            } while (D_00647FB0 != 0);
        }
    } else {
        while (D_00647FB8 != D_00647FBC || D_00647FB0 != 0) {
            func_002365e0();
            func_00265b28(0);
        }
    }
}

s32 func_00233ee8(void) {
    return D_006477A8;
}

void func_00233ef8(s32 arg0) {
    D_006477A8 = 1;
    D_00647FD4 = arg0;
    D_00647FD8 = 0;
}

void func_00233f18(void) {
    D_006477A8 = 0;
}

void func_00233f28(s32 arg0, s32 arg1) {
    D_00647FDC = arg0;
    D_00647FE0 = arg1;
}

s32 func_00233f40(s32 arg0, s32 arg1) {
    s32 *p = &D_00425C48[arg0][arg1];
    s32 v = *p;
    *p = 0;
    return v;
}

void func_00233f68(s32 arg0, s32 arg1) {
    D_00425C48[arg0][arg1] = 0;
}

s32 func_00233f88(s32 arg0, s32 arg1) {
    s32 *p = &D_00425C68[arg0][arg1];
    s32 v = *p;
    *p = 0;
    return v;
}

void func_00233fb0(s32 arg0, s32 arg1) {
    D_00425C68[arg0][arg1] = 0;
}

s32 func_00233fd0(s32 arg0, s32 arg1) {
    s32 *p = &D_00425C88[arg0][arg1];
    s32 v = *p;
    *p = 0;
    return v;
}

void func_00233ff8(s32 arg0, s32 arg1) {
    D_00425C88[arg0][arg1] = 0;
}

s32 func_00234018(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 1;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[2] = arg2;
    return id;
}

s32 func_00234098(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 2;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[4] = arg4;
    return id;
}

s32 func_00234148(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 3;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_006477B0[i].a[4] = arg4;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[5] = arg5;
    return id;
}

s32 func_00234210(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 4;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[2] = arg2;
    return id;
}

s32 func_00234290(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 5;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[2] = arg2;
    return id;
}

s32 func_00234310(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 6;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[3] = arg3;
    return id;
}

s32 func_002343a8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 7;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[3] = arg3;
    return id;
}

s32 func_00234440(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 8;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_006477B0[i].a[4] = arg4;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[5] = arg5;
    return id;
}

s32 func_00234508(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 9;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[3] = arg3;
    return id;
}

s32 func_002345a0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 10;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_006477B0[i].a[4] = arg4;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[5] = arg5;
    return id;
}

s32 func_00234668(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 11;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_006477B0[i].a[4] = arg4;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[5] = arg5;
    return id;
}

s32 func_00234730(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 9;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_006477B0[i].a[3] = arg3;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[4] = arg4;
    return id;
}

s32 func_002347e0(s32 arg0) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 13;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[0] = arg0;
    return id;
}

s32 func_00234840(void) {
    return D_00647FEC;
}

s32 func_00234850(void) {
    return D_00647FF0;
}

s32 func_00234860(void) {
    return D_00647FF4;
}

s32 func_00234870(void) {
    return D_00647FF8;
}

s32 func_00234880(void) {
    return D_00647FFC;
}

s32 func_00234890(void) {
    return D_00648000;
}

s32 func_002348a0(void) {
    return D_00648004;
}

s32 func_002348b0(void) {
    return D_00648008;
}

s32 func_002348c0(void) {
    return D_0064800C;
}

s32 func_002348d0(void) {
    return D_00648010;
}

s32 func_002348e0(void) {
    return D_00648014;
}

s32 func_002348f0(void) {
    return D_00648018;
}

s32 func_00234900(void) {
    return D_0064801C;
}
