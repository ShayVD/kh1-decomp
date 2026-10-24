/* The pppRyjMngFlag class's frame and the pppRyjMegaBirthPrize class's Con
 * (docs/modules.md "Session 50"): pppRyjMngFlagFrame copies three of its
 * key's bytes into the system's flag bytes 0xB0-0xB2 at its key's frame;
 * pppRyjMegaBirthPrizeCon clears the prize table D_0035C710 (0x2000 bytes)
 * and sets the flags 0xB3 and 0xB0.  The prize draw is in
 * ryjmbprize.nostrict.c.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "ppp.h"
M2C_UNK func_00250054(M2C_UNK *, M2C_UNK, M2C_UNK);
extern void *D_00615E60;
#include "data/bss_0061_mixed.h"
#include "data/pieces/D_0035C710.h"

void pppRyjMngFlagFrame(void *arg0, void *arg1) {
    if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
        M2C_FIELD(D_00615E60, u8 *, 0xB2) = (u8) M2C_FIELD(arg1, u8 *, 4);
        M2C_FIELD(D_00615E60, u8 *, 0xB1) = (u8) M2C_FIELD(arg1, u8 *, 5);
        M2C_FIELD(D_00615E60, u8 *, 0xB0) = (u8) M2C_FIELD(arg1, u8 *, 6);
    }
}

void pppRyjMegaBirthPrizeCon(void) {
    func_00250054(((M2C_UNK *)&D_0035C710), 0, 0x2000);
    M2C_FIELD(D_00615E60, s8 *, 0xB3) = 1;
    M2C_FIELD(D_00615E60, s8 *, 0xB0) = 1;
}

