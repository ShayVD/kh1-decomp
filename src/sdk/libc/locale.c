/* newlib locale/locale.c, _setlocale_r (the rest matched automatically:
 * src/sdk/auto). sdk segment. */
#include "reent.h"

int strcmp(const char *, const char *);

extern char D_00491FC8[]; /* "C" */
extern char D_00491FB8[]; /* "" */

char *_setlocale_r(struct _reent *p, int category, const char *locale) {
    if (locale) {
        if (strcmp(locale, D_00491FC8) && strcmp(locale, D_00491FB8))
            return 0;
        p->_current_category = category;
        p->_current_locale = locale;
    }
    return D_00491FC8;
}
