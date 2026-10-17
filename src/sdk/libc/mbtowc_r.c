/* newlib stdlib/mbtowc_r.c (no multibyte locales). sdk segment. */
#include "reent.h"

typedef int wchar_t;
typedef int mbstate_t;

int _mbtowc_r(struct _reent *r, wchar_t *pwc, const char *s, size_t n, mbstate_t *state) {
    wchar_t dummy;
    unsigned char *t = (unsigned char *) s;

    if (pwc == 0)
        pwc = &dummy;

    if (s == 0)
        return 0; /* not state-dependent */

    if (n == 0)
        return -1;

    *pwc = (wchar_t) *t;
    return (*t != '\0');
}
