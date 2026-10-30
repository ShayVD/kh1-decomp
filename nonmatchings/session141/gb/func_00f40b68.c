/* Round 41 wwm2: score 26 -> 24, port.py of the wm twin func_00f67c60 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* Round 35 (wgb): no change (30 words). The target has cur += 6 in the delay slot of the merged func_00f3c8c8 call at the loop head, so in the original it sits right after that call in the same block. A loop with func_00f3c8c8(buf, cur, sel); cur += 6; at the top puts it there (27 words, score 28) but loses the cross-jumped pre-loop (buf, 0, 0) call. Tried: cur += 6 after each call (both paths), goto into the loop, k = cur % 6 temporaries. */
typedef struct {
    u8 pad[8];
    u32 btn;
} Pad;

s32 func_001ba9d8(s32);
void func_00f3cc20(void *, s32, s32);
void func_00f3c8c8(char *, s32, s32);
void func_001bfac8(void);
Pad *func_001ba488(s32);
s32 func_00f40780(s32, s32, u32);
void func_00f40830();
void func_00f409d0(char *);

s32 func_00f40b68(void *x, s32 unused, s32 y) {
    char buf[32];
    s32 sel;
    s32 cur;
    s32 v;
    s32 n;
    u32 btn;
    Pad *pad;

    sel = 0;
    cur = 0;
    v = 0;
    func_00f3cc20(x, func_001ba9d8(0), y);
    func_00f3c8c8(buf, sel, v);
    while (1) {
        func_001bfac8();
        pad = func_001ba488(0);
        btn = pad->btn;
        if (btn & 0x400) {
            cur--;
        }
        if (btn & 0x800) {
            cur++;
        }
        sel = (cur + 6) % 6;
        cur = sel;
        v = func_00f40780(sel, v, btn);
        if (btn & 0x1000) {
            return 0;
        }
        if ((btn & 8) && buf[0]) {
            return 1;
        }
        n = 0;
        while (buf[n]) {
            n++;
        }
        n /= 2;
        if (n < 8 && (btn & 0x2000)) {
            func_00f40830(buf, sel, v);
        }
        if (n > 0 && (pad->btn & 0x4000)) {
            func_00f409d0(buf);
        }
        func_00f3cc20(x, func_001ba9d8(0), y);
        func_00f3c8c8(buf, sel, v);
    }
}
