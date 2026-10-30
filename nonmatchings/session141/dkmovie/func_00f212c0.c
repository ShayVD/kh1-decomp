/* Round 58 (wwm2): score 93 -> 89 (300 vs 304 bytes): c1 is read before c0, as the target loads 4(c) first. Left: the target copies the coefficient pointer (move v1,v0) and reads c0 through the copy, which costs the missing word; tried a[k].c0 / a[k].c1 forms (312 bytes), a struct copy, an s32 * and a second pointer. Earlier header below. */
/* dkmovie.x func_00f212c0: near miss (session 141), 51 words: ADPCM block decoder (16 blocks of 8 bytes, 2 samples a byte); the coefficient pair is read through a copied pointer in the original and the loop registers differ. */
#include "ovl.h"
typedef struct { s32 c0, c1; } AdpcmCoef;
extern AdpcmCoef D_00F283A0[];
void func_00f212c0(u8 *src, s16 *dst, s32 *hist) {
    s32 i, j;
    s32 s1 = hist[0];
    s32 s2 = hist[1];
    for (i = 0; i < 16; i++) {
        u8 h = *src++;
        s32 shift = h & 0xF;
        AdpcmCoef *c = &D_00F283A0[(s8)h >> 4];
        s32 c1 = c->c1;
        s32 c0 = c->c0;
        for (j = 0; j < 8; j++) {
            s8 b = *src++;
            s32 n;
            n = (b & 0xF) << 12;
            if (n & 0x8000) n |= 0xFFFF0000;
            n = (n >> shift) + (s1 * c0 + s2 * c1) / 64;
            s2 = s1;
            s1 = n;
            *dst++ = n;
            n = (b & 0xF0) << 8;
            if (n & 0x8000) n |= 0xFFFF0000;
            n = (n >> shift) + (s1 * c0 + s2 * c1) / 64;
            s2 = s1;
            s1 = n;
            *dst++ = n;
        }
    }
    hist[0] = s1;
    hist[1] = s2;
}
