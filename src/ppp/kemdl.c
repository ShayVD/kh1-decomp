/* The ppp model texture classes' default-flag functions (docs/modules.md
 * "Session 50"): the Cons of pppKeMdlTfd / TfdUv / Tfd2 / TfdUv2 / Dtt, the
 * Resets of Dtt and Bmp, and the empty pppKeMdlBmp draw and Con and
 * pppKeAcmSolidFn18 (an empty slot of another class, next in the ELF).  The
 * draws are in kemdl.nostrict.c, the "3" versions in kemdltfd3*.c.  Read
 * from the code, not proved by a boot. */

/* pppKeMdlTfdCon (from auto/text_00180000_3.c). */
#include "m2c.h"
#include "ppp.h"
#include "data/pieces/D_00364130.h"
void pppKeMdlTfdCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[2];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
}

/* pppKeMdlTfdUvCon (from hand/ppp.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
void pppKeMdlTfdUvCon(void *obj, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 2);

    w[0] = w[1] = w[2] = w[4] = w[5] = w[6] = w[7] = w[8] = w[9] = 0.0f;
}
#undef PPP_WORK

/* pppKeMdlTfd2Con (from auto/text_00180000_3.c). */
void pppKeMdlTfd2Con(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[2];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
}

/* pppKeMdlTfdUv2Con (from hand/ppp.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
void pppKeMdlTfdUv2Con(void *obj, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 2);

    w[0] = w[1] = w[2] = w[4] = w[5] = w[6] = w[7] = w[8] = w[9] = 0.0f;
}

/* pppKeMdlDttCon (from hand/ppp.c). */
typedef struct {
    u64 a;
    s32 b;
} PppU64S32;
void pppKeMdlDttCon(void *obj, PppEntry *e) {
    PppU64S32 *w = PPP_WORK(PppU64S32, obj, e, 0);

    w->a = 0;
    w->b = 0;
}

/* pppKeMdlDttReset (from auto/text_00180000_19.c). */
void pppKeMdlDttReset(s32 arg0, void *arg1) {
  s8 *new_var2;
  void *temp_a0;
  s32 **new_var;
  new_var = (s32 **) (((s8 *) arg1) + 0xC);
  temp_a0 = arg0 + (*(*new_var));
  *((s32 *) ((new_var2 = (s8 *) (temp_a0 + 0xA0)) + 8)) = (*((s64 *) (((s8 *) temp_a0) + 0xA0)) = 0);
}

/* pppKeMdlBmpDraw (from auto/text_00180000.c). */
#include "data/pieces/D_00370130.h"
void pppKeMdlBmpDraw(void) {

}

/* pppKeMdlBmpCon (from auto/text_00180000.c). */
void pppKeMdlBmpCon(void) {

}

/* pppKeMdlBmpReset (from auto/text_00180000.c). */
void pppKeMdlBmpReset(void) {

}

/* pppKeAcmSolidFn18 (from auto/text_00180000.c). */
void pppKeAcmSolidFn18(void) {

}

