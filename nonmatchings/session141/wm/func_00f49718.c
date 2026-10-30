/* drafttwins.py: score 303 -> 295, port.py of the gb twin func_00f22620 draft. Earlier header below. */
/* score 327 (1316 vs 1320). Port of gb func_00f22620 (wgb near miss, same score) via portmap2; D_00F56D90/98 -> D_00F9B510/18 and D_00F74210 -> D_010809C8 mapped by hand. See the gb header for what is left. Round 26 wwm2. Round 19 (wwm1): 217 -> 198 raw words with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). Round 19 (wwm1): score 311 -> 303 with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). */
typedef struct { u8 pad0[0x2200]; u64 tex[1]; } GbWorld;
typedef struct { s16 idx; s16 pad2; s32 u; s32 v; s32 w; s32 h; } GbTbl;
extern GbWorld *D_00F9B540;
extern GbTbl D_00FA6000[];
extern u64 *D_00F9B548;
extern s32 D_00F9B508;
extern s32 D_00F9B50C;
extern s32 D_00F9B510;
extern s32 D_00F9B518;
extern s32 D_00F9B51C;
extern s32 D_010809C8;
extern s32 D_01080A28;
extern s32 D_01080A2C;
extern s32 D_01080A30;
extern s32 D_01080A34;
void func_001bb558(void);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66ae0(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
void func_00f66f78(s32, u64 *);
u64 *func_00f49530(u64 *, s32, s32, s32, s32);
void func_00f59b30(u64 **, s32, s32);
void func_001efaf0(void); CONTEXT_ONLY void func_001efaf0() {}
void func_001bfac8(void);

void func_00f49718(void) {
    s32 a, b;
    s32 u, v, x1, y1, x2, y2;
    u64 *p;
    s32 show;
    for (;;) {
        if (D_00F9B508 == 0) {
            show = D_00F9B50C;
            a = 31;
            b = 32;
        } else {
            switch (D_00F9B510) {
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
        if (D_00F9B518 == 0) {
            func_001bb558();
            p = func_00f66b78(func_00f66ac8(D_00F9B548));
            p[0] = 0x740000007000;
            p[1] = 24;
            p += 2;
            func_00f66b90(p);
            if (D_00F9B508 == 0)
                p = func_00f49530(p, D_01080A28, D_01080A2C, D_01080A30, D_01080A34);
            if (show) {
                v = D_00FA6000[a].v;
                y2 = D_00FA6000[a].h + 25;
                u = D_00FA6000[a].u;
                x2 = D_00FA6000[a].w + 82;
                y1 = D_00FA6000[a].v + D_00FA6000[a].h + 1;
                x1 = D_00FA6000[a].u + D_00FA6000[a].w + 1;
                p = func_00f66b78(p);
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
                p[0] = D_00F9B540->tex[a];
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
                func_00f66b90(p);
                u = D_00FA6000[b].u + 1;
                x1 = u + D_00FA6000[b].w;
                y2 = D_00FA6000[b].h + 25;
                x2 = D_00FA6000[b].w + 82;
                v = D_00FA6000[b].v + 1;
                y1 = v + D_00FA6000[b].h;
                p = func_00f66b78(p);
                p[0] = 0;
                p[1] = 24;
                p += 2;
                p[1] = 66;
                p[0] = 0x8000000048;
                p += 2;
                p[0] = D_00F9B540->tex[b];
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
                func_00f66b90(p);
            }
            func_00f66f78(11840, func_00f66ae0(p));
            D_00F9B548 = p;
        }
        func_00f59b30(&D_00F9B548, D_00F9B51C, D_010809C8);
        func_001efaf0();
        func_001bfac8();
    }
}
