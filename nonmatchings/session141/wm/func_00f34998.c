/* Round 48 wwm2: the hill3o order from a90bb89a (wm func_00f34998 near miss, score 316 -> 310, hill3o statement order (wwm2 round) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 308 was not valid. Restored the last valid statement order: score 316. Earlier header below. */
/* Round 46 wwm2: score 318 -> 316, func_00f68770 declared void. Earlier header below. */
/* 387 words by address, 173 after alignment (round 13). Logic believed complete (3 loops: D_00FBE3B8 list, D_00FBE7B8 flags with 0x4000/0x8000/else, D_00FCC570 sound points with a 6-way switch). The ApplyMatrix output is m[3] of the unit matrix. Left: we hoist sp+80 into an s-reg and spill i to the stack; the target recomputes addiu sp,80 at each use and keeps i in s8 for all three loops (frame 192 vs our 208). */
typedef struct { u8 pad0[6]; s16 h6; u8 pad8[10]; u16 h18; u8 pad20[12]; f32 m[4][4]; u8 pad96[48]; } S34998;
typedef struct { s32 w0; s32 w4; u8 pad8[12]; s32 w20; u8 pad24[8]; u8 b32[1]; } O34998;
extern S34998 D_00FBEBC0[];
extern s32 D_00F8C16C, D_00F8C170, D_00FCC560, D_00F87048;
extern s32 D_00FBE3B8[];
extern s32 D_00FBE7B8[];
extern f32 D_00FCC570[][4];
extern s8 D_00FCC670[];
extern f32 D_00F8C240[4][4];
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0ApplyMatrix(f32 *, f32 (*)[4], f32 *);
O34998 *func_00f3d978(f32, f32, f32 *, s32);
s32 func_00f3dbf8(s32, u8 *, s32);
void func_00f68770(s32, s32, void *, s32, s32);

void func_00f34998(void) {
    f32 v[4];
    f32 d[4];
    f32 m[4][4];
    s32 i;
    s32 j;
    s32 idx;
    s32 fl;
    s32 sel;
    O34998 *o;

    v[3] = 1.0f;
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
    sceVu0UnitMatrix(m);
    d[0] = 1000.0f;
    d[1] = 500.0f;
    for (i = 0; i < D_00F8C16C; i++) {
        idx = D_00FBE3B8[i];
        for (j = 0; j < 2; j++) {
            v[2] = d[j];
            sceVu0ApplyMatrix(m[3], D_00FBEBC0[idx].m, v);
            o = func_00f3d978(800.0f, 200.0f, m[3], 0);
            if (o == NULL) continue;
            D_00FBEBC0[idx].h18 |= 1;
            if ((u32)(o->w0 - 2) < 2 && (u32)(func_00f3dbf8(o->w4, o->b32, D_00FBEBC0[idx].h6) - 1) < 2 && !(o->w20 & 1)) {
                func_00f68770(75, 1, m, 0, D_00F87048);
                o->w20 |= 1;
            }
            break;
        }
    }
    d[0] = 1800.0f;
    d[1] = 0;
    for (i = 0; i < D_00F8C170; i++) {
        fl = D_00FBE7B8[i];
        if (fl & 0x4000) {
            idx = fl & 0xFFF;
            o = func_00f3d978(900.0f, 200.0f, D_00FBEBC0[idx].m[3], 0);
            if (o == NULL) continue;
            D_00FBEBC0[idx].h18 |= 1;
            if ((u32)(o->w0 - 2) >= 2) continue;
            if ((u32)(func_00f3dbf8(o->w4, o->b32, D_00FBEBC0[idx].h6) - 1) >= 2) continue;
            if (o->w20 & 1) continue;
            func_00f68770(75, 1, o->b32, 0, D_00F87048);
            o->w20 |= 1;
        } else if (fl & 0x8000) {
            idx = fl & 0xFFF;
            o = func_00f3d978(1200.0f, 200.0f, D_00FBEBC0[idx].m[3], 0);
            if (o == NULL) continue;
            if ((u32)(o->w0 - 2) >= 2) continue;
            if (func_00f3dbf8(o->w4, o->b32, D_00FBEBC0[idx].h6) != 2) continue;
            if (o->w20 & 1) continue;
            func_00f68770(75, 1, o->b32, 0, D_00F87048);
            o->w20 |= 1;
        } else {
            idx = fl & 0xFFF;
            for (j = 0; j < 2; j++) {
                v[2] = d[j];
                sceVu0ApplyMatrix(m[3], D_00FBEBC0[idx].m, v);
                o = func_00f3d978(900.0f, 200.0f, m[3], 0);
                if (o == NULL) continue;
                D_00FBEBC0[idx].h18 |= 1;
                if ((u32)(o->w0 - 2) < 2 && (u32)(func_00f3dbf8(o->w4, o->b32, D_00FBEBC0[idx].h6) - 1) < 2 && !(o->w20 & 1)) {
                    func_00f68770(75, 1, m, 0, D_00F87048);
                    o->w20 |= 1;
                }
                break;
            }
        }
    }
    for (i = 0; i < D_00FCC560; i++) {
        switch (D_00FCC670[i]) {
        case 0:
            d[0] = 200.0f;
            d[1] = -100.0f;
            sel = 0;
            break;
        case 1:
            d[0] = -200.0f;
            d[1] = 100.0f;
            sel = 0;
            break;
        case 2:
            d[0] = -200.0f;
            d[1] = 100.0f;
            sel = 1;
            break;
        case 3:
            d[0] = 200.0f;
            d[1] = -100.0f;
            sel = 1;
            break;
        case 5:
            d[0] = -200.0f;
            d[1] = 100.0f;
            sel = 2;
            break;
        default:
            d[0] = 200.0f;
            d[1] = -100.0f;
            sel = 2;
            break;
        }
        for (j = 0; j < 1; j++) {
            v[0] = D_00FCC570[i][0];
            v[1] = D_00FCC570[i][1];
            v[2] = D_00FCC570[i][2];
            v[sel] += d[j];
            v[3] = 1.0f;
            sceVu0ApplyMatrix(m[3], D_00F8C240, v);
            o = func_00f3d978(300.0f, 0.0f, m[3], 0);
            if (o == NULL) continue;
            if ((u32)(o->w0 - 2) >= 2) continue;
            if ((u32)(func_00f3dbf8(o->w4, o->b32, 141) - 1) >= 2) continue;
            if (o->w20 & 1) continue;
            func_00f68770(75, 1, o->b32, 0, D_00F87048);
            o->w20 |= 1;
        }
    }
}
