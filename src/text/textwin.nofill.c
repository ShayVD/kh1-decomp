/* The functions of src/text/textwin.c that need nofill: func_001f4058 sets
 * a window's +0x68 to entry i of D_003E8E30 (-1: none); func_001f5fe0 runs
 * the opening / closing animation picked by +0x80 (+0x9c is the time, +0x90
 * the alpha, +0x50 ... +0x5c and +0xb0 / +0xb4 positions, +0x74 / +0x78 the
 * scale). */
#include "common.h"
#include "text/textwin.h"
#include "data/pieces/D_003E8E30.h"

void func_001f4058(TextWin *p, s32 i) {
    p->x68 = (i == -1) ? 0 : &D_003E8E30[i];
}

f32 sinf(f32);
f32 cosf(f32);
f32 func_001edcd8(f32);
u32 func_001eddc0(u32, u32, f32);

#define PI_2 1.57079637050628662109375f
#define PI_1 3.1415927410125732421875f
#define PI2 6.283185482025146484375f
#define PI3_2 4.7123889923095703125f
#define PI8 25.1327419281005859375f
#define LERP(a, b, x) ((a) + ((b) - (a)) * (x))

/* rodata: jump table at 0x490c70.  s11w70, natural (no flagged shapes). */
void func_001f5fe0(TextWin *o) {
    f32 t;
    f32 p;
    f32 s;

    t = o->x9c;
    switch ((u32)o->x80) {
    case 0:
        o->state++;
        break;
    case 2:
        if (t >= 16.0f) {
            o->x90 = 0x80;
            o->state++;
        }
        break;
    case 3:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->xb4 = (f32)(o->x50 - 0x400) + sinf(p * PI_2) * 1024.0f;
        if (t >= 10.0f) {
            o->x90 = 0x80;
            o->xb4 = o->x50;
            o->state++;
        }
        break;
    case 4:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->xb4 = (f32)(o->x50 + 0x400) - sinf(p * PI_2) * 1024.0f;
        if (t >= 10.0f) {
            o->x90 = 0x80;
            o->xb4 = o->x50;
            o->state++;
        }
        break;
    case 5:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->xb0 = (f32)(o->x50 - 0x400) + sinf(p * PI_2) * 1024.0f;
        if (t >= 10.0f) {
            o->x90 = 0x80;
            o->xb0 = o->x50;
            o->state++;
        }
        break;
    case 6:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->xb0 = (f32)(o->x50 + 0x400) - sinf(p * PI_2) * 1024.0f;
        if (t >= 10.0f) {
            o->x90 = 0x80;
            o->xb0 = o->x50;
            o->state++;
        }
        break;
    case 7:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->xb0 = (f32)(o->x50 - 0x120) + p * 288.0f;
        o->xb4 = (f32)(o->x54 - 0x90) + p * 144.0f;
        if (t >= 10.0f) {
            o->x90 = 0x80;
            o->xb0 = o->x50;
            o->xb4 = o->x54;
            o->state++;
        }
        break;
    case 8:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->xb0 = (f32)(o->x50 + 0x120) - p * 288.0f;
        o->xb4 = (f32)(o->x54 - 0x90) + p * 144.0f;
        if (t >= 10.0f) {
            o->x90 = 0x80;
            o->xb0 = o->x50;
            o->xb4 = o->x54;
            o->state++;
        }
        break;
    case 9:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->xb0 = (f32)(o->x50 - 0x120) + p * 288.0f;
        o->xb4 = (f32)(o->x54 + 0x90) - p * 144.0f;
        if (t >= 10.0f) {
            o->x90 = 0x80;
            o->xb0 = o->x50;
            o->xb4 = o->x54;
            o->state++;
        }
        break;
    case 10:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->xb0 = (f32)(o->x50 + 0x120) - p * 288.0f;
        o->xb4 = (f32)(o->x54 + 0x90) - p * 144.0f;
        if (t >= 10.0f) {
            o->x90 = 0x80;
            o->xb0 = o->x50;
            o->xb4 = o->x54;
            o->state++;
        }
        break;
    case 11:
        p = t / 16.0f;
        o->x90 = p * 128.0f;
        o->x74 = o->x78 = LERP(0.9f, 1.0f, p);
        if (t >= 16.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 12:
        p = t / 16.0f;
        o->x90 = p * 128.0f;
        o->x74 = o->x78 = LERP(1.1f, 1.0f, p);
        if (t >= 16.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 13:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->x74 = o->x78 = LERP(0.0f, 1.0f, sinf(p * PI_2));
        if (t >= 10.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 14:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->x74 = o->x78 = LERP(1.5f, 1.0f, sinf(p * PI_2));
        if (t >= 10.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 15:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->x74 = sinf(p * PI_2);
        if (t >= 10.0f) {
            o->u48.q &= ~1;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 16:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->x78 = sinf(p * PI_2);
        if (t >= 10.0f) {
            o->u48.q &= ~1;
            o->x90 = 0x80;
            o->x78 = 1.0f;
            o->state++;
        }
        break;
    case 21:
        p = t / 10.0f;
        o->x74 = p;
        o->x90 = p * 128.0f;
        o->x78 = LERP(2.0f, 1.0f, p);
        if (t >= 10.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 22:
        p = t / 10.0f;
        o->x78 = p;
        o->x90 = p * 128.0f;
        o->x74 = LERP(2.0f, 1.0f, p);
        if (t >= 10.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 17:
        p = t / 8.0f;
        o->x90 = p * 128.0f;
        o->x74 = LERP(0.75f, 1.0f, p);
        if (t >= 8.0f) {
            o->u48.q &= ~1;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 18:
        p = t / 8.0f;
        o->x90 = p * 128.0f;
        o->x78 = LERP(0.75f, 1.0f, p);
        if (t >= 8.0f) {
            o->u48.q &= ~1;
            o->x90 = 0x80;
            o->x78 = 1.0f;
            o->state++;
        }
        break;
    case 19:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->x74 = LERP(1.7f, 1.0f, p);
        if (t >= 10.0f) {
            o->u48.q &= ~1;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 20:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        o->x78 = LERP(1.7f, 1.0f, p);
        if (t >= 10.0f) {
            o->u48.q &= ~1;
            o->x90 = 0x80;
            o->x78 = 1.0f;
            o->state++;
        }
        break;
    case 23:
        p = t / 12.0f;
        o->x90 = p * 128.0f;
        o->x74 = LERP(0.0f, 1.0f, sinf((p * PI_2) + PI3_2) + 1.0f);
        o->x78 = LERP(0.0f, 1.0f, sinf((p * PI_2)));
        if (t >= 12.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 24:
        p = t / 12.0f;
        o->x90 = p * 128.0f;
        o->x74 = LERP(0.0f, 1.0f, sinf((p * PI_2)));
        o->x78 = LERP(0.0f, 1.0f, sinf((p * PI_2) + PI3_2) + 1.0f);
        if (t >= 12.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 25:
        p = t / 16.0f;
        o->x90 = p * 128.0f;
        o->xb0 = (f32)o->x50 + (800.0f - p * 800.0f) * sinf((p * PI2));
        o->xb4 = (f32)o->x54 + (800.0f - p * 800.0f) * -cosf((p * PI2));
        if (t >= 16.0f) {
            o->x90 = 0x80;
            o->xb0 = o->x50;
            o->xb4 = o->x54;
            o->state++;
        }
        break;
    case 26:
        p = t / 16.0f;
        o->x90 = p * 128.0f;
        o->xb0 = (f32)o->x50 + (1280.0f - p * 1280.0f) * sinf((p * PI_2));
        o->xb4 = (f32)o->x54 + (1280.0f - p * 1280.0f) * -cosf((p * PI_2));
        if (t >= 16.0f) {
            o->x90 = 0x80;
            o->xb0 = o->x50;
            o->xb4 = o->x54;
            o->state++;
        }
        break;
    case 27:
        p = t / 16.0f;
        o->x90 = p * 128.0f;
        o->x74 = o->x78 = LERP(0.95f, 1.0f, sinf(p * PI_2));
        o->xb0 = (f32)o->x50 + (16.0f - p * 16.0f) * sinf(func_001edcd8((p * PI8)));
        o->xb4 = (f32)o->x54 + (16.0f - p * 16.0f) * -cosf(func_001edcd8((p * PI8)));
        if (t >= 16.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->xb0 = o->x50;
            o->xb4 = o->x54;
            o->state++;
        }
        break;
    case 28:
        if (t <= 12.0f) {
            p = t / 12.0f;
            o->x90 = p * 128.0f;
            o->x74 = o->x78 = LERP(0.0f, 1.2f, sinf(p * PI_2));
        } else {
            o->x90 = 0x80;
            p = (t - 12.0f) / 8.0f;
            o->x74 = o->x78 = LERP(1.2f, 1.0f, sinf(p * PI_2));
        }
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 29:
        p = t / 16.0f;
        o->x90 = p * 128.0f;
        o->x74 = cosf(func_001edcd8(p * PI2));
        if (t >= 16.0f) {
            o->u48.q &= ~1;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 30:
        p = t / 16.0f;
        o->x90 = p * 128.0f;
        o->x78 = cosf(func_001edcd8(p * PI2));
        if (t >= 16.0f) {
            o->u48.q &= ~1;
            o->x90 = 0x80;
            o->x78 = 1.0f;
            o->state++;
        }
        break;
    case 31:
        p = t / 20.0f;
        o->x90 = p * 128.0f;
        o->x74 = cosf(func_001edcd8(p * PI2)) * o->x78;
        o->x78 = LERP(0.2f, 1.0f, p);
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 32:
        p = t / 20.0f;
        o->x90 = p * 128.0f;
        o->x74 = LERP(0.2f, 1.0f, p);
        o->x78 = cosf(func_001edcd8(p * PI2)) * o->x74;
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 33:
        p = t / 20.0f;
        o->x90 = p * 128.0f;
        o->x74 = cosf(func_001edcd8(p * PI2)) * o->x78;
        o->x78 = LERP(1.5f, 1.0f, p);
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 34:
        p = t / 20.0f;
        o->x90 = p * 128.0f;
        o->x74 = LERP(1.5f, 1.0f, p);
        o->x78 = cosf(func_001edcd8(p * PI2)) * o->x74;
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 35:
        if (t <= 16.0f) {
            p = t / 16.0f;
            o->x90 = p * 128.0f;
            s = sinf(p * PI_2);
            o->x74 = LERP(0.05f, 1.0f, s);
            o->x78 = 0.05f;
        } else {
            o->x90 = 0x80;
            o->x74 = 1.0f;
            p = (t - 16.0f) / 10.0f;
            o->x78 = LERP(0.05f, 1.0f, sinf(p * PI_2));
        }
        if (t >= 26.0f) {
            o->u48.q &= ~1;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->state++;
        }
        break;
    case 36:
        if (t <= 4.0f) {
            p = t / 4.0f;
            o->x90 = p * 128.0f;
            o->xb4 = (f32)(o->x50 - 0x600) + p * 1536.0f;
        } else {
            o->x90 = 0x80;
            p = (t - 4.0f) / 4.0f;
            s = sinf(func_001edcd8(p * PI_1));
            o->x74 = LERP(1.0f, 1.0f, s);
            o->x78 = LERP(1.0f, 0.95f, s);
            o->xb4 = o->x50;
        }
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->xac = 0;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->xb4 = o->x50;
            o->state++;
        }
        break;
    case 37:
        if (t <= 4.0f) {
            p = t / 4.0f;
            o->x90 = p * 128.0f;
            o->xb4 = (f32)(o->x50 + 0x600) - p * 1536.0f;
        } else {
            o->x90 = 0x80;
            p = (t - 4.0f) / 4.0f;
            s = sinf(func_001edcd8(p * PI_1));
            o->x74 = LERP(1.0f, 1.0f, s);
            o->x78 = LERP(1.0f, 0.95f, s);
            o->xb4 = o->x50;
        }
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->xac = 0;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->xb4 = o->x50;
            o->state++;
        }
        break;
    case 38:
        if (t <= 4.0f) {
            p = t / 4.0f;
            o->x90 = p * 128.0f;
            o->xb0 = (f32)(o->x50 - 0x800) + p * 2048.0f;
        } else {
            o->x90 = 0x80;
            p = (t - 4.0f) / 4.0f;
            s = sinf(func_001edcd8(p * PI_1));
            o->x74 = LERP(1.0f, 0.95f, s);
            o->x78 = LERP(1.0f, 1.0f, s);
            o->xb0 = o->x50;
        }
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->xac = 0;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->xb0 = o->x50;
            o->state++;
        }
        break;
    case 39:
        if (t <= 4.0f) {
            p = t / 4.0f;
            o->x90 = p * 128.0f;
            o->xb0 = (f32)(o->x50 + 0x800) - p * 2048.0f;
        } else {
            o->x90 = 0x80;
            p = (t - 4.0f) / 4.0f;
            s = sinf(func_001edcd8(p * PI_1));
            o->x74 = LERP(1.0f, 0.95f, s);
            o->x78 = LERP(1.0f, 1.0f, s);
            o->xb0 = o->x50;
        }
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->xac = 0;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->xb0 = o->x50;
            o->state++;
        }
        break;
    case 40:
        if (t <= 8.0f) {
            p = t / 8.0f;
            o->x90 = p * 128.0f;
            o->xb4 = (f32)(o->x50 - 0x600) + p * 1536.0f;
        } else {
            o->x90 = 0x80;
            p = (t - 8.0f) / 6.0f;
            s = sinf(func_001edcd8(p * PI_1));
            o->x74 = LERP(1.0f, 1.0f, s);
            o->x78 = LERP(1.0f, 1.1f, s);
            o->xb4 = o->x50;
        }
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->xac = 0;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->xb4 = o->x50;
            o->state++;
        }
        break;
    case 41:
        if (t <= 8.0f) {
            p = t / 8.0f;
            o->x90 = p * 128.0f;
            o->xb4 = (f32)(o->x50 + 0x600) - p * 1536.0f;
        } else {
            o->x90 = 0x80;
            p = (t - 8.0f) / 6.0f;
            s = sinf(func_001edcd8(p * PI_1));
            o->x74 = LERP(1.0f, 1.0f, s);
            o->x78 = LERP(1.0f, 1.1f, s);
            o->xb4 = o->x50;
        }
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->xac = 0;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->xb4 = o->x50;
            o->state++;
        }
        break;
    case 42:
        if (t <= 8.0f) {
            p = t / 8.0f;
            o->x90 = p * 128.0f;
            o->xb0 = (f32)(o->x50 - 0x800) + p * 2048.0f;
        } else {
            o->x90 = 0x80;
            p = (t - 8.0f) / 6.0f;
            s = sinf(func_001edcd8(p * PI_1));
            o->x74 = LERP(1.0f, 1.1f, s);
            o->x78 = LERP(1.0f, 1.0f, s);
            o->xb0 = o->x50;
        }
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->xac = 0;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->xb0 = o->x50;
            o->state++;
        }
        break;
    case 43:
        if (t <= 8.0f) {
            p = t / 8.0f;
            o->x90 = p * 128.0f;
            o->xb0 = (f32)(o->x50 + 0x800) - p * 2048.0f;
        } else {
            o->x90 = 0x80;
            p = (t - 8.0f) / 6.0f;
            s = sinf(func_001edcd8(p * PI_1));
            o->x74 = LERP(1.0f, 1.1f, s);
            o->x78 = LERP(1.0f, 1.0f, s);
            o->xb0 = o->x50;
        }
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->xac = 0;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->xb0 = o->x50;
            o->state++;
        }
        break;
    case 44:
        p = t / 40.0f;
        o->x90 = p * 128.0f;
        if (t >= 40.0f) {
            o->x90 = 0x80;
            o->state++;
        }
        break;
    case 45:
        p = t / 40.0f;
        o->x90 = p * 128.0f;
        if (t >= 40.0f) {
            o->x90 = 0x80;
            o->state++;
        }
        break;
    case 46:
        p = t / 11.0f;
        o->x90 = p * 128.0f;
        if (t >= 11.0f) {
            o->x90 = 0x80;
            o->state++;
        }
        break;
    case 47:
        p = t / 6.0f;
        o->x90 = p * 128.0f;
        if (t >= 6.0f) {
            o->x90 = 0x80;
            o->state++;
        }
        break;
    case 48:
        if (t <= 8.0f) {
            p = t / 8.0f;
            o->xb0 = (f32)o->x50 + sinf(p * PI_2) * -3840.0f;
        } else if (t <= 18.0f) {
            p = (t - 8.0f) / 10.0f;
            o->xb0 = (f32)o->x54 + sinf(p * PI_2) * 672.0f;
        } else if (t <= 32.0f) {
            p = (t - 18.0f) / 14.0f;
            o->xb0 = (f32)o->x58 + sinf(p * PI_2) * -160.0f;
        }
        if (t <= 8.0f) {
            o->x24 = func_001eddc0(0, 0x80FF8080, t / 8.0f);
        } else if (t <= 32.0f) {
            o->x24 = func_001eddc0(0x80FF8080, 0x5A3287CD, (t - 8.0f) / 24.0f);
        }
        if (t >= 32.0f) {
            o->x24 = 0x5A3287CD;
            o->xb0 = o->x5c;
            o->state++;
        }
        break;
    case 49:
        if (t <= 8.0f) {
            p = t / 8.0f;
            o->xb0 = (f32)o->x50 + sinf(p * PI_2) * 1952.0f;
        } else if (t <= 20.0f) {
            p = (t - 8.0f) / 12.0f;
            o->xb0 = (f32)o->x54 + sinf(p * PI_2) * -672.0f;
        }
        if (t <= 8.0f) {
            o->x24 = func_001eddc0(0, 0x80FF8080, t / 8.0f);
        } else if (t <= 20.0f) {
            o->x24 = func_001eddc0(0x80FF8080, 0x5A3287CD, (t - 8.0f) / 12.0f);
        }
        if (t >= 20.0f) {
            o->x24 = 0x5A3287CD;
            o->xb0 = o->x58;
            o->state++;
        }
        break;
    case 50:
        p = t / 10.0f;
        o->x90 = p * 128.0f;
        if (t >= 10.0f) {
            o->x90 = 0x80;
            o->state++;
        }
        break;
    case 1:
    case 51:
        p = t / 16.0f;
        o->x90 = p * 128.0f;
        if (t >= 16.0f) {
            o->x90 = 0x80;
            o->state++;
        }
        break;
    case 54:
        if (t <= 8.0f) {
            p = t / 8.0f;
            o->x90 = p * 128.0f;
            o->xb0 = (f32)(o->x50 + 0x800) - p * 2048.0f;
        } else {
            o->x90 = 0x80;
            p = (t - 8.0f) / 6.0f;
            s = sinf(func_001edcd8(p * PI_1));
            o->x74 = LERP(1.0f, 1.02f, s);
            o->x78 = LERP(1.0f, 1.0f, s);
            o->xb0 = o->x50;
        }
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->xac = 0;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->xb0 = o->x50;
            o->state++;
        }
        break;
    case 52:
        if (t <= 8.0f) {
            p = t / 8.0f;
            o->x90 = p * 128.0f;
            o->xb4 = (f32)(o->x50 - 0x600) + p * 1536.0f;
        } else {
            o->x90 = 0x80;
            p = (t - 8.0f) / 6.0f;
            s = sinf(func_001edcd8(p * PI_1));
            o->x74 = LERP(1.0f, 1.0f, s);
            o->x78 = LERP(1.0f, 1.04f, s);
            o->xb4 = o->x50;
        }
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->xac = 0;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->xb4 = o->x50;
            o->state++;
        }
        break;
    case 53:
        if (t <= 8.0f) {
            p = t / 8.0f;
            o->x90 = p * 128.0f;
            o->xb4 = (f32)(o->x50 + 0x600) - p * 1536.0f;
        } else {
            o->x90 = 0x80;
            p = (t - 8.0f) / 6.0f;
            s = sinf(func_001edcd8(p * PI_1));
            o->x74 = LERP(1.0f, 1.0f, s);
            o->x78 = LERP(1.0f, 1.04f, s);
            o->xb4 = o->x50;
        }
        if (t >= 20.0f) {
            o->u48.q &= ~1;
            o->xac = 0;
            o->x78 = 1.0f;
            o->x90 = 0x80;
            o->x74 = 1.0f;
            o->xb4 = o->x50;
            o->state++;
        }
        break;
    }
}
