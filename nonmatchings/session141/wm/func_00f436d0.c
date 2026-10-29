/* 30 words differ, score 56 (1008 vs 1008 bytes); logic complete (loader like f47810; 64-byte unused pad gives the 288 frame). Left: s2/s3 swapped (orig i in s2, &dir and the u64 out pointer share s3) and the D_00F9B2CC = 1 store scheduling. Tried: decl orders, separate loop vars, count-up vs count-down loops, do-while, inline helper, indexed loops, late struct copies, 10 min permuter (no gain) */
typedef struct { char s[6]; } Dir6;
typedef struct { char s[10]; } Dir10;
typedef struct { s16 a, b; u8 pad[16]; } TexDef;
extern Dir6 D_00FB7290;
extern Dir10 D_00FB7240;
extern char D_00FB7298[];
extern char D_00FB72B0[];
extern char D_00FB72C0[];
extern char D_00FB72D0[];
extern char D_00FB72E0[];
extern char D_00FB72F8[];
extern char D_00FB7310[];
extern char D_00FB7320[];
extern char D_00FB7330[];
extern char D_00FB7350[];
extern s32 D_00F9B2CC;
extern void *D_00F87028;
extern void *D_00F8702C;
extern void *D_00F87030;
extern void *D_00F87034;
extern void *D_00F87038;
extern void *D_00F87044;
extern void *D_00F87048;
extern void *D_00F87060;
extern void *D_00F87064;
extern u64 D_00F87070[];
extern u64 D_00F87170[];
extern TexDef D_00F9B330[];
extern TexDef D_00F85000[];
extern s32 D_00F850D4;
extern s32 D_00F850BC;
extern s32 D_00F87304;
extern s32 D_00F87EDC[][22];
void func_00f436c0(void);
s32 func_001bb7c8(char *, void *);
void func_0011cdf0(s32, void *, void (*)(void));
void func_001bfac8(void);
void func_001bef40(char *, char *, char *);
void func_00f65a68(void *);
void func_00f65ab0(s32);
s32 func_00f65b48(s32, void *, s32);
u64 func_00f65bb8(s32, void *, s32, s32);
void func_00f64b88(void *);
s32 func_00f64c10(void *);
s32 func_00f64c38(s32, void *);
void func_00f64c78(s32);
void func_001763f0(void *);
void func_00f3fd60(s32, s32, s32);
void func_00f3f7c8(s32);
void func_00162058(void *);

void func_00f436d0(void) {
    char path[128];
    Dir6 dir = D_00FB7290;
    Dir10 dir2 = D_00FB7240;
    char pad[64];
    u64 *o;
    TexDef *t;
    s32 i;

    func_001bb7c8(D_00FB7298, D_00F87048);
    D_00F9B2CC = 1;
    func_0011cdf0(-8, D_00F87048, func_00f436c0);
    while (D_00F9B2CC)
        func_001bfac8();
    func_001bef40(path, dir.s, D_00FB72B0);
    func_001bb7c8(path, D_00F87030);
    func_00f64b88(D_00F87030);
    func_001bef40(path, dir.s, D_00FB72C0);
    func_001bb7c8(path, D_00F87034);
    func_00f64b88(D_00F87034);
    for (i = 0; i < func_00f64c10(D_00F87034); i++)
        func_00f64c78(func_00f64c38(i, D_00F87034));
    func_00f65ab0(9728);
    func_001bef40(path, dir.s, D_00FB72D0);
    func_001bb7c8(path, D_00F87038);
    func_00f65a68(D_00F87038);
    func_001bb7c8(D_00FB72E0, D_00F87028);
    func_00f65a68(D_00F87028);
    o = D_00F87070;
    t = D_00F9B330;
    for (i = 0; i < 18; i++) {
        s32 a = t->a;
        *o++ = func_00f65bb8(func_00f65b48(10464, D_00F87028, a), D_00F87028, a, t->b);
        t++;
    }
    func_001bb7c8(D_00FB72F8, D_00F8702C);
    func_00f65a68(D_00F8702C);
    o = D_00F87170;
    t = D_00F85000;
    for (i = 0; i < 18; i++) {
        s32 a = t->a;
        *o++ = func_00f65bb8(func_00f65b48(13824, D_00F8702C, a), D_00F8702C, a, t->b);
        t++;
    }
    func_001bef40(path, dir2.s, D_00FB7310);
    func_001bb7c8(path, D_00F87048);
    func_001763f0(D_00F87048);
    func_001bef40(path, dir2.s, D_00FB7320);
    func_001bb7c8(path, D_00F87044);
    func_001763f0(D_00F87044);
    func_00f3fd60(0, D_00F850D4, 0);
    func_00f3fd60(0, D_00F850D4, 1);
    if (D_00F850BC == 0) {
        func_00f3f7c8(D_00F87EDC[D_00F850D4][0]);
    } else {
        func_00f3f7c8(D_00F87EDC[D_00F87304][0]);
    }
    func_001bb7c8(D_00FB7330, D_00F87060);
    func_001bb7c8(D_00FB7350, D_00F87064);
    func_00162058(D_00F87060);
    func_00162058(D_00F87064);
}
