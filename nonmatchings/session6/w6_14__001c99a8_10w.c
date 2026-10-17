/* func_001c99a8: 10 words off, strict (src/hand), CONTEXT_ONLY func_001c6890 above + types.inc. Off: FP regs of the 3 deg->rad values (orig z->f0, x->f1); same issue as 95f8. */
void func_001e9fe8(V4a *d, V4a *s);
s32 func_001c99a8(VM *vm) {
    s32 m;
    f32 d;
    func_001c6890();
    D_003C5510.u.flags |= 0x20;
    m = vm->stk[vm->sp - 3];
    d = (f32)vm->stk[vm->sp - 4] * 2.0f;
    D_003C5510.x30 = m;
    D_003C5510.p80.x = vm->stk[vm->sp - 2] * 3.1415928f / 180.0f;
    D_003C5510.p80.y = vm->stk[vm->sp - 1] * 3.1415928f / 180.0f;
    D_003C5510.p80.z = vm->stk[vm->sp] * 3.1415928f / 180.0f;
    D_003C5510.u.s.f8 = d;
    func_001e9fe8(&D_003C5510.p80, &D_003C5510.p80);
    D_003C5510.p50.x = D_003C5510.b.x;
    D_003C5510.p50.y = D_003C5510.b.y;
    D_003C5510.p50.z = D_003C5510.b.z;
    vm->sp -= 5;
    return 2;
}
