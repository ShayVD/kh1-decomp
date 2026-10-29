/* score 43 (21 words; 836 vs 840 bytes). Modal picture viewer loop. Fixes so far: load w/h/bpp/addr into locals before func_00f471a0 (order addr, h, bpp, w), `nb++; nb &= 1;` (not (nb+1)&1, which combine turns into xori), D_0108F264 uses entry field +0, global init order brute-forced. Left: registers only - the hoisted %hi(0x109) pseudo for D_0108F26C lands in v1 instead of a0, which ripples to the 2 constant (a2) and &D_002C5AD0 (v1), a bnezl vs bnez at the loop top, and the func_00f69a20 address load order. */
typedef struct { s32 x0, x4; u32 x8; } Pad;
extern Pad D_002C5AD0;
typedef struct { s32 x0; s16 w; s16 h; s32 bpp; s32 off; } Ent;
typedef struct { s32 idx; s32 sel; s32 base; s32 buf[2]; s32 x14; s32 id; } Obj;
extern s32 D_00FB4F40[];
extern Ent *D_00FB4F30[];
extern void *D_0108F248[];
extern s32 D_0108F25C;
extern s32 D_0108F264;
extern s32 D_0108F268;
extern s32 D_0108F26C;
extern s32 D_0108F270;
extern s32 D_0108F274;
extern s32 D_0108F278;
void func_0011d768(s32);
void func_001c01b0(s32, void (*)(void));
void func_00f69a20(void);
void func_001bfac8(void);
void *func_00f471a0(void);
void func_00f471b0(void *);
void func_00f699d8(s32);
void func_00f66f78(s32, void *);
void func_00f693e0(s32, s32, s32, s32, s32, s32, s32, u8 *, s32, u64, s32, u64);

void func_00f69aa8(Obj *o)
{
    s32 fade = 0;
    s32 state = 0;
    s32 nb = 0;
    u8 col[4];
    s32 cnt;
    Ent *ent;
    Ent *e;
    s32 addr;
    void *pk;
    s32 v;
    s32 w, h, bpp;

    col[0] = 0;
    ent = D_00FB4F30[o->idx];
    cnt = D_00FB4F40[o->idx];
    col[1] = 0;
    col[2] = 0;
    col[3] = 0;
    D_0108F278 = -1;
    D_0108F274 = -1;
    D_0108F270 = 0;
    D_0108F26C = 0;
    do {
        if (D_0108F26C == 0 && state != 2) {
            if (D_002C5AD0.x8 & 0x20) {
                o->sel++;
                if (o->sel >= cnt) o->sel = cnt - 1;
            }
            if (D_002C5AD0.x8 & 0x80) {
                v = o->sel - 1;
                if (v < 0) v = 0;
                o->sel = v;
            }
            if (o->sel != D_0108F278) {
                if (D_0108F278 == -1) func_0011d768(2);
                else func_0011d768(1);
                D_0108F278 = o->sel;
                D_0108F264 = o->base + ent[o->sel].x0;
                D_0108F268 = o->buf[nb];
                nb++;
                nb &= 1;
                D_0108F26C = 1;
                func_001c01b0(-1, func_00f69a20);
            }
        }
        if (D_0108F270 != 0) {
            if (state == 0) {
                fade += 12;
                if (fade >= 128) {
                    fade = 128;
                    state = 1;
                }
            }
            if (state == 2) {
                fade -= 12;
                if (fade <= 0) {
                    state = 3;
                    fade = 0;
                }
            }
            col[3] = fade;
            col[2] = fade;
            col[1] = fade;
            col[0] = fade;
            if (D_0108F26C == 2) D_0108F26C = 0;
            D_0108F25C = o->x14;
            e = (Ent *)(D_0108F274 * 16 + (s32)ent);
            addr = o->base + e->off;
            h = e->h;
            bpp = e->bpp;
            w = e->w;
            pk = func_00f471a0();
            D_0108F248[0] = pk;
            func_00f693e0(D_0108F270, addr, 0, 0, w, h, bpp, col, 0, 68, 0, 0x5001D);
            func_00f699d8(0);
            func_00f471b0(D_0108F248[0]);
            func_00f66f78(o->id, pk);
        }
        func_001bfac8();
        if ((D_002C5AD0.x8 & 1) && state == 1) {
            func_0011d768(3);
            state = 2;
        }
    } while (state != 3);
}
