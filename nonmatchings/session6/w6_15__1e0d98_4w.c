/* func_001e0d98: 4 words off (hand or hand/nofill): same bgtz-slot issue as func_001e0ab0 (li v0,4 filled into bgtz slot, orig nop). */
extern s32 D_003DB064;
extern s32 D_0062F6D0;
extern s32 D_0062F64C;
extern s32 D_0062F650;
extern s32 D_0062F654;
extern f32 D_003DACB0;
extern f32 D_003DACB4;
extern s32 D_003DACB8;
extern s32 D_003DACBC;
extern u64 D_003DAE40[];
extern u8 D_003DAF60[];
void func_001e07a8(s32);
void func_001e05a8(void *);
s32 func_001e0d98(void) {
    f32 f;
    switch (D_003DB064) {
    case 0:
        D_0062F64C = D_0062F6D0;
        D_0062F650 = 0;
        D_0062F654 = 128;
        D_003DB064 = 1;
    case 1:
        break;
    default:
        goto ret0;
    }
    if (D_0062F64C <= 0) {
        D_003DB064 = 0;
        return 4;
    }
    func_001e07a8(0);
    D_003DAE40[22] = 0x8000000664020E00ULL;
    D_003DAE40[15] = (u64)D_0062F650 << 24 | 0x100808080ULL;
    D_003DAE40[33] = (u64)((f32)(D_003DACB8 + 0x7000) + (4096.0f - D_003DACB0 * 4096.0f))
        | (u64)((f32)(D_003DACBC + 29688) + (3072.0f - D_003DACB4 * 3072.0f)) << 16
        | 0xFFFFFFFE00000000ULL;
    D_003DAE40[31] = (u64)D_0062F654 << 24 | 0x100808080ULL;
    D_003DAE40[35] = (u64)(D_003DACB0 * 8192.0f * 0.5f - 4096.0f + 36864.0f + (f32)D_003DACB8)
        | (u64)(D_003DACB4 * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f + (f32)D_003DACBC) << 16
        | 0xFFFFFFFE00000000ULL;
    func_001e05a8(D_003DAF60);
    D_003DAE40[22] = 0x8008000264120E00ULL;
    D_0062F64C--;
    f = (f32)D_0062F64C / (f32)D_0062F6D0 * 128.0f;
    D_0062F654 = f;
    D_0062F650 = 128.0f - f;
ret0:
    return 0;
}
