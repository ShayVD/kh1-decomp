/* xl_limit.x func_00f21d90: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xC]; void *fC; } Res;
void func_00f20130(void *);
void func_0014f830(s32, s32, void *, void *, void *, s32, void *, s32, s32);
void func_0014f658(void *, s32);
void func_00130340(void *, s32, f32);
Res *func_00130578(void *, s32, f32);
s32 func_00148968(void *, s32, s32);
void func_00f219d8(void);
void func_00f21a20(void);
void func_00f21a68(void);
void func_0014f828(void);
void func_00f21b10(void);
extern void *D_002E26A0;
extern s32 D_00F23208;
extern u8 D_00F23260[];
extern s32 D_00F23E14;
void func_00f21d90(void) {
    void *p;
    func_00f20130(D_00F23260);
    p = D_002E26A0;
    func_0014f830(0x27, 4, func_00f219d8, func_00f21a20, func_00f21a68, 0, func_0014f828, 0, 0);
    func_0014f658(p, 0x27);
    func_00130340(p, 0x010000E6, 0.0f);
    func_00130578(p, 0xE7, 0.0f)->fC = func_00f21b10;
    func_00148968(p, D_00F23208, 0);
    D_00F23E14 = 0;
}
