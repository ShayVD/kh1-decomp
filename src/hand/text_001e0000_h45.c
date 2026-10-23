#include "common.h"
#include "vm/script_vm.h"
#include "vm/vm_find.h"
#include "data/bss_0062.h"
#include "data/bss_0063.h"

/* Menu window (0xb0 bytes); D_0062F6E0/D_0062F790/D_0062F840 and
 * D_00630300/D_006303B0/D_00630460 are runs of these. */
#include "data/types/text_001e0000_h45.h"

#include "data/types/text_001e0000_h45_p.h"
typedef struct { f32 x, y, z; } Vec3;

/* Message passed to func_001c4640. */

extern E212 D_003DB078[];
extern E212 D_003DB718[];
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_003DABD4.h"
extern s32 D_003DD258;
extern s32 D_003DD28C;
extern s32 D_003F7A68;
#include "data/pieces/D_003DBA68.h"
#include "data/pieces/D_003DC390.h"
#include "data/pieces/D_003DCD70.h"


/* func_001e31b8, func_001e3600, func_001e3770, func_001e38b0, func_001e3b40, func_001e3c70, func_001e3dd0, func_001e3f20, func_001e4790, func_001e4868 are in src/shop/shop.c. */


/* func_001e4990, func_001e4b08, func_001e4c20, func_001e5810, func_001e6ba8, func_001e6d20, func_001e7800 are in src/list/list.c. */


/* func_001e7f08, func_001e8238, func_001e8560, func_001e8800, func_001e88e0, func_001e8a50, func_001e8bd8, func_001e8f68 are in src/event/sound.c. */


/* func_001e9310 is in src/screen/wave.c. */

void func_001e9fe8(Vec3 *out, Vec3 *in) {
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
    while (1) {
        if (out->x > 3.1415928f) out->x -= 6.2831855f;
        else if (out->x < -3.1415928f) out->x += 6.2831855f;
        else break;
    }
    while (1) {
        if (out->y > 3.1415928f) out->y -= 6.2831855f;
        else if (out->y < -3.1415928f) out->y += 6.2831855f;
        else break;
    }
    while (1) {
        if (out->z > 3.1415928f) out->z -= 6.2831855f;
        else if (out->z < -3.1415928f) out->z += 6.2831855f;
        else break;
    }
}

/* func_001ea498, func_001ea6b8, func_001ea760, func_001ea908, func_001ea9c8, func_001eaa88, func_001eab78 are in src/vm/vm_ent.c. */


/* func_001eb698 is in src/save/flags.c. */

#include "data/bss_0063_typed.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_003D.h"
#include "data/data_003F.h"
#include "data/data_0049.h"
#include "data/pieces/D_003DD258.h"
#include "data/pieces/D_003DD28C.h"
#include "data/pieces/D_003F7A68.h"
#include "data/pieces/D_003DB078.h"
#include "data/pieces/D_003DB718.h"
