/* 14 words / score 28; instruction order right, registers shifted by one (orig addr a2, const a3, result a1; ours a1/a2/a0); tried void * and u64 * params, extra param, all flag modes, statement perms; 5 min permuter no gain */
extern u32 *D_00F82874;

void func_00f3fa40(u32 p) {
    u32 n = p - (u32)D_00F82874;
    n = (n >> 4) - 1;
    D_00F82874[0] = 0;
    D_00F82874[1] = 0;
    D_00F82874[2] = 0;
    D_00F82874[3] = n | 0x50000000;
}
