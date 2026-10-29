/* dkmovie.x func_00f270c8: draft (session 141, round 28), structurally complete, not polished, 1176 vs 1184 bytes, 217 words differ, score 148 (m2c draft scored 307). Player reset: installs the work area, sets the picture size when one is given, clears the player state and the three stream slots, and places the slot buffers after the work area (0x3DF80, 0x162780, 0x286F80). Round 19 (wwm1): 217 -> 126 raw words with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). Round 19 (wwm1): score 134 -> 96 with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). Round 21 (wwm1): score 96 -> 76 with the dependency-checked reorderer (w3.py, from wwm2 r35 hill3). Round 22 (wwm1): 76 -> 52 with w3.py seed 3. Then the if as `func_00219380() == 0` first (bnezl like the original), without the CONTEXT_ONLY stub: score 38. Then 38 -> 30 with w3.py seed 5. */
#include "../nonmatchings/session141/dkmovie/movie_work.h"

s32 func_00219380(void);

void func_00f270c8(MovieWork *w, s32 width, s32 height, s32 limit) {
    s32 i;

    D_00F28460 = w;
    if (width != 0 || height != 0) {
        w->f3DD18 = width / 16;
        w->f3DD1C = height / 16;
        w->f3DD20 = width;
        w->f3DD24 = height;
        w->f3DF4C = 0;
    }
    D_00F28460->f3DD28 = 0;
    D_00F28460->f3DD38 = 0;
    D_00F28460->f3DD2C = 0;
    D_00F28460->f3DD30 = 0;
    D_00F28460->f3DD34 = 0;
    D_00F28460->f3DD3C = 0;
    D_00F28460->f3DF1C = 0xFFFF;
    D_00F28460->f3DF67 = 0;
    D_00F28460->f3DD40 = 0;
    D_00F28460->f3DEE8 = 0x7F;
    D_00F28460->f3DD44 = 0;
    D_00F28460->f3DEDC = 0;
    D_00F28460->f3DEE0 = 0;
    D_00F28460->f3DEE4 = -1;
    D_00F28460->f3DDB0 = 0;
    D_00F28460->f3DDB4 = 0;
    D_00F28460->f3DDB8 = 0;
    D_00F28460->f3DDBC = 0;
    D_00F28460->f3DDD0 = 2;
    D_00F28460->f3DED4 = 0;
    D_00F28460->f3DED8 = 0;
    D_00F28460->f3DEEC = 0;
    D_00F28460->f3DD48 = -1;
    D_00F28460->f3DF54 = 0;
    D_00F28460->f3DEF0 = 0;
    D_00F28460->f3DF55 = 0;
    D_00F28460->f3DF56 = 0;
    D_00F28460->f3DF58 = 0;
    D_00F28460->f3DF28 = 0;
    if (func_00219380() == 0) {
        D_00F28460->f3DF5A = 0;
    } else {
        D_00F28460->f3DF5A = 1;
    }
    D_00F28460->f3DF30 = 0;
    D_00F28460->f3DF20 = 0;
    D_00F28460->f3DF24 = 0;
    D_00F28460->f3DF5D[0] = 0;
    D_00F28460->f3DF5D[1] = 0;
    D_00F28460->f3DF5B[0] = 0;
    D_00F28460->f3DF5B[1] = 0;
    D_00F28460->f3DF59 = 0;
    D_00F28460->f3DF34 = 0;
    D_00F28460->f3DF38[0] = -1;
    D_00F28460->f3DF38[1] = -1;
    D_00F28460->f3DF40 = -1;
    D_00F28460->f3DF62 = 0;
    D_00F28460->f3DF44 = 2;
    D_00F28460->f3DF63 = 0;
    D_00F28460->f3DF64 = 0;
    D_00F28460->f3DF65 = 0;
    D_00F28460->f3DF66 = 0;
    D_00F28460->f3DD4C = 0;
    D_00F28460->f3DF60 = 0;
    D_00F28460->f3DF61 = 0;
    D_00F28460->f3DF48 = limit;
    D_00F28460->f3DF50 = 3;
    for (i = 0; i < 3; i++) {
        D_00F28460->f3DD74[i] = 0;
        D_00F28460->f3DD68[i] = 0;
        D_00F28460->f3DD50[i] = 0;
    }
    D_00F28460->f3DF08 = ((s32)D_00F28460 + 0x3AB87F) & ~0xFF;
    D_00F28460->f3DD5C[0] = (s32)D_00F28460 + 0x3DF80;
    D_00F28460->f3DF10 = 0x124800;
    D_00F28460->f3DD5C[2] = (s32)D_00F28460 + 0x286F80;
    D_00F28460->f3DD5C[1] = (s32)D_00F28460 + 0x162780;
    D_00F28460->f3DF0C = 0x123800;
}
