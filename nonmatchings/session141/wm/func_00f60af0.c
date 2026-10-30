/* drafttwins.py: score 94 -> 80, port.py of the gb twin func_00f399f8 draft. Earlier header below. */
/* score 94 (56 words; 496 vs 512 bytes). Updates entry nibble bitfields by (v - cur)/2, then the u64 bitfields at +88 and a float. Control flow and the nibble loop match. Left: the original computes each of the three +88 fields from its own (u16)v / 2 (one of them as a 64-bit dsrl), and builds the 64-bit masks in a different register order. Tried s32/u16 v, inverted index branch. */
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

extern Wm *D_00F9B540;
s32 func_001bc4a8(void);
s32 func_001bc4b8(s32);
void func_001be1e8(s32, s32);
void func_001bd470(void);
s32 func_001bb678(void);

void func_00f60af0(s32 idx) {
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
    d = (v - D_00F9B540->cur) / 2;
    for (i = 0; i < D_00F9B540->n; i++) {
        if (D_00F9B540->ent[i].on != 0) {
            D_00F9B540->ent[i].a += d;
            D_00F9B540->ent[i].b += d;
            D_00F9B540->ent[i].c += d;
        }
    }
    D_00F9B540->cur = v;
    D_00F9B540->fa = (u16)((u16)v / 2 + 0xFFFF);
    D_00F9B540->cur2 = v;
    D_00F9B540->y = -2944.0f - ((u16)v * 420 - 2520);
    D_00F9B540->cur3 = v;
    D_00F9B540->fb = D_00F9B540->cur3 / 2;
    D_00F9B540->fc = (u16)(D_00F9B540->cur2 / 2 - 1);
}
