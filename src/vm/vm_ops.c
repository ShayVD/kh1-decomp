/* The script VM's instruction handlers and their helpers, 0x001c08e8-0x001c1d20
 * (the first named module; docs/modules.md).
 *
 * D_0037A198 holds the 32 handlers the interpreter loop calls with
 * D_0037A198[op](vm, arg); 30 of them are here, in address order, with the
 * helpers they call (the variable clamp, the save block accessors) and the
 * script fetch functions.  The other two entries (func_001cd208, func_001dcad0)
 * live far away and stay where they are.
 *
 * Two functions here need flags of their own and are in the variant files
 * next to this one (docs/modules.md "Flags"): func_001c1718
 * (vm_ops.nosi.c) and func_001c1980 (vm_ops.nostrict.c). */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/script_vm.h"
#include "data/data_0038.h"
#include "data/data_003C.h"

void *func_00232cc0(s32);
VmRec *func_001e98d0(s32, s32);

/* func_001c4640's message (h66). */
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} VmMsg;
s32 func_001c4640(VmMsg *m);

/* op 0: nop */
s32 func_001c08e8(void) {
    return 2;
}

/* op 2: jump by `off` */
s32 func_001c08f0(VmRec *v, s32 off) {
    v->pc += off;
    return off < 0 ? 4 : 1;
}

/* op 3: pop; jump by `off` if it was 0 */
s32 func_001c0910(VmRec *v, s32 off) {
    if (v->stk[v->sp--] == 0) {
        v->pc += off;
        return off < 0 ? 4 : 1;
    }
    return 2;
}

/* op 4: nop */
s32 func_001c0960(void) {
    return 2;
}

/* op 6: pop into variable bank slot `i` (selects it) */
s32 func_001c0968(VmRec *v, s32 i) {
    v->x270[i] = v->stk[v->sp];
    v->x2f0 = i;
    v->sp--;
    return 2;
}

/* op 7: push (selected slot == x) */
s32 func_001c09a0(VmRec *v, s32 x) {
    v->sp++;
    if (v->x270[v->x2f0] == x) v->stk[v->sp] = 1;
    else v->stk[v->sp] = 0;
    return 2;
}

/* op 26: push (selected slot < x) */
s32 func_001c09e8(VmRec *v, s32 x) {
    v->sp++;
    if (v->x270[v->x2f0] < x) v->stk[v->sp] = 1;
    else v->stk[v->sp] = 0;
    return 2;
}

/* op 27: push (selected slot <= x) */
s32 func_001c0a38(VmRec *v, s32 x) {
    v->sp++;
    if (v->x270[v->x2f0] <= x) v->stk[v->sp] = 1;
    else v->stk[v->sp] = 0;
    return 2;
}

/* op 28: push (selected slot > x) */
s32 func_001c0a88(VmRec *v, s32 x) {
    v->sp++;
    if (v->x270[v->x2f0] > x) v->stk[v->sp] = 1;
    else v->stk[v->sp] = 0;
    return 2;
}

/* op 29: push (selected slot >= x) */
s32 func_001c0ad8(VmRec *v, s32 x) {
    v->sp++;
    if (v->x270[v->x2f0] >= x) v->stk[v->sp] = 1;
    else v->stk[v->sp] = 0;
    return 2;
}

/* op 8: select the previous slot */
s32 func_001c0b28(VmRec *v) {
    v->x2f0--;
    return 2;
}

/* op 5: return: drop this return level, resume at the next one set */
s32 func_001c0b40(VmRec *v) {
    s32 i;
    if (v->rsp == 7) {
        v->fl.x |= 8;
        return 4;
    }
    v->ret[v->rsp] = -1;
    for (i = v->rsp + 1; i < 8; i++) {
        s32 r = v->ret[i];
        if (r != -1) {
            v->pc = r;
            v->rsp = i;
            break;
        }
    }
    return 4;
}

