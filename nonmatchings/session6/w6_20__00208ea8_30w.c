/* func_00208ea8 near miss, 30 words, mode hand. Off: loop-tail register choice (slt v0/v1 vs dx/dy reload), outer loop top x=x0 reload / nop placement. Same C fits func_00209030 (30w, callee func_001f94f0) and func_002091b8 (49w, callee func_001f9e48; there rows+1 is computed before func_001f8e18). Probing CONTEXT_ONLY callees: no effect. */
#include "common.h"
typedef struct {
    u8 pad0[0xbe];
    s16 be;
    s16 c0;
    s16 c2;
    s16 c4;
    s16 c6;
    u8 padc8[0xcc - 0xc8];
    s16 cc;
    s16 ce;
    u8 padd0[0xd8 - 0xd0];
    s16 d8;
} Win;
void func_001f8e18(void *);
void func_001f8f30(void);
s32 func_001fd518(void *);
s32 func_001fd538(void *);
s32 func_001fd590(void *);
s32 func_001fd618(void *);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_00208ea8(Win *o, s32 a1, s32 *strs, s32 k, s32 c0, s32 c1) {
    s32 x0 = o->be >> 4;
    s32 dx = o->c2 >> 4;
    s32 dy = o->c4 >> 4;
    s32 sr = func_001fd518(o);
    s32 sc = func_001fd538(o);
    s32 idx = func_001fd618(o);
    s32 y = func_001fd590(o);
    s32 cnt = o->cc;
    s32 rows = o->ce;
    s32 cols = o->d8;
    s32 r, c, x;
    func_001f8e18(o);
    for (r = 0; r < rows + 1; r++) {
        x = x0;
        for (c = 0; c < cols; c++) {
            if (idx >= cnt) goto done;
            { s32 col = (r == sr && c == sc) ? c1 : c0; func_001f9438(o, 0, x, y, strs[idx], k, col); }
            idx++;
            x += dx;
        }
        y += dy;
    }
done:
    func_001f8f30();
}
