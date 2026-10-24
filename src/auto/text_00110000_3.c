/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_00102a48(M2C_UNK, M2C_UNK);
M2C_UNK func_00111340(s32, M2C_UNK);
M2C_UNK func_0013c078();
M2C_UNK func_00267328(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK func_002675b8(M2C_UNK *, M2C_UNK *);
#include "data/pieces/D_002BBE20.h"
#include "data/pieces/D_002BBE60.h"
#include "data/pieces/D_002BBEA0.h"
#include "data/pieces/D_002BBEE0.h"
#include "data/pieces/D_002BBF20.h"
#include "data/pieces/D_002BBF60.h"
#include "data/pieces/D_002BBFA0.h"
#include "data/pieces/D_002BBFE0.h"
#include "data/pieces/D_002BC020.h"
#include "data/pieces/D_002E2700.h"
extern M2C_UNK D_004D8E40; /* src/data/bss_004D.c: Mtx52 D_004D8E40 */
extern M2C_UNK D_004D8E80; /* src/data/bss_004D.c: Mtx52 D_004D8E80 */
extern M2C_UNK D_004D9100; /* src/data/bss_004D.c: Mtx52 D_004D9100 */
extern M2C_UNK D_004D9140; /* src/data/bss_004D.c: Mtx52 D_004D9140 */
extern M2C_UNK D_004D9180; /* src/data/bss_004D.c: Mtx52 D_004D9180 */
extern M2C_UNK D_004D91C0; /* src/data/bss_004D.c: Mtx52 D_004D91C0 */
M2C_UNK D_004D9200[0x10] ALIGNED(64);
extern M2C_UNK func_00113ee0;
#include "data/pieces/D_002BCB60.h"
extern s32 D_002BCC24;
#include "data/pieces/D_002BCDA0.h"
extern s32 D_002BCDD8;
extern s32 D_002BCDDC;
#include "data/pieces/D_002E26A0.h"
extern s32 D_004D9330; /* src/data/bss_004D.c: u32 D_004D9330 */
void *func_0011ef10(M2C_UNK, M2C_UNK *);

void func_00110ba8(void) {
    func_002675b8(&D_004D9200, (M2C_UNK *)&D_002BBFA0);
    func_00267328((M2C_UNK *)&D_002BBFA0, ((M2C_UNK *)&D_002BBE60), ((M2C_UNK *)&D_002E2700));
    func_00267328((M2C_UNK *)&D_002BBFE0, ((M2C_UNK *)&D_002BBEE0), ((M2C_UNK *)&D_002E2700));
    func_00267328((M2C_UNK *)&D_002BC020, ((M2C_UNK *)&D_002BBF20), ((M2C_UNK *)&D_002E2700));
}

void func_00110c30(void) {
    func_002675b8(((M2C_UNK *)&D_002BBE20), &D_004D8E40);
    func_002675b8(((M2C_UNK *)&D_002BBE60), &D_004D9100);
    func_002675b8(((M2C_UNK *)&D_002BBEA0), &D_004D9140);
    func_002675b8(((M2C_UNK *)&D_002BBEE0), &D_004D9180);
    func_002675b8(((M2C_UNK *)&D_002BBF20), &D_004D91C0);
    func_002675b8((M2C_UNK *)&D_002BBF60, &D_004D8E80);
    func_00267328((M2C_UNK *)&D_002BBFA0, ((M2C_UNK *)&D_002BBE60), ((M2C_UNK *)&D_002E2700));
}

void func_001113f8(s32 arg0) {
    f32 temp_f0;
    s32 var_a0;
    void *var_v0;
    void *var_v1;

    if ((*(s32 *)&D_002E26A0) != 0) {
        func_00111340((*(s32 *)&D_002E26A0), 0);
    }
    var_a0 = 1;
    var_v1 = ((s32)D_002BCB60) + 0x2C;
    var_v0 = (arg0 << 6) + ((s32)D_002BCDA0) + 0x2C;
    do {
        var_a0 -= 1;
        M2C_FIELD(var_v1, f32 *, -0xC) = (f32) M2C_FIELD(var_v0, f32 *, -0xC);
        M2C_FIELD(var_v1, f32 *, -8) = (f32) M2C_FIELD(var_v0, f32 *, -8);
        M2C_FIELD(var_v1, f32 *, -4) = (f32) M2C_FIELD(var_v0, f32 *, -4);
        temp_f0 = M2C_FIELD(var_v0, f32 *, 0);
        var_v0 += 0x10;
        M2C_FIELD(var_v1, f32 *, 0) = temp_f0;
        var_v1 += 0x10;
    } while (var_a0 >= 0);
}

void func_00111590(s32 arg0, void *arg1) {
    s32 temp_a0;

    temp_a0 = arg0 * 0x10;
    M2C_FIELD(arg1, f32 *, 0) = (f32) M2C_FIELD((temp_a0 + ((s32)D_002BCB60)), f32 *, 0x10);
    M2C_FIELD(arg1, f32 *, 4) = (f32) M2C_FIELD((temp_a0 + ((s32)D_002BCB60)), f32 *, 0x14);
    M2C_FIELD(arg1, f32 *, 8) = (f32) M2C_FIELD((temp_a0 + ((s32)D_002BCB60)), f32 *, 0x18);
    M2C_FIELD(arg1, f32 *, 0xC) = (f32) M2C_FIELD((temp_a0 + ((s32)D_002BCB60)), f32 *, 0x1C);
}

void func_00111ca8(void) {
    D_002BCC24 = 0;
}

void func_00112260(void) {

}

void func_00112268(void) {

}

void func_00113518(void) {
    if (D_002BCDD8 != 0) {
        if (D_002BCDDC == 0) {
            func_0013c078();
        }
    }
}

s32 func_00113f18(void) {
    M2C_FIELD(func_0011ef10(0x2903, &func_00113ee0), s16 *, 2) = 1;
    func_00102a48(0x80, 0x10);
    D_004D9330 = 3;
    return 4;
}
#include "data/data_002B.h"
#include "data/pieces/D_002BCC24.h"
