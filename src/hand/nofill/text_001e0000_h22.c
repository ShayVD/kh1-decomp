#include "common.h"

u32 func_001ee118(void);

u32 func_001ee388(void) {
    return (u32)((f32)(func_001ee118() % 60U) * 1.6666667f);
}
