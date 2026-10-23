/* The script's sound commands (docs/modules.md "Session 35"), 0x001e7e78-0x001e92b8.
 *
 * VM library entries (D_003D9FE0 1980-2019) over the sound layer at
 * 0x0011c7a8-0x0011ec08: play / stop / fade the two music tracks
 * (func_0011c7a8 / func_0011c7d8 with the track D_006314D4), load and start
 * a sequence or a sound bank by number (func_0011eae0 / func_0011ea40 name
 * the file, func_00120748 loads it into D_00F20000 or the bank buffer
 * D_003DABD4, func_0011ec08 / func_0011eb88 start it with the counters
 * D_006314CC-D_006314DC), wait for the IOP (func_0011e340, else retry
 * through func_0011ef10), the effect volumes and pans (func_0011c7c0 ...
 * func_0011d350; positions in D_006314E0), and the event sound effects
 * "eventse/%s_%03d.dat" (func_001e8f68, the bank number in D_00631560).
 * Each request sets a bit of D_00389C90.f3070 that its done callback
 * clears (func_001e7fe0 bit 56, func_001e8308 bit 51, func_001e8628 bit 57,
 * func_001e8e38 bit 55) and the wait commands test (D_0038CD00). */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/vm_mgr.h"
#include "vm/vm_sub.h"
#include "data/bss_0063.h"
#include "data/data_003D.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_003DABD4.h"

extern VmMgr D_00389C90;
extern u64 D_0038CD00;
extern volatile s32 D_002C5958;
extern volatile s32 D_002C58C0;
extern s32 D_002C1364;
extern char D_004908C8[];   /* "eventse/%s_%03d.dat" */
extern u8 D_00F20000[];

int sprintf(char *, const char *, ...);
void func_00101728(s32);
void func_0011c7a8(s32, s32, s32, s32, s32, s32);
void func_0011c7c0(s32, s32, s32);
void func_0011c7d8(s32);
void func_0011c7f0(s32);
s32 func_0011c808(s32);
s32 func_0011c820(void);
void func_0011c9a0(void);
void func_0011c9b0(void);
s32 func_0011cdf0();
void func_0011d080(s32, s32);
void func_0011d0d8(s32, s32);
void func_0011d108(s32, s32, s32);
void func_0011d2a0(s32, s32, f32 *, s32);
void func_0011d350(s32, s32);
void func_0011d448(void);
void func_0011d588(void);
void func_0011d688(s32);
s32 func_0011e340(s32);
s32 func_0011e368(s32, s32);
void func_0011e518(void);
void func_0011e528(void);
void func_0011e9a8(void *, void *);
void func_0011e9d8(s32, s32, void *, void *);
void func_0011ea40(s32, void *);
void func_0011eae0(s32, void *);
void func_0011eb88(s32, void *, s32, void *);
void func_0011ec08(s32, void *, s32, void *);
s32 func_0011ef10(s32, void *);
void func_00120748(void *, void *, void *, s32);
s32 func_00123158(s32, s32);
void func_00146928(s32);
void func_001557b0(s32);
void func_001557d0(void);
void func_00155878(void);

