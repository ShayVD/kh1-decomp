/* 3 words left; tried 11 variants; 10-min permuter found nothing */
typedef struct { u16 f; u16 k; u8 pad[8]; } I2d480;
typedef struct { s32 n; u8 pad[0x32]; I2d480 items[1]; } L2d480;
CONTEXT_ONLY L2d480 D_00F85240 = {0};
void func_00f2cfd8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f2d3d8(s32);

void func_00f2d480(void) {
    s32 i;
    for (i = 0; i < D_00F85240.n; i++) {
        s32 k = D_00F85240.items[i].k - 1;
        if (((D_00F85240.items[i].f >> 8) & 0xF) == 4) {
            s32 x = -1;
            switch (k) {
            case 4: x = 0; break;
            case 5: x = 4; break;
            case 6: x = 8; break;
            case 7: x = 12; break;
            case 8: x = 16; break;
            }
            if (x >= 0) {
                func_00f2cfd8(0, i, k, x, 2, x, 0, 0, 0, -1);
            }
        }
    }
    func_00f2d3d8(0);
}
