#include "common.h"
#include "text/textwin.h"
void func_001f8e18(void *);
void func_001f8f30(void);
s32 func_001fd518(void *);
s32 func_001fd538(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
void func_00207830(TextWin *, s32, s32, s32, s32, s32, s32);
void func_00207870(TextWin *, s32, s32, s32, s32, s32, s32);
void func_002078b0(TextWin *, s32, s32, s32, s32, s32, s32);
void func_002078f0(TextWin *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00207938(TextWin *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00207980(TextWin *, s32, s32, s32, s32, s32, s32, s32, s32);

void func_00209340(TextWin *o, s32 a1, s32 *strs) {
    s32 x0 = o->xbe >> 4;
    s32 dx = o->xc2 >> 4;
    s32 dy = o->xc4 >> 4;
    s32 sr = func_001fd518(o);
    s32 sc = func_001fd538(o);
    s32 idx = func_001fd618(o);
    s32 y = func_001fd590(o);
    s32 rows = o->xce;
    s32 w = dx - (o->xc6 >> 4);
    s32 cnt = o->xcc;
    s32 cols = o->xd8;
    s32 r, c, x;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            func_00207830(o, r == sr && c == sc, a1, x, y, w, strs[idx]);
            idx++;
            x += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

void func_002094e0(TextWin *o, s32 a1, s32 *strs) {
    s32 x0 = o->xbe >> 4;
    s32 dx = o->xc2 >> 4;
    s32 dy = o->xc4 >> 4;
    s32 sr = func_001fd518(o);
    s32 sc = func_001fd538(o);
    s32 idx = func_001fd618(o);
    s32 y = func_001fd590(o);
    s32 rows = o->xce;
    s32 w = dx - (o->xc6 >> 4);
    s32 cnt = o->xcc;
    s32 cols = o->xd8;
    s32 r, c, x;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            func_00207870(o, r == sr && c == sc, a1, x, y, w, strs[idx]);
            idx++;
            x += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

void func_00209680(TextWin *o, s32 a1, s32 *strs) {
    s32 x0 = o->xbe >> 4;
    s32 dx = o->xc2 >> 4;
    s32 dy = o->xc4 >> 4;
    s32 sr = func_001fd518(o);
    s32 sc = func_001fd538(o);
    s32 idx = func_001fd618(o);
    s32 y = func_001fd590(o);
    s32 rows = o->xce;
    s32 w = dx - (o->xc6 >> 4);
    s32 cnt = o->xcc;
    s32 cols = o->xd8;
    s32 r, c, x;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            func_002078b0(o, r == sr && c == sc, a1, x, y, w, strs[idx]);
            idx++;
            x += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

void func_00209820(TextWin *o, s32 a1, s32 a2, s32 a3, s32 *strs) {
    s32 x0 = o->xbe >> 4;
    s32 dx = o->xc2 >> 4;
    s32 dy = o->xc4 >> 4;
    s32 sr = func_001fd518(o);
    s32 sc = func_001fd538(o);
    s32 idx = func_001fd618(o);
    s32 y = func_001fd590(o);
    s32 rows = o->xce;
    s32 w = dx - (o->xc6 >> 4);
    s32 cnt = o->xcc;
    s32 cols = o->xd8;
    s32 r, c, x;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            func_002078f0(o, r == sr && c == sc, a1, a2, x, y, w, a3, strs[idx]);
            idx++;
            x += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

void func_002099d8(TextWin *o, s32 a1, s32 a2, s32 a3, s32 *strs) {
    s32 x0, dx, dy, sr, sc, idx, y, rows, w, r, cnt, cols, c, x;
    x0 = o->xbe >> 4;
    dx = o->xc2 >> 4;
    dy = o->xc4 >> 4;
    sr = func_001fd518(o);
    sc = func_001fd538(o);
    idx = func_001fd618(o);
    y = func_001fd590(o);
    rows = o->xce;
    w = dx - (o->xc6 >> 4);
    cnt = o->xcc;
    cols = o->xd8;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            func_00207938(o, r == sr && c == sc, a1, a2, x, y, w, a3, strs[idx]);
            idx++;
            x += dx;
            a3 += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

void func_00209b90(TextWin *o, s32 a1, s32 a2, s32 a3, s32 *strs) {
    s32 x0, dx, dy, sr, sc, idx, y, rows, w, r, cnt, cols, c, x;
    x0 = o->xbe >> 4;
    dx = o->xc2 >> 4;
    dy = o->xc4 >> 4;
    sr = func_001fd518(o);
    sc = func_001fd538(o);
    idx = func_001fd618(o);
    y = func_001fd590(o);
    rows = o->xce;
    w = dx - (o->xc6 >> 4);
    cnt = o->xcc;
    cols = o->xd8;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            func_00207980(o, r == sr && c == sc, a1, a2, x, y, w, a3, strs[idx]);
            idx++;
            x += dx;
            a3 += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}

/* needs make: uses rodata */
