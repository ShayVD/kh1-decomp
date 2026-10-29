/* score 102. Menu list builder, same family as f639c0 (GS header, per-row sprite with highlight colour, names via func_001f0758/func_001f0798). Structure is right. Main issue: gcc strength-reduces the whole (y + 1920) << 4 << 16 qword as a giv (lui 0x7800 base); the original recomputes addiu/sll/dsll from y every iteration while still hoisting the 1, 5 and 0x8000<<17 constants. Tried s64 temps, an explicit y biv, and constant forms. Next: a goto loop or a permuter run. */
typedef struct { char buf[15]; } Str15;
typedef struct { u8 pad[80]; char name[3872]; } Item;
extern u64 **D_00FA66D8;
extern s32 D_00FA66DC;
extern Str15 D_00FB8708;
extern char D_00FB8718[];
extern char D_00FB8728[];
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
u64 *func_00f66ae0(u64 *);
void func_00f66f78(s32, u64 *);
u64 *func_001f0798(u64 *, s32, s32, s32, s32, char *, s32);
u64 *func_001f0758(u64 *, s32, s32, s32, s32, char *, s32);
void func_001efb18(char *, s32 *);

void func_00f63d18(s32 mode, Item *it, s32 cur)
{
    Str15 buf = D_00FB8708;
    s32 tmp;
    u64 *p;
    s32 i, y;

    p = func_00f66b78(func_00f66ac8(*D_00FA66D8));
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 0x30000;
    p[1] = 71;
    p += 2;
    func_00f66b90(p);
    if (mode == 0) {
        p = func_001f0798(p, 1, 0x80808080, 32, 32, D_00FB8718, D_00FA66DC);
    } else {
        p = func_001f0798(p, 1, 0x80808080, 32, 32, D_00FB8728, D_00FA66DC);
    }
    y = 0;
    for (i = 0; i < 10; i++) {
        p = func_00f66b78(p);
        p[0] = 70;
        p[1] = 0;
        p += 2;
        if (i == cur) {
            p[0] = 0x3F800000802020FFLL;
        } else {
            p[0] = 0x3F80000080202020LL;
        }
        p[1] = 1;
        p += 2;
        p[0] = 29184 | ((s64)((y + 1920) << 4) << 16) | ((s64)0x8000 << 17);
        p[1] = 5;
        p += 2;
        p[0] = 32384 | ((s64)((y + 1944) << 4) << 16) | ((s64)0x8000 << 17);
        p[1] = 5;
        p += 2;
        func_00f66b90(p);
        if (it->name[0]) {
            tmp = 0;
            func_001efb18(it->name, &tmp);
            p = func_001f0758(p, 1, 0x80808080, 32, y + 68, it->name, D_00FA66DC);
        } else {
            p = func_001f0798(p, 1, 0x80808080, 32, y + 68, buf.buf, D_00FA66DC);
        }
        it++;
        y += 28;
    }
    func_00f66f78(40000, func_00f66ae0(p));
    *D_00FA66D8 = p;
}
