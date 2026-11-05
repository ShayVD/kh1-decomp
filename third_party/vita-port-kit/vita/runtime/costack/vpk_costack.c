/* Stacks for coroutines (vpk_costack.h): from the pool the platform gives, else malloc'd.
 * From kh1-decomp host/port/costack.c @ e1575e1a. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "vpk_costack.h"

static unsigned char *pool_lo, *pool_hi; /* the pool's unused part */
static unsigned char *pool_base;         /* the whole pool: pool_base to pool_hi */
static unsigned long own_lo, own_hi;     /* the whole stack it came from (vpk_costack_stack) */

void vpk_costack_pool(void *base, unsigned int size) {
    pool_base = pool_lo = (unsigned char *)(((uintptr_t)base + 15) & ~(uintptr_t)15);
    pool_hi = (unsigned char *)base + size;
}

void vpk_costack_stack(void *base, unsigned int size) {
    own_lo = (unsigned long)base;
    own_hi = own_lo + size;
}

int vpk_costack_owns(unsigned long a, unsigned int n) {
    if (own_hi && a >= own_lo && a + n <= own_hi) return 1;
    return pool_base && a >= (unsigned long)pool_base && a + n <= (unsigned long)pool_hi;
}

void *vpk_costack_alloc(unsigned int size) {
    static int warned;
    size = (size + 15) & ~15u;
    if (pool_lo && (unsigned int)(pool_hi - pool_lo) >= size) {
        void *p = pool_lo;
        pool_lo += size;
        return p;
    }
    /* say so once: on the Vita a system call from a malloc'd stack stops the app with no log of its own */
    if (pool_base && !warned) {
        warned = 1;
        printf("vpk-costack: the coroutines' stack pool is used up (%lu KiB): malloc'd stacks from here on\n",
               (unsigned long)(pool_hi - pool_base) >> 10);
    }
    return malloc(size);
}
