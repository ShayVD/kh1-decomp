/* gb.x func_00f4cdb8 near miss: 105 words differ, score 152 (1424 = 1424 bytes). Port of wm func_00f73eb0's near miss (port.py maps it cleanly), not worked further. See the wm notes. */
typedef struct { s16 v[2]; } S2;
typedef struct { u8 pad[4]; u8 on; } Ic;
typedef struct { u8 pad[16]; s32 x10; } Win;
typedef struct { u8 pad[8]; u32 x8; } Pad;
typedef struct { u8 pad[12]; u16 xc; u16 xe; u8 pad2[14]; s16 x1e; } Lay;
extern Pad D_002C5AD0;
extern f32 D_00F702E0;
extern s32 D_00F702F0;
extern f32 D_00F70330;
extern u16 D_00F7038C;
extern u16 D_00F703B0;
extern s32 D_00F703B8;
extern s32 D_00F703BC;
extern s32 D_00F703EC;
extern s32 D_00F703F0;
extern s32 D_00F704A4;
extern s32 D_00F704A8;
extern s32 D_00F704AC;
extern s32 D_00F70518;
extern s32 D_00F7051C;
extern s32 D_00F70520;
extern s32 D_00F70524;
extern s32 D_00F70528;
extern s32 D_00F7052C;
extern s32 D_00F70530;
extern s32 D_00F705BC;
extern s32 D_00F705C0;
extern s32 D_00F705D0;
extern s32 D_00F712E4;
extern Lay D_00F712F0;
extern S2 D_00F74138;
extern S2 D_00F74140;
extern s32 D_00F829C8;
extern s32 D_00F829CC;
extern s32 D_00F829EC;
extern s32 D_00F829F8;
extern s32 D_00F82A0C;
extern s32 D_00F82A10;
extern s32 D_00F82A14;
extern f32 D_00F82A28;
extern s32 D_00F82D68;
extern s32 D_00F82D6C;
extern s32 D_00F82D70;
void func_0011d768(s32);
s16 func_001bc520(void);
void func_001be470(s32 *);
s32 func_001f31a8(Lay *, s32);
void func_001f3dc0(s32);
void func_0024e468(s32);
s32 func_00f20018(void);
void func_00f43cf0(s32);
void func_00f444b8(Ic *, f32, f32);
void func_00f444d8(s32, s32, s32);
void *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f4b978(s32, Win *);
void func_00f4be48(s32, Win *);
void func_00f4d880(Ic *, s32);

void func_00f4cdb8(void)
{
    Ic *ic[2];
    s32 tbl[2];
    S2 a;
    S2 b;
    s16 *pa;
    s32 i, sel, idx, mode, r, ptr;
    Win *w;
    u32 pad;
    s16 t;
    Ic **pp;

    sel = 0;
    a = D_00F74138;
    b = D_00F74140;
    pa = a.v;
    D_00F82A0C = D_00F705BC;
    D_00F82A10 = D_00F705C0;
    D_00F82A14 = D_00F705D0;
    D_00F702E0 = D_00F70330;
    D_00F82A28 = 128.0f;
    D_00F82D6C = 0;
    D_00F82D68 = 0;
    mode = D_00F702F0;
    D_00F829EC = 0;
    D_00F712E4 = 0;
    D_00F82D70 = 0;
    t = func_001bc520();
    D_00F712F0.xc = D_00F7038C;
    D_00F712F0.xe = D_00F703B0;
    D_00F712F0.x1e = t;
    D_00F829C8 = 0;
    r = func_001f31a8(&D_00F712F0, 1);
    func_001f3dc0(D_00F829CC);
    w = func_00f445a8(13, 2, 0, 2, 0, D_00F70518, b.v[0], 0, D_00F7051C, D_00F70520, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, func_00f20018() == 0 ? mode : 1);
    func_00f445a8(13, 0, 2, 1, 0, 15, 5, 4, D_00F704A4, D_00F704A8, 0, D_00F704AC, 0, 0, 0, 0, 0, 256, mode);
    pp = ic;
    ptr = D_00F703BC;
    for (i = 0; i < 2; i++) {
        pp[i] = func_00f445a8(13, 0, 2, 1, 0, 15, *pa++, 1, D_00F703B8, ptr, 0, D_00F703F0, 0, 0, 0, 0, 0, 0, mode);
        ptr += D_00F703EC;
    }
    idx = 0;
    pp[0]->on = 1;
    pp[1]->on = 0;
    func_00f4d880(pp[0], 8);
    for (i = 0; i < 2; i++) {
        func_00f444b8(pp[i], 256.0f, D_00F702F0);
        func_0024e468(2);
    }
    tbl[0] = 0;
    tbl[1] = 1;
    goto test;
loop:
    {
        if (pad & 0x2000) {
            func_0011d768(2);
            for (i = 0; i < 2; i++) {
                func_00f444b8(pp[i], 0.0f, D_00F702F0);
            }
            if (sel == 0) D_00F82D6C = 1;
            else D_00F82D6C = 2;
            func_001f3dc0(r);
            func_0024e468(D_00F702F0);
            if (sel == 0) func_00f4be48(r, w);
            else func_00f4b978(r, w);
            for (i = 0; i < 2; i++) {
                func_00f444b8(pp[i], 256.0f, D_00F702F0);
                func_0024e468(2);
            }
            func_0024e468(16);
            D_00F82D6C = 0;
            func_001f3dc0(D_00F829CC);
            pad = 0;
        }
        if (pad & 0x50) {
            sel++; sel &= 1;
            func_0011d768(1);
            idx = sel * 4;
        }
        (*(Ic **)((u8 *)pp + idx))->on = 1;
        (*(Ic **)((u8 *)pp + (((sel + 1) & 1) << 2)))->on = 0;
        w->x10 = b.v[sel];
        func_00f4d880((*(Ic **)((u8 *)pp + idx)), 8);
        func_0024e468(1);
    }
test:
    pad = D_002C5AD0.x8;
    pad |= pad >> 24;
    if (!(pad & 0x4000)) goto loop;
    func_0011d768(3);
    D_00F702E0 = D_00F70330;
    D_00F82D68 = 1;
    D_00F82A0C = D_00F705BC;
    D_00F82A28 = 128.0f;
    D_00F82A10 = D_00F705C0;
    D_00F82A14 = D_00F705D0;
    func_00f444d8(13, 0, D_00F702F0);
    func_0024e468(D_00F702F0);
    func_00f43cf0(13);
    if (D_00F829F8 > 0) D_00F829F8 = -1;
    func_001be470(&D_00F829F8);
}
