/* func_001cf348: 19 words (score 6) off, mode hand/nostrict_nogcse. The loop-top copy 't = base' (re-set at loop end) is what stops the giv/invariant hoist. Off: 'move s0,zero' is scheduled early instead of in the blez slot, and 'addiu s0' before the addu. cf3e0 is the same function with D_003DABD4, a u8 count and bit 34. */
typedef struct { u8 pad[12400]; u64 d12400; } Big3;
extern Big3 D_00389C90;
typedef struct { s32 x0; s32 n; s32 off[1]; } Tbl;
extern Tbl *D_003DABD0;
void func_00155be0(void *p);
void func_001cf348(void) {
    Tbl *base;
    Tbl *t;
    s32 i, n;
    D_00389C90.d12400 &= ~0x200000000ULL;
    base = D_003DABD0;
    n = base->n;
    t = base;
    for (i = 0; i < n; i++) {
        func_00155be0((u8 *)t + *(s32 *)(i * 4 + (u8 *)t + 8));
        t = base;
    }
}
