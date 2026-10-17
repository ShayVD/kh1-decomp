/* func_001cd600: 20 words off, mode hand/nogcse (strict). Off: which stack value gets the direct vs copied address reg/FP reg (orig x->f0,z->f1,y->f2) and flags ld/or/sd scheduled too early. Same 3-value issue as 95f8/99a8. */
typedef struct { u8 pad[48]; f32 rot[3]; u8 pad3c[880 - 60]; u64 flags; } Obj600;
typedef struct { s32 x0; Obj600 *obj; u8 pad8[376]; s32 sp; s32 stk[92]; } VM600;
s32 func_001cd600(VM600 *vm) {
    if (vm->obj) {
        vm->obj->rot[0] = vm->stk[vm->sp - 2] * 3.1415928f / 180.0f;
        vm->obj->rot[1] = vm->stk[vm->sp - 1] * 3.1415928f / 180.0f;
        vm->obj->rot[2] = vm->stk[vm->sp] * 3.1415928f / 180.0f;
        vm->obj->flags |= 0x100000000000ULL;
    }
    vm->sp -= 3;
    return 2;
}
