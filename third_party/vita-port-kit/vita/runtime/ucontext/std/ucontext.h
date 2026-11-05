/* <ucontext.h> for newlib targets: put this directory on the include path (-I.../ucontext/std) and code
 * written against POSIX ucontext (ucontext_t, getcontext, setcontext, swapcontext, makecontext) uses
 * vpk_ucontext.S.  See ../vpk_ucontext.h for what is supported. */
#ifndef VPK_STD_UCONTEXT_H
#define VPK_STD_UCONTEXT_H

#include "../vpk_ucontext.h"

#define ucontext_t vpk_ucontext_t
#define getcontext vpk_getcontext
#define setcontext vpk_setcontext
#define swapcontext vpk_swapcontext
#define makecontext vpk_makecontext

#endif /* VPK_STD_UCONTEXT_H */
