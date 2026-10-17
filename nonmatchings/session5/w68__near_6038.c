#include "common.h"
#include "/tmp/claude-0/s/w68/hdr4.h"
s32 func_001e6038(void) {
    SvA80 *sv = func_00232cc0(1); s32 *p = &D_003DD284; s32 *q = &D_003DD288; s32 r = 4;
    if (*p != 0) {
        if (--*q < 0) {
            *p = 0;
            func_001ea128(D_00630FC8, D_003DD270);
            if (sv->a80[D_003DD258] == 0) {
                func_001ea268(D_00630FC8, D_006305DA[D_003DD258]);
                func_001ea268(D_00630FC8, D_003DCB90);
            } else {
                func_001ea268(D_00630FC8, D_006305DA[D_003DD258]);
                func_001ea268(D_00630FC8, D_006310C8[sv->a80[D_003DD258] - 1].a);
                func_001ea268(D_00630FC8, D_003DD230);
                func_001ea268(D_00630FC8, D_003DD278);
                func_001ea268(D_00630FC8, D_006310C8[sv->a80[D_003DD258] - 1].b);
            }
            func_0010e3f0(D_006304E0);
            func_0010ef70(D_006304E0 - 0x80, D_00630FC8, 0);
            return 4;
        } else {
            return 0;
        }
    }
    return r;
}
