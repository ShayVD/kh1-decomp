/* newlib errno.c: errno is _impure_ptr->_errno. sdk segment. */
#include "reent.h"

int *__errno(void) {
    return &_REENT->_errno;
}
