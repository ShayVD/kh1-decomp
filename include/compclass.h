/* CompClass: a component "class" record, recovered in session 4.
 *
 * About 224 of these sit back to back in data (0x00304B5C-0x00425BB4,
 * 0x28 bytes each). Every word is either 0 or the address of a function,
 * except +0xC, which points to an array of s32 byte offsets. The functions
 * in the slots are called as fn(base, class) and find their data at
 * `base + class->offsets[i]` (often a sub-struct at +0xA0 from there), so
 * one function can serve any object that embeds the component. What the
 * slots mean (init / update / draw ...) is not known yet. */
#ifndef KH1_COMPCLASS_H
#define KH1_COMPCLASS_H

#include "common.h"

typedef struct CompClass {
    void *fn00;
    void *fn04;
    void *fn08;
    s32 *offsets; /* +0x0C: byte offsets of the component's data in the object */
    void *fn10;
    void *fn14;
    void *fn18;
    void *fn1C;
    void *fn20;
    void *fn24;
} CompClass; /* 0x28 bytes */

/* layout check */
typedef char CompClass_check_size[(sizeof(struct CompClass) == 0x28) ? 1 : -1];

#endif /* KH1_COMPCLASS_H */
