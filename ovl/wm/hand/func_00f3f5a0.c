/* wm.x func_00f3f5a0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u8 b4; u8 pad5[27]; u16 h20; } P3f5a0;
typedef struct { u16 h0; u16 h2; u16 h4; u16 h6; } Q3f5a0;
extern char *D_00F9B1E8[];
extern char D_00FB71D0[];
extern char D_00FB71D8[];
extern char D_00FB71F0[];
extern s32 D_00F8703C;
extern s32 D_00F87040;
s32 func_00f62b90(s32);
P3f5a0 *func_00f62b98(s32, s32);
Q3f5a0 *func_00f62c78(s32, s32);
void func_001bef40(char *, const char *, ...);
s32 func_001bb7c8(char *, s32);
void func_001763f0(s32);

void func_00f3f5a0(s32 arg0) {
    char buf[64];
    char name[32];
    s32 i;
    s32 n;
    s32 t;
    P3f5a0 *p;
    Q3f5a0 *q;
    n = func_00f62b90(arg0);
    for (i = 0; i < n; i++) {
        p = func_00f62b98(i, arg0);
        t = p->b4;
        if (t == 2) {
            q = func_00f62c78(p->h20, arg0);
            if (q->h2 == t && D_00F9B1E8[q->h6] != NULL) {
                s32 *pm = &D_00F8703C;
                func_001bef40(name, D_00F9B1E8[q->h6], D_00FB71D0);
                func_001bef40(buf, D_00FB71D8, name);
                func_001bb7c8(buf, *pm);
                func_001763f0(*pm);
                func_001bef40(name, D_00F9B1E8[q->h6], D_00FB71F0);
                func_001bef40(buf, D_00FB71D8, name);
                func_001bb7c8(buf, D_00F87040);
                return;
            }
        }
    }
}
