/* newlib stdlib/assert.c. sdk segment. */
#include "reent.h"

/* "assertion \"%s\" failed: file \"%s\", line %d\n" */
extern const char D_004919E8[];

void __assert(const char *file, int line, const char *failedexpr) {
    (void) fiprintf(_REENT->_stderr, D_004919E8, failedexpr, file, line);
    abort();
    /* NOTREACHED */
}
