/* getcontext / setcontext / swapcontext / makecontext as vpk_ names for the Vita's Cortex-A9 (newlib has
 * no ucontext; vpk_ucontext.h): the AAPCS callee-saved registers (r4-r11, sp, lr, d8-d15, FPSCR) saved and
 * loaded.  Meant for coroutines, so a switch only happens at a call and the caller-saved registers need no
 * saving.  Each context keeps its own FPSCR (rounding, flush-to-zero).
 * From kh1-decomp host/vita/context.S @ e1575e1a (renamed kh1_ to vpk_). */
	.syntax unified
	.arm
	.text


	.global vpk_getcontext
	.type vpk_getcontext, %function
vpk_getcontext:
	add r1, r0, #16
	stmia r1!, {r4-r11}
	str sp, [r1], #4
	str lr, [r1], #4
	vstmia r1!, {d8-d15}
	vmrs r2, fpscr
	str r2, [r1]
	mov r0, #0
	bx lr

/* r0: the context to load; returns from that context's call (0) */
	.global vpk_setcontext
	.type vpk_setcontext, %function
vpk_setcontext:
	add r1, r0, #56
	vldmia r1!, {d8-d15}
	ldr r2, [r1]
	vmsr fpscr, r2
	add r1, r0, #16
	ldmia r1!, {r4-r11}
	ldr sp, [r1], #4
	ldr lr, [r1]
	mov r0, #0
	bx lr

/* r0: save the caller here, r1: load this */
	.global vpk_swapcontext
	.type vpk_swapcontext, %function
vpk_swapcontext:
	add r2, r0, #16
	stmia r2!, {r4-r11}
	str sp, [r2], #4
	str lr, [r2], #4
	vstmia r2!, {d8-d15}
	vmrs r3, fpscr
	str r3, [r2]
	mov r0, r1
	b vpk_setcontext

/* r0: the context, r1: the entry.  The context starts in vpk_ctx_start on its own stack with the
 * entry in r4 and the context in r5; the stack top is 8-aligned (AAPCS) */
	.global vpk_makecontext
	.type vpk_makecontext, %function
vpk_makecontext:
	ldr r2, [r0, #4]              /* uc_stack.ss_sp */
	ldr r3, [r0, #8]              /* uc_stack.ss_size */
	add r2, r2, r3
	bic r2, r2, #7
	str r1, [r0, #16]             /* r4: the entry */
	str r0, [r0, #20]             /* r5: the context */
	str r2, [r0, #48]             /* sp */
	adr r3, vpk_ctx_start
	str r3, [r0, #52]             /* lr */
	bx lr

vpk_ctx_start:
	blx r4
	ldr r0, [r5]                  /* uc_link */
	cmp r0, #0
	bne vpk_setcontext
	bl abort
