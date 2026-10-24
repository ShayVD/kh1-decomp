/* The start up and the frame loop: func_0011ecd8 the boot (the pads, the
 * disc, the scratchpad stack, the game phases), func_0011edc8 one frame (the
 * frame callbacks of src/util/proc.c, the object updates, the draw),
 * func_0011eeb0 the frame's end (1 / the frame time into D_002C5970,
 * func_0011f130 over the main list, the double buffer flip D_002C5950). Flag
 * mode: nofill (the other modes are in the sibling files). Read from the
 * code, not proved by a boot (docs/modules.md "Session 54"). */
#include "common.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C5968.h"

/* func_0011ecd8 (from hand/nofill/text_00110000_s6_na.c). */
extern s32 D_002C5978;
void func_0011fa88(void);
void func_001209d8(char *);
void func_00120b10(void);
void func_00120ba0(void);
void func_00122028(void);
void func_001220e8(void);
void func_0024d4b0(void);
void func_0011ecd8(void) {
    (*(u32 *)&D_002C5960) = 0;
    D_002C5968 = 0;
    func_00120b10();
    func_001209d8("sio2man.irx");
    func_001209d8("sio2d.irx");
    func_001209d8("dbcman.irx");
    { s32 i; for (i = 0; i < 2; i++) func_001209d8("ds2o.irx"); }
    func_0011fa88();
    func_001209d8("mcman.irx");
    func_001209d8("mcserv.irx");
    func_001209d8("libsd.irx");
    func_001209d8("libssl.irx");
    func_0024d4b0();
    func_00120ba0();
    func_00122028();
    func_001220e8();
    D_002C5978 = 0;
}

