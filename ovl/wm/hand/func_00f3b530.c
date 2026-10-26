/* wm.x func_00f3b530: matched by hand. */
#include "ovl.h"

#include "ovl.h"

typedef struct { u8 pad[0x90]; OvlVec rot; s32 flag; } A;
typedef struct { u8 pad[0x18]; s32 n; s32 rx; s32 ry; s32 rz; } B;
void func_001be9f0(f32 *);
void func_001bfac8(void);

void func_00f3b530(A *arg0, B *arg1) {
    OvlVec v;
    OvlVec tgt;
    OvlVec cur;
    s32 n, i;
    n = arg1->n;
    PlatVu0CopyVector(cur, arg0->rot);
    tgt[0] = arg1->rx * 0.017453291f;
    tgt[1] = arg1->ry * 0.017453291f;
    tgt[2] = arg1->rz * 0.017453291f;
    tgt[3] = 1.0f;
    if (n > 0) {
        for (i = 0; i < n && arg0->flag != 0; i++) {
            v[3] = 1.0f;
            v[0] = (tgt[0] - cur[0]) * i / n + cur[0];
            v[1] = (tgt[1] - cur[1]) * i / n + cur[1];
            v[2] = (tgt[2] - cur[2]) * i / n + cur[2];
            PlatVu0CopyVector(arg0->rot, v);
            func_001be9f0(arg0->rot);
            func_001bfac8();
        }
    }
    PlatVu0CopyVector(arg0->rot, tgt);
    func_001be9f0(arg0->rot);
}
