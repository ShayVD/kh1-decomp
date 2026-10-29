/* NEAR MISS 1405 words, score 1324 (5984 vs 6064 bytes). Port of gb func_00f446d0 (same score); D_00FB4AFC mapped by hand = gb D_00F7037C. See the gb file for notes. */
typedef struct {
    u8 x0, x1, x2, x3, x4, x5;
    u8 pad6[2];
    u16 x8, xA, xC;
    u16 padE;
    s32 x10;
    f32 x14, x18, x1C, x20;
    u8 pad24[8];
    f32 x2C, x30;
    u8 pad34[4];
    u8 c[4];
} Item;
extern s32 D_00FB4A70;
extern s32 D_00FB4A5C;
extern s32 D_0108F27C;
extern s32 D_0108F1F4;
extern s32 D_0108F280;
extern s32 D_0108F284;
extern u32 D_002C5AD8;
extern s32 D_00FB4B84, D_00FB4B88, D_00FB4B8C, D_00FB4B9C, D_00FB4BA0, D_00FB4BA4, D_00FB4BA8;
extern s32 D_00FB4C08, D_00FB4C0C, D_00FB4C10, D_00FB4BDC;
extern s32 D_00FB4B74, D_00FB4B78, D_00FB4B7C, D_00FB4B80;
extern s32 D_00FB4AEC, D_00FB4AF0, D_00FB4AF4, D_00FB4AF8;
extern s32 D_00FB4AFC, D_00FB4B00, D_00FB4B04, D_00FB4B08;
extern s32 D_00FB4BBC, D_00FB4BC0, D_00FB4BC4, D_00FB4BC8;
extern s32 D_00FB4BCC, D_00FB4BD0, D_00FB4BD4, D_00FB4BD8;
extern s32 D_00FB4BE0, D_00FB4BE4, D_00FB4BE8, D_00FB4BEC;
extern s32 D_00FB4BF0, D_00FB4BF4, D_00FB4BF8, D_00FB4BFC;
Item *func_00f6a480(void);
void func_00f6b5b0(Item *, f32, f32);
u8 *func_001bc4e0(void);
void func_0011d768(s32);
void func_0024e468(s32);
void func_001bfac8(void);
void func_00f6b5d0(s32, s32);
void func_00f6ade8(s32);

#define B(x) (*(u8 *)&(x))
#define POS(it, X, Y)                                \
    if (D_0108F27C == 0) {                           \
        it->x1C = (X);                               \
        it->x20 = (Y);                               \
    } else {                                         \
        it->x1C = (X) + D_00FB4BA4;                  \
        it->x20 = (Y) + D_00FB4BA8;                  \
    }                                                \
    it->x14 = it->x1C;                               \
    it->x18 = it->x20;                               \
    it->x30 = 0.0f;                                  \
    it->x2C = 0.0f;
#define COL(it, q0, q1, q2, q3) \
    it->c[0] = B(q0);        \
    it->c[1] = B(q1);        \
    it->c[2] = B(q2);        \
    it->c[3] = B(q3);
#define LABEL(it, id)                                           \
    it = func_00f6a480();                                       \
    it->x10 = id;                                               \
    it->x0 = 2;                                                 \
    it->x1 = 1;                                                 \
    it->xC = 3;                                                 \
    it->x3 = 0;                                                 \
    it->x5 = 15;                                                \
    POS(it, D_00FB4C08, y);                                     \
    COL(it, D_00FB4AEC, D_00FB4AF0, D_00FB4AF4, D_00FB4AF8);    \
    func_00f6b5b0(it, 256.0f, depth);
#define BOX(it, kind, X)                                        \
    it = func_00f6a480();                                       \
    it->x0 = 2;                                                 \
    it->x1 = kind;                                              \
    it->xC = 3;                                                 \
    it->x3 = 1;                                                 \
    it->x5 = 15;                                                \
    it->x10 = 0;                                                \
    POS(it, X, y);                                              \
    COL(it, D_00FB4AEC, D_00FB4AF0, D_00FB4AF4, D_00FB4AF8);    \
    func_00f6b5b0(it, 256.0f, depth);

