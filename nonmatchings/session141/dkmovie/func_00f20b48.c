/* Round 60 (wwm2): score 14 -> 4. The two-buffer path returns 1 itself, so its f3DF38[i] = f3DF34 store no longer shares a tail with the plain-call path, and its registers match (the load goes to a0, the address to v1). Left: in the plain func_00f209d0 call the target sets a0 = pic before loading a3 = f3DF34 (a scheduling tie). No else, `a` as a variable, and both ternary forms make no difference or are worse. Earlier header below. */
/* dkmovie.x func_00f20b48: draft (session 141, round 28; round 29 wgb): 1520 vs 1520 bytes, 10 words differ, score 14 (was 12/18). Round 29: `i = w->f3DF38[0] > w->f3DF38[1]` and, in the else branch, `i = w->f3DF38[1] < w->f3DF38[0] && w->f3DF38[1] >= 0` (the && value form gives the slti/sltiu pair). Left: register allocation only. At the join store w->f3DF38[i] = w->f3DF34 the target loads into a0 and forms the address in v1 (ours v1/v0), and in the else-branch call the target moves a0 from s3 before loading a3 = f3DF34. Tried (&w->f3DF30)[i + 2] forms (worse), a temp pointer, ternary/temp forms of the aux argument, !(x < 0), u32/s8 i, a 10-minute -j1 permuter run (no gain); callee prototypes checked (func_001ed920 s32, func_00f20aa8 and func_00f209d0 void). m2c output is unusable (ldl/ldr block copies). Stores a decoded picture (0x6400 bytes) and its second plane (0x2300 bytes) into one of the two picture buffers; when both are full it presents the older one (func_00f20aa8 / func_00f209d0) and reuses it. The copies are struct assignments (EE gcc expands them with the ldl/ldr vs ld alignment test); the 8-byte f3DF58 test reads both f3DF5D flags at once. */
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
        } else {
            i = w->f3DF38[1] < w->f3DF38[0] && w->f3DF38[1] >= 0;
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
        return 1;
    } else {
        func_00f209d0((s32)pic, w->f3DF28 != 0 ? (s32)aux : 0, 0, w->f3DF34, w, sync);
    }
    return 1;
}
