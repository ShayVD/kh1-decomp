/* xl_limit.x func_00f22d40: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xC]; void *fC; } Res;
typedef struct { s32 f0; s32 f4; s32 f8; s32 pad[5]; } Ent;
void func_00f20130(void *);
void func_0014f830(s32, s32, void *, void *, void *, s32, void *, s32, s32);
void func_0014f658(u8 *, s32);
void func_00130340(u8 *, s32, f32);
Res *func_00130578(u8 *, s32, f32);
s32 func_00148968(u8 *, s32, s32);
void func_0011ef10(s32, void *);
void func_00f22510(void);
void func_00f22540(void);
void func_00f22d10(void);
void func_0014f828(void);
void func_00f22578(void);
s32 func_00f22ba0(u16 *);
extern u8 *D_002E26A0;
extern s32 D_00F23208;
extern u8 D_00F23270[];
extern f32 D_00F23280[];
extern Ent D_00F23290[];
extern f32 D_00F23EB0[];
extern u8 *D_00F23F90;
void func_00f22d40(void) {
    s32 i;
    func_00f20130(D_00F23270);
    func_0014f830(0x29, 0, func_00f22510, func_00f22540, func_00f22d10, 0, func_0014f828, 0, 0);
    D_00F23F90 = D_002E26A0;
    func_0014f658(D_00F23F90, 0x29);
    func_00130340(D_00F23F90, 0x010000FA, 0.0f);
    func_00130578(D_00F23F90, 0x40000000, 0.0f)->fC = func_00f22578;
    PlatVu0AddVector(D_00F23EB0, D_00F23F90 + 0x10, D_00F23280);
    func_00148968(D_00F23F90, D_00F23208, 15);
    {
        Ent *e = D_00F23290;
        for (i = 5; i >= 0; i--) {
            e[i].f8 = 0;
        }
    }
    func_0011ef10(0xCF08, func_00f22ba0);
}
