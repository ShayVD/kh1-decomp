/* 001cfc28 18w (hand, same as w6_14 s6 draft; LCS 12). New finding (w7 s9): the late `sw m.x` is sched1's stale INSN_TICK. The function is one 6-block region; when bb2 (the Msg block) is scheduled, insns that become ready inside it are queued with INSN_TICK left from bb0, where the call group (call + r copy, insn 96) sat at clock 8, so the m.x store (true dep on the x load) waits until t=9 while initially-ready stores go at t=0..5. Original needs the store early (then x gets v0 and 29 gets a1). -fno-sched-interblock fixes the Msg block but merges the r==0 tail (248 bytes). do{}while(0)/for(;;)break wrappers, block-local decls, Msg2 (u32 val:24 aligned 8) and all 24 orders of x/type/val/v0 do not change it. */
typedef struct {
    s32 x0;
    void *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, brest:26;
    u32 hi;
    u64 q;
} VMd;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
typedef struct { s32 x0; s32 x4; } R4;
typedef struct { s32 x0; R4 *x4; } R;
void func_001c4640(Msg *m);
R *func_001e98d0(s32 a, s32 b);
s32 func_001cfc28(VMd *vm) {
    Msg m;
    s32 a = vm->stk[vm->sp - 2];
    s32 b = vm->stk[vm->sp - 1];
    s32 c = vm->stk[vm->sp];
    R *r = func_001e98d0(vm->b5, a);
    if (r == 0) {
        vm->sp -= 3;
        return 2;
    }
    if (r->x4) {
        m.x = r->x4->x4;
        m.type = 29;
        m.val = (u32)b;
        m.v[0] = c * 2.0f;
        m.v[1] = 0;
        m.v[2] = 0;
        m.v[3] = 1.0f;
        func_001c4640(&m);
    }
    vm->sp -= 3;
    return 2;
}
