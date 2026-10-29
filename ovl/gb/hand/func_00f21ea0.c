/* gb.x func_00f21ea0: matched by hand. */
#include "ovl.h"

/* gb.x func_00f21ea0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x76]; s16 mode; } GbState;
extern GbState *D_00F56DC0;
extern s32 D_00F56DC4;
extern s32 D_00F56D8C;
extern s32 D_00F56D98;
extern s32 D_00F56EC0;
extern s32 D_00F56EC4;
extern s32 D_00F74200;
extern s32 D_00F74268;
extern s32 D_00F7426C;
void func_00106780(s32);
s32 func_001ba9d8(s32);
void func_001bab80(s32, s32);
void func_001bb428(s32);
void func_001be1e8(s32, s32);
void func_001bfac8(void);
s32 func_001c01b0(s32, void *, s32);
void func_00f20a68(void);
void func_00f21778(s32, s32);
void func_00f21bd8(void);
void func_00f21c38(void);
void func_00f21ce0(void);
void func_00f21e78(void);
s32 func_00f24240(s32, s32);
void func_00f24780(s32);
void func_00f262e0(void);
void func_00f27300(s32);
void func_00f29400(s32);
void func_00f2ac20(void);
void func_00f31ea0(s32);
void func_00f32728(s32, s32);
void func_00f35a80(void);
void func_00f39350(s32);

void func_00f21ea0(void) {
    s32 i;
    D_00F7426C = 0;
    for (;;) {
        switch (D_00F56DC0->mode) {
        case 2:
            func_00f35a80();
            break;
        case 1:
            func_00f2ac20();
            break;
        case 0:
            func_00f31ea0(0);
            break;
        case 3:
            D_00F74268 = 0;
            for (i = 0; i < 60; i++)
                func_001bfac8();
            func_00f21c38();
            func_00106780(30);
            if (D_00F56EC4 != 0) {
                func_001c01b0(12, func_00f262e0, D_00F56EC4 - 1);
                D_00F56EC4 = 0;
            }
            func_001bfac8();
            func_001bfac8();
            func_001bb428(0);
            func_00f39350(D_00F7426C);
            func_001bb428(1);
            while (D_00F74200 != 0)
                func_001bfac8();
            if (D_00F56EC0 != 0) {
                func_001bab80(10, func_001ba9d8(0));
                func_001be1e8(0, 0);
                func_00f20a68();
            }
            func_00f24780(D_00F56DC4);
            func_00f24240(D_00F56DC4, 0);
            func_00f27300(0);
            D_00F56DC0->mode = 0;
            func_00f32728(7, 0);
            func_00f32728(5, 0);
            func_00f21778(0, 0);
            D_00F56D8C = 1;
            D_00F56D98 = 0;
            func_00f29400(1);
            func_00f21bd8();
            func_00106780(30);
            if (D_00F56EC0 == 0) {
                func_00f21e78();
                func_00f21ce0();
            }
            D_00F7426C = 1;
            break;
        }
    }
}
