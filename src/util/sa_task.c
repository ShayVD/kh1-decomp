/* src/sa_task.c (its assert names the file; docs/modules.md "Session 47"),
 * 0x0024b1f0-0x0024b9a8 except sa_task.nostrict.c's func_0024b1f0 (the
 * reset).  Up to eight (TASK_GRUPE_MAX) tasks, each with its own stack
 * (func_0024b778 the size of a group's block, func_0024b7a0 makes one in it,
 * func_0024b958 with malloc), started and switched by the hand-written
 * assembly in src/asm/text_0024e0a4.s (func_0024e0a4 the set up,
 * func_0024e0f0 into a task, func_0024e1d0 back out) through the current
 * task's stacks in D_0046A03C ... D_0046A048.  Each slot has three entry
 * points in tables D_00469FF8 (func_0024b508 + slot: run its next step),
 * D_00469FD8 (func_0024b2c8 + slot: call into it) and D_0046A018
 * (func_0024b610 + slot: free it).  "Cooperative tasks" is read from the
 * code; not proved by a boot. */
#include "common.h"
#include "data/data_0046.h"
#include "data/pieces/D_002C5968.h"

/* A task (0x28 bytes). */
typedef struct {
    void *unk0;     /* its run entry */
    void *unk4;     /* its free entry */
    s32 unk8;       /* its call entry */
    u8 *unkC;       /* the stack block, 16-aligned */
    u8 *unk10;
    u8 *unk14;
    s32 unk18;      /* the group (stack size) */
    void *unk1C;    /* runs */
    s32 unk20;      /* its slot */
    void *unk24;    /* freed with the task when set */
} Task;
/* The same task read as words: func_0024b228, func_0024b448 and
 * func_0024b6d0 load the stacks as s32 (a union member would change the
 * alias set and func_0024b7a0's order). */
typedef struct { s32 unk0, unk4, unk8, unkC, unk10, unk14, unk18, unk1C; } TaskW;

extern Task *D_00669A18[8]; /* src/data/bss_0066.c: s32 D_00669A18[8] */
extern TaskW *D_0046A038;
extern s32 D_0046A03C;
extern s32 D_0046A040;
extern u8 *D_0046A044;
extern void *D_00469FF8[];
extern s32 D_00469FD8[];
extern void *D_0046A018[];

void free(void *);
void *malloc(u32);
void func_0024b1e8(const char *, const char *, s32);
void func_0024b1f0(void);
void func_0024e0a4(void);
void func_0024e0f0(s32, s32, s32);
void func_0024e1d0(void);

void func_0024b228(s32 i, s32 a, s32 b, s32 c) {
    TaskW *p = (TaskW *)D_00669A18[i];
    s32 o40, o48, t10, t18;
    D_0046A03C = p->unkC;
    o40 = D_0046A040;
    o48 = D_0046A048;
    t10 = p->unk10;
    (*(s32 *)&D_0046A044) = p->unk14;
    t18 = p->unk18;
    D_0046A040 = t10;
    D_0046A048 = t18;
    func_0024e0f0(a, b, c);
    D_0046A040 = o40;
    D_0046A048 = o48;
}

void func_0024b2c8(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(0, arg0, arg1, arg2);
}

void func_0024b2f8(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(1, arg0, arg1, arg2);
}

void func_0024b328(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(2, arg0, arg1, arg2);
}

void func_0024b358(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(3, arg0, arg1, arg2);
}

void func_0024b388(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(4, arg0, arg1, arg2);
}

void func_0024b3b8(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(5, arg0, arg1, arg2);
}

void func_0024b3e8(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(6, arg0, arg1, arg2);
}

void func_0024b418(s32 arg0, s32 arg1, s32 arg2) {
    func_0024b228(7, arg0, arg1, arg2);
}

void func_0024b448(s32 i) {
    s32 o40, o48, t10, t18;
    TaskW *p;
    o40 = D_0046A040;
    o48 = D_0046A048;
    switch ((*(volatile Sema_2c5968 *)&D_002C5968).mode) { default: return; case 0: break; }
    p = (TaskW *)D_00669A18[i];
    D_0046A038 = p;
    D_0046A03C = p->unkC;
    t10 = p->unk10;
    (*(s32 *)&D_0046A044) = p->unk14;
    D_0046A040 = t10;
    t18 = p->unk18;
    D_0046A048 = t18;
    p->unk1C++;
    func_0024e1d0();
    D_0046A040 = o40;
    D_0046A048 = o48;
}

