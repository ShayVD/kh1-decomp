#include "common.h"
typedef struct { u8 pad[0x3070]; u64 f3070; } G389;
extern G389 D_00389C90;
extern s32 D_0062A220;
void func_001763f0(s32);
void func_001ddbf8(void)
{
    func_001763f0(D_0062A220);
    D_00389C90.f3070 &= ~(1ULL << 44);
}
