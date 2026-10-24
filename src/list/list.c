/* The record lists (docs/modules.md "Session 35"), 0x001e4918-0x001e7e78.
 *
 * Menus a script opens over save block 1's four lists at 0xa80 (10, 10, 10
 * and 50 entries, 0 = empty; include/save/save1.h): func_001e58c0(list) shows
 * a list with each entry's name and text from the tables D_006310C8 /
 * D_00631148 / D_006311C8 / D_00631248 (loaded by func_001e4918 at script
 * load), func_001e74b0(list) picks an entry (the pick is read back by
 * func_001e7488), and func_001e5d78, func_001e79a0, func_001e7ad8 and
 * func_001e7e00 are other VM library entries (D_003D9FE0 1975-1979).  The
 * fourth list is paged, 10 entries a page (D_006305CC).  The windows are
 * D_00630300 / D_006303B0 / D_00630460 / D_00630510, four window records of
 * 0xb0 bytes like the message windows' (MsgWin; the text of D_00630300 at
 * D_00630380, of D_00630460 at D_006304E0), with the choice list
 * D_006305C0, the entry numbers D_006305D0 and the text buffers D_006307C8
 * / D_00630FC8; the state is D_003DD258-D_003DD28C.  That data is theirs
 * alone: it follows the shop's D_0062FF00 / D_003DC494, and the code after
 * 0x001e7e78 works on the D_006314CC counters instead. */
#include "common.h"
#include "save/save1.h"
#include "data/types/vm_rec.h"
#include "vm/vm_mgr.h"
#include "msgwin/msgwin.h"
#include "data/types/text_001c0000_c10.h"
#include "data/bss_0063.h"
#include "data/data_003D.h"
#include "data/data_003E.h"
#include "data/data_003F.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_003DCB90.h"
#include "data/pieces/D_003DCD70.h"
#include "data/pieces/D_003DD230.h"
#include "data/pieces/D_003DD258.h"
#include "data/pieces/D_003DD28C.h"
#include "list/listmenu.h"

/* A choice list (func_0010f558): fn gets the index picked. */
typedef struct { s32 a; s32 n; void (*fn)(); s32 d; } ListCb;

extern VmMgr D_00389C90;
extern volatile s32 D_002C5958;
extern s32 D_002C5BB8;
extern ListMenu D_003DC498;
extern char D_003DCB10[][32];
extern MsgWin D_00630300;
extern MsgWin D_006303B0;   /* src/data/bss_0063.c: u8 D_006303B0[0xb0] */
extern MsgWin D_00630460;
extern MsgWin D_00630510;   /* src/data/bss_0063.c: u8 D_00630510[0xb0] */
extern u8 D_00630460_rec[] __asm__("D_00630460");
#define D_006304E0 (D_00630460_rec + 0x80) /* D_00630460.f80 */
extern ListCb D_006305C0;
extern s32 D_006305CC;
extern char D_006305D0[][10];
extern char D_006307C8[];
extern char D_00630FC8[];
extern Pair D_006310C8[];
extern Pair D_00631148[];
extern Pair D_006311C8[];
extern Pair D_00631248[];
extern s8 D_006314C8;

void func_0010bd90(void *, void *);
void func_0010bdd0(void *, void *);
void func_0010e3f0(void *);
void func_0010ef70(void *, void *, void *);
void func_0010f558(void *, void *, s32);
s32 func_0011ef10(s32, void *);
void func_001c2d20(s8 *p, s32 *cnt, s8 **tbl);
void func_001ea128(void *, void *);
void func_001ea268(void *, void *);
void func_002329a0(void *, void *, void *);
void func_00232aa8(void);
void *func_00232cc0(s32);

void func_001e4918(void);
void func_001e4990(void);
s32 func_001e4a68(void);
void func_001e4b08(void);
void func_001e4c20(void);
void func_001e4d20(void);
void func_001e4d50(void);
void func_001e5198(void);
void func_001e5788(s32 a);
void func_001e5810(void);
void func_001e58c0(s32 mode);
s32 func_001e5d78(void);
void func_001e5ee0(void);
s32 func_001e6038(void);
void func_001e61c0();
void func_001e6388(void);
s32 func_001e63a8(void);
void func_001e6410(void);
void func_001e6438(s32 arg0);
s32 func_001e6450(void);
void func_001e64e0(void);
s32 func_001e6500(void);
void func_001e6578(void);
void func_001e6580(s32 a);
void func_001e65d0(void);
void func_001e6b70(s32 arg0);
void func_001e6ba8(void);
void func_001e6c68(void);
s32 func_001e6c90(void);
void func_001e6d20(void);
void func_001e6de0(void);
void func_001e6e08(s32 arg0);
s32 func_001e6e20(void);
s32 func_001e6eb0(void);
void func_001e6f28(void);
void func_001e7228(s32 a);
void func_001e7278(void);
void func_001e72a0(void);
s32 func_001e7488(VmRec *vm);
void func_001e74b0(s32 mode);
void func_001e7800(void);
void func_001e78d8(void);
void func_001e7928(void);
void func_001e7930(void);
s32 func_001e79a0(void);
void func_001e7a10(void);
void func_001e7a60(void);
void func_001e7a68(void);
s32 func_001e7ad8(void);
void func_001e7b48(void);
void func_001e7b50(void);
void func_001e7ba8(void);
void func_001e7d58(void);
void func_001e7d80(s32 arg0);
void func_001e7d90(void);
s32 func_001e7e00(void);