void func_00f6b7c8(void) {
    Item *lab[16];
    Item *box[8];
    Item *rows[8];
    s32 flag;
    s32 wait;
    Item *head;
    f32 depth;
    Item *it;
    Item *s15;
    Item *cur;
    s32 i, y, n;
    u8 *t;

    depth = D_00FB4A70;
    wait = D_00FB4A70;
    for (;;) {
        it = func_00f6a480();
        it->x1 = 6;
        head = it;
        it->x0 = 2;
        it->xC = 1;
        it->x3 = 0;
        it->x5 = 15;
        it->x10 = 0;
        POS(it, D_00FB4B84, D_00FB4B88);
        it->xA = (D_00FB4B9C + 1) * D_00FB4BA0;
        it->x8 = *(u16 *)&D_00FB4B8C;
        COL(it, D_00FB4B74, D_00FB4B78, D_00FB4B7C, D_00FB4B80);
        func_00f6b5b0(it, 256.0f, depth);
        y = D_00FB4B88 + D_00FB4BA0 + D_00FB4BA0;
        for (i = 0; i < D_00FB4B9C / 2; i++) {
            it = func_00f6a480();
            it->x1 = 3;
            it->xC = 2;
            it->x0 = 2;
            it->x3 = 0;
            it->x5 = 15;
            it->x10 = 0;
            POS(it, D_00FB4B84 + 2, y);
            rows[i] = it;
            it->xA = *(u16 *)&D_00FB4BA0 - 1;
            it->x8 = *(u16 *)&D_00FB4B8C - 4;
            COL(it, D_00FB4BBC, D_00FB4BC0, D_00FB4BC4, D_00FB4BC8);
            func_00f6b5b0(it, 256.0f, depth);
            y += D_00FB4BA0 * 2;
        }
        y = D_00FB4C0C;
        LABEL(it, 21);
        lab[0] = it;
        it = func_00f6a480();
        box[0] = it;
        it->x5 = 4;
        it->x1 = 4;
        it->x0 = 2;
        it->xC = 3;
        it->x3 = 1;
        it->x10 = 0;
        POS(it, D_00FB4C10 + 2, y);
        lab[1] = it;
        COL(it, D_00FB4AEC, D_00FB4AF0, D_00FB4AF4, D_00FB4AF8);
        func_00f6b5b0(it, 256.0f, depth);
        y += D_00FB4BA0;
        LABEL(it, 15);
        s15 = it;
        lab[2] = it;
        BOX(it, 1, D_00FB4C10);
        box[3] = it;
        lab[3] = it;
        y += D_00FB4BA0;
        LABEL(it, 16);
        lab[4] = it;
        BOX(it, 1, D_00FB4C10);
        box[4] = it;
        lab[5] = it;
        y += D_00FB4BA0;
        LABEL(it, 17);
        lab[6] = it;
        BOX(it, 1, D_00FB4C10);
        box[5] = it;
        lab[7] = it;
        y += D_00FB4BA0;
        LABEL(it, 20);
        lab[8] = it;
        BOX(it, 1, D_00FB4C10);
        box[6] = it;
        lab[9] = it;
        y += D_00FB4BA0;
        LABEL(it, 18);
        lab[10] = it;
        BOX(it, 5, D_00FB4C10);
        box[1] = it;
        lab[11] = it;
        y += D_00FB4BA0;
        LABEL(it, 19);
        lab[12] = it;
        BOX(it, 5, D_00FB4C10);
        box[2] = it;
        lab[13] = it;
        cur = func_00f6a480();
        cur->x1 = 14;
        cur->x0 = 2;
        cur->xC = 3;
        cur->x3 = 0;
        cur->x5 = 15;
        n = D_00FB4A5C;
        cur->x10 = (s32)(func_001bc4e0() + n * 96 + 52);
        if (D_0108F27C == 0) {
            cur->x1C = D_00FB4BDC;
            cur->x20 = D_00FB4B88 + 4;
        } else {
            cur->x1C = D_00FB4BDC + D_00FB4BA4;
            cur->x20 = D_00FB4B88 + D_00FB4BA8 + 4;
        }
        cur->x14 = cur->x1C;
        cur->x18 = cur->x20;
        flag = 0;
        cur->x30 = 0.0f;
        cur->x2C = 0.0f;
        COL(cur, D_00FB4BE0, D_00FB4BE4, D_00FB4BE8, D_00FB4BEC);
        func_00f6b5b0(cur, 256.0f, depth);
        for (;;) {
            t = func_001bc4e0() + D_00FB4A5C * 96;
            if (t[0] == 0) {
                box[0]->x10 = 0;
                box[1]->x10 = 0;
                box[2]->x10 = 0;
            } else {
                box[0]->x10 = t[0];
                box[1]->x10 = t[5];
                box[2]->x10 = t[6];
            }
            if (D_0108F1F4 == 0) {
                for (i = 0; i < 14; i++) {
                    COL(lab[i], D_00FB4AEC, D_00FB4AF0, D_00FB4AF4, D_00FB4AF8);
                }
                for (i = 0; i < D_00FB4B9C / 2; i++) {
                    COL(rows[i], D_00FB4BBC, D_00FB4BC0, D_00FB4BC4, D_00FB4BC8);
                }
            } else {
                for (i = 0; i < 14; i++) {
                    COL(lab[i], D_00FB4AFC, D_00FB4B00, D_00FB4B04, D_00FB4B08);
                }
                for (i = 0; i < D_00FB4B9C / 2; i++) {
                    COL(rows[i], D_00FB4BCC, D_00FB4BD0, D_00FB4BD4, D_00FB4BD8);
                }
            }
            if (t[2]) {
                box[3]->x10 = 22;
            } else {
                box[3]->x10 = 23;
                COL(box[3], D_00FB4BF0, D_00FB4BF4, D_00FB4BF8, D_00FB4BFC);
                COL(s15, D_00FB4BF0, D_00FB4BF4, D_00FB4BF8, D_00FB4BFC);
            }
            box[4]->x10 = t[3] ? 22 : 23;
            box[5]->x10 = t[4] ? 22 : 23;
            if (t[7] == 0) {
                box[6]->x10 = 23;
            } else if (t[7] == 2) {
                box[6]->x10 = 229;
            } else {
                box[6]->x10 = 24;
            }
            n = D_00FB4A5C;
            cur->x10 = (s32)(func_001bc4e0() + n * 96 + 52);
            head->x10 = D_0108F1F4;
            if (D_0108F280 != 0) break;
            if (flag == 0) {
                flag = 1;
                func_00f6b5b0(cur, 256.0f, depth);
            }
            if (D_0108F284 == 0) {
                func_0024e468(1);
                continue;
            }
            if (D_002C5AD8 & 0x6000) {
                func_0011d768(3);
                break;
            }
            func_001bfac8();
        }
        func_00f6b5d0(2, 0);
        if (D_0108F284 == 0) {
            func_0024e468(wait);
        } else {
            for (n = wait; n > 0; n--) {
                func_001bfac8();
            }
        }
        func_00f6ade8(2);
        if (D_0108F284 != 0) return;
        while (D_0108F280 != 0) {
            func_0024e468(1);
        }
    }
}
