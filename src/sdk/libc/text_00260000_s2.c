/* newlib stdlib/atexit.c. sdk segment. */
#include "reent.h"

void *malloc(unsigned int);

int func_002650e0(void (*fn)(void)) {
    register struct _atexit *p;

    if ((p = _REENT->_atexit) == 0)
        _REENT->_atexit = p = &_REENT->_atexit0;
    if (p->_ind >= 32) {
        if ((p = (struct _atexit *)malloc(sizeof *p)) == 0)
            return -1;
        p->_ind = 0;
        p->_next = _REENT->_atexit;
        _REENT->_atexit = p;
    }
    p->_fns[p->_ind++] = fn;
    return 0;
}
