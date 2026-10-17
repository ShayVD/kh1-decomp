/* func_001c95f8: 15 words off, strict (src/hand), needs CONTEXT_ONLY func_001c6890 above (ctx6890.inc) + types.inc. Off: FP reg assignment of the 3 stack loads (orig z->f1,x->f2,y->f3) and sp in a2 vs a1. */
s32 func_001c95f8(VM *vm) {
    s32 m, sp;
    f32 d, x, y, z;
    func_001c6890();
    D_003C5510.u.flags |= 0x10;
    D_003C5510.p40.x = D_003C5510.a.x;
    D_003C5510.p40.y = D_003C5510.a.y;
    D_003C5510.p40.z = D_003C5510.a.z;
    m = vm->stk[vm->sp - 3];
    d = (f32)vm->stk[vm->sp - 4] * 2.0f;
    D_003C5510.x2c = m;
    D_003C5510.t0 = 0;
    sp = vm->sp;
    x = vm->stk[sp - 2];
    y = vm->stk[sp - 1];
    z = vm->stk[sp];
    vm->sp = sp - 5;
    D_003C5510.u.s.f4 = d;
    D_003C5510.p70.x = x;
    D_003C5510.p70.y = y;
    D_003C5510.p70.z = z;
    return 2;
}
