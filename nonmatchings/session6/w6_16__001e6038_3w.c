/* 3w off (all modes except nogcse worse): %hi(D_003DD288) gets a0 (ours) vs v0 after move s2,v0 (orig). strict hand. header reconstructed from session-5 draft */
#include "common.h"
typedef struct { u8 pad[0xa80]; u8 a80[16]; } SvA80;
typedef struct { char *a; char *b; } StrPair;
extern s32 D_003DD284;
extern s32 D_003DD288;
extern s32 D_003DD258;
extern char D_00630FC8[];
extern char D_003DD270[];
extern char D_003DCB90[];
extern char D_003DD230[];
extern char D_003DD278[];
extern char D_006305DA[][10];
extern StrPair D_006310C8[];
extern u8 D_006304E0[];
SvA80 *func_00232cc0(s32);
void func_001ea128(char *, char *);
void func_001ea268(char *, char *);
void func_0010e3f0(void *);
void func_0010ef70(void *, void *, void *);

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
