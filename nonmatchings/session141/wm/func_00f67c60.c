/* score 24 (23 words; was 46). Round 31 wwm2: hill2 put `v = 0` after `cur = 0` (35 -> 30 words), then dropping `cur += 6` at the loop top and writing `sel = (cur + 6) % 6` gave 23. Left: the original has `addiu s3,s3,6` in the delay slot of the jal func_00f639c0 before the loop, and cur-1 in a0 rather than v1; moving `cur += 6` after the calls, duplicating it at the loop end or starting cur at 6 is worse; ctx2 gives nothing. Earlier header: func_00f67c60: near miss (session 141 round 4), score 46, 35 words: loop shape right (f63d18 before the loop, f639c0 call duplicated before the loop and at the end, so the loop top is the f639c0 call). Left: the original keeps the stepped value (cur, s3) and the result of % 6 (sel, s2) in swapped registers, and puts cur += 6 in the f639c0 delay slot; ours schedules it after func_001ba488. Tried cur/sel temps in several orders, every flag mode, and the permuter (nothing equivalent). */
typedef struct {
    u8 pad[8];
    u32 btn;
} Pad;

s32 func_001ba9d8(s32);
void func_00f63d18(void *, s32, s32);
void func_00f639c0(char *, s32, s32);
void func_001bfac8(void);
Pad *func_001ba488(s32);
s32 func_00f67878(s32, s32, u32);
void func_00f67928();
void func_00f67ac8(char *);

s32 func_00f67c60(void *x, s32 unused, s32 y) {
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
    func_00f63d18(x, func_001ba9d8(0), y);
    func_00f639c0(buf, sel, v);
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
        v = func_00f67878(sel, v, btn);
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
            func_00f67928(buf, sel, v, 0, 0); /* lim and base: set by its switch, sel is 0-5 */
        }
        if (n > 0 && (pad->btn & 0x4000)) {
            func_00f67ac8(buf);
        }
        func_00f63d18(x, func_001ba9d8(0), y);
        func_00f639c0(buf, sel, v);
    }
}
