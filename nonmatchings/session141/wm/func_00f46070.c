/* Round 31 wwm1: score 51 -> 15. c is copied with memcpy (gcc's inline block move) before the bits struct copy; with two struct assignments sched1 always put the 32-byte bits copy first. memcpy for bits instead gives 15 too. In the original these are aggregate initializers, so this is a stand-in for the order, not the source. Left: a0/a1/a2 numbering in the 105 - r*35 branch. Earlier header below. */
/* score 51 (1332 vs 1336). Pad-intro animation loop: per frame i, q = i/4, k = q%8, tbl[k] picks a button whose alpha ramps 35..140 or back, mask bits pick which of 4 func_00f45e68 sprites draw in mode bit 0/1; first/cnt/done drive mode from func_00f40c98/func_00f35960/func_00f2c848. The three local tables are aggregate initializers in the original (D_00FB74B0 = {0x8C4D3F28, 0x8C193C7F x3}, D_00FB74C0 = {1,3,7,15,13,9,1,0}, D_00FB74E0 = {0,1,2,3,1,2,3,0}); this draft uses struct copies of the extern rodata so hand.py can score it (with initializers the rodata placement fails until the code matches). Keys: done != 0 || (f40c98 && f35960) shape keeps done on the stack (98 -> 59). Left: gcc schedules the 32-byte bits copy before the 16-byte c copy (orig c first; every decl/statement order tried), and a0/a1/a2 numbering in the 105 - r*35 branch. Round 27 wwm2. */
extern u64 **D_00F85160;
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
s32 func_00f66ae0(u64 *);
void func_00f66fb0(s32, s32);
void func_001bfac8(void);
f32 *func_00f2c848(void);
s32 func_00f35960();
s32 func_00f40c98(void);
u64 *func_00f45e68(u64 *, s32, s32, s32);

typedef struct { s32 v[4]; } A4;
void *memcpy(void *, const void *, u32);
typedef struct { s32 v[8]; } A8;
extern A4 D_00FB74B0;
extern A8 D_00FB74C0;
extern A8 D_00FB74E0;

void func_00f46070(s32 mode, s32 n)
{
    s32 a[4];
    A4 c;
    A8 bits;
    A8 tbl;
    s32 mask;
    s32 i;
    s32 first;
    s32 cnt;
    s32 done;
    s32 q;
    s32 k;
    s32 j;
    f32 *f;
    u64 *p;

    memcpy(&c, &D_00FB74B0, sizeof(c));
    bits = D_00FB74C0;
    tbl = D_00FB74E0;
    mask = 0;
    i = 0;
    first = mode == 0;
    cnt = 0;
    done = 0;
    a[0] = 0;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
    while (i < n || first || func_00f35960()) {
        q = i / 4;
        k = q % 8;
        j = tbl.v[k];
        if (k < 4) {
            mask |= 1 << j;
            a[j] = (i - q * 4) * 35 + 35;
        } else {
            a[j] = 105 - (i - q * 4) * 35;
            if (j >= 5) {
                mask ^= 1 << (j - 1);
            }
        }
        c.v[0] = (a[0] << 24) | 0x4D3F28;
        c.v[1] = (a[1] << 24) | 0x193C7F;
        c.v[2] = (a[2] << 24) | 0x193C7F;
        c.v[3] = (a[3] << 24) | 0x193C7F;
        p = func_00f66b78(func_00f66ac8(*D_00F85160));
        p[0] = 0x30003;
        p[1] = 71;
        p += 2;
        p[0] = 0x60;
        p[1] = 20;
        p += 2;
        p[0] = 0;
        p[1] = 24;
        p += 2;
        p[0] = 68;
        p[1] = 66;
        p += 2;
        func_00f66b90(p);
        if (first) {
            f = func_00f2c848();
            if (cnt < 20) {
                mode = 3;
            } else {
                if (done != 0 || (func_00f40c98() != 0 && func_00f35960() != 0)) {
                    if (done == 0) mode = func_00f35960();
                    done = 1;
                } else {
                    mode = 1;
                    if (!(*f <= 0.0f)) {
                        mode = 2;
                    }
                }
                if (func_00f35960() != 0) {
                    first = 0;
                } else if (func_00f40c98() != 0) {
                    return;
                }
            }
            cnt++;
        }
        if (mode & 1) {
            if (mask & 1) p = func_00f45e68(p, 0, 0, c.v[0]);
            if (mask & 2) p = func_00f45e68(p, 0, 1, c.v[1]);
            if (mask & 4) p = func_00f45e68(p, 0, 2, c.v[2]);
            if (mask & 8) p = func_00f45e68(p, 0, 3, c.v[3]);
        }
        if (mode & 2) {
            if (mask & 1) p = func_00f45e68(p, 1, 0, c.v[0]);
            if (mask & 2) p = func_00f45e68(p, 1, 1, c.v[1]);
            if (mask & 4) p = func_00f45e68(p, 1, 2, c.v[2]);
            if (mask & 8) p = func_00f45e68(p, 1, 3, c.v[3]);
        }
        i++;
        p = func_00f66b78(p);
        p[0] = 0x5000D;
        p[1] = 71;
        p += 2;
        p[0] = 0x0000740000007000LL;
        p[1] = 24;
        p += 2;
        p[0] = 68;
        p[1] = 66;
        p += 2;
        func_00f66b90(p);
        func_00f66fb0(10, func_00f66ae0(p));
        *D_00F85160 = p;
        func_001bfac8();
    }
}
