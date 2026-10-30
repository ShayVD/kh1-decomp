/* Round 46 (wgb): score 303 -> 295. show = 0 moves from before the switch into a case 0: default: arm, so it lands in the delay slot of the default path (move s1,zero) as in the target. Separate case 0 and default arms, or a default at the end, score worse (315-316). Guarded hill3 (300 s) found nothing more. Left: in the tail call func_00f32a38(&D_00F56DC8, D_00F56D9C, D_00F74210) the target loads the hi of D_00F74210 first, and reorg puts it in the delay slot of a bnezl at the D_00F56D98 test; ours starts with &D_00F56DC8. */
/* Round 41 wwm2: score 327 -> 303, port.py of the wm twin func_00f49718 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* 217 words / score 327 (1316 vs 1320). Logic complete (endless frame loop: two sprites from D_00F61880[31/32 or 33/34] plus closing packet, then func_00f32a38/func_001efaf0/func_001bfac8). Switch needs case 0 to get the orig slti tree; orig puts show = 0 in the default path delay slot (ours hoists it before the switch). Orig loads table fields w, v, h, u in that order; locals for them made the switch shape regress (399). No more variants tried. */
typedef struct { u8 pad0[0x2200]; u64 tex[1]; } GbWorld;
typedef struct { s16 idx; s16 pad2; s32 u; s32 v; s32 w; s32 h; } GbTbl;
extern GbWorld *D_00F56DC0;
extern GbTbl D_00F61880[];
extern u64 *D_00F56DC8;
extern s32 D_00F56D88;
extern s32 D_00F56D8C;
extern s32 D_00F56D90;
extern s32 D_00F56D98;
extern s32 D_00F56D9C;
extern s32 D_00F74210;
extern s32 D_00F74270;
extern s32 D_00F74274;
extern s32 D_00F74278;
extern s32 D_00F7427C;
void func_001bb558(void);
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3f9e8(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
void func_00f3fe80(s32, u64 *);
u64 *func_00f22438(u64 *, s32, s32, s32, s32);
void func_00f32a38(u64 **, s32, s32);
void func_001efaf0(void); CONTEXT_ONLY void func_001efaf0() {}
void func_001bfac8(void);

void func_00f22620(void) {
    s32 a, b;
    s32 u, v, x1, y1, x2, y2;
    u64 *p;
    s32 show;
    for (;;) {
        if (D_00F56D88 == 0) {
            show = D_00F56D8C;
            a = 31;
            b = 32;
        } else {
            switch (D_00F56D90) {
            case 0:
            default:
                show = 0;
                break;
            case 1:
                show = 1;
                a = 31;
                b = 32;
                break;
            case 2:
                a = 33;
                show = 1;
                b = 34;
                break;
            }
        }
        if (D_00F56D98 == 0) {
            func_001bb558();
            p = func_00f3fa80(func_00f3f9d0(D_00F56DC8));
            p[0] = 0x740000007000;
            p[1] = 24;
            p += 2;
            func_00f3fa98(p);
            if (D_00F56D88 == 0)
                p = func_00f22438(p, D_00F74270, D_00F74274, D_00F74278, D_00F7427C);
            if (show) {
                v = D_00F61880[a].v;
                y2 = D_00F61880[a].h + 25;
                u = D_00F61880[a].u;
                x2 = D_00F61880[a].w + 82;
                y1 = D_00F61880[a].v + D_00F61880[a].h + 1;
                x1 = D_00F61880[a].u + D_00F61880[a].w + 1;
                p = func_00f3fa80(p);
                p[0] = 0;
                p[1] = 20;
                p += 2;
                p[1] = 71;
                p[0] = 0x30000;
                p += 2;
                p[0] = 0;
                p[1] = 24;
                p += 2;
                p[1] = 66;
                p[0] = 68;
                p += 2;
                p[0] = D_00F56DC0->tex[a];
                p[1] = 6;
                p += 2;
                p[0] = 342;
                p[1] = 0;
                p += 2;
                p[1] = 1;
                p[0] = 0x3F8000004D808080;
                p += 2;
                p[1] = 3;
                p[0] = (u << 4) | ((u64)(v << 4) << 16);
                p += 2;
                p[1] = 5;
                p[0] = 0x101900520;
                p += 2;
                p[1] = 3;
                p[0] = (x1 << 4) | ((u64)(y1 << 4) << 16);
                p += 2;
                p[1] = 5;
                p[0] = (x2 << 4) | ((u64)(y2 << 4) << 16) | 0x100000000;
                p += 2;
                func_00f3fa98(p);
                u = D_00F61880[b].u + 1;
                x1 = u + D_00F61880[b].w;
                y2 = D_00F61880[b].h + 25;
                x2 = D_00F61880[b].w + 82;
                v = D_00F61880[b].v + 1;
                y1 = v + D_00F61880[b].h;
                p = func_00f3fa80(p);
                p[0] = 0;
                p[1] = 24;
                p += 2;
                p[1] = 66;
                p[0] = 0x8000000048;
                p += 2;
                p[0] = D_00F56DC0->tex[b];
                p[1] = 6;
                p += 2;
                p[0] = 342;
                p[1] = 0;
                p += 2;
                p[0] = 0x3F80000038808080;
                p[1] = 1;
                p += 2;
                p[1] = 3;
                p[0] = (u << 4) | ((u64)(v << 4) << 16);
                p += 2;
                p[0] = 0x101900520;
                p[1] = 5;
                p += 2;
                p[0] = (x1 << 4) | ((u64)(y1 << 4) << 16);
                p[1] = 3;
                p += 2;
                p[0] = (x2 << 4) | ((u64)(y2 << 4) << 16) | 0x100000000;
                p[1] = 5;
                p += 2;
                p[1] = 66;
                p[0] = 68;
                p += 2;
                p[0] = 0x740000007000;
                p[1] = 24;
                p += 2;
                p[0] = 0x5000D;
                p[1] = 71;
                p += 2;
                p[1] = 20;
                p[0] = 96;
                p += 2;
                func_00f3fa98(p);
            }
            func_00f3fe80(11840, func_00f3f9e8(p));
            D_00F56DC8 = p;
        }
        func_00f32a38(&D_00F56DC8, D_00F56D9C, D_00F74210);
        func_001efaf0();
        func_001bfac8();
    }
}
