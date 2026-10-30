/* gb.x func_00f20718: matched by hand. */
#include "ovl.h"

typedef struct { char s[6]; } GbDir;
typedef struct { s16 a, b; u8 pad[16]; } GbTexDef;
extern GbDir D_00F714B0;
extern char D_00F714B8[];
extern char D_00F714D0[];
extern char D_00F714E0[];
extern char D_00F714F0[];
extern char D_00F71500[];
extern char D_00F71510[];
extern char D_00F71520[];
extern char D_00F71530[];
extern char D_00F71540[];
extern char D_00F71550[];
extern s32 D_00F56DBC;
extern u8 *D_00F56DC0;
extern void *D_00F56DE0;
extern void *D_00F56DE4;
extern void *D_00F56DE8;
extern void *D_00F74204;
extern void *D_00F74210;
extern void *D_00F74214;
extern void *D_00F74218;
extern void *D_00F7421C;
extern void *D_00F74220;
extern GbTexDef D_00F61880[];
void func_00f20708(void);
void func_00f40ed8(s32, void *);
void func_00f40f10(s32, void *);
void func_00f40f78(void);
s32 func_001bb7c8(char *, void *);
void func_0011cdf0(s32, void *, void (*)(void));
void func_001bfac8(void);
void func_00f3f148(s32, s32);
void func_001bef40(char *, char *, char *);
void func_00f3e878(void *);
void func_00f3e970(void *);
s32 func_00f3ea50(s32, void *, s32);
u64 func_00f3eac0(s32, void *, s32, s32);
void func_00f3da90(void *);
s32 func_00f3db18(void *);
s32 func_00f3db40(s32, void *);
void func_00f3db80(s32);
void func_00f23850(void *);
void func_00f23830(void *);
void func_00f23840(void *);
void func_001763f0(void *);

s32 func_00f20718(void) {
    char path[256];
    GbDir dir = D_00F714B0;
    u64 *o;
    GbTexDef *t;
    s32 i;
    func_00f40ed8(124, D_00F74210);
    func_00f40f10(124, D_00F74210);
    func_00f40f78();
    func_001bb7c8(D_00F714B8, D_00F74210);
    D_00F56DBC = 1;
    func_0011cdf0(-8, D_00F74210, func_00f20708);
    while (D_00F56DBC)
        func_001bfac8();
    func_00f3f148(640, 480);
    func_001bef40(path, dir.s, D_00F714D0);
    if (!func_001bb7c8(path, D_00F74210))
        return 0;
    func_00f3e878(D_00F74210);
    func_001bef40(path, dir.s, D_00F714E0);
    if (!func_001bb7c8(path, D_00F74220))
        return 0;
    func_00f3e970(D_00F74220);
    o = (u64 *)(D_00F56DC0 + 8704);
    t = D_00F61880;
    for (i = 0; i < 39; i++) {
        s32 a = t->a;
        *o++ = func_00f3eac0(func_00f3ea50(10752, D_00F74220, a), D_00F74220, a, t->b);
        t++;
    }
    func_001bef40(path, dir.s, D_00F714F0);
    if (!func_001bb7c8(path, D_00F7421C))
        return 0;
    func_00f3e970(D_00F7421C);
    func_001bef40(path, dir.s, D_00F71500);
    if (!func_001bb7c8(path, D_00F74214))
        return 0;
    func_00f3da90(D_00F74214);
    func_001bef40(path, dir.s, D_00F71510);
    if (!func_001bb7c8(path, D_00F74218))
        return 0;
    func_00f3da90(D_00F74218);
    for (i = 0; i < func_00f3db18(D_00F74218); i++)
        func_00f3db80(func_00f3db40(i, D_00F74218));
    func_001bef40(path, dir.s, D_00F71520);
    if (!func_001bb7c8(path, D_00F56DE0))
        return 0;
    func_001bef40(path, dir.s, D_00F71530);
    if (!func_001bb7c8(path, D_00F56DE4))
        return 0;
    func_001bef40(path, dir.s, D_00F71540);
    if (!func_001bb7c8(path, D_00F74204))
        return 0;
    func_00f23850(D_00F74210);
    func_00f23830(D_00F74214);
    func_00f23840(D_00F74218);
    func_001bb7c8(D_00F71550, D_00F56DE8);
    func_001763f0(D_00F56DE8);
    return 1;
}