void func_001e4918(void) {
    s32 n[4];
    func_001c2d20((s8 *)&D_003E0D20, n, (s8 **)D_006310C8);
    func_001c2d20((s8 *)&D_003E0F40, n, (s8 **)D_00631148);
    func_001c2d20((s8 *)&D_003E1150, n, (s8 **)D_006311C8);
    func_001c2d20((s8 *)&D_003E12E0, n, (s8 **)D_00631248);
}

void func_001e4990(void) {
    D_003F7EC8 = 1;
    func_0010e3f0(D_00630380);
    func_0010ef70(D_00630380 - 0x80, D_006307C8, func_001e5198);
    if (D_003DD25C == 3) {
        ListCb *p = &D_006305C0;
        p->a = D_003DD25C;
        if (D_006305CC == 4 || D_006305CC == 0) p->n = 13;
        else p->n = 14;
    } else {
        D_006305C0.a = 4;
        D_006305C0.n = 13;
    }
    D_006305C0.fn = func_001e5788;
    func_0010f558(&D_006305C0, &D_00630300, D_006314C8);
}

s32 func_001e4a68(void) {
    if (D_002C5BB8 & 2) {
        if (D_003DD264 == 1) {
            func_0010bd90(&D_006303B0, func_001e4990);
            D_003DD264 = 0;
        } else {
            func_0010bd90(&D_00630300, 0);
            func_00232aa8();
            D_00389C90.f3078.x &= ~0x10;
            return 4;
        }
    }
    return 0;
}

void func_001e4b08(void) {
    s32 i;
    for (i = 0; i < 50; i++) {
        if (i < 9) {
            D_006305D0[i][0] = 15;
            D_006305D0[i][1] = 2;
            D_006305D0[i][2] = 1;
            D_006305D0[i][3] = i + 34;
            D_006305D0[i][4] = 1;
            D_006305D0[i][5] = 15;
            D_006305D0[i][6] = 3;
            D_006305D0[i][7] = 0;
        } else {
            D_006305D0[i][0] = 15;
            D_006305D0[i][1] = 2;
            D_006305D0[i][2] = (i + 1) / 10 + 33;
            D_006305D0[i][3] = (i + 1) % 10 + 33;
            D_006305D0[i][4] = 1;
            D_006305D0[i][5] = 15;
            D_006305D0[i][6] = 3;
            D_006305D0[i][7] = 0;
        }
    }
}

void func_001e4c20(void) {
    D_00630300.v30[0] = -110.0f;
    D_00630300.v30[1] = -5.0f;
    D_00630300.v40[0] = 10.0f;
    D_00630300.v40[1] = 14.0f;
    D_00630300.h4 = 6;
    D_00630300.hc = 1;
    D_00630300.he = 1;
    D_00630300.h6 = 0;
    D_00630300.h8 = 0;
    D_00630300.b90 = 0;
    D_00630300.f1c = 45.0f;
    D_00630300.x0 = -1;
    D_00630300.f94 = 1.0f;
    D_006303B0.v30[0] = 120.0f;
    D_006303B0.v30[1] = 100.0f;
    D_006303B0.v40[0] = 9.0f;
    D_006303B0.v40[1] = 5.0f;
    D_006303B0.h4 = 6;
    D_006303B0.hc = 1;
    D_006303B0.he = 1;
    D_006303B0.h6 = 0;
    D_006303B0.h8 = 0;
    D_006303B0.b90 = 0;
    D_006303B0.f1c = 45.0f;
    D_006303B0.x0 = -1;
    D_006303B0.f94 = 1.0f;
    D_003DC498.a = 28512;
    D_003DC498.b = 30176;
    D_003DC498.c = 0x8180;
    D_003DC498.d = 0x8c60;
}

void func_001e4d20(void) {
    D_003DD264 = 0;
    func_0010bd90(&D_006303B0, func_001e4990);
}

void func_001e4d50(void) {
    Save1 *s = func_00232cc0(1);
    func_001ea128(D_00630FC8, D_003DD248);
    func_001ea268(D_00630FC8, D_003DD270);
    switch (D_003DD25C) {
    case 0:
        if (s->l0[D_003DD258]) {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258]);
            func_001ea268(D_00630FC8, D_006310C8[s->l0[D_003DD258] - 1].a);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_006310C8[s->l0[D_003DD258] - 1].b);
        } else {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258]);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[1]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[2]);
        }
        break;
    case 1:
        if (s->l1[D_003DD258]) {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258]);
            func_001ea268(D_00630FC8, D_00631148[s->l1[D_003DD258] - 1].a);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_00631148[s->l1[D_003DD258] - 1].b);
        } else {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258]);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[1]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[2]);
        }
        break;
    case 2:
        if (s->l2[D_003DD258]) {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258]);
            func_001ea268(D_00630FC8, D_006311C8[s->l2[D_003DD258] - 1].a);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_006311C8[s->l2[D_003DD258] - 1].b);
        } else {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258]);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[1]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[2]);
        }
        break;
    case 3:
        if (!s->l3[D_003DD258 + D_006305CC * 10]) {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258 + D_006305CC * 10]);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[1]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[2]);
        } else {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258 + D_006305CC * 10]);
            func_001ea268(D_00630FC8, D_00631248[s->l3[D_003DD258 + D_006305CC * 10] - 1].a);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_00631248[s->l3[D_003DD258 + D_006305CC * 10] - 1].b);
        }
        break;
    }
    func_001ea268(D_00630FC8, D_003DD240);
    func_0010ef70(&D_006303B0, D_00630FC8, func_001e4d20);
}