void func_001e7e78(void);
s32 func_001e7ea8(VmRec *vm);
s32 func_001e7f08(VmRec *vm);
void func_001e7fe0(void);
s32 func_001e8010(void);
void func_001e8060(s32 arg0);
s32 func_001e80d0(VmRec *vm);
s32 func_001e8178(void);
void func_001e81c8(s32 arg0);
s32 func_001e8238(VmRec *vm);
s32 func_001e82e0(VmRec *vm);
void func_001e8308(void);
s32 func_001e8338(void);
void func_001e8388(s32 arg0);
s32 func_001e83f8(VmRec *vm);
s32 func_001e84a0(void);
void func_001e84f0(s32 arg0);
s32 func_001e8560(VmRec *vm);
s32 func_001e8608(VmRec *vm);
void func_001e8628(void);
s32 func_001e8658(void);
void func_001e86a0(void);
s32 func_001e86e8(void);
void func_001e8728(void);
s32 func_001e8770(void);
s32 func_001e87b8(void);
s32 func_001e8800(VmRec *vm);
s32 func_001e88e0(VmRec *vm);
s32 func_001e89c0(VmRec *vm);
s32 func_001e89e0(void);
s32 func_001e8a10(void);
s32 func_001e8a30(void);
s32 func_001e8a50(VmRec *vm);
s32 func_001e8b08(VmRec *vm);
s32 func_001e8b50(VmRec *vm);
s32 func_001e8bc0(VmRec *vm);
s32 func_001e8bd8(VmRec *vm);
s32 func_001e8c88(VmRec *vm);
s32 func_001e8cf0(VmRec *vm);
s32 func_001e8d40(VmRec *vm);
s32 func_001e8da0(VmRec *vm);
s32 func_001e8de8(VmRec *vm);
void func_001e8e38(void);
s32 func_001e8e68(void);
s32 func_001e8ed8(s32 a0, s32 a1, s32 a2);
s32 func_001e8f68(VmRec *vm);
s32 func_001e9028(void);
s32 func_001e9048(VmRec *vm);
s32 func_001e90c8(void);
s32 func_001e90d0(VmRec *vm);
s32 func_001e9108(VmRec *vm);
s32 func_001e9150(void);
s32 func_001e9170(void);
s32 func_001e9190(void);
s32 func_001e91c0(void);
s32 func_001e91f0(VmRec *vm);
s32 func_001e9238(void);
s32 func_001e9288(void);

/* The effect positions (func_001e8bd8). */
f32 D_006314E0[0x8][4] ALIGNED(32);

void func_001e7e78(void) {
    func_0011c7a8(D_006314D4, 0, 0x3000, 0, 0, 0);
}

s32 func_001e7ea8(VmRec *vm) {
    D_006314D4 = vm->stk[vm->sp] - 1;
    func_0011c7d8(D_002C1364);
    func_001e7e78();
    vm->sp--;
    return 2;
}

s32 func_001e7f08(VmRec *vm) {
    VmSub *s = (VmSub *)&vm->obj;
    s32 *p = &D_006314D4;
    s32 i = vm->sp;
    s32 a = s->stk[i - 2], b = s->stk[i - 1], c = s->stk[i];
    s32 t, n;
    *p = a - 1;
    t = (f32)(b * 0x3000) / 100.0f;
    n = c * 8;
    func_0011c7d8(D_002C1364);
    func_0011c7a8(*p, 0, t, n, 0, 0);
    vm->sp -= 3;
    return 2;
}

void func_001e7fe0(void) {
    D_00389C90.f3070.x &= ~0x0100000000000000ULL;
}

s32 func_001e8010(void) {
    if (func_0011e340(0) == 0) {
        func_0011ec08(D_006314D0, D_00F20000, D_006314D8, func_001e7fe0);
        return 4;
    }
    return 0;
}

void func_001e8060(s32 arg0) {
    D_006314D8 = arg0;
    if (func_0011e340(0) == 0) {
        func_0011ec08(D_006314D0, D_00F20000, D_006314D8, func_001e7fe0);
        return;
    }
    func_0011ef10(0xC352, func_001e8010);
}

s32 func_001e80d0(VmRec *vm) {
    s32 buf[64];
    VmSub *s = (VmSub *)&vm->obj;
    s32 i;
    func_0011eae0(s->stk[vm->sp], buf);
    func_00120748(buf, D_00F20000, func_001e8060, 0);
    D_00389C90.f3070.x |= 0x8000LL << 41;
    i = vm->sp;
    D_006314D0 = s->stk[i - 1] - 1;
    vm->sp = i - 2;
    return 2;
}

s32 func_001e8178(void) {
    if (func_0011e340(0)) return 0;
    func_0011ec08(D_006314D0, D_003DABD4, D_006314D8, func_001e7fe0);
    return 4;
}

