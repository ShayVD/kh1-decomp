/* score 327 (2372 vs 2368). The count switch needs a separate `cnt++; break;` per case 0..8 plus an explicit case 9, or gcc turns it into a range test instead of the 10-entry jump table. The draw loop uses two pairs: palette ids pal[2] (sp16) and colours c[2] (sp32), both indexed by sel == i. func_001fd548 is called unconditionally (t = ...; if (!D_00FB5A64) sel = t). The x4 switch needs t = 0 before it, with case 0x2000 an empty break. Left: the scheduling of the colour globals in the D_00FB5A64 block (the original keeps five %hi parts in s3..s7), the count index should share the k stack slot (sp48), and the x4 decision tree around 0x100/0x200. */
typedef struct { u8 pad[176]; s32 xB0; s32 xB4; } Obj;
typedef struct { u8 b0; u8 pad1[3]; u32 x4; } Item;
extern s32 D_00FB4A6C;
extern s32 D_00FB4A7C;
extern s32 D_00FB4A80;
extern s32 D_00FB4AB8, D_00FB4ABC, D_00FB4AC0, D_00FB4AC4;
extern s32 D_00FB4AC8, D_00FB4ACC, D_00FB4AD0, D_00FB4AD4;
extern s32 D_00FB4AD8, D_00FB4ADC, D_00FB4AE0, D_00FB4AE4;
extern s32 D_00FB4AE8;
extern s32 D_00FB4B10;
extern s32 D_00FB4B14;
extern s32 D_00FB4B34;
extern s32 D_00FB4BB4;
extern s32 D_00FB4BB8;
extern s32 D_00FB4E08;
extern s32 D_00FB4E0C;
extern s32 D_00FB4E10;
extern s32 D_00FB4E14;
extern s32 D_00FB4E1C;
extern s32 D_00FB4E28;
extern s32 D_00FB4E38, D_00FB4E3C, D_00FB4E40, D_00FB4E44;
extern s32 D_00FB4E48, D_00FB4E4C, D_00FB4E50, D_00FB4E54;
extern s32 D_00FB4E58, D_00FB4E5C, D_00FB4E60, D_00FB4E64;
extern s32 D_00FB4E68, D_00FB4E6C, D_00FB4E70, D_00FB4E74;
extern s32 D_00FB4E78, D_00FB4E7C, D_00FB4E80, D_00FB4E84;
extern s32 D_00FB4E88, D_00FB4E8C, D_00FB4E90, D_00FB4E94;
extern s16 D_00FB59F0[];
extern s16 D_00FB5A08[];
extern s32 D_00FB5A50;
extern s32 D_00FB5A64;
extern s32 D_0108F194;
extern s32 D_0108F198;
extern s32 D_0108F1AC;
extern s32 D_0108F528;
extern s32 D_0108F52C;
extern s32 D_0108F530;
void func_001bb558(void);
Item *func_001bc4f0(void);
s32 func_001bc520(void);
void func_001efb18(s32, s32);
void func_001f3840(Obj *);
s32 func_001f42b8(Obj *);
s32 func_001f4390(Obj *);
void func_001f8ee0(Obj *);
void func_001f8f30(void);
void func_001f9438(Obj *, s32, s32, s32, s32, s32, s32);
s32 func_001fd548(Obj *);
s32 func_001fd590(Obj *);
s32 func_001fd618(Obj *);
void func_001fd858(Obj *);
void func_002014a0(Obj *, s32, s32, s32, s32, s32, s32, s32 *, s32, s32);
void func_00202fc0(Obj *);
void func_00206370(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_002078f0(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_0020bc48(s32, s32, s32);
s32 func_00f60428(void);
s32 func_00f60438(void);

#define C4(a, b, c, d) ((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))

void func_00f73570(Obj *o)
{
    s32 pal[2];
    s32 c[2];
    s32 i, m, n, cnt, off, sel, y, k, t, xo, h, ca, cb;
    Item *items;
    Item *it;

    if (func_001f42b8(o) && D_00FB5A64 == 0) func_001fd858(o);
    items = func_001bc4f0();
    n = func_001bc520();
    off = 0;
    if (D_00FB5A64) {
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
        ca = C4(D_00FB4E48, D_00FB4E4C, D_00FB4E50, D_00FB4E54);
        h = D_00FB4E1C - D_00FB4E0C - off;
        cb = C4(D_00FB4E68, D_00FB4E6C, D_00FB4E70, D_00FB4E74);
        func_00206370(o, D_00FB4E08, D_00FB4E0C + off, D_00FB4E10 - D_00FB4E08, h,
                      C4(D_00FB4E38, D_00FB4E3C, D_00FB4E40, D_00FB4E44), ca,
                      C4(D_00FB4E58, D_00FB4E5C, D_00FB4E60, D_00FB4E64), cb);
        func_00206370(o, D_00FB4E10, D_00FB4E14 + off, D_00FB4E28 - D_00FB4E10, h, ca,
                      C4(D_00FB4E78, D_00FB4E7C, D_00FB4E80, D_00FB4E84), cb,
                      C4(D_00FB4E88, D_00FB4E8C, D_00FB4E90, D_00FB4E94));
        func_001efb18(func_00f60428(), func_00f60438());
        ca = C4(D_00FB4AB8, D_00FB4ABC, D_00FB4AC0, D_00FB4AC4);
        cb = C4(D_00FB4AC8, D_00FB4ACC, D_00FB4AD0, D_00FB4AD4);
        func_00206370(o, D_00FB4E08, D_00FB4E0C + off, D_00FB4E10 - D_00FB4E08, D_00FB4AE8, ca, cb, ca, cb);
        ca = C4(D_00FB4AC8, D_00FB4ACC, D_00FB4AD0, D_00FB4AD4);
        cb = C4(D_00FB4AD8, D_00FB4ADC, D_00FB4AE0, D_00FB4AE4);
        func_00206370(o, D_00FB4E10, D_00FB4E0C + off, D_00FB4E28 - D_00FB4E10, D_00FB4AE8, ca, cb, ca, cb);
        func_002014a0(o, 2, 2, D_00FB4A7C + D_00FB4BB8, D_00FB4A80 + off, D_00FB4BB4, D_00FB4BB4 / 2, &D_00FB5A50, 237, 14);
    }
    func_001bb558();
    if (D_00FB5A64 == 0) {
        func_00202fc0(o);
        if (D_00FB5A64 == 0) func_001f8ee0(o);
    }
    sel = -1;
    i = func_001fd618(o);
    y = func_001fd590(o);
    k = 9;
    t = func_001fd548(o);
    if (D_00FB5A64 == 0) sel = t;
    y += off;
    func_001efb18(func_00f60428(), func_00f60438());
    for (; k >= 0; k--) {
        it = &items[i];
        if (i < n) {
            switch (D_0108F52C) {
            case 0:
                pal[0] = 6;
                pal[1] = 9;
                c[0] = 0x80808080;
                c[1] = 0x80808080;
                break;
            case 1:
                if (D_00FB5A64 == 0) {
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
            if (D_00FB5A64) {
                pal[0] = 9;
                pal[1] = 9;
                c[0] = 0x80808080;
                c[1] = 0x80808080;
            } else if (D_0108F52C == 1 && it->b0 == 9) {
                pal[0] = 8;
                c[0] = 0x40808080;
                pal[1] = 9;
                c[1] = 0x80808080;
            }
            func_002078f0(o, pal[sel == i], 2, 0, 0, y, D_00FB4B34, 16, D_00FB5A08[it->b0]);
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
            if (it->b0 == 9) xo = D_00FB4A6C;
            func_001f9438(o, 2, D_00FB4B14 + xo, y + 5, 96, 15, c[sel == i]);
            func_001f9438(o, 1, D_00FB4B10, y + 5, D_00FB59F0[t], 15, c[sel == i]);
            if (D_0108F52C && sel == i) {
                D_0108F530 = i;
                if (func_001f4390(o)) {
                    D_0108F194 = (o->xB0 >> 4) + D_00FB4B34 - 1788;
                    D_0108F198 = (o->xB4 >> 4) + y - 1856;
                }
            }
            if (D_00FB5A64 && sel == i && func_001f4390(o)) {
                func_0020bc48(8, (o->xB0 >> 4) + D_00FB4B34 - 1788, (o->xB4 >> 4) + y - 1856);
            }
            y += 28;
        }
        i++;
    }
    func_001f8f30();
    if (func_001f4390(o) && (D_0108F528 || D_0108F1AC)) func_001f3840(o);
}
