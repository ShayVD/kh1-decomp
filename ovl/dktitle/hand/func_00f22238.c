/* dktitle.x func_00f22238: matched by hand. */
#include "ovl.h"

typedef struct { f32 v; s32 st; } Blink;
void func_00f201c8(u64, s32, s32, s32, s32, s32, s32);
void func_00f203a8(u64, s32, s32, s32, s32, s32, s32);
extern Blink D_00F2C848;
extern s32 D_00F2C700;
extern s32 D_00F2C70C, D_00F2C710, D_00F2C714;
extern s32 D_00F2C718, D_00F2C71C, D_00F2C720, D_00F2C724, D_00F2C728, D_00F2C72C, D_00F2C730;
extern f32 D_00F2C7A8, D_00F2C7B8, D_00F2C7C8, D_00F2C7D8, D_00F2C7E8, D_00F2C7F8;
extern f32 D_00F2C808, D_00F2C818, D_00F2C828, D_00F2C838;
extern s32 D_00F2C854, D_00F2C858, D_00F2C85C;
extern f32 D_00F2C860, D_00F2C870, D_00F2C880;
extern s32 D_002B6478;

void func_00f22238(void) {
    Blink *b = &D_00F2C848;
    switch (b->st) {
    case 0:
        b->v += 0.001f;
        if (0.23999998f <= b->v) { b->st = 1; b->v = 0.0f; }
        break;
    case 1:
        b->v += 2.1333334f;
        if (128.0f <= b->v) { b->v = 128.0f; b->st = 2; }
        break;
    case 2:
        b->v -= 2.1333334f;
        if (b->v <= 0.0f) { b->v = 0.0f; b->st = 3; }
        break;
    case 3:
        b->v += 0.001f;
        if (0.015f <= b->v) { b->st = 1; b->v = 0.0f; }
        break;
    }
    func_00f203a8(0x200F1D0665323764ULL, 68, (s32)D_00F2C7C8, 8, D_00F2C70C, 512, 32);
    func_00f201c8(0x200F1EA6654235E0ULL, 68, (s32)D_00F2C7B8, D_00F2C718 + 2, D_00F2C71C + 2, 512, 32);
    if (D_00F2C700 == 0) {
        func_00f201c8(0x200F1EA6654235E0ULL, 68, (s32)D_00F2C7A8, D_00F2C718, D_00F2C71C, 512, 32);
    }
    func_00f203a8(0x200F1D86653237E4ULL, 68, (s32)D_00F2C7F8, 8, D_00F2C710, 512, 32);
    func_00f201c8(0x200F1EC665423660ULL, 68, (s32)D_00F2C7E8, D_00F2C720 + 2, D_00F2C724 + 2, 512, 32);
    if (D_00F2C700 == 1) {
        func_00f201c8(0x200F1EC665423660ULL, 68, (s32)D_00F2C7D8, D_00F2C720, D_00F2C724, 512, 32);
    }
    func_00f203a8(0x200F3F466532397AULL, 68, (s32)D_00F2C880, 8, D_00F2C854, 512, 32);
    func_00f201c8(0x200F3FC6654238FAULL, 68, (s32)D_00F2C870, D_00F2C858 + 2, D_00F2C85C + 2, 512, 32);
    if (D_00F2C700 == 2) {
        func_00f201c8(0x200F3FC6654238FAULL, 68, (s32)D_00F2C860, D_00F2C858, D_00F2C85C, 512, 32);
    }
    if (D_002B6478) {
        func_00f203a8(0x200F1E0665323864ULL, 68, (s32)D_00F2C828, 8, D_00F2C714, 512, 32);
        func_00f201c8(0x200F1EE6654236E0ULL, 68, (s32)D_00F2C818, D_00F2C728 + 2, D_00F2C72C + 2, 512, 32);
        if (D_00F2C700 == 3) {
            func_00f201c8(0x200F1EE6654236E0ULL, 68, (s32)D_00F2C808, D_00F2C728, D_00F2C72C, 512, 32);
        }
    }
    func_00f203a8(0x200F1F0665407760ULL, 68, (s32)D_00F2C838, 6, D_00F2C730, 32, 32);
    func_00f203a8(0x200F1F2665407762ULL, 72, (s32)D_00F2C848.v, 6, D_00F2C730, 32, 32);
}
