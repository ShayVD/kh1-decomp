#include "common.h"
/* func_00233168: matched session 8 (w7), hand, rodata 0x491350: case 7 is a goto loop (k = q->n; goto t7; i7: k = q->n + 1; q->n = k; ...; t7: if (!q->flag[k]) goto i7;). */
typedef struct { s32 x0; s32 x4; u8 pad8[0x3C - 8]; } R60;
typedef struct R64 { u8 pad[0x2D]; u8 x2d; u8 x2e; u8 pad2f[0x40 - 0x2F]; } R64;
typedef struct {
    s32 x0;
    s32 x4;
    u8 pad8[0x38];
    R64 rec[65];
    u8 pad1080[0x10C0 - 0x1080];
    union { R64 *tbl[52][10]; R64 *tbl1[520]; };
    u8 pad[0x1900 - 0x10C0 - 52 * 40];
    s32 flag[99];
    s32 n;
    R60 r[99];
} St;
extern St D_00351E10;
extern s32 D_003F8370[];
extern s32 D_00425C18;
extern u32 D_00425C1C;
extern s32 D_00425C20;
extern s32 D_00425CAC;
void func_002365e0(void);
s32 func_00233d08(s32);
s32 func_00234018(s32, s32, s32);
s32 func_00234148(s32, s32, s32, s32, s32, s32);
s32 func_002345a0(s32, s32, s32, s32, s32, s32);
s32 func_00234860(void);
s32 func_002348d0(void);
s32 func_00234840(void);
s32 func_00233018(s32);

#define FAIL(K) D_003F8370[D_00351E10.x4] = K; D_00351E10.x0 = 11; goto end
/* rodata */
s32 func_00233168(void) {
    s32 i, r, k;
    R64 *p;
    St *q;
    func_002365e0();
    switch (D_00351E10.x0) {
    case 0:
        D_00351E10.x0 = 1;
        D_00351E10.x4 = 0;
        break;
    case 1:
        func_00234018(D_00351E10.x4, 0, 0);
        D_00351E10.x0 = 2;
        break;
    case 2:
        if (func_00233d08(0)) return 0;
        if (D_00425C18 != 2) {
            FAIL(4);
        }
        if (!D_00425C20) {
            FAIL(3);
        }
        D_00351E10.x0 = 3;
        break;
    case 3:
        func_00234148(D_00351E10.x4, 0, (s32)"BISLPS-25198-??", (s32)D_00351E10.rec, 99, 0);
        D_00351E10.x0 = 4;
        break;
    case 4:
        if (func_00233d08(0)) return 0;
        r = func_00234860();
        if (r == 4) {
            FAIL(r);
        }
        if (D_00425CAC == 0 && D_00425C1C < 132) {
            FAIL(2);
        }
        D_00351E10.x0 = 5;
        break;
    case 5:
        for (i = 0; i < 99; i++) D_00351E10.flag[i] = 0;
        p = D_00351E10.rec;
        for (i = 0; i < D_00425CAC; i++, p++) {
            D_00351E10.tbl[p->x2d][p->x2e - 1] = p;
        }
        D_00351E10.x0 = 6;
        break;
    case 6:
        D_00351E10.x0 = 7;
        D_00351E10.n = 0;
        break;
    case 7:
        q = &D_00351E10;
        k = q->n;
        goto t7;
    i7:
        k = q->n + 1;
        q->n = k;
        if (k >= 99) goto done;
    t7:
        if (!q->flag[k]) goto i7;
        D_00351E10.r[D_00351E10.n].x0 = 0;
        r = func_00233018(D_00351E10.n + 1);
        func_002345a0(D_00351E10.x4, 0, r, (s32)&D_00351E10.r[D_00351E10.n], 60, 0);
        D_00351E10.x0 = 8;
        break;
    case 8:
        if (func_00233d08(0)) return 0;
        if (func_002348d0() == 7) {
            FAIL(4);
        }
        q = &D_00351E10;
        if (++q->n >= 99) goto done;
        q->x0 = 7;
        break;
    case 9:
        func_00234018(D_00351E10.x4, 0, 0);
        D_00351E10.x0 = 10;
        break;
    case 10:
        if (func_00233d08(0)) return 0;
        if (func_00234840() == 1) {
            FAIL(4);
        }
        for (i = 0; i < 99; i++) {
            if (D_00351E10.flag[i] && D_00351E10.r[i].x0 == 0x5153484B && D_00351E10.r[i].x4 == 0x01317F14) {
                goto found;
            }
        }
        if (D_00425C1C < 132) D_003F8370[D_00351E10.x4] = 2;
        else D_003F8370[D_00351E10.x4] = 1;
        D_00351E10.x0 = 11;
        break;
    case 11:
        if (D_00351E10.x4 == 0) {
            D_00351E10.x4 = 1;
            D_00351E10.x0 = 1;
            break;
        }
        D_00351E10.x0 = 0;
        return 1;
    found:
        FAIL(0);
    done:
        q->x0 = 9;
    }
end:
    return 0;
}
