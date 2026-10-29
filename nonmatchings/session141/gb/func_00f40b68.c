/* Round 35 (wgb): no change (30 words). The target has cur += 6 in the delay slot of the merged func_00f3c8c8 call at the loop head, so in the original it sits right after that call in the same block. A loop with func_00f3c8c8(buf, cur, sel); cur += 6; at the top puts it there (27 words, score 28) but loses the cross-jumped pre-loop (buf, 0, 0) call. Tried: cur += 6 after each call (both paths), goto into the loop, k = cur % 6 temporaries. */
/* 30 words / score 26 (size right). An explicit pre-loop func_00f3c8c8(buf, 0, 0) plus the call at the loop end reproduces the original's cross-jumped loop head. Left: the original does cur += 6 in the delay slot of that merged call; ours schedules it after func_001ba488, which shifts everything after it by one slot. Tried cur += 6 at the top of the loop, a t = cur + 6 temporary, a separate k = cur % 6, and the norlo/fmam/nosi modes. */
#include "ovl.h"

typedef struct { u8 pad[8]; s32 btn; } GbPad;
GbPad *func_001ba488(s32);
s32 func_001ba9d8(s32);
void func_001bfac8(void);
void func_00f3c8c8(s8 *, s32, s32);
void func_00f3cc20(s32, s32, s32);
s32 func_00f40780(s32, s32, s32);
void func_00f40830(s8 *, s32, s32);
void func_00f409d0(s8 *);

s32 func_00f40b68(s32 a, s32 b, s32 c) {
    s8 buf[32];
    s32 cur = 0;
    s32 sel = 0;
    s32 len;
    GbPad *pad;
    s32 btn;
    func_00f3cc20(a, func_001ba9d8(0), c);
    func_00f3c8c8(buf, 0, 0);
    for (;;) {
        cur += 6;
        func_001bfac8();
        pad = func_001ba488(0);
        btn = pad->btn;
        if (btn & 0x400)
            cur--;
        if (btn & 0x800)
            cur++;
        cur %= 6;
        sel = func_00f40780(cur, sel, btn);
        if (btn & 0x1000)
            return 0;
        if ((btn & 8) && buf[0] != 0)
            return 1;
        for (len = 0; buf[len]; len++);
        len /= 2;
        if (len < 8 && (btn & 0x2000))
            func_00f40830(buf, cur, sel);
        if (len > 0 && (pad->btn & 0x4000))
            func_00f409d0(buf);
        func_00f3cc20(a, func_001ba9d8(0), c);
        func_00f3c8c8(buf, cur, sel);
    }
}