s64 func_001c0bf0(s64 x, u32 type) {
    switch (type) {
    case 0:
    case 1:
        x &= 1;
    case 2:
        if (x < -128) x = -128;
        else if (x >= 127) x = 127;

        break;
    case 3:
        if (x < -32768) x = -32768;
        else if (x >= 32767) x = 32767;

        break;
    case 4:
        if (x < -0x800000) x = -0x800000;
        else if (x >= 0x7fffff) x = 0x7fffff;
        break;
    case 5:
        if (x < 0) x = 0;
        else if (x >= 255) x = 255;

        break;
    case 6:
        if (x < 0) x = 0;
        else if (x >= 0xffff) x = 0xffff;

        break;
    case 7:
        if (x < 0) x = 0;
        else if (x >= 0xffffff) x = 0xffffff;
        break;
    }
    return x;
}

/* op 9: push the argument clamped to s24 */
s32 func_001c0d20(VmRec *v, s32 arg) {
    s32 x = func_001c0bf0(arg, 4);
    v->stk[++v->sp] = x;
    return 2;
}

/* op 10: push register `i` */
s32 func_001c0d70(VmRec *v, s32 i) {
    v->sp++;
    v->stk[v->sp] = v->var[i];
    return 2;
}

void func_001c0da0(s32 off, s32 size, void *dst) {
    u8 *p = func_00232cc0(2);
    switch (size) {
    case 1: *(u8 *)dst = *(u8 *)(p + off); break;
    case 2: *(u16 *)dst = *(u16 *)(p + off); break;
    case 4: *(u32 *)dst = *(u32 *)(p + off); break;
    }
}

s32 func_001c0e50(s32 off) {
    return (s32)func_00232cc0(2) + off;
}

void func_001c0e80(s32 off, s32 size, void *src) {
    s32 p = (s32)func_00232cc0(2);
    switch (size) {
    case 1:
        *(s8 *)(p + off) = *(s32 *)src;
        return;
    case 2:
        *(s16 *)(p + off) = (u16)*(s32 *)src;
        break;
    case 4:
        *(s32 *)(p + off) = *(s32 *)src;
        break;
    }
}

/* op 12: push s8 variable `idx` */
s32 func_001c0f30(VmRec *v, s32 idx) {
    s8 *a = func_00232cc0(1);
    s8 *b = func_00232cc0(2);
    v->stk[32] = idx;
    if (idx < 0x800) {
        v->stk[++v->sp] = a[idx];
    } else if (idx < 0x900) {
        v->stk[++v->sp] = a[idx];
    } else if (idx < 0xb00) {
        idx -= 0x900;
        if ((s32)(v->fl.x >> 5) & 1) {
            v->stk[++v->sp] = D_0038B4C4[idx];
        } else {
            v->stk[++v->sp] = D_0038ACC4[idx];
        }
    } else if (idx < 0xc80) {
        v->stk[++v->sp] = *(u8 *)(idx + (u32)a - 0x200);
    } else if (idx < 0xcc0) {
        v->stk[++v->sp] = D_003C2D30[idx];
    } else if (idx < 0xd00) {
        v->stk[++v->sp] = D_003C2D30[idx];
    } else if (idx < 0xd40) {
        v->stk[++v->sp] = D_003C2D30[idx];
    } else {
        v->stk[++v->sp] = *(s8 *)(idx + (u32)b - 0xd40);
    }
    return 2;
}

/* op 14: push s16 variable `a` */
s32 func_001c1118(VmRec *v, s32 a) {
    u8 *p1 = func_00232cc0(1);
    u8 *p2 = func_00232cc0(2);
    s16 x;
    v->stk[32] = a;
    if (a < 2048) {
        v->sp++;
        v->stk[v->sp] = *(s16 *)(p1 + a);
        return 2;
    }
    if (a < 2304) {
        v->sp++;
        v->stk[v->sp] = *(s16 *)(a + (s32)p1);
    } else {
        v->sp++;
        v->stk[v->sp] = *(s16 *)(a + (s32)p2 - 3392);
    }
    return 2;
}

