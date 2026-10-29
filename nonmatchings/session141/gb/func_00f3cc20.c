/* 92 words / score 127 (740 vs 744). An inline gs_xyz(x, y, z) helper reproduces the hoisted 1<<32 constant in an s-reg. Left: the original does not strength-reduce (y+1920)<<4 / (y+1944)<<4 (ours makes lui 0x7800 givs), hoists p[1]=1 into s8, and list is s2 not s3; inline gs_put helper, i*28, u64 temporaries tried */
typedef struct { char s[15]; } GbStr15;
extern GbStr15 D_00F72658;
extern char D_00F72668[];
extern char D_00F72678[];
extern u64 **D_00F61F58;
extern void *D_00F61F5C;
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3f9e8(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
void func_00f3fe80(s32, u64 *);
u64 *func_001f0798(u64 *, s32, u32, s32, s32, char *, void *);
u64 *func_001f0758(u64 *, s32, u32, s32, s32, char *, void *);
void func_001efb18(char *, s32 *, u32, s32, s32, char *);

static inline u64 gs_xyz(u32 x, u32 y, u32 z) { return (u64)x | ((u64)y << 16) | ((u64)z << 32); }

void func_00f3cc20(s32 mode, u8 *list, s32 sel) {
    GbStr15 buf = D_00F72658;
    s32 w;
    u64 *p;
    s32 i;
    s32 y;
    p = func_00f3fa80(func_00f3f9d0(*D_00F61F58));
    p[0] = 0x740000007000;
    p[1] = 0x18;
    p += 2;
    p[0] = 0x30000;
    p[1] = 0x47;
    p += 2;
    func_00f3fa98(p);
    if (mode == 0)
        p = func_001f0798(p, 1, 0x80808080, 32, 32, D_00F72668, D_00F61F5C);
    else
        p = func_001f0798(p, 1, 0x80808080, 32, 32, D_00F72678, D_00F61F5C);
    for (i = 0, y = 0; i < 10; i++, y += 28, list += 3952) {
        p = func_00f3fa80(p);
        p[0] = 0x46;
        p[1] = 0;
        p += 2;
        if (i == sel)
            p[0] = 0x3F80802020FF;
        else
            p[0] = 0x3F8080202020;
        p[1] = 1;
        p += 2;
        p[0] = gs_xyz(0x7200, (y + 1920) << 4, 1);
        p[1] = 5;
        p += 2;
        p[0] = gs_xyz(0x7E80, (y + 1944) << 4, 1);
        p[1] = 5;
        p += 2;
        func_00f3fa98(p);
        if (list[80] != 0) {
            w = 0;
            func_001efb18((char *)&list[80], &w, 0x80808080, 32, y + 68, buf.s);
            p = func_001f0758(p, 1, 0x80808080, 32, y + 68, (char *)&list[80], D_00F61F5C);
        } else {
            p = func_001f0798(p, 1, 0x80808080, 32, y + 68, buf.s, D_00F61F5C);
        }
    }
    func_00f3fe80(0x9C40, func_00f3f9e8(p));
    *D_00F61F58 = p;
}
