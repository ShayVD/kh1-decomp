#include "common.h"

/* func_00171970 (session 7, w6): `ok` shared by cases 0 and 8 at function
 * scope (gets a1, so t moves to a3), its own `ok2` in case 24; the n2 copy
 * keeps the two slti range tests; each case ends `if (m & K) return 0;`
 * so jump2 cross-jumps the tail. Matches in strict mode too. */
typedef struct { u8 pad[0x70]; s32 w70; u8 pad74[0xF0]; s32 w164; } Act19;
typedef struct { u8 pad[0x4C]; s32 w4C; } Tgt19;

s32 func_00171970(Act19 *a, Tgt19 *t, s32 m) {
    s32 ok, n, n2;
    switch (a->w70) {
    case 0:
        n = a->w164; n2 = n;
        if (n < 3 && n2 >= 0) ok = 1; else ok = (n == t->w4C);
        if (!ok) return 0;
        if (m & 6) return 0;
        break;
    case 8:
        n = a->w164; n2 = n;
        if (n < 124 && n2 >= 117) ok = 1; else ok = (n == t->w4C);
        if (!ok) return 0;
        if (m & 3) return 0;
        break;
    case 24: {
        s32 ok2;
        n = a->w164; n2 = n;
        if (n2 >= 0 && (n < 3 || (n < 131 && n2 >= 124))) ok2 = 1; else ok2 = (n == t->w4C);
        if (!ok2) return 0;
        if (m & 5) return 0;
        break;
    }
    default:
        return 0;
    }
    return 1;
}
