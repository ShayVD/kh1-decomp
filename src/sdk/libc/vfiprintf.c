/* newlib stdio/vfprintf.c built with INTEGER_ONLY (vfiprintf), the wrapper.
 * sdk segment. */
#include "reent.h"

int vfiprintf(FILE *fp, const char *fmt0, va_list ap) {
    CHECK_INIT(fp);
    return _vfiprintf_r(fp->_data, fp, fmt0, ap);
}
