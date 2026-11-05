/* The app's log file on the Vita, written with sceIoWrite one call per line (unbuffered, timed), and stdio's
 * stdout / stderr pointed at it.  newlib's own fopen'd / freopen'd log stayed empty in Vita3K, and pointing
 * newlib's stdout at a file reached neither its global nor its per-thread stream, so: a funopen FILE for
 * stdout / stderr, and (vpk_log_stdio.c, link it if wanted) printf / vprintf / puts that write here directly.
 * From kh1-decomp host/vita/main.c @ e1575e1a. */
#ifndef VPK_LOG_H
#define VPK_LOG_H

#include <stdarg.h>

/* (re)creates the file at path (removed first: Vita3K's open kept the last run's tail past the new lines
 * without truncating), points stdout / stderr at it and writes first_line as is (0: nothing); the fd, or < 0 */
int vpk_log_open(const char *path, const char *first_line);
/* n bytes to the log (nothing before vpk_log_open) */
void vpk_log_write(const void *buf, int n);
/* a formatted line (up to 4,607 bytes; longer is cut) */
void vpk_log(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void vpk_logv(const char *fmt, va_list ap);

/* the time spent in the log's sceIoWrite calls (microseconds) and their number, for a watchdog line */
extern volatile unsigned int vpk_log_us, vpk_log_writes;

#endif /* VPK_LOG_H */
