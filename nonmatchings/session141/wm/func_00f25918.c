/* score 530 (3808 vs 3832). Main-menu state machine: wait D_00FBAA90 == 3, ids[] from func_00f2ac10(n) >= 3, D_00FBB550 = index of D_00FBB330, three intro branches (func_001b9b78(3)/(4) and func_001bb370), then do { if (state == 4) ...; switch (state - 1) { 5 cases } } while (state) (jump table of 5), slide-out loop with n = D_00F878E0 and func_00f22d70. Lerps need n as a variable: v = (0 - 640) * i / n + 640. Moving the integer lerps into temps v/k before the func_00f21ef0 float call took it 644 -> 530. Left: register allocation of n/prev/id across the cases and some lerp temps; 24 bytes short. Round 28 wwm2. */
extern s32 D_00FBAA90;
extern s32 D_00FBAA68;
extern s32 D_00FBAA70;
extern s32 D_00FBAA74;
extern s32 D_00FBB550;
extern s32 D_00FBB330;
extern s32 D_00F878E0;
extern s32 D_00F878E4;
void func_001bfac8(void);
s32 func_00f2ac10(s32);
void func_00f29500(s32, s32, s32);
s32 func_001b9b78(s32);
void func_001b9bb0(s32, s32);
s32 func_001bb370(void);
void func_001ba358(s32, s32);
void func_0011d140(s32, s32);
void func_0011d1a8(s32, s32, s32);
void func_00f28448(s32, s32, s32, s32 *);
void func_00f28a68(s32, s32, s32);
void func_00f28e58(void);
void func_00f258c8(s32);
void func_00f25728(s32, s32, s32 *, s32, s32, s32, s32, s32);
void func_00f28ed8(s32, s32, s32, f32);
void func_00f29418(void);
void func_00f21ef0(f32);
void func_00f26810(s32, s32, s32, s32);
void func_00f26e80(s32, s32, s32 *, s32, f32);
void func_00f27ff0(s32, s32, s32 *);
s32 func_00f26d50(s32, s32 *);
s32 func_00f27a00(s32 *);
s32 func_00f28158(s32 *);
void func_00f22d70(void);

