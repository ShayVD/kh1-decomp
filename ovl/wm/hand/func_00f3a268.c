/* wm.x func_00f3a268: matched by hand. */
#include "ovl.h"

typedef struct { s32 type; s32 pad[3]; s32 f10; s32 pad2[7]; } E3a268;
typedef struct {
    f32 m[4][4];
    f32 v40[4];
    f32 v50[4];
    f32 m60[4][4];
    f32 mA0[4][4];
    s32 e0;
    s32 e4;
    f32 e8;
    u8 *ec;
    s32 *f0;
    s32 f4;
    s32 f8;
    s32 fc;
    s32 f100;
    s32 f104;
    s32 f108;
    E3a268 *list;
} O3a268;
typedef struct { u8 pad[0x540]; s32 f540; } P3a268;
typedef struct { u8 pad[6]; u16 f6; } Q3a268;
void func_00f39f60(O3a268 *);
s32 func_00f3a1d8(void *);
s32 func_00f361d8(void);
Q3a268 *func_00f3f260(s32, s32);
s32 func_00f39968(s32, O3a268 *, void *);
s32 func_001c0310(s32, void *, ...);
void func_00f39de8(O3a268 *);
void func_00f3a0f0(O3a268 *);
void func_001bfac8(void);
void func_00f20b08(s32, s32);
void func_001ba708(s32);
void func_00f309d0(s32);
void func_00f39fd0(O3a268 *);
void func_00f39b10();
extern s32 D_00F85098;
extern s32 D_00F850A0;
extern s32 D_00F850A4;
extern P3a268 *D_00F864C0;
extern f32 D_00F86480[4][4];
extern s32 D_00F8C2F0;

void func_00f3a268(O3a268 *o) {
    E3a268 *list;
    E3a268 *p;
    s32 off;
    Q3a268 *q;

    o->fc = 1;
    if (o->e4 < 0) {
        D_00F8C2F0 = 0;
    } else {
        func_00f39f60(o);
    }
    list = o->list;
    o->f104 = 0;
    while (o->fc != 0 && func_00f3a1d8(o->m[3]) != 0
           && (!(o->e4 & 0x80000000) || func_00f361d8() != 0)
           && (q = func_00f3f260(o->e4, D_00F864C0->f540)) != NULL
           && !(q->f6 & 1)) {
        if (D_00F850A4 == 0) {
            if (D_00F8C2F0 != 0 && (o->e4 & 0x80000000)) {
                goto next;
            }
            for (off = 0; list[off].type != 1; off++) {
                if (list[off].f10 != 5 && func_00f39968(o->f104, o, &o->list[off]) != 0) {
                    func_001c0310(12, func_00f39b10, o, &list[off], 1);
                }
            }
            func_00f39de8(o);
            o->f104++;
        }
        if (o->e4 >= 0) {
            func_00f3a0f0(o);
        }
    next:
        func_001bfac8();
    }
    o->e0 = 0;
    o->fc = 0;
    if (o->e4 < 0) {
        if (!(o->e4 & 1)) {
            func_00f20b08(0, 0);
        }
        sceVu0CopyMatrix(D_00F86480, o->m);
        D_00F850A0 = 0;
        D_00F85098 = 1;
        func_001ba708(1);
        func_00f309d0(1);
        return;
    }
    func_00f39fd0(o);
}
