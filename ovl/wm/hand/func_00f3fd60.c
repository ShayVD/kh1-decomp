/* wm.x func_00f3fd60: matched by hand. */
#include "ovl.h"

typedef struct { s32 cur; u8 pad[1420]; } P3fd60;
typedef struct { char name[16]; s32 kind; u8 pad[68]; } N3fd60;
extern P3fd60 D_00F86A58[];
extern N3fd60 D_00F87E88[];
extern s32 D_00F850BC;
extern s32 D_010807E0;
extern s32 D_00F87300;
extern char *D_00F87E60[];
extern char D_00FB7250[];
extern char D_00FB7240[];
void func_001bef40(char *, const char *, ...);
void func_00f3f8d0(s32, char *);
void func_00f3fb28(s32, char *);

void func_00f3fd60(s32 arg0, s32 arg1, s32 arg2) {
    char a[32];
    char b[32];
    s32 v;
    D_00F86A58[arg0].cur = arg1;
    if (arg2 == 0) {
        if (D_00F850BC != 0 && D_010807E0 == 0) {
            v = D_00F87300 - 1;
        } else {
            v = D_00F87E88[arg1].kind - 1;
        }
        func_001bef40(b, D_00FB7250, D_00F87E60[v]);
        func_00f3f8d0(arg0, b);
    } else {
        func_001bef40(a, D_00FB7240, D_00F87E88[arg1].name);
        func_00f3fb28(arg0, a);
    }
}
