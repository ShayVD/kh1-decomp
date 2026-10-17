/* newlib stdlib/rand.c. sdk segment. */
#include "reent.h"

int rand(void) {
    struct _reent *r = _REENT;
    r->_rand_next = r->_rand_next * __extension__ 6364136223846793005LL + 1;
    return (int) ((r->_rand_next >> 32) & 0x7fffffff);
}
