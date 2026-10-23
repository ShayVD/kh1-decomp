#include "common.h"
#include "vm/script_vm.h"
#include "data/types/vm_rec.h"
#include "data/bss_0062.h"

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
extern u8 D_00F20000[];
/* func_001e15a0, func_001e24c8 are in src/screen/screen.c. */

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

extern u8 D_00F20000[];

#include "data/bss_0062_mixed.h"
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003D.h"
#include "data/pieces/D_003DACC0.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_003F7A68.h"
#include "data/pieces/D_004906D0.h"
