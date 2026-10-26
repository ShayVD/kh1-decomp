/* xs_mushu.x func_00f20978: matched by hand. */
#include "ovl.h"

typedef struct { u32 used; s32 pad[15]; } Slot;
typedef struct { u8 pad[0x164]; s32 f164; } Pl;
void func_00f20550(Slot *);
void func_00f20778(Slot *);
void func_00f207e8(Slot *);
extern s32 D_00F21398;
extern Slot D_00F21400[];
extern s32 D_00F21680;
extern Pl *D_00F21388;
s32 func_00f20978(void) {
    s32 i;
    Slot *s;
    if (D_00F21398 == 101) {
        return 4;
    }
    s = D_00F21400;
    D_00F21680 = 0;
    for (i = 0; i < 10; i++, s++) {
        switch (s->used) {
        case 0:
            break;
        case 1:
            if (D_00F21388->f164 != 200) {
                if (D_00F21388->f164 == 201) {
                    func_00f20550(s);
                } else {
                    func_00f20778(s);
                }
            }
            D_00F21680++;
            break;
        case 2:
            func_00f207e8(s);
            D_00F21680++;
            break;
        }
    }
    return 0;
}
