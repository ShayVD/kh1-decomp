/* 3 words left (328 vs 328): address-CSE copy order of D[idx] base. Tried inline helpers, CONTEXT_ONLY callees, callee return types, permuter (-j1, 10 min). */
typedef struct { u8 p[6]; u16 f; u16 h; u16 pad; } N2fcf8;
typedef struct { s32 n; u8 pad[0x2C]; N2fcf8 ent[1]; } D2fcf8;
extern D2fcf8 D_00F85240;
extern s32 D_00F8C1F0;
void func_00f2cfd8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f2d590(void);
void func_00f2d3d8(s32);

void func_00f2fcf8(void) {
    s32 i;
    s32 r;
    s32 h, t;
    if (D_00F8C1F0 != 0) {
        return;
    }
    for (i = 0; i < D_00F85240.n; i++) {
        h = D_00F85240.ent[i].h;
        t = h - 1;
        if (((D_00F85240.ent[i].f >> 8) & 0xF) == 4) {
            r = -1;
            switch (h) {
            case 5:
                r = 1;
                break;
            case 6:
                r = 5;
                break;
            case 7:
                r = 9;
                break;
            case 8:
                r = 13;
                break;
            case 9:
                r = 17;
                break;
            }
            if (r >= 0) {
                func_00f2cfd8(0, i, t, r, 2, r, 0, 0, 0, -1);
            }
        }
    }
    D_00F8C1F0 = 1;
    func_00f2d590();
    func_00f2d3d8(1);
}
