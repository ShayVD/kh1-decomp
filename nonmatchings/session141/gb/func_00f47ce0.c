/* gb.x func_00f47ce0 near miss: 298 words differ, score 186 (ours 1280 bytes, original 1232). Port of wm func_00f6edd8's near miss (port.py), not worked further. See the wm file for notes. Round 22 (wwm1): the if/else at line(s) 85,123 with the arms swapped and the test negated (ifswap.py): score 186 -> 167. */
typedef struct { u8 pad[176]; s32 x; s32 y; u8 pad2[6]; s16 hbe; s16 pad3; s16 hc2; } Obj;
typedef struct { u8 a0; u8 pad1; u8 a2; u8 pad3[5]; u8 a8; u8 pad9[43]; u8 s34[44]; } Ent;
extern s32 D_002C5AD8;
extern s32 D_00F702D8;
extern s32 D_00F702DC;
extern s32 D_00F703C8;
extern s32 D_00F705B0;
extern s32 D_00F829D4;
extern s32 D_00F829D8;
extern s32 D_00F82AD0;
extern s32 D_00F82AEC;
extern s32 D_00F82AF0;
extern s32 D_00F82AF4;
void func_0011d768(s32);
s32 func_001ba3f0(s32);
u8 *func_001bc4e0(void);
s32 func_001bc510(void);
s32 func_001be278(void);
void func_001efb18(s32, s32);
void func_001f3840(Obj *);
s32 func_001f4338(Obj *);
s32 func_001f4400(Obj *);
void func_001f8ee0(Obj *);
void func_001f8f30(void);
s32 func_001fd548(Obj *);
s32 func_001fd590(Obj *);
s32 func_001fd618(Obj *);
void func_001fd858(Obj *);
void func_00202fc0(Obj *);
void func_002078f0(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00207938(Obj *, s32, s32, s32, s32, s32, s32, s32, u8 *);
void func_00208280(Obj *, s32, s32, s32, s32, s32);
s32 func_00f39330(void);
s32 func_00f39340(void);

void func_00f47ce0(Obj *o)
{
    s32 c[2];
    s32 selx, sely;
    s32 sel;
    Ent *base;
    s32 cnt;
    s32 cur;
    s32 hl;
    Ent *p;
    u8 *e;
    s32 n, i, k, y, num, s3;

    e = func_001bc4e0();
    n = func_001bc510() - 1;
    base = (Ent *)(e + 96);
    if (func_001f4338(o)) func_001fd858(o);
    k = 0;
    cur = func_001be278();
    cnt = 0;
    while (k < n && base[k].a8 != 0) {
        k++;
        cnt++;
    }
    n -= cnt;
    cur -= cnt;
    base += cnt;
    func_00202fc0(o);
    func_001f8ee0(o);
    i = func_001fd618(o);
    y = func_001fd590(o);
    sel = func_001fd548(o);
    num = 1 - n;
    if (func_001ba3f0(69)) num = 5 - n;
    if (func_001ba3f0(70)) num = 10 - n;
    for (k = 0; k < i; k++) {
        if (base[k].a0 == 0 && base[k].a8 == 0) num++;
    }
    o->hc2 = 2240;
    selx = 0;
    o->hbe = 0;
    sely = 0;
    p = &base[i];
    for (k = n + 1; k >= 0; k--) {
        if (i < n) {
            hl = 0;
            s3 = sel == i;
            if (D_00F82AD0) {
                if (!(s3)) {
                    c[0] = 6;
                    c[1] = 6;
                    if (cur == i) goto seven;
                } else {
                    c[0] = 0;
                    c[1] = 1;
                    hl = 1;
                }
            } else if (cur != i) {
                c[0] = 0;
                c[1] = 0;
            } else {
            seven:
                c[0] = 7;
                hl = 1;
                c[1] = 7;
            }
            if (p->a0 == 0 && p->a8 == 0) {
                func_001efb18(func_00f39330(), func_00f39340());
                func_002078f0(o, c[s3], 2, 0, 0, y, D_00F705B0, D_00F703C8, num + 196);
                num++;
            } else {
                func_00207938(o, c[s3], 2, 0, 0, y, D_00F705B0, D_00F703C8, p->s34);
            }
            if (s3) {
                selx = (o->x >> 4) + D_00F705B0 - 1792;
                sely = (o->y >> 4) + y - 1856;
            }
            func_00208280(o, 10, y + 4, 18, 49, hl ? 128 : 64);
            y += 28;
        }
        i++;
        p++;
    }
    func_001f8f30();
    if (func_001f4400(o)) {
        if (D_00F82AD0) D_00F702D8 = D_00F702DC = sel + cnt + 1;
        if (D_00F82AF4 != 0) {
            func_001f3840(o);
        } else {
            if (D_00F82AD0) {
                D_00F829D4 = selx;
                D_00F829D8 = sely;
                if (D_002C5AD8 & 0x2000) {
                    switch (D_00F82AEC) {
                    case 0:
                        if (base[sel].a2 == 0) {
                            func_0011d768(4);
                            return;
                        }
                    case 1:
                    case 2:
                        if (base[sel].a0 == 0) {
                            func_0011d768(4);
                            return;
                        }
                    }
                    D_00F82AF0 = sel + cnt;
                    func_0011d768(2);
                    func_001f3840(o);
                } else if (D_002C5AD8 & 0x4000) {
                    D_00F82AF0 = -1;
                    func_0011d768(3);
                    func_001f3840(o);
                }
            }
        }
    }
}
