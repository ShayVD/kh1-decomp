/* func_001cfc28: 18 words off (src/hand; also nogcse/nofill). Off: register choice in the Msg block (type 29 in a2 vs a1, x in a1 vs v0) and the resulting schedule; statement order has no effect. */
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
