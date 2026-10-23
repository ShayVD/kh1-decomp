#include "common.h"
#include "vm/script_vm.h"
#include "data/types/vm_rec.h"
#include "data/bss_0062.h"
typedef VmRec VM;

typedef struct {
    u8 pad0[0x3034];
    s32 x3034;
    u8 pad3038[0x3070 - 0x3038];
    union { u64 x; struct { u64 b0:50; u64 b50:1; u64 b51:1; u64 b52:1; u64 r:11; } b; } x3070;
    union { u64 x; struct { u64 b0:3; u64 b3:1; u64 r:60; } b; } x3078;
    u8 pad3080[0x3150 - 0x3080];
    s32 x3150;
    VM *x3154;
} G389C90;
extern G389C90 D_00389C90;
extern f32 D_002BBDFC;
extern s32 D_003DC470;
extern s32 D_003DC474;
extern s32 D_003DC478;
extern s32 D_003DC47C;
extern s32 D_003DC494;
extern u8 D_003DC468[];
extern u8 D_0062F760[];
extern u8 D_0062FA00[];
extern u8 D_0062F6E0[];
extern s32 D_0062FF00[];
extern s32 D_0062FB00[];
void func_0010e3f0(void *);
void func_001ea128(void *, void *);
void func_001ea268(void *, s32);
void func_0010ef70(void *, void *, void (*)());
void func_001e2810(void);





#include "data/pieces/D_0037A178.h"

#include "data/pieces/D_0038D170.h"
#include "data/pieces/D_0039A580.h"
#include "data/pieces/D_0037A378.h"
/* func_001dcd98 and func_001dcea8 are in src/vm/vm_lib.c. */


/* func_001dd208, func_001dd320 and func_001dd488 are in src/event/effect.c. */



/* func_001de130, func_001de1e0, func_001de420, func_001de5b0, func_001de6a8, func_001de778, func_001de848, func_001de910, func_001de9e0, func_001deaf8, func_001dec10, func_001ded08, func_001df4a0, func_001df708, func_001dfcb0, func_001dfea8, func_001e0078 are in src/event/effect.c. */

















#include "data/types/text_001d0000_h44.h"
extern Col4 D_003DACC0;
extern s32 D_003DACD0;
extern u64 D_003DB028;
extern u8 D_00F20000[];
extern u8 D_003DB050[];
void func_001e1480(void);
void func_001e14e0(void);
void func_001e05a8(void *);
s32 func_001e15a0(void) {
    s32 i, j;
    u8 *p;
    D_003DACC0.d += D_003DACD0;
    if (D_003DACC0.d > 128) {
        D_003DACC0.d = 128;
    } else if (D_003DACC0.d < 0) {
        return 4;
    }
    {
        u64 r = (s64)D_003DACC0.a | 0x100000000LL;
        r |= (s64)D_003DACC0.c << 16 | (s64)D_003DACC0.b << 8;
        r |= (s64)D_003DACC0.d << 24;
        D_003DB028 = r;
    }
    func_001e1480();
    p = D_00F20000;
    for (i = 0; i < 384; i++) {
        for (j = 0; j < 512; j++) {
            p[2] = p[0] = p[1];
            p += 3;
        }
    }
    func_001e14e0();
    func_001e05a8(D_003DB050);
    return 0;
}

void func_001e2810(void) {
    s32 n = D_003DC470;
    if (n != D_003DC474 && n != 0) {
        {
            D_003DC474 = n;
            if (D_003DC478 == 0) {
                func_0010e3f0(D_0062F760);
                func_001ea128(D_0062FA00, D_003DC468);
                if (D_003DC494) {
                    func_001ea268(D_0062FA00, D_0062FF00[D_003DC470]);
                } else {
                    func_001ea268(D_0062FA00, D_0062FB00[D_003DC470]);
                }
                func_0010ef70(D_0062F6E0, D_0062FA00, func_001e2810);
            } else {
                D_003DC47C = 0;
            }
        }
    }
}

extern s32 D_003F7A68;
s32 func_001e2920(void) {
    if (D_003DC478 == 0) return 4;
    if (--D_003DC47C < 0) {
        D_003DC478 = 0;
        if (D_003F7A68 == 1 && D_003DC470 != 0) {
            func_0010e3f0(D_0062F760);
            func_001ea128(D_0062FA00, D_003DC468);
            if (D_003DC494) {
                func_001ea268(D_0062FA00, D_0062FF00[D_003DC470]);
            } else {
                func_001ea268(D_0062FA00, D_0062FB00[D_003DC470]);
            }
            func_0010ef70(D_0062F6E0, D_0062FA00, func_001e2810);
        }
        return 4;
    }
    return 0;
}

/* needs make: uses rodata */

#include "data/types/text_001d0000_h44_p.h"
extern Tbl55 D_004906D0;

extern char D_003DACD8[][6];
extern u8 D_00F20000[];
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
int sprintf(char *, const char *, ...);
s32 func_00120748(void *, void *, void (*)(), s32);
void func_001e2498();
s32 func_001e24c8(VM *vm) {
    char buf[256];
    char tmp[16];
    strcpy(buf, "image/");
    strcat(buf, D_003DACD8[vm->stk[vm->sp - 1]]);
    sprintf(tmp, "_%03d.rgb", vm->stk[vm->sp]);
    strcat(buf, tmp);
    func_00120748(buf, D_00F20000, func_001e2498, 0);
    D_00389C90.x3070.b.b50 = 1;
    vm->sp -= 2;
    return 2;
}

#include "data/bss_0062_mixed.h"
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003D.h"
#include "data/pieces/D_003DACC0.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_003F7A68.h"
#include "data/pieces/D_004906D0.h"
