/* wm.x func_00f36498: first draft (session 142, for the native overlay), written from the asm.
 * Not a match: only checked by reading it against the asm.
 *
 * The task func_00f36e78 starts for an object list entry of kind 59-61 (func_001c0310(11, this,
 * slot)): an effect (func_00f68770(t->t, 1000, ...)) that flies from the object's matrix along its
 * z row, D_002BBDEC-scaled speed (t->c * 100, or 250), for t->b / D_002BBDEC frames (b = 80 when
 * 0). Unless t->a is 4 it homes on a target: every t->d frames (10 when 0) the target is the
 * matrix func_00f2c818 gives (its row 3), and the matrix turns towards it about z x (target - pos)
 * by at most 5 degrees a frame. Each frame it hands the matrix to the effect (func_00f689f0),
 * queues the slot (func_00f36308) and waits (func_001bfac8). Ends when the frames run out, the
 * object or entry goes, flag bit 0 is set, or func_00f41448 says so; unless func_00f41448 ended it,
 * a second effect (36 / 38, or 48 / 49 with flag bit 0) starts at t's +160. */
#include "ovl.h"

typedef struct {
    u8 pad[4];
    u8 kind;
} Ent;

typedef struct {
    void *obj;    /* 0x00: its matrix */
    Ent *e;       /* 0x04 */
    s32 t;        /* 0x08 */
    s32 z;        /* 0x0c: bit 0 ends the flight */
    s32 c;        /* 0x10: speed / 100 */
    s32 b;        /* 0x14: distance */
    s32 d;        /* 0x18: re-aim period */
    s32 a;        /* 0x1c: 4 = no homing */
    u8 pad20[0x60 - 0x20];
    OvlMtx m;     /* 0x60 */
    u8 pad_a0[0xA0 - 0xA0];
    u8 at[0x40];  /* 0xa0 */
} Task;

extern f32 D_002BBDEC;
extern s32 D_00F87048;

Task *func_00f363c0(s32);
void func_00f363e0(OvlMtx, void *, Ent *);
s32 func_00f68770(s32, s32, void *, s32, s32);
void func_00f689f0(s32, OvlMtx);
void func_00f68a40(s32);
void func_00f36308(s32);
void func_001bfac8(void);
s32 func_00f41448(void);
void func_00f2c818(f32 (*)[4]);
void func_001bf290(f32 *);
void func_001bf698(f32 *, f32 *, f32);
void func_001bf3e8(f32 (*)[4], f32 *);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void sceVu0Normalize(f32 *, f32 *);
void sceVu0OuterProduct(f32 *, f32 *, f32 *);
f32 sceVu0InnerProduct(f32 *, f32 *);
f32 acosf(f32);

void func_00f36498(s32 slot) {
    OvlMtx rot;   /* sp+0 */
    OvlMtx m;     /* sp+64 */
    OvlVec save;  /* sp+128 */
    OvlVec dir;   /* sp+144 */
    OvlVec axis;  /* sp+160 */
    OvlVec up;    /* sp+176 */
    f32 q[4] __attribute__((aligned(16))); /* sp+192 */
    OvlVec aim;   /* sp+208 */
    Task *t;
    s32 homing, h, i, period, next;
    f32 speed, steps, c, ang;

    t = func_00f363c0(slot);
    homing = t->a != 4;
    func_00f363e0(t->m, t->obj, t->e);
    h = func_00f68770(t->t, 1000, t->m, 0, D_00F87048);
    if (h < 0) return;
    speed = 250.0f;
    if (t->c != 0) speed = (f32)t->c * 100.0f;
    speed *= D_002BBDEC;
    if (t->b == 0) t->b = 80;
    period = t->d ? t->d : 10;
    steps = (f32)t->b / D_002BBDEC;

    for (i = 0; i < (s32)steps; i++) {
        if (t->obj == 0) break;
        if (t->e == 0) goto end;
        if (t->z & 1) break;

        sceVu0CopyMatrix(m, t->m);
        m[0][0] = -m[0][0];
        m[0][1] = -m[0][1];
        m[0][2] = -m[0][2];
        m[2][0] = -m[2][0];
        m[2][1] = -m[2][1];
        m[2][2] = -m[2][2];
        if (homing) {
            if (i % period == 0) {
                func_00f2c818(rot);
                aim[0] = rot[3][0];
                aim[1] = rot[3][1];
                aim[2] = rot[3][2];
                aim[3] = 1.0f;
            }
            dir[0] = aim[0] - m[3][0];
            dir[1] = aim[1] - m[3][1];
            dir[2] = aim[2] - m[3][2];
            dir[3] = 1.0f;
            sceVu0Normalize(dir, dir);
            up[0] = m[2][0];
            up[1] = m[2][1];
            up[2] = m[2][2];
            up[3] = 1.0f;
            sceVu0Normalize(up, up);
            sceVu0OuterProduct(axis, up, dir);
            sceVu0Normalize(axis, axis);
            c = sceVu0InnerProduct(up, dir) /
                __builtin_sqrtf((dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]) *
                                (up[0] * up[0] + up[1] * up[1] + up[2] * up[2]));
            if ((c > 0.9989999532699585f && c < 1.000999927520752f) || (c < -0.9989999532699585f && c > -1.000999927520752f))
                goto move;
            if (c > -0.0009999999310821295f && c < 0.0009999999310821295f)
                ang = 1.570796251296997f;
            else
                ang = acosf(c);
            while (ang > 3.141592502593994f) ang -= 6.283185005187988f;
            while (ang < -3.141592502593994f) ang += 6.283185005187988f;
            if (ang < 0.0f) {
                if (ang < -0.0872664526104927f) ang = -0.0872664526104927f;
            } else {
                if (ang > 0.0872664526104927f) ang = 0.0872664526104927f;
            }
            func_001bf290(q);
            func_001bf698(q, axis, ang);
            func_001bf3e8(rot, q);
            save[0] = m[3][0];
            save[1] = m[3][1];
            save[2] = m[3][2];
            m[3][0] = 0.0f;
            m[3][1] = 0.0f;
            m[3][2] = 0.0f;
            sceVu0MulMatrix(m, rot, m);
            m[3][0] = save[0];
            m[3][1] = save[1];
            m[3][2] = save[2];
        }
    move:
        m[3][0] += m[2][0] * speed;
        m[3][1] += m[2][1] * speed;
        m[3][2] += m[2][2] * speed;
        m[2][0] = -m[2][0];
        m[2][1] = -m[2][1];
        m[2][2] = -m[2][2];
        m[0][0] = -m[0][0];
        m[0][1] = -m[0][1];
        m[0][2] = -m[0][2];
        sceVu0CopyMatrix(t->m, m);
        func_00f689f0(h, t->m);
        func_00f36308(slot);
        func_001bfac8();
        if (func_00f41448()) {
            t->e = 0;
            func_00f68a40(h);
            t->obj = 0;
            return;
        }
    }

    if (t->e != 0 && t->obj != 0) {
        /* kind - 1 is 58, 59 or 60 (func_00f36e78 starts no other) */
        if (t->z & 1)
            next = t->e->kind - 1 == 60 ? 49 : 48;
        else
            next = t->e->kind - 1 == 60 ? 38 : 36;
        func_00f68770(next, 1, t->at, 0, D_00F87048);
    }
end:
    t->e = 0;
    func_00f68a40(h);
    t->obj = 0;
}