void func_0024b508(void) {
    func_0024b448(0);
}

void func_0024b520(void) {
    func_0024b448(1);
}

void func_0024b538(void) {
    func_0024b448(2);
}

void func_0024b550(void) {
    func_0024b448(3);
}

void func_0024b568(void) {
    func_0024b448(4);
}

void func_0024b580(void) {
    func_0024b448(5);
}

void func_0024b598(void) {
    func_0024b448(6);
}

void func_0024b5b0(void) {
    func_0024b448(7);
}

void func_0024b5c8(s32 i) {
    Task **pp = &D_00669A18[i];
    Task *t = *pp;
    if (t->unk24 != 0) {
        free(t);
    }
    *pp = NULL;
}

void func_0024b610(void) {
    func_0024b5c8(0);
}

void func_0024b628(void) {
    func_0024b5c8(1);
}

void func_0024b640(void) {
    func_0024b5c8(2);
}

void func_0024b658(void) {
    func_0024b5c8(3);
}

void func_0024b670(void) {
    func_0024b5c8(4);
}

void func_0024b688(void) {
    func_0024b5c8(5);
}

void func_0024b6a0(void) {
    func_0024b5c8(6);
}

void func_0024b6b8(void) {
    func_0024b5c8(7);
}

void func_0024b6d0(TaskW *p, s32 a, s32 b, s32 c) {
    s32 o40, o48, t10, t18;
    D_0046A03C = p->unkC;
    o40 = D_0046A040;
    o48 = D_0046A048;
    t10 = p->unk10;
    (*(s32 *)&D_0046A044) = p->unk14;
    t18 = p->unk18;
    D_0046A040 = t10;
    D_0046A048 = t18;
    func_0024e0f0(a, b, c);
    D_0046A040 = o40;
    D_0046A048 = o48;
}

void func_0024b760(s32 a, s32 b, s32 c) {
    func_0024e0f0(a, b, c);
}

s32 func_0024b778(s32 n) {
    s32 a = n * 32;
    a += n * 0x10320;
    return (a + 1511) & ~63;
}

Task *func_0024b7a0(s32 grp, Task *t, void *arg) {
    u8 *a, *b, *c;
    s32 i, off;
    u8 *s40;
    s32 s48;
    off = grp * 0x10320;
    s40 = (u8 *)D_0046A040;
    s48 = D_0046A048;
    a = (u8 *)t + 40;
    if ((u32)a & 15) a = a - ((u32)a & 15) + 16;
    t->unkC = a;
    for (i = 0; i < 8; i++) if (D_00669A18[i] == NULL) break;
    if (i == 8) func_0024b1e8("i!=TASK_GRUPE_MAX", "src/sa_task.c", 257);
    b = a + off;
    c = b + 0x370;
    t->unk20 = i;
    t->unkC = a;
    (*(u8 **)&D_0046A03C) = a;
    t->unk10 = b;
    D_0046A040 = (s32)b;
    t->unk14 = c;
    D_0046A044 = c;
    t->unk18 = grp;
    D_0046A048 = grp;
    t->unk0 = D_00469FF8[i];
    t->unk8 = D_00469FD8[i];
    t->unk4 = D_0046A018[i];
    t->unk24 = arg;
    D_00669A18[i] = t;
    t->unk1C = NULL;
    func_0024e0a4();
    D_0046A040 = (s32)s40;
    D_0046A048 = s48;
    return t;
}

void func_0024b958(s32 grp) {
    func_0024b7a0(grp, malloc(func_0024b778(grp)), (void *)1);
}

void func_0024b990(void) {
    func_0024b1f0();
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
void *D_00469FF8[0x8] ALIGNED(8) = {
    (void *)func_0024b508, (void *)func_0024b520, (void *)func_0024b538, (void *)func_0024b550,
    (void *)func_0024b568, (void *)func_0024b580, (void *)func_0024b598, (void *)func_0024b5b0,
};
s32 D_00469FD8[0x8] ALIGNED(8) = {
    (s32)func_0024b2c8, (s32)func_0024b2f8, (s32)func_0024b328, (s32)func_0024b358,
    (s32)func_0024b388, (s32)func_0024b3b8, (s32)func_0024b3e8, (s32)func_0024b418,
};
void *D_0046A018[0x8] ALIGNED(8) = {
    (void *)func_0024b610, (void *)func_0024b628, (void *)func_0024b640, (void *)func_0024b658,
    (void *)func_0024b670, (void *)func_0024b688, (void *)func_0024b6a0, (void *)func_0024b6b8,
};
