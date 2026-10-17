# Session 5 near-miss drafts

Not built. File names are `<worker dir>__<file>`. Most files hold the target function and the types it needs. Some (s1__*, c09 group) must be appended after the head of the file named below. The word counts in each worker's notes are approximate.

To test a draft, use `python3 tools/autodecomp.py try NAME --file F --out-dir src/hand[/mode]` or `tools/checkfile.py`. Jump-table and literal drafts need the rodata-tolerant runner (tools/matching/wqb03_rr.py ADDR try ...).

Notes recorded during the session, including which callee must be defined above each caller:

(unresolved after consolidation pass 1)
DONE func_00180c20: 2-5 words off even with func_00180ab8 above (scheduling)
func_00113e28: needs func_00113df8 above + printf a1/a2 order
func_00137330: 8 bytes too long (&b built twice)
func_001c4808: needs func_001c3770 (unmatched?) above; /tmp/claude-0/s/w42/c4808.c
DONE func_001c91e8: needs func_001c6890 above; /tmp/claude-0/s/w42/c91e8.c
DONE func_001ce4b8 (nostrict_nofill, rodata doubles 180.0/pi at 0x490610): rodata placement fails in make; code /tmp/claude-0/s/w42/ce4b8_rodata.c
DONE func_00249c48: layout symbol covers several functions (stub jumping to 0x249d48, bodies at 0x249c60/0x249d20/0x249d48) - investigate split
D_003F2C40 group (func_0020dd38 0020de28 0020ded8 0020dfc8 0020e090 0020e1c0 002114f0 00214290): base kept in own reg (lui;addiu;addu) where gcc folds to la SYM(r); maybe different flags for that file - investigate
DONE func_0022fba8: needs func_0022f818 (unmatched) above; /tmp/claude-0/s/w48/pending_0022fba8.c
DONE func_00233610: layout symbol holds several small functions after a j to local label - investigate split
branch-likely vs plain near-misses (maybe callee-earlier): func_00142e30 (no draft found), [DONE] func_00145aa0 (needs 00145188 above), [DONE] func_0014ade0 (needs 0014a1b0 above) (w56; best in /tmp/claude-0/s/w56/)
w53 near-misses: [DONE func_00126c10, now below func_00125dc8 in b01] func_0011cdf0 (5, regswap), func_00120cf8 (7, sched), func_00126c10 (5, delay slot), func_001269d8 (19 tail reload)
DONE func_0012f700 (w54): needs func_0012f560/func_0012f690 (h5.c) above it; code in w54 report, saved below
w54 near-misses: func_0012f868 (3), func_00130398 (4), func_00130660 (7), func_00139240 (hoist)
w57 near-misses: func_0014bba8 (4, arg order), func_0014ee88 (3, reg), func_0014b9e0 (12), func_00152928 (13)
w58 callee cases (code in /tmp/claude-0/s/w58/callee_*.c, hdr.h): [DONE] func_00153500 (needs 001532c8+00152598 from h9), [DONE] func_00157a30 (needs 00157a00 from src/auto, 3 params), [DONE] func_0015b098 (needs 0015b060 from h10, rodata); near-miss func_00156e88 (6)
w62 near-misses: func_00182ec0 (3, sched; /tmp/claude-0/s/w62/ec0_b.c), pppPointRApFrame (20 fregs; pra_a.c)
w60 near-misses: func_00169510 (4, reg), func_0016ce10 (23, reg order)
w61 near-misses: func_00179d30 (3, sched), func_00172998 (6), func_00175be0 (21, maybe needs func_00175ba0 in h11 above)
w63 near-miss: func_0018e348 (4, a0 vs a2; /tmp/claude-0/s/w63/b9.c)
w64: func_0019cb88 needs func_0019bbf0 (undecompiled, 3140B) above; func_001a0628 needs func_0019f1f0 (3996B) above. Code /tmp/claude-0/s/w64/. Do after 161+ band.
w64 near-miss: pppKeShpTailXFrame / pppKeShpTail2XFrame (2, swc1 vs addiu order)
VU0 asm functions to flag in docs: func_001996d0, func_0019a828 (nostrict/text_00190000_h64.c)
w65: [DONE] func_001aaf88 needs func_001aaed0+func_001aaf00 above (/tmp/claude-0/s/w65/func_001aaf88_with_callees.c). func_001aa1f8/func_001aa448 need `sq $zero` (inline asm?). func_001a2d40 maybe needs func_001a26f0 above.
DONE w66: func_001c0460 needs func_001bffa0 (h14) above; func_001c13e8 (nostrict) needs func_001c0bf0 (h41) above. func_001bfac8 = context-switch asm (flag). near: func_001c1718.
w69: [DONE] func_001f52e8 -> /tmp/claude-0/s/later/1f52e8.c. near: func_001f0448 (9). Grid-menu group func_00208ea8/9030/91b8 (same reg issue)
w68 near: func_001e6038 (3, lui reg), func_001f0148 (8, s4/s5 swap jtbl). near_*.c in /tmp/claude-0/s/w68/
w72 near: func_00228e70 (6, regs; /tmp/claude-0/s/w72/e70_best.c)
w71: func_00219870 needs func_00219598 (182 instr, undecompiled) above it; body /tmp/claude-0/s/w71/9870_best.c, goes in src/hand/text_00210000_h71.c. near: func_0021af38 (10), func_0021b6a0 (13, jtbl)
w73: func_0022f818 now in src/hand/text_00220000_h73.c -> func_0022fba8 can go below it. near: func_00237d48 (2), func_002327b0 (3)
w74 [DONE func_0023f0d8: callee float param order]: func_0023ee80 needs func_0023e8f0 (undecompiled) + func_0023e330 above (/tmp/claude-0/s/w74/ok_23ee80_*). near: func_0023f0d8 (2), func_00238258 (4), func_0023ec88 (5), func_0023d528 (6)
b00 near (in /tmp/claude-0/s/b00/): func_00101bb8 b10.c (2, nostrict), func_00106000 d9.c (2, rodata), func_001012e0 h6.c.best (6). VU0: func_00115940
w75: func_00245b08 needs 00245a08+00245ad8 above; func_00246ed8 needs 00246ea8. near: func_0024bce8 (5), func_0024d1c8 (7), func_0024ddf8 (9, rodata). Remaining part func_0024d618 now 408B (split done)
b01: func_0011c338 needs func_0011a728 (undecompiled) above (/tmp/claude-0/s/wq01/c338_callee_earlier.c). near: func_00126f18 (2), func_0011f668 (7), func_00119ad8 (8) in /tmp/claude-0/s/wq01/
b03 near: [DONE] func_00149170 (needed func_00148fb0 above; now in h34), func_00140960 (2; g_best.c)
b02: func_0012fcd0 needs 0012eb08+0012fa98 (h5), 0012fc58 (src/auto), 0012f868 (near-miss w54) above; /tmp/claude-0/s/wqb02/12fcd0_match.c. near: func_00127568 (3), func_001350d8 (8)
b04 near: [DONE func_001568e8, needs func_00156768 above, in h58] func_001502e8 (2; /tmp/claude-0/s/b04/partial_1502e8.c), func_001568e8 (5, delay slots; partial_1568e8.c)
DONE b06: func_00179700 (strict) needs func_00177358 (h11) above: /tmp/claude-0/s/b06/callee_f179700.c
DONE b06: func_0017ae48 (strict) needs func_00176f08 (h61) above: /tmp/claude-0/s/b06/callee_f17ae48.c
DONE b06: func_0017cf08 (nostrict) needs func_001770b8 (h38) above: /tmp/claude-0/s/b06/callee_f17cf08_full_nostrict.c
DONE b06: func_0017d238 (nostrict) needs func_00176f08 (h61) + func_0017b200 (src/auto/text_00170000_4.c) above: /tmp/claude-0/s/b06/callee_f17d238.c
b05: func_00168d20 needs func_00168618 (near-miss w59, 55 words) above: /tmp/claude-0/s/b05/func_00168d20_needs_00168618_above.c. near: func_00166248 (4), func_00170170 (4, jtbl), func_001752a0 (14)
DONE b07: func_00181738 (nostrict) needs func_00180280 (h38, also matches nostrict) above: /tmp/claude-0/s/b07/func_00181738_callee_earlier.c. near: pppKeBornRndFrame (6)
DONE b09: func_001a2248 (strict) needs func_001a2178 (in vu0.c) above: /tmp/claude-0/s/wqb09/f1a2248_callee_above.c
b09: func_001a67f0, func_001a72c8 are GNU nested functions of func_001a7718 (static chain in v0) - do together with func_001a7718.
DONE b13 near: func_0020a248 (6; /tmp/claude-0/s/b13/nearmiss_0020a248.c)
DONE b12: func_001f54f8, func_001f5988 (nostrict) need func_001f4570 (now in nostrict/text_001f0000_h69.c) above: /tmp/claude-0/s/b12/callee_54f8.c, callee_5988.c. near (2 words, X/Y reg tie): func_002016b0, func_00201988, func_00201c60 in /tmp/claude-0/s/b12/nearmiss/
b10: func_001c4ed0 needs func_001c1ce8 (src/auto/text_001c0000.c) above: /tmp/claude-0/s/wq10/c4ed0.c. near: func_001cd2d8 (16, nofill), func_001cb440 (21). func_001ca368 matches with -fno-gcse (investigate per-file flags?)
DONE b15 near: /tmp/claude-0/s/b15/near_0022d730_nofill.c (2w arg load swap), near_0022db98_nofill.c (2w same), near_00220c28_nofill.c (6w), near_00233168.c (17w gcse)  [d730/db98/0c28 matched; 3168 split to next line]
b15 near: func_00233168 (21w in checkfile, 1132 vs 1136; GCSE keeps q->n in reg) /tmp/claude-0/s/b15/near_00233168.c - still open
b11 near: /tmp/claude-0/s/b11w/near_1d5b58.c (2w store swap), near_1e0ab0/1e0d98/1e10f8.c (4w each, li v0,4 filled into bgtz slot vs nop), near_1f0ea8.c (~20w nofill)
b16 callee-earlier: /tmp/claude-0/s/b16/f23f250_needs_d528_above.c (d528 undecompiled), f240b68_needs_d148_409e0_above.c, f2416a8_needs_d698_414a8_410b8_above.c, f243ef8_needs_243d18_above.c
c00 near: /tmp/claude-0/s/c00/near_00109770.c (13w, rodata 0048cce0, cross-jumped tail regalloc)
b17 callee-earlier: /tmp/claude-0/s/b17/match_00248b58_needs_002489c8_above.c (callee in src/auto/text_00240000_14.c; Mgr type conflicts with Vec12Mgr in h26)
b14 near: /tmp/claude-0/s/b14w/near_77c8.c (5w strict lui early); 9598t_a.c.best (28w, unlocks w71 9870_best.c which matches when 9598 is above it); e120c.c (23w)
c01 callee-earlier: /tmp/claude-0/s/c01/func_00124218_nostrict_needs_00123f28_above.c (callee in nostrict h30); func_00126360_nostrict_needs_00126238_above.c (callee strict h31, also matches nostrict); func_0012e4b0_needs_ca38_e1b0_above.c (callees undecompiled, stubs ok?); func_00130f18_needs_00130660_above.c (callee undecompiled)
c04 callee-earlier: /tmp/claude-0/s/c04/func_00179ee8_needs_00176f08_00177680_above.c (callees in h61 and h38, both strict)
c05b near: /tmp/claude-0/s/c05b/pppKeShpTail2Draw_near165.c, pppKeShpTail2XDraw_near171.c (same size, global-alloc order)
c03 near: /tmp/claude-0/s/c03/f28_near.c (13w, ndiff 3), 9688_near.c (ndiff 22)
c11 near: /tmp/claude-0/s/c11/near_001f4778_with_4570_above.c (20w, nostrict, place in h69 after 4570)
