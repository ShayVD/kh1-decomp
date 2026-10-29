/* Round 41 wwm2: score 327 -> 325, port.py of the wm twin func_00f73570 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* score 327 (2372 vs 2368). Port of the wm func_00f73570 near miss via portmap2.py (all symbols mapped); same remaining issues as wm, see that header. */
typedef struct { u8 pad[176]; s32 xB0; s32 xB4; } Obj;
typedef struct { u8 b0; u8 pad1[3]; u32 x4; } Item;
extern s32 D_00F702EC;
extern s32 D_00F702FC;
extern s32 D_00F70300;
extern s32 D_00F70338, D_00F7033C, D_00F70340, D_00F70344;
extern s32 D_00F70348, D_00F7034C, D_00F70350, D_00F70354;
extern s32 D_00F70358, D_00F7035C, D_00F70360, D_00F70364;
extern s32 D_00F70368;
extern s32 D_00F70390;
extern s32 D_00F70394;
extern s32 D_00F703B4;
extern s32 D_00F70434;
extern s32 D_00F70438;
extern s32 D_00F70688;
extern s32 D_00F7068C;
extern s32 D_00F70690;
extern s32 D_00F70694;
extern s32 D_00F7069C;
extern s32 D_00F706A8;
extern s32 D_00F706B8, D_00F706BC, D_00F706C0, D_00F706C4;
extern s32 D_00F706C8, D_00F706CC, D_00F706D0, D_00F706D4;
extern s32 D_00F706D8, D_00F706DC, D_00F706E0, D_00F706E4;
extern s32 D_00F706E8, D_00F706EC, D_00F706F0, D_00F706F4;
extern s32 D_00F706F8, D_00F706FC, D_00F70700, D_00F70704;
extern s32 D_00F70708, D_00F7070C, D_00F70710, D_00F70714;
extern s16 D_00F71270[];
extern s16 D_00F71288[];
extern s32 D_00F712D0;
extern s32 D_00F712E4;
extern s32 D_00F829D4;
extern s32 D_00F829D8;
extern s32 D_00F829EC;
extern s32 D_00F82D68;
extern s32 D_00F82D6C;
extern s32 D_00F82D70;
void func_001bb558(void);
Item *func_001bc4f0(void);
s32 func_001bc520(void);
void func_001efb18(s32, s32);
s32 func_001f3840(Obj *);
s32 func_001f42b8(Obj *);
s32 func_001f4390(Obj *);
void func_001f8ee0(Obj *);
void func_001f8f30(void);
s32 func_001f9438(Obj *, s32, s32, s32, s32, s32, s32);
s32 func_001fd548(Obj *);
s32 func_001fd590(Obj *);
s32 func_001fd618(Obj *);
void func_001fd858(Obj *);
s32 func_002014a0(Obj *, s32, s32, s32, s32, s32, s32, s32 *, s32, s32);
void func_00202fc0(Obj *);
void func_00206370(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_002078f0(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_0020bc48(s32, s32, s32);
s32 func_00f39330(void);
s32 func_00f39340(void);

#define C4(a, b, c, d) ((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))

void func_00f4c478(Obj *o)
{
    s32 pal[2];
    s32 c[2];
    s32 i, m, n, cnt, off, sel, y, k, t, xo, h, ca, cb;
    Item *items;
    Item *it;

    if (func_001f42b8(o) && D_00F712E4 == 0) func_001fd858(o);
    items = func_001bc4f0();
    n = func_001bc520();
    off = 0;
    if (D_00F712E4) {
        cnt = 0;
        m = func_001bc520();
        for (k = 0; k < m; k++) {
            switch (func_001bc4f0()[k].b0) {
            case 0:
                cnt++;
                break;
            case 1:
                cnt++;
                break;
            case 2:
                cnt++;
                break;
            case 3:
                cnt++;
                break;
            case 4:
                cnt++;
                break;
            case 5:
                cnt++;
                break;
            case 6:
                cnt++;
                break;
            case 7:
                cnt++;
                break;
            case 8:
                cnt++;
                break;
            case 9:
                break;
            }
        }
        off = (6 - cnt) * 28;
        func_001f8f30();
        ca = C4(D_00F706C8, D_00F706CC, D_00F706D0, D_00F706D4);
        h = D_00F7069C - D_00F7068C - off;
        cb = C4(D_00F706E8, D_00F706EC, D_00F706F0, D_00F706F4);
        func_00206370(o, D_00F70688, D_00F7068C + off, D_00F70690 - D_00F70688, h,
                      C4(D_00F706B8, D_00F706BC, D_00F706C0, D_00F706C4), ca,
                      C4(D_00F706D8, D_00F706DC, D_00F706E0, D_00F706E4), cb);
        func_00206370(o, D_00F70690, D_00F70694 + off, D_00F706A8 - D_00F70690, h, ca,
                      C4(D_00F706F8, D_00F706FC, D_00F70700, D_00F70704), cb,
                      C4(D_00F70708, D_00F7070C, D_00F70710, D_00F70714));
        func_001efb18(func_00f39330(), func_00f39340());
        ca = C4(D_00F70338, D_00F7033C, D_00F70340, D_00F70344);
        cb = C4(D_00F70348, D_00F7034C, D_00F70350, D_00F70354);
        func_00206370(o, D_00F70688, D_00F7068C + off, D_00F70690 - D_00F70688, D_00F70368, ca, cb, ca, cb);
        ca = C4(D_00F70348, D_00F7034C, D_00F70350, D_00F70354);
        cb = C4(D_00F70358, D_00F7035C, D_00F70360, D_00F70364);
        func_00206370(o, D_00F70690, D_00F7068C + off, D_00F706A8 - D_00F70690, D_00F70368, ca, cb, ca, cb);
        func_002014a0(o, 2, 2, D_00F702FC + D_00F70438, D_00F70300 + off, D_00F70434, D_00F70434 / 2, &D_00F712D0, 237, 14);
    }
    func_001bb558();
    if (D_00F712E4 == 0) {
        func_00202fc0(o);
        if (D_00F712E4 == 0) func_001f8ee0(o);
    }
    sel = -1;
    i = func_001fd618(o);
    y = func_001fd590(o);
    k = 9;
    t = func_001fd548(o);
    if (D_00F712E4 == 0) sel = t;
    y += off;
    func_001efb18(func_00f39330(), func_00f39340());
    for (; k >= 0; k--) {
        it = &items[i];
        if (i < n) {
            switch (D_00F82D6C) {
            case 0:
                pal[0] = 6;
                pal[1] = 9;
                c[0] = 0x80808080;
                c[1] = 0x80808080;
                break;
            case 1:
                if (D_00F712E4 == 0) {
                    pal[0] = 0;
                    pal[1] = 1;
                } else {
                    pal[0] = 6;
                    pal[1] = 9;
                }
                c[0] = 0x80808080;
                c[1] = 0x80FFFFFF;
                break;
            case 2:
                pal[0] = 6;
                pal[1] = 9;
                c[0] = 0x80808080;
                c[1] = 0x80808080;
                break;
            }
            if (D_00F712E4) {
                pal[0] = 9;
                pal[1] = 9;
                c[0] = 0x80808080;
                c[1] = 0x80808080;
            } else if (D_00F82D6C == 1 && it->b0 == 9) {
                pal[0] = 8;
                c[0] = 0x40808080;
                pal[1] = 9;
                c[1] = 0x80808080;
            }
            func_002078f0(o, pal[sel == i], 2, 0, 0, y, D_00F703B4, 16, D_00F71288[it->b0]);
            t = 0;
            switch (it->x4) {
            case 0x100: t = 7; break;
            case 0x200: t = 5; break;
            case 0x400: t = 6; break;
            case 0x800: t = 4; break;
            case 0x1000: t = 1; break;
            case 0x2000: break;
            case 0x4000: t = 3; break;
            case 0x8000: t = 2; break;
            default: t = 8; break;
            }
            xo = 0;
            if (it->b0 == 9) xo = D_00F702EC;
            func_001f9438(o, 2, D_00F70394 + xo, y + 5, 96, 15, c[sel == i]);
            func_001f9438(o, 1, D_00F70390, y + 5, D_00F71270[t], 15, c[sel == i]);
            if (D_00F82D6C && sel == i) {
                D_00F82D70 = i;
                if (func_001f4390(o)) {
                    D_00F829D4 = (o->xB0 >> 4) + D_00F703B4 - 1788;
                    D_00F829D8 = (o->xB4 >> 4) + y - 1856;
                }
            }
            if (D_00F712E4 && sel == i && func_001f4390(o)) {
                func_0020bc48(8, (o->xB0 >> 4) + D_00F703B4 - 1788, (o->xB4 >> 4) + y - 1856);
            }
            y += 28;
        }
        i++;
    }
    func_001f8f30();
    if (func_001f4390(o) && (D_00F82D68 || D_00F829EC)) func_001f3840(o);
}
