#include "common.h"
#include "data/bss_0064.h"
#include "data/types/text_00200000_h47.h"
extern s32 D_003F3488[];
s32 func_001f31a8(s32, s32);
void func_001f3d58(s32, s32);
void func_001f3e20(s32, s32);
void func_001f3e90(s32, s32);

typedef struct { u8 pad[0x24]; s32 x24; s32 x28; } Obj7d8;
void func_0011d768(s32);
s32 func_001f42b8(void);
s32 func_001fe570(Obj7d8 *);
void func_0020bd18(Obj7d8 *, s32);
extern s32 D_00641C10[];
extern s32 D_00642410;
extern s32 D_00641C10[];
extern s32 D_00642410;
s32 func_001f31a8(s32, s32);
void func_001f3dc0(s32);
void func_001f3e20(s32, s32);
void func_001f3e90(s32, s32);
s32 func_001f42b8(void);
void func_00207830(s32, s32, s32, s32, s32, s32, s32);

#include "data/types/text_00200000_h47_p.h"

void func_0021b860(s32, s32, s32, s32, s32, s32);
void func_0021b860(s32, s32, s32, s32, s32, s32);

extern s32 D_003F3488[];
s32 func_001f31a8(s32, s32);
void func_001f3d58(s32, s32);
void func_001f3e48(s32, s32);
extern s32 D_003F5C50[];
extern s32 D_0064324C;
extern s32 D_0064324C;
extern s32 D_0064324C;
s32 func_001f31a8(s32, s32);
void func_001f3e48(s32, s32);
void func_0011d768(s32);
s32 func_001f31a8(s32, s32);
void func_001f3e48(s32, s32);
s32 func_001f42b8(void);
s32 func_001f31a8(s32, s32);
void func_001f3e48(s32, s32);
#include "vm/script_vm.h"

void func_0011d768(s32);
s32 func_001f42b8(void);
s32 func_001fe570(Obj7d8 *);
void func_0020bd18(Obj7d8 *, s32);
extern s32 D_006436D4;
void func_0011d768(s32);
s32 func_001f31a8(s32, s32);
void func_001f3e48(s32, s32);
void func_001f3d58(s32, s32);
void func_0020bda8();
extern s32 D_006436D4;

typedef struct { u8 pad[0xCC]; u16 cc; u16 ce; u16 d0; s16 d2; } O9088;
extern u8 D_003F6CE0[];
extern u8 D_003F6CA0[];
extern u16 D_00643730; /* src/data/bss_0064.c: s32 D_00643730 */
extern u16 D_006436D0; /* src/data/bss_0064.c: s32 D_006436D0 */
s32 func_001f31a8(s32, s32);
void func_001f3dc0(s32);
void func_001f3e48(s32, s32);
s32 func_001f42b8(void);
void func_00207830(s32, s32, s32, s32, s32, s32, s32);

void func_00229088(s32 a0) {
    s32 b[2];
    if (func_001f42b8() != 0) {
        b[0] = func_001f31a8((s32)D_003F6CE0, 6);
        if (b[0] != 0) {
            func_001f3e48(b[0], a0);
            ((O9088 *)b[0])->cc = ((O9088 *)b[0])->ce = D_00643730;
            ((O9088 *)b[0])->d2 = D_006436D0 * 16;
            b[1] = func_001f31a8((s32)D_003F6CA0, 6);
            if (b[1] != 0) {
                func_001f3e48(b[1], b[0]);
                func_001f3dc0(b[0]);
            }
        }
    }
    func_00207830(a0, 4, 2, 0, 0, 122, 112);
}

extern u8 D_003F6D68[];
void func_00205e30(s32, void *);
void func_00206130(s32, s32, s32, s32, s32, s32);
void func_0020ca30(s32, s32, s32, s32);
void func_001fc308(s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_0010fd18(void);
void func_001f9e48(s32, s32, s32, s32, s32, s32, s32);
void func_0020b3d8(s32, s32, s32);

void func_00229150(s32 a0) {
    func_00205e30(a0, D_003F6D68);
    func_00206130(a0, 0, 62, 512, 2, 0x8078C850);
    func_0020ca30(a0, 0, 0x80283212, 0x8050C846);
    func_001fc308(a0, 160, 35, 0, 19, 20, 0, 0x80399BFF, 0x80399BFF);
    func_001f9e48(a0, 0, 173, 35, func_0010fd18(), 19, 0x80399BFF);
    func_0020b3d8(a0, 401, 4);
}

extern s32 D_003F6E18[];
extern s32 D_003F3488[];
extern s32 D_003F3468[];
extern u8 D_003F6D40[];
s32 func_001f31a8(s32, s32);
void func_001f3d58(s32, s32);
void func_001f3e48(s32, s32);
void func_002293f0(s32);
void func_0020bb90(s32, s32);
void func_0020bd18(Obj7d8 *, s32);
void func_0020bda8();

s32 func_00229338(s32 a0) {
    s32 buf[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        buf[i] = func_001f31a8(D_003F6E18[i], 1);
        if (buf[i] != 0) {
            func_001f3e48(buf[i], a0);
            func_001f3d58(buf[i], D_003F3488[i]);
            a0 = buf[i];
        }
    }
    return a0;
}

void func_00229490(s32 a0) {
    s32 buf[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        buf[i] = func_001f31a8(D_003F6E18[i], D_003F3468[i]);
        if (buf[i] != 0) {
            func_001f3e48(buf[i], a0);
            func_001f3d58(buf[i], D_003F3488[i]);
            a0 = buf[i];
        }
    }
    buf[0] = func_001f31a8((s32)D_003F6D40, 4);
    if (buf[0] != 0) {
        func_001f3e48(buf[0], a0);
        func_002293f0(buf[0]);
    }
    func_0020bb90(133, 0);
    func_0020bd18((Obj7d8 *)buf[0], 8);
    func_0020bda8(16);
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_00491030[];
extern u8 D_00491048[];
extern u8 D_00491060[];
s32 D_003F5C50[0x4] ALIGNED(16) = {
    (s32)D_00491060, (s32)D_00491048, (s32)D_00491030, 0,
};
#include "data/data_003F.h"
#include "data/data_0049.h"
#include "data/pieces/D_003F6DF0.h"
#include "data/pieces/D_003F3488.h"
