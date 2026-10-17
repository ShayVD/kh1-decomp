/* Leftover SDK runtime functions matched by hand (session s2), ee-gcc 2.96:
 * libgcc2's global constructor/destructor walkers and the frame.c unwind
 * table helpers that sit beside them. */
#include "common.h"

typedef void (*func_ptr)(void);
typedef struct { u32 length; s32 CIE_delta; u32 pc_begin; u32 pc_range; } fde;
#define next_fde(f) ((fde *)((char *)(f) + (f)->length + sizeof((f)->length)))
typedef struct { fde **array; u32 count; } fde_vec;
typedef struct { fde_vec linear; fde_vec erratic; } fde_accu;
/* Registered object: pc range, fde list or array, fde count, chain link. */
typedef struct Obj { u32 pc_begin; u32 pc_end; fde *fde_begin; fde **fde_array; u32 count; struct Obj *next; } Obj;
/* CIE info decoded by func_00264400. */
typedef struct { char *aug; void *eh; u32 code_align; s32 data_align; u32 ra; } CieInfo;
typedef union { void *p; u16 b2; u32 b4; } __attribute__((packed)) Unaligned;
/* Unwind state: cfa, eh pointer, cfa offset, two more offsets, per-register
 * save slots (123), cfa register, return-address column, per-register save
 * kinds, and a flag. The internal form adds the remember-state chain. */
typedef struct { void *x0; void *eh; s64 q8; s64 q16; s64 q24; s64 reg[123]; u16 h; u16 ra; u8 saved[123]; u8 b; } CfaState;
typedef struct { CfaState s; void *saved; } CfaInternal;

void *malloc(u32);
void free(void *);
void *memset(void *, s32, u32);
void *memcpy(void *, const void *, u32);
fde *func_00264258(u32 pc);
u8 *func_00264630(u8 *insn, CfaInternal *st, CieInfo *info, u32 *loc);
void abort(void);
s32 strcmp(const char *, const char *);
u32 strlen(const char *);
void *func_00263ee8(void *);
void func_00263db8(void *, void *);
s32 func_002650e0(void (*)(void));
s32 func_00263fc8(fde *f);
void func_00264008(fde *f, fde_accu *accu, u32 *beg_ptr, u32 *end_ptr);
fde **func_00263840(fde_accu *a, u32 count);
u8 *func_002636a8(u8 *, u32 *);
u8 *func_002636f0(u8 *, s32 *);
extern func_ptr *D_0046C4DC;
extern s32 D_0046C4E0;
extern u8 D_00494040[];
extern u8 D_0066FAB0[];
extern func_ptr D_0049402C[];
extern char D_00492850[]; /* "" */
extern char D_00492858[]; /* "eh" */

static inline s32 fde_cmp(fde *x, fde *y) {
    return x->pc_begin - y->pc_begin;
}
CONTEXT_ONLY void func_00263748(fde_vec *v1, fde_vec *v2) {
    u32 i1, i2;
    fde *f2;
    i2 = v2->count;
    if (i2) {
        i1 = v1->count;
        do {
            i2--;
            f2 = v2->array[i2];
            while (i1 > 0 && fde_cmp(v1->array[i1 - 1], f2) > 0) {
                v1->array[i1 + i2] = v1->array[i1 - 1];
                i1--;
            }
            v1->array[i1 + i2] = f2;
        } while (i2);
        v1->count += v2->count;
    }
}

extern fde *D_0066FACC;

static inline void fde_split(fde_vec *linear, fde_vec *erratic) {
    u32 count = linear->count;
    fde **chain_end = &D_0066FACC;
    u32 i, j, k;
    for (i = 0; i < count; i++) {
        fde **probe;
        for (probe = chain_end; probe != &D_0066FACC && fde_cmp(linear->array[i], *probe) < 0; probe = chain_end) {
            chain_end = (fde **)erratic->array[probe - linear->array];
            erratic->array[probe - linear->array] = 0;
        }
        erratic->array[i] = (fde *)chain_end;
        chain_end = &linear->array[i];
    }
    for (i = j = k = 0; i < count; i++)
        if (erratic->array[i])
            linear->array[j++] = linear->array[i];
        else
            erratic->array[k++] = linear->array[i];
    linear->count = j;
    erratic->count = k;
}

