/* A small stack VM: the bytecode interpreter func_0013cfe8(vm, cb, arg)
 * and its stack helpers (push func_0013cec8, pop func_0013cf28, peek
 * func_0013cf78, drop func_0013cfc0).  The script threads of 0x0012
 * (func_0012ba48) run it on their nodes; native calls go through the
 * tables at vm->nat (op 11).  Flag mode: nostrict. */
#include "common.h"

typedef struct {
    void (*fn)(s32 *);
    u16 n;
    u16 fl;
} SVmNat;

typedef struct {
    u16 *pc;
    s32 *fp;
    u32 *sp;
    s32 base;
    SVmNat **nat;
} SVm;

void *memcpy(void *, const void *, u32);

void func_0013cec8(SVm *q, void *src, u32 n) {
    memcpy(q->sp, src, n);
    q->sp += n >> 2;
    *q->sp++ = n;
}

u32 func_0013cf28(SVm *q, void *dst) {
    u32 n = *--q->sp;
    q->sp -= n >> 2;
    memcpy(dst, q->sp, n);
    return n;
}

u32 func_0013cf78(SVm *q, void *dst) {
    u32 *sp = q->sp;
    u32 n = sp[-1];
    memcpy(dst, (u8 *)sp - (n >> 2) * 4 - 4, n);
    return n;
}

u32 func_0013cfc0(SVm *q) {
    u32 n = *--q->sp;
    q->sp -= n >> 2;
    return n;
}

