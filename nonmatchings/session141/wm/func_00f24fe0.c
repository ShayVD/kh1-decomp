/* Round 35 wwm1: score 39 -> 35, `if (it == NULL || func_00f2b9e8(it) == 0) n = 0; else n = it->n;`. The target sets n = 0 in both branch delay slots (beqz it, beqzl v0); the exact branch sequence comes from `if (it != NULL && func_00f2b9e8(it) != 0) n = it->n; else n = 0;` (cfdiff 0), but that rotates it/n/cy over s3-s5 and scores 49. Earlier header below. */
/* score 39 (1084 vs 1088). Status row: level pips via func_00f23c20, item slots, colour text via func_001f0758, optional name/value. Reusing cx/cy for x+10/y+32 and y+46/x+158 took it 218 -> 39; u16 n. Left: the original keeps a copy of y+6 in s5 for the second pip loop (s3 is reused for n); copies/literal y+6 get propagated away. Round 26 wwm2. */
typedef struct { u8 v[4]; } C4;
typedef struct { u16 x0; u16 n; u16 name; u16 val; } It;
extern C4 D_00FB6750;
s32 func_001ba228(u16);
u64 *func_001f0758(u64 *, s32, s32, s32, s32, C4 *, s32);
u64 *func_001f0868(u64 *, s32, s32, s32, s32, s32, s32, s32);
u64 *func_00f23a58(s32, s32, s32, s32, u64 *);
u64 *func_00f23c20(s32, s32, s32, s32, s32, s32, s32, s32, u64 *);
C4 *func_00f2b8f0(s32);
C4 *func_00f2b940(s32, s32);
It *func_00f2b9a0(s32, s32);
s32 func_00f2b9e8(It *);
C4 *func_00f2be10(u16, s32);
u64 *func_00f66b78(s32);
void func_00f66b90(u64 *);

u64 *func_00f24fe0(s32 x, s32 y, s32 kind, s32 lv, s32 info, s32 pk)
{
    C4 col;
    s32 i;
    s32 cx;
    s32 cy;
    s32 small;
    u16 n;
    u64 *p;
    It *it;
    C4 *c;

    cx = x + 74;
    cy = y + 6;
    p = func_00f66b78(pk);
    p[1] = 20;
    p[0] = 0;
    p += 2;
    p[0] = 0x50003;
    p[1] = 71;
    p += 2;
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 68;
    p[1] = 66;
    p += 2;
    small = lv < 4;
    func_00f66b90(p);
    if (small) {
        for (i = 0; i < lv; i++) {
            p = func_00f23c20(cx, cy, 32, 0, 16, 16, 30, 128, p);
            cx += 16;
        }
        for (; i < 3; i++) {
            p = func_00f23c20(cx, cy, 48, 0, 16, 16, 30, 128, p);
            cx += 16;
        }
    } else {
        p = func_00f23c20(cx, cy, 64, 0, 16, 16, 30, 128, p);
    }
    it = func_00f2b9a0(kind, lv);
    if (it == NULL || func_00f2b9e8(it) == 0) {
        n = 0;
    } else {
        n = it->n;
    }
    cx = x + 180;
    for (i = 0; i < n; i++) {
        if (func_00f2b9e8(it)) {
            p = func_00f23c20(cx, cy, 0, 0, 16, 16, 30, 128, p);
        } else {
            p = func_00f23c20(cx, cy, 0, 0, 16, 16, 30, 128, p);
        }
        cx += 16;
    }
    for (; i < 5; i++) {
        p = func_00f23c20(cx, cy, 16, 0, 16, 16, 30, 128, p);
        cx += 16;
    }
    cx = x + 10;
    cy = y + 32;
    if (small) {
        c = func_00f2b940(kind, lv);
        if (c != NULL) {
            if (func_00f2b9e8(it)) {
                p = func_001f0758(p, 1, -128, cx, cy, c, 16);
            } else {
                p = func_001f0758(p, 1, -128, cx, cy, func_00f2b8f0(11), 16);
            }
        } else {
            col = D_00FB6750;
            p = func_001f0758(p, 1, -128, cx, cy, &col, 16);
        }
    } else {
        p = func_001f0758(p, 1, -128, cx, cy, func_00f2b8f0(12), 16);
    }
    if (info != 0 && it != NULL) {
        cy = y + 46;
        p = func_00f23a58(x + 36, y + 43, 7, 128, func_00f23a58(x + 28, y + 42, 3, 128, p));
        if (it->name != 0) {
            cx = x + 158;
            p = func_001f0868(p, 1, 2, -128, cx, cy, func_001ba228(it->name), 16);
            p = func_001f0758(p, 1, -128, x + 216, cy, func_00f2be10(it->val, 16), 16);
        }
    }
    return p;
}
