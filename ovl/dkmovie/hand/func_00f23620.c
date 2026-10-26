/* dkmovie.x func_00f23620: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x3DF51]; s8 flag; } MovieWork;
void func_00f22460(MovieWork *);
void func_00f235d8(MovieWork *);
void func_00f23620(MovieWork *arg0) {
    if (arg0->flag != 0) {
        func_00f22460(arg0);
        return;
    }
    func_00f235d8(arg0);
}
