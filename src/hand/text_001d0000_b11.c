#include "common.h"

typedef struct {
    u8 pad[0xa80];
    u8 a[10];
    u8 b[10];
    u8 c[10];
    u8 d[40];
    u8 padac8[0xad0 - 0xac8];
    s32 fad0;
} Save;
typedef struct { char *a; char *b; } Pair;
typedef struct {
    s32 n;
    char str[50][32];
    char last[64];
} Menu;
typedef struct { u8 pad[0x3078]; u64 f3078; } Big;
typedef struct {
    u8 a[2048];
    u8 b[256];
    u8 c[384];
    u8 l0[10];
    u8 l1[10];
    u8 l2[10];
    u8 l3[50];
    u32 f0:1;
    u32 f1:1;
    u32 f2:1;
    u32 f3:1;
    char name[10];
    u8 padade[0xb14 - 0xadb];
    s32 tab[32][5];
    u8 padd94[0xdc4 - 0xd94];
    u32 g0:1;
    u32 g1:1;
    u32 g2:1;
    u32 g3:1;
    u32 g4:1;
    u8 padg[3];
    u8 h[8];
    u8 dd0;
    s32 dd4;
} SaveInit;
typedef struct { char s[10]; } Str10;
typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1c[0x30 - 0x1c];
    f32 f30;
    f32 f34;
    f32 f38;
} Actor;
typedef struct {
    s32 x0;
    Actor *obj;
    f32 p[3];
    f32 f14[3];
    f32 f20;
    u8 pad24[0x28];
    f32 f4c;
    f32 f50;
    f32 f54;
    f32 f58;
    s8 b5c;
    s8 b5d;
    u8 pad5e[2];
    s32 f60;
    s32 f64;
    u8 pad68[0x118];
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    union { u64 x; s32 i[2]; } flags;
} VM;

extern Big D_00389C90;
extern Menu D_003DC498;
extern Str10 D_004908F0;
extern char D_003DCB90[][32];
extern char D_003DCD10[][32];
extern char D_003DCDF0[];
extern char D_003DCE30[];
extern char D_003DCE70[];
extern char D_003DD210[];
extern char D_003DD230[];
extern char D_003DD238[];
extern char D_003DD240[];
extern char D_003DD248[];
extern char D_003DD270[];
extern char D_003DD278[];
extern s32 D_003DD258;
extern s32 D_003DD25C;
extern s32 D_003DD260;
extern s32 D_003DD27C;
extern s32 D_003DD280;
extern s32 D_003DD28C;
extern u8 D_00630300[];
extern u8 D_006303B0[];
extern u8 D_006304E0[];
extern u8 D_00630510[];
extern s32 D_006305CC;
extern char D_006305D0[][10];
extern char D_006307C8[];
extern char D_00630FC8[];
extern Pair D_006310C8[];
extern Pair D_00631148[];
extern Pair D_006311C8[];
extern Pair D_00631248[];

void *func_00232cc0(s32);
void func_001ea128(void *, void *);
void func_001ea268(void *, void *);
void func_0010ef70(void *, char *, void *);
void func_0010bdd0(void *, void *);
void func_0010e3f0(void *);
void func_002329a0(void *, void *, void *);
void func_00112150(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_001ec758(s32, s32, s32);
void func_001e4b08(void);
void func_001e4d20();
void func_001e5ee0(void);
void func_001e6578();
void func_001e6580();
void func_001e6ba8();
void func_001e6e20();

void func_001e4d50(void) {
    Save *s = func_00232cc0(1);
    func_001ea128(D_00630FC8, D_003DD248);
    func_001ea268(D_00630FC8, D_003DD270);
    switch (D_003DD25C) {
    case 0:
        if (s->a[D_003DD258]) {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258]);
            func_001ea268(D_00630FC8, D_006310C8[s->a[D_003DD258] - 1].a);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_006310C8[s->a[D_003DD258] - 1].b);
        } else {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258]);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[1]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[2]);
        }
        break;
    case 1:
        if (s->b[D_003DD258]) {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258]);
            func_001ea268(D_00630FC8, D_00631148[s->b[D_003DD258] - 1].a);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_00631148[s->b[D_003DD258] - 1].b);
        } else {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258]);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[1]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[2]);
        }
        break;
    case 2:
        if (s->c[D_003DD258]) {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258]);
            func_001ea268(D_00630FC8, D_006311C8[s->c[D_003DD258] - 1].a);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_006311C8[s->c[D_003DD258] - 1].b);
        } else {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258]);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[1]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[2]);
        }
        break;
    case 3:
        if (!s->d[D_003DD258 + D_006305CC * 10]) {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258 + D_006305CC * 10]);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_003DCB90[0]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[1]);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DCB90[2]);
        } else {
            func_001ea268(D_00630FC8, D_006305D0[D_003DD258 + D_006305CC * 10]);
            func_001ea268(D_00630FC8, D_00631248[s->d[D_003DD258 + D_006305CC * 10] - 1].a);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_00631248[s->d[D_003DD258 + D_006305CC * 10] - 1].b);
        }
        break;
    }
    func_001ea268(D_00630FC8, D_003DD240);
    func_0010ef70(D_006303B0, D_00630FC8, func_001e4d20);
}

