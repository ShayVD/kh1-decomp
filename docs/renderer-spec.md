# Renderer specification (phase 3)

What the PS2 renderer of Kingdom Hearts Final Mix (`SLPS_251.98`) does, written
for a future PC/Vita port. This is not matching work: nothing here changes the
build. Session 14 (VU worker), from static analysis of the ELF and of our
matched C. Nothing was traced at run time.

Conventions:

- Addresses are main-RAM addresses in the pinned ELF. `func_XXXXXXXX` and
  `D_XXXXXXXX` are the names used in `src/`. VU addresses are in qwords
  (16 bytes) unless marked as bytes, and VU code addresses are in
  instructions (8 bytes each).
- **(inferred)** marks a conclusion drawn from the code's shape and not
  confirmed by a run or by data. Everything else is read directly from code
  or from static data, and can be checked with the tools below.
- Program numbers `P0`..`P21` are the indices printed by `find_vu1.py`.

## Tools (all read the user's own ELF; never commit their output)

| Command | What it shows |
| --- | --- |
| `python3 -I tools/vu/find_vu1.py SLPS_251.98 --layout layout.tsv` | the 22 VU microprograms, their MPG chunks, the DMA tag that carries each one, and the code or table that references it |
| `python3 -I tools/vu/find_vu1.py SLPS_251.98 --disasm N` | VU disassembly of program N (upper and lower pipes, `[E]`/`[I]` bits, labels) |
| `python3 -I tools/vu/find_vu1.py SLPS_251.98 --summary N` | opcode histogram of program N and its fixed (`vi00`-based) VU memory accesses |
| `python3 -I tools/vu/vif_chain.py ADDR...` | walks a static DMA chain and prints its tags and VIF commands (STCYCL, UNPACK layout, MPG, MSCAL/MSCNT, BASE/OFFSET); `--one` decodes a single spliced tag. New in this session |
| `python3 -I tools/vu/gs_packets.py --callers --layout layout.tsv` | decodes every static GS packet passed to the GIF send wrapper `func_00106b18`, register by register |
| `python3 -I tools/vu/model_header.py FILE` | structure of a model or map file you extracted (`.mdls`, `MOBJ` chain, map `.bin`, `.ard`, renderer A mesh header); layouts in docs/structs.md. New in session 16 |
| `python3 -I tools/vu/rb_stream.py FILE --mobj OFF [--ram] [-v]`, `--scan --ram` | decodes and checks renderer B mesh command streams (§2.3 "Input") for every part of a `MOBJ`/`MENV` in a `.mdls`, the ELF, or a PCSX2 `eeMemory.bin` (`--ram`: pointers already relocated); `--scan` finds every chunk. New in session 17 |
| `python3 tools/kh1tool.py asm func_X` / `src/` | the EE side; every function cited here is matched C, so the source is the reference |

A quick way to see the differences between programs is to diff two `--disasm`
outputs with the address column cut off. That is how the family tables below
were built.

## 1. Overview

The renderer uses all three GS paths:

- **PATH1 (VU1 XGKICK)** for all 3D geometry. There are two VU1 renderers,
  each with its own set of microprograms:
  - **Renderer A** (`P0`-`P7`, plus the standalone `P8`): strip meshes with
    full polygon clipping. Its C side is at `0x00100000`-`0x00115000`
    (`func_00100580`, `func_00107ec0`, `func_00108900`-`func_00108fd0`,
    `func_00114c18`). It supports per-vertex fog, environment mapping and UV
    scrolling, so it draws the world/background (inferred: the field maps).
  - **Renderer B** (`P10`-`P20`): command-stream meshes with a matrix palette
    and weighted multi-bone skinning, per-vertex directional lighting,
    PSMT8 textures uploaded per draw and two-pass alpha. Its C side is at
    `0x0015E000`-`0x00163000` (files `src/hand/nostrict/text_00140000_b04.c`,
    `text_00150000_h36.c`, `text_00150000_h59.c`, `text_00140000_s6_07.c`).
    This is the character/object renderer (inferred from the skeleton code in
    `func_00162xxx` that feeds it).
