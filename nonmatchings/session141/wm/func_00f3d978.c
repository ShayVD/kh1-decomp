/* 98 words (648 vs 640), but only 2 instructions off; the rest is an offset shift. Collision scan over func_00f3b460 objects (f218d8 parity filter, f3af58 for f4<0, f3caf0 sphere then f3cb90 box when s->f200 > 1500, then func_0024e640 walk with func_00f3d300). Left: reorg fills (d == NULL uses beqz+li v0,255 in the target, beqzl here) and the target loads o->f256 into f13 in the h8 branch delay slot. hill2 over the f4/d/h2 test forms (2x7 min), a rad temp, and a goto for the d test. */
typedef struct { u8 b0; u8 pad1; u16 h2; u8 pad4[4]; u16 h8; } D3d978;
typedef struct { u8 pad[176]; f32 pos[3]; f32 size[3]; f32 f200; } S3d978;
typedef struct {
    s32 f0;
    s32 f4;
    u8 pad8[20];
    D3d978 *d;
    f32 m[4][4];
    u8 pad96[160];
    f32 f256;
    S3d978 *s;
} O3d978;
typedef struct { f32 *p; f32 r; void *h; f32 (*m)[4]; s32 hit; } A3d978;
extern s32 D_00F87270;
O3d978 *func_00f3b460(s32);
s32 func_00f3b480(void);
s32 func_00f218d8(void);
s32 func_00f3af58(f32 *, f32);
s32 func_00f3caf0(f32 *, f32 *, f32, f32);
s32 func_00f3cb90(f32 *, f32 *, f32 *, f32 (*)[4], f32);
void sceVu0ApplyMatrix(f32 *, f32 (*)[4], f32 *);
void *func_00f650f0(s32, S3d978 *);
void func_0024e640(s32, s32, void (*)(A3d978 *), A3d978 *);
void func_00f3d300(A3d978 *);

O3d978 *func_00f3d978(f32 *p, s32 mode, f32 r1, f32 r2) {
    A3d978 a;
    f32 size[4];
    f32 pos[4];
    s32 i;
    O3d978 *o;
    D3d978 *d;
    S3d978 *s;
    f32 r;

    for (i = 0; i < func_00f3b480(); i++) {
        o = func_00f3b460(i);
        if (o == NULL) {
            continue;
        }
        if (mode == 1) {
            if ((func_00f218d8() & 1) && (o->f4 & 1)) {
                continue;
            }
            if (!(func_00f218d8() & 1) && !(o->f4 & 1)) {
                continue;
            }
        }
        if (o->f4 & 0x80000000) {
            if (func_00f3af58(p, r1)) return o;
            continue;
        }
        if (!((u32)o->f4 <= 4096)) continue;
        d = o->d;
        if (d == NULL) continue;
        if (d->b0 == 255) continue;
        if (mode == 1 && d->h2 != mode) continue;
        s = o->s;
        r = r1;
        if (d->h8 == 0) {
            r = r2;
        }
        if (r == 0.0f) {
            continue;
        }
        if (!func_00f3caf0(p, o->m[3], r, o->f256)) {
            continue;
        }
        if (s->f200 > 1500.0f) {
            pos[0] = s->pos[0];
            pos[1] = s->pos[1];
            pos[2] = s->pos[2];
            pos[3] = 1.0f;
            size[0] = s->size[0];
            size[1] = s->size[1];
            size[2] = s->size[2];
            size[3] = 1.0f;
            sceVu0ApplyMatrix(pos, o->m, pos);
            if (!func_00f3cb90(p, pos, size, o->m, r)) {
                continue;
            }
        }
        a.h = func_00f650f0(0, s);
        a.p = p;
        a.r = r;
        a.m = o->m;
        func_0024e640(D_00F87270, 4096, func_00f3d300, &a);
        if (a.hit) {
            return o;
        }
    }
    return NULL;
}
