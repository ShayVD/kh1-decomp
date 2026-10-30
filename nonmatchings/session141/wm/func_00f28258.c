/* Round 36 (wgb): wm.x func_00f28258 near miss: 90 -> 90 words, score 87 -> 85 (aligned diff 51 -> 48). Statement order from tools/ovl/hill3.py (score-ranked, strict dependency rules). Tried: hill3 sweep of every gb RANKING row and wm RANKING rows 1-100 (85-90 s, seed 1; strict rules; the order kept passes hill3.py --check against the previous draft), and port.py from the twin (not better). Earlier header below. */
/* 90 words (484 vs 496). Control flow is right (wait for state 3, crossfade between D_00FBB558[cur]/[nxt] with 150-frame hold and 32-step fade, quit on D_00F878E8, restart on D_00FBB568); left: register allocation (target keeps D_00FBB568 hi in s8, overwrites cur with cur*8) and the duplicated xori. Tried top/bottom-tested loops and i-reset placement. */
typedef struct { s32 on; s32 val; } F28258;
void func_00f28230(void);
void func_001bfac8(void);
extern s32 D_00FBAA90;
extern s32 D_00FBB568;
extern s32 D_00F8756C;
extern s32 D_00F878E8;
extern F28258 D_00FBB558[2];

void func_00f28258(void) {
    s32 step;
    s32 cur = 0;
    s32 nxt;
    s32 i;
    s32 t;
    s32 v;

    func_00f28230();
    D_00FBB568 = 0;
    step = D_00F8756C + 16;
    while (D_00FBAA90 != 3) {
        func_001bfac8();
    }
    while (1) {
        if (D_00FBB568) {
            cur = 0;
            D_00FBB568 = 0;
        }
        nxt = cur ^ 1;
        D_00FBB558[cur].on = 1;
        D_00FBB558[nxt].on = 0;
        D_00FBB558[cur].val = 0;
        if (D_00F878E8) {
            return;
        }
        i = 0;
        if (!D_00FBB568) {
            do {
                i++;
                func_001bfac8();
                if (i >= 150) {
                    break;
                }
                if (D_00F878E8) {
                    return;
                }
            } while (!D_00FBB568);
        }
        if (D_00F878E8) {
            return;
        }
        if (!D_00FBB568) {
            i = 0;
            t = 0;
            do {
                v = t / 32;
                D_00FBB558[cur].on = 1;
                D_00FBB558[nxt].on = 1;
                D_00FBB558[cur].val = v;
                D_00FBB558[nxt].val = v - step;
                i++;
                func_001bfac8();
                t += step;
                if (i >= 32) {
                    break;
                }
                if (D_00F878E8) {
                    return;
                }
            } while (!D_00FBB568);
        }
        cur = nxt;
    }
}
