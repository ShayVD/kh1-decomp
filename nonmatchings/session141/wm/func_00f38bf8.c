/* 2 words left: li s2,1 should fill the beqz s0 delay slot; tried inline-helper variants; 10-min permuter gave no output */
typedef struct { s32 v[5]; } T38bf8;
typedef struct { u8 pad[0x18]; s32 k; s32 x; s32 y; } S38bf8;
extern T38bf8 D_00FB7010;
extern s32 D_00F8C2F0;
void func_00f20b08(s32, s32);
s32 func_00f20ac8(void);
f32 func_00f20ad8(void);
void func_001bfac8(void);
void func_00f387a8(s32, S38bf8 *);
void func_00f38630(s32, S38bf8 *);
void func_00f38a38(f32, f32);

void func_00f38bf8(s32 arg0, S38bf8 *arg1) {
    s32 k = arg1->k;
    T38bf8 t = D_00FB7010;
    s32 done;
    D_00F8C2F0 = 1;
    func_00f20b08(k + 1, 1);
    while (func_00f20ac8() != k + 1) {
        func_001bfac8();
    }
    func_00f20b08(0, 0);
    done = 0;
    while (func_00f20ac8() == k + 1) {
        if (!done && !((s32)func_00f20ad8() < t.v[k] * 2)) {
            switch (k) {
            case 0:
                func_00f387a8(arg0, arg1);
                break;
            case 1:
                func_00f38630(arg0, arg1);
                break;
            case 2:
                func_00f38a38(arg1->x * 100.0f, arg1->y * 100.0f);
                break;
            }
            done = 1;
        }
        func_001bfac8();
    }
    D_00F8C2F0 = 0;
}