void func_00f25918(void)
{
    s32 ids[32];
    s32 prev;
    s32 *q;
    s32 id;
    s32 state;
    s32 n;
    s32 i;
    s32 v;
    s32 k;

    while (D_00FBAA90 != 3) {
        func_001bfac8();
    }
    q = ids;
    if (func_00f2ac10(0) >= 3) *q++ = 3;
    if (func_00f2ac10(1) >= 3) *q++ = 4;
    if (func_00f2ac10(2) >= 3) *q++ = 11;
    if (func_00f2ac10(3) >= 3) *q++ = 5;
    if (func_00f2ac10(4) >= 3) *q++ = 8;
    if (func_00f2ac10(6) >= 3) *q++ = 9;
    if (func_00f2ac10(5) >= 3) *q++ = 10;
    if (func_00f2ac10(7) >= 3) *q++ = 13;
    if (func_00f2ac10(8) >= 3) *q++ = 15;
    if (func_00f2ac10(9) >= 3) *q++ = 16;
    *q = 0;
    q = ids;
    D_00FBB550 = 0;
    while (*q != 0 && *q != D_00FBB330) {
        q++;
        D_00FBB550++;
    }
    state = 1;
    func_00f29500(0, 0x3600, D_00FBAA68);
    func_001bfac8();
    id = D_00FBB330;
    if (func_001b9b78(3) == 0 && func_001bb370() == 0) {
        D_00FBAA70 = -0x200;
        n = 10;
        D_00FBAA74 = 0;
        D_00F878E4 = 0;
        for (i = 0; i < n; i++) {
            v = (0 - 640) * i / n + 640;
            func_00f29500(0, 0x3600, D_00FBAA68);
            func_00f28448(-v, 0, 128, ids);
            func_00f28a68(v, 0, 128);
            func_001bfac8();
        }
        func_00f28e58();
        func_00f258c8(0);
        for (i = 0; i < n; i++) {
            v = 640 * i / n;
            func_00f25728(1, id, ids, v - 640, 0, 0, 0, (0 - 96) * i / n + 96);
            func_00f28a68(v, 0, 128);
            func_001bfac8();
        }
        D_00F878E4 = 1;
        func_001b9bb0(3, 1);
    } else if (func_001b9b78(4) == 0 && func_001bb370() != 0) {
        n = 14;
        D_00FBAA70 = -0x200;
        func_001ba358(140, 1);
        D_00FBAA74 = 0;
        func_001ba358(118, 1);
        D_00F878E4 = 0;
        for (i = 0; i < n; i++) {
            if (i == 3) {
                func_0011d140(11, 0x1111);
            }
            func_00f29500(0, 0x3600, D_00FBAA68);
            func_00f28448(i < 8 ? (0 - 640) * i / 8 + 640 : 0, 0, 128, ids);
            func_00f28ed8(0, 0, 128, (f32)i * 100.0f / (f32)n + 0.0f);
            func_001bfac8();
        }
        func_00f29418();
        n = 10;
        func_0011d1a8(11, 0x1111, 10);
        func_00f258c8(0);
        for (i = 0; i < n; i++) {
            v = (0 - 96) * i / n + 96;
            k = (0 - 128) * i / n + 128;
            func_00f21ef0((f32)i * -100.0f / (f32)n + 100.0f);
            func_00f25728(1, id, ids, 0, 0, 0, 0, v);
            func_00f28ed8(0, 0, k, 100.0f);
            func_001bfac8();
        }
        func_00f21ef0(0.0f);
        D_00F878E4 = 1;
        func_001b9bb0(4, 1);
    } else {
        n = 8;
        for (i = 0; i < n; i++) {
            v = 640 * i / n;
            D_00FBAA70 = 0x70;
            D_00FBAA74 = -0x30;
            func_00f29500(0, 0x3600, D_00FBAA68);
            func_00f28448(640 - v, 0, 0, ids);
            func_00f26810(v - 640, 0, id, 0);
            func_001bfac8();
        }
    }
    n = 10;
    prev = 1;
    do {
        if (state == 4) {
            state = func_001bb370() != 0 ? 5 : state;
        }
        switch (state - 1) {
        case 0:
            D_00FBAA70 = 0x70;
            prev = state;
            D_00FBAA74 = -0x30;
            state = func_00f26d50(id, ids);
            if (state != 0) {
                func_00f258c8(1);
            }
            D_00F878E4 = 0;
            if (state == 2) {
                for (i = 0; i < n; i++) {
                    v = 640 * i / n;
                    D_00FBAA74 = -0x30;
                    D_00FBAA70 = 0x70 - v;
                    func_00f29500(0, 0x3600, D_00FBAA68);
                    func_00f28448(0, 0, 0, ids);
                    func_00f26810(-v, 0, id, 0);
                    func_00f26e80(640 - v, 0, ids, 1, 0.0f);
                    func_001bfac8();
                }
            } else if (state == 3) {
                for (i = 0; i < n; i++) {
                    v = 640 * i / n;
                    D_00FBAA74 = -0x30;
                    D_00FBAA70 = v + 0x70;
                    func_00f29500(0, 0x3600, D_00FBAA68);
                    func_00f28448(0, 0, 0, ids);
                    func_00f26810(v, 0, id, 0);
                    func_00f27ff0(v - 640, 0, ids);
                    func_001bfac8();
                }
            }
            D_00F878E4 = 1;
            break;
        case 1:
            prev = state;
            state = func_00f27a00(ids);
            if (state != 0) {
                func_00f258c8(1);
            }
            D_00F878E4 = 0;
            if (state == 3) {
                for (i = 0; i < n; i++) {
                    v = 640 * i / n;
                    func_00f29500(0, 0x3600, D_00FBAA68);
                    func_00f28448(0, 0, 0, ids);
                    func_00f26e80(-v, 0, ids, 1, 0.0f);
                    func_00f27ff0(640 - v, 0, ids);
                    func_001bfac8();
                }
            } else if (state == 1) {
                for (i = 0; i < n; i++) {
                    v = 640 * i / n;
                    D_00FBAA74 = -0x30;
                    D_00FBAA70 = v - 0x210;
                    func_00f29500(0, 0x3600, D_00FBAA68);
                    func_00f28448(0, 0, 0, ids);
                    func_00f26e80(v, 0, ids, 1, 0.0f);
                    func_00f26810(v - 640, 0, id, 0);
                    func_001bfac8();
                }
            }
            D_00F878E4 = 1;
            break;
        case 2:
            prev = state;
            state = func_00f28158(ids);
            if (state != 0) {
                func_00f258c8(1);
            }
            D_00F878E4 = 0;
            if (state == 1) {
                for (i = 0; i < n; i++) {
                    v = 640 * i / n;
                    D_00FBAA74 = -0x30;
                    D_00FBAA70 = 0x2F0 - v;
                    func_00f29500(0, 0x3600, D_00FBAA68);
                    func_00f28448(0, 0, 0, ids);
                    func_00f27ff0(-v, 0, ids);
                    func_00f26810(640 - v, 0, id, 0);
                    func_001bfac8();
                }
            } else if (state == 2) {
                for (i = 0; i < n; i++) {
                    v = 640 * i / n;
                    func_00f29500(0, 0x3600, D_00FBAA68);
                    func_00f28448(0, 0, 0, ids);
                    func_00f27ff0(v, 0, ids);
                    func_00f26e80(v - 640, 0, ids, 1, 0.0f);
                    func_001bfac8();
                }
            }
            D_00F878E4 = 1;
            break;
        case 3:
            D_00F878E4 = 0;
            n = 10;
            for (i = 0; i < n; i++) {
                v = (0 - 640) * i / n;
                func_00f25728(prev, id, ids, v, 0, 0, 0, 96 * i / n);
                func_00f28a68(v + 640, 0, 128);
                func_001bfac8();
            }
            func_00f28e58();
            func_00f258c8(0);
            for (i = 0; i < n; i++) {
                v = 640 * i / n;
                func_00f25728(prev, id, ids, v - 640, 0, 0, 0, (0 - 96) * i / n + 96);
                func_00f28a68(v, 0, 128);
                func_001bfac8();
            }
            state = prev;
            D_00F878E4 = 1;
            break;
        case 4:
            n = 14;
            D_00F878E4 = 0;
            for (i = 0; i < n; i++) {
                if (i == 3) {
                    func_0011d140(11, 0x1111);
                }
                if (i < 6) {
                    func_00f21ef0((f32)i * 100.0f / 6.0f + 0.0f);
                } else {
                    func_00f21ef0(100.0f);
                }
                func_00f25728(prev, id, ids, 0, 0, 0, 0, 96 * i / n);
                func_00f28ed8(0, 0, 128, (f32)i * 100.0f / (f32)n + 0.0f);
                func_001bfac8();
            }
            func_00f29418();
            n = 10;
            func_0011d1a8(11, 0x1111, 10);
            func_00f258c8(0);
            for (i = 0; i < n; i++) {
                v = (0 - 96) * i / n + 96;
                k = (0 - 128) * i / n + 128;
                func_00f21ef0((f32)i * -100.0f / (f32)n + 100.0f);
                func_00f25728(prev, id, ids, 0, 0, 0, 0, v);
                func_00f28ed8(0, 0, k, 100.0f);
                func_001bfac8();
            }
            func_00f21ef0(0.0f);
            state = prev;
            D_00F878E4 = 1;
            break;
        }
    } while (state != 0);
    n = D_00F878E0;
    for (i = 0; i < n; i++) {
        v = 640 * i / n;
        func_00f25728(prev, id, ids, -v, 0, v, 0, 0);
        func_001bfac8();
    }
    func_00f22d70();
}
