/* wm.x func_00f47810: matched by hand. */
#include "ovl.h"

typedef struct { char s[6]; } GbDir;
typedef struct { s16 a, b; u8 pad[16]; } GbTexDef;
extern GbDir D_00FB7560;
extern char D_00FB7568[];
extern char D_00FB7580[];
extern char D_00FB7590[];
extern char D_00FB75A0[];
extern char D_00FB75B0[];
extern char D_00FB75C0[];
extern char D_00FB75D0[];
extern char D_00FB75E0[];
extern char D_00FB75F0[];
extern char D_00FB7600[];
extern s32 D_00F9B53C;
extern u8 *D_00F9B540;
extern void *D_00F9B560;
extern void *D_00F9B564;
extern void *D_00F9B568;
extern void *D_010809BC;
extern void *D_010809C8;
extern void *D_010809CC;
extern void *D_010809D0;
extern void *D_010809D4;
extern void *D_010809D8;
extern GbTexDef D_00FA6000[];
void func_00f47800(void);
void func_00f67fd0(s32, void *);
void func_00f68008(s32, void *);
void func_00f68070(void);
s32 func_001bb7c8(char *, void *);
void func_0011cdf0(s32, void *, void (*)(void));
void func_001bfac8(void);
void func_00f66240(s32, s32);
void func_001bef40(char *, char *, char *);
void func_00f65970(void *);
void func_00f65a68(void *);
s32 func_00f65b48(s32, void *, s32);
u64 func_00f65bb8(s32, void *, s32, s32);
void func_00f64b88(void *);
s32 func_00f64c10(void *);
s32 func_00f64c38(s32, void *);
void func_00f64c78(s32);
void func_00f4a948(void *);
void func_00f4a928(void *);
void func_00f4a938(void *);
void func_001763f0(void *);

s32 func_00f47810(void) {
    char path[256];
    GbDir dir = D_00FB7560;
    u64 *o;
    GbTexDef *t;
    s32 i;
    func_00f67fd0(124, D_010809C8);
    func_00f68008(124, D_010809C8);
    func_00f68070();
    func_001bb7c8(D_00FB7568, D_010809C8);
    D_00F9B53C = 1;
    func_0011cdf0(-8, D_010809C8, func_00f47800);
    while (D_00F9B53C)
        func_001bfac8();
    func_00f66240(640, 480);
    func_001bef40(path, dir.s, D_00FB7580);
    if (!func_001bb7c8(path, D_010809C8))
        return 0;
    func_00f65970(D_010809C8);
    func_001bef40(path, dir.s, D_00FB7590);
    if (!func_001bb7c8(path, D_010809D8))
        return 0;
    func_00f65a68(D_010809D8);
    o = (u64 *)(D_00F9B540 + 8704);
    t = D_00FA6000;
    for (i = 0; i < 39; i++) {
        s32 a = t->a;
        *o++ = func_00f65bb8(func_00f65b48(10752, D_010809D8, a), D_010809D8, a, t->b);
        t++;
    }
    func_001bef40(path, dir.s, D_00FB75A0);
    if (!func_001bb7c8(path, D_010809D4))
        return 0;
    func_00f65a68(D_010809D4);
    func_001bef40(path, dir.s, D_00FB75B0);
    if (!func_001bb7c8(path, D_010809CC))
        return 0;
    func_00f64b88(D_010809CC);
    func_001bef40(path, dir.s, D_00FB75C0);
    if (!func_001bb7c8(path, D_010809D0))
        return 0;
    func_00f64b88(D_010809D0);
    for (i = 0; i < func_00f64c10(D_010809D0); i++)
        func_00f64c78(func_00f64c38(i, D_010809D0));
    func_001bef40(path, dir.s, D_00FB75D0);
    if (!func_001bb7c8(path, D_00F9B560))
        return 0;
    func_001bef40(path, dir.s, D_00FB75E0);
    if (!func_001bb7c8(path, D_00F9B564))
        return 0;
    func_001bef40(path, dir.s, D_00FB75F0);
    if (!func_001bb7c8(path, D_010809BC))
        return 0;
    func_00f4a948(D_010809C8);
    func_00f4a928(D_010809CC);
    func_00f4a938(D_010809D0);
    func_001bb7c8(D_00FB7600, D_00F9B568);
    func_001763f0(D_00F9B568);
    return 1;
}
