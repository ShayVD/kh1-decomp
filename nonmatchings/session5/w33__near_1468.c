typedef struct { u8 pad[0x88]; f32 f88; } Cfg88;
extern Cfg88 *D_00308CDC;
typedef struct { u8 b0; u8 b1; } S1C8;
typedef struct { u32 flags; u8 pad4[0x38]; s32 w3c; s32 w40; u8 pad44[0xC8 - 0x44]; S1C8 *pc8; } St6C;
extern St6C D_00304C70;
typedef struct { u8 pad[0x4C]; u16 h4c; } S130b;
typedef struct { u8 pad[0x6C]; St6C *p6c; u8 pad70[0x18]; u32 w88; u8 pad8c[0x130 - 0x8C]; S130b *p130; } O1468;
s32 func_00141448(s32, s32, s32);
s32 func_0013c968(s32, s32);

s32 func_00141468(O1468 *o, s32 x) {
    St6C *s;
    s32 v;
    if ((s = o->p6c) == 0) return 0;
    if (s == &D_00304C70) {
        return 0;
    } else {
        v = func_00141448(s->w3c, x, s->w40);
        if ((o->w88 & 0x20) && !func_0013c968(9, o->p130->h4c)) {
            v = s->w3c + (s32)((v - s->w3c) * D_00308CDC->f88);
        }
        s->w3c = v;
        s->flags &= ~4;
        if (s->pc8) s->pc8->b1 = v;
    }
    return v;
}
