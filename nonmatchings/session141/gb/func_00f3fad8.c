/* Round 36 (wgb): gb.x func_00f3fad8 near miss: 59 -> 61 words, score 96 -> 82 (aligned diff 65 -> 60). Statement order from tools/ovl/hill3.py (score-ranked, strict dependency rules). Tried: hill3 sweep of every gb RANKING row and wm RANKING rows 1-100 (85-90 s, seed 1; strict rules; the order kept passes hill3.py --check against the previous draft), and port.py from the twin (not better). Earlier header below. */
/* 59 words / score 96 (344 vs 352 bytes): GS packet build; 2 insns short, order of the field shift/or chains differs. */
typedef struct { u16 a, b, c, flags, d, e; } GbEnt;
typedef struct {
    u8 pad0[4];
    u16 count;
    u16 w;
    u16 pad8;
    u16 h;
    u8 padc[0x70 - 0xC];
    GbEnt ents[1];
} GbHdr;
typedef struct {
    u8 pad0[0xA0];
    GbHdr hdr;
} GbMap;
typedef struct { u8 pad0[4]; u16 used; u8 pad6[8]; u16 kind; } GbCell;
typedef struct { u8 pad0[8]; GbCell cells[1]; } GbGrid;
extern GbMap *D_00F56DC0;
u32 *func_00f3fad8(u32 *p, u32 addr, s32 dbp, s32 dbw, s32 dpsm, s32 dsax, s32 dsay, s32 w, s32 h) {
    s32 f;
    s32 n;
    s32 qwc;
    u64 *q;
    s32 x = dpsm & 7;
    f = 8;
    if (x == 1)
        f = 6;
    if (x == 2)
        f = 4;
    if (x == 3)
        f = 2;
    if (x == 4)
        f = 1;
    n = w * h * f;
    qwc = n / 32;
    if (n & 31)
        qwc++;
    p[3] = 0;
    p[0] = 0x10000007;
    p[2] = 0;
    p[1] = 0;
    q = (u64 *)(p + 4);
    q[0] = 0x1000000000000005;
    q[3] = 0x3F;
    q[4] = ((u64)dbp << 32) | ((u64)dbw << 48) | ((u64)dpsm << 56);
    q[8] = w | ((u64)h << 32);
    q[5] = 0x50;
    q[6] = ((u64)dsax << 32) | ((u64)dsay << 48);
    q[1] = 14;
    q[9] = 0x52;
    q[11] = 0x53;
    q[12] = qwc | 0x8000 | ((u64)2 << 58);
    q[7] = 0x51;
    q[10] = 0;
    q[13] = 0;
    q[2] = 0;
    p = (u32 *)(q + 14);
    p[1] = addr;
    p[0] = qwc | 0x30000000;
    p[2] = 0;
    p[3] = 0;
    return p + 4;
}
