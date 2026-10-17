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
typedef struct { u32 pc_begin; u32 pc_end; fde *fde_begin; fde **fde_array; u32 count; void *next; } Obj;
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

static inline s32 start_sort(fde_accu *a, u32 count) {
    a->linear.array = count ? (fde **)malloc(count * sizeof(fde *)) : 0;
    a->erratic.array = a->linear.array ? (fde **)malloc(count * sizeof(fde *)) : 0;
    a->linear.count = 0;
    a->erratic.count = 0;
    return a->linear.array != 0;
}

void func_00262b28(void) {
    while (*D_0046C4DC) { D_0046C4DC++; (*(D_0046C4DC - 1))(); }
    if (D_0046C4E0 == 0) {
        D_0046C4E0 = 1;
        func_00263ee8(D_00494040);
    }
}

void func_00262bb8(void) {
    unsigned long nptrs;
    u32 i;
    func_00263db8(D_00494040, D_0066FAB0);
    nptrs = (unsigned long)D_0049402C[0];
    if (nptrs == (unsigned long)-1)
        for (nptrs = 0; D_0049402C[nptrs + 1] != 0; nptrs++);
    for (i = nptrs; i >= 1; i--) D_0049402C[i]();
    func_002650e0(func_00262b28);
}

void func_00263748(fde_vec *v1, fde_vec *v2) {
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

s32 func_00263fc8(fde *f) {
    s32 count = 0;
    for (; f->length != 0; f = next_fde(f)) {
        if (f->CIE_delta != 0 && f->pc_begin != 0) count++;
    }
    return count;
}

void func_00264008(fde *f, fde_accu *accu, u32 *beg_ptr, u32 *end_ptr) {
    u32 pc_begin = *beg_ptr;
    u32 pc_end = *end_ptr;
    for (; f->length != 0; f = next_fde(f)) {
        u32 pc;
        if (f->CIE_delta == 0) continue;
        pc = f->pc_begin;
        if (pc == 0) continue;
        if (accu->linear.array) accu->linear.array[accu->linear.count++] = f;
        if (pc < pc_begin) pc_begin = pc;
        if (pc + f->pc_range > pc_end) pc_end = pc + f->pc_range;
    }
    *beg_ptr = pc_begin;
    *end_ptr = pc_end;
}

fde *func_00264098(fde *f, u32 pc) {
    for (; f->length != 0; f = next_fde(f)) {
        if (f->CIE_delta == 0) continue;
        if (f->pc_begin == 0) continue;
        if (pc - f->pc_begin < f->pc_range) return f;
    }
    return 0;
}

void func_002640f0(Obj *ob) {
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

u8 *func_00264400(fde *f, CieInfo *c) {
    u8 *p;
    u32 n;
    c->aug = (char *)&f->CIE_delta - f->CIE_delta + 9;
    if (strcmp(c->aug, D_00492850) != 0 && strcmp(c->aug, D_00492858) != 0 && c->aug[0] != 'z') return 0;
    p = (u8 *)c->aug + strlen(c->aug) + 1;
    if (strcmp(c->aug, D_00492858) == 0) {
        c->eh = ((Unaligned *)p)->p;
        p += 4;
    } else {
        c->eh = 0;
    }
    p = func_002636a8(p, &c->code_align);
    p = func_002636f0(p, &c->data_align);
    c->ra = *p++;
    if (c->aug[0] == 'z') {
        p = func_002636a8(p, &n);
        p += n;
    }
    return p;
}

u8 *func_00264510(u8 *p, CfaState *s) {
    u32 op = *p++;
    s32 t;
    switch (op) {
    case 0x50 ... 0x6f:
        s->h = op - 0x50;
        break;
    case 0x90:
        p = func_002636f0(p, &t);
        s->h = t;
    case 0x70 ... 0x8f:
        s->h = op - 0x70;
        p = func_002636f0(p, &t);
        s->q16 = t;
        break;
    case 0x92:
        p = func_002636f0(p, &t);
        s->h = t;
        p = func_002636f0(p, &t);
        s->q16 = t;
        break;
    case 6:
        s->b = 1;
        break;
    case 0x23:
        p = func_002636a8(p, (u32 *)&t);
        s->q8 = t;
        break;
    default:
        abort();
    }
    return p;
}

u8 *func_00264630(u8 *insn, CfaInternal *st, CieInfo *info, u32 *loc) {
    u32 op = *insn++;
    s32 offset;
    u32 reg, reg2;
    u8 *end;
    CfaInternal *save;
    if (op & 0x40) {
        *loc += (op & 0x3f) * info->code_align;
    } else if (op & 0x80) {
        reg = op & 0x3f;
        insn = func_002636a8(insn, (u32 *)&offset);
        if (reg != st->s.h) {
            offset *= info->data_align;
            st->s.saved[reg] = 1;
            st->s.reg[reg] = offset;
        }
    } else if (op & 0xc0) {
        reg = op & 0x3f;
        st->s.saved[reg] = 0;
    } else {
        switch (op) {
        case 0:
            break;
        case 1:
            *loc = ((Unaligned *)insn)->b4;
            insn += 4;
            break;
        case 2:
            *loc += *insn;
            insn++;
            break;
        case 3:
            *loc += ((Unaligned *)insn)->b2;
            insn += 2;
            break;
        case 4:
            *loc += ((Unaligned *)insn)->b4;
            insn += 4;
            break;
        case 5:
            insn = func_002636a8(insn, &reg);
            insn = func_002636a8(insn, (u32 *)&offset);
            if (reg == st->s.h) break;
            offset *= info->data_align;
            st->s.saved[reg] = 1;
            st->s.reg[reg] = offset;
            break;
        case 6:
            insn = func_002636a8(insn, &reg);
            st->s.saved[reg] = 0;
            break;
        case 7:
        case 8:
            break;
        case 9:
            insn = func_002636a8(insn, &reg);
            insn = func_002636a8(insn, &reg2);
            st->s.saved[reg] = 2;
            st->s.reg[reg] = reg2;
            break;
        case 12:
            insn = func_002636a8(insn, &reg);
            insn = func_002636a8(insn, (u32 *)&offset);
            st->s.h = reg;
            st->s.q8 = offset;
            break;
        case 13:
            insn = func_002636a8(insn, &reg);
            st->s.h = reg;
            break;
        case 14:
            insn = func_002636a8(insn, (u32 *)&offset);
            st->s.q8 = offset;
            break;
        case 15:
            st->s.h = 0;
            st->s.q8 = 0;
            st->s.q16 = 0;
            st->s.b = 0;
            insn = func_002636a8(insn, (u32 *)&offset);
            end = insn + offset;
            while (insn < end) insn = func_00264510(insn, &st->s);
            break;
        case 10:
            {
                CfaInternal *n = (CfaInternal *)malloc(sizeof(CfaInternal));
                memcpy(n, st, sizeof(CfaInternal));
                st->saved = n;
            }
            break;
        case 11:
            {
                CfaInternal *o = st->saved;
                memcpy(st, o, sizeof(CfaInternal));
                free(o);
            }
            break;
        case 0x2d:
            for (reg = 16; reg < 32; ++reg) {
                st->s.saved[reg] = 1;
                st->s.reg[reg] = (reg - 16) * sizeof(void *);
            }
            break;
        case 0x2e:
            insn = func_002636a8(insn, (u32 *)&offset);
            st->s.q24 = offset;
            break;
        case 0x2f:
            insn = func_002636a8(insn, &reg);
            insn = func_002636a8(insn, (u32 *)&offset);
            offset *= info->data_align;
            st->s.saved[reg] = 1;
            st->s.reg[reg] = -offset;
            break;
        default:
            abort();
        }
    }
    return insn;
}

CfaState *func_00264a80(u32 target, CfaState *out) {
    fde *f;
    u8 *insn, *end;
    CieInfo info;
    CfaInternal st;
    u32 n, pc;
    f = func_00264258(target);
    if (f == 0) return 0;
    insn = func_00264400(f, &info);
    if (insn == 0) return 0;
    memset(&st, 0, sizeof st);
    st.s.ra = info.ra;
    st.s.eh = info.eh;
    {
        fde *cie = (fde *)((char *)&f->CIE_delta - f->CIE_delta);
        end = (u8 *)cie + cie->length + 4;
    }
    while (insn < end) insn = func_00264630(insn, &st, &info, 0);
    insn = (u8 *)(f + 1);
    if (info.aug[0] == 'z') {
        insn = func_002636a8(insn, &n);
        insn += n;
    }
    end = (u8 *)f + f->length + 4;
    pc = f->pc_begin;
    while (insn < end && pc <= target) insn = func_00264630(insn, &st, &info, &pc);
    *out = st.s;
    return out;
}
