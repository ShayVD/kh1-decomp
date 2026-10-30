/* dkmovie.x func_00f25180: matched by hand. */
#include "ovl.h"

/* dkmovie.x func_00f25180: matched (session 141, round 58, wwm2). func_00f279f8 takes the height * 16 as a second argument, which puts it in a1 as the target has it. */
#include "ovl.h"
typedef struct { u8 pad[8]; u8 b8; u8 pad9[2]; u8 bB; u8 bC; } MvHdr;
typedef struct {
    u8 pad[0x3DD18];
    s32 f3DD18;
    s32 f3DD1C;
    s32 f3DD20;
    s32 f3DD24;
    u8 pad3DD28[0x68];
    MvHdr *f3DD90;
    u8 pad3DD94[0x158];
    s32 f3DEEC;
} MovieWork;
extern MovieWork *D_00F28460;
extern u8 *D_00F28464;
void func_00f279f8(s32, s32);
void func_00f26b60(void);
void func_0024e640(void *, s32, void *, s32);
void func_00f25658(void);
void func_00f25978(void);
void func_00f25180(void) {
    MvHdr *h = D_00F28460->f3DD90;
    s32 w = h->bB;
    s32 ht;
    D_00F28460->f3DD18 = w;
    w *= 16;
    ht = h->bC;
    D_00F28460->f3DD20 = w;
    D_00F28460->f3DD1C = ht;
    D_00F28460->f3DD24 = ht * 16;
    func_00f279f8(w, ht * 16);
    func_00f26b60();
    *(volatile u32 *)0x10002010 = 0x40000000;
    if (D_00F28460->f3DD90->b8 == 0) {
        func_0024e640(D_00F28464 + 0x10F0, 0x1000, func_00f25658, 0);
    } else {
        func_0024e640(D_00F28464 + 0x10F0, 0x1000, func_00f25978, 0);
    }
    D_00F28460->f3DEEC = 1;
}