void func_001e5198(void) {
    Save1 *s = func_00232cc0(1);
    s32 *m = &D_003DD25C;
    s32 i;

    if (*m == 3) {
        switch (D_003DD258) {
        case 10:
            if (D_006305CC == 4) D_006305CC = 3;
            else D_006305CC++;
            D_003DC498.n = 50;
            func_001ea128(D_006307C8, D_003DD1B0);
            func_001ea268(D_006307C8, D_003DD230);
            func_001ea268(D_006307C8, D_003DCB10[D_003DD25C]);
            func_001ea268(D_006307C8, D_003DD230);
            for (i = D_006305CC * 10; i < D_006305CC * 10 + 10; i++) {
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_006305D0[i]);
                if (!s->l3[i]) {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_00631248[s->l3[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
            }
            if (D_006305CC < 4) {
                func_001ea268(D_006307C8, D_003DD210);
                func_001ea268(D_006307C8, D_003DD230);
                func_001ea268(D_006307C8, D_003DD220);
                func_001ea268(D_006307C8, D_003DD230);
            } else {
                func_001ea268(D_006307C8, D_003DD220);
                func_001ea268(D_006307C8, D_003DD230);
                func_001ea268(D_006307C8, D_003DD230);
            }
            func_001ea268(D_006307C8, D_003DD1F0);
            func_001ea268(D_006307C8, D_003DD240);
            func_0010e3f0(D_00630380);
            func_0010ef70(D_00630380 - 0x80, D_006307C8, func_001e5198);
            {
                ListCb *p = &D_006305C0;
                p->a = 3;
                if (D_006305CC < 4) p->n = 14;
                else p->n = 13;
            }
            D_006305C0.fn = func_001e5788;
            func_0010f558(&D_006305C0, &D_00630300, D_006305C0.a);
            return;
        case 11:
            D_006305CC--;
            D_003DC498.n = 50;
            func_001ea128(D_006307C8, D_003DD1B0);
            func_001ea268(D_006307C8, D_003DD230);
            func_001ea268(D_006307C8, D_003DCB10[*m]);
            func_001ea268(D_006307C8, D_003DD230);
            for (i = D_006305CC * 10; i < D_006305CC * 10 + 10; i++) {
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_006305D0[i]);
                if (!s->l3[i]) {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_00631248[s->l3[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
            }
            func_001ea268(D_006307C8, D_003DD210);
            func_001ea268(D_006307C8, D_003DD230);
            if (D_006305CC > 0) func_001ea268(D_006307C8, D_003DD220);
            func_001ea268(D_006307C8, D_003DD230);
            func_001ea268(D_006307C8, D_003DD1F0);
            func_001ea268(D_006307C8, D_003DD240);
            func_0010e3f0(D_00630380);
            func_0010ef70(D_00630380 - 0x80, D_006307C8, func_001e5198);
            {
                ListCb *p = &D_006305C0;
                p->a = 3;
                if (D_006305CC > 0) p->n = 14;
                else p->n = 13;
            }
            D_006305C0.fn = func_001e5788;
            func_0010f558(&D_006305C0, &D_00630300, D_006305C0.a);
            break;
        }
    }
}

void func_001e5788(s32 a) {
    D_006314C8 = a;
    if (D_003DD25C == 3) {
        D_003DD258 = a - 3;
        if (a - 3 < 10) {
            func_0010bdd0(&D_006303B0, func_001e4d50);
            D_003DD264 = 1;
        }
    } else {
        D_003DD258 = a - 4;
        func_0010bdd0(&D_006303B0, func_001e4d50);
        D_003DD264 = 1;
    }
}

void func_001e5810(void) {
    func_0010ef70(&D_00630300, D_006307C8, func_001e5198);
    func_0011ef10(0xc350, func_001e4a68);
    if (D_003DD25C == 3) {
        ListCb *p = &D_006305C0;
        D_006305CC = 0;
        p->a = D_003DD25C;
        p->n = 13;
        p->fn = func_001e5788;
    } else {
        D_006305C0.n = 13;
        D_006305C0.fn = func_001e5788;
        D_006305C0.a = 4;
    }
    func_0010f558(&D_006305C0, &D_00630300, D_006305C0.a);
}

void func_001e58c0(s32 mode) {
    Save1 *s;
    s32 i;

    D_003DD25C = mode;
    D_003DD264 = 0;
    D_002C5958 |= 0xC;
    s = func_00232cc0(1);
    func_001e4b08();
    func_001ea128(D_003DC498.last, D_003DCB10[mode]);
    if (mode == 3) {
        D_003DC498.n = 50;
        func_001ea128(D_006307C8, D_003DD1B0);
        func_001ea268(D_006307C8, D_003DD230);
        func_001ea268(D_006307C8, D_003DCB10[3]);
        func_001ea268(D_006307C8, D_003DD230);
        for (i = 0; i < 10; i++) {
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_006305D0[i]);
            if (!s->l3[i]) {
                func_001ea268(D_006307C8, D_003DD250);
                func_001ea268(D_006307C8, D_003DCB90[0]);
                func_001ea268(D_006307C8, D_003DD230);
            } else {
                func_001ea268(D_006307C8, D_003DD250);
                func_001ea268(D_006307C8, D_00631248[s->l3[i] - 1].a);
                func_001ea268(D_006307C8, D_003DD230);
            }
        }
        func_001ea268(D_006307C8, D_003DD210);
        func_001ea268(D_006307C8, D_003DD230);
        func_001ea268(D_006307C8, D_003DD230);
        func_001ea268(D_006307C8, D_003DD1F0);
        func_001ea268(D_006307C8, D_003DD240);
        D_006314C8 = 3;
    } else {
        D_003DC498.n = 10;
        func_001ea128(D_006307C8, D_003DD1B0);
        func_001ea268(D_006307C8, D_003DD230);
        func_001ea268(D_006307C8, D_003DD1D8);
        func_001ea268(D_006307C8, D_003DD230);
        func_001ea268(D_006307C8, D_003DCB10[mode]);
        func_001ea268(D_006307C8, D_003DD230);
        for (i = 0; i < 10; i++) {
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_006305D0[i]);
            switch (mode) {
            case 0:
                if (!s->l0[i]) {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_006310C8[s->l0[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
                break;
            case 1:
                if (!s->l1[i]) {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_00631148[s->l1[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
                break;
            case 2:
                if (!s->l2[i]) {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_006311C8[s->l2[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
                break;
            }
        }
        func_001ea268(D_006307C8, D_003DD230);
        func_001ea268(D_006307C8, D_003DD1F0);
        func_001ea268(D_006307C8, D_003DD240);
        D_006314C8 = 4;
    }
    func_001e4c20();
    func_0010bdd0(&D_00630300, func_001e5810);
    D_00389C90.f3078.x |= 16;
}

s32 func_001e5d78(void) {
    u8 buf[16];
    s32 i;
    D_003DD264 = 0;
    D_002C5958 |= 0xC;
    func_001e4b08();
    for (i = 0; i < 10; i++) {
        if (D_00304BE8->cnt[i] < 9) {
            buf[0] = 1;
            buf[1] = 1;
            buf[2] = D_00304BE8->cnt[i] + 33;
            buf[3] = 1;
            buf[4] = 0;
        } else {
            buf[0] = (D_00304BE8->cnt[i] + 1) / 10 + 33;
            buf[1] = (D_00304BE8->cnt[i] + 1) % 10 + 33;
            buf[2] = 1;
            buf[3] = 0;
        }
        func_001ea268(D_006307C8, buf);
    }
    func_001e4c20();
    D_00630300.v30[0] = -60.0f;
    D_00630300.v30[1] = -30.0f;
    D_00630300.v40[0] = 10.0f;
    D_00630300.v40[1] = 11.0f;
    func_0010bdd0(&D_00630300, func_001e5810);
    return 2;
}

void func_001e5ee0(void) {
    D_00630460.v30[0] = -130.0f;
    D_00630460.v30[1] = -90.0f;
    D_00630460.v40[0] = 7.0f;
    D_00630460.v40[1] = 5.0f;
    D_00630460.h4 = 6;
    D_00630460.hc = 2;
    D_00630460.he = 2;
    D_00630460.h6 = 1;
    D_00630460.h8 = 13;
    D_00630460.b90 = 0;
    D_00630460.f1c = 135.0f;
    D_00630460.x0 = -1;
    D_00630460.f94 = 1.0f;
    D_00630510.v30[0] = 100.0f;
    D_00630510.v30[1] = -90.0f;
    D_00630510.v40[0] = 5.0f;
    D_00630510.v40[1] = 4.5f;
    D_00630510.h4 = 2;
    D_00630510.hc = 2;
    D_00630510.he = 2;
    D_00630510.h6 = 1;
    D_00630510.h8 = 13;
    D_00630510.b90 = 0;
    D_00630510.f1c = 200.0f;
    D_00630510.x0 = -1;
    D_00630510.f94 = 1.0f;
    D_00630300.v30[0] = 110.0f;
    D_00630300.v30[1] = 0.0f;
    D_00630300.v40[0] = 10.0f;
    D_00630300.v40[1] = 11.0f;
    D_00630300.h4 = 6;
    D_00630300.hc = 1;
    D_00630300.he = 1;
    D_00630300.h6 = 0;
    D_00630300.h8 = 13;
    D_00630300.b90 = 0;
    D_00630300.f1c = 200.0f;
    D_00630300.x0 = -1;
    D_00630300.f94 = 1.0f;
    D_003DC498.a = 0x7E60;
    D_003DC498.b = 0x7540;
    D_003DC498.c = 0x8FE0;
    D_003DC498.d = 0x8B20;
}

/* Plain globals (no pointer locals), `if (!D_003DD284) return 4;` first and the return 0 last. */
s32 func_001e6038(void) {
    Save1 *sv = func_00232cc0(1);
    if (D_003DD284 == 0) return 4;
    if (--D_003DD288 < 0) {
        D_003DD284 = 0;
        func_001ea128(D_00630FC8, D_003DD270);
        if (sv->l0[D_003DD258] == 0) {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258 + 1]);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
        } else {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258 + 1]);
            func_001ea268(D_00630FC8, D_006310C8[sv->l0[D_003DD258] - 1].a);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_006310C8[sv->l0[D_003DD258] - 1].b);
        }
        func_0010e3f0(D_006304E0);
        func_0010ef70(D_006304E0 - 0x80, D_00630FC8, 0);
        return 4;
    }
    return 0;
}

void func_001e61c0() {
    s32 ok = 0;
    Save1 *sv = func_00232cc0(1);
    switch (D_003DD258) {
    case 1:
        func_0010bd90(&D_00630460, 0);
        break;
    case 2:
        switch (D_003DD25C) {
        case 0:
            if (sv->ad0.open & 1) ok = 1;
            break;
        case 1:
            if (sv->ad0.open & 2) ok = 1;
            break;
        case 2:
            if (sv->ad0.open & 4) ok = 1;
            break;
        case 3:
            if (sv->ad0.open & 8) ok = 1;
            break;
        }
        if (ok == 1) {
            func_002329a0(&D_003DC498, func_001e6578, func_001e6580);
            func_0010bdd0(&D_00630300, func_001e6ba8);
            func_0010e3f0(D_006304E0);
            func_0010ef70(D_006304E0 - 0x80, D_003DCEF0, 0);
            D_003DD284 = ok;
            D_003DD288 = 60;
            func_0011ef10(0xC350, func_001e6038);
            D_003DD280 = 0;
            D_003DD27C = 0;
        } else {
            func_0010e3f0(D_006304E0);
            func_0010ef70(D_006304E0 - 0x80, D_00630FC8, 0);
            do { func_0010bdd0(&D_00630510, func_001e6e20); } while (0);
        }
        break;
    }
}

void func_001e6388(void) {
    func_001e61c0(0, &D_00630510);
}

s32 func_001e63a8(void) {
    if (!D_003DD28C) return 4;
    if (D_002C5BB8 & 2) {
        D_003DD28C = 0;
        D_003DD258 = 2;
        func_0010bd90(&D_00630510, func_001e6388);
        return 4;
    }
    return 0;
}

void func_001e6410(void) {
    func_0010bd90(&D_00630510, func_001e61c0);
}

void func_001e6438(s32 arg0) {
    D_003DD28C = 0;
    D_003DD258 = arg0;
}

s32 func_001e6450(void) {
    s32 r;
    func_0010ef70(&D_00630510, D_003DCEB0, func_001e6410);
    D_006305C0.fn = func_001e6438;
    D_006305C0.n = 2;
    D_006305C0.a = 1;
    func_0010f558(&D_006305C0, &D_00630510, 1);
    r = func_0011ef10(50000, func_001e63a8);
    D_003DD28C = 1;
    return r;
}

void func_001e64e0(void) {
    D_00389C90.f3078.x &= ~0x10;
}

s32 func_001e6500(void) {
    if (!D_003DD28C) return 4;
    if (D_002C5BB8 & 2) {
        func_0010bd90(&D_00630300, func_001e64e0);
        D_003DD28C = 0;
        D_003DD260 = -1;
        return 4;
    }
    return 0;
}

void func_001e6578(void) {
}

void func_001e6580(s32 a) {
    D_003DD28C = 0;
    D_003DD260 = a + D_006305C0.d * 10;
    func_0010bd90(&D_00630300, func_001e64e0);
}

void func_001e65d0(void) {
    Save1 *s = func_00232cc0(1);
    s32 i;

    if (D_003DD25C == 3) {
        s32 *q = &D_003DD260;
        switch (*q) {
        default:
            *q += D_006305CC * 10;
            func_0010bd90(&D_00630300, func_001e64e0);
            D_003DD28C = 0;
            return;
        case 10:
            if (D_006305CC == 4) D_006305CC = 3;
            else D_006305CC++;
            func_001ea128(D_006307C8, D_003DD248);
            for (i = D_006305CC * 10; i < D_006305CC * 10 + 10; i++) {
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_006305D0[i]);
                if (!s->l3[i]) {
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_00631248[s->l3[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
            }
            if (D_006305CC < 4) {
                func_001ea268(D_006307C8, D_003DD210);
                func_001ea268(D_006307C8, D_003DD230);
                func_001ea268(D_006307C8, D_003DD220);
                func_001ea268(D_006307C8, D_003DD230);
            } else {
                func_001ea268(D_006307C8, D_003DD220);
                func_001ea268(D_006307C8, D_003DD230);
                func_001ea268(D_006307C8, D_003DD230);
            }
            func_001ea268(D_006307C8, D_003DD240);
            func_0010e3f0(D_00630380);
            func_0010ef70(D_00630380 - 0x80, D_006307C8, func_001e65d0);
            if (D_006305CC < 4) {
                ListCb *p = &D_006305C0;
                p->a = 1;
                p->n = 12;
            } else {
                ListCb *p = &D_006305C0;
                p->a = 1;
                p->n = 11;
            }
            D_006305C0.fn = func_001e6b70;
            func_0010f558(&D_006305C0, &D_00630300, D_006305C0.a);
            return;
        case 11:
            D_003DC498.n = 50;
            D_006305CC--;
            func_001ea128(D_006307C8, D_003DD248);
            for (i = D_006305CC * 10; i < D_006305CC * 10 + 10; i++) {
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_006305D0[i]);
                if (!s->l3[i]) {
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_00631248[s->l3[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
            }
            func_001ea268(D_006307C8, D_003DD210);
            func_001ea268(D_006307C8, D_003DD230);
            if (D_006305CC > 0) func_001ea268(D_006307C8, D_003DD220);
            func_001ea268(D_006307C8, D_003DD240);
            func_0010e3f0(D_00630380);
            func_0010ef70(D_00630380 - 0x80, D_006307C8, func_001e65d0);
            if (D_006305CC > 0) {
                ListCb *p = &D_006305C0;
                p->a = 1;
                p->n = 12;
            } else {
                ListCb *p = &D_006305C0;
                p->a = 2;
                p->n = 11;
            }
            D_006305C0.fn = func_001e6b70;
            func_0010f558(&D_006305C0, &D_00630300, D_006305C0.a);
            return;
        }
    }
    func_0010bd90(&D_00630300, func_001e64e0);
    D_003DD28C = 0;
}

void func_001e6b70(s32 arg0) {
    if (D_003DD25C == 3) {
        D_003DD260 = arg0 - 1;
        return;
    }
    D_003DD260 = arg0 - 2;
}

void func_001e6ba8(void) {
    func_0011ef10(0xc350, func_001e6500);
    D_003DD28C = 1;
    func_0010ef70(&D_00630300, D_006307C8, func_001e65d0);
    if (D_003DD25C == 3) {
        ListCb *p = &D_006305C0;
        D_006305CC = 0;
        p->a = 2;
        p->n = 11;
        p->fn = func_001e6b70;
    } else {
        D_006305C0.n = 10;
        D_006305C0.fn = func_001e6b70;
        D_006305C0.a = 2;
    }
    func_0010f558(&D_006305C0, &D_00630300, D_006305C0.a);
}

void func_001e6c68(void) {
    func_0010bdd0(&D_00630510, func_001e72a0);
}

s32 func_001e6c90(void) {
    if (!D_003DD28C) return 4;
    if (D_002C5BB8 & 2) {
        func_0010e3f0(D_006304E0);
        func_0010ef70(D_006304E0 - 0x80, D_003DCD70, 0);
        func_0010bd90(&D_00630510, func_001e6c68);
        D_003DD28C = 0;
        return 4;
    }
    return 0;
}

void func_001e6d20(void) {
    s32 k = D_003DD258;
    switch (k) {
    case 1:
        func_0010e3f0(D_006304E0);
        func_0010ef70(D_006304E0 - 0x80, D_003DCF30, 0);
        func_0010bdd0(&D_00630510, func_001e6450);
        break;
    case 2:
        func_0010e3f0(D_006304E0);
        func_0010ef70(D_006304E0 - 0x80, D_003DCD70, 0);
        { MsgWin *q = &D_00630510; void (*fp)() = func_001e72a0; func_0010bdd0(q, fp); }
        break;
    }
}

void func_001e6de0(void) {
    func_0010bd90(&D_00630510, func_001e6d20);
}

void func_001e6e08(s32 arg0) {
    D_003DD28C = 0;
    D_003DD258 = arg0;
}

s32 func_001e6e20(void) {
    s32 r;
    func_0010ef70(&D_00630510, D_003DCEB0, func_001e6de0);
    D_006305C0.fn = func_001e6e08;
    D_006305C0.n = 2;
    D_006305C0.a = 1;
    func_0010f558(&D_006305C0, &D_00630510, 1);
    r = func_0011ef10(50000, func_001e6c90);
    D_003DD28C = 1;
    return r;
}

s32 func_001e6eb0(void) {
    if (!D_003DD28C) return 4;
    if (D_002C5BB8 & 2) {
        func_0010bd90(&D_00630510, 0);
        func_0010bd90(&D_00630460, 0);
        D_003DD28C = 0;
        return 4;
    }
    return 0;
}

void func_001e6f28(void) {
    Save1 *s = func_00232cc0(1);
    s32 i, j;
    switch (D_003DD25C) {
    case 0:
        if (s->ad0.open & 1) {
            D_003DC498.n = 9;
            func_001ea128(D_006307C8, D_006305D0[0]);
            func_001ea268(D_006307C8, D_003DCB90[0]);
            func_001ea128(D_003DC498.last, D_006307C8);
            for (i = 0; i < 9; i++) {
                func_001ea128(D_006307C8, D_006305D0[i + 1]);
                if (s->l0[i + 1] == 0) {
                    func_001ea268(D_006307C8, D_003DCB90[s->l0[i + 1]]);
                } else {
                    func_001ea268(D_006307C8, D_006310C8[s->l0[i + 1] - 1].a);
                }
                func_001ea128(D_003DC498.str[i], D_006307C8);
            }
            func_002329a0(&D_003DC498, func_001e6578, func_001e6580);
            func_0010bdd0(&D_00630300, func_001e6ba8);
            D_003DD280 = 0;
            D_003DD27C = 0;
        }
        break;
    case 1:
        if (!(s->ad0.open & 2)) {
            for (i = 1; i < 10; i++) {
                if (s->l1[i] == 0) {
                    func_001ea128(D_00630FC8, D_003DCDF0);
                    func_001ea268(D_00630FC8, D_003DD270);
                    func_001ea268(D_00630FC8, D_006305D0[i - 1]);
                    func_001ea268(D_00630FC8, D_003DCB90[s->l1[i - 1]]);
                    func_001ea268(D_00630FC8, D_003DD278);
                    for (j = 0; j < 3; j++) {
                        func_001ea268(D_00630FC8, D_003DD230);
                        func_001ea268(D_00630FC8, D_003DCD10[j]);
                        if (j < 2) {
                            func_001ea268(D_00630FC8, D_003DCE30);
                        } else {
                            func_001ea268(D_00630FC8, D_003DCE70);
                        }
                    }
                    func_0010e3f0(D_006304E0);
                    func_0010ef70(D_006304E0 - 128, D_00630FC8, 0);
                    func_0010bdd0(&D_00630510, func_001e6e20);
                    return;
                }
            }
        }
        break;
    case 2:
        j = 2;
        break;
    case 3:
        j = 3;
        break;
    case 4:
        j = 4;
        break;
    }
}

void func_001e7228(s32 a) {
    D_003DD28C = 0;
    D_003DD258 = a;
    if (D_003DD268 < a) func_0010bd90(&D_00630460, 0);
}

void func_001e7278(void) {
    func_0010bd90(&D_00630510, func_001e6f28);
}

void func_001e72a0(void) {
    Save1 *sv = func_00232cc0(1);
    s32 i;
    func_001ea128(D_006307C8, D_003DCB10[0]);
    func_001ea268(D_006307C8, D_003DD230);
    D_003DD268 = 1;
    if (sv->ad0.open & 1) {
        func_001ea268(D_006307C8, D_003DCB10[1]);
        func_001ea268(D_006307C8, D_003DD230);
        D_003DD268++;
    }
    if (sv->ad0.open & 2) {
        func_001ea268(D_006307C8, D_003DCB10[2]);
        func_001ea268(D_006307C8, D_003DD230);
        D_003DD268++;
    }
    if (sv->ad0.open & 4) {
        func_001ea268(D_006307C8, D_003DCB10[3]);
        func_001ea268(D_006307C8, D_003DD230);
        D_003DD268++;
    }
    i = 0;
    while (D_006307C8[i] != 0) {
        i += (u32)((u8)D_006307C8[i] - 9) < 23;
        i++;
    }
    D_006307C8[i] = 4;
    func_0010ef70(&D_00630510, D_006307C8, func_001e7278);
    D_006305C0.n = D_003DD268 + 1;
    D_006305C0.fn = func_001e7228;
    D_006305C0.a = 1;
    func_0010f558(&D_006305C0, &D_00630510, 1);
    func_0011ef10(0xC350, func_001e6eb0);
    D_003DD28C = 1;
}

s32 func_001e7488(VmRec *vm) {
    vm->stk[++vm->sp] = D_003DD260;
    return 2;
}

void func_001e74b0(s32 mode) {
    Save1 *s = func_00232cc0(1);
    s32 i;
    D_003DD25C = mode;
    D_003DD28C = 0;
    func_001e5ee0();
    func_001e4b08();
    D_003DD260 = -1;
    if (mode == 3) {
        func_001ea128(D_006307C8, D_003DD248);
        for (i = 0; i < 10; i++) {
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_006305D0[i]);
            if (!s->l3[i]) {
                func_001ea268(D_006307C8, D_003DCB90[0]);
                func_001ea268(D_006307C8, D_003DD230);
            } else {
                func_001ea268(D_006307C8, D_00631248[s->l3[i] - 1].a);
                func_001ea268(D_006307C8, D_003DD230);
            }
        }
        func_001ea268(D_006307C8, D_003DD210);
        func_001ea268(D_006307C8, D_003DD240);
    } else {
        func_001ea128(D_006307C8, D_003DD248);
        for (i = 0; i < 10; i++) {
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_006305D0[i]);
            switch (mode) {
            case 0:
                if (!s->l0[i]) {
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_006310C8[s->l0[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
                break;
            case 1:
                if (!s->l1[i]) {
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_00631148[s->l1[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
                break;
            case 2:
                if (!s->l2[i]) {
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_006311C8[s->l2[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
                break;
            }
        }
        func_001ea268(D_006307C8, D_003DD240);
    }
    func_0010bdd0(&D_00630300, func_001e6ba8);
    D_00389C90.f3078.x |= 16;
}

void func_001e7800(void) {
    D_00630460.v30[0] = 0.0f;
    D_00630460.v30[1] = 0.0f;
    D_00630460.v40[0] = 7.0f;
    D_00630460.v40[1] = 1.9f;
    D_00630460.h4 = 0;
    D_00630460.hc = 2;
    D_00630460.he = 2;
    D_00630460.h6 = 0;
    D_00630460.h8 = 13;
    D_00630460.b90 = 0;
    D_00630460.f1c = 135.0f;
    D_00630460.x0 = -1;
    D_00630460.f94 = 1.0f;
    D_00630300.v30[0] = 120.0f;
    D_00630300.v30[1] = -30.0f;
    D_00630300.v40[0] = 7.0f;
    D_00630300.v40[1] = 11.0f;
    D_00630300.h4 = 6;
    D_00630300.hc = 1;
    D_00630300.he = 3;
    D_00630300.h6 = 0;
    D_00630300.h8 = 0;
    D_00630300.b90 = 0;
    D_00630300.f1c = 45.0f;
    D_00630300.x0 = -1;
    D_00630300.f94 = 1.0f;
}

void func_001e78d8(void) {
    func_0010bd90(&D_00630460, 0);
    D_00389C90.f3070.x &= ~0x0020000000000000ULL;
}

void func_001e7928(void) {
}

void func_001e7930(void) {
    func_0010ef70(&D_00630460, D_003DCFF0, func_001e78d8);
    D_006305C0.a = 1;
    D_006305C0.n = 2;
    D_006305C0.fn = func_001e7928;
    func_0010f558(&D_006305C0, &D_00630460, 1);
}

s32 func_001e79a0(void) {
    D_002C5958 |= 0xc;
    func_001e7800();
    D_00630460.h4 = 1;
    func_0010bdd0(&D_00630460, func_001e7930);
    D_00389C90.f3070.x |= 0x20000000000000LL;
    return 6;
}

void func_001e7a10(void) {
    func_0010bd90(&D_00630460, 0);
    D_00389C90.f3070.x &= ~0x0020000000000000ULL;
}

void func_001e7a60(void) {
}

void func_001e7a68(void) {
    func_0010ef70(&D_00630460, D_003DD030, func_001e7a10);
    D_006305C0.a = 1;
    D_006305C0.n = 2;
    D_006305C0.fn = func_001e7a60;
    func_0010f558(&D_006305C0, &D_00630460, 1);
}

s32 func_001e7ad8(void) {
    D_002C5958 |= 0xc;
    func_001e7800();
    D_00630460.h4 = 1;
    func_0010bdd0(&D_00630460, func_001e7a68);
    D_00389C90.f3070.x |= 0x20000000000000LL;
    return 6;
}

void func_001e7b48(void) {
}

void func_001e7b50(void) {
    func_00232aa8();
    func_0010bd90(&D_00630300, 0);
    D_00389C90.f3070.x &= ~0x0020000000000000ULL;
}

void func_001e7ba8(void) {
    Save1 *sv = func_00232cc0(1);
    s32 i;
    switch (D_003DD258) {
    default: return;
    case 1:
        D_00389C90.f3070.x &= ~0x0020000000000000ULL;
        break;
    case 2:
        D_00389C90.f3070.x &= ~0x0020000000000000ULL;
        break;
    case 3:
        D_003DC498.n = 9;
        func_001ea128(D_006307C8, D_006305D0[0]);
        func_001ea268(D_006307C8, D_003DCB90[sv->l0[0]]);
        func_001ea128(D_003DC498.last, D_006307C8);
        for (i = 1; i < 10; i++) {
            func_001ea128(D_006307C8, D_006305D0[i]);
            func_001ea268(D_006307C8, D_003DCB90[sv->l0[i]]);
            func_001ea128(D_003DC498.str[i - 1], D_006307C8);
        }
        func_002329a0(&D_003DC498, func_001e7b48, func_001e7b50);
        func_0010bdd0(&D_00630300, 0);
        break;
        break;
    }
}

void func_001e7d58(void) {
    func_0010bd90(&D_00630460, func_001e7ba8);
}

void func_001e7d80(s32 arg0) {
    D_003DD258 = arg0;
}

void func_001e7d90(void) {
    func_0010ef70(&D_00630460, D_003DD070, func_001e7d58);
    D_006305C0.a = 1;
    D_006305C0.n = 3;
    D_006305C0.fn = func_001e7d80;
    func_0010f558(&D_006305C0, &D_00630460, 1);
}

s32 func_001e7e00(void) {
    D_002C5958 |= 0xc;
    func_001e7800();
    func_001e4b08();
    D_00630460.h4 = 1;
    func_0010bdd0(&D_00630460, func_001e7d90);
    D_00389C90.f3070.x |= 0x20000000000000LL;
    return 6;
}

