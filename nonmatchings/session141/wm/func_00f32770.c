/* Round 38 (wwm2): wm.x func_00f32770 near miss: score 8 -> 2 (6 -> 2 words, 856 = 856). fx and fy copied into locals inside the if: `x = fx; c[cnt].id = o->id; y = fy; c[cnt].x = x; c[cnt].o = o; c[cnt].y = y;` (1374 orders of the copies and stores enumerated, /tmp/claude-0/s141/r38/e327c.py). Left: the original stores x (swc1 $f0,4) before loading fy (lwc1 $f1); no tried order does both. Earlier header below. */
/* 6 words left (round 12): only the delay-slot fill after if (func_00f323b8(o,&fx,&fy)) differs (target beqz to i++ with the fx load in the slot). Tried all 24 store orders of the c[cnt] block (this is the best), continue/else/!=0 forms, c[cnt++].o, one shared counter for sort and assign; a 10 min permuter only found outputs that move cnt++ before the o store (changes behaviour, rejected). Round 13: a 300 s hill2 pass (store order, if-form and loop-condition slots) found nothing. */
typedef struct { s32 active; s32 id; s32 cnt; s32 pad; f32 pos[4]; } S32770;
typedef struct { u8 pad[2]; u16 h2; u8 pad2[2]; u16 h6; } K32770;
typedef struct { s32 f0; s32 id; u8 pad[20]; K32770 *k; u8 pad2[48]; f32 v80[4]; u8 pad3[112]; f32 pos[4]; } O32770;
typedef struct { s32 id; f32 x; f32 y; O32770 *o; } C32770;
extern s32 D_00F850F4, D_00FBB82C;
extern S32770 D_00FBB5D0[];
O32770 *func_00f3b4e0(s32);
O32770 *func_00f3b460(s32);
s32 func_00f3b480(void);
s32 func_00f32378(f32 *);
s32 func_00f32718(s32);
s32 func_00f323b8(O32770 *, f32 *, f32 *);

void func_00f32770(void) {
    C32770 c[16];
    s32 order[16];
    f32 fx;
    f32 fy;
    O32770 *o;
    K32770 *k;
    S32770 *sl;
    s32 n;
    s32 cnt;
    s32 i;
    s32 j;
    s32 m;
    s32 used;
    s32 num;

    if (D_00F850F4 == 0) return;
    n = D_00FBB82C;
    for (i = 0; i < n; i++) {
        sl = &D_00FBB5D0[i];
        if (sl->active == 0) continue;
        sl->cnt++;
        o = func_00f3b4e0(sl->id);
        if (o != NULL && func_00f32378(o->v80) && (sl->active != 1 || (u32)sl->cnt <= 90)) {
            sl->pos[0] = o->pos[0];
            sl->pos[1] = o->pos[1];
            sl->pos[2] = o->pos[2];
            sl->pos[3] = o->pos[3];
        } else {
            sl->active = 0;
            sl->cnt = 0;
        }
    }
    cnt = 0;
    for (i = 0; i < func_00f3b480() && cnt < 16; i++) {
        o = func_00f3b460(i);
        if (o == NULL) continue;
        k = o->k;
        if (k == NULL) continue;
        if (k->h2 != 0) {
            if (k->h2 != 1) continue;
            if (!(u16)(k->h6 & 1)) continue;
        }
        if (func_00f32718(o->id)) continue;
        if (func_00f323b8(o, &fx, &fy)) {
            f32 x, y;
            x = fx;
            c[cnt].id = o->id;
            y = fy;
            c[cnt].x = x;
            c[cnt].o = o;
            c[cnt].y = y;
            cnt++;
        }
    }
    num = 0;
    for (i = 0; i < cnt; i++) {
        for (j = 0; j < num; j++) {
            if (c[i].x < c[order[j]].x) break;
        }
        for (m = num - 1; m >= j; m--) {
            order[m + 1] = order[m];
        }
        order[j] = i;
        num++;
    }
    num = 0;
    for (i = 0; i < n && num < cnt; i++) {
        if (D_00FBB5D0[i].active == 0) {
            D_00FBB5D0[i].active = 1;
            D_00FBB5D0[i].cnt = 0;
            D_00FBB5D0[i].id = c[order[num]].id;
            D_00FBB5D0[i].pos[0] = c[order[num]].o->pos[0];
            D_00FBB5D0[i].pos[1] = c[order[num]].o->pos[1];
            D_00FBB5D0[i].pos[2] = c[order[num]].o->pos[2];
            D_00FBB5D0[i].pos[3] = c[order[num]].o->pos[3];
            num++;
        }
    }
}
