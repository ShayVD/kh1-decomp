#include "common.h"
s32 WaitSema(s32);
s32 SignalSema(s32);
typedef struct { u32 length; s32 CIE_delta; u32 pc_begin; u32 pc_range; } fde;
typedef struct Obj { u32 pc_begin, pc_end; fde *fde_begin; fde **fde_array; u32 count; struct Obj *next; } Obj;
extern s32 D_0046AF14;
extern Obj *D_0066FAD0;
void func_002640f0(Obj *ob);
fde *func_00264098(fde *f, u32 pc);

fde *func_00264258(u32 pc) {
    Obj *ob;
    fde *f;
    u32 lo, hi, i;
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
            i = (lo + hi) / 2;
            f = ob->fde_array[i];
            if (pc < f->pc_begin) hi = i;
            else if (pc < f->pc_begin + f->pc_range) return f;
            else lo = i + 1;
        }
        return 0;
    }
    if (ob->fde_array) {
        fde **p = ob->fde_array;
        for (; *p; p++) {
            f = func_00264098(*p, pc);
            if (f) break;
        }
    } else {
        f = func_00264098(ob->fde_begin, pc);
    }
    SignalSema(D_0046AF14);
    return f;
}
