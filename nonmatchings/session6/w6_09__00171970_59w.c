/* 00171970: 59w off, nostrict. Off: t copied to a3 in orig (ok flag in a1); tail 'if (m & 6) return 0; return 1;' becomes sltiu store-flag in ours, orig uses beqzl/li v0,1 and a shared tail (L6C) for all 3 cases. u64 v/m makes it 248 bytes. */
#include "common.h"
typedef struct { u8 pad[0x70]; s32 w70; u8 pad74[0xF0]; s32 w164; } Act19;
typedef struct { u8 pad[0x4C]; s32 w4C; } Tgt19;

s32 func_00171970(Act19 *a, Tgt19 *t, u64 m) {
    s32 v;
    switch (a->w70) {
    case 0: {
        s32 n = a->w164, n2 = n, ok;
        ok = (n < 3 && n2 >= 0) ? 1 : (n == t->w4C);
        if (!ok) return 0;
        v = m & 6;
        break;
    }
    case 8: {
        s32 n = a->w164, n2 = n, ok;
        ok = (n < 124 && n2 >= 117) ? 1 : (n == t->w4C);
        if (!ok) return 0;
        v = m & 3;
        break;
    }
    case 24: {
        s32 n = a->w164, n2 = n;
        s32 ok = ((n2 >= 0 && n < 3) || (n < 131 && n2 >= 124)) ? 1 : (n == t->w4C);
        if (!ok) return 0;
        v = m & 5;
        break;
    }
    default:
        return 0;
    }
    if (v) return 0;
    return 1;
}
