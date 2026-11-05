/* The app's log file (vpk_log.h).  From kh1-decomp host/vita/main.c @ e1575e1a. */
#include <psp2/io/fcntl.h>
#include <psp2/kernel/processmgr.h>
#include <stdio.h>
#include "vpk_log.h"

static SceUID log_fd = -1;
volatile unsigned int vpk_log_us, vpk_log_writes;

void vpk_log_write(const void *buf, int n) {
    unsigned int t0;
    if (log_fd < 0 || n <= 0) return;
    t0 = (unsigned int)sceKernelGetProcessTimeWide();
    sceIoWrite(log_fd, buf, n);
    vpk_log_us += (unsigned int)sceKernelGetProcessTimeWide() - t0;
    vpk_log_writes++;
}

#ifndef VPK_LOG_NO_STDIO_REDIRECT
static int log_cookie_write(void *cookie, const char *buf, int n) {
    (void)cookie;
    vpk_log_write(buf, n);
    return n;
}
#endif

int vpk_log_open(const char *path, const char *first_line) {
    sceIoRemove(path);
    log_fd = sceIoOpen(path, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777);
    if (log_fd >= 0) {
#ifndef VPK_LOG_NO_STDIO_REDIRECT /* (host tests: funopen and _GLOBAL_REENT are newlib's) */
        FILE *f;
        /* newlib sets the standard streams up at its first stdio call on them (__sinit), which would put the
         * console's back over ours: make that happen first */
        fflush(stdout);
        fflush(stderr);
        f = funopen(0, 0, log_cookie_write, 0, 0);
        if (f) {
            setvbuf(f, 0, _IONBF, 0);
            stdout = f;
            stderr = f;
            _GLOBAL_REENT->_stdout = f;
            _GLOBAL_REENT->_stderr = f;
        }
#endif
        if (first_line) {
            int n = 0;
            while (first_line[n]) n++;
            sceIoWrite(log_fd, first_line, n);
        }
    }
    return log_fd;
}

void vpk_logv(const char *fmt, va_list ap) {
    char buf[4608]; /* room for a shader's text */
    int n = vsnprintf(buf, sizeof buf, fmt, ap);
    if (n > (int)sizeof buf - 1) n = sizeof buf - 1;
    vpk_log_write(buf, n);
}

void vpk_log(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vpk_logv(fmt, ap);
    va_end(ap);
}
