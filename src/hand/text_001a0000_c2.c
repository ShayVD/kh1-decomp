/* Model draw dispatch (func_001aaf88) with its two helpers, which must be
 * defined above it (consolidated from w65). */
#include "common.h"

typedef struct { u32 flags; } DMdl;
typedef struct {
    s32 flags;
    u8 pad04[0x48];
    union { u16 h; struct { s8 a, b; } c; } x4c;
} DParam;
extern s32 D_00616224;
extern s32 D_00616228;
extern s32 D_00616230;
s32 func_00265bc0(s32, s32);
void func_00266f38(s32, void *);
extern s32 D_00372908;
extern u8 D_00373000[], D_00373030[];
void func_001aaed0(void) {
    func_00265bc0(0, 0);
    func_00266f38(D_00372908, &D_00373000);
}
void func_001aaf00(void) {
    func_00265bc0(0, 0);
    func_00266f38(D_00372908, &D_00373030);
}
void func_001aaf30(void);
s32 func_001b6910(DMdl *, DParam *);
s32 func_001b3870(DMdl *, DParam *);
s32 func_001ae010(DMdl *, DParam *);
s32 func_001ab0e0(DMdl *, DParam *);
s32 func_001b1ab8(DMdl *, DParam *);
s32 func_001afac0(DMdl *, DParam *);

s32 func_001aaf88(DMdl *m, DParam *p, s32 n) {
    s32 r;

    if (p->flags & 4) {
        if (p->x4c.c.b)
            func_001aaed0();
        else if (p->x4c.c.a)
            func_001aaf00();
        if (p->flags & 0x300)
            r = func_001b6910(m, p);
        else
            r = func_001b3870(m, p);
        if (p->x4c.h)
            func_001aaf30();
    } else {
        if (D_00616228 + n >= D_00616230)
            return D_00616224;
        if (p->flags & 0x80) {
            if (p->flags & 0x300)
                r = func_001ae010(m, p);
            else
                r = func_001ab0e0(m, p);
        } else {
            if (p->flags & 0x300)
                r = func_001b1ab8(m, p);
            else
                r = func_001afac0(m, p);
        }
        D_00616228 += r - D_00616224;
    }
    return r;
}