s32 func_0013cfe8(SVm *vm, void (*cb)(void *), void *arg)
{
    union {
        s32 i[4];
        f32 f[4];
    } t;
    s32 args[16];
    s32 b;
    s32 op;
    s32 n;
    s32 i;
    SVmNat *e;

    for (;;) {
        op = *vm->pc++;
        switch (op & 0xf) {
        case 0:
            switch ((u16)op >> 8) {
            case 0:
                return 0;
            case 3:
                vm->pc = (u16 *)*--vm->fp;
                if (vm->pc == NULL) {
                    return -1;
                }
                op = *--vm->fp;
                vm->fp -= op;
                break;
            case 4:
                func_0013cf28(vm, t.i);
                break;
            case 5:
                func_0013cf28(vm, t.i);
                t.f[1] = t.i[0];
                func_0013cec8(vm, &t.i[1], 4);
                break;
            case 6:
                func_0013cf28(vm, t.i);
                t.i[1] = t.f[0];
                func_0013cec8(vm, &t.i[1], 4);
                break;
            case 7:
                op = func_0013cfc0(vm);
                b = (s32)vm->sp;
                func_0013cf28(vm, t.i);
                memcpy((void *)t.i[0], (void *)b, op);
                break;
            case 8:
                return -1;
            case 9:
                func_0013cf28(vm, t.i);
                t.i[1] = -t.i[0];
                func_0013cec8(vm, &t.i[1], 4);
                break;
            case 10:
                func_0013cf28(vm, t.i);
                t.f[1] = -t.f[0];
                func_0013cec8(vm, &t.i[1], 4);
                break;
            case 11:
                func_0013cf28(vm, t.i);
                t.i[1] = ~t.i[0];
                func_0013cec8(vm, &t.i[1], 4);
                break;
            case 12:
                n = func_0013cf78(vm, t.i);
                func_0013cec8(vm, t.i, n);
                break;
            case 1:
                func_0013cf28(vm, t.i);
                t.i[1] = t.i[0] < 0 ? -t.i[0] : t.i[0];
                func_0013cec8(vm, &t.i[1], 4);
                break;
            case 2:
                func_0013cf28(vm, t.i);
                t.f[1] = __builtin_fabsf(t.f[0]);
                func_0013cec8(vm, &t.i[1], 4);
                break;
            case 13:
                func_0013cf28(vm, t.i);
                t.i[1] = !t.i[0];
                func_0013cec8(vm, &t.i[1], 4);
                break;
            }
            break;
        case 1:
            func_0013cf28(vm, &t.i[1]);
            func_0013cf28(vm, t.i);
            switch (((u16)op >> 4) & 3) {
            case 0:
                switch ((u16)op >> 8) {
                case 0: t.i[2] = t.i[0] + t.i[1]; break;
                case 1: t.i[2] = t.i[0] - t.i[1]; break;
                case 2: t.i[2] = t.i[0] * t.i[1]; break;
                case 3: t.i[2] = t.i[0] / t.i[1]; break;
                case 4: t.i[2] = t.i[0] % t.i[1]; break;
                case 5: t.i[2] = t.i[0] & t.i[1]; break;
                case 6: t.i[2] = t.i[0] | t.i[1]; break;
                case 7: t.i[2] = t.i[0] ^ t.i[1]; break;
                case 8: t.i[2] = t.i[0] << t.i[1]; break;
                case 9: t.i[2] = t.i[0] >> t.i[1]; break;
                case 10: t.i[2] = t.i[0] && t.i[1]; break;
                case 11: t.i[2] = t.i[0] || t.i[1]; break;
                }
                break;
            case 1:
                switch ((u16)op >> 8) {
                case 0: t.f[2] = t.f[0] + t.f[1]; break;
                case 1: t.f[2] = t.f[0] - t.f[1]; break;
                case 2: t.f[2] = t.f[0] * t.f[1]; break;
                case 3: t.f[2] = t.f[0] / t.f[1]; break;
                }
                break;
            }
            func_0013cec8(vm, &t.i[2], 4);
            break;
        case 4:
            op = (s16)*vm->pc++;
            vm->pc += op;
            break;
        case 5:
            op = (s16)*vm->pc++;
            func_0013cf28(vm, t.i);
            if (t.i[0] == 0) {
                vm->pc += op;
            }
            break;
        case 6:
            op = (s16)*vm->pc++;
            func_0013cf28(vm, t.i);
            if (t.i[0] != 0) {
                vm->pc += op;
            }
            break;
        case 2:
            switch (((u16)op >> 4) & 3) {
            case 0:
            case 1:
                func_0013cec8(vm, vm->pc, 4);
                vm->pc += 2;
                break;
            case 2:
                switch (((u16)op >> 6) & 3) {
                case 0: t.i[0] = (s32)vm->fp; break;
                case 1: t.i[0] = vm->base; break;
                case 2: t.i[0] = *vm->fp; break;
                case 3: t.i[0] = (s32)vm->pc; break;
                }
                t.i[0] += (s16)*vm->pc++;
                func_0013cec8(vm, t.i, 4);
                break;
            case 3:
                switch (((u16)op >> 6) & 3) {
                case 0: b = (s32)vm->fp; break;
                case 1: b = vm->base; break;
                case 2: b = *vm->fp; break;
                }
                b += *vm->pc++;
                func_0013cec8(vm, (void *)b, ((u16)op >> 8) * 4);
                break;
            }
            break;
        case 3:
            switch (((u16)op >> 6) & 3) {
            case 0: b = (s32)vm->fp; break;
            case 1: b = vm->base; break;
            case 2: b = *vm->fp; break;
            }
            b += *vm->pc++;
            func_0013cf28(vm, (void *)b);
            break;
        case 7:
            func_0013cf28(vm, t.i);
            switch (((u16)op >> 4) & 3) {
            case 0:
                switch ((u16)op >> 8) {
                case 0: t.i[1] = t.i[0] < 0; break;
                case 1: t.i[1] = t.i[0] <= 0; break;
                case 2: t.i[1] = t.i[0] == 0; break;
                case 3: t.i[1] = t.i[0] != 0; break;
                case 4: t.i[1] = t.i[0] >= 0; break;
                case 5: t.i[1] = t.i[0] > 0; break;
                }
                break;
            case 1:
                switch ((u16)op >> 8) {
                case 0: t.i[1] = t.f[0] < 0.0f; break;
                case 1: t.i[1] = t.f[0] <= 0.0f; break;
                case 2: t.i[1] = t.f[0] == 0.0f; break;
                case 3: t.i[1] = t.f[0] != 0.0f; break;
                case 4: t.i[1] = t.f[0] >= 0.0f; break;
                case 5: t.i[1] = t.f[0] > 0.0f; break;
                }
                break;
            }
            func_0013cec8(vm, &t.i[1], 4);
            break;
        case 8:
            {
                s32 k = (u16)op >> 8;
                op = (s16)*vm->pc++;
                vm->fp += k;
                *vm->fp++ = k;
                *vm->fp++ = (s32)vm->pc;
                vm->pc += op;
            }
            break;
        case 9:
            n = func_0013cf28(vm, t.i);
            t.i[0] += ((u16)op >> 8) * 4;
            func_0013cec8(vm, t.i, n);
            break;
        case 10:
            func_0013cf28(vm, &b);
            func_0013cec8(vm, (void *)b, ((u16)op >> 8) * 4);
            break;
        case 11:
            e = &vm->nat[((u16)op >> 6) & 3][(u16)op >> 8];
            n = e->n;
            for (i = 0; i < n; i++) {
                func_0013cf28(vm, &args[n - 1 - i]);
            }
            e->fn(args);
            if (*(u32 *)&e->n & 0x40000000) {
                func_0013cec8(vm, args, 4);
            }
            break;
        }
        if (cb != NULL) {
            cb(arg);
        }
    }
}