void func_001e74b0(s32 mode) {
    Save *s = func_00232cc0(1);
    s32 i;
    D_003DD25C = mode;
    D_003DD28C = 0;
    func_001e5ee0();
    func_001e4b08();
    D_003DD260 = -1;
    if (mode == 3) {
        func_001ea128(D_006307C8, D_003DD248);
        for (i = 0; i < 10; i++) {
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_006305D0[i]);
            if (!s->d[i]) {
                func_001ea268(D_006307C8, D_003DCB90[0]);
                func_001ea268(D_006307C8, D_003DD230);
            } else {
                func_001ea268(D_006307C8, D_00631248[s->d[i] - 1].a);
                func_001ea268(D_006307C8, D_003DD230);
            }
        }
        func_001ea268(D_006307C8, D_003DD210);
        func_001ea268(D_006307C8, D_003DD240);
    } else {
        func_001ea128(D_006307C8, D_003DD248);
        for (i = 0; i < 10; i++) {
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_006305D0[i]);
            switch (mode) {
            case 0:
                if (!s->a[i]) {
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_006310C8[s->a[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
                break;
            case 1:
                if (!s->b[i]) {
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_00631148[s->b[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
                break;
            case 2:
                if (!s->c[i]) {
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_006311C8[s->c[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
                break;
            }
        }
        func_001ea268(D_006307C8, D_003DD240);
    }
    func_0010bdd0(D_00630300, func_001e6ba8);
    D_00389C90.f3078 |= 16;
}

void func_001eacd0(void) {
    Str10 tmp = D_004908F0;
    SaveInit *s;
    u8 *q;
    s32 i, j;

    s = (SaveInit *)func_00232cc0(1);
    q = (u8 *)func_00232cc0(2);
    for (i = 0; i < 2048; i++) s->a[i] = 0;
    for (i = 0; i < 256; i++) s->b[i] = 0;
    for (i = 0; i < 384; i++) s->c[i] = 0;
    for (i = 0; i < 1024; i++) q[i] = 0;
    for (i = 0; i < 10; i++) {
        if (i == 9) {
            s->l2[i] = 0;
            s->l1[i] = 0;
            s->l0[i] = 0;
        } else {
            s->l2[i] = i + 1;
            s->l1[i] = i + 1;
            s->l0[i] = i + 1;
        }
    }
    for (i = 0; i < 50; i++) {
        if (i == 49) s->l3[i] = 0;
        else s->l3[i] = i + 1;
    }
    s->f2 = 0;
    s->f1 = 0;
    s->f0 = 0;
    s->f3 = 0;
    for (i = 0; i < sizeof(tmp); i++) s->name[i] = tmp.s[i];
    s->g0 = 0;
    s->g1 = 0;
    s->g2 = 0;
    s->g3 = 0;
    s->g4 = 0;
    for (i = 0; i < 32; i++)
        for (j = 0; j < 5; j++) s->tab[i][j] = -1;
    for (i = 0; i < 8; i++) s->h[i] = 0;
    s->dd0 = 0;
    s->dd4 = 0;
    for (i = 0; i < 5; i++) {
        func_001ec758(0, i, -1);
        func_001ec758(1, i, -1);
        func_001ec758(2, i, -1);
        func_001ec758(3, i, -1);
    }
}

/* Split out of the func_001e6f28 layout entry. */
extern s32 D_003DD268;
extern s32 D_003DD258;
extern s32 D_003DD28C;
extern u8 D_00630460[];
void func_0010bd90(void *, s32);
void func_001e7228(s32 a) {
    D_003DD28C = 0;
    D_003DD258 = a;
    if (D_003DD268 < a) func_0010bd90(D_00630460, 0);
}

/* needs make: uses rodata */
s32 func_001dad58(VM *vm) {
    switch (vm->stk[vm->sp - 1]) {
    case 0: func_00112150(7, 1, 1, 1, vm->stk[vm->sp], 0, 1, 0, 295, 1); break;
    case 1: func_00112150(8, 1, 1, 0, vm->stk[vm->sp], 0, 1, 0, 295, 1); break;
    case 2: func_00112150(9, 1, 1, 1, vm->stk[vm->sp], 0, 2, 0, 151, 1); break;
    case 3: func_00112150(2, 1, 1, 1, vm->stk[vm->sp], 0, 2, 0, 295, 1); break;
    case 4: func_00112150(2, 1, 1, 0, vm->stk[vm->sp], 0, 0, 0, 15, 1); break;
    case 5: func_00112150(0, 0, 0, 1, vm->stk[vm->sp], 0, 2, 0, 0, 1); break;
    case 6: func_00112150(3, 1, 0, 1, vm->stk[vm->sp], 0, 3, 0, 295, 0); break;
    case 7: func_00112150(4, 1, 0, 1, vm->stk[vm->sp], 0, 3, 0, 295, 0); break;
    case 8: func_00112150(4, 1, 0, 0, vm->stk[vm->sp], 0, 0, 0, 295, 1); break;
    case 9: func_00112150(5, 1, 1, 1, vm->stk[vm->sp], 0, 3, 0, 295, 1); break;
    case 10: func_00112150(5, 1, 1, 0, vm->stk[vm->sp], 0, 0, 0, 295, 1); break;
    case 11: func_00112150(6, 0, 0, 0, vm->stk[vm->sp], 1, 3, 0, 295, 1); break;
    }
    vm->sp -= 2;
    return 2;
}

void func_001e6f28(void) {
    Save *s = func_00232cc0(1);
    s32 i, j;
    switch (D_003DD25C) {
    case 0:
        if (s->fad0 & 1) {
            D_003DC498.n = 9;
            func_001ea128(D_006307C8, D_006305D0[0]);
            func_001ea268(D_006307C8, D_003DCB90[0]);
            func_001ea128(D_003DC498.last, D_006307C8);
            for (i = 0; i < 9; i++) {
                func_001ea128(D_006307C8, D_006305D0[i + 1]);
                if (s->a[i + 1] == 0) {
                    func_001ea268(D_006307C8, D_003DCB90[s->a[i + 1]]);
                } else {
                    func_001ea268(D_006307C8, D_006310C8[s->a[i + 1] - 1].a);
                }
                func_001ea128(D_003DC498.str[i], D_006307C8);
            }
            func_002329a0(&D_003DC498, func_001e6578, func_001e6580);
            func_0010bdd0(D_00630300, func_001e6ba8);
            D_003DD280 = 0;
            D_003DD27C = 0;
        }
        break;
    case 1:
        if (!(s->fad0 & 2)) {
            for (i = 1; i < 10; i++) {
                if (s->b[i] == 0) {
                    func_001ea128(D_00630FC8, D_003DCDF0);
                    func_001ea268(D_00630FC8, D_003DD270);
                    func_001ea268(D_00630FC8, D_006305D0[i - 1]);
                    func_001ea268(D_00630FC8, D_003DCB90[s->b[i - 1]]);
                    func_001ea268(D_00630FC8, D_003DD278);
                    for (j = 0; j < 3; j++) {
                        func_001ea268(D_00630FC8, D_003DD230);
                        func_001ea268(D_00630FC8, D_003DCD10[j]);
                        if (j < 2) {
                            func_001ea268(D_00630FC8, D_003DCE30);
                        } else {
                            func_001ea268(D_00630FC8, D_003DCE70);
                        }
                    }
                    func_0010e3f0(D_006304E0);
                    func_0010ef70(D_006304E0 - 128, D_00630FC8, 0);
                    func_0010bdd0(D_00630510, func_001e6e20);
                    return;
                }
            }
        }
        break;
    case 2:
        j = 2;
        break;
    case 3:
        j = 3;
        break;
    case 4:
        j = 4;
        break;
    }
}
#include "data/bss_0063_mixed.h"
#include "data/data_003D.h"
#include "data/pieces/D_003DD258.h"
#include "data/pieces/D_003DD28C.h"