void func_001e81c8(s32 arg0) {
    D_006314D8 = arg0;
    if (func_0011e340(0) == 0) {
        func_0011ec08(D_006314D0, D_003DABD4, D_006314D8, func_001e7fe0);
        return;
    }
    func_0011ef10(0xC352, func_001e8178);
}

s32 func_001e8238(VmRec *vm) {
    s32 buf[64];
    VmSub *s = (VmSub *)&vm->obj;
    s32 i;
    func_0011eae0(s->stk[vm->sp], buf);
    func_00120748(buf, D_003DABD4, func_001e81c8, 0);
    D_00389C90.f3070.x |= 0x100000000000000LL;
    i = vm->sp;
    D_006314D0 = s->stk[i - 1] - 1;
    vm->sp = i - 2;
    return 2;
}

s32 func_001e82e0(VmRec *vm) {
    if ((s32)(D_0038CD00 >> 56) & 1) return 4;
    return 2;
}

void func_001e8308(void) {
    D_00389C90.f3070.x &= ~0x0008000000000000ULL;
}

s32 func_001e8338(void) {
    if (func_0011e340(0) == 0) {
        func_0011eb88(D_006314CC, D_00F20000, D_006314DC, func_001e8308);
        return 4;
    }
    return 0;
}

void func_001e8388(s32 arg0) {
    D_006314DC = arg0;
    if (func_0011e340(0) == 0) {
        func_0011eb88(D_006314CC, D_00F20000, D_006314DC, func_001e8308);
        return;
    }
    func_0011ef10(0xC352, func_001e8338);
}

s32 func_001e83f8(VmRec *vm) {
    s32 buf[64];
    VmSub *s = (VmSub *)&vm->obj;
    s32 i;
    func_0011ea40(s->stk[vm->sp], buf);
    func_00120748(buf, D_00F20000, func_001e8388, 0);
    D_00389C90.f3070.x |= 0x8000LL << 36;
    i = vm->sp;
    D_006314CC = s->stk[i - 1] - 1;
    vm->sp = i - 2;
    return 2;
}

s32 func_001e84a0(void) {
    if (func_0011e340(0)) return 0;
    func_0011eb88(D_006314CC, D_003DABD4, D_006314DC, func_001e8308);
    return 4;
}

void func_001e84f0(s32 arg0) {
    D_006314DC = arg0;
    if (func_0011e340(0) == 0) {
        func_0011eb88(D_006314CC, D_003DABD4, D_006314DC, func_001e8308);
        return;
    }
    func_0011ef10(0xC352, func_001e84a0);
}

s32 func_001e8560(VmRec *vm) {
    s32 buf[64];
    VmSub *s = (VmSub *)&vm->obj;
    s32 i;
    func_0011ea40(s->stk[vm->sp], buf);
    func_00120748(buf, D_003DABD4, func_001e84f0, 0);
    D_00389C90.f3070.x |= 0x8000LL << 36;
    i = vm->sp;
    D_006314CC = s->stk[i - 1] - 1;
    vm->sp = i - 2;
    return 2;
}

s32 func_001e8608(VmRec *vm) {
    if ((s32)(D_0038CD00 >> 51) & 1) return 4;
    return 2;
}

void func_001e8628(void) {
    D_00389C90.f3070.x &= ~0x0200000000000000ULL;
}

s32 func_001e8658(void) {
    if (func_0011e340(0) == 0) {
        func_0011e9a8(func_001e8628, D_00F20000);
        return 4;
    }
    return 0;
}

void func_001e86a0(void) {
    if (func_0011e340(0) == 0) {
        func_0011e9a8(func_001e8628, D_00F20000);
        return;
    }
    func_0011ef10(0xC352, func_001e8658);
}

s32 func_001e86e8(void) {
    if (func_0011e340(0) == 0) {
        func_0011e9a8(func_001e8628, D_003DABD4);
        return 4;
    }
    return 0;
}

void func_001e8728(void) {
    if (func_0011e340(0) == 0) {
        func_0011e9a8(func_001e8628, D_003DABD4);
        return;
    }
    func_0011ef10(0xC352, func_001e86e8);
}

