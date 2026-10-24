/* The player's model change (docs/modules.md "Session 47"), 0x0024f008-0x0024f2e0
 * except plmodel.nostrict_nogcse.c's func_0024f098, after the hand asm of
 * src/asm/text_0024e0a4.s.  func_0024f098 swaps the controlled character
 * for the object with a request's id: it saves the old one's place and
 * angle in D_0066AA90, removes it, finds the new object (D_0066AA84) and
 * loads it (func_001560f8) with func_0024f070 as the callback, which hooks
 * func_0024f008 to put it in the saved place and call the caller's
 * callback D_0066AA80.  func_0024f210 loads the current character's model
 * id from D_0046A6B0 (other ids for characters 1 and 2 when D_002C5C4C or
 * D_002C5C50 is set) with func_0024f1d0 as the callback.  Read from the
 * code; what the requests are in the game is not known and not proved by
 * a boot. */
#include "common.h"
#include "data/bss_0066.h"
#include "data/bss_0066_typed.h"
#include "data/data_002C.h"
#include "data/data_0046.h"
#include "data/pieces/D_00304BE8_s.h"

/* The object func_00132040 walks (its id at +0x4C). */
typedef struct { s32 x0; u8 pad[0x48]; u16 id; u8 pad4e[6]; s8 kind; s8 x55; } Obj;

extern Obj *D_0066AA84; /* src/data/bss_0066.c: s32 *D_0066AA84 */
extern void (*D_0066AA80)(void);

void func_00123a88(s32, V4f *);
s32 func_00124218(s32);
void func_00131d68(s32, s32);
void func_00149c80(u16, void (*)(void));
s32 func_001560f8(s32, void *);
void func_0024ef88(void);

void func_0024f008(void) {
    func_00124218(D_0066AA84->x0);
    func_00123a88(D_0066AA84->x0, &D_0066AA90);
    func_0024ef88();
    if (D_0066AA80 != NULL) {
        D_0066AA80();
    }
}

void func_0024f070(void) {
    func_00149c80(D_0066AA84->id, func_0024f008);
}

s32 func_0024f1d0(s32 a) {
    s32 (*cb)(void);

    func_00131d68(a, D_0066AAA0);
    cb = (s32 (*)(void))D_0066AA80;
    if (cb != NULL) {
        cb = (s32 (*)(void))cb();
    }
    return (s32)cb;
}

s32 func_0024f210(s32 a, void (*cb)(void)) {
    u8 c;
    s32 id;
    D_0066AAA0 = a;
    D_0066AA80 = cb;
    c = D_00304BE8->x48e[3];
    id = D_0046A6B0[c];
    if (D_002C5C4C) {
        if (c == 1) id = 0xc000a;
        else if (c == 2) id = 0xc000b;
    } else if (D_002C5C50) {
        if (c == 1) id = 0xc0008;
        else if (c == 2) id = 0xc0009;
    }
    func_001560f8(id, func_0024f1d0);
    return id;
}
