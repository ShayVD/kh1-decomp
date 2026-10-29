/* 73 words left (436 vs 448): switch decision-tree layout differs. Tried case orders, if-chains. */
typedef struct { u16 id; u8 pad[10]; } It502e8;
typedef struct { u8 pad[4]; u16 count; } Inv502e8;
typedef struct {
    u8 pad[0x4C];
    u16 cur;
    u8 pad2[0xA0 - 0x4E];
    Inv502e8 inv;
    u8 pad3[0x114 - 0xA6];
    It502e8 items[1];
} W502e8;
s32 func_001ba3f0(s32);
s32 func_001be680(void);
s32 func_001be6c8(s32);
s32 func_001be710(s32);
extern W502e8 *D_00F9B540;

s32 func_00f502e8(void) {
    W502e8 *w = D_00F9B540;
    Inv502e8 *inv;
    It502e8 *p;
    s32 a = 0;
    s32 b = 0;
    s32 c = 0;
    s32 i;
    s32 k;

    inv = &w->inv;
    if (inv->count >= func_001be680()) {
        return func_001be680() >= 200 ? 29 : 28;
    }
    p = w->items;
    for (i = 0; i < inv->count; i++) {
        k = p->id - 1;
        switch (k) {
        case 0 ... 3:
            a++;
            break;
        case 4 ... 8:
            b++;
            break;
        case 58 ... 63:
            c++;
            break;
        }
        p++;
    }
    k = D_00F9B540->cur - 1;
    switch (k) {
    case 0 ... 3:
        if (a > 0) {
            return 234;
        }
        return 0;
    case 4 ... 8:
        if (b < func_001be6c8(k)) {
            return 0;
        }
        return func_001ba3f0(70) != 0 ? 230 : 26;
    case 58 ... 63:
        if (c < func_001be710(k)) {
            return 0;
        }
        return func_001ba3f0(70) != 0 ? 231 : 27;
    }
    return 0;
}
