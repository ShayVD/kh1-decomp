/* func_001cdc58: 2 words off (strict src/hand, vm16.inc types). sw x (4) and sw zero (24) swapped around the jal delay slot; all statement orders give the same. */
typedef struct { u8 pad0[0x10]; f32 pos[3]; } Actor;
typedef struct {
    s32 x0;
    Actor *obj;
    f32 v08[3];
    f32 f14;
    f32 f18;
    f32 f1c;
    f32 f20;
    u8 pad24[0x15c];
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    union { u64 x; s32 i[2]; } flags;
} VM;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
void func_001c4640(Msg *m);
s32 func_001cdc58(VM *vm) {
    Msg m;
    m.type = 15;
    m.val = 0;
    m.v[3] = 1.0f;
    m.v[0] = 0;
    m.v[1] = 0;
    m.v[2] = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}
