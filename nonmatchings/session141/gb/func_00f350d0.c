/* 1 word / score 2. Everything matches except one delay slot. The original fills the k < 0 branch as bltz with 'lw v1,D_00F56DC0' in the slot; ours uses bltzl. Tried nested ifs, two continues, && (worse), and a 0..3 switch (same). Round 16 (wwm1): 10 min permuter (-j1), no gain. */
#include "ovl.h"

typedef struct { u16 a, b, c, flags, d, e; } GbEnt;
typedef struct {
    u8 pad0[4];
    u16 count;
    u16 w;
    u16 pad8;
    u16 h;
    u8 padc[0x70 - 0xC];
    GbEnt ents[1];
} GbHdr;
typedef struct {
    u8 pad0[0xA0];
    GbHdr hdr;
} GbMap;
extern GbMap *D_00F56DC0;
extern s32 D_00F56DE8;
void func_00f33d18(OvlMtx, s32);
void func_00f33da0(s32, s32);
s32 func_00f41678(s32, s32, OvlMtx, s32, s32);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0RotMatrixY(OvlMtx, OvlMtx, f32);
void sceVu0CopyVector(f32 *, f32 *);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);

void func_00f350d0(void) {
    OvlMtx m;
    OvlMtx w;
    OvlMtx rot;
    s32 mode;
    s32 i, n, k;
    mode = -1;
    for (i = 0; i < D_00F56DC0->hdr.count; i++) {
        k = D_00F56DC0->hdr.ents[i].c - 1;
        switch (k) {
        case 54:
            if (mode < 0)
                mode = 0;
            break;
        case 55:
            if (mode <= 0)
                mode = 1;
            break;
        }
    }
    if (mode < 0)
        return;
    sceVu0UnitMatrix(rot);
    sceVu0RotMatrixY(rot, rot, 3.1415926f);
    for (i = 0; i < D_00F56DC0->hdr.count; i++) {
        k = D_00F56DC0->hdr.ents[i].c - 1;
        if (k < 4) {
            if (k >= 0) {
                func_00f33d18(w, i);
                sceVu0UnitMatrix(m);
                sceVu0CopyVector(m[3], w[3]);
                if (mode != 0)
                    func_00f33da0(func_00f41678(27, 1, m, 0, D_00F56DE8), 8);
                sceVu0MulMatrix(m, m, rot);
                func_00f33da0(func_00f41678(27, 1, m, 0, D_00F56DE8), 8);
                return;
            }
        }
    }
}