/* op 16: push s32 variable `a` */
s32 func_001c11d8(VmRec *v, s32 a) {
    u8 *p1 = func_00232cc0(1);
    u8 *p2 = func_00232cc0(2);
    v->stk[32] = a;
    if (a < 2048) {
        v->sp++;
        v->stk[v->sp] = *(s32 *)(p1 + a);
    } else if (a < 2304) {
        v->sp++;
        v->stk[v->sp] = *(s32 *)(a + (s32)p1);
    } else if (a < 2816) {
        a -= 2304;
        if ((s32)(v->fl.x >> 5) & 1) {
            v->sp++;
            v->stk[v->sp] = D_0038B4C4[a];
        } else {
            v->sp++;
            v->stk[v->sp] = D_0038ACC4[a];
        }
    } else {
        v->sp++;
        v->stk[v->sp] = *(s32 *)(a + (s32)p2 - 3392);
    }
    return 2;
}

/* op 18: nop */
s32 func_001c1318(void) {
    return 2;
}

/* op 19: nop */
s32 func_001c1320(void) {
    return 2;
}

/* op 20: nop */
s32 func_001c1328(void) {
    return 2;
}

/* op 30: push bit variable `a` */
s32 func_001c1330(VmRec *v, s32 a) {
    u8 *p1 = func_00232cc0(1);
    u8 *p2 = func_00232cc0(2);
    s32 bit = a % 8;
    s32 q = a / 8;
    a = q - 3392;
    v->stk[++v->sp] = (*(s8 *)(p2 + a) >> bit) & 1;
    return 2;
}

/* op 11: pop into register `i` */
s32 func_001c13b8(VmRec *v, s32 i) {
    v->var[i] = v->stk[v->sp--];
    return 2;
}

/* op 13: pop into s8 variable `idx` */
s32 func_001c13e8(VmRec *v, s32 idx) {
    s8 *a = func_00232cc0(1);
    s8 *b = func_00232cc0(2);
    if (idx < 0x800) {
        a[idx] = func_001c0bf0(v->stk[v->sp], 2);
        v->sp--;
    } else if (idx < 0x900) {
        idx -= 0x800;
        *(u8 *)(idx + (u32)a + 0x800) = func_001c0bf0(v->stk[v->sp], 2);
        v->sp--;
    } else if (idx < 0xb00) {
        idx -= 0x900;
        if ((s32)(v->fl.x >> 5) & 1) {
            D_0038B4C4[idx] = v->stk[v->sp];
            v->sp--;
        } else {
            D_0038ACC4[idx] = v->stk[v->sp];
            v->sp--;
        }
    } else if (idx < 0xc80) {
        *(u8 *)(idx + (u32)a - 0x200) = v->stk[v->sp];
        v->sp--;
    } else if (idx < 0xcc0) {
        idx -= 0xc80;
        D_003C39B0[idx] = func_001c0bf0(v->stk[v->sp], 2);
        v->sp--;
    } else if (idx < 0xd00) {
        idx -= 0xcc0;
        D_003C39F0[idx] = func_001c0bf0(v->stk[v->sp], 2);
        v->sp--;
    } else if (idx < 0xd40) {
        idx -= 0xd00;
        D_003C3A30[idx] = func_001c0bf0(v->stk[v->sp], 2);
        v->sp--;
    } else {
        idx -= 0xd40;
        b[idx] = func_001c0bf0(v->stk[v->sp], 2);
        v->sp--;
    }
    return 2;
}

