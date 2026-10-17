#include "common.h"
typedef struct {
    s32 x0;
    void *ent;
    u8 pad8[0x68];
    s32 code;
    u8 pad74[8];
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    u64 flags;
} VM;
typedef struct { u8 st[4]; u8 x4[12]; u16 tbl[8][256]; s32 cnt[8]; s8 ids[4]; u8 pad1034[0x3070 - 0x1034]; union { u64 x; s32 i[2]; } f3070; union { u64 x; s32 i[2]; } f3078; } Str;
extern Str D_00389C90;
extern s32 D_00389C80;
extern char *D_00388480[];
typedef struct { u64 d[22]; } Win;
extern Win D_00629E70[];
extern s32 D_0037A378;
void func_0010ef70(Win *, char *, void *);
s32 func_001cbd80();
extern u8 D_003C5650[];
extern char D_0062A1F0[];

s32 func_001cb7d0(VM *vm) {
    s32 val = vm->stk[vm->sp];
    s32 idx = vm->stk[vm->sp - 1];
    s32 n, i, j, d, q;
    vm->sp -= 2;
    n = 1;
    for (d = val / 10; d > 0; d /= 10) n++;
    for (i = 0; i < n; i++) {
        d = 1;
        for (j = 0; j < n - 1 - i; j++) d *= 10;
        q = val / d;
        D_0062A1F0[i] = q + 33;
        val -= q * d;
    }
    for (j = 0; (u32)j < 12; j++) D_0062A1F0[i++] = D_003C5650[j];
    D_00388480[D_00389C80] = D_0062A1F0;
    D_00389C90.tbl[idx][D_00389C90.cnt[idx]++] = *(u16 *)&D_00389C80;
    D_00389C80++;
    return 2;
}

s32 func_001cb960(VM *vm) {
    s32 idx, v, i;
    if (D_0037A378 & 1) { vm->sp -= 2; return 2; }
    idx = vm->stk[vm->sp - 1];
    v = vm->stk[vm->sp];
    vm->sp -= 2;
    D_00389C90.tbl[idx][D_00389C90.cnt[idx]++] = v;
    for (i = 0; i < 4; i++) if (idx == D_00389C90.ids[i]) break;
    if (i < 4) {
        if (D_00389C90.st[i] == 4) {
            D_00389C90.st[i] = 2;
            D_00389C90.x4[idx] = 2;
            func_0010ef70(&D_00629E70[i], D_00388480[v], func_001cbd80);
        }
    }
    return 2;
}

extern Win D_006298F0[];
void func_0010bdd0(Win *, void *);
s32 func_001cbab0();
s32 func_001cbbd0(VM *vm) {
    s32 idx, i;
    if (D_0037A378 & 1) { vm->sp--; return 2; }
    idx = vm->stk[vm->sp];
    for (i = 0; i < 4; i++) if (D_00389C90.st[i] == 0) break;
    if (i >= 4 || D_00389C90.x4[idx] != 0) return 4;
    vm->sp--;
    D_00629E70[i] = D_006298F0[idx];
    D_00389C90.ids[i] = idx;
    func_0010bdd0(&D_00629E70[i], func_001cbab0);
    D_00389C90.st[i] = 1;
    D_00389C90.x4[idx] = 1;
    return 2;
}

s32 func_001cbea0();
s32 func_001cbfc0(VM *vm) {
    s32 idx, i;
    if (D_0037A378 & 1) { vm->sp--; return 2; }
    idx = vm->stk[vm->sp];
    for (i = 0; i < 4; i++) if (D_00389C90.st[i] == 0) break;
    if (i >= 4 || D_00389C90.x4[idx] != 0) return 4;
    vm->sp--;
    D_00629E70[i] = D_006298F0[idx];
    D_00389C90.ids[i] = idx;
    func_0010bdd0(&D_00629E70[i], func_001cbea0);
    D_00389C90.st[i] = 1;
    D_00389C90.x4[idx] = 1;
    return 2;
}

extern void *D_003DABD0[];
extern char D_003C58E0[][256];
void *func_001559f0(s32, s32);
void func_00120748(char *, void *, void *, s32);
s32 func_001cf348();
s32 func_001cf3e0();
s32 func_001cf478(VM *vm) {
    switch (vm->stk[vm->sp - 1]) {
    case 1:
        D_003DABD0[0] = func_001559f0(52, 4);
        func_00120748(D_003C58E0[vm->stk[vm->sp]], D_003DABD0[vm->stk[vm->sp - 1] - 1], func_001cf348, 0);
        D_00389C90.f3070.x |= 0x200000000ULL;
        break;
    case 2:
        D_003DABD0[1] = func_001559f0(56, 4);
        func_00120748(D_003C58E0[vm->stk[vm->sp]], D_003DABD0[vm->stk[vm->sp - 1] - 1], func_001cf3e0, 0);
        D_00389C90.f3070.x |= 0x400000000ULL;
        break;
    }
    vm->sp -= 2;
    return 2;
}

extern char D_003D97E0[][256];
s32 func_001cf5d0(VM *vm) {
    switch (vm->stk[vm->sp - 1]) {
    case 1:
        D_003DABD0[0] = func_001559f0(52, 4);
        func_00120748(D_003D97E0[vm->stk[vm->sp]], D_003DABD0[vm->stk[vm->sp - 1] - 1], func_001cf348, 0);
        D_00389C90.f3070.x |= 0x200000000ULL;
        break;
    case 2:
        D_003DABD0[1] = func_001559f0(56, 4);
        func_00120748(D_003D97E0[vm->stk[vm->sp]], D_003DABD0[vm->stk[vm->sp - 1] - 1], func_001cf3e0, 0);
        D_00389C90.f3070.x |= 0x400000000ULL;
        break;
    }
    vm->sp -= 2;
    return 2;
}