#define SWAP(x, y) do { fde *tmp = x; x = y; y = tmp; } while (0)
static inline void frame_heapsort(fde_vec *erratic) {
    fde **a = erratic->array;
    u32 n = erratic->count;
    u32 m = n;
    u32 i;
    while (m > 0) {
        m--;
        for (i = m; 2 * i + 1 < n;) {
            if (2 * i + 2 < n && fde_cmp(a[2 * i + 2], a[2 * i + 1]) > 0 && fde_cmp(a[2 * i + 2], a[i]) > 0) {
                SWAP(a[i], a[2 * i + 2]);
                i = 2 * i + 2;
            } else if (fde_cmp(a[2 * i + 1], a[i]) > 0) {
                SWAP(a[i], a[2 * i + 1]);
                i = 2 * i + 1;
            } else
                break;
        }
    }
    while (n > 1) {
        n--;
        SWAP(a[0], a[n]);
        for (i = 0; 2 * i + 1 < n;) {
            if (2 * i + 2 < n && fde_cmp(a[2 * i + 2], a[2 * i + 1]) > 0 && fde_cmp(a[2 * i + 2], a[i]) > 0) {
                SWAP(a[i], a[2 * i + 2]);
                i = 2 * i + 2;
            } else if (fde_cmp(a[2 * i + 1], a[i]) > 0) {
                SWAP(a[i], a[2 * i + 1]);
                i = 2 * i + 1;
            } else
                break;
        }
    }
}
#undef SWAP

fde **func_00263840(fde_accu *accu, u32 count) {
    if (accu->linear.array && accu->linear.count != count) abort();
    if (accu->erratic.array) {
        fde_split(&accu->linear, &accu->erratic);
        if (accu->linear.count + accu->erratic.count != count) abort();
        frame_heapsort(&accu->erratic);
        func_00263748(&accu->linear, &accu->erratic);
        free(accu->erratic.array);
    } else {
        frame_heapsort(&accu->linear);
    }
    return accu->linear.array;
}

s32 WaitSema(s32);
s32 SignalSema(s32);
extern s32 D_0046AF14;
extern Obj *D_0066FAD0;

void *func_00263ee8(void *begin) {
    Obj **p;
    WaitSema(D_0046AF14);
    p = &D_0066FAD0;
    while (*p) {
        if ((*p)->fde_begin == begin) {
            Obj *ob = *p;
            *p = (*p)->next;
            if (ob->fde_array && ob->fde_array != begin)
                free(ob->fde_array);
            SignalSema(D_0046AF14);
            return ob;
        }
        p = &(*p)->next;
    }
    SignalSema(D_0046AF14);
    abort();
}

static inline s32 start_sort(fde_accu *a, u32 count) {
    a->linear.array = count ? (fde **)malloc(count * sizeof(fde *)) : 0;
    a->erratic.array = a->linear.array ? (fde **)malloc(count * sizeof(fde *)) : 0;
    a->linear.count = 0;
    a->erratic.count = 0;
    return a->linear.array != 0;
}

CONTEXT_ONLY fde *func_00264098(fde *f, u32 pc) {
    for (; f->length != 0; f = next_fde(f)) {
        if (f->CIE_delta == 0) continue;
        if (f->pc_begin == 0) continue;
        if (pc - f->pc_begin < f->pc_range) return f;
    }
    return 0;
}
CONTEXT_ONLY void func_002640f0(Obj *ob) {
    fde_accu accu;
    u32 beg_pc, end_pc;
    u32 count;
    fde **p;
    if (ob->pc_begin) {
        count = ob->count;
    } else {
        if (ob->fde_array) {
            fde **q = ob->fde_array;
            count = 0;
            while (*q) count += func_00263fc8(*q++);
        } else {
            count = func_00263fc8(ob->fde_begin);
        }
    }
    ob->count = count;
    if (!start_sort(&accu, count) && ob->pc_begin) return;
    beg_pc = -1;
    end_pc = 0;
    if (ob->fde_array) {
        for (p = ob->fde_array; *p; p++) func_00264008(*p, &accu, &beg_pc, &end_pc);
    } else {
        func_00264008(ob->fde_begin, &accu, &beg_pc, &end_pc);
    }
    {
        fde **r = func_00263840(&accu, count);
        if (r) ob->fde_array = r;
    }
    ob->pc_begin = beg_pc;
    ob->pc_end = end_pc;
}
fde *func_00264258(u32 pc) {
    Obj *ob;
    u32 lo, hi;
    WaitSema(D_0046AF14);
    for (ob = D_0066FAD0; ob; ob = ob->next) {
        if (ob->pc_begin == 0) func_002640f0(ob);
        if (pc >= ob->pc_begin && pc < ob->pc_end) break;
    }
    if (ob == 0) {
        SignalSema(D_0046AF14);
        return 0;
    }
    if (ob->fde_array == 0 || (fde *)ob->fde_array == ob->fde_begin) func_002640f0(ob);
    if (ob->fde_array && (fde *)ob->fde_array != ob->fde_begin) {
        SignalSema(D_0046AF14);
        for (lo = 0, hi = ob->count; lo < hi;) {
            u32 i = (lo + hi) / 2;
            fde *f = ob->fde_array[i];
            if (pc < f->pc_begin) hi = i;
            else if (pc >= f->pc_begin + f->pc_range) lo = i + 1;
            else return f;
        }
    } else {
        fde *f;
        if (ob->fde_array) {
            fde **p = ob->fde_array;
            do {
                f = func_00264098(*p, pc);
                if (f) break;
                p++;
            } while (*p);
        } else {
            f = func_00264098(ob->fde_begin, pc);
        }
        SignalSema(D_0046AF14);
        return f;
    }
    return 0;
}
