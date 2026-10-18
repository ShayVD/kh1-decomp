#include "common.h"

/* Menu window, 0xb0 bytes (full layout in src/hand/text_001e0000_h45.c). */
typedef struct { u8 b[0xb0]; } Win;
extern Win D_0062F840;
extern u8 D_0062F810[];
extern s32 D_003DC484;
extern u8 D_003DC3C0[];
extern u8 D_003DC390[];
void func_001e39f0(void);
void func_0010bd90(void *, void (*)());
void func_00231b98(void);
void func_0010e3f0(void *);
void func_0010ef70(void *, void *, void *);

/* func_00231b98 takes no arguments; D_0062F810 written out in both branches (gcse hoists it). */
void func_001e3a00(void) {
    func_0010bd90(&D_0062F840, func_001e39f0);
    if (D_003DC484 == 1) {
        func_00231b98();
        func_0010e3f0(D_0062F810);
        func_0010ef70(D_0062F810 - 0x80, D_003DC3C0, 0);
    } else {
        func_0010e3f0(D_0062F810);
        func_0010ef70(D_0062F810 - 0x80, D_003DC390, 0);
    }
}

typedef struct { u8 pad[0xa80]; u8 a80[16]; } SvA80;
typedef struct { char *a; char *b; } StrPair;
extern s32 D_003DD284;
extern s32 D_003DD288;
extern s32 D_003DD258;
extern char D_00630FC8[];
extern char D_003DD270[];
extern char D_003DCB90[];
extern char D_003DD230[];
extern char D_003DD278[];
extern char D_006305DA[][10];
extern StrPair D_006310C8[];
extern u8 D_006304E0[];
SvA80 *func_00232cc0(s32);
void func_001ea128(char *, char *);
void func_001ea268(char *, char *);


/* Plain globals (no pointer locals), `if (!D_003DD284) return 4;` first and the return 0 last. */
s32 func_001e6038(void) {
    SvA80 *sv = func_00232cc0(1);
    if (D_003DD284 == 0) return 4;
    if (--D_003DD288 < 0) {
        D_003DD284 = 0;
        func_001ea128(D_00630FC8, D_003DD270);
        if (sv->a80[D_003DD258] == 0) {
            func_001ea268(D_00630FC8, D_006305DA[D_003DD258]);
            func_001ea268(D_00630FC8, D_003DCB90);
        } else {
            func_001ea268(D_00630FC8, D_006305DA[D_003DD258]);
            func_001ea268(D_00630FC8, D_006310C8[sv->a80[D_003DD258] - 1].a);
            func_001ea268(D_00630FC8, D_003DD230);
            func_001ea268(D_00630FC8, D_003DD278);
            func_001ea268(D_00630FC8, D_006310C8[sv->a80[D_003DD258] - 1].b);
        }
        func_0010e3f0(D_006304E0);
        func_0010ef70(D_006304E0 - 0x80, D_00630FC8, 0);
        return 4;
    }
    return 0;
}
