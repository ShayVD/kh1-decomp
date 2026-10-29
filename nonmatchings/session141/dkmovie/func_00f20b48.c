/* dkmovie.x func_00f20b48: draft (session 141, round 28), structurally complete, not polished, 1520 vs 1520 bytes, 12 words differ, score 18 (m2c output unusable (ldl/ldr block copies)). Stores a decoded picture (0x6400 bytes) and its second plane (0x2300 bytes) into one of the two picture buffers; when both are full it presents the older one (func_00f20aa8 / func_00f209d0) and reuses it. The copies are struct assignments (EE gcc expands them with the ldl/ldr vs ld alignment test); the 8-byte f3DF58 test reads both f3DF5D flags at once. */
#include "ovl.h"
#include "../nonmatchings/session141/dkmovie/movie_work.h"

typedef struct { u8 b[0x6400]; } PicBuf;
typedef struct { u8 b[0x2300]; } AuxBuf;
s32 func_001ed920(void);
void func_00f209d0(s32, s32, s32, s32, MovieWork *, s32);
void func_00f20aa8(MovieWork *);

s32 func_00f20b48(u8 *pic, u8 *aux, MovieWork *w) {
    s32 sync;
    s32 i;
    s32 a;

    if (w->f3DF59 != 0) {
        return 0;
    }
    func_00f20aa8(w);
    sync = w->f3DF34 & 1;
    if (w->f3DF34 >= 2) {
        sync = func_001ed920();
    }
    if (sync == -1) {
        if (w->f3DF5D[0] != 0 && w->f3DF5D[1] != 0) {
            w->f3DF63++;
        }
        i = w->f3DF38[0] > w->f3DF38[1];
        w->f3DF5D[i] = 1;
        *(PicBuf *)w->pic[i] = *(PicBuf *)pic;
        if (w->f3DF28 != 0 && aux != 0) {
            *(AuxBuf *)w->aux[i] = *(AuxBuf *)aux;
            w->f3DF5B[i] = 1;
        }
        w->f3DF38[i] = w->f3DF34;
        return 0;
    }
    a = 0;
    if (*(u64 *)&w->f3DF58 & ((u64)0xFFFF << 40)) {
        i = 0;
        if (w->f3DF38[0] == -1) {
            i = 1;
        } else if (w->f3DF38[1] < w->f3DF38[0]) {
            i = w->f3DF38[1] >= 0;
        }
        if (w->f3DF28 != 0 && aux != 0) {
            a = (s32)w->aux[i];
        }
        func_00f209d0((s32)w->pic[i], a, 0, w->f3DF38[i], w, sync);
        *(PicBuf *)w->pic[i] = *(PicBuf *)pic;
        if (w->f3DF28 != 0 && aux != 0) {
            *(AuxBuf *)w->aux[i] = *(AuxBuf *)aux;
            w->f3DF5B[i] = 1;
        }
        w->f3DF38[i] = w->f3DF34;
    } else {
        func_00f209d0((s32)pic, w->f3DF28 != 0 ? (s32)aux : 0, 0, w->f3DF34, w, sync);
    }
    return 1;
}