- **PATH3 (GIF DMA, channel 2)** for 2D: UI, fonts, fades, the end-of-frame
  copy and texture uploads. Static packets go through `func_00106b18`; dynamic
  ones go straight to `PlatDmaSend(PlatDmaGetChan(2), tag)` (include/platform/dma.h;
  libdma's sceDmaSend / sceDmaGetChan, named from their code in session 56).
- **PATH2 (VIF1 DIRECT)** was not seen in any static chain.

VU0 runs one micro-mode program (`P21`) for skeleton matrices. The rest of the
game's VU0 work is macro mode (inline `vXXX` in C, `src/hand/vu0.c`).

All drawing is ordered by a **draw list**: callbacks sorted by an integer key,
built during frame N and executed during frame N+1 from DMA-end interrupts
(section 4).

## 2. VU1 microprograms

### 2.1 Inventory

`find_vu1.py` reads dvp-as's `.DVP.ovlytab`. Every program is linked at VU
address 0. Sizes are in instructions.

| P | Size | Carrier (DMA tag) | Uploaded by | Role |
| --- | --- | --- | --- | --- |
| 0 | 400 | REF `0x0048C6F0` (table index 0) | `func_00100580(0,..)`, `func_00108970` (generic copier) | A: textured strips, culling, clipping, no fog |
| 1 | 368 | REF `0x0048C710` (table index 2) | `func_00114c18(.., 2)` (chains `D_004D9380`/`D_004D9420`) | A: float-STQ strips, no backface cull; the projected-shadow receivers (§3.4) |
| 2 | 413 | REF `0x0048C700` (table index 1) and inside the templates `0x0048C630`/`0x0048C690` | `func_00100580(1,..)`, `func_001148c8` -> `func_00108a60(.., 1, ..)` (objects `D_002A6C60`: area props, session 16) | A: P0 + per-vertex fog |
| 3 | 468 | REF `0x0048C720` (table index 3) | `func_00100580(3,..)` | A: P2 + env-map and UV-scroll texture coordinates |
| 4 | 373 | REF `0x0048C730` (table index 4) | `func_00108cf8(.., 4)` | A: P0 without backface culling (double-sided); the two map meshes of the `.bin` (docs/structs.md) |
| 5 | 72 | REF `0x0048C740` (table index 5) | `func_001148c8` (objects `D_002AA060`) | A: single-colour mesh, no clip or cull; prop shadow silhouettes (§3.4) |
| 6 | 431 | REF `0x0048C750` (table index 6) | `func_00100580(6,..)` | A: P0 + spherical point light (inferred) |
| 7 | 413 | REF `0x0048C760` (table index 7) | table | A: P2 with the batch PRIM forced to a fixed value |
| 8 | 105 | CNT `0x0048C770` (complete chain) | `func_00103c48` | standalone 25x25 textured height-grid demo/effect |
| 9 | 10 | END `0x00272C70` (VIF1) | `func_0015f018` (init) | seeds VU1's random register (`RINIT`) and exits; draws nothing |
| 10 | 140 | END `0x00272E20` | `func_0015fc00` via `D_00351BE0[4,5,12,13,20,21]` | B: rigid, no cull or clip; kicks the header tag first |
| 11 | 125 | END `0x002732A0` | `D_00351BE0[0]` | B: rigid, flat colour, cull |
| 12 | 139 | END `0x002736B0` | `D_00351BE0[1,17]` | B: rigid, lit (3 lights + ambient), cull |
| 13 | 183 | END `0x00273B30` | `D_00351BE0[2,6,7,14,15,18,22,23]` | B: skinned, flat colour, cull |
| 14 | 209 | END `0x00274110` | `D_00351BE0[3,11,19]` | B: skinned, lit, cull |
| 15 | 502 | END `0x002747C0` | `D_00351BE0[8]` | B: rigid, flat colour, full clipping |
| 16 | 532 | END `0x002757A0` | `D_00351BE0[9]` | B: rigid, lit, full clipping |
| 17 | 583 | END `0x00276870` | `D_00351BE0[10]` | B: skinned, flat colour, full clipping |
| 18 | 104 | END `0x00277AE0` | `D_00351BE0[16]` | B: rigid, flat colour, backface cull but no `CLIPW` test |
| 19 | 118 | END `0x00277E40` | `func_0015fc00` when `fl & 8` and `x48 & 0x10` | B: special (see 2.3) |
| 20 | 138 | END `0x00278210` | `func_0015fc00` when `fl & 8` | B: special (see 2.3) |
| 21 | 113 | END `0x00278680` (**VIF0**) | `func_0015f018` (init) | **VU0** micro: Euler rotation to matrix for bones |

How a program reaches VU micro memory:

- **Renderer A**: the 8 REF tags at `0x0048C6F0`-`0x0048C760` form a table.
  Its order is P0, P2, P1, P3, P4, P5, P6, P7 (index 1 is P2, index 2 is
  P1). Every per-object chain starts with one of them (`func_00100580` copies tag `idx` and an END tag, `D_00472150`, into
  two double-buffered slots; `func_00108970`/`func_00114c18` do the same
  into object chains). So **the program is re-uploaded with every object
  chain**: an MPG of 368-468 instructions per object.
- **Renderer B**: `func_0015fc00` (state 1 of `func_0015ff78`) sends the END
  chain of the chosen program on VIF1 (`D_0055C640 = sceDmaGetChan(1)`).
  Each chain is `MPG; MSCAL 0; BASE; OFFSET`. The `MSCAL 0` runs the init
  block up to the first `[E]`.
- **Boot** (`func_0015f018`): VIF0 and VIF1 error masks are set (`VIFn_ERR =
  6`), `P21` goes to VU0 over DMA channel 0 and `P9` goes to VU1 over channel 1.
- `P8` is one complete CNT/NEXT/REFE chain sent by writing `D1_TADR`/`D1_CHCR`
  directly (`func_00103c48`); `func_00106db0` and `func_00108d90` kick
  renderer A chains the same way (`D1_CHCR = 0x105` or `0x145`: chain mode,
  `0x145` with TTE).

### 2.2 Renderer A (P0-P7)

**VU1 memory map** (filled per frame by `func_00107ec0` into the static block
at `0x0048BFD0`/`0x0048C060`, or `0x0048C300`/`0x0048C390` for the other
frame parity `D_00351BD0`):

| VU qw | Source (EE) | Use |
| --- | --- | --- |
| 0-3 | object matrix (arg of `func_00107ec0`; per object via `func_00108be8`/`func_00108c58`) | local -> world |
| 4-7 | `D_002BC170` (4x4 s32 block) | qw4.w / qw5.w = fog coefficients A, B (P2, P3, P7); qw6 = RGBA scale (P0-P4, P6, P7; P5 uses it as the flat colour); qw7 unused? |
| 8-11 | `D_002BC020` | world -> clip (frustum-normalised: `CLIPW` against w) |
| 12-15 | `D_002BBF60` | clip -> GS screen (viewport, Z scale, `XYOFFSET` centring) |
| 16-31 | `D_002A3F60[4]` | UV-scroll offsets; P3 reads `qw(15+n).xy` for vertex flag n (inferred: 16 material slots, 4 per matrix) |
| 32-33 | `D_00494BC0` rows | P6 point light: qw32 = position (xyz) and radius (w), qw33 = colour |
| 36-39 | `D_002A6C10` (built by `func_00107e60`) | P3 env-map matrix (normal -> sphere-map ST) |
| 48 | uploaded by `MSCNT` | GIF tag template used for clipped output |
| 0x58-0xA0 | scratch | clipper polygon buffers (`0x58` and `0x80`) |
| 168 / 568 | `BASE 168`, `OFFSET 400` | double-buffered input batches (TOPS) |
| 0x30 | scratch | GIF packet built by the clipper |
| down from 0x400 | `vi14` stack | clipper save area |

Per-object chain (template `0x0048C630`/`0x0048C690`, built by
`func_00108a60` -> `func_00108900`, `func_00108970`, `func_001089f8`,
`func_00108b60`; or `func_00114c18` for the `Ent52` path). Walk it with
`vif_chain.py 0048c630`:

1. `REF -> MPG` program (2.1).
2. `REF 9 qw`: `STCYCL 1,1; UNPACK V4-32 8 -> @0` (VU 0-7: object matrix and
   `D_002BC170`).
3. `REF 42 qw`: `UNPACK V4-32 40 -> @8` (VU 8-47), `MSCAL 0` (init),
   `BASE 168`, `OFFSET 400`.
4. Two REF slots, which are placeholders (`REF qwc 0 -> 0x004862A0`) in the
   template. `func_001089f8`/`func_00108b60` fill them with two tags read from
   the model file header (+0x80..+0x9C, relocated by the file base). One of
   the possible values is `D_00486300`/`D_004862D0`: `UNPACK V4-32 1 -> @0
   +TOPS` of a GIF tag, then `MSCNT`. That runs the second init block, which
   stores the tag at VU qw48 as the clipped-output template:
   `TRIFAN|IIP|TME|ABE|CTXT2`, without or with `FGE` (`0x312EC000`
   or `0x313EC000` in the tag's PRIM word). The mesh stream itself comes from
   the model file (inferred).
5. `END` (`D_00472150`).

Each object has two such 0x60-byte chains, one per frame parity, so the EE can
build frame N+1 while DMA reads frame N.

**Input batch** (at TOPS, one per `MSCNT`):

- qw0 = GIF tag for the batch. `NLOOP & 0x7FFF` = vertex count n. It is copied
  to the output with its REGS word replaced by the template's (`0x412` = ST,
  RGBAQ, XYZF2) and carries the strip's PRIM. Its w word (the unused upper
  REGS bits) is copied into the PRIM word of the qw48 template (`MR32` twice,
  `SQ.y`), so each batch also says which PRIM its clipped fans use
  (inferred from the code; P5 does not update the template and P7 forces the
  PRIM, see 2.2.1).
- then n x 3 qwords, interleaved per vertex:
  - `[0]` position xyz (float), w = **strip flag** (integer via `MTIR`):
    0 = do not draw a triangle at this vertex (strip restart), +-1 = draw,
    with the sign giving the winding for backface culling;
  - `[1]` colour RGBA (integers, `ITOF0`, multiplied by qw6 and converted
    back with `FTOI0`; 0x80 = 1.0 in GS convention);
  - `[2]` ST as 1.12 fixed point (`ITOF12`); Q comes from 1/w. In P3 the w
    of this qword selects the texture-coordinate mode (2.2.1).
- The VIF UNPACK formats that produce this layout are set by the model data,
  not by the ELF (open question 1).

**Per vertex** (P0, the base program):

1. `clip = M_clip * (M_view * M_local) * pos`. The two matrices are
   pre-multiplied in the init block (`0x0176`): VU 8-11 x VU 0-3 gives vf13-16.
2. `CLIPW.xyz clip, clip.w` on the last 3 vertices. `FCAND 0x3F` /
   `FCAND 0x020820` and the `FCOR` cascade classify each triangle as inside
   (draw), entirely outside one plane (reject) or crossing (clip).
3. `screen = M_screen * clip`, then `* 1/w` (`DIV Q`, `MULQ`), then `FTOI4`
   (12.4 fixed point) for XYZ.
4. STQ = (S, T, 1) x Q (perspective-correct texturing), RGBA as above.
5. **Backface culling**: the cross product (`OPMULA`/`OPMSUB`) of two screen
   edges, multiplied by the vertex's strip flag. If its sign says back-facing,
   or the strip flag is 0, the vertex's XYZ w is set to `0x8FF0` (ADC bit +
   F=0xFF), so the GS does not draw the triangle that ends there.
6. Fog field F: constant 255 in P0 (I register, `MULI.w`).
7. Output (in place after the input, `vi02 = top + 1 + 3n`): the GIF tag, then
   per vertex `ST(Q)`, `RGBAQ`, `XYZF2` (REGS `0x412`, packed; in GIF REGS
   code 4 is XYZF2). `XGKICK` once per batch.

**Clipping** (P0-P4, P6, P7; code `0x005E`-`0x0175` in P0): a triangle that
crosses the frustum is clipped by a Sutherland-Hodgman loop over the 6 planes
(`vi05` = plane masks `0x800, 0x80, 0x40, 0x200, 0x100, ...`, `vf30.x` = +-1
for the plane side). Vertices are interpolated in clip space (position,
colour, STQ). The result is projected and written as a separate GIF packet at
VU qw `0x30` using the template at qw48 (a TRIFAN), `XGKICK`ed, and the strip
then resumes. A port can drop this code and let the API clip.

#### 2.2.1 Differences between the A programs

From diffs of the disassembly:

| P | Fog F | Backface cull | Texture coordinates | Other |
| --- | --- | --- | --- | --- |
| 0 | 255 | yes | ST 1.12 | - |
| 1 | none written (no I=255; ADC word `0x8000`) | no | STQ as float (`MULQ` without `ITOF12`), strip flag in STQ.w | all-float input: position xyzw, RGBA float (`FTOI0` only), 4 XGKICKs |
| 2 | `clamp(qw4.w + qw5.w * Q, 0, 255)` | yes | ST 1.12 | colour scale qw6 |
| 3 | as P2 | yes | ST 1.12, or flag `0x11` = env map, or flag n != 0 = ST + VU qw(15+n).xy (UV scroll) | env map: `ST = 0.5 * (M36 * v).xz + 0.5` (inferred: sphere map from the normal) |
| 4 | 255 | no | ST 1.12 | double-sided |
| 5 | 255 | no | none | colour from VU qw6, no clipping |
| 6 | 255 | yes | ST 1.12 | `d = |p - L.xyz| - L.w`; if inside (sign flag), colour += qw33 * |d|, clamped to 0..255 (inferred: point-light glow) |
| 7 | as P2 | yes | ST 1.12 | replaces the batch tag's PRIM word with the constant `0x313E4000` (`TRISTRIP|IIP|TME|FGE|ABE|CTXT2`, NREG 3) instead of taking it from the mesh: a forced fogged, blended variant (inferred) |

