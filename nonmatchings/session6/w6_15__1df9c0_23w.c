/* func_001df9c0: 23 words off (hand). Orig loads vm->obj twice (lw 4(a0) and lw 0(vm+4)); ours CSEs it into one. */
typedef struct { f32 x, y, z; } V3;
typedef struct { u8 pad0[0x10]; V3 pos; } O10;
extern V3 *D_0062A428;
s32 func_001df9c0(VM *vm) {
    f32 x, y, z;
    O10 *o = vm->obj;
    x = vm->stk[vm->sp - 2];
    y = vm->stk[vm->sp - 1];
    z = vm->stk[vm->sp];
    vm->sp -= 4;
    D_0062A428->x = o->pos.x + x;
    D_0062A428->y = ((O10 *)vm->obj)->pos.y + y;
    D_0062A428->z = ((O10 *)vm->obj)->pos.z + z;
    return 2;
}
