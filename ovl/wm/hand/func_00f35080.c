/* wm.x func_00f35080: matched by hand. */
#include "ovl.h"

void func_00162070(s32, void *, void *, void *);
void func_001623d0(s32, void *);
void func_001c0310(s32, void (*)(void));
extern s32 D_00F87060;
extern s32 D_00F87064;
extern s32 D_00F8C228;
extern s32 D_00F8C22C;
extern s32 D_00F8C230;
extern s32 D_00F8C234;
extern s32 D_00F8C238;
extern s32 D_00FCD630;
extern s32 D_00FCD634;
extern s32 D_00FCD638;
void func_00f35188(void);

void func_00f35080(void) {
    func_00162070(D_00F87064, &D_00FCD630, &D_00FCD634, &D_00FCD638);
    func_001623d0(D_00F87060, &D_00FCD634);
    D_00F8C228 = 0;
    D_00F8C22C = 0;
    D_00F8C230 = 0;
    D_00F8C234 = 0;
    D_00F8C238 = 0;
    func_001c0310(1, func_00f35188);
}
