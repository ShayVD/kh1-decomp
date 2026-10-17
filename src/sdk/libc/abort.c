/* newlib stdlib/abort.c. sdk segment. */
#include "reent.h"

int raise(int);

void abort(void) {
    while (1) {
        raise(6); /* SIGABRT */
        _exit(1);
    }
}
