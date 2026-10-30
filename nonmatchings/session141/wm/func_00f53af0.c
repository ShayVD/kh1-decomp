/* Round 64 wwm2: score 194 -> 192 with CONTEXT_ONLY definitions of func_00f533f8 (tools/ovl/nothrow.py: the call becomes nothrow, so reorg picks the original's plain/-likely branch next to it). Earlier header below. */
/* Round 48 wwm2: the hill3o order from dcd79c10 (wm func_00f53af0 near miss, score 194 -> 186, hill3o statement order (wwm2 round) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 186 was not valid. Restored the last valid statement order: score 194. Earlier header below. */
/* Round 36 (wgb): wm.x func_00f53af0 near miss: 332 -> 332 words, score 204 -> 194 (aligned diff 108 -> 104). port.py of gb func_00f2c9f8's round 36 draft, the round 36 order from tools/ovl/hill3.py (score-ranked, strict dependency rules). See the gb file for what is left. Earlier header below. */
/* wm.x func_00f53af0 near miss: 332 words differ, score 204 (ours 1400 bytes, original 1376). Port of gb func_00f2c9f8 (nonmatchings/session141/gb), which has the same diff and notes. Symbols mapped: D_00FA5B34/5B04/5AF0 = gb D_00F613B4/61384/61370, D_0108CE10 = D_00F80650, D_00F9B540 = D_00F56DC0. */
typedef struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 r : 4; } GbPos;
typedef struct { u8 pad[0x5C]; GbPos p5C; u8 pad2[2]; GbPos p60; GbPos p62; u8 pad3[0x10]; u16 x74; } World;
typedef struct { u8 pad[4]; u32 ax : 4; u32 ay : 4; u32 az : 4; u32 ar : 4; u32 bx : 4; u32 by : 4; u32 bz : 4; u32 br : 4; } Box;
extern World *D_00F9B540;
extern s32 D_00FA5B34;
extern s32 D_00FA5B04;
extern s32 D_00FA5AF0;
extern u8 D_0108CE10[];
u64 *func_00f66ac8(u64 *);
u64 *func_00f66ae0(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
void func_00f66f78(s32, u64 *);
u64 *func_00f533f8(GbPos, GbPos, void *, u32, u64 *, s32); CONTEXT_ONLY u64 * func_00f533f8(GbPos a0, GbPos a1, void * a2, u32 a3, u64 * a4, s32 a5) { return 0; }
u64 *func_00f53758(GbPos, GbPos, void *, s32, u64 *);
u64 *func_00f549d0(u64 *, void *);

s32 func_00f53af0(s32 arg0, u64 **pp, Box *b) {
    u64 *p;
    u64 *q;
    s32 mode;
    s32 type;
    u32 col;
    u32 col2;
    GbPos size;
    GbPos one;
    if (D_00FA5B34 == 0) {
        return arg0;
    }
    *pp = func_00f66ac8(*pp);
    p = func_00f66b78(*pp);
    p[1] = 24;
    p[0] = 0x720000006F00;
    *pp = p + 2;
    func_00f66b90(p + 2);
    if (D_00FA5B34 == 1) {
        if (D_00F9B540->x74 & 2) {
            mode = 6;
        } else if (D_00F9B540->x74 & 1) {
            mode = 5;
        } else {
            mode = 4;
        }
    } else {
        mode = D_00FA5B34;
    }
    if (D_00FA5B04 > 0) {
        switch (mode) {
        case 4:
        case 5:
        case 6:
            col = 0x800078D2;
            p = func_00f66b78(*pp);
            p[0] = ((u64)D_00FA5B04 << 32) | 72;
            p[1] = 66;
            q = p + 2;
            q[0] = 0x30000;
            q[1] = 71;
            *pp = p + 4;
            func_00f66b90(p + 4);
            one.x = 1;
            one.y = 1;
            one.z = 1;
            one.r = 0;
            *pp = func_00f533f8(D_00F9B540->p5C, one, D_0108CE10, col, *pp, 3);
            p = func_00f66b78(*pp);
            p[0] = ((u64)D_00FA5B04 << 32) | 72;
            p[1] = 66;
            q = p + 2;
            q[0] = 0x5000D;
            q[1] = 71;
            *pp = p + 4;
            func_00f66b90(p + 4);
            if (D_00FA5AF0 != 0) {
                col = (D_00FA5B04 << 24) | 0xC6C4;
                type = 18;
            } else {
                switch (mode) {
                case 6:
                    col = (D_00FA5B04 << 24) | 0x2747B8;
                    type = 16;
                    break;
                case 5:
                    col = (D_00FA5B04 << 24) | 0xC6C4;
                    type = 18;
                    break;
                case 4:
                    col = (D_00FA5B04 << 24) | 0xC6C4;
                    type = 17;
                    break;
                }
            }
            p = func_00f66b78(*pp);
            p[1] = 71;
            p[0] = 0x30000;
            *pp = p + 2;
            func_00f66b90(p + 2);
            if (D_00FA5B04 == 128) {
                *pp = func_00f533f8(D_00F9B540->p60, D_00F9B540->p62, D_0108CE10, col, *pp, 0);
                *pp = func_00f533f8(D_00F9B540->p60, D_00F9B540->p62, D_0108CE10, col, *pp, 2);
            }
            *pp = func_00f53758(D_00F9B540->p60, D_00F9B540->p62, D_0108CE10, type, *pp);
            break;
        case 2:
        case 3:
            if (D_00FA5B34 == 2) {
                col = 0x80B65D00;
                col2 = 0x80782F09;
                type = 12;
            } else {
                col = 0x802747B8;
                col2 = 0x80111D82;
                type = 11;
            }
            size.x = b->bx - b->ax + 1;
            size.y = b->by - b->ay + 1;
            size.z = b->bz - b->az + 1;
            p = func_00f66b78(*pp);
            p[0] = ((u64)D_00FA5B04 << 32) | 72;
            p[1] = 66;
            q = p + 2;
            q[0] = 0x30000;
            *pp = p + 4;
            q[1] = 71;
            func_00f66b90(p + 4);
            if (D_00FA5B04 == 128) {
                *pp = func_00f533f8(*(GbPos *)&b->pad[4], size, D_0108CE10, col2, *pp, 1);
            }
            p = func_00f66b78(*pp);
            p[0] = 0x30000;
            p[1] = 71;
            *pp = p + 2;
            func_00f66b90(p + 2);
            if (D_00FA5B04 == 128) {
                *pp = func_00f533f8(*(GbPos *)&b->pad[4], size, D_0108CE10, col, *pp, 0);
                *pp = func_00f533f8(*(GbPos *)&b->pad[4], size, D_0108CE10, col, *pp, 2);
            }
            *pp = func_00f53758(*(GbPos *)&b->pad[4], size, D_0108CE10, type, *pp);
        }
    }
    *pp = func_00f549d0(*pp, D_0108CE10);
    p = func_00f66b78(*pp);
    p[0] = 68;
    p[1] = 66;
    q = p + 2;
    q[1] = 71;
    q[0] = 0x5000D;
    *pp = p + 4;
    func_00f66b90(p + 4);
    func_00f66f78(arg0, func_00f66ae0(*pp));
    return arg0 + 1;
}
