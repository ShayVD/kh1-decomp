/* score 21 (10 words, 1052 vs 1056 bytes with the trailing pad; was 53). Round 31 wwm2: hill2 over the st stores (xC, xD and x4 moved up after x8) took it to 56 words; then writing the first tail branch in the same order as the else-if branch (D_00F85120 before D_00F85124) gave 10. Left: both D_00F8512C decrements put the address in v1 and the value in v0 (the original has them the other way round). Tried --x, -= 1, x = x - 1, a local copy, a pointer, u32, the != 0 branch order and about 1900 orders of the two tail blocks; ctx2 (pairs) gives nothing. Earlier header: score 53 (1060 vs 1056 bytes); left: st byte-store order (orig xE,xF,x13,x30,x34,x38,x40,xC,xD,x4), tail regs and cross-jump of D_00F85120/28 stores; tried greedy store perms, if/switch reorder, goto shared tail (worse, 151+) */
typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s8 xC, xD, xE, xF;
    u8 pad10[3];
    s8 x13;
    u8 pad14[0x1C];
    void *x30;
    void *x34;
    u64 x38;
    u64 x40;
} St20;
extern s32 D_00F850F0;
extern s32 D_00F85120;
extern s32 D_00F85124;
extern s32 D_00F85128;
extern s32 D_00F8512C;
extern f32 D_00F8511C;
extern s32 *D_00F850E8;
extern s32 D_00F850EC;
extern f32 D_00FBA990[4][4];
extern f32 D_00FBA9D0[4][4];
extern f32 D_00F85180[4][4];
extern f32 D_00F85200[4][4];
extern f32 D_00F872C0[4][4];
extern f32 D_002BBDFC;
extern s32 D_00FBAA58;
extern s32 D_00FBAA38[];
extern s32 D_00FBAA18[];
void *memset(void *, s32, u32);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0RotMatrixX(OvlMtx, OvlMtx, f32);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0CopyMatrix(OvlMtx, OvlMtx);
void func_001655e0(OvlMtx, s32, f32, s32);
void func_001621e0(s32, OvlMtx, St20 *, s32);
void func_0011d140(s32, s32);
s32 func_00167698(s32);
void func_00f20ba0(OvlMtx);
void func_00f20068(void);
void func_00f20088(void);

void func_00f20d08(s32 id, OvlMtx m, OvlMtx w, f32 a) {
    St20 st;
    OvlMtx r;
    OvlMtx v;
    s32 al;
    s32 k;
    s32 i;
    f32 n;

    if (D_00F850F0 < 0) return;
    al = a * 128.0f;
    if (al == 0) return;
    memset(&st, 0, sizeof(st));
    sceVu0UnitMatrix(r);
    sceVu0RotMatrixX(r, r, 3.1415927f);
    sceVu0MulMatrix(D_00FBA990, w, r);
    sceVu0MulMatrix(m, m, r);
    sceVu0MulMatrix(v, D_00F85180, D_00F85200);
    sceVu0CopyMatrix(D_00FBA9D0, D_00F872C0);
    D_00FBA9D0[3][3] = a;
    func_001655e0(m, D_00F850EC, D_00F8511C, D_00F850E8[D_00F85120]);
    st.xC = -128;
    st.xD = -128;
    st.x8 = id;
    st.xE = -128;
    st.xF = al;
    st.x13 = -1;
    st.x30 = func_00f20068;
    st.x34 = func_00f20088;
    st.x4 = 1;
    st.x38 = 0x31000070;
    st.x40 = 0x800D0;
    func_001621e0(D_00F850EC, v, &st, 0);
    if (0.0f <= D_00F8511C && D_00F8511C <= 0.09999999404f) {
        if (D_00F850F0 == 0) {
            switch (D_00F85120) {
            case 1:
                k = 0xE2D1;
                break;
            case 2:
                k = 0xE2D2;
                break;
            case 5:
                k = 0xE2D4;
                break;
            default:
                goto skip;
            }
            func_0011d140(k, 0);
        } else if (D_00F85120 == 1) {
            func_0011d140(0xE2F1, 0);
        }
    }
skip:
    if (D_00F85124 >= 0) {
        n = func_00167698(D_00F850E8[D_00F85120]);
        D_00F8511C += D_002BBDFC;
        if (D_00FBAA58 == 0 && D_00F85120 == 5 && 544.0f <= D_00F8511C) func_00f20ba0(m);
        if (n < D_00F8511C) {
            if (D_00F8512C == 0) {
                D_00F8511C -= n;
                if (D_00F85124 > 0 && --D_00F85124 == 0) {
                    D_00F8511C = n;
                    D_00F85124 = -1;
                }
            } else {
                D_00F8512C--;
                D_00F8511C = 0.0f;
                i = D_00F85128;
                D_00F85120 = D_00FBAA18[i];
                D_00F85124 = D_00FBAA38[i];
                D_00F85128 = (i + 1) & 7;
            }
        }
    } else if (D_00F8512C != 0) {
        D_00F8512C--;
        D_00F8511C = 0.0f;
        i = D_00F85128;
        D_00F85120 = D_00FBAA18[i];
        D_00F85124 = D_00FBAA38[i];
        D_00F85128 = (i + 1) & 7;
    }
}