Fog in P2/P3/P7 is linear in 1/w: `F = A + B/w`, clamped. The GS blends
toward `FOGCOL` by `(255 - F)`.

### 2.3 Renderer B (P10-P20)

**Selection** (`func_0015fc00`, `src/hand/nostrict/text_00150000_s6_08.c`):
`v = object->x48` (a byte of flags). Bit 2 is kept only when the entry's
`fl >> 4 & 2` is set, and bit 1 = `fl >> 4 & 1`. The program is
`D_00351BE0[v]` (24 entries at `0x00351BE0`). Read off the table:

| v | 0 | 1 lit | 2 skinned | 3 skinned+lit |
| --- | --- | --- | --- | --- |
| base | P11 | P12 | P13 | P14 |
| +4 | P10 | P10 | P13 | P13 |
| +8 | P15 | P16 | P17 | P14 |
| +12 | P10 | P10 | P13 | P13 |
| +16 | P18 | P12 | P13 | P14 |
| +20 | P10 | P10 | P13 | P13 |

So bit 0 = lighting, bit 1 = skinning (from the part's `g & 1`), bit 2 = the
alternate mesh (`Prm.x0 & 1` with a model that has `t2`; kept only for parts
with `g & 2`, whose records hold XYZ-only vertices: P10; the table gives
P13 for `g = 3`, which no data uses and whose 8-qword matrix records would not
match the EE's 5), bit 3 = full clipping (`Prm.x0 & 0x200`), bit 4 = the object's box
is known to be inside the guard band (`Prm.x0 & 0x100`), so the unlit program
P18 drops the `CLIPW` test (there is no lit or skinned variant without it:
P12, P13, P14 are reused). Bits 3 and 4 never appear together (the table has
24 entries; `func_001606d0` tests `0x100` first). *Session 17:* these meanings
come from the callers (§2.3.1) and the program bodies (P18 and P19 are the
only B programs without `CLIPW`, P10 has no culling at all); the savestate's
draw instances (§2.3.1) confirm bits 2 and 4.

If `fl & 8`, the program is `P19` (if `x48 & 0x10`) or `P20` (with `CLIPW`).
*Session 17:* both take the normal 3-qword vertices but ignore the vertex ST
and the material colour: they store 0x80 x 4 into VU qw1 and write
`S = (x - 2048) / 512 + 0.5`, `T = (y - 2048) / 384 + 0.5`, `Q = 1` from the
projected position (qw7 constants, `LOI 0.5`), i.e. **screen-mapped texture
coordinates**: the part shows whatever texture is bound, stretched over the
512x384 screen. Step 2 sends only ZBUF/FRAME for these entries (no texture
upload, no TEST/ALPHA), so the bound texture is the previous draw's or one a
step-3 callback set (not determined statically). Inferred use: a see-through
or refraction-like part effect.

**VU1 memory map** (per draw header: chain `0x00272CF0`, `UNPACK V4-32 9 ->
@0`, patched by `func_0015f798` before sending):

| VU qw | Content |
| --- | --- |
| 0 | GIF tag `NLOOP=1, EOP, NREG=1, REGS=RGBAQ` (P10 kicks it first with `XGKICK vi00`) |
| 1 | material colour RGBA (`D_00272D94` <- `e->x20..x2C`; default 0x80 x 4). Used as the vertex colour by unlit programs |
| 2-5 | lighting: `D_00272DA4` <- 16 words of `e->x10->data` when `e->x48 & 1`. qw2-4 = light colour matrix, qw5 = ambient (inferred) |
| 6 | `.w` = bits ORed into every output XYZF2 w word (`ILW.w vi12, 6(vi00)`, from `e->x3C`): fog F in bits 4-11 (inferred) |
| 7 | `(2048, 2048, 1/512, 1/384)`: screen centre and inverse half-size, for the guard-band tests of P15-P17 |
| 8 | GIF tag template `TRIFAN|IIP|TME|FGE|ABE`, REGS `0x412` = ST, RGBAQ, XYZF2 (`0x303EC000`), for clipped output |
| 12, 34, 56-61 | scratch for the clipper (P15-P17) |
| 0x1E0 / 0x200 past TOPS | output buffer (`vi03 = top + 0x1E0` in P13, `+0x200` in P10; others not checked) |

**Input** (TOPS, `BASE 64 / OFFSET 240` or `BASE 0 / OFFSET 256`) is a
**command stream** of records. *Session 17:* the record rule is settled from
the EE walker `func_0015fd20` (which fills the matrix records each frame) and
the dispatch code of P10-P20, and checked on every mesh in the savestate (12
`MOBJ` + 3 `MENV`, 50 parts, 390 DMA packets, 7,530 records), on
`xa_ex_4030.mdls` and on the three models embedded in the ELF, with zero
misparses (`tools/vu/rb_stream.py`).

A mesh chain is DMA `CNT` packets (the last may be `END`), each `STCYCL 1,1;
UNPACK V4-32 n -> 0 +TOPS; MSCNT`; `n` is the packet's qwc minus 1 (the last
qword holds the `MSCNT`). Every record starts with a qword `{u32 op, u32 arg,
u32 z, u32 w}`:

| op | Meaning | Length |
| --- | --- | --- |
| 0 | load matrix slot `z` (0-2: vf05-08, vf12-15, vf19-22) with bone `arg` (+ the draw's bone base `DObj.x18`); lit programs take the 3 light rows after it (vf09-11...). In skinned programs `w = 1` marks the record as the palette base (`vi06`) and `w >= 2` skips the load | 1 + 4 qwords when the part's `g & 2`, else 1 + 7 (lit or not: unlit draws copy 4 and skip 7) |
| 1 | vertex group: `z` vertices, `w` = winding parity of the first triangle (`vi05`), then a GIF tag (`NLOOP = z`) and the vertices | `arg` bytes |
| 2 | bone index list for the skinned programs: `z` qwords of 4 indexes each, read in order as the influences are processed | `arg` bytes (= 16 * (1 + z)) |
| 0x8000 | end of packet: write the EOP word, `XGKICK`, wait for the next `MSCNT` | `arg` = bytes to the next packet's first record (48: this qword, the `MSCNT` qword and the next DMA tag), 0 = end of mesh |

The VU programs never read `arg`: they step by `z` and the vertex size. The
EE walker uses only `arg`, and spins forever on any other opcode, so there is
no op 8 (session 16's op 8 at `+0x1930` lay past the end of the 239-qword
packet it was read from). Matrix slots stay loaded across packets: most
packets after the first load nothing.

Vertex layouts (qwords per vertex; the first qword's `w` is the matrix slot,
or `>= 0x100` for a palette entry at `vi06 + (w - 0x100) + 1..4`):

- `g & 3 == 0`: 3 qwords: normal (xyz) + slot, position (xyz, w = 1.0), STQ
  floats (S, T, 1.0). GIF tag `TRISTRIP|IIP|TME|FGE|ABE`, REGS `0x412`. Every
  main part table in the savestate uses it.
- `g & 2`: 1 qword: position + slot. GIF tag `TRISTRIP`, `REGS = XYZ2`, the
  untextured strips of the shadow pass (§3.3). The alternate part tables use
  it.
- `g & 1` (skinned, P13/P14/P17; layout read from P13, no such part in the
  savestate or the files at hand): 1 qword whose `w` = influence count `k`,
  then `k` weighted positions (`xyz * weight`, w = weight) whose bones come
  from the op 2 list, then STQ. The program does `ACC = sum(M_bone_i * p_i)`
  (`MULAX`... for the first, `MADDAX`... for the rest), then `MADDI` with
  I = 0 to finish: the "vertices stored per bone" layout.

Colour = VU qw1 (unlit) or the lit colour.

**Lighting** (P12, P14, P16): `n' = Lmat(slot) * n` (3 directional lights,
3x3), `n' = max(n', 0)`, `c = Cmat * n' + ambient` (`MULAX/MADDAY/MADDAZ` by
qw2-4, `MADDW` qw5), clamped to 0..255 with `MINII` and converted with `FTOI0`.
Inferred: this is the sceVu0 NormalLight/LightColor scheme with 3 parallel
lights.

**Culling and clipping**:

- P11-P14: `CLIPW` against a widened w (guard band: `(x - 2048) * ...`). A
  triangle with any vertex outside, or back-facing (`OPMULA` cross product,
  sign from `FMAND 0x20`; the winding alternates along the strip, `vi05 &
  1`), gets ADC set (`vi13 = 0x8000`). There is no geometric clipping, so
  objects that cross the screen edge or the near plane are expected to use
  P15-P17.
- P15-P17: full polygon clipping against the guard-band planes (`1/3072`,
  `1/1024` constants, x and y passes `0x00DD`, `0x018E`). The output is a fan
  using the qw8 template. There are 3 XGKICKs per batch.

**Output** per vertex: `ST(Q)`, `RGBAQ`, `XYZF2` (REGS `0x412`) with the w
word = `vi12 | ADC`, where `vi12` = VU qw6.w. Bits 4-11 of that word are the
fog F, so qw6.w is the per-draw fog value shifted left by 4 (inferred; the
default `0xFF` gives F = 15). A GIF tag comes from the stream (`vf31`, stored
first).

#### 2.3.1 Who sets the program bits (session 17, static unless marked)

`func_001606d0` (via `func_001621e0` or `func_00161de8`) has six callers in
the main ELF. Overlays and the runtime code at `0x00F20000` were not searched.

| Caller | `Prm.x0` | `Prm.x2c` | Objects |
| --- | --- | --- | --- |
| `func_00136428` (from `func_001368e8`, `func_00136768`) | `0x100` when `o->x370` bit 49 is clear and `func_00121000` finds all 8 corners of the box `func_00135a68(o->x410 radius, o->x414 height)` in front (w >= 1) and inside 0..4095 after projection; `0x200` when the spawn record `o->x130->x4 & 4`; never bit 0 | `o->x394` | field actors (inferred from the callers: characters, NPCs, objects) |
| `func_00127960` | `0x101` | 0 | projected shadows (§3.4) |
| `func_00209e18`, `func_0020a518`, `func_0020a758` (`D_003F3530`, initialised by `func_0020a248`) | 0 | 0 | party models drawn in a menu (keys 60001 up) |
| `func_0021af38` (`D_00643020`, `text_00210000_h71.c`) | 0 | 0 | one more menu model (key 60000) |

`o->x394` is a per-actor part mask: `func_00135a10(o, n)` sets bit `n - 1`,
`func_00135a38` clears it. Their only callers are script commands: entries
77/78 of the command table at `0x002E2810` (8-byte `{fn, argc}` records,
reached through the descriptor `D_002E2F20` that `func_0012b738` puts into
the 64 script nodes `D_004F8310`), via `func_00129e08`/`func_00129e28`, and
opcodes 402/403 of the script VM table at `0x003D9FE0` (`func_001d6780`,
`func_001d67c8`, which pop the part number from the VM stack and use the VM's
actor). So P19/P20 appear only when an event or field script asks for them.
The other masks follow the same pattern: `x38c` = parts hidden in the normal
draw (`Prm.x28`), `x390` = parts hidden in the shadow (`func_00127960`).

*Confirmed in the session 17 savestate* (End of the World field, PCSX2, both
frames of the draw-instance array): the three party characters (spawn
classes 0, 1, 2; the models at `0xFE0080`, `0x12E0080`, `0x1520080`) draw
with `x48 = 0x10` (box inside, bit 0 clear: **unlit** in this field), so their parts use
P18; their weapons (the `MENV` second models) also `0x10`; their shadows use
`x48 = 0x14` with the alternate part tables (all parts `g = 2`), so P10, with
ZBUF `0x3A0001C0`/FRAME `0x1_000401D0`; one class-200 object draws with
`x48 = 0` (P11). All four actors have `x394 = 0` and spawn flags without
bit 2 (as do the other spawn records next to them), so no P15-P17 or P19/P20
in that frame.

### 2.4 Other programs

- **P8** (`func_00103c48`, a scheduler task at key `0x280A4`, returns 4): a
  25x25 vertex grid (`-192..+192`, 16-unit steps) whose z comes from a
  sine-table sum, i.e. a waving height field (inferred: an effect or test
  screen). The chain is `CNT` (MPG) -> `NEXT` (4x `UNPACK V4-32 4` = 4
  matrices at VU 0-15, `MSCAL 0`, `BASE 0`, `OFFSET 512`) -> `REFE` to a
  packet built in a heap buffer. Per strip: `UNPACK V4-32 (3n+1) +TOPS`, a GIF
  tag `NLOOP=n, EOP, PRE, PRIM=TRISTRIP|IIP|TME`, REGS `0x412` (ST, RGBAQ,
  XYZF2), n
  positions, n colours (128.0), n STQ, then `MSCNT`. The init block computes
  `M = VU4-7 x VU0-3` into VU 16-19 (VU 8-15 are loaded but the main loop
  does not use them); per vertex it transforms by M, divides by w, `FTOI4`,
  and writes `ST*Q / RGBA / XYZF2`. It is the smallest example of the A
  design, and a good first test for a port.
- **P9**: `LQ 0(vi00)` then `RINIT R`. VU1's random generator is seeded once;
  no rendering program uses `RNEXT`/`RGET`, so a port can ignore it.
- **P21 (VU0)**, called from `func_00162cd0` (`src/hand/vu0.c`, `VCALLMS 0`)
  for every bone in the skeleton build (`func_00163490`,
  `text_00150000_h59.c`: `func_00162cd0(e->x150[i].m[2], e->x150[i].m[3],
  w)`, and `func_00164ba8`). Input vf1 = rotation. *Session 17* (the
  constants are in the savestate's VU0 memory, qw0-17):
  - **Units: radians.** If all three angles are 0 it returns the identity
    (qw0-3). Otherwise, per axis, `t = pi/2 - |a|` (qw5 = pi/2), `cos a =
    sin t` by the odd Taylor series to `t^9` (qw6-9 = -1/6, 1/120, -1/5040,
    1/362880, slightly tuned), `|sin a| = sqrt(1 - cos^2 a)` and the sign of
    `a` from the table qw10-17 (indexed by the sign bits). Valid for |a| <= pi;
    the bone tables in RAM stay inside that (max |a| = pi on Sora's model).
  - **Order: X, then Y, then Z.** It builds `Rx` rows `(1,0,0) (0,cx,sx)
    (0,-sx,cx)`, `Ry` rows `(cy,0,-sy) (0,1,0) (sy,0,cy)`, `Rz` rows
    `(cz,sz,0) (-sz,cz,0) (0,0,1)` and returns the rows of `Rx * Ry * Rz`
    (row-vector product) in vf26-28. In the sceVu0 layout (`v' = m[0] x +
    m[1] y + m[2] z + m[3]`) that is `R = Rz(z) * Ry(y) * Rx(x)` in
    column-vector math, all right-handed: the same as `sceVu0RotMatrix` on an
    identity matrix. `func_00162cd0` stores vf26-28 as rows 0-2 and the
    translation (w = 1.0) as row 3.
  - **Composition** (`func_00163490`): `func_00162c5c(out, A, B)` is `out =
    A * B` (each row of B transformed by A, like `sceVu0MulMatrix`). Per bone
    i with parent p: `L = [R(rot_i) | t_i]` (P21); `G_i = G_p * L` with `G`
    the unscaled chain (`D_00351E10[]`, root `D_00573F10`); the accumulated
    scale `S_i = S_p * s_i` (component-wise, `func_001627d0`); the world
    matrix `W_i` (`x154[i]`) = rows 0-2 of `G_i` scaled by `S_i.x/y/z`
    (`func_00267e90`) and row 3 = `W_p * t_i` (`func_00162848`, the
    parent's *scaled* matrix). So scale is not inherited through rotation
    (no shear), but positions are scaled by the parents.
  Port: a CPU Euler (XYZ, radians) to matrix function plus this composition;
  no VU0 needed.

## 3. GS state

### 3.1 Memory map and display

| GS address | Buffer | Source |
| --- | --- | --- |
| `0x000000` | display buffer, PSMCT24, FBW 512 (or 640), 448 lines | `D_002A6890`/`D_002A6960` (end-of-frame copy target) |
| `0x0E0000` | Z buffer, PSMZ24, 512 x 384 | `ZBUF_1/2 ZBP=0x70` everywhere |
| `0x118000` | 640-wide PSMCT24 buffer (FBP `0x8C`) | drawn by `func_0010b6c0` (`D_002B73E0`), copied to the display by `func_00106000` case 2 (`TEX0 TBP0=0x1180 TBW=640`) |
| `0x1A0000` | **3D render target**, PSMCT32, FBW 512, **512 x 384** | `FRAME_1/2 FBP=0xD0`; renderer B default `FRAME_1 = 0x800D0` |
| `0x360000` (block `0x3600`) | texture slot, rewritten per draw (renderer B PSMT8, UI PSMT4/CT24) | `func_0015f488`, `func_00106460` |
| block `0x3700` | renderer B CLUT (PSMCT32) | `func_0015f488` |
| block `0x3A00`, `0x3FF4`, `0x3FF8` | UI CLUTs | static packets |
| `0x180000` (block `0x1800`) | PSMT8H texture (8-bit indices in the top byte of 32-bit pixels, overlapping the Z area) | `func_00103058`, `func_0010b6c0` |

- Drawing offset: the 512 x 384 target is centred at (2048, 2048),
  `XYOFFSET = (1792, 1856)` (static sprite coordinates `0x7000/0x7400`, and
  `func_00102da8` uses `-256/-192` and `+28664/+29680` in 1/16 units). VU
  programs subtract 2048 for their guard-band tests.
- **End of frame** (`func_00106000`, cases 0/1/3/4): the target is copied to
  the display buffer with 16 vertical 32-pixel `SPRITE|TME|FST` strips,
  source V 0..384 to destination 448 lines (a vertical stretch), with
  bilinear filtering (`TEX1 MMAG=MMIN=1`), +0.5 texel U and RGBAQ =
  `D_002BC070` (0x80 = unity, 0 = black: the global fade). Before the copy,
  if `D_002BC0B0.a != 0`, a full-screen quad of that colour is blended over
  the target additively (`(Cs-0)*As+Cd`, packet `D_002A69D0`); after the copy,
  if `D_002A6B80 != 0`, the same packet draws a `0x80FEFEFE` quad over the
  display buffer (a flash). Case 2 copies to a 512- or
  640-wide buffer (`func_001110d0` picks the width) and sets
  `DISPLAY` through `func_0010fee8` -> `sceGsSetDefDispEnv(PSMCT24, w, 448)`.
- **Video mode**: `func_001101e8` -> `sceGsResetGraph(0, INTERLACE, NTSC,
  FIELD)` (`func_00265350(0, 1, 2, 0)`), so the output is 448 lines,
  interlaced, field mode. `func_0010ffe0` resets with mode 1 and clears
  `EXTWRITE`. `func_00110020` moves `DISPLAY.DX/DY` (screen position
  setting). `func_0010f5f8` writes `PMODE=0xFF03`, `DISPFB1 = 0x360000`
  CT32 512 and a DISPLAY1 128 lines tall: a special display used by the
  screens built in `func_0010f6xx` (inferred: memory-card/system messages);
  src/screen/fade.c's ending does the same.  Since session 57 these writes
  (and `func_0010f658`'s `PMODE = 0x22`, the EXTWRITE clear and the CSR
  field read) go through `PlatGsPutPmode` / `PutDispfb1` / `PutDisplay1` /
  `PutExtwrite` / `PlatGsGetCsr` in include/platform/gs.h: the Vita display
  pass takes its values from them.
  `func_0010fea0` picks `0x14996C4`/`0x112A84E` from a 1.0 frame-rate factor
  (inferred: a VSync timing constant).

### 3.2 Modes in use

Static packets (`gs_packets.py --callers`), renderer B's template
(`func_0015f128`, `func_0015f488`, `func_0015f388`) and the VU GIF tags:

**PRIM**

| Primitive | Where |
| --- | --- |
| `TRISTRIP|IIP|TME` (+`FGE`, `ABE`, `CTXT2` per mesh) | renderer A batches (tag from the mesh), P8 |
| `TRIFAN|IIP|TME|ABE|CTXT2` (+`FGE`) | renderer A clipped polygons (qw48 template) |
| `TRIFAN|IIP|TME|FGE|ABE` | renderer B clipped polygons (qw8 template) |
| `SPRITE|TME|FST` (UV) | frame copy, UI, fonts, post effects |
| `SPRITE` untextured | full-screen fades and flashes |
| `POINT|ABE` | `func_00106460` (destination-alpha mask, see TEST) |

Renderer A's clipped tags use context 2 (`CTXT=1`), so both contexts are live
and a port must track `*_1` and `*_2` registers separately.

**ALPHA** (`(A-B)*C>>7 + D`)

| Equation | Use |
| --- | --- |
| `(Cs-Cd)*As + Cd` | normal alpha blend: most packets, renderer B translucent pass (`0x80_00000044`) |
| `(Cs-0)*As + Cd` | additive (fades/flashes `D_002A6970`, glow) |
| `(0-0)*FIX + Cs`, FIX=0x80 (`0x80_0000002A`) | renderer B default, i.e. no blending |

**TEST**

| Setting | Use |
| --- | --- |
| `ZTE=1 ZTST=GEQUAL` | 3D (renderer B default `0x5080B`); Z grows toward the viewer |
| `ZTST=ALWAYS` | 2D, copies |
| `ATE ATST=GEQUAL AREF=min(k,120)`, ZBUF from the model (`x0->x0`) | renderer B **pass 1** (opaque texels); k = `x0->x2c` |
| `ATE ATST=LESS AREF=k`, same ZBUF with `ZMSK=1` | renderer B **pass 2** (`a->x5` set; translucent texels). Both passes set ALPHA to `(Cs-Cd)*As+Cd` (`func_0015f488`) |
| `ATE ATST=GREATER AREF=0` | cutout sprites (UI) |
| `ATE ATST=NOTEQUAL AREF=0` | `func_00106460` (PSMT4 UI) |
| `ATE ATST=NEVER AFAIL=FB_ONLY` | colour-only writes (masks) |
| `DATE=1 DATM=1` | destination alpha test with `POINT|ABE` (`func_00106460`, `D_002A6AA0`) |

**Frame and Z**: FRAME PSMCT32 (3D) / PSMCT24 (display); `FBMSK=0xFFFFFF`
(alpha-only writes) appears twice. Z is PSMZ24 throughout; `ZMSK` toggles for
translucent passes and 2D.

**Textures**

| Format | Where |
| --- | --- |
| PSMT8 + PSMCT32 CLUT (`CLD=1`, CSM1) | renderer B, uploaded per draw by `func_0015f8c8` (`BITBLTBUF/TRXPOS/TRXREG/TRXDIR` + IMAGE). Default `TEX0_1 = 0x2006E005DD313600` (128x128, `TCC=1`, `TFX=MODULATE`) |
| PSMT4 + CT32 CLUT | UI (`func_00106460`) |
| PSMT8H + CT32 CLUT | block `0x1800`, CLUT `0x3FF4`/`0x3FF8` (`func_00103058`, `func_0010b6c0`) |
| PSMCT24 / PSMCT32 | the render target sampled for post effects and the frame copy (`TBP0=0x1A00`); a 512x512 CT24 image at `0x0E00` (the Z area, `func_0010a120`/`a248`/`a378`) and at `0x3600` (inferred: movie or still frames drawn while 3D is off) |

Filtering is bilinear (`TEX1 MMAG=1 MMIN=1`) with no mipmaps (`MXL=0`) in
every packet seen. `CLAMP` is CLAMP/CLAMP for 2D, and `CLAMP_1 = 5`
(CLAMP, CLAMP) by default in renderer B; per-mesh wrap modes are open
(question 2). `TEXA TA0=128` (for CT24 sources).

**Fog**: per-vertex F from the VU (A: P2/P3/P7; B: from qw6.w bits,
inferred). `FOGCOL` is set per draw from `a->x0->x30/34/38`
(`func_0015f488`) or from the global `D_002BC0F0` (`func_0015f388`).

**Dither, colour clamp, PABE, FBA, SCANMSK**: only `SCANMSK=0` is written
by the static packets (`D_002A65C0`, end of frame). The GS dump (§3.3) shows
`DTHE=0` and `COLCLAMP=1`: no dithering, colours clamp.

### 3.3 Captured GS state (PCSX2 GS dump, session 15)

One `.gs.zst` dump of a fight in Agrabah (game-over screen fading in), read
with `tools/vu/gsdump.py` (never commit dumps or their output). 4 vsyncs,
41,107 vertex kicks under 108 distinct states.

- **Display**: PMODE EN2 only; DISPFB2 FBP 0, FBW 512, PSMCT24; DISPLAY2
  DW=2560 MAGH=5 (512 pixels), DH=447 (448 lines); SMODE2 INT=1 FFMD=0.
  This matches §3.1.
- **Global registers** (answers question 3): `DTHE=0` (dither **off**),
  `COLCLAMP=1` (clamp), `PABE=0`, `PRMODECONT=1`, `SCANMSK=0`. TEXA is
  switched between `TA0=0/TA1=128`, `TA0=128/TA1=0` and `128/128`.
- **The GIF stream is one merged stream.** PCSX2 2.8 records every
  transfer with path byte 3 here, so the dump cannot say which path sent
  what. Uploads are IMAGE tags inside it: 364 in 4 vsyncs (3.2 MB), mostly
  PSMT8 128x128 (120) and 16x16 CT32 CLUTs (180), i.e. the per-draw texture
  slot of §3.1 is real and busy.
- **Empty tags**: 1,216 `NLOOP=0, EOP=1` tags. The `XYZ2`-only strips leave
  one vertex qword past NLOOP, which the GS reads as an empty tag. A port's
  GIF parser has to accept them.
- **Per-mesh state** (answers question 2 for this scene): almost all 3D
  uses `CLAMP_1 = CLAMP/CLAMP`; 72 kicks use `REPEAT/REPEAT`. Context 2
  draws (renderer A's clipped fans and the effects) use `REGION_CLAMP` with
  per-draw MINU/MAXU windows (0..127, 128..255, 176..239, 65..191,
  256..383) and one `REGION_REPEAT` (mask 255): **texture atlases**, so the
  wrap window comes with the mesh. TEX1 is bilinear everywhere except 796
  kicks of point sampling; `LCM=1` with `MXL=0` (no mips) on the 256x256
  draws.
- **Most-used states**:

| Kicks | PRIM | Texture | ALPHA / TEST | Target |
| --- | --- | --- | --- | --- |
| 20.6k | `TRISTRIP|IIP|TME|FGE|ABE` | PSMT8 128x128 at `0x3600`, CLUT `0x3700` | blend; `ATST=GEQUAL AREF=120`, Z GEQUAL (renderer B pass 1) | `0x1A0000` 512x384 CT32, Z24 at `0xE0000` |
| 16.3k | `TRISTRIP` (XYZ2 only, no texture, no colour per vertex) | none | blend; `ATST=GREATER AREF=0` | **`0x3A0000`, FBW 256, CT32, `FBMSK=1`; Z16S at `0x380000`; XYOFFSET 1920; scissor windows 124/192/252 pixels** |
| 4.7k | `TRISTRIP|IIP|TME|FGE|ABE` | same slot | `(0-0)*FIX+Cs` (opaque) | 3D target |
| 387 | same | same | `ATST=LESS AREF=128` | renderer B pass 2 |
| 1.5k | `TRIFAN`/`TRISTRIP ... CTXT2` | atlases (region clamp) | `TEST_2 ATST=GREATER AREF=16` | 3D target |

  The second row is a **256x256 off-screen pass**: flat untextured strips
  drawn into their own colour and 16-bit Z buffer, then read back as the
  `TBP0=0x3A00` CT32 256x256 texture. Session 16 followed it in the code:
  it is the **projected character shadow** (§3.4).

**Field dump (session 16).** A second dump, of End of the World walking in a
plain field (shiftable M12 + `SHIFT_FLOAT=1` build), gives the same picture:
55,021 kicks; map draws are `TRISTRIP|IIP|TME|FGE|ABE` ST/RGBAQ/XYZF2 with
TEX0 TBP `0x3600` PSMT8 128x128, CBP `0x3700` CLD=1, CLAMP, `ATST=GEQUAL
AREF=120`, Z GEQUAL, `COLCLAMP=1`, `DTHE=0`. The shadow pass is still there
with no fight on screen (3,047 untextured XYZ2 strip kicks, `ATST=GREATER
AREF=0`; TEX0 left at `0x3A00`), so it is drawn every frame for every
character near the ground. Uploads: 94 PSMT8 128x128 and 146 CT32 16x16
CLUTs. Display as in §3.1 (DISPFB2 FBW 512 PSMCT24, MAGH 5).

### 3.4 The off-screen buffer at `0x3A0000` (session 16, static)

Three users of the 256 x 256 CT32 area at block `0x3A00` (FBP `0x1D0`), all
render-to-texture:

1. **Projected shadows** (`func_00127c20`, per character within 300 units
   of the ground below it, `func_00128218`). Draw-list keys from 60000 up:
   - `D_004F7820[size]` (built once by `func_001284a0`; 3 window sizes
     `D_002E27E0[0..2]`, chosen by actor `x370` bits 40-41): FRAME_1 and
     FRAME_2 = FBP `0x1D0`, FBW 4 (256), CT32, `FBMSK=1`; ZBUF = ZBP `0x1C0`
     (`0x380000`), PSMZ16S; XYOFFSET (1920, 1920), so (2048, 2048) maps to the
     buffer centre; SCISSOR = a centred w x w window; one untextured SPRITE
     with RGBA 0 clears the window; then `TEST_1/2 = ATE GREATER AREF 0,
     ZTE GEQUAL`.
   - The silhouette: `func_00127b98` builds a light-space matrix
     (`func_00267930` from the light direction) and draws the actor's model
     with colour (0, 0, 0, a), `a = (1 - height/300) * 64 * scale`.
     Characters go through renderer B (`func_00127960` -> `func_001606d0`
     with `Prm.x38` = {ZBUF `0x3A0001C0`, FRAME `0x1_000401D0`}, `Prm.x0 =
     0x101`, so `x48` = 16, + 4 when the model has the alternate part table:
     P18, or P10); props with the bit `x370 >> 39` go through renderer A P5
     (`func_00127b18` -> `func_001149e8`, the prop's +0x20 mesh). Both
     contexts point at the buffer, so either renderer lands there.
   - `D_004F7C10[size]` (`func_00128738`): FRAME_1 = FBP `0x1B0`
     (`0x360000`, the 0x3600 texture slot as CT32 256 wide); the window is
     copied there with a bilinear SPRITE from `TEX0_1 = 0x3A00` (CT32,
     256x256, `TCC=1`), `ALPHA (Cs-Cd)*As+Cd`; then the 3D state is
     restored for both contexts (FRAME `0x800D0`, ZBUF `0x31000070`,
     XYOFFSET `(0x7000, 0x7400)`, SCISSOR 512x384) and context 2 is set up
     to sample the result: `TEX0_2` = `0x3600` CT32 256x256, bilinear,
     `CLAMP_2 = REGION_CLAMP` to the window minus one texel (the per-draw
     MINU/MAXU windows of §3.3), `ALPHA_2 = (Cs-Cd)*As+Cd`, `TEST_2 ATE
     GREATER AREF 0, ZTE GEQUAL`.
   - The receivers: `func_00114f18` collects the collision faces inside the
     shadow volume's box, and `func_00127568` writes them as a renderer A
     batch for **P1** (`func_00114f50` queues the `D_004D9380`/`D_004D9420`
     chain, program table index 2): positions, colour 128.0, STQ as floats
     (the shadow projection of each vertex, `/ size + 0.5`), strip flag in
     STQ.w, GIF tag PRIM `TRISTRIP|IIP|TME|ABE|CTXT2` (`0x312E4000`). Faces
     whose normal has a non-negative dot product with the light direction
     are skipped. So the floor under the
     character is redrawn darkened by the silhouette texture.
   Port: render the silhouette into a 256x256 texture from the light, blur by
   one bilinear copy, and draw it as a projected decal on the ground
   triangles (or use a real shadow map).
2. **Texture crossfade** (`func_00135ed0`, a renderer B step-3 callback set
   by `func_00136428`): after step 2 uploaded the part's texture to `0x3600`,
   it copies it into `0x3A0000` (SPRITE, alpha = the callback argument),
   uploads texture `index + count/2` of the same model to `0x3600`/`0x3700`,
   blends it over the copy with `ALPHA (Cd-Cs)*Ad+Cs`, restores the 3D state
   and sets `TEX0_1 = 0x3A00` CT32, so the part is drawn with a mix of its two
   textures (inferred: facial expression or damage blend).
3. **Eye overlay** (`func_00175600`, step-3 callback for parts with id 3 and
   4): `D_0035C4A0` copies the part's 128x128 texture into `0x3A0000` at
   double size, then `D_0035C550` draws a 64x64 sprite from the model's
   `URSL` image at a position that `func_001752a0` moves each frame toward
   the camera as seen from bone 46 (`x154 + 0xB80`, at most 0.015 per frame),
   restores the 3D state and sets `TEX0_1 = 0x3A00` (256x256 CT32,
   `REGION_CLAMP`). Inferred: pupils that follow the camera.

## 4. Per-frame packet flow

### 4.1 Schedulers

1. **Task list** `D_004E3A48` (`func_0011ef10(key, fn)` ->
   `func_0011f090`): the main loop's per-frame callbacks, run in ascending
   key order. Keys whose callbacks are known to render:
   - `0x9C40` `func_0015eb78`: frame flip of the draw list (4.2);
   - `0x27CB8` `func_0015eea0`: runs the **immediate list**;
   - `0x280A3` `func_001039f8` and `0x280A4` `func_00103c48` (P8);
   - `0x2E630` `func_00160370`: renderer B builds this frame's draw entries
     (`func_0010a058` and `func_00112cf8` also use this key).
   Many other keys (`0xC350`, `0x28489`, `0x2BFxx`, `0x2C04C`...) belong to
   menus and screens; not classified.
2. **Draw list** (`func_0015ed80(key, cb)` -> `func_0011f090` on
   `D_00559DB0`, two pools `D_00551D90[2]` of 512 nodes, 32 bytes each):
   insertion-sorted by key, stable (equal keys keep insertion order). A node
   has an in-use word at +0, `next` at +8, the callback at +0xC and the
   payload from +0x10 (`func_0015ea98`); the key is also stored. The callback
   returns flags: `0x20` = "not finished, call me again", `2` = "a DMA is
   running, wait for its interrupt".
3. **Immediate list** (`func_0015ee78(key, cb)` on `D_0055BDE0`, pools
   `D_00559DC0[2]`, 128 nodes): run synchronously by `func_0015eea0` in the
   same frame, with `sceGsSyncPath(0,0)` between nodes. Renderer B puts
   entries flagged `e->x4 & 8` or `x48 & 0x20000` here, plus a state reset at
   key `0x7FFFFFFF`.

### 4.2 Frame N+1 drawing frame N

- `func_0015eb78` (task `0x9C40`): `FlushCache`. It hands the list just built
  (`D_00559DB0->x8`) to the executor (`D_00551D80`) and flips
  `D_00351BD0 ^= 1` (**frame parity**: every double-buffered chain picks its
  half with it). It waits until `sceGsSyncPath(1,0)` reports the paths idle,
  disables DMAC interrupts 1 and 2, clears `D_STAT` CIS1/CIS2, and calls
  `func_0015ea98`.
- `func_0015ea98` walks the list: for each node it calls `cb(node)`. If the
  callback returned without `0x20` the node is released and the walk moves on;
  if it returned `2`, the walk returns 1 and DMAC interrupts are re-enabled.
- `func_0015eda8` installed `func_0015efc0` as the DMAC handler for
  channels 1 (VIF1) and 2 (GIF). Each DMA end calls `func_0015ea98` again
  (with `iFlushCache` swapped into the flush hook `D_00351BC8`), so the list
  is consumed one DMA at a time, interrupt to interrupt.
- So the GS sees exactly the list order. **Painter's order is the key**:
  3D draws, alpha passes and UI interleave by key, and a port must replay the
  list in the same order (it can batch consecutive nodes with the same state).

### 4.3 Callbacks that build or send DMA

| Callback | Channel | What it sends |
| --- | --- | --- |
| `func_00106db0` (queued by `func_00107d30`, `func_001085e8`) | VIF1, direct `D1_*` writes, `CHCR=0x105` | renderer A chain at `node->x10`; chains `D_0046E120`/`D_00472160` (case 1), `D_004761A0`/`D_0047A1E0` (case 0), `D_0047E220`/`D_00482260` (case 3), picked by parity |
| `func_00108d90` (`func_00108f18`, `func_00108fd0`, `text_00110000_h29.c`) | VIF1, `CHCR=0x145` (TTE) | renderer A per-object chain `D_00494D80[i].e[parity]`, `D_002AA060[i].e[parity]`, `D_004D9380`/`D_004D9420` |
| `func_00127500` | VIF1 via `sceDmaSend` | a heap chain built by the code around `text_00110000_s6_04.c:295` (224 bytes per item), freed after the send |
| `func_00103c48` | VIF1 direct | P8 grid chain (heap) |
| `func_0015ff78` (renderer B, one node per draw entry) | VIF1 + GIF | state machine, below |
| `func_0015f388` | GIF | renderer B default GS state (TEST, ALPHA, FOGCOL, ZBUF, FRAME, CLAMP), at keys `0x5013`, `0x11363` (draw list) and `0x7FFFFFFF`, `0` (immediate list) |
| `func_00106b18(tag)` | GIF, synchronous (`FlushCache`, `sceGsSyncPath`, `sceDmaSend(ch2)`) | every static 2D packet (`gs_packets.py --callers`: 35 call sites) |
| about 160 direct `sceDmaGetChan(2)` + `sceDmaSend` sites (168 `jal 0x266c08` in all, two with channel 1, one with 0) | GIF | UI, menus, fonts (`text_001f0000_h69.c`, `text_00200000_s11_w50.c`, `0x001B3870`-`0x001B99B8` write `D2_*` directly) |

**Renderer B per draw** (`func_0015ff78`, `text_00140000_b04.c`; `node->x14`
is the step):

0. `func_0015f798`: patch the header chain `0x00272CF0` (colour, light block,
   qw6.w) and send it on VIF1 (`UNPACK 9 -> VU 0`).
1. `func_0015fc00`: send the selected program (`MPG; MSCAL 0; BASE; OFFSET`).
   If `x48 & 4`, fill the matrix records (`func_0015fd20`) and skip to step
   4: no GS state and no texture are sent, so the alternate (shadow) mesh
   draws with whatever state its caller set up (§3.4).
2. GS state on GIF:
   - entries flagged `x4 & 8`: a small A+D packet `D_00351C40` with two
     values from the draw instance, `s->x0->x0`/`x8` = ZBUF_1 and FRAME_1
     (session 16: they are the caller's `Prm.x38`/`x40`, copied by
     `func_001606d0`; the shadow pass passes the `0x3A0000` buffer here);
   - otherwise `func_0015f488` + `func_0015f8c8` build `D_00573AC0`: CLUT
     upload (BITBLTBUF to block `0x3700`, CT32 16x16), texture upload (PSMT8
     to block `0x3600`, size from the image header, `REF` into the model's
     pixel data), then `D_00573E40` = `TEXFLUSH, TEX0_1, TEX1_1, TEST_1,
     ALPHA_1, ZBUF_1, FOGCOL, FRAME_1, CLAMP_1` (template in
     `func_0015f128`). `a->x5` selects the translucent pass values (3.2).
3. Optional model callback `s->x0->x40(&D_0055C680, ...)` with a description
   of the texture slot (block `0x3600`/`0x3700`, size, format 19 = PSMT8,
   part id, texture index). The two callbacks render into `0x3A0000` and
   point `TEX0_1` at it (§3.4).
4. Send the mesh chain `table[byte7].x18` on VIF1 (TTE on).
5. Busy-wait until VIF1 is idle (`VIF1_STAT & 0x1F000003 == 0`) and VU1 is
   stopped (`VPU_STAT` bit 8 via `cfc2 vi29`), then finish.

`func_00160370` (task `0x2E630`) builds these entries every frame: objects are
sorted by `x10->x0->x3C` (depth), the sort index is added to the entry key
`e->x28` (clamped to +-500 around its base), and each entry is inserted with
`func_0015ed80` (or `func_0015ee78`). It also frees the previous frame's
temporary packets.

## 5. Mapping to a modern API

For a Vulkan/GL-class backend (the Vita's GXM has the same concepts).

**Overall approach.** Do not emulate VIF/VU. Decode the model data on the CPU
once at load into vertex and index buffers, and replace each microprogram with
a small vertex shader. The draw list stays: each node becomes a recorded
command (bind pipeline, set uniforms, draw) and is replayed in key order. The
interrupt-driven executor becomes a plain loop.

| PS2 | Port |
| --- | --- |
| Draw list, key order | sorted command list; same order, no reordering across nodes with blending |
| Frame parity `D_00351BD0`, double-buffered chains | per-frame uniform ring (2-3 frames in flight) |
| VU1 qw 0-15 (A) | uniform block: `model`, `params`, `viewProj`, `screen`; drop `screen` and use the API viewport |
| VU1 qw 16-39 (A) | uniforms: UV scroll table, point light, env matrix |
| A strip flag (vertex w) | index buffer: emit triangles only where the flag is non-zero; restart where it is 0; winding from the sign |
| A/B backface cull via cross product and ADC | API culling with the per-strip winding baked into the index order, or no culling plus a `gl_FrontFacing` discard where the sign was data-driven |
| VU clipping (A all, B 15-17), guard band | hardware clipping; remove |
| `FTOI4` + `XYOFFSET` + 512x384 target | render at any resolution; keep a 4:3 projection matching `D_002BBF60` (VU qw 12-15) |
| ST 1.12 with Q | `vec2 uv = st / 4096.0`, perspective-correct by default |
| RGBA 0x80 = 1.0, `TFX=MODULATE` | `out = tex * vcol * 2.0` (clamp); alpha the same (`TCC=1`) |
| Fog F = clamp(A + B/w) | per-vertex fog factor `f = F/255`, `mix(fogColor, color, f)` in the fragment shader |
| Renderer B matrix slots and palette | bone matrix UBO/SSBO; skinning in the vertex shader with weights pre-split from the per-bone weighted positions (`p_i = xyz_i / w_i`, weight `w_i`) |
| B lighting (3 parallel lights + ambient, clamp 255) | vertex-shader lighting with the same clamps (saturate before scaling) |
| P21 (VU0 Euler -> matrix) | CPU function: `Rz * Ry * Rx`, radians, composition as in §2.4 |
| PSMT4/8 + CLUT | decode to RGBA8 at load (or use a palette texture + shader lookup if CLUT animation is used: renderer B callback step 3, open question 6) |
| per-draw texture upload to block `0x3600` | cache decoded textures by source pointer and CLUT |
| `ALPHA (Cs-Cd)*As+Cd` | `SRC_ALPHA, ONE_MINUS_SRC_ALPHA` with As scaled ×2 (0x80 = 1.0) |
| `ALPHA (Cs-0)*As+Cd` | `SRC_ALPHA, ONE` (additive) |
| `(0-0)*FIX+Cs` | blending off |
| `TEST ATST GEQUAL/LESS AREF=k` two-pass | two draws with `discard` in the shader (`a >= k/128` and `a < k/128`), the second with depth writes off and blending on |
| `ATST NEVER, AFAIL=FB_ONLY` | colour write on, depth write off, no discard |
| `DATE/DATM` destination alpha | stencil: write a bit where dest alpha is set, test it |
| `ZTST GEQUAL`, PSMZ24 | depth test `GREATER_OR_EQUAL` on reversed Z, or flip the projection and use `LESS_OR_EQUAL` |
| `FBMSK=0xFFFFFF` | colour write mask (alpha only) |
| CTXT1/CTXT2 | no equivalent: they are two state sets; fold into the pipeline state |
| End-of-frame copy 384 -> 448, fade `D_002BC070`, flashes | final full-screen pass: scale to the window, multiply by the fade colour, add the flash quads |
| Interlace/field mode, DISPLAY offsets | ignore; present progressive frames |
| `sceGsSyncPath` busy-waits | remove (single-threaded command replay) |

## 6. Open questions

1. **Model data formats.** The mesh VIF streams (UNPACK formats, STCYCL
   patterns, the renderer B opcode set) live in the model files on the disc,
   not in the ELF. Next step: dump one renderer A and one renderer B mesh chain
   from a PCSX2 run (GS/VIF dump or a breakpoint on `func_00108d90` and
   `func_0015ff78` step 4) and walk it with `vif_chain.py` logic; then
   document the file headers (`+0x80..0x9C` relocated tags) in
   docs/structs.md.
   *Session 16:* the file headers and names are in docs/structs.md ("Model
   files"): map meshes come from `<ww>00_<nn>.bin` (8 bbox corners + the two
   tags at +0x80/+0x90), characters from `*.mdls` chunk chains (`MOBJ`
   header, texture records, part table, per-part mesh chain).
   `tools/vu/model_header.py` parses them. The renderer B chain was checked
   on a model embedded in the ELF: one `CNT` with `STCYCL 1,1; UNPACK V4-32
   -> 0 +TOPS`, a command stream of `{op, arg}` records (0 = matrix slot for
   bone `arg`, filled by `func_0015fd20`; 1/2 = vertex group with byte
   length; 0x8000 = end). Still open: the renderer A strip stream behind the
   +0x90 tag, and checking the derived file names against KINGDOM.IDX.
   *Session 17:* the renderer B record rule is settled (§2.3 "Input"): op 0
   is 5 or 8 qwords by the part's `g & 2`, ops 1/2 are `arg` bytes, 0x8000
   carries the byte step to the next packet (48) or 0 at the end of the
   mesh, and no other opcode exists. `tools/vu/rb_stream.py` walks every
   mesh in a RAM dump, a `.mdls` or the ELF with zero misparses. Still open
   for B: a skinned (`g & 1`) part to check the P13 layout on real data.
2. ~~Per-mesh GS state~~ Partly answered by §3.3: CLAMP/CLAMP for most
   meshes, REGION_CLAMP atlas windows for context-2 draws. Still open: where
   in the model file those values live.
3. ~~DTHE and COLCLAMP~~ Answered (§3.3): dither off, colour clamp on.
4. P19/P20 (`fl & 8`) and P10 (`v` bit 2): which game objects use them
   (shadows? effects? §3.3's 256x256 off-screen pass is the likely
   consumer). Breakpoint on `func_0015fc00` and log `fl`/`x48`.
   *Session 16:* `fl & 8` is the entry's bit for parts whose id is set in
   the caller's mask `Prm.x2c` (`func_001606d0`); the shadow silhouettes
   use `Prm.x0 = 0x101`, i.e. `x48` = 16 (+4 with the alternate part
   table): P18 or P10, not P19/P20 (§3.4). Which callers set `Prm.x2c`
   is still open; the dump's `ATST GREATER AREF 0` for the silhouettes
   does not match step 2's `ATST GEQUAL AREF=x2c`, so a run should confirm
   which path they take.
   *Session 17:* mostly answered (§2.3.1). P10 is the alternate mesh
   (`g & 2`, XYZ-only strips) drawn by the shadow pass; confirmed in the
   savestate (shadow draw instances `x48 = 0x14`, alternate tables all
   `g = 2`). The `AREF` mismatch is explained by step 1: entries with
   `x48 & 4` skip step 2 entirely, so the silhouettes keep the shadow
   buffer state of `D_004F7820` (`ATST GREATER AREF 0`). `Prm.x0 & 0x100` =
   the actor's box projects inside the guard band (`func_00121000`), `0x200`
   = spawn flag `o->x130->x4 & 4` (static only: no actor in the savestate
   has it). `Prm.x2c` = actor `x394`, set only by two script commands
   (table `0x002E2810` entries 77/78, VM opcodes 402/403), so P19/P20
   (screen-mapped texture, §2.3) are script-driven; which scripts use them,
   and which texture is bound when they draw, is still open (needs the
   script files or a run that triggers them). Overlays were not searched.
   *Session 19:* a RAM dump during an Agrabah fight (Pot Spiders and
   bandits, float build F19A) shows only P10, P11 and P18 drawn. There are
   no P19/P20, no P15-P17, no lit programs and still no skinned (`g & 1`)
   part, even with enemies on screen. The x48 = 20 (0x14) entries with
   `g = 0` drop bit 2 and run as P18. So a normal fight does not trigger
   the script-driven `Prm.x2c` path; a cutscene or a boss is the next
   place to look.
5. ~~P21's rotation order and angle units, and how `func_00162c5c` composes
   the parent matrix.~~ *Session 17:* answered (§2.4): radians, `R = Rz *
   Ry * Rx` (X applied first), `func_00162c5c(out, A, B)` = `A * B`, world =
   parent's unscaled chain times the local matrix, then rows scaled by the
   accumulated scale and the position taken through the parent's scaled
   matrix. Static, with the VU0 constants read from the savestate; not yet
   checked numerically against a posed skeleton in RAM.
6. ~~What renderer B's step-3 callback (`s->x0->x40`) does~~ Answered
   (§3.4): render-to-texture into `0x3A0000`, then `TEX0_1 = 0x3A00`.
   Two callbacks, both chosen in `func_00136428`: `func_00135ed0` (blend
   texture i with texture i + count/2) and `func_00175600` (eye sprites
   from the `URSL` chunk on parts 3 and 4).
7. ~~P1's input and which chain uses it~~ Answered (§3.4): the shadow
   receivers (`func_00114c18(.., 2)` chains, batches from
   `func_00127568`: float xyz + 1.0, colour 128.0 x 4, STQ floats with the
   strip flag in STQ.w as `+-1.0` with the low bits `0x20`). Map meshes use
   P4 (`func_00108cf8(.., 4)`), area props P2 and prop silhouettes P5
   (`func_001148c8`).
8. The `REFE` chains at `D_0046E120`..`D_00482260` (renderer A, cases 0/1/3
   of `func_00107d30`): what they draw (sky? the "far" layer?). Static
   walk with `vif_chain.py` once their placeholders are understood.
   *Session 16:* the case 0/1 chains (`+0x20` of each) are patched by
   `func_00106ed0` from section 1 of the map `.bin` (its tag table and
   per-texture records), so they carry per-map data (inferred: texture
   state for the map meshes). Case 3 not traced.
9. VSync and frame pacing: the constants in `func_0010fea0`, the 30/60 fps
   switch (`D_002BBDEC`), and where the main loop waits for the vertical
   blank.
10. `0x118000` display area and the special `PMODE/DISPFB1` setup of
    `func_0010f5f8`: which screens use them.
11. The runtime-loaded code at `0x00F20000` (docs/elf-notes.md) may draw;
    it is not covered here.
