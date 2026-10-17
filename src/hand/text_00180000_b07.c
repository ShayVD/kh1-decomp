#include "common.h"
typedef int u128 __attribute__((mode(TI)));

typedef struct {
    s32 key;
    s32 mask;
    s8 start;
    s8 len;
    u8 used;
} Slot;

typedef struct {
    u8 pad[0x88];
    s32 key;
    u8 pad8c[7];
    u8 bit;
} SlotOwner;

void func_00180e80(Slot *);

s32 func_00180f18(Slot *slots, s32 cnt, SlotOwner *o, u8 n) {
    union { u128 q; u8 b[16]; } buf;
    s32 i;
    s32 j;
    s32 run;
    s32 found;
    s32 key;
    s32 bit;
    Slot *best;
    Slot *s;

    key = o->key;
    bit = o->bit;
    for (i = 0; i < cnt; i++) {
        if (slots[i].used && key == slots[i].key) {
            s32 m = slots[i].mask;
            j = 1 << bit;
            if (m & j) return -1;
            slots[i].mask = m | j;
            return slots[i].start;
        }
    }
    buf.q = 0;
    for (i = 0; i < cnt; i++) {
        if (slots[i].used) {
            j = slots[i].len;
            if (j > 0) {
                u8 *p = (u8 *)((u32)slots[i].start + (u32)buf.b);
                do {
                    j--;
                    *p++ = 1;
                } while (j != 0);
            }
        }
    }
    run = 0;
    found = -1;
    for (i = 0; i < cnt; i++) {
        if (buf.b[i]) {
            run = 0;
        } else {
            run++;
            if (run == n) {
                found = i - n + 1;
                break;
            }
        }
    }
    if (found > 0) {
        for (i = 0; i < cnt; i++) {
            if (!slots[i].used) {
                slots[i].key = key;
                slots[i].mask = 1 << bit;
                slots[i].used = 1;
                slots[i].len = n;
                slots[i].start = found;
                return found;
            }
        }
    }
    best = 0;
    found = -1;
    for (i = 0; i < cnt; i++) {
        s = &slots[i];
        if (s->used) {
            if (n == s->len) {
                s->key = key;
                s->mask = 1 << bit;
                return s->start;
            }
            if (n < s->len) {
                if (best == 0 || s->len - n < found) {
                    found = s->len - n;
                    best = s;
                }
            }
        }
    }
    if (best) {
        best->key = key;
        best->len = n;
        best->mask = 1 << bit;
        return best->start;
    }
    for (i = 0; i < cnt; i++) {
        if (slots[i].used && slots[i].start < n) func_00180e80(&slots[i]);
    }
    for (i = 0; i < cnt; i++) {
        if (!slots[i].used) {
            slots[i].key = key;
            slots[i].mask = 1 << bit;
                slots[i].used = 1;
            slots[i].len = n;
            slots[i].start = 0;
            return 0;
        }
    }
    return -1;
}
