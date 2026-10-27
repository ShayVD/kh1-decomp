# Session 139 matching notes

- **xl_limit func_00f20ff0 matched** (ovl/xl_limit/hand/func_00f20ff0.c; the limit set-up for case 3
  of func_00f20000, shaped like the matched func_00f21d90 / func_00f21428). Steps: written from the
  sibling (12 words off); a store-order search over the five closing stores, then decomp-permuter's
  `D_00F23488 = D_00F2348C = 0` and the order 3488 / 348C, 3480, 3484, 3E00 (2 off: D_00F23208's
  `lui` / `lw` in v0, the original v1); the permuter's last step was declaring func_00130578's unused
  return value `u8` (it returns the motion task, `Res *` in func_00f21d90; the return type changes
  the register allocation here). The English disc's xl_limit.x is the pinned one.
- Left in xl_limit.x (7): func_00f202d8, func_00f20400, func_00f206e8, func_00f20ae0, func_00f20e10,
  func_00f21e60 (1,448 bytes), func_00f225b0.
