/* The coroutines' stacks (include/platform/costack.h): from the pool the platform gives, else malloc'd.
 * Not part of the PS2 build. */
#include "common.h"
#include "platform/costack.h"

void *malloc(__SIZE_TYPE__);

static u8 *pool_lo, *pool_hi; /* the pool's unused part */
static u8 *pool_base;         /* the whole pool: pool_base to pool_hi */

void kh1_costack_pool(void *base, u32 size) {
    pool_base = pool_lo = (u8 *)(((__SIZE_TYPE__)base + 15) & ~(__SIZE_TYPE__)15);
    pool_hi = (u8 *)base + size;
}

int kh1_costack_owns(unsigned long a, u32 n) {
    return pool_base && a >= (unsigned long)pool_base && a + n <= (unsigned long)pool_hi;
}

void *kh1_costack_alloc(u32 size) {
    size = (size + 15) & ~15u;
    if (pool_lo && (u32)(pool_hi - pool_lo) >= size) {
        void *p = pool_lo;
        pool_lo += size;
        return p;
    }
    return malloc(size);
}
