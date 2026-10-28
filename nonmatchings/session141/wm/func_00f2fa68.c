/* 73 words left (468 vs 488 bytes): first loop should count down, const-hoist order of 1 vs 53, loop-2 addressing */
typedef struct { u16 a; u16 f; u16 h; u16 pad; s32 c; } N2fa68;
typedef struct { s32 n; u8 pad[48]; N2fa68 ent[1]; } D2fa68;
extern D2fa68 D_00F85240;
extern s32 D_00F8C1EC;
extern s32 D_00FBB5AC;
extern s32 D_00FBB5B0;
void func_00f2cfd8(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f2d590(void);
void func_00f2d3d8(s32);

static inline s32 id_2fa68(s32 i) {
    return D_00F85240.ent[i].h - 1;
}

void func_00f2fa68(void) {
    s32 i;
    s32 found;
    s32 r;
    s32 t;
    if (D_00F8C1EC != 0) {
        return;
    }
    found = 0;
    for (i = 0; i < D_00F85240.n; i++) {
        if (id_2fa68(i) == 53) {
            found = 1;
        }
    }
    if (!found) {
        D_00FBB5AC++;
    } else {
        D_00FBB5B0++;
    }
    for (i = 0; i < D_00F85240.n; i++) {
        if (((D_00F85240.ent[i].f >> 8) & 0xF) == 4) {
            t = id_2fa68(i);
            r = -1;
            switch (t) {
            case 4:
                r = found ? 3 : 2;
                break;
            case 5:
                r = found ? 7 : 6;
                break;
            case 6:
                r = found ? 11 : 10;
                break;
            case 7:
                r = found ? 15 : 14;
                break;
            case 8:
                r = found ? 19 : 18;
                break;
            }
            if (r >= 0) {
                func_00f2cfd8(0, i, t, r, 2, r, 0, 0, -1);
            }
        }
    }
    D_00F8C1EC = 1;
    func_00f2d590();
    func_00f2d3d8(found + 2);
}
