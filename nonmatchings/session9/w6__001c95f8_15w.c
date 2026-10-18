/* 001c95f8 15w, hand, needs nonmatchings/session6/w6_14__types.inc + w6_14__ctx6890.inc above (inline them). Finding (w6 s9, -dS -dl): source order x,y,z already gives the orig address/copy structure (t0=z base, a1-copy=x, v1-copy=y) and the orig final load order (z first after sched2); only local-alloc differs: in sched1 the loads issue x(126), y(144), z(160) by LUID, lives tie (6 each), so qty birth order gives x f1, y f2, z f3; orig needs z loaded first in sched1 (z f1). Reordering the source statements changes which address gets t0 (the last one in source), so permutations stay at 15-23w. */
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
