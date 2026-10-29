/* gb.x func_00f2c9f8 near miss: 332 words differ, score 204 (ours 1400 bytes, original 1376). Draws the selection/highlight boxes: a 0x6F00/0x7200 packet, a mode from D_00F613B4 (if it is 1, from World x74 bits: 6/5/4), then for D_00F61384 > 0 either cases 4-6 (World p5C/p60/p62 boxes through func_00f2c300 / func_00f2c660, color and type from D_00F61370 or the mode) or cases 2-3 (box size from the Box arg's two packed nibble triples). Then func_00f2d8d8 and the closing packet. Logic is complete and the Box nibble math matches. Left: the original keeps the constant 1 in s1 from the prologue for the mode == 1 compare (bnel v0,s1), and builds packets with separate p+16 / p+32 bases, where ours copies p into t0. That shifts the s-registers, plus a blez vs blezl at the D_00F61384 test. Tried: four packet forms (p[0..3], q = p + 2, *p++, *pp = p += 4), a nogcse/nofill/nostrict/nosi mode, and four ways to write the mode selection (if/else with a re-read, a switch, an explicit one variable). wm twin: func_00f53af0 (same score). */
typedef struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 r : 4; } GbPos;
typedef struct { u8 pad[0x5C]; GbPos p5C; u8 pad2[2]; GbPos p60; GbPos p62; u8 pad3[0x10]; u16 x74; } World;
typedef struct { u8 pad[4]; u32 ax : 4; u32 ay : 4; u32 az : 4; u32 ar : 4; u32 bx : 4; u32 by : 4; u32 bz : 4; u32 br : 4; } Box;
extern World *D_00F56DC0;
extern s32 D_00F613B4;
extern s32 D_00F61384;
extern s32 D_00F61370;
extern u8 D_00F80650[];
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3f9e8(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
void func_00f3fe80(s32, u64 *);
u64 *func_00f2c300(GbPos, GbPos, void *, u32, u64 *, s32);
u64 *func_00f2c660(GbPos, GbPos, void *, s32, u64 *);
u64 *func_00f2d8d8(u64 *, void *);

s32 func_00f2c9f8(s32 arg0, u64 **pp, Box *b) {
    u64 *p;
    u64 *q;
    s32 mode;
    s32 type;
    u32 col;
    u32 col2;
    GbPos size;
    GbPos one;
    if (D_00F613B4 == 0) {
        return arg0;
    }
    *pp = func_00f3f9d0(*pp);
    p = func_00f3fa80(*pp);
    p[0] = 0x720000006F00;
    p[1] = 24;
    *pp = p + 2;
    func_00f3fa98(p + 2);
    if (D_00F613B4 == 1) {
        if (D_00F56DC0->x74 & 2) {
            mode = 6;
        } else if (D_00F56DC0->x74 & 1) {
            mode = 5;
        } else {
            mode = 4;
        }
    } else {
        mode = D_00F613B4;
    }
    if (D_00F61384 > 0) {
        switch (mode) {
        case 4:
        case 5:
        case 6:
            col = 0x800078D2;
            p = func_00f3fa80(*pp);
            p[0] = ((u64)D_00F61384 << 32) | 72;
            p[1] = 66;
            q = p + 2;
            q[0] = 0x30000;
            q[1] = 71;
            *pp = p + 4;
            func_00f3fa98(p + 4);
            one.x = 1;
            one.y = 1;
            one.z = 1;
            one.r = 0;
            *pp = func_00f2c300(D_00F56DC0->p5C, one, D_00F80650, col, *pp, 3);
            p = func_00f3fa80(*pp);
            p[0] = ((u64)D_00F61384 << 32) | 72;
            p[1] = 66;
            q = p + 2;
            q[0] = 0x5000D;
            q[1] = 71;
            *pp = p + 4;
            func_00f3fa98(p + 4);
            if (D_00F61370 != 0) {
                type = 18;
                col = (D_00F61384 << 24) | 0xC6C4;
            } else {
                switch (mode) {
                case 6:
                    type = 16;
                    col = (D_00F61384 << 24) | 0x2747B8;
                    break;
                case 5:
                    type = 18;
                    col = (D_00F61384 << 24) | 0xC6C4;
                    break;
                case 4:
                    type = 17;
                    col = (D_00F61384 << 24) | 0xC6C4;
                    break;
                }
            }
            p = func_00f3fa80(*pp);
            p[0] = 0x30000;
            p[1] = 71;
            *pp = p + 2;
            func_00f3fa98(p + 2);
            if (D_00F61384 == 128) {
                *pp = func_00f2c300(D_00F56DC0->p60, D_00F56DC0->p62, D_00F80650, col, *pp, 0);
                *pp = func_00f2c300(D_00F56DC0->p60, D_00F56DC0->p62, D_00F80650, col, *pp, 2);
            }
            *pp = func_00f2c660(D_00F56DC0->p60, D_00F56DC0->p62, D_00F80650, type, *pp);
            break;
        case 2:
        case 3:
            if (D_00F613B4 == 2) {
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
            p = func_00f3fa80(*pp);
            p[0] = ((u64)D_00F61384 << 32) | 72;
            p[1] = 66;
            q = p + 2;
            q[0] = 0x30000;
            q[1] = 71;
            *pp = p + 4;
            func_00f3fa98(p + 4);
            if (D_00F61384 == 128) {
                *pp = func_00f2c300(*(GbPos *)&b->pad[4], size, D_00F80650, col2, *pp, 1);
            }
            p = func_00f3fa80(*pp);
            p[0] = 0x30000;
            p[1] = 71;
            *pp = p + 2;
            func_00f3fa98(p + 2);
            if (D_00F61384 == 128) {
                *pp = func_00f2c300(*(GbPos *)&b->pad[4], size, D_00F80650, col, *pp, 0);
                *pp = func_00f2c300(*(GbPos *)&b->pad[4], size, D_00F80650, col, *pp, 2);
            }
            *pp = func_00f2c660(*(GbPos *)&b->pad[4], size, D_00F80650, type, *pp);
        }
    }
    *pp = func_00f2d8d8(*pp, D_00F80650);
    p = func_00f3fa80(*pp);
    p[0] = 68;
    p[1] = 66;
    q = p + 2;
    q[0] = 0x5000D;
    q[1] = 71;
    *pp = p + 4;
    func_00f3fa98(p + 4);
    func_00f3fe80(arg0, func_00f3f9e8(*pp));
    return arg0 + 1;
}
