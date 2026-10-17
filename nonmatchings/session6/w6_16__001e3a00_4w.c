/* 4w off (all modes): li v0/v1 for compare const + addiu order before bne; else-branch jal slot move a0,s0 vs orig nop (dbr). strict hand. s32 func_0010bd90 helped (6->4) */
#include "common.h"
typedef struct { u8 pad[0x80]; u8 sub[0x30]; } WinX;
extern WinX D_0062F790;
extern u8 D_0062F810[];
extern u8 D_0062F840[];
extern s32 D_003DC484;
extern u8 D_003DC3C0[];
extern u8 D_003DC390[];
void func_001e39f0(void);
s32 func_0010bd90(void *, void (*)());
void func_00231b98(void *);
void func_0010e3f0(void *);
void func_0010ef70(void *, void *, void *);

void func_001e3a00(void) {
    u8 *s;
    s32 k;
    func_0010bd90(D_0062F840, func_001e39f0);
    k = D_003DC484;
    s = D_0062F790.sub;
    if (k == 1) {
        func_00231b98(s);
        func_0010e3f0(D_0062F810);
        func_0010ef70(D_0062F810 - 128, D_003DC3C0, 0);
    } else {
        func_0010e3f0(s);
        func_0010ef70(&D_0062F790, D_003DC390, 0);
    }
}
