/* The helpers after vm_find (docs/modules.md "Session 35"), 0x001e9d00-0x001ea438.
 *
 * Vector helpers of the VM library: an offset rotated by angles and added
 * to a point (func_001e9dc8, func_001e9f18, through libvu0: platform
 * calls), the angle wrap to [-pi, pi] (func_001e9fe8, D_003D9FE0 354), and
 * the message text copy / append that keeps control codes whole
 * (func_001ea128 / func_001ea268: codes 5-7 take two bytes, 10 one or
 * three, 11 and 13 three, 9-31 one).  The angle and distance helpers that
 * need nofill are in vm_util.nofill.c. */
#include "common.h"

typedef struct { f32 x, y, z; } VmVec3;

void func_00267620(void *m);                    /* sceVu0UnitMatrix */
void func_00267768(void *d, void *m, f32 a);    /* rotate about x */
void func_00267810(void *d, void *m, f32 a);    /* rotate about y */
void func_002676c0(void *d, void *m, f32 a);    /* rotate about z */
void func_002672f8(void *d, void *m, void *v);  /* d = m v */
void func_00267518(void *d, void *a, void *b);  /* d = a + b */

void func_001e9dc8(f32 *pos, f32 *rot, f32 *v);
void func_001e9f18(f32 *out, f32 *base, f32 *rot, f32 d);
void func_001e9fe8(VmVec3 *out, VmVec3 *in);
void func_001ea128(char *dst, char *src);
void func_001ea268(char *dst, char *src);
void func_001ea430(void);

/* func_001e9d00 is in src/vm/vm_util.nofill.c. */

/* pos += v rotated by rot (x, then y, then z). */
void func_001e9dc8(f32 *pos, f32 *rot, f32 *v) {
    f32 m[4][4];
    func_00267620(m);
    func_00267768(m, m, rot[0]);
    func_00267810(m, m, rot[1]);
    func_002676c0(m, m, rot[2]);
    func_002672f8(v, m, v);
    func_00267518(pos, pos, v);
}

/* func_001e9e58, func_001e9ec0 are in src/vm/vm_util.nofill.c. */

/* out = base - (0, 0, d) rotated by rot (x, then y). */
void func_001e9f18(f32 *out, f32 *base, f32 *rot, f32 d) {
    f32 m[4][4];
    f32 x, y, z;

    out[3] = 1.0f;
    out[2] = d;
    out[0] = 0.0f;
    out[1] = 0.0f;
    func_00267620(m);
    func_00267768(m, m, rot[0]);
    func_00267810(m, m, rot[1]);
    func_002672f8(out, m, out);
    x = -out[0];
    y = -out[1];
    z = -out[2];
    out[0] = x;
    out[1] = y;
    out[2] = z;
    out[0] = x + base[0];
    out[1] = y + base[1];
    out[2] = z + base[2];
}

void func_001e9fe8(VmVec3 *out, VmVec3 *in) {
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
    while (1) {
        if (out->x > 3.1415928f) out->x -= 6.2831855f;
        else if (out->x < -3.1415928f) out->x += 6.2831855f;
        else break;
    }
    while (1) {
        if (out->y > 3.1415928f) out->y -= 6.2831855f;
        else if (out->y < -3.1415928f) out->y += 6.2831855f;
        else break;
    }
    while (1) {
        if (out->z > 3.1415928f) out->z -= 6.2831855f;
        else if (out->z < -3.1415928f) out->z += 6.2831855f;
        else break;
    }
}

void func_001ea128(char *dst, char *src) {
    s32 n = 0, i = 0;
    while (src[i] != 0) {
        dst[n] = src[i];
        if ((u8)(src[i] - 5) < 3) {
            i++; n++;
            dst[n] = src[i];
            i++; n++;
            dst[n] = src[i];
        } else if (src[i] == 11) {
            i++; n++;
            dst[n] = src[i];
            i++; n++;
            dst[n] = src[i];
            i++; n++;
            dst[n] = src[i];
        } else if (src[i] == 10) {
            i++; n++;
            dst[n] = src[i];
            if (dst[n] == 0) {
                i++; n++;
                dst[n] = src[i];
                i++; n++;
                dst[n] = src[i];
            }
        } else if (src[i] == 13) {
            i++; n++;
            dst[n] = src[i];
            i++; n++;
            dst[n] = src[i];
            i++; n++;
            dst[n] = src[i];
        }
        if ((u8)(src[i] - 9) < 23) {
            i++; n++;
            dst[n] = src[i];
        }
        i++; n++;
    }
    dst[n] = 0;
}

void func_001ea268(char *dst, char *src) {
    s32 len = 0; s32 i; s64 c;
    while (1) {
        c = dst[len];
        if (c == 0) {
            i = 0;
            while (src[i] != 0) {
                dst[len + i] = src[i];
                if ((u8)(src[i] - 5) < 3) {
                    i++;
                    dst[len + i] = src[i];
                    i++;
                    dst[len + i] = src[i];
                } else if (src[i] == 11) {
                    i++;
                    dst[len + i] = src[i];
                    i++;
                    dst[len + i] = src[i];
                    i++;
                    dst[len + i] = src[i];
                } else if (src[i] == 10) {
                    i++;
                    dst[len + i] = src[i];
                    if (dst[len] == 0) {
                        i++;
                        dst[len + i] = src[i];
                        i++;
                        dst[len + i] = src[i];
                    }
                } else if (src[i] == 13) {
                    i++;
                    dst[len + i] = src[i];
                    i++;
                    dst[len + i] = src[i];
                    i++;
                    dst[len + i] = src[i];
                }
                if ((u8)(src[i] - 9) < 23) {
                    i++;
                    dst[len + i] = src[i];
                }
                i++;
            }
            dst[i + len] = 0;
        return; }

        if ((u8)(dst[len] - 5) < 3) {
            len += 2;
        } else if (c == 11) {
            len += 3;
        } else if (c == 10) {
            len++;
            if (dst[len] == 0) len += 2;
        } else if (c == 13) {
            len += 3;
        } else {
            len += (u8)(dst[len] - 9) < 23;
        }
        len++;
    }
}

void func_001ea430(void) {
}