/* op 15: pop into s16 variable `a` */
s32 func_001c1628(VmRec *v, s32 a) {
    u8 *p1 = func_00232cc0(1);
    u8 *p2 = func_00232cc0(2);
    if (a < 2048) {
        *(u16 *)(p1 + a) = func_001c0bf0(v->stk[v->sp], 3);
        v->sp--;
    } else if (a < 2304) {
        a -= 2048;
        *(u16 *)(p1 + a + 2048) = func_001c0bf0(v->stk[v->sp], 3);
        v->sp--;
    } else {
        a -= 3392;
        *(u16 *)(p2 + a) = func_001c0bf0(v->stk[v->sp], 3);
        v->sp--;
    }
    return 2;
}

/* func_001c1718 (pop into s32 variable): vm_ops.nosi.c */

/* op 31: pop into bit variable `a` */
s32 func_001c1880(VmRec *v, s32 a) {
    u8 *p1 = func_00232cc0(1);
    u8 *p2 = func_00232cc0(2);
    s32 bit = a % 8;
    s32 q = a / 8;
    u8 *p;
    if (v->stk[v->sp] >= 2) {
        v->stk[v->sp] = 1;
    } else if (v->stk[v->sp] < 0) {
        v->stk[v->sp] = 0;
    }
    a = q - 3392;
    p = p2 + a;
    *p &= ~(1 << bit);
    *p |= v->stk[v->sp] << bit;
    v->sp--;
    return 2;
}

/* op 21: push the argument */
s32 func_001c1960(VmRec *v, s32 arg) {
    v->sp++;
    v->stk[v->sp] = arg;
    return 2;
}

/* func_001c1980 (jump another VM): vm_ops.nostrict.c */

/* op 22: pop VM id and level; jump that VM to its label `k` */
s32 func_001c19f8(VmRec *vm, s32 k) {
    s32 a = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    VmRec *p;
    if (b < 0) b = 0;
    else if (b >= 8) b = 7;
    p = func_001e98d0((s32)(vm->fl.x >> 5) & 1, a);
    func_001c1980(p, b, p->lbl[k]);
    return 2;
}

/* op 23: pop VM id and level; wait while that VM has the level set */
s32 func_001c1aa8(VmRec *vm) {
    s32 a = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    VmRec *p;
    if (b < 0) b = 0;
    else if (b >= 8) b = 7;
    p = func_001e98d0((s32)(vm->fl.x >> 5) & 1, a);
    if (p->ret[b] != -1) {
        vm->pc -= 2;
        return 4;
    }
    return 2;
}

/* op 25: pop VM id and level; clear that level of that VM */
s32 func_001c1b58(VmRec *v) {
    s32 id, lvl, j;
    VmRec *t;
    VmMsg m;
    id = v->stk[v->sp--];
    lvl = v->stk[v->sp--];
    if (lvl < 0) lvl = 0;
    else if (lvl >= 8) lvl = 7;
    t = func_001e98d0((s32)(v->fl.x >> 5) & 1, id);
    if (t == v) return 6;
    t->ret[lvl] = -1;
    if (lvl != t->rsp) return 2;
    for (j = lvl + 1; j < 8; j++) {
        if (t->ret[j] != -1) {
            t->pc = t->ret[j];
            t->rsp = j;
            break;
        }
    }
    if ((u32)t->fl.i[0] % 2 == 1) {
        m.type = 18;
        m.val = 0;
        m.v[0] = 0.0f;
        m.v[1] = 0.0f;
        m.v[2] = 0.0f;
        m.v[3] = 1.0f;
        m.x = t->x0;
        func_001c4640(&m);
        t->fl.x &= ~1;
    }
    return 2;
}

/* opcode of instruction `pc` */
s32 func_001c1ce8(s8 *code, s32 pc) {
    return code[pc * 4 + 3];
}

/* argument (s24) of instruction `pc` */
s32 func_001c1cf8(s8 *code, s32 pc) {
    u8 *p = (u8 *)(pc * 4 + (s32)code);
    return p[0] | (p[1] << 8) | (((s8 *)p)[2] << 16);
}
