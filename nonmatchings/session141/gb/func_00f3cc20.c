/* Round 41 wwm2: score 127 -> 102, port.py of the wm twin func_00f63d18 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* 92 words / score 127 (740 vs 744). An inline gs_xyz(x, y, z) helper reproduces the hoisted 1<<32 constant in an s-reg. Left: the original does not strength-reduce (y+1920)<<4 / (y+1944)<<4 (ours makes lui 0x7800 givs), hoists p[1]=1 into s8, and list is s2 not s3; inline gs_put helper, i*28, u64 temporaries tried */
typedef struct { char buf[15]; } Str15;
typedef struct { u8 pad[80]; char name[3872]; } Item;
extern u64 **D_00F61F58;
extern s32 D_00F61F5C;
extern Str15 D_00F72658;
extern char D_00F72668[];
extern char D_00F72678[];
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
u64 *func_00f3f9e8(u64 *);
void func_00f3fe80(s32, u64 *);
u64 *func_001f0798(u64 *, s32, s32, s32, s32, char *, s32);
u64 *func_001f0758(u64 *, s32, s32, s32, s32, char *, s32);
void func_001efb18(char *, s32 *);

void func_00f3cc20(s32 mode, Item *it, s32 cur)
{
    Str15 buf = D_00F72658;
    s32 tmp;
    u64 *p;
    s32 i, y;

    p = func_00f3fa80(func_00f3f9d0(*D_00F61F58));
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 0x30000;
    p[1] = 71;
    p += 2;
    func_00f3fa98(p);
    if (mode == 0) {
        p = func_001f0798(p, 1, 0x80808080, 32, 32, D_00F72668, D_00F61F5C);
    } else {
        p = func_001f0798(p, 1, 0x80808080, 32, 32, D_00F72678, D_00F61F5C);
    }
    y = 0;
    for (i = 0; i < 10; i++) {
        p = func_00f3fa80(p);
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
        func_00f3fa98(p);
        if (it->name[0]) {
            tmp = 0;
            func_001efb18(it->name, &tmp);
            p = func_001f0758(p, 1, 0x80808080, 32, y + 68, it->name, D_00F61F5C);
        } else {
            p = func_001f0798(p, 1, 0x80808080, 32, y + 68, buf.buf, D_00F61F5C);
        }
        it++;
        y += 28;
    }
    func_00f3fe80(40000, func_00f3f9e8(p));
    *D_00F61F58 = p;
}
