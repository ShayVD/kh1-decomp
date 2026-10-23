#include "common.h"
#include "data/bss_0063.h"

typedef struct {
    u8 pad[0xa80];
    u8 a[10];
    u8 b[10];
    u8 c[10];
    u8 d[40];
} Save;
#include "data/types/text_001c0000_c10.h"
#include "data/types/text_001c0000_c10_p.h"
typedef struct { u8 pad[0x3078]; u64 f3078; } Big;

extern volatile s32 D_002C5958;
extern s32 D_003DD25C;
extern s32 D_003DD264;
extern Menu D_003DC498;
extern Big D_00389C90;
extern char D_003DCB10[][32];
#include "data/pieces/D_003DCB90.h"
extern char D_003DD1B0[];
extern char D_003DD1D8[];
extern char D_003DD1F0[];
extern char D_003DD210[];
#include "data/pieces/D_003DD230.h"
extern char D_003DD238[];
extern char D_003DD240[];
extern char D_003DD250[];
extern char D_006305D0[][10];
extern char D_006307C8[];
extern Pair D_006310C8[];
extern Pair D_00631148[];
extern Pair D_006311C8[];
extern Pair D_00631248[];
extern s8 D_006314C8;
extern s32 D_003DD260;
extern s32 D_003DD28C;
extern s32 D_006305CC;
extern char D_003DD220[];
extern char D_003DD248[];
extern u8 D_00630380[];
typedef struct { s32 a; s32 b; void (*fn)(); s32 d; } Cb20;
extern Cb20 D_006305C0;
extern u8 D_00630300[];

void *func_00232cc0(s32);
void func_001ea128(void *, void *);
void func_001ea268(void *, void *);
void func_0010bdd0(void *, void *);
void func_001e4b08(void);
void func_001e4c20(void);
void func_001e5810();

void func_0010bd90(void *, void (*)());
void func_0010e3f0(void *);
void func_0010ef70(void *, void *, void *);
void func_0010f558(void *, void *, s32);
void func_001e64e0();
void func_001e6b70();
void func_001e5788();


extern s32 D_003DD258;
void func_001e5198(void);

