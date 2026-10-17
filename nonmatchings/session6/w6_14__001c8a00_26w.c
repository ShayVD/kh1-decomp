/* func_001c8a00: 26 words off (src/hand, CONTEXT_ONLY func_001c6890 + types.inc). Structure right (WRAP macro loops); off: register numbering of the 3 stack values / D_003C5510 base (same 3-value issue as 95f8/99a8/cd600). */
#define WRAP(a) while (1) { if (a > 3.1415928f) a -= 6.2831855f; else if (a < -3.1415928f) a += 6.2831855f; else break; }
s32 func_001c8a00(VM *vm) {
    s32 sp;
    func_001c6890();
    D_003C5510.u.flags |= 2;
    D_003C5510.t1 = 0;
    sp = vm->sp;
    D_003C5510.p80.z = vm->stk[sp] / 180.0f * 3.1415928f;
    D_003C5510.p80.x = vm->stk[sp - 2] / 180.0f * 3.1415928f;
    D_003C5510.p80.y = vm->stk[sp - 1] / 180.0f * 3.1415928f;
    D_003C5510.u.s.f8 = vm->stk[sp - 3] * 2.0f;
/*E*/
    WRAP(D_003C5510.p80.x);
    WRAP(D_003C5510.p80.y);
    WRAP(D_003C5510.p80.z);
    D_003C5510.p50.x = D_003C5510.b.x;
    D_003C5510.p50.y = D_003C5510.b.y;
    D_003C5510.p50.z = D_003C5510.b.z;
    vm->sp = sp - 4;
    return 2;
}
