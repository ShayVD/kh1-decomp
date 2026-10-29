/* NEAR MISS 1405 words, score 1324 (5984 vs 6064 bytes). Structurally complete draft, not polished (time-boxed). Settings/option panel: builds a header item, D_00F7041C/2 row items, then 7 label+box item pairs via func_00f43388/func_00f444b8 (LABEL/BOX/POS/COL macros), then the cursor item; the inner loop refreshes box values from the func_001bc4e0() record (stride 96) and colours per D_00F82A34 until D_00F82AC0 or pad 0x6000. The call sequence matches the original call for call. Left: the original keeps depth in f21 and 0.0f in f20 (ours swaps them), different stack slots for the item arrays (orig: lab[14] at sp+0, box at sp+64.., rows at sp+96, flag at 128, wait at 132, head at 136), and lbu/lui addressing of the colour globals. */
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
extern s32 D_00F702F0;
extern s32 D_00F702DC;
extern s32 D_00F82ABC;
extern s32 D_00F82A34;
extern s32 D_00F82AC0;
extern s32 D_00F82AC4;
extern u32 D_002C5AD8;
extern s32 D_00F70404, D_00F70408, D_00F7040C, D_00F7041C, D_00F70420, D_00F70424, D_00F70428;
extern s32 D_00F70488, D_00F7048C, D_00F70490, D_00F7045C;
extern s32 D_00F703F4, D_00F703F8, D_00F703FC, D_00F70400;
extern s32 D_00F7036C, D_00F70370, D_00F70374, D_00F70378;
extern s32 D_00F7037C, D_00F70380, D_00F70384, D_00F70388;
extern s32 D_00F7043C, D_00F70440, D_00F70444, D_00F70448;
extern s32 D_00F7044C, D_00F70450, D_00F70454, D_00F70458;
extern s32 D_00F70460, D_00F70464, D_00F70468, D_00F7046C;
extern s32 D_00F70470, D_00F70474, D_00F70478, D_00F7047C;
Item *func_00f43388(void);
void func_00f444b8(Item *, f32, f32);
u8 *func_001bc4e0(void);
void func_0011d768(s32);
void func_0024e468(s32);
void func_001bfac8(void);
void func_00f444d8(s32, s32);
void func_00f43cf0(s32);

