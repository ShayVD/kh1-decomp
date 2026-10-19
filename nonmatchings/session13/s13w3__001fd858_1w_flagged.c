/* 001fd858 1w, hand/nostrict, CONTEXT_ONLY fe1b8/fe408/fe4e0 included, FLAGGED (dead float test). Same source as nonmatchings/session13/s13w3__001fd858_1w_flagged.c. New finding (s13w4): the 0x654 bnezl needs v0 in opposite_needed when reorg fills insn 1635 from its target thread; gdb-forcing opposite_needed|=v0 at fill_slots_from_thread gives a full match. But mark_target_live_regs always loses v0 on the fallthrough: method 1 (block scan + find_dead_or_set_registers) kills it at the fe408 call reached via b L170 -> b done (also with the bnez REG_DEAD note removed), and method 2 (live at L170) kills it at the same call. With the final control flow, no path from the fallthrough reads v0 before that call, so no source change on this path can make reorg annul; the original's reorg state must have differed (e.g. a transient v0 reader on the fallthrough path). */
#include "common.h"
typedef struct {
    u8 pad0[0xcc];
    s16 cc;
    s16 ce;
    u16 d0;
    u16 d2;
    s16 d4;
    s16 d6;
} Scr;
typedef struct {
    u8 pad0[0xce];
    s16 ce;
    s16 d0;
    s16 d2;
    u8 pad_d4[8];
    u8 dc[1];
} Fade;
typedef struct {
    u8 pad0[0x98];
    s32 x98;
    u8 pad9c[0xbc - 0x9c];
    s16 xbc;
    u8 padbe[0xcc - 0xbe];
    s16 cc;
    s16 ce;
    s16 d0;
    s16 d2;
    s16 d4;
    s16 d6;
} Menu;
typedef struct { u8 pad[4]; u32 x4; u32 x8; u32 xc; u32 x10; } Pad;
extern Pad *D_00425BC8;
extern u32 D_00640DE4, D_00640DE8, D_00640DEC;
extern f32 D_002BBDFC;
void func_0011d768(s32);

CONTEXT_ONLY s32 func_001fe1b8(Scr *o) {
    s32 r = 0;
    s32 t, lim;
    u16 v = o->d2;
    s32 sv = v << 16;
    if (o->d4 < 0) {
        t = (s16)(v & 0xfff0);
        if (v & 0xf) {
            o->d2 = (s32)((sv >> 16) - D_002BBDFC * 4.0f);
            if ((s16)o->d2 <= 0) {
                o->d2 = 0;
            } else if (t < (s16)o->d2) {
                goto next;
            } else {
                o->d2 = t;
            }
        }
        o->d4 = 0;
    } else if (o->d4 > 0) {
        t = (s16)(v & ~0xf) + 16;
        lim = (o->ce - 1) << 4;
        if (v & 0xf) {
            o->d2 = (s32)((sv >> 16) + D_002BBDFC * 4.0f);
            if ((s16)o->d2 >= lim) {
                o->d2 = lim;
            } else if ((s16)o->d2 < t) {
                goto next;
            } else {
                o->d2 = t;
            }
            r = 1;
        }
        o->d4 = 0;
    }
next:
    if (o->d6 < 0) {
        v = o->d0;
        t = (s16)(v & 0xfff0);
        if (v & 0xf) {
            o->d0 = (s32)((s16)v - D_002BBDFC * 4.0f);
            if ((s16)o->d0 <= 0) {
                o->d0 = 0;
                o->d6 = 0;
                goto end;
            }
            if (t < (s16)o->d0) goto end;
            o->d0 = t;
        }
        o->d6 = 0;
    } else if (o->d6 > 0) {
        v = o->d0;
        t = (s16)(v & 0xfff0) + 16;
        lim = o->ce; lim = (o->cc - lim) << 4;
        if (v & 0xf) {
            o->d0 = (s32)((s16)v + D_002BBDFC * 4.0f);
            if ((s16)o->d0 >= lim) {
                o->d0 = lim;
            } else if ((s16)o->d0 < t) {
                goto end;
            } else {
                o->d0 = t;
            }
            r = 1;
        }
        o->d6 = 0;
    }
end:
    return r;
}

CONTEXT_ONLY void func_001fe408(Fade *o) {
    s32 i;
    s32 n1 = o->ce + 1;
    s32 cnt = (o->d0 & 0xf) ? n1 : o->ce;
    s32 k = (o->d0 >> 4) % n1;
    s32 sel = o->d2 >> 4;
    for (i = 0; i < cnt; i++) {
        u8 *p = &o->dc[k];
        if (i == sel) {
            *p = 0x80;
        } else {
            s32 d = (s32)(D_002BBDFC * 4.0f);
            if (d + 64 >= *p) *p = 64;
            else *p -= d;
        }
        k = (k + 1) % n1;
    }
}

