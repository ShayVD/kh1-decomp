#include "common.h"

#include "data/pieces/D_002A6308.h"
#include "data/pieces/D_002A6318.h"
#include "data/pieces/D_002A6324.h"
void func_00104908(void) {
    (*(s32 (*)[3])&D_002A6318)[0] = (*(s32 (*)[3])&D_002A6308)[0] = (*(s32 (*)[3])&D_002A6318)[1] = (*(s32 (*)[3])&D_002A6318)[2] = (*(s32 (*)[3])&D_002A6308)[1] = (*(s32 (*)[3])&D_002A6308)[2] = -1;
    D_002A6324 = 0;
}

#include "data/types/text_00100000_s6_na.h"
extern E4 D_002BCB80[];
extern s32 D_002BC128;
extern s32 D_002BC130;
void func_00111480(void);
void func_00111380(void);
void func_001113f8(s32);

void func_00111510(void) {
    s32 i;
    E4 *e;
    func_00111480();
    for (i = 0; i < 39; i++) {
        e = &D_002BCB80[i];
        if (D_002BC128 == e->a && D_002BC130 == e->b) {
            func_001113f8(e->c);
            return;
        }
    }
    func_00111380();
}

/* func_001cdc58 is in src/vm/vm_lib.c. */
#include "data/data_002B.h"
#include "data/pieces/D_002BC128.h"
#include "data/pieces/D_002BCB80.h"