void func_001e5198(void) {
    Save *s = func_00232cc0(1);
    s32 *m = &D_003DD25C;
    s32 i;

    if (*m == 3) {
        switch (D_003DD258) {
        case 10:
            if (D_006305CC == 4) D_006305CC = 3;
            else D_006305CC++;
            D_003DC498.n = 50;
            func_001ea128(D_006307C8, D_003DD1B0);
            func_001ea268(D_006307C8, D_003DD230);
            func_001ea268(D_006307C8, D_003DCB10[D_003DD25C]);
            func_001ea268(D_006307C8, D_003DD230);
            for (i = D_006305CC * 10; i < D_006305CC * 10 + 10; i++) {
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_006305D0[i]);
                if (!s->d[i]) {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_00631248[s->d[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
            }
            if (D_006305CC < 4) {
                func_001ea268(D_006307C8, D_003DD210);
                func_001ea268(D_006307C8, D_003DD230);
                func_001ea268(D_006307C8, D_003DD220);
                func_001ea268(D_006307C8, D_003DD230);
            } else {
                func_001ea268(D_006307C8, D_003DD220);
                func_001ea268(D_006307C8, D_003DD230);
                func_001ea268(D_006307C8, D_003DD230);
            }
            func_001ea268(D_006307C8, D_003DD1F0);
            func_001ea268(D_006307C8, D_003DD240);
            func_0010e3f0(D_00630380);
            func_0010ef70(D_00630380 - 0x80, D_006307C8, func_001e5198);
            {
                Cb20 *p = &D_006305C0;
                p->a = 3;
                if (D_006305CC < 4) p->b = 14;
                else p->b = 13;
            }
            D_006305C0.fn = func_001e5788;
            func_0010f558(&D_006305C0, D_00630300, D_006305C0.a);
            return;
        case 11:
            D_006305CC--;
            D_003DC498.n = 50;
            func_001ea128(D_006307C8, D_003DD1B0);
            func_001ea268(D_006307C8, D_003DD230);
            func_001ea268(D_006307C8, D_003DCB10[*m]);
            func_001ea268(D_006307C8, D_003DD230);
            for (i = D_006305CC * 10; i < D_006305CC * 10 + 10; i++) {
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_003DD238);
                func_001ea268(D_006307C8, D_006305D0[i]);
                if (!s->d[i]) {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_00631248[s->d[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
            }
            func_001ea268(D_006307C8, D_003DD210);
            func_001ea268(D_006307C8, D_003DD230);
            if (D_006305CC > 0) func_001ea268(D_006307C8, D_003DD220);
            func_001ea268(D_006307C8, D_003DD230);
            func_001ea268(D_006307C8, D_003DD1F0);
            func_001ea268(D_006307C8, D_003DD240);
            func_0010e3f0(D_00630380);
            func_0010ef70(D_00630380 - 0x80, D_006307C8, func_001e5198);
            {
                Cb20 *p = &D_006305C0;
                p->a = 3;
                if (D_006305CC > 0) p->b = 14;
                else p->b = 13;
            }
            D_006305C0.fn = func_001e5788;
            func_0010f558(&D_006305C0, D_00630300, D_006305C0.a);
            break;
        }
    }
}

void func_001e58c0(s32 mode) {
    Save *s;
    s32 i;

    D_003DD25C = mode;
    D_003DD264 = 0;
    D_002C5958 |= 0xC;
    s = func_00232cc0(1);
    func_001e4b08();
    func_001ea128(D_003DC498.last, D_003DCB10[mode]);
    if (mode == 3) {
        D_003DC498.n = 50;
        func_001ea128(D_006307C8, D_003DD1B0);
        func_001ea268(D_006307C8, D_003DD230);
        func_001ea268(D_006307C8, D_003DCB10[3]);
        func_001ea268(D_006307C8, D_003DD230);
        for (i = 0; i < 10; i++) {
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_006305D0[i]);
            if (!s->d[i]) {
                func_001ea268(D_006307C8, D_003DD250);
                func_001ea268(D_006307C8, D_003DCB90[0]);
                func_001ea268(D_006307C8, D_003DD230);
            } else {
                func_001ea268(D_006307C8, D_003DD250);
                func_001ea268(D_006307C8, D_00631248[s->d[i] - 1].a);
                func_001ea268(D_006307C8, D_003DD230);
            }
        }
        func_001ea268(D_006307C8, D_003DD210);
        func_001ea268(D_006307C8, D_003DD230);
        func_001ea268(D_006307C8, D_003DD230);
        func_001ea268(D_006307C8, D_003DD1F0);
        func_001ea268(D_006307C8, D_003DD240);
        D_006314C8 = 3;
    } else {
        D_003DC498.n = 10;
        func_001ea128(D_006307C8, D_003DD1B0);
        func_001ea268(D_006307C8, D_003DD230);
        func_001ea268(D_006307C8, D_003DD1D8);
        func_001ea268(D_006307C8, D_003DD230);
        func_001ea268(D_006307C8, D_003DCB10[mode]);
        func_001ea268(D_006307C8, D_003DD230);
        for (i = 0; i < 10; i++) {
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_003DD238);
            func_001ea268(D_006307C8, D_006305D0[i]);
            switch (mode) {
            case 0:
                if (!s->a[i]) {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_006310C8[s->a[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
                break;
            case 1:
                if (!s->b[i]) {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_00631148[s->b[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
                break;
            case 2:
                if (!s->c[i]) {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_003DCB90[0]);
                    func_001ea268(D_006307C8, D_003DD230);
                } else {
                    func_001ea268(D_006307C8, D_003DD250);
                    func_001ea268(D_006307C8, D_006311C8[s->c[i] - 1].a);
                    func_001ea268(D_006307C8, D_003DD230);
                }
                break;
            }
        }
        func_001ea268(D_006307C8, D_003DD230);
        func_001ea268(D_006307C8, D_003DD1F0);
        func_001ea268(D_006307C8, D_003DD240);
        D_006314C8 = 4;
    }
    func_001e4c20();
    func_0010bdd0(D_00630300, func_001e5810);
    D_00389C90.f3078 |= 16;
}

void func_001e65d0(void) {
    Save *s = func_00232cc0(1);
    s32 i;

    if (D_003DD25C == 3) {
        s32 *q = &D_003DD260;
        switch (*q) {
        default:
            *q += D_006305CC * 10;
            func_0010bd90(D_00630300, func_001e64e0);
            D_003DD28C = 0;
            return;
        case 10:
            if (D_006305CC == 4) D_006305CC = 3;
            else D_006305CC++;
            func_001ea128(D_006307C8, D_003DD248);
            for (i = D_006305CC * 10; i < D_006305CC * 10 + 10; i++) {
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
            if (D_006305CC < 4) {
                func_001ea268(D_006307C8, D_003DD210);
                func_001ea268(D_006307C8, D_003DD230);
                func_001ea268(D_006307C8, D_003DD220);
                func_001ea268(D_006307C8, D_003DD230);
            } else {
                func_001ea268(D_006307C8, D_003DD220);
                func_001ea268(D_006307C8, D_003DD230);
                func_001ea268(D_006307C8, D_003DD230);
            }
            func_001ea268(D_006307C8, D_003DD240);
            func_0010e3f0(D_00630380);
            func_0010ef70(D_00630380 - 0x80, D_006307C8, func_001e65d0);
            if (D_006305CC < 4) {
                Cb20 *p = &D_006305C0;
                p->a = 1;
                p->b = 12;
            } else {
                Cb20 *p = &D_006305C0;
                p->a = 1;
                p->b = 11;
            }
            D_006305C0.fn = func_001e6b70;
            func_0010f558(&D_006305C0, D_00630300, D_006305C0.a);
            return;
        case 11:
            D_003DC498.n = 50;
            D_006305CC--;
            func_001ea128(D_006307C8, D_003DD248);
            for (i = D_006305CC * 10; i < D_006305CC * 10 + 10; i++) {
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
            func_001ea268(D_006307C8, D_003DD230);
            if (D_006305CC > 0) func_001ea268(D_006307C8, D_003DD220);
            func_001ea268(D_006307C8, D_003DD240);
            func_0010e3f0(D_00630380);
            func_0010ef70(D_00630380 - 0x80, D_006307C8, func_001e65d0);
            if (D_006305CC > 0) {
                Cb20 *p = &D_006305C0;
                p->a = 1;
                p->b = 12;
            } else {
                Cb20 *p = &D_006305C0;
                p->a = 2;
                p->b = 11;
            }
            D_006305C0.fn = func_001e6b70;
            func_0010f558(&D_006305C0, D_00630300, D_006305C0.a);
            return;
        }
    }
    func_0010bd90(D_00630300, func_001e64e0);
    D_003DD28C = 0;
}
#include "data/bss_0063_mixed.h"
#include "data/bss_0063_typed.h"
#include "data/data_003D.h"
#include "data/pieces/D_003DC498.h"
#include "data/pieces/D_003DD258.h"
#include "data/pieces/D_003DD28C.h"