CONTEXT_ONLY void func_001fe4e0(Fade *o) {
    s32 i;
    s32 n1 = o->ce + 1;
    s32 cnt = (o->d0 & 0xf) ? n1 : o->ce;
    s32 k = (o->d0 >> 4) % n1;
    for (i = 0; i < cnt; i++) {
        o->dc[k] = 64;
        k = (k + 1) % n1;
    }
}

void func_001fd858(Menu *o) {
    s32 r;
    s32 f;
    s32 k6;
    s32 y0, y2;
    f32 sp;
    s32 max, lim, t;
    Pad *pad;
    u32 m;
    u32 m2;

    if (o->cc < 2 || o->ce == 0) {
        o->d2 = 0;
        return;
    }
    if (o->cc < o->ce) {
        o->ce = o->cc;
    }
    if (((s16)o->d2 >> 4) >= o->ce) {
        o->d2 = (o->ce - 1) << 4;
    }
    y2 = (s16)o->d2;
    y0 = (s16)o->d0;
    r = 0;
    if (o->xbc != 0) { r = func_001fe1b8((Scr *)o); goto done; }
    pad = D_00425BC8;
    if (pad->x4 & 0x300) {
        if (o->cc == o->ce) goto norm;
        if (o->ce >= o->cc) { r = func_001fe1b8((Scr *)o); goto done; }
        m = pad->x4 & D_00640DEC;
        if (m & D_00640DE4) {
            if (y0 > 0) {
                sp = D_002BBDFC * 8.0f;
                o->d0 = (s32)(y0 - sp);
                if ((s16)o->d0 < 0) {
                    o->d0 = 0;
                    r = 1;
                    o->d6 = 0;
                } else {
                    o->d6 = (s32)(-(sp));
                    if (((s16)o->d0 >> 4) != (y0 >> 4)) r = 1;
                }
            } else if (pad->x8 & D_00640DE4) {
                if (o->cc == 2 && y2 == 0) goto down;
                o->d0 = (o->cc - o->ce) << 4;
                r = 1;
                o->d2 = (o->ce - 1) << 4;
            }
        } else if (m & D_00640DE8) {
            max = (o->cc - o->ce) << 4;
            if (y0 < max) {
                sp = D_002BBDFC * 8.0f;
                o->d0 = (s32)(y0 + sp);
                if (max < (s16)o->d0) {
                    o->d0 = max;
                    r = 1;
                    o->d6 = 0;
                } else {
                    o->d6 = (s32)(sp);
                    if (((s16)o->d0 >> 4) != (y0 >> 4)) r = 1;
                }
            } else if (pad->x8 & D_00640DE8) {
                if (o->cc == 2 && y2 == 16) goto up;
                o->d0 = 0;
                r = 1;
                o->d2 = 0;
            }
        } else {
            r = func_001fe1b8((Scr *)o); goto done;
        }
        if ((f32)r < 0.0f) t = 0; else f = 0;
        goto fade;
    } else if (pad->x10 & 0x400) {
        if (o->ce < o->cc) {
            max = o->ce << 4;
            if (y0 > 0) {
                o->d0 = o->d0 - max;
                r = 1;
                if ((s16)o->d0 < 0) {
                    o->d0 = 0;
                    o->d6 = 0;
                }
            } else if (pad->x8 & 0x400) {
                o->d0 = (o->cc - o->ce) << 4;
                r = 1;
                o->d2 = (o->ce - 1) << 4;
            }
        }
    } else if (pad->x10 & 0x800) {
        if (o->ce < o->cc) {
            max = (o->cc - o->ce) << 4;
            if (y0 < max) {
                o->d0 = o->d0 + (o->ce << 4);
                r = 1;
                if (max < (s16)o->d0) {
                    o->d0 = max;
                    o->d6 = 0;
                }
            } else if (pad->x8 & 0x800) {
                o->d0 = 0;
                r = 1;
                o->d2 = 0;
            }
        }
    } else {
        goto norm;
    }
fade:
    func_001fe4e0((Fade *)o);
    goto done;
norm:
    m2 = D_00425BC8->x10 & D_00640DEC;
    if (m2 & D_00640DE4) {
up:
        if ((s16)o->d2 > 0) {
            sp = D_002BBDFC * 4.0f;
            o->d2 = (s32)((s16)o->d2 - sp);
            if ((s16)o->d2 < 0) {
                o->d2 = 0;
                r = 1;
                o->d4 = 0;
            } else {
                r = ((s16)o->d2 >> 4) != (y2 >> 4);
                o->d4 = (s32)(-(sp));
            }
            if (o->d6 < 0) {
                f = o->d0 & 0xf;
                t = (s16)(o->d0 & ~0xf);
                if (f) {
                    o->d0 = (s32)((s16)o->d0 - D_002BBDFC * 4.0f);
                    if ((s16)o->d0 <= 0) {
                        o->d0 = 0;
                        o->d6 = 0;
                        goto done;
                    } else if (t < (s16)o->d0) {
                        goto done;
                    } else {
                        o->d0 = t;
                    }
                }
                o->d6 = 0;
            } else {
                if (o->d6 > 0) {
                f = o->d0 & 0xf;
                t = (s16)(o->d0 & ~0xf) + 16;
                max = (o->cc - o->ce) << 4;
                if (f) {
                    o->d0 = (s32)((s16)o->d0 + D_002BBDFC * 4.0f);
                    if (!((s16)o->d0 < max)) {
                        o->d0 = max;
                    } else if ((s16)o->d0 < t) {
                        goto done;
                    } else {
                        o->d0 = t;
                        o->d6 = 0;
                        goto done;
                    }
                    o->d6 = 0;
                }
                }
            }
        } else if ((s16)o->d0 > 0) {
            sp = D_002BBDFC * 4.0f;
            o->d0 = (s32)((s16)o->d0 - sp);
            if ((s16)o->d0 < 0) {
                o->d0 = 0;
                r = 1;
                o->d6 = 0;
            } else {
                o->d6 = (s32)(-(sp));
                if (((s16)o->d0 >> 4) != (y0 >> 4)) r = 1;
            }
        } else if (D_00425BC8->x8 & D_00640DE4) {
            if (o->cc == 2) goto down;
            o->d0 = (o->cc - o->ce) << 4;
            r = 1;
            o->d2 = (o->ce - 1) << 4;
        }
    } else if (m2 & D_00640DE8) {
down:
        lim = (o->ce - 1) << 4;
        if ((s16)o->d2 < lim) {
            sp = D_002BBDFC * 4.0f;
            o->d2 = (s32)((s16)o->d2 + sp);
            if (lim < (s16)o->d2) {
                o->d2 = lim;
                r = 1;
                o->d4 = 0;
            } else {
                r = ((s16)o->d2 >> 4) != (y2 >> 4);
                o->d4 = (s32)(sp);
            }
            if (o->d6 < 0) {
                f = o->d0 & 0xf;
                t = (s16)(o->d0 & ~0xf);
                if (f) {
                    o->d0 = (s32)((s16)o->d0 - D_002BBDFC * 4.0f);
                    if ((s16)o->d0 <= 0) {
                        o->d0 = 0;
                        o->d6 = 0;
                        goto done;
                    } else if (t < (s16)o->d0) {
                        goto done;
                    } else {
                        o->d0 = t;
                    }
                }
                o->d6 = 0;
            } else {
                if (o->d6 > 0) {
                f = o->d0 & 0xf;
                t = (s16)(o->d0 & ~0xf) + 16;
                max = (o->cc - o->ce) << 4;
                if (f) {
                    o->d0 = (s32)((s16)o->d0 + D_002BBDFC * 4.0f);
                    if (!((s16)o->d0 < max)) {
                        o->d0 = max;
                    } else if ((s16)o->d0 < t) {
                        goto done;
                    } else {
                        o->d0 = t;
                        o->d6 = 0;
                        goto done;
                    }
                    o->d6 = 0;
                }
                }
            }
        } else {
            max = (o->cc - o->ce) << 4;
            if ((s16)o->d0 < max) {
                sp = D_002BBDFC * 4.0f;
                o->d0 = (s32)((s16)o->d0 + sp);
                if (max < (s16)o->d0) {
                    o->d0 = max;
                    r = 1;
                    o->d6 = 0;
                } else {
                    o->d6 = (s32)(sp);
                    if (((s16)o->d0 >> 4) != (y0 >> 4)) r = 1;
                }
            } else if (D_00425BC8->x8 & D_00640DE8) {
                if (o->cc == 2) goto up;
                o->d0 = 0;
                r = 1;
                o->d2 = 0;
            }
        }
    } else {
        r = func_001fe1b8((Scr *)o);
    }
done:
    func_001fe408((Fade *)o);
    if (r) {
        func_0011d768(1);
        o->x98 = 0;
    }
}
