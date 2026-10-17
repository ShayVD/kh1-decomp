/* 0 words off: exact bytes, but layout.tsv gives 36 bytes (ends 0x10057c); real function is 40 bytes incl. b-delay-slot nop at 0x10057c (next func at 0x100580). Mode: hand. Fix layout size to 40. */
#include "common.h"
void func_00262c78(void);
void func_00109288(void);
void func_00109770(void);
void func_00100558(void) {
    func_00262c78();
    func_00109288();
    for (;;) func_00109770();
}
