/* Round 39 (wgb): gb.x func_00f399f8 near miss: 56 -> 49 words, score 94 -> 80 (512 = 512 bytes, was 496). msd showed the target recomputing (u16)n for the bitfields: fb as cur3 / 2 and fc as (u16)(cur2 / 2 - 1), read back from the u16 fields just stored, give the target dsrl for fb and the separate move/srl for fc; fa = (u16)((u16)v / 2 + 0xFFFF) gives the 32-bit addu (a plain int + 0xFFFF became a daddu). Then a hill3 order (150 s). Left: the bitfield mask constants each get their own register in the target (t1/t3/t4, ours reuses v0), and the cur store comes last. Tried: (u64)(u16)v / 2 and >> 1 forms for fb/fc (no change, 94), fa from cur too (516 bytes, 81). Earlier header below. */
/* Round 41 wwm2: score 110 -> 94, port.py of the wm twin func_00f60af0 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* 104 words / score 110 (472 vs 512 bytes): the call sequence and nibble-bitfield entity loop are right. Left: the original keeps n (func_001bb678) as an int and recomputes (u16)n for each of the three x88 nibble fields separately (+0xffff for -1, one with a 64-bit dsrl), plus the n*420-2520 float; my u16 temporaries get CSE'd. Wanted for the f22d00 table (wm twin func_00f60af0). */
typedef struct {
    u16 a : 4;
    u16 b : 4;
    u16 c : 4;
    u16 d : 4;
    u16 pad2;
    u16 on;
    u16 pad6[3];
} Ent;

typedef struct {
    u8 pad0[88];
    u64 lo : 32;
    u64 fa : 4;
    u64 fb : 4;
    u64 fc : 4;
    u64 hi : 20;
    u8 pad96[40];
    f32 y;
    u8 pad140[24];
    u16 n;
    u16 cur;
    u16 cur2;
    u16 cur3;
    u8 pad172[100];
    Ent ent[1];
} Wm;

extern Wm *D_00F56DC0;
s32 func_001bc4a8(void);
s32 func_001bc4b8(s32);
void func_001be1e8(s32, s32);
void func_001bd470(void);
s32 func_001bb678(void);

void func_00f399f8(s32 idx) {
    s32 v;
    s32 d;
    s32 i;

    if (idx >= func_001bc4a8()) {
        idx -= func_001bc4a8();
    } else {
        idx = func_001bc4b8(idx) | 0x80;
    }
    func_001be1e8(0, idx);
    func_001bd470();
    v = func_001bb678();
    d = (v - D_00F56DC0->cur) / 2;
    for (i = 0; i < D_00F56DC0->n; i++) {
        if (D_00F56DC0->ent[i].on != 0) {
            D_00F56DC0->ent[i].a += d;
            D_00F56DC0->ent[i].b += d;
            D_00F56DC0->ent[i].c += d;
        }
    }
    D_00F56DC0->cur = v;
    D_00F56DC0->fa = (u16)((u16)v / 2 + 0xFFFF);
    D_00F56DC0->cur2 = v;
    D_00F56DC0->y = -2944.0f - ((u16)v * 420 - 2520);
    D_00F56DC0->cur3 = v;
    D_00F56DC0->fb = D_00F56DC0->cur3 / 2;
    D_00F56DC0->fc = (u16)(D_00F56DC0->cur2 / 2 - 1);
}
