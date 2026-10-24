#include "common.h"
#include "data/bss_004E.h"
extern s32 D_002C1390;
extern s32 D_004E3444;
extern void (*D_004E3434)(void);
CONTEXT_ONLY void func_0011e528(void) { D_002C1390 = 0; }
CONTEXT_ONLY void func_0011e610(void) { D_002C1390 = 1; }
extern s32 D_002C1368[];
extern s32 D_004E3438, D_004E343C, D_004E3440, D_004E3444, D_004E3448;
extern void (*D_004E3434)(void);
void func_001ed520(s32);
CONTEXT_ONLY void func_0011c7d8(s32 a) { func_001ed520(a); }
typedef struct { char c[13]; } Str13;
extern char D_0048D110[];
extern Str13 D_0048D118;
extern char D_0048D128[];
int sprintf(char *, const char *, ...);
char *strcat(char *, const char *);
CONTEXT_ONLY void func_0011ca68(s32 a0, char *a1) {
    char buf[80];
    sprintf(buf, D_0048D110, a0);
    if (buf[0] == ' ') {
        buf[0] = '0';
        if (buf[1] == ' ') buf[1] = '0';
    }
    *(Str13 *)a1 = D_0048D118;
    strcat(a1, buf);
    strcat(a1, D_0048D128);
}
extern s32 D_002C1368[];
#include "data/bss_004E_mixed.h"
#include "data/data_002C.h"
#include "data/pieces/D_002C1368.h"
