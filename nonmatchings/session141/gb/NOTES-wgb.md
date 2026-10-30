# Session 141, worker wgb (gb.x)

## Matched (each confirmed by `make ovl OVL=gb` byte-identical; overlay now 379 functions)

func_00f50f08, func_00f51258, func_00f279a8, func_00f319a8, func_00f2e660,
func_00f34d48, func_00f34ea8, func_00f35288, func_00f353e8, func_00f29038,
func_00f22438, func_00f285e0 (12). All need wm twin ports (lead / port.py).

Also: tools/autodecomp.py disasm() now passes `-z` to objdump (committed with f51258).

## Near misses (drafts in this folder, first comment line has details)

| func | left | blocker |
|---|---|---|
| func_00f37080 | 4 words | lui v0/v1 swap |
| func_00f51360 | 6 words, score 11 | store order / `li 8` placement |
| func_00f3eac0 | 9 words, score 19 | w copied into another reg for first log2 loop |
| func_00f240f0 | 11 words, score 23 | register allocation (tile family) |
| func_00f363a0 | 15 words, score 8 | prologue sd ra order + missing nop after slti |
| func_00f395a8 | 21 words, score 18 | t[3]=1.0f store scheduled first |
| func_00f405c0 | 27-29 words, score 52-54 | w copied in t3/t8; permuter 600s gave 52. Twin func_00f40438 follows it |
| func_00f3fad8 | 59 words, score 96 | GS packet shift/or chain order, 2 insns short |
| func_00f34aa8 | 65 words, score 26 | switch block layout / beql |
| func_00f36ee0 | 81 words, score 18 | frame right; v0=w, v1=col, a1=w copies |
| func_00f268c8 | n/a | original does not CSE x*16 / y*16 |

## Round 2 (after rebase onto claude/project-thread-rl45wv; gb 395, wm 785)

Matched gb (wm twin in brackets, each via portall.py + make ovl OVL=wm byte-identical):
f397a0 [f60898], f20718 [f47810], f28090 [f4f188], f27b38 [f4ec30], f27640 [f4e738],
f2b800 [f528f8], f51440 [f78538], f22d00 [f49df8, hand-fixed: entry 16 is func_00f60af0],
f23098 [f4a190], f288d0 [f4f9c8], f3bfc8 [f630c0], f3bda8 [f62ea0].

New near misses:

| func | left | blocker |
|---|---|---|
| func_00f38158 | 14 words, score 2 | only the t[3]=1.0f store position (lead has taken this one) |
| func_00f425a8 | 30 words, score 39 | a/c regs s5/s7 swapped + store schedule |
| func_00f28aa8 | 62 words, score 51 | (y*26+1952)<<4 must not fold |
| func_00f37448 | 77 words, score 55 | w copied through t1 (same blocker as f36ee0/f405c0) |
| func_00f37618 | 71 words, score 91 | original keeps every memory access in source order |
| func_00f399f8 | 104 words, score 110 | three x88 nibble fields recomputed from int n |

Round 2 tips:
- Double constants in .rodata (`lui at; ld a1,%lo(D)(at)`) are source literals. gcc 2.96 reads
  decimals its own way, so check them: `0.01` gives 3f847ae147ae147a and `0.1f` gives the
  truncated 0x3DCCCCCC promoted. /tmp/claude-0/s141/wgb/dl.py HEX lit... checks double spellings.
- An arg-setup order of `mov.s $f12` before the a0/a1 moves means the float param comes first in the
  prototype: func_00f3bda8(f32 t, f32 *out, void *c).
- A loop whose test sits at the top (no rotation) and that keeps an invariant inside:
  `while (1) { if (i >= 257) break; ... }` (f3bfc8).
- A movz that reuses the loop's `i < n` result needs n in a local (`n = c->n;`) (f3bda8).
- Wait loop `if (X) D=1; else { do f(); while(!X); D=1; }` with two different stores comes from
  `for (;;) { if (X) { D = 1; break; } f(); }` (f51440).
- Store order inside a switch case: the scheduler moves the last store first, so keep source order natural
  (f23098, f2b800, f28090's col[0..2]).
- Frame too small by 16/32 bytes: add unused OvlVec locals (f3bda8) or OvlVec padding in an arg struct (f37448).
- Function-pointer tables: one extern per slot (separate %hi each), not an array (f22d00).
- `s32 a = t->a;` held in a local across two calls gives the extra s-register (f20718).

## Tips

- Entity table: `static inline GbEnt *ent_of(s32 k){ GbEnt *e = D_00F56DC0->hdr.ents; return &e[k]; }`.
  Read one field through ent_of() and the other directly (`D_00F56DC0->hdr.ents[i].c`) to get the
  two separate `D + i*12` adds. Matched f34d48/f34ea8/f35288. Candidates: f20718, f27b38, f28090,
  f2d8d8, f32a38, f333f8, f35a80, f377b0, f38158, f397a0, f39eb0, f3e0d8, f3e388, f425a8, f46718.
- A store to `*pp` that flow deletes under strict aliasing survives when the packet qword type is
  `typedef union { struct { u64 data, addr; }; u64 *ptr; } GbQw;` (f279a8).
- Wait loops with s0=&D and s2=hi: non-volatile global,
  `if (D != 2) { do f(); while (D != 2); }` (f50f08); `for(;;){...; if (D==2) break; f();}` (f51258).
- `id = !alt ? lo : hi` gives movn; `alt ? hi : lo` gives movz.
- GS RGBAQ: `((u64)r | (u64)g<<8 | (u64)b<<16 | (u64)a<<24 | (u64)0x3F800000<<32)` (f319a8, f2e660).
- Case order in the switch source sets case-block order in the output (f353e8, f22438).
- Load a field into a local before the branch to fix load order (`u16 c = e->c;`).
- Permuter fixed f2e660 by moving an address computation after two calls; try that by hand first.
- Permuter output source.c is preprocessed: strip everything before the draft's own typedefs
  before feeding it to hand.py (otherwise "PlatSqrtf previously defined").
- Rotation angle idiom: `D->rx * 3.141592503f * (1.0f / 2048)` (f279a8, f285e0).
