#include "common.h"
#include "vm/script_vm.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0062.h"

/* Script VM handlers: value stack at +0x184, top index at +0x180. */
typedef struct { s32 flags; } Obj;
typedef struct {
    s32 x0;
    Obj *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    union { u64 x; s32 i[2]; } flags; /* 0x328 */
    f32 f330;
    u8 pad334[0xc];
    f32 f340;
    f32 f344;
    f32 f348;
} VM;


extern void (*D_00377368)(s32, s32);
extern void (*D_0037736C)(s32, s32);
extern void (*D_00377370)(s32, s32);
extern void (*D_00377378)(s32, s32);
extern void (*D_0037737C)(s32, s32);
extern void (*D_00377380)(s32, s32, s32, s32);
extern void (*D_00377384)(s32);
extern s32 (*D_00377388)(s32, s32, s32);
extern void (*D_0037738C)(s32, s32);
extern void (*D_0037739C)(s32, s32, s32, s32, s32);
extern void (*D_00377390)(s32, s32, s32, s32);
extern void (*D_00377394)(s32, s32, s32, s32);
extern void (*D_00377398)(s32, s32, s32, s32, s32);
extern void (*D_003773A0)(s32, s32, s32, s32, s32);
extern void (*D_003773A4)(s32);
extern void (*D_003773A8)(s32);
extern void (*D_003773AC)(s32);
extern void (*D_003773B0)(s32, s32);
extern void (*D_003773B4)(s32);
extern void (*D_003773B8)(s32);
extern void (*D_003773BC)(s32, s32, s32, s32, s32);
extern s32 (*D_003773C0)(s32, s32);
extern s32 (*D_003773C4)(void);
extern void (*D_003773CC)(s32, s32);
extern void (*D_003773D0)(s32);
extern void (*D_003773D4)(s32, s32);
extern void (*D_003773D8)(s32, s32, s32);
extern s32 (*D_003773C8)(s32, s32);
extern void (*D_00377374)(s32, s32, s32);
extern u64 D_0038CD00;
#include "data/pieces/D_0037A178.h"
extern s32 D_0062A220;
extern s32 D_0062A224;
extern s32 D_0062A628;
extern u8 D_0062A630[];
void func_0011efa8(void *, void *, s32, s32);
s32 func_0011ef10(s32, void (*)());
void func_001dd148();
typedef struct { f32 *f0; u8 pad4[0x10]; s32 f14; } HObj;
typedef struct { u8 pad0[0x15c]; s32 f15c; } HSub4;
typedef struct { u8 pad0[4]; HSub4 *f4; } HSub;
typedef struct { u8 pad0[0x10]; HObj *f10; HSub *f14; s32 f18; } Handler;
typedef struct { u8 pad0[0x30]; f32 v[3]; u8 pad3c[4]; } M64;
M64 *func_001623e0(s32);
void func_001318e8(HSub4 *, s32, void *);
void func_00147e08(HObj *, void *);
typedef struct { u8 pad0[0x3078]; u64 f3078; } Big19;
s32 func_001559f0(s32, s32);
typedef W606Mem_304be8 E116;
#include "data/pieces/D_00304BE8.h"


/* func_001dd170, func_001dd3f8 and func_001dd550 (and D_0062A640) are in src/event/effect.c. */



s32 func_001ddf98(VM *vm) {
    if ((s32)(D_0038CD00 >> 44) & 1) return 4;
    return 2;
}
#include "data/bss_0062_mixed.h"
#include "data/data_0038.h"
#include "data/data_003F.h"
#include "data/pieces/D_00377368.h"
#include "data/pieces/D_0037736C.h"
#include "data/pieces/D_00377370.h"
#include "data/pieces/D_00377374.h"
#include "data/pieces/D_00377378.h"
#include "data/pieces/D_0037737C.h"
#include "data/pieces/D_00377380.h"
#include "data/pieces/D_00377384.h"
#include "data/pieces/D_00377388.h"
#include "data/pieces/D_0037738C.h"
#include "data/pieces/D_00377390.h"
#include "data/pieces/D_00377394.h"
#include "data/pieces/D_00377398.h"
#include "data/pieces/D_0037739C.h"
#include "data/pieces/D_003773A0.h"
#include "data/pieces/D_003773A4.h"
#include "data/pieces/D_003773A8.h"
#include "data/pieces/D_003773AC.h"
#include "data/pieces/D_003773B0.h"
#include "data/pieces/D_003773B4.h"
#include "data/pieces/D_003773B8.h"
#include "data/pieces/D_003773BC.h"
#include "data/pieces/D_003773C0.h"
#include "data/pieces/D_003773C4.h"
#include "data/pieces/D_003773C8.h"
#include "data/pieces/D_003773CC.h"
#include "data/pieces/D_003773D0.h"
#include "data/pieces/D_003773D4.h"
#include "data/pieces/D_003773D8.h"
