/* The coroutines' stacks (include/platform/costack.h): from the pool the platform gives, else malloc'd.
 * Not part of the PS2 build. */
#include "common.h"
#include "platform/costack.h"

void *malloc(__SIZE_TYPE__);

static u8 *pool_lo, *pool_hi; /* the pool's unused part */
static u8 *pool_base;         /* the whole pool: pool_base to pool_hi */
static unsigned long own_lo, own_hi; /* the whole stack it came from (kh1_costack_stack) */

void kh1_costack_pool(void *base, u32 size) {
    pool_base = pool_lo = (u8 *)(((__SIZE_TYPE__)base + 15) & ~(__SIZE_TYPE__)15);
    pool_hi = (u8 *)base + size;
}

void kh1_costack_stack(void *base, u32 size) {
    own_lo = (unsigned long)base;
    own_hi = own_lo + size;
}

int kh1_costack_owns(unsigned long a, u32 n) {
    if (own_hi && a >= own_lo && a + n <= own_hi) return 1;
    return pool_base && a >= (unsigned long)pool_base && a + n <= (unsigned long)pool_hi;
}

int printf(const char *, ...);

void *kh1_costack_alloc(u32 size) {
    static int warned;
    size = (size + 15) & ~15u;
    if (pool_lo && (u32)(pool_hi - pool_lo) >= size) {
        void *p = pool_lo;
        pool_lo += size;
        return p;
    }
    /* 2026-11-04: say so once: on the Vita a system call from a malloc'd stack stops the app with no log
     * of its own (the first hardware run into gb.x) */
    if (pool_base && !warned) {
        warned = 1;
        printf("kh1-port: the coroutines' stack pool is used up (%lu KiB): malloc'd stacks from here on\n",
               (unsigned long)(pool_hi - pool_base) >> 10);
    }
    return malloc(size);
}
