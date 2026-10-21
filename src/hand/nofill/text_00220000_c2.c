#include "common.h"
#include "data/bss_0064.h"
typedef struct { s32 x0, x4, x8, xc, x10; u32 x14; f32 x18, x1c; } St;
extern s32 D_00643430[];
extern s32 D_0064342C;
#include "data/pieces/D_003E8E08.h"
void func_0021b820(void);
void func_0021c9a0(void *, s32, s32);
void func_0021b860(void *, s32, s32, s32, s32, s32);
f32 func_00236970(u32 *);
void func_0021bf68(void *, St *);
void func_0021cb00(void *, s32, s32, s32, s32);
s32 func_0021b800(s32);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);

/* func_001fb428 is left undeclared on purpose (implicit declaration gives the original register choice). */
void func_00220c28(void *a) {
    St st;
    u32 seed;
    s32 i, j, k, x, y;
    s32 *p;
    k = 0;
    y = 98;
    func_0021b820();
    func_0021c9a0(a, 16, 72);
    st.x10 = 28;
    st.x14 = 0x64465A96;
    seed = 12345678;
    st.x4 = 113;
    st.x8 = 0;
    st.xc = 0;
    for (i = 0; i < 8; i++) {
        st.x0 = 47;
        func_0021b860(a, 32, y, 0, 0, i != 7 ? 29 : 27);
        x = 32;
        for (j = 0; j < 7; j++) {
            if (k >= 50) goto done;
            func_001fb428(a, 2, 2, 0, x + 15, y + 9, k + 1, 12, 0x80808080);
            x += 28;
            st.x18 = func_00236970(&seed);
            st.x1c = func_00236970(&seed);
            if (D_00643430[k]) {
                st.x18 = st.x18 * 0.1 + 0.9;
                st.x1c = st.x1c * 1.047197491f - 0.5235987455f;
                func_0021bf68(a, &st);
            }
            k++;
            st.x0 += 28;
        }
        st.x4 += 28;
        y += 28;
    }
done:
    st.x4 = 113;
    y = 98;
    for (i = 0; i < 7; i++) {
        st.x0 = 295;
        func_0021b860(a, 280, y, 0, 0, 29);
        x = 280;
        for (j = 0; j < 7; j++) {
            func_001fb428(a, 2, 2, 0, x + 15, y + 9, k + 1, 12, 0x80808080);
            x += 28;
            if (D_00643430[k]) {
                st.x18 = func_00236970(&seed) * 0.1 + 0.9;
                st.x1c = func_00236970(&seed) * 1.047197491f - 0.5235987455f;
                func_0021bf68(a, &st);
            }
            k++;
            st.x0 += 28;
        }
        st.x4 += 28;
        y += 28;
    }
    func_0021cb00(a, 280, 318, 2, 30);
    (*(s32 *)&D_003E8E08) = D_0064342C;
    func_001f94f0(a, 0, 303, 326, func_0021b800(18), 15, 0x80461E00);
}