s32 func_001e8770(void) {
    func_0011c7d8(D_006314D4);
    D_00389C90.f3070.x |= 0x8000LL << 42;
    func_001e86a0();
    return 2;
}

s32 func_001e87b8(void) {
    func_0011c7d8(D_006314D4);
    D_00389C90.f3070.x |= 0x8000LL << 42;
    func_001e8728();
    return 2;
}

s32 func_001e8800(VmRec *vm) {
    VmSub *s = (VmSub *)&vm->obj;
    s32 i = vm->sp;
    s32 a = s->stk[i - 1], c = s->stk[i];
    s32 t, n;
    t = (f32)(a * 0x3000) / 100.0f;
    n = c * 8;
    if (!func_0011e340(0)) {
        func_0011e9d8(t, n, func_001e8628, D_00F20000);
        D_00389C90.f3070.x |= 0x200000000000000LL;
        vm->sp -= 2;
        return 2;
    }
    return 4;
}

s32 func_001e88e0(VmRec *vm) {
    VmSub *s = (VmSub *)&vm->obj;
    s32 i = vm->sp;
    s32 a = s->stk[i - 1], c = s->stk[i];
    s32 t, n;
    t = (f32)(a * 0x3000) / 100.0f;
    n = c * 8;
    if (!func_0011e340(0)) {
        func_0011e9d8(t, n, func_001e8628, D_003DABD4);
        D_00389C90.f3070.x |= 0x200000000000000LL;
        vm->sp -= 2;
        return 2;
    }
    return 4;
}

s32 func_001e89c0(VmRec *vm) {
    if ((s32)(D_0038CD00 >> 57) & 1) return 4;
    return 2;
}

s32 func_001e89e0(void) {
    func_0011e518();
    func_0011c7d8(0);
    func_0011c7d8(1);
    return 2;
}

s32 func_001e8a10(void) {
    func_0011e518();
    return 2;
}

s32 func_001e8a30(void) {
    func_0011e528();
    return 2;
}

s32 func_001e8a50(VmRec *vm) {
    VmSub *s = (VmSub *)&vm->obj;
    s32 t;
    if (s->stk[vm->sp - 1] == 1) t = 1; else t = (f32)(s->stk[vm->sp - 1] * 0x3000) / 100.0f;
    if (16383 < t) t = 16383; else if (t < 0) t = 0;
    func_0011c7c0(s->stk[vm->sp - 2] - 1, t, s->stk[vm->sp] * 8);
    vm->sp -= 3;
    return 2;
}

s32 func_001e8b08(VmRec *vm) {
    func_0011c7f0(vm->stk[vm->sp] - 1);
    vm->sp--;
    return 2;
}

s32 func_001e8b50(VmRec *vm) {
    D_002C58C0 |= 0x8000;
    if (!func_0011c808(((VmSub *)&vm->obj)->stk[vm->sp] - 1)) return 4;
    vm->sp -= 1;
    return 2;
}

s32 func_001e8bc0(VmRec *vm) {
    vm->sp -= 4;
    return 2;
}

s32 func_001e8bd8(VmRec *vm) {
    VmSub *s = (VmSub *)&vm->obj;
    s32 flag;
    s32 i = vm->sp;
    f32 z;
    s32 a;
    flag = D_0037A378 & 1;
    D_006314E0[s->stk[i - 3]][0] = s->stk[i - 2];
    a = s->stk[i - 4];
    D_006314E0[s->stk[i - 3]][1] = s->stk[i - 1];
    z = s->stk[i];
    D_006314E0[s->stk[i - 3]][2] = z;
    if (!flag) {
        func_0011d2a0(a, s->stk[i - 3], D_006314E0[s->stk[i - 3]], 0);
        i = vm->sp;
    }
    vm->sp = i - 5;
    return 2;
}

s32 func_001e8c88(VmRec *vm) {
    VmSub *s = (VmSub *)&vm->obj;
    s32 i = vm->sp;
    s32 a = s->stk[i - 1], b = s->stk[i];
    if (!(D_0037A378 & 1)) {
        func_0011d080(a, b);
        i = vm->sp;
    }
    vm->sp = i - 2;
    return 2;
}

