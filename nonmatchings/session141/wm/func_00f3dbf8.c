/* 50 words left; tried variants b-c */
typedef struct { u16 h0; u16 h2; u16 h4; u16 flags; u8 pad8[0x18]; u16 id; u16 pad22; u16 cnt; } R3dbf8;
typedef struct { u8 b0; u8 pad1; u16 h2; u8 pad4[12]; u8 b10; } Q3dbf8;
typedef struct { u8 pad[0xC8]; f32 dist; } T3dbf8;
typedef struct { u8 pad[0x540]; s32 x540; } G3dbf8;
extern G3dbf8 *D_00F864C0;
extern s32 D_00F87020;
extern s32 D_00F87048;
R3dbf8 *func_00f3f260(s32, s32);
Q3dbf8 *func_00f62c78(s32, s32);
s32 func_00f348e0(s32);
T3dbf8 *func_00f64c38(s32, s32);
void func_00f68770(s32, s32, u8 *, s32, s32);
void func_00f3de48(u8 *, Q3dbf8 *);
void func_00f2c108(s32, s32);

s32 func_00f3dbf8(s32 arg0, u8 *arg1, s32 arg2) {
    G3dbf8 **pg = &D_00F864C0;
    R3dbf8 *r;
    Q3dbf8 *q;
    s32 n;
    s32 k;
    f32 d;
    r = func_00f3f260(arg0, (*pg)->x540);
    if (r == NULL) {
        return 0;
    }
    if ((u16)(r->flags & 1)) {
        return 0;
    }
    q = func_00f62c78(r->id, (*pg)->x540);
    if (q != NULL && q->h2 < 2) {
        if (r->cnt == 0) {
            return 1;
        }
        r->flags |= 8;
        n = func_00f348e0(arg2);
        if (n >= r->cnt) {
            r->cnt = 0;
            r->flags |= 1;
            d = func_00f64c38(q->b0, D_00F87020)->dist;
            if (d < 1400.0f) {
                k = 78;
            } else if (d < 4000.0f) {
                k = 77;
            } else {
                k = 76;
            }
            func_00f68770(k, 1, arg1, 0, D_00F87048);
            func_00f3de48(arg1 + 48, q);
            func_00f2c108(q->b10, q->h2);
            return 3;
        }
        r->cnt -= n;
        return 2;
    }
    return 0;
}
