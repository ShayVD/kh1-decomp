#include "common.h"
#include "data/pieces/D_003E8E08.h"

/* rodata: jump table at 0x490960 */
s32 func_001effc0(u8 *s) {
    s32 n = 0;
    u8 **tbl = ((u8 **)&D_003E8E08);
    for (;;) {
        if (*s < 21) {
            switch (*s) {
            case 1:
                n++;
                s++;
                break;
            case 4:
                s++;
                break;
            case 5:
                s++;
                break;
            case 6:
                s++;
                break;
            case 9:
                s++;
                break;
            case 10:
                if (tbl[0]) n += func_001effc0(tbl[0]);
                tbl++;
                s++;
                break;
            case 11:
                tbl++;
                s += 4;
                break;
            case 8:
                s += 5;
                break;
            case 7:
                s += 2;
                break;
            case 12:
                s += 2;
                break;
            case 15:
                s += 2;
                break;
            case 13:
                s += 3;
                break;
            case 14:
                s += 3;
                break;
            case 17:
                s += 3;
                break;
            case 18:
                s += 3;
                break;
            case 19:
                s += 3;
                break;
            case 20:
                s += 3;
                break;
            case 0: case 2: case 3: case 16:
                return n;
            default:
                s++;
                break;
            }
        } else {
            if (*s == 24) s += 2;
            else s = (*s < 32) ? s + 2 : s + 1;
            n++;
        }
    }
}
