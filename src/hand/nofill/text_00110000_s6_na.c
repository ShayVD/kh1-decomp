#include "common.h"

#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C5968.h"
extern s32 D_002C5978;
void func_0011fa88(void);
void func_001209d8(char *);
void func_00120b10(void);
void func_00120ba0(void);
void func_00122028(void);
void func_001220e8(void);
void func_0024d4b0(void);
/* rodata */
void func_0011ecd8(void) {
    (*(s32 *)&D_002C5960) = 0;
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
