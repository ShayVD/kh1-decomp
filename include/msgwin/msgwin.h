/* Message windows (src/msgwin/msgwin.c; docs/modules.md "Session 32").
 *
 * The script sets up 8 window templates D_006298F0[0..7] (position v30, size
 * v40, f1c, h4 / h6 / h8 / hc / he, f94), queues message ids for each one in
 * D_00389C90.tbl[k] (VmMgr, vm/vm_mgr.h), and opens a template in one of the
 * 4 windows D_00629E70[0..3]; D_0062A130 is one more window.  The window
 * code (func_0010bd90 / func_0010bdd0 / func_0010ef70 ...) calls back into
 * this module when a window opens, shows its text or closes.  The three
 * arrays are contiguous, 0xb0 bytes per entry (D_0062A130 is entry 12). */
#ifndef KH1_MSGWIN_MSGWIN_H
#define KH1_MSGWIN_MSGWIN_H

#include "common.h"

typedef struct {
    s32 x0;
    u16 h4;
    u16 h6;
    u16 h8;
    u8 pada[2];
    u16 hc;
    u16 he;
    u8 pad10[0xc];
    f32 f1c;
    u8 pad20[0x10];
    f32 v30[2];             /* 0x30: position */
    u8 pad38[8];
    f32 v40[2];             /* 0x40: size */
    u8 pad48[0x38];
    u8 f80[0x10];
    u8 b90;
    u8 pad91[3];
    f32 f94;
    u8 pad98[0x18];
} __attribute__((aligned(8))) MsgWin;

extern MsgWin D_006298F0[];     /* the 8 templates */
extern MsgWin D_00629E70[4];    /* the open windows (src/data/bss_0062.c) */
extern MsgWin D_0062A130;       /* D_00629E70[4] (src/data/bss_0062.c: Ent176 D_00629E70[5]) */

/* Reset the templates (called at script load, src/vm/script_vm.c). */
void func_001cab48(void);
/* Close every open window. */
void func_001caf58(void);

#endif /* KH1_MSGWIN_MSGWIN_H */
