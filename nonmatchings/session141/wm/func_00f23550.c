/* Round 28 wwm1: score 5 -> 2 with a local pinned to a3 (KH1_REG("$7"), set right before the m.x30 store and passed as the 4th argument): the shared li a3,10 now comes out, one slot early (before lui v1,0x5 instead of after). Every placement of ten = 10 among the x2c/x30/sel stores gives 2 or 6; setting it before the func_001bb500 call drops the li (a3 is not kept across calls), so that form is wrong. Plain-C forms (a const local, m.x30 as the argument, a struct pointer, all 18 flag modes) stay at 5. Earlier header below. */
/* Round 27 wwm1: score 20 -> 5 (220 vs 216 bytes). The tail is `if (r != 0) return -1; if (m.sel >= n) return -2; return vals[m.sel];`. Left: the target loads 10 once into a3 for both the m.x30 store and the 4th argument (ours: li t0 for the store); a t = 10 local, m.x30 as the argument, chained and moved stores all keep two li. Earlier header below. */
/* Round 29 (wgb): 30 words, score 20 (224 vs 216 bytes; was 228 bytes, score 21). Passing the literal 10 to func_00f2b360 and ending with `ret = -2; if (m.sel < n) ret = vals[m.sel]; return ret;` saved one instruction. Tried m.x30 = n = 10 chains, m.x30 as the argument, init store orders. */
typedef struct {
    s32 type;
    s32 x4;
    s32 list[8];
    s32 x28;
    s32 x2c;
    s32 x30;
    s32 sel;
} M23550;
void func_00242b68(s32);
void func_001bb480(void);
s32 func_00f2b6f0(s32);
s32 func_001bb500(s32, s32);
s32 func_00f2b360(s32 *, s32 *, s32, s32);
s32 func_00f7ecd8(M23550 *);
void func_001bb4b0(void);
extern s32 D_00F850AC;

s32 func_00f23550(s32 arg0) {
    M23550 m;
    s32 vals[8];
    s32 n;
    s32 r;
    s32 ret;
    register s32 ten KH1_REG("$7"); /* the target loads 10 once, in a3, for both the m.x30 store and the 4th argument; cse folds every plain-C form back into two li */

    func_00242b68(4);
    D_00F850AC = 0;
    func_001bb480();
    m.x4 = func_00f2b6f0(arg0);
    m.type = 0x3600;
    m.x28 = func_001bb500(0x50000, 128);
    m.x2c = 0x50000;
    ten = 10;
    m.x30 = ten;
    m.sel = 0;
    n = func_00f2b360(m.list, vals, arg0, ten);
    m.list[n] = 0;
    r = func_00f7ecd8(&m);
    func_001bb4b0();
    if (r != 0) {
        return -1;
    }
    if (m.sel >= n) {
        return -2;
    }
    return vals[m.sel];
}
