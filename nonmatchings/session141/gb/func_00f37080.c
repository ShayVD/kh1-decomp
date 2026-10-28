/* 4 words / score 6: the two lui for D_00F809D0 / D_00F813D0 take v0/v1 the other way round. Tried loop forms, init order, pointer locals, permuter. */
typedef struct {
    s32 obj;
    u8 pad4[36];
} GbSlot;
typedef struct {
    u8 pad0[8];
    u8 id;
} GbItem;
GbItem *func_001bb658(s32);
void func_001be820(void *, s32);
s32 func_00f23860(s32);
s32 func_00f3dff0(s32);
extern GbSlot D_00F809D0[];
extern GbSlot *D_00F813D0[192];

void func_00f37080(void) {
    s32 i;
    GbSlot *s;
    GbItem *it;
    s32 r;
    for (i = 191; i >= 0; i--)
        D_00F813D0[i] = NULL;
    s = D_00F809D0;
    for (i = 0x80; i < 0xA0; i++) {
        it = func_001bb658(i);
        if (it != NULL && it->id != 0xFF) {
            r = func_00f3dff0(func_00f23860(it->id));
            if (r != 0) {
                func_001be820(s, sizeof(GbSlot));
                s->obj = r;
                D_00F813D0[it->id] = s;
                s++;
            }
        }
    }
}