s32 func_001e8cf0(VmRec *vm) {
    VmSub *s = (VmSub *)&vm->obj;
    s32 i = vm->sp;
    func_0011d0d8(s->stk[i - 1], s->stk[i]);
    vm->sp -= 2;
    return 2;
}

s32 func_001e8d40(VmRec *vm) {
    VmSub *s = (VmSub *)&vm->obj;
    s32 i = vm->sp;
    func_0011d108(s->stk[i - 2], s->stk[i - 1], s->stk[i] * 8);
    vm->sp -= 3;
    return 2;
}

s32 func_001e8da0(VmRec *vm) {
    s32 r = func_0011e368(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    if (r != 0) return r = 4;
    return 2;
}

s32 func_001e8de8(VmRec *vm) {
    VmSub *s = (VmSub *)&vm->obj;
    s32 i = vm->sp;
    func_0011d350(s->stk[i - 1], s->stk[i]);
    vm->sp -= 2;
    return 2;
}

void func_001e8e38(void) {
    D_00389C90.f3070.x &= ~0x0080000000000000ULL;
}

s32 func_001e8e68(void) {
    if (func_0011e340(0) == 0) {
        func_00146928(-6);
        func_00146928(-7);
        D_002C5958 |= 0x40000;
        func_0011cdf0(-8, D_00631560, func_001e8e38, 0x40000);
        return 4;
    }
    return 0;
}

s32 func_001e8ed8(s32 a0, s32 a1, s32 a2) {
    D_00631560 = a2;
    if (func_0011e340(0) == 0) {
        func_00146928(-6);
        func_00146928(-7);
        D_002C5958 |= 0x40000;
        return func_0011cdf0(-8, D_00631560, func_001e8e38);
    }
    return func_0011ef10(0xc352, func_001e8e68);
}

s32 func_001e8f68(VmRec *vm) {
    char buf[512];
    if (!(D_0037A378 & 1)) {
        VmSub *s = (VmSub *)&vm->obj;
        sprintf(buf, D_004908C8, D_003DD290[s->stk[vm->sp - 1]], s->stk[vm->sp]);
        D_00389C90.f3070.x |= 0x80000000000000LL;
        func_00120748(buf, D_003DABD4, func_001e8ed8, 0);
    }
    vm->sp -= 2;
    return 2;
}

s32 func_001e9028(void) {
    return ((s32)(D_0038CD00 >> 55) & 1) ? 4 : 2;
}

s32 func_001e9048(VmRec *vm) {
    if (func_0011e340(0) == 0 && func_0011e368(-1, -1) == 0) {
        D_002C5958 &= ~0x40000;
        func_00155878();
        vm->fl.x |= 0x2000;
        return 6;
    }
    return 4;
}

s32 func_001e90c8(void) {
    return 2;
}

s32 func_001e90d0(VmRec *vm) {
    func_0011d588();
    vm->sp--;
    return 2;
}

s32 func_001e9108(VmRec *vm) {
    func_0011d688(vm->stk[vm->sp] * 8);
    vm->sp--;
    return 2;
}

s32 func_001e9150(void) {
    func_0011c9a0();
    return 2;
}

s32 func_001e9170(void) {
    func_0011c9b0();
    return 2;
}

s32 func_001e9190(void) {
    func_0011c9b0();
    func_00101728(0);
    func_0011d448();
    return 2;
}

s32 func_001e91c0(void) {
    if (func_0011e340(0) == 0) {
        func_001557d0();
        return 2;
    }
    return 4;
}

s32 func_001e91f0(VmRec *vm) {
    func_001557b0(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001e9238(void) {
    s32 r = func_00123158((s32)D_002E26A0[0], 0);
    while (r) r = func_00123158((s32)D_002E26A0[0], r);
    return 2;
}

s32 func_001e9288(void) {
    return func_0011c820() ? 4 : 2;
}