#define B(x) (*(u8 *)&(x))
#define POS(it, X, Y)                                \
    if (D_00F82ABC == 0) {                           \
        it->x1C = (X);                               \
        it->x20 = (Y);                               \
    } else {                                         \
        it->x1C = (X) + D_00F70424;                  \
        it->x20 = (Y) + D_00F70428;                  \
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
    it = func_00f43388();                                       \
    it->x10 = id;                                               \
    it->x0 = 2;                                                 \
    it->x1 = 1;                                                 \
    it->xC = 3;                                                 \
    it->x3 = 0;                                                 \
    it->x5 = 15;                                                \
    POS(it, D_00F70488, y);                                     \
    COL(it, D_00F7036C, D_00F70370, D_00F70374, D_00F70378);    \
    func_00f444b8(it, 256.0f, depth);
#define BOX(it, kind, X)                                        \
    it = func_00f43388();                                       \
    it->x0 = 2;                                                 \
    it->x1 = kind;                                              \
    it->xC = 3;                                                 \
    it->x3 = 1;                                                 \
    it->x5 = 15;                                                \
    it->x10 = 0;                                                \
    POS(it, X, y);                                              \
    COL(it, D_00F7036C, D_00F70370, D_00F70374, D_00F70378);    \
    func_00f444b8(it, 256.0f, depth);

void func_00f446d0(void) {
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

    depth = D_00F702F0;
    wait = D_00F702F0;
    for (;;) {
        it = func_00f43388();
        it->x1 = 6;
        head = it;
        it->x0 = 2;
        it->xC = 1;
        it->x3 = 0;
        it->x5 = 15;
        it->x10 = 0;
        POS(it, D_00F70404, D_00F70408);
        it->xA = (D_00F7041C + 1) * D_00F70420;
        it->x8 = *(u16 *)&D_00F7040C;
        COL(it, D_00F703F4, D_00F703F8, D_00F703FC, D_00F70400);
        func_00f444b8(it, 256.0f, depth);
        y = D_00F70408 + D_00F70420 + D_00F70420;
        for (i = 0; i < D_00F7041C / 2; i++) {
            it = func_00f43388();
            it->x1 = 3;
            it->xC = 2;
            it->x0 = 2;
            it->x3 = 0;
            it->x5 = 15;
            it->x10 = 0;
            POS(it, D_00F70404 + 2, y);
            rows[i] = it;
            it->xA = *(u16 *)&D_00F70420 - 1;
            it->x8 = *(u16 *)&D_00F7040C - 4;
            COL(it, D_00F7043C, D_00F70440, D_00F70444, D_00F70448);
            func_00f444b8(it, 256.0f, depth);
            y += D_00F70420 * 2;
        }
        y = D_00F7048C;
        LABEL(it, 21);
        lab[0] = it;
        it = func_00f43388();
        box[0] = it;
        it->x5 = 4;
        it->x1 = 4;
        it->x0 = 2;
        it->xC = 3;
        it->x3 = 1;
        it->x10 = 0;
        POS(it, D_00F70490 + 2, y);
        lab[1] = it;
        COL(it, D_00F7036C, D_00F70370, D_00F70374, D_00F70378);
        func_00f444b8(it, 256.0f, depth);
        y += D_00F70420;
        LABEL(it, 15);
        s15 = it;
        lab[2] = it;
        BOX(it, 1, D_00F70490);
        box[3] = it;
        lab[3] = it;
        y += D_00F70420;
        LABEL(it, 16);
        lab[4] = it;
        BOX(it, 1, D_00F70490);
        box[4] = it;
        lab[5] = it;
        y += D_00F70420;
        LABEL(it, 17);
        lab[6] = it;
        BOX(it, 1, D_00F70490);
        box[5] = it;
        lab[7] = it;
        y += D_00F70420;
        LABEL(it, 20);
        lab[8] = it;
        BOX(it, 1, D_00F70490);
        box[6] = it;
        lab[9] = it;
        y += D_00F70420;
        LABEL(it, 18);
        lab[10] = it;
        BOX(it, 5, D_00F70490);
        box[1] = it;
        lab[11] = it;
        y += D_00F70420;
        LABEL(it, 19);
        lab[12] = it;
        BOX(it, 5, D_00F70490);
        box[2] = it;
        lab[13] = it;
        cur = func_00f43388();
        cur->x1 = 14;
        cur->x0 = 2;
        cur->xC = 3;
        cur->x3 = 0;
        cur->x5 = 15;
        n = D_00F702DC;
        cur->x10 = (s32)(func_001bc4e0() + n * 96 + 52);
        if (D_00F82ABC == 0) {
            cur->x1C = D_00F7045C;
            cur->x20 = D_00F70408 + 4;
        } else {
            cur->x1C = D_00F7045C + D_00F70424;
            cur->x20 = D_00F70408 + D_00F70428 + 4;
        }
        cur->x14 = cur->x1C;
        cur->x18 = cur->x20;
        flag = 0;
        cur->x30 = 0.0f;
        cur->x2C = 0.0f;
        COL(cur, D_00F70460, D_00F70464, D_00F70468, D_00F7046C);
        func_00f444b8(cur, 256.0f, depth);
        for (;;) {
            t = func_001bc4e0() + D_00F702DC * 96;
            if (t[0] == 0) {
                box[0]->x10 = 0;
                box[1]->x10 = 0;
                box[2]->x10 = 0;
            } else {
                box[0]->x10 = t[0];
                box[1]->x10 = t[5];
                box[2]->x10 = t[6];
            }
            if (D_00F82A34 == 0) {
                for (i = 0; i < 14; i++) {
                    COL(lab[i], D_00F7036C, D_00F70370, D_00F70374, D_00F70378);
                }
                for (i = 0; i < D_00F7041C / 2; i++) {
                    COL(rows[i], D_00F7043C, D_00F70440, D_00F70444, D_00F70448);
                }
            } else {
                for (i = 0; i < 14; i++) {
                    COL(lab[i], D_00F7037C, D_00F70380, D_00F70384, D_00F70388);
                }
                for (i = 0; i < D_00F7041C / 2; i++) {
                    COL(rows[i], D_00F7044C, D_00F70450, D_00F70454, D_00F70458);
                }
            }
            if (t[2]) {
                box[3]->x10 = 22;
            } else {
                box[3]->x10 = 23;
                COL(box[3], D_00F70470, D_00F70474, D_00F70478, D_00F7047C);
                COL(s15, D_00F70470, D_00F70474, D_00F70478, D_00F7047C);
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
            n = D_00F702DC;
            cur->x10 = (s32)(func_001bc4e0() + n * 96 + 52);
            head->x10 = D_00F82A34;
            if (D_00F82AC0 != 0) break;
            if (flag == 0) {
                flag = 1;
                func_00f444b8(cur, 256.0f, depth);
            }
            if (D_00F82AC4 == 0) {
                func_0024e468(1);
                continue;
            }
            if (D_002C5AD8 & 0x6000) {
                func_0011d768(3);
                break;
            }
            func_001bfac8();
        }
        func_00f444d8(2, 0);
        if (D_00F82AC4 == 0) {
            func_0024e468(wait);
        } else {
            for (n = wait; n > 0; n--) {
                func_001bfac8();
            }
        }
        func_00f43cf0(2);
        if (D_00F82AC4 != 0) return;
        while (D_00F82AC0 != 0) {
            func_0024e468(1);
        }
    }
}
