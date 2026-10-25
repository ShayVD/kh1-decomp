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
| `python3 -I tools/host/dmawalk.py [--regs [-v]] [--float ELF]` | every DMA send whose chain is a name (PlatDmaSend's static rows and dmapool's GIF wrappers): the chain walked, its data read as GIF packets / VIF codes (VIF1 DIRECT data as GIF packets, PATH2), the GS registers each send writes (`-v`: decoded), and with `--float` whether the m12 float build sends the same chain (§4.6). New in session 76. `--state` (session 77): the state list instead, each register's distinct values decoded with the functions that send each (§4.7). Session 78: `SEEDS` writes the 17 chains init code builds from constants over the ELF's bytes first (68 more sends walked; `--no-seeds` turns it off, §4.8) |
| `KH1_HOST_TRACE=4 out/host/kh1-host > run.txt`, then `python3 -I tools/host/gsstate.py run.txt [--sends]` | the same state list for the chains a host run sends (the run-time ones too: the text windows, the HUD), each named by the host symbol at its start (§4.7). New in session 77 |
| `KH1_HOST_TRACE=5 out/host/kh1-host > run.txt`, then `python3 -I tools/host/gsstate.py run.txt --draws` | the draw states the host's GS register file (host/null/gsregs.c) counted: each distinct PRIM + context state the vertex kicks drew with, decoded, with kicks, primitives and the chains that kicked them (§4.9, §5.1). New in session 79 |
| `KH1_HOST_TRACE=5 out/host/kh1-host > run.txt`, then `python3 -I tools/host/gsstate.py run.txt --uploads` | the transfers into the host's GS memory model (host/null/gsmem.c): each destination DBP / DBW / PSM and rectangle, how often, the pixels and the chains that sent them (§5.2). New in session 80 |
| `KH1_HOST_TRACE=5 out/host/kh1-host > run.txt`, then `python3 -I tools/host/gsstate.py run.txt --targets [--draws]` | the render targets the host's GS memory model saw drawn into (each FRAME / ZBUF, its extent, bits and primitives) and, with `--draws`, which draw states read a target as a texture (§5.2). New in session 81 |
| `KH1_HOST_TRACE=5 out/host/kh1-host > run.txt`, then `python3 -I tools/host/gsstate.py run.txt --nodes [--frame N]` | the draw / immediate list nodes as the walks ran them (`PlatGsListNode`): one frame's command order (nodes and the main-thread sends between them) with each node's callback, payload, sends, kicks and uploads, then every distinct node checked against `drawkeys.py`'s key map (§4.12). New in session 83 |
| `python3 -I tools/host/sendorder.py [--all]` | the main loop's tasks that send to the GS, with their key and first sync or send, against the draw list's start (`0x9C40`) and the immediate list's wait (`0x27CB8`): reads only src/ (§4.12). New in session 81 |
| `python3 -I tools/host/giftags.py src/text/*.c` | the GIF tags (with PRE) the C writes as constants, by function: the shape of packets built per draw, which no static walk sees (§4.9). New in session 79 |
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
| 8-11 | `D_002BC020` | world -> clip (renderer A's guard box, 1636 x 303 GS pixels about the centre, not the 4:3 screen; session 90, §5.4: `CLIPW` against w) |
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
  sine-table sum: the event script's lens bulge over a copy of the frame
  (session 88, §4.17). The chain is `CNT` (MPG) -> `NEXT` (4x `UNPACK V4-32 4` = 4
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
| `0x360000` (block `0x3600`) | texture slot, rewritten per draw (renderer B PSMT8, UI PSMT4/CT24); also the texture animations' frame A (§4.13) | `func_0015f488`, `func_00106460`, `D_002A4230` |
| blocks `0x3E00` + i | **the room's CLUTs** (CT32): 16-colour 8x2 ones at `0x3E00 + i` (i < n0), 256-colour 16x16 ones at every 4th block from n0 to n1, from the room's background file; the texture animations cross-fade some of them in place (§4.13) | roombg.c `func_00101048` (session 83) |
| blocks `0x2600` + 256 i | the room's background textures: PSMT8 256x256 (BW 4) or PSMT4 512x256 (BW 8) by the file's kind byte (19 / 20), up to 16; and a PSMT8H 256x1024 at block 0 (BW 4: the top byte of the words from block 0, the display buffer's area) | roombg.c `func_00100e80` / `func_00100e08` / `func_00100ef8` (session 83) |
| block `0x3700` | renderer B CLUT (PSMCT32) | `func_0015f488` |
| block `0x3A00`, `0x3FF4`, `0x3FF8` | UI CLUTs | static packets |
| block `0x1000` (`0x100000`) | **the message font, in the Z buffer's top byte**: two 256x256 4-bit halves uploaded as PSMT4HH and PSMT4HL (`func_001ef950`, CLUT block `0x3FFC`); text.c's draws read the PSMT4HL half (`D_003F2270`) | session 78 (§4.8) |
| block `0x3D7C`, CLUT `0x3DFC` | the window font, PSMT4 256x256 from the ELF (`D_003E9660`, CLUT `D_003F1660`), uploaded by `D_003F2670` / `D_003F2720` | session 78 (§4.8) |
| blocks `0x3600`-`0x3700` | also the menus' images: menubg (PSMT8 104x56 + CLUT `0x3640`), config (PSMT8 138x88 + CLUT `0x3680`), journal (PSMT8 256x256 + CLUT `0x3700`; 64x64 + `0x3680`) | session 78 (§4.8) |
| `0x180000` (block `0x1800`) | PSMT8H texture (8-bit indices in the top byte of 32-bit pixels, overlapping the Z area) | `func_0010b6c0`, `func_0010f0d0` (session 88: not `func_00103058`, §4.17) |

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
| `SPRITE` untextured | full-screen fades and flashes; `func_00106460`'s destination-alpha mask (see TEST) |
| `SPRITE|ABE` / `SPRITE|ABE|FST` untextured | the additive fade quad (`func_00106000`), `func_001039f8` |
| `TRISTRIP|IIP` untextured | src/screen/fade.c `func_001137f8` (`D_002BD100`, 18 strips: a gouraud wipe) |
| `TRISTRIP|TME|ABE|FST` | sceneeff `func_00102da8` (a textured 2D strip) |
| `LINE|IIP|ABE` | the wave transition (src/screen/wave.c `D_00631620`): 100 horizontal gouraud lines, one per row, shifted by a sine (session 78) |

Session 77 (`dmawalk.py --state`): the `POINT|ABE` this table listed for `func_00106460` is not
there; `D_002A6AA0` is an untextured `SPRITE` (one RGBAQ, two XYZ2) under `DATE=1 DATM=1`. The
one `POINT` (PRIM 0) in a run is opdma's `D_0061E8B0` (`func_001aa008`): **three** of its five A+D
qwords (the 2nd, 4th and 5th; session 77 said two) are left zero, so they write PRIM 0 with no vertex
after them, a state write and no draw (a port's GIF parser must take A+D to address 0 with value 0
as harmless). `D_0061E800` is the same packet with `ZMSK=1` (§4.8).

Renderer A's clipped tags use context 2 (`CTXT=1`), so both contexts are live
and a port must track `*_1` and `*_2` registers separately.

**ALPHA** (`(A-B)*C>>7 + D`)

| Equation | Use |
| --- | --- |
| `(Cs-Cd)*As + Cd` | normal alpha blend: most packets, renderer B translucent pass (`0x80_00000044`) |
| `(Cs-0)*As + Cd` | additive (fades/flashes `D_002A6970`, glow) |
| `(0-0)*FIX + Cs`, FIX=0x80 (`0x80_0000002A`) | renderer B default, i.e. no blending (seen at run time, `D_00573AC0`) |
| `(Cd-Cs)*As + 0` | `func_00106000` (end of frame), one pass: a subtractive darken |
| `(Cs-0)*As + Cd`, FIX=0x80 (`0x80_00000048`) | the HUD's numbers: counter, dmgnum, lblnum override the default environment's ALPHA_1 with it (§4.7) |

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
| `ATE ATST=NEVER AFAIL=ZB_ONLY ZTST=GREATER` | opdma `func_001aaf00` (`D_00373030`): **Z-only writes**, where the new Z is nearer (session 77) |
| `ATE ATST=GREATER AREF=0 ZTST=GREATER` | opdma's set-up packets `D_0061E800` / `D_0061E8B0` (run time; §4.8) |
| `ATE ATST=GREATER AREF=0`, **`ZTE=0`** (`0x4000D`) | the text windows' and text.c's headers (`D_003F1A70`, `D_003F1E70`, `D_003F2270`) and the wave: no depth test (a port reads `ZTE=0` as `ZTST=ALWAYS`); windows with flag `0x10` then send `D_003F27D0`, the same with `ZTE=1 ZTST=GEQUAL` (session 78) |
| `ATE ATST=GEQUAL AREF=120 ZTST=ALWAYS`, then `ZTST=GEQUAL` | texspot `func_00175600`: the 256x256 pass into `0x3A0000`, then its composite (§4.8) |
| `ATE ATST=GREATER AREF=0 ZTST=GEQUAL` | sceneeff `func_00103058`, `func_0010ff60`; `TEST_2` in field.c `func_00100988`, display.c `func_00110ce0` |
| `TEST_2 ATST=GREATER AREF=16` / `AREF=127` | field.c `func_00100988` / roommdl `func_00114a38` |
| `ATE ATST=ALWAYS ZTST=ALWAYS` (`0x30003`) | the HUD: every caller of the default environment `func_002370c8` overrides its `TEST_1` with it (§4.7) |
| `DATE=1 DATM=1` | destination alpha test with `POINT|ABE` (`func_00106460`, `D_002A6AA0`) |

**Frame and Z**: FRAME PSMCT32 (3D) / PSMCT24 (display); `FBMSK=0xFFFFFF`
(alpha-only writes) appears three times (sceneeff `func_00103058`, brightfade `func_00106460`,
`func_0010f5a8`). Z is PSMZ24 throughout; `ZMSK` toggles for translucent passes and 2D.
Other targets the static chains set (session 77): FBP `0x1F0` (`0x3E0000`), FBW 64, CT32,
`FBMSK=0xFF000000` (colour only, alpha kept; texanim `func_00102118`, an 8x2 / 16x16 texture
area); FBP `0x70` CT24 (**the Z buffer's memory drawn as colour**, sceneeff `func_00103c48`
`D_002A5FD0`, with `ZBUF ZBP=0 ZMSK=1` meanwhile: a copy of the target into the Z area, read back
as `TEX0 TBP0=0xE00`); FBP `0x1B0` FBW 256 (pause / capture `func_0010a3e8`: the `0x3600` slot as
a 256-wide target); FBP `0x8C` FBW 640 (§3.1).

**Textures**

| Format | Where |
| --- | --- |
| PSMT8 + PSMCT32 CLUT (`CLD=1`, CSM1) | renderer B, uploaded per draw by `func_0015f8c8` (`BITBLTBUF/TRXPOS/TRXREG/TRXDIR` + IMAGE). Default `TEX0_1 = 0x2006E005DD313600` (128x128, `TCC=1`, `TFX=MODULATE`) |
| PSMT4 + CT32 CLUT | UI (`func_00106460`) |
| PSMT8H + CT32 CLUT | block `0x1800`, CLUT `0x3FF4`/`0x3FF8` (`func_0010b6c0`, `func_0010f0d0`; session 88: not `func_00103058`) |
| PSMCT24 / PSMCT32 | the render target sampled for post effects and the frame copy (`TBP0=0x1A00`); a 512x512 CT24 image at `0x0E00` (the Z area, `func_0010a120`/`a248`/`a378`) and at `0x3600` (inferred: movie or still frames drawn while 3D is off) |

Filtering is bilinear (`TEX1 MMAG=1 MMIN=1`) with no mipmaps (`MXL=0`) in
most packets; **point sampling** (`MMAG=MMIN=0`) in texanim `func_00102118`, brightfade's
`func_00105f28` and capture `func_00109e20` (session 77). `CLAMP` is CLAMP/CLAMP for 2D, and
`CLAMP_1 = 5` (CLAMP, CLAMP) by default in renderer B; one static `REGION_CLAMP` (U 0..510,
sceneeff `func_00103c48`); per-mesh wrap modes come with the mesh (§3.3). `TEXA TA0=128 TA1=0`
in the static packets (for CT24 sources), `TA0=TA1=128` in the HUD's environment. Most CT24
sources load with `CLD=4` (the CLUT loads only when CBP changes; no CLUT is used).

**Fog**: per-vertex F from the VU (A: P2/P3/P7; B: from qw6.w bits,
inferred). `FOGCOL` is set per draw from `a->x0->x30/34/38`
(`func_0015f488`) or from the global `D_002BC0F0` (`func_0015f388`).

**Dither, colour clamp, PABE, FBA, SCANMSK**: only `SCANMSK=0` is written
by the static packets (`D_002A65C0`, end of frame). The GS dump (§3.3) shows
`DTHE=0` and `COLCLAMP=1`: no dithering, colours clamp. The C agrees (session 77): the HUD's
default environment `func_002370c8` writes `DTHE=0`, `COLCLAMP=1`, `PABE=0`, `FBA_1=0`,
`PRMODECONT=1`, `DIMX=-4` (inert with DTHE 0) every time a HUD element draws (§4.7).

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

### 4.4 The channel's CHCR and the chain walk (sessions 73-74, static)

- **Word 0 of a channel is its CHCR.** `sceDmaGetChan(n)` returns the
  channel's register block (`sceDmaChan`: CHCR +0x00, MADR +0x10, QWC +0x20,
  TADR +0x30); the port's `PlatDmaChan` keeps the same words, and the game
  writes the first one itself. `sceDmaSend` (func_00266f38) sets
  `TADR = tag`, `QWC = 0` and `CHCR = (CHCR & ~0xC) | 0x105`: source chain
  mode, from memory, start. It keeps every other bit the game left there, so
  **TTE (0x40) is whatever the last writer of word 0 set**.
- **Who sets what.** drawlist's func_00237f20 / func_002380c0 set TTE on the
  GIF channel (`*chan |= 0x40`) and nothing clears it again, so once drawlist
  has run, every later GIF `sceDmaSend` on the PS2 also transfers its tags'
  upper 64 bits. A port must take TTE from word 0 at each send, not from the
  call site, and on the GIF channel then drop the tag anyway (4.5). shadow's func_00127500 sets chain mode and
  clears TTE on VIF1 before its send (the 224-byte heap chain, 4.3). The
  direct VIF1 senders write `D1_CHCR` themselves: func_00106db0 `0x105` (no
  TTE), func_00108d90 `0x145` (TTE: the tag's upper words are VIF codes).
- **drawlist's end tag** is ORed onto the qword after the last packet
  (`*r |= 0x70000000`): its qwc bits are whatever was in that qword, sent as
  data on the PS2 too. A walker reads END's qwc as the tag says.
- **The walk** (what the Vita's PlatDmaSend does, and what the host's null
  platform does under `KH1_HOST_TRACE=2`, host/null/plat_null.c): from TADR,
  tag by tag; id 0 refe (the data at ADDR, then stop), 1 cnt (the data after
  the tag, then the tag after it), 2 next (the data after the tag, then the
  tag at ADDR), 3 ref / 4 refs (the data at ADDR, then the next qword), 5 call
  (push the qword after the data, two deep), 6 ret (pop; an empty stack
  stops), 7 end (the data after the tag, then stop). With TTE the tag's
  upper 64 bits go first. An address with bit 31 set reads the scratchpad on
  the PS2 (dma.h PLAT_DMA_SPR, 0 off the EE: the port's addresses are plain
  pointers).
- **Host result** (session 74, fake disc, `KH1_HOST_OVL=stub:2`): 86 sends,
  84 on the GIF channel and one each on VIF0 / VIF1 (func_0015f018, session 75),
  1-3 tags each (cnt / ref / end and lone refe / end), none leaving host
  memory, valgrind 0 errors.

### 4.5 The tags' upper words and the receiver's read (session 75, static)

- **What the GIF tags' upper 64 bits hold.** The builders clear the qword
  before writing the low word (`*p = KH1_Q(0)`: func_00237018, drawlist's
  packets), and the static chains hold 0 there: upper words 0. The exception
  is func_0011fbb0's image upload on its caller's stack (text.c): the tags are
  written as 64-bit words and the upper half is stack garbage.
- **TTE on the GIF channel.** Nothing in the main ELF calls drawlist's
  flushes, so on the main ELF alone the GIF channel's TTE stays clear (every
  send seen: CHCR 0 or 4). If an overlay calls them, the tag can not reach
  the GIF: read as a GIFtag, `0x1000000N` is NLOOP N, NREG 16 (0), PACKED
  PRIM, and would swallow 16 x N qwords of a packet that starts with its own
  EOP GIFtag. **The GIF parser drops every tag on channel 2, TTE or not**
  (inference; a PCSX2 GS dump settles it if an overlay runs drawlist).
- **VIF tags with TTE.** The upper words are VIF codes and come first:
  func_0015f018's static VIF0 / VIF1 chains (D_00278680, D_00272C70) start
  `FLUSHE` / `FLUSHA`, `STCYCL 4,4` in the tag, then one UNPACK each.
- **The receiver's read** (what the Vita's PlatDmaSend feeds its GIF parser;
  host/null/dmawalk.c under `KH1_HOST_TRACE=2`): the data of every tag in
  chain order is **one stream**. GIF: a GIFtag (NLOOP bits 0-14, EOP 15, FLG
  58-59, NREG 60-63 with 0 = 16), then NLOOP x NREG qwords PACKED,
  (NLOOP x NREG + 1) / 2 REGLIST, NLOOP IMAGE; a packet can run on into the
  next tag's data (an IMAGE GIFtag in a cnt, its pixels by ref). VIF: codes
  and their data; UNPACK reads `ceil(n x bits / 32)` words for n = NUM (or,
  with WL > CL, CL of each WL), bits = (32 >> vl) x (vn + 1) (16 for V4-5);
  DIRECT / DIRECTHL data starts on a qword, MPG's on 64 bits; STMASK 1 word,
  STROW / STCOL 4. A send should end on a packet / code boundary: on the
  fake disc every one of the 86 does.

### 4.6 Every static chain read, and the GS registers each send writes (session 76, static)

- **The offline walk** (`tools/host/dmawalk.py`, the Python twin of host/null/dmawalk.c over the
  user's ELF): the sends whose chain is a name, 155 of them (93 from the PlatDmaSend calls
  dmacheck `--list` calls static, each of `D_00351BE0`'s 9 distinct chain pointers counted once;
  62 through dmapool's `func_00106b18` / `func_00106bd8`). **81 walk whole** (67 GIF, 14 VIF: 1
  VIF0, 13 VIF1), **0 problems**: no chain leaves the ELF, ends inside a GIF packet or a VIF code,
  or holds a word that is no VIF code. **61 are zero in the ELF** (built at run time: the text
  windows' 0x400-byte buffers `D_003F1A70` / `D_003F1E70` / `D_003F2270` and textwin's
  `D_003F2670` / `D_003F2720` / `D_003F27D0`, grideff's `D_002BC270`, mdlgs' `D_00351C40`,
  texspot's `D_0035C4A0` / `D_0035C550`) and **13 are in bss** (the image uploads, `D_00573AC0` /
  `D_00573E40`, wave's `D_00631620`): the host run reads those (4.4) when it reaches them.
  Session 78: 68 of these 74 sends go to chains an init function builds from constants; the walk
  now seeds them and reads them whole (§4.8).
- **The VIF chains are microcode and setup**: mdlgs' `func_0015fc00` table (`D_00351BE0`, 24 entries,
  9 chains) and `D_00277E40` / `D_00278210` are one END tag each holding 1-3 MPG uploads (the VU1
  programs of §2.1) and a few codes; `func_0015f018`'s VIF0 / VIF1 chains and `func_0015f798`'s
  `D_00272CF0` carry one UNPACK each. None holds a DIRECT, so no static chain uses PATH2.
- **The float build sends the same chains.** `--float out/shift/m12-float/kh1-shift.linked.elf`:
  all 81 start at names the float build moved (so did every one of the 147 named starts), and every tag sits at the same name +
  offset, every ADDR word (264 point at moved objects) names the same name + offset, every data
  block holds the same bytes. So the static chains do not depend on the original layout.
- **GS registers written by the static chains** (`--regs`, register: sends): context 1 `PRIM`
  (written as a register or the GIFtag's PRE), `FRAME_1` 31, `ZBUF_1` 41, `TEST_1` 51, `ALPHA_1`
  38, `TEX0_1` 28, `TEX1_1` 26, `CLAMP_1` 12, `SCISSOR_1` 109 (sceneeff's strips: one scissor per
  strip), `TEXA` 5, `TEXFLUSH` 22, `SCANMSK` 1 (end of frame); context 2 only `ALPHA_2` 4, `TEST_2`
  6, `TEX1_2` 3, `ZBUF_2` 3 (field.c's and display.c's queued packets, roommdl), `FRAME_2` 1
  (brightfade's func_00105f28) and `FOGCOL` 1 (display.c's func_00110ce0). **Never written by a
  static chain**: `TEX0_2`, `CLAMP_2`, `SCISSOR_2`, `TEX2_x`, `XYOFFSET_x`, `PRMODE(CONT)`,
  `TEXCLUT`, `DIMX`, `DTHE`, `COLCLAMP`, `PABE`, `FBA_x`, `MIPTBP*`, and the transfer registers.
  So context 2's texture state (§3.3's REGION_CLAMP windows) comes from the model data (the VU
  GIF tags and the mesh chains in the disc's files), not from the ELF.
- **The run-time chains** (host, fake disc, `KH1_HOST_OVL=stub:2 KH1_HOST_TRACE=2`, which now
  prints each send's registers): the HUD's packets through `func_00237018` (src/hud: marker,
  counter, dmgnum, lblnum, gauge, popup) are 21 qwords that write **the whole context-1
  environment**, including `TEX2_1`, `XYOFFSET_1`, `PRMODECONT`, `DIMX`, `DTHE`, `COLCLAMP`,
  `PABE`, `FBA_1`, `MIPTBP1_1` / `MIPTBP2_1`: the only sends in the run that set those (consistent
  with §3.3's DTHE 0, COLCLAMP 1). func_001ef950's image uploads write `BITBLTBUF` / `TRXPOS` /
  `TRXREG` / `TRXDIR` + IMAGE; mdlgs' func_0015f388 renderer B's draw state (`TEX0_1`, `CLAMP_1`,
  `TEX1_1`, `FOGCOL`, `ALPHA_1`, `TEST_1`, `FRAME_1`, `ZBUF_1`, `TEXFLUSH`); shadow's func_001274c8
  `TEX1_1`, `TEST_1`, `TEST_2`. For the port: the HUD resets every context-1 register before it
  draws, so a renderer that keeps the GS state as a register file (not per draw) sees the same
  state the PS2 does.
- **PATH2** (VIF1 `DIRECT` / `DIRECTHL`): the data is one stream of GIF packets across the chain's
  DIRECTs; a chain that ends inside such a packet is a problem (host: `KH1_DMA_PATH2_SHORT`). No
  static chain and no fake-disc send has a DIRECT; renderer A's mesh chains (from the disc) are the
  likely users.

### 4.7 The state list: every GS state value and who sends it (session 77, static + fake disc)

- **The tools.** `tools/host/dmawalk.py --state` (static chains, the user's ELF) and
  `KH1_HOST_TRACE=4` + `tools/host/gsstate.py` (any host run: host/null/dmawalk.c keeps each send's
  distinct state values, `kh1_dma_gs_values`) print one block per GS register: each distinct
  value, decoded, with its senders (the function, or at run time the chain's host symbol). The
  output is derived from the user's ELF / disc: never commit it; the counts and the findings below
  are what the docs keep.
- **Static (81 chains): 18 registers, 87 distinct values.** `SCISSOR_1` has 19 (sceneeff's 16
  vertical 32-pixel strips, 512x384, 512x448, 640x448), `TEX0_1` 20, `FRAME_1` 10, `TEST_1` 8,
  `PRIM` 7, `TEST_2` 4, `ALPHA_1` / `ZBUF_1` 3, `CLAMP_1` / `TEX1_1` / `ZBUF_2` 2, and one each of
  `TEX1_2`, `ALPHA_2`, `FRAME_2`, `TEXA`, `FOGCOL` (rgb 16,112,128, display.c `func_00110ce0`),
  `TEXFLUSH`, `SCANMSK`. Against §3.2 this found the corrections now in it: `func_00106460`'s mask
  is a SPRITE (no POINT), the subtractive `(Cd-Cs)*As` pass, Z-only writes (`AFAIL=ZB_ONLY
  ZTST=GREATER`), the extra targets (Z area as colour, `0x3E0000`), point sampling, a static
  `REGION_CLAMP`. Everything else in §3.2's tables is there as written.
- **The HUD's default environment** (src/gfx/gspkt.c `func_002370c8(p)`, called from 17 files in src/hud (18 jal with `func_002372e0`),
  each into its own 22-qword bss block, sent by `func_00237018(p, 0x16, 1)`): two A+D GIF packets,
  15 + 4 registers. Decoded from the C: `FRAME_1` FBP `0xD0` FBW 512 CT32; `ZBUF_1` `0x70` Z24;
  `XYOFFSET_1` (1792, 1856); `SCISSOR_1` 512x384; `TEST_1` `ATE ATST=ALWAYS ZTE ZTST=GEQUAL`;
  `ALPHA_1` `(Cs-Cd)*As+Cd` FIX 128; `FBA_1` 0; `TEX0_1` a placeholder (TBP0 2, PSMT8 128x128, CBP 2,
  CLD 1); `TEX1_1` bilinear; `TEX2_1` PSMT8, CBP 0, CLD 1; `MIPTBP1_1` / `MIPTBP2_1` 0; `CLAMP_1`
  REPEAT; `PRMODECONT` 1; `COLCLAMP` 1; then `DTHE` 0, `DIMX` -4, `PABE` 0, `TEXA` 128 / 128. 14 of the
  HUD callers then set `TEST_1 = 0x30003` (ATST ALWAYS, ZTST ALWAYS: the HUD ignores Z) and
  `CLAMP_1 = 5` (CLAMP); counter, dmgnum and lblnum also set `ALPHA_1` additive (`0x80_00000048`).
  §3.3's dump (DTHE 0, COLCLAMP 1, PABE 0, PRMODECONT 1, TEXA 128 / 128 among others) matches.
  `func_002372e0` (sends the default from `D_006480D0`) and `func_00237318` (a 3D variant: TEST
  `GREATER` / `GEQUAL`, ALPHA FIX 0, CLAMP) have **no caller in the main ELF** (0 jal, 0 pointer
  words): dktitle.x or another overlay, or dead.
- **The fake-disc run** (`KH1_HOST_OVL=stub:2 KH1_HOST_TRACE=4`, 86 sends, 21 chains): 32 registers,
  53 distinct values. The HUD's seven environments (`D_00650DE0`, `D_00650F40`, `D_00651C00`,
  `D_006562C0`, `D_0065FB30`, `D_006627E0`, `D_00668E20`) carry exactly the values above; renderer
  B's draw state at `D_00573AC0+0x390` (`TEX0_1` `0x3600` PSMT8 128x128 CBP `0x3700`, `ALPHA_1`
  `(0-0)*FIX+Cs` FIX 128, `TEST_1 ATST=GEQUAL AREF=128 ZTST=GEQUAL`, `FOGCOL` 0) matches §3.2 / §3.3;
  the image uploads on the stack (`func_001ef950`) write `BITBLTBUF` (DBP `0x3FFC` CT32, `0x1000`
  PSMT4HL / PSMT4HH: the font halves), `TRXPOS` 0,0, `TRXREG` 16x16 / 256x256, `TRXDIR` host->local.
  Not yet seen: the text windows' chains (they are drawn after the title, which the fake disc does
  not reach): the real disc's run (next-session item 2) gives them.

### 4.8 The run-time chains the C builds from constants, and opdma's set-up packets (session 78, static)

- **Seeds.** 61 of 4.6's sends start at a chain that is zero in the ELF, but most of those chains
  are not drawn from data: an init function writes the whole packet from constants once and the
  senders send it as it is. `dmawalk.py` now has a `SEEDS` table (17 chains, each with the
  function whose C it copies) and writes them over the ELF's bytes before the walk; `--no-seeds`
  gives 4.6's numbers back. **155 sends: 81 whole, 68 whole from seeds, 0 problems**; still run
  time: 2 zero (grideff `D_002BC270`, whose transfer size comes from the run; mdlgs `D_00351C40`)
  and 4 in bss (mdlgs `D_00573AC0` / `D_00573E40`: renderer B's per-frame chains). With
  `--float` all 149 walked chains are the same chain in the float build. **The seeds were checked
  against the host build**: under gdb, after the boot ran `func_001f2eb8` and after `call
  func_001e9670()` / `call func_0020b338()`, every word of the host's packets equals the seed's
  (the ref tags' ADDR is a host pointer there).
- **What the seeded chains are.**
  - `func_001f2eb8` (text.nofill.c) builds the text's headers once: `D_003F1A70` (TEST_1 only,
    sent by 16 window draws), `D_003F1E70` (TEST_1, TEXFLUSH, `TEX0_1` the window font: PSMT4
    256x256 at `0x3D7C`, CLUT `0x3DFC`; `TEX1_1 LCM=1` bilinear; 23 senders), `D_003F2270` (the
    same with `TEX0_1` the message font: **PSMT4HL** 256x256 at `0x1000`, CLUT `0x3FFC`; 9
    senders: text.c's and wintext's draws), `D_003F27D0` (TEST_1 with Z GEQUAL, for windows with flag
    `0x10`), and the window font's uploads `D_003F2670` / `D_003F2720` (`func_0011fbb0`: 2048
    qwords PSMT4 from `D_003E9660`, the CLUT from `D_003F1660`; both in the ELF). The headers'
    `TEST_1 = 0x4000D` has **`ZTE=0`**: no depth test (ZTST is not used); a port reads it as
    `ZTST=ALWAYS`.
  - The message font is the disc's file `D_00490940` (`func_001ef950`): its CLUT to `0x3FFC` and its
    two halves to block `0x1000` as PSMT4HH and PSMT4HL, i.e. **into the top byte of the Z
    buffer's words** (the Z buffer is Z24 at `0xE0000`..`0x1C0000`; the top 8 bits are free). Only
    the HL half is drawn by the static headers; a port uploads both as ordinary 4-bit textures.
  - The menus' image uploads (`func_0011fbb0` into bss, the pixels from a file the menu loaded):
    menubg `D_00641080` / `D_00641130` (`func_0020b338`: PSMT8 104x56 at `0x3600`, CLUT `0x3640`),
    config `D_00642D30` / `D_00642DE0` (`func_00219500`: PSMT8 138x88, CLUT `0x3680`), journal
    `D_00642EB0` / `D_00642F60` (`func_0021d188`: PSMT8 256x256, CLUT `0x3700`) and
    `D_00643290` / `D_00643340` (`func_0021e120`: PSMT8 64x64, CLUT `0x3680`). The seeds give the
    pixels' source as a stand-in address the walk reads as run-time data.
  - The wave transition (`func_001e9670`, src/screen/wave.c): a cnt tag of 404 qwords, `TEST_1`
    `0x4000D`, `ALPHA_1 (Cs-Cd)*As+Cd`, then a GIF tag `LINE|IIP|ABE` with RGBAQ + XYZF2 x 200:
    100 lines, one per row (Y 2098+i), X from 1928+v to 2168+v where `func_001e9418` moves v along
    a sine each frame and fades the two colours' alpha (`D_003DD308` / `D_003DD30C`, 0..112).
  - texspot (`func_00175708` writes only the tags, QWC 10 and 16, over packets the ELF holds;
    `func_00175600` sends them around a renderer B draw `func_0015fa20`): `D_0035C4A0` points
    the target at the off-screen buffer `0x3A0000` (FBW 256, `XYOFFSET` 0,0, scissor 256x256,
    `ATST=GEQUAL AREF=120`, Z off and not written); `D_0035C550` then draws a PSMT8 64x64 sprite
    (`0x3600`, CLUT `0x3700`, `TFX=DECAL`) and composites the `0x3A00` CT32 256x256 texture with
    `REGION_CLAMP` 1..255 into the 3D target (`XYOFFSET` 1792,1856). Its `ZBUF_1` / `FRAME_1`
    (+0xF0 / +0x100) and the sprite corners come from the run (the object's own target and the
    spot's position), so the walk lists the ELF's placeholders (the default `0x1A0000` / Z24).
- **The state list with the seeds**: 23 registers, 115 distinct values (from 18 / 87). New:
  `XYOFFSET_1` (0,0 and 1792,1856), `PRIM LINE|IIP|ABE`, four `TEX0_1` (the two fonts, texspot's
  sprite and its `0x3A00` read), `TEX1_1 LCM=1`, `CLAMP_1 REGION_CLAMP 1..255`, three `TEST_1`
  (the `ZTE=0` header, texspot's two), `FRAME_1 0x3A0000` FBW 256, a 256x256 scissor, and the
  transfer registers (`BITBLTBUF` 7, `TRXREG` 5, `TRXPOS` / `TRXDIR` 1 each).
- **opdma's set-up packets** (`func_001a9eb8`, next-session item 4a of session 77). The insert
  functions' count (`func_001aa6b0` / `func_001aa700`'s `qwc`) **includes the DMA tag**: the tag's
  QWC is `qwc - 1`. So `func_001a9f88`'s `7` sends the tag's 6 qwords, a GIF tag (NLOOP 1, EOP,
  5 A+D) and its 5 A+D qwords, exactly as `func_001aa008`'s END tag of QWC 6 does: **no 7th
  qword goes and nothing runs short**. The 5 A+D are PRIM 0, `ZBUF_1`, PRIM 0, PRIM 0, `TEST_1
  ATE ATST=GREATER ZTE ZTST=GREATER` (`0x7000D`); `D_0061E800` has `ZBUF ZMSK=1` and heads list 1
  at priority 0, `D_0061E8B0` has `ZMSK=0` and goes last in list 3 at priority 15, so each frame
  the draws queued in the three lists (sent by pppobj's `func_001aa650`) go without writing Z and
  the end restores Z writes;
  `func_001aa008` sends `D_0061E8B0` alone to restore them. The words `func_001a9eb8` writes after
  the 5th A+D (`TEX1_1` `0x21`: LCM, bilinear magnify; `TEXA` TA1 128; `CLAMP_1` REPEAT, at
  +0x70..+0x9F) **are never sent and never read** in the main ELF: the readers are the VU0 draw
  routines (src/asm/vu0_render_2.s: the `ZBUF` qword at +0x30 and the `TEST` qword at +0x60, copied
  into their own packets), keshpdtt (+0x60), ryjkekoto (+0x30) and `func_001aaf30` (+0x60). The
  three zero A+D qwords are never written. Checked on the host: gdb's dump of both packets after
  the boot matches this word for word.

### 4.9 The text windows' per-draw packets, and renderer B's draw state, from the C (session 79, static)

- **How a window draw goes out.** Every text and window draw (text.c's `func_001f2a50` ...
  `func_001f2d68`, textwin, winpart, winmenu, wintext, winlist, util.c) is two GIF sends on
  channel 2, one after the other: first one of §4.8's static headers (`D_003F1A70` / `1E70` /
  `2270` / `27D0`: TEST_1, and with `1E70` / `2270` the font's TEXFLUSH / TEX0_1 / TEX1_1), then a
  packet built into a scratch frame (`func_00122048(1024, 128)` on the scratchpad, popped by
  `func_001220b8` after `PlatGsSyncPath`): an END tag (`qwc - 1 | 0x70000000`, its upper words never
  set) and one or two GIF packets. **The second send relies on the state the first left**: the
  header is not repeated in the packet. This is the case host/null/gsregs.c is for (§5.1).
- **The tags** (`python3 -I tools/host/giftags.py src/text/*.c src/util/util.c`, 43 functions):
  every per-draw primitive is a `SPRITE` or a `TRISTRIP` with PRE, **always `ABE`**, textured ones
  always `FST` (UV, no Q): `SPRITE|TME|ABE|FST` (21 functions: glyphs, window parts, icons),
  `TRISTRIP|IIP|ABE` (13: gradient frames and bars), `SPRITE|ABE` (5: fills),
  `TRISTRIP|IIP|TME|ABE|FST` (4: wintext's icons `func_001fc330` / `func_001fc750` /
  `func_001fcdc8`), `TRISTRIP|TME|ABE|FST` (3: winmenu's `func_001ff488` / `func_001ffb30` and
  winpart's `func_00203028`, 24-vertex strips), `TRISTRIP|ABE` (2: the bevels below). No
  TRIANGLE, TRIFAN, LINE or POINT; Z is a constant `0x10000` with ZTE 0 from the headers.
- **Glyphs** (text.nofill.c `func_001f0ea8` / `func_001f12c0` / `func_001f15f0` / `func_001f18e8`,
  text.nostrict_nofill.c `func_001f0868`): a header GIF tag (6 A+D; `func_001f0868`: 5) with
  `TEXFLUSH`, `TEX0_1 0x2007FF8622411000` (TBP0 `0x1000` TBW 256 **PSMT4HL** 256x256, TCC 1,
  MODULATE, CBP `0x3FFC` CT32, CLD 1), `TEX1_1 0x61` (LCM 1, bilinear), `TEX2_1
  0x4007FF8001300000` (PSMT8, CBP `0x3FFC`, **CLD 2**: the whole 256-entry CLUT into the CLUT
  buffer), `ALPHA_1 0x44` (`(Cs-Cd)*As+Cd`) and the colour as RGBAQ (Q 0; `func_001f0868` sends a
  colour per glyph instead: control codes 7 / 8 / 9 change it, `D_003E8D08` is its table); then
  one sprite tag `SPRITE|TME|ABE|FST` with NLOOP = the glyph count and EOP, its registers `A+D,
  UV, XYZF2, UV, XYZF2` (`func_001f0868`: `A+D, A+D, UV, XYZF2, UV, XYZF2`). **Each glyph's A+D
  is a `TEX2_1`**: PSM `D_003E8D00[f7 >> 4]` (`0x24` PSMT4HL or `0x2C` **PSMT4HH**), CSA `f7 & 15`,
  CBP `0x3FFC`, **CLD 0**. The default glyph table `D_003E4658` (`func_001efaa8`, `0x310` = 784
  entries) has **196 cell positions, each used by four glyphs**: (HL, CSA 0), (HL, CSA 1), (HH,
  CSA 0), (HH, CSA 1), 196 each. So the message font is four layers on one 256x256 grid of
  18.5-pixel cells: the two 4-bit halves of the Z buffer's top byte, each read through palette 0
  or 1 of the CLUT at `0x3FFC`. **That answers who draws the PSMT4HH half: every glyph with `f7 >>
  4 = 1`, through its own TEX2**, in all five builders. That palette 0 and 1 pick different bit
  pairs of the 4-bit texel (2 bits a layer) is an inference: the CLUT is in the disc's file
  (`D_00490940`), not the ELF. The first vertex has ADC set (XYZF3, no drawing kick).
- **Windows** (textwin, winpart, winmenu, wintext; header `D_003F1E70` for the textured ones):
  the window font `TEX0_1 0x7BF8621413D7C` (TBP0 `0x3D7C` PSMT4 256x256, CBP `0x3DFC`, CLD 0; CLD 1
  only in func_001f2eb8's header set-up), `TEX2_1 0x4007BF8001300000` (PSMT8, CBP `0x3DFC`, CLD 2:
  16 builders), then per part a `TEX2_1` PSMT4 with CSA 0, 3 or 4 (`0x7BF8001400000`,
  `0x307BF8001400000`, `0x407BF8001400000`: palettes 0 / 3 / 4 of the window CLUT). Clipping is
  per draw: wintext.c's `func_001f86e0` / `func_001f8950` / `func_001f8ba8` and util.c's
  `func_001edfb8` send an A+D-only packet
  `SCISSOR_1 = x0 | x1 << 16 | y0 << 32 | y1 << 48` (`func_0011fb38(64, ...)`), clamped to
  512x384, before the window's contents; `func_001f8f30` puts it back to the full 512x384.
- **The bevel** (winpart.nostrict.c `func_00206748`): one GIF tag, `TRISTRIP|ABE` NREG 15 = five
  groups of (A+D, XYZF2, XYZF2), the 10 vertices outer / inner corners around the rectangle (2
  pixels wide). The first A+D is the colour (`0x202020`, alpha `+0x90`); the other four are
  `ALPHA_1` **changed in the middle of the strip**: `0x48` (`(Cs-0)*As+Cd`, additive) on two sides
  and `0x42` (**`(0-Cs)*As+Cd`, subtractive**) on the other two, swapped by `f1` (raised or
  sunken). On the GS a register write between vertex kicks applies to the next primitive and the
  strip goes on: a port has to split the strip there and keep its last two vertices (gsregs.c
  counts such a strip as two draw states with the queue carried over).
- **Renderer B's draw state** (src/model/mdlgs.nostrict.c). `func_0015f128` (init) builds
  `D_00573E40`: a CALL tag to `D_00573AC0` (the upload list), an END tag of QWC 10, a GIF tag of 9
  A+D: `TEXFLUSH`, `TEX0_1`, `TEX1_1 0x60` (bilinear, LCM 0), `TEST_1`, `ALPHA_1`, `ZBUF_1
  0x31000070`, `FOGCOL`, `FRAME_1 0x800D0`, `CLAMP_1 5`. Per draw `func_0015f488` fills it:
  - the uploads `D_00573AD0[i]` (each 4 A+D BITBLTBUF / TRXPOS / TRXREG / TRXDIR and an IMAGE tag,
    the pixels by REF): the CLUT 16x16 CT32 to `0x3700` (DBW 64), the texture PSMT8 `w x h` to
    `0x3600` (DBW 256), then a RET; `func_0015f8c8` adds up to 7 more PSMT8 uploads into `0x3600`
    at TRXPOS `(x0, x1)` from frame `k` of each source (`data + n * k * 16`): sub-rectangle
    texture animation (called with k 0 in the main ELF);
  - `TEX0_1 = 0x2006E00401313600 | TW << 26 | TH << 30`: TBP0 `0x3600` TBW 256 PSMT8, TCC 1,
    MODULATE, CBP `0x3700` CT32, CLD 1;
  - the two passes by `a->x5` (§5's two-pass `TEST` row): **opaque**
    (`x5 == 0`): `TEST_1 = k << 4 | 0x5800B` (ATST GEQUAL, AREF k = the model's `+0x2C` clamped to
    120, ZTST GEQUAL, DATM 1 without DATE: inert), `ZBUF_1` the instance's (Z written), `FOGCOL` the
    model's `+0x30 / +0x34 / +0x38`; **translucent** (`x5 != 0`): `TEST_1 = k << 4 | 0x50005`
    (ATST LESS, AREF k unclamped), `ZBUF_1` with **ZMSK 1**, FOGCOL left as it was. Both:
    `ALPHA_1 (Cs-Cd)*As+Cd` FIX 128, `FRAME_1` the instance's `+0x8`, `CLAMP_1 5`;
  - with a model callback (`+0x40`) the slot description `D_0055C680` (block `0x3600`, format 19,
    size, CLUT `0x3700`) for §3.4's off-screen passes.
  `func_0015f388` (put in the draw list by mdldraw.nostrict.c at keys 0, `0x5013`, `0x11363` and
  `0x7FFFFFFF`: a reset between groups of draws) sends `D_00573E40` from its END tag (no
  uploads, TEX0 as the last draw left it): `TEST_1 0x5080B` (ATST GEQUAL AREF 128, ZTST GEQUAL),
  `ALPHA_1 (0-0)*FIX+Cs` FIX 128 (blending off), `FOGCOL` from `D_002BC0F0`, `ZBUF_1 0x31000070`,
  `FRAME_1 0x800D0`, `CLAMP_1 5`: the values the fake-disc run saw at `D_00573AC0+0x390` (§4.7).
- **The fake-disc run's draws** (`KH1_HOST_OVL=stub:2 KH1_HOST_TRACE=5`, then `gsstate.py
  --draws`): 4 draw states, 392 vertex kicks, 196 sprites:
  `D_002A6500` 112 untextured sprites into the 3D target (FBP `0xD0`, 16 a send), `D_002A6890` 80
  `SPRITE|TME|FST` copying the 3D target (`TEX0` `0x1A00` CT24 512x512) to the display buffer (FBP
  0), `D_002B66B0` 3 sprites reading the Z area as a CT24 texture (`0xE00`) into the 3D target,
  `D_002BC980` one fill of the display buffer. None has ABE (their ALPHA_1 is set but unused).

### 4.10 The builders giftags.py misses: lists, the field text, the selector, the HUD gauges (session 80, static)

`giftags.py` only sees GIF tags written as one PACKED constant: it reports `func_00208458` (2 of 4
tags) and the face pictures, and nothing in winrow, winlist.c, selector, fldtext* or the rest of the
gauges. Read from the C (the two still-assembly functions from their drafts, marked):

- **Menu rows, tabs, titles and lists draw nothing themselves.** winrow.c and winlist.c (`func_00208ea8`
  ... `func_00209b90`) only call wintext (`func_001f9270`, `func_001f9438`, `func_001f94f0`,
  `func_001f9e48`, `func_001f9010`, `func_001fc308`, `func_001fb428`) and winpart (`func_00201440` /
  `460` / `480`, `func_00200648`, `func_002016b0`, `func_00201988`, `func_00201c60`, `func_002053e8`);
  each list sits between `func_001f8e18` (its SCISSOR_1 via `func_001f86e0`) and `func_001f8f30`. *From
  the drafts (inferred):* `func_00200e28` re-sends the window-font uploads `D_003F2670` / `2720` and
  `D_003F1E70`, then 5 A+D (TEXFLUSH, the window TEX0_1, TEX2_1 CLD 2, TEX2_1 CSA 0, ALPHA 0x44) and a
  `TRISTRIP|IIP|TME|ABE|FST` of 24; `func_001f1fc8` sends `D_003F2270`, 3 A+D (TEXFLUSH, `TEX2_1
  0x4007FF8001300000`, ALPHA 0x44) and one `SPRITE|TME|ABE|FST` NREG 6 tag a glyph.
- **The list frame** (winlist.nostrict.c `func_00208458`): `D_003F1E70`, then four PACKED tags in a
  `func_00122048(1536, 128)` frame: 5 A+D (TEXFLUSH, window font TEX0_1 CLD 0, TEX2_1 PSMT8 `0x3DFC` CLD
  2, TEX2_1 CSA 3, ALPHA 0x44); `TRISTRIP|IIP|ABE` NLOOP 18 of (A+D RGBAQ, XYZF2) that is **three
  6-vertex strips in one tag, restarted by ADC on v6 / v7 and v12 / v13** (winlist.nostrict.c:81-89);
  one window-font cell `SPRITE|TME|ABE|FST`; and `SPRITE|ABE` NLOOP n + 1 with its tag built from parts
  (`(n+1) | 0x8000 | 0xC08D << 46`, :102): the dividers.
- **The field text and the value selector use neither §4.8's headers nor PACKED.** They send their own
  static chains through dmapool's `func_00106b18` (ch 2), draw in offset coordinates, set no SCISSOR:
  - the field text's header `D_002BBAA0` (REFE to `D_002BBA20`, from `func_0010ea00` / `ea38` / `ea70`,
    `func_0010ed20`): TEXFLUSH, `ZBUF_1` 0x70 Z24 **ZMSK 1**, ALPHA 0x44, `TEX1_1 0x60`, `TEST_1` ATST
    GREATER AREF 0 **ZTE 1 ZTST ALWAYS**, then a **REGLIST** tag that writes **PRIM `SPRITE|TME|ABE|FST`
    as a register** and RGBAQ 128 x 4;
  - the glyphs (`func_0010c540`, fldtext.c:124): one REGLIST tag, **no PRE, NREG 6 `TEX0_1, RGBAQ, UV,
    XYZ2, UV, XYZ2`** (`0x535316`), relying on the PRIM the header wrote. Each glyph's TEX0
    (`func_0010c5c8`) is PSMT4 512x512 at `0x3600` / `0x3800`, CBP `0x3FDC`..`0x3FF3`, **CLD 1 on every
    glyph**; Z `0xFFFFFFFE`. Icons (id >= 10000) are **PSMT8H at `0x1800`** (the Z buffer's top byte), CBP
    `0x3FF4`; icons 6-9 PSMT4 at `0x3A00`, CBP `0x3C00`. `func_0010e610` builds each CLUT pair as `a[i] =
    c[i & 3]`, `b[i] = c[i >> 2]`: **CBP n shows a texel's low 2 bits, n + 1 its high 2 bits** (read from
    the C; §4.9's message-font layers are the same idea, still inferred there). `func_0010c4b0` uploads
    the kanji file again before each draw (CT32 256x256 at `0x3600`, pre-arranged PSMT4, inferred);
  - the selector (`func_0010f0d0`, selector.c:101) patches two XYZ2 words of `D_002BBAF0` and sends
    `D_002BBB90`: TEXFLUSH, the same TEST_1, `TEX0_1` PSMT8H `0x1800` CBP `0x3FF4` CLD 1, `TEX1_1 0x60`,
    ALPHA 0x44, then a REGLIST tag writing PRIM `SPRITE|TME|ABE|FST`, RGBAQ, UV, XYZ2, UV, XYZ2 (its
    tag's PRIM field is ignored: no PRE in REGLIST matters only with FLG 0).
- **The HUD gauges** (src/hud/gauge*.c), after `func_002416a8`'s environment (§4.7), each built into
  `D_00351E10` and sent by `func_00237018`:
  - sprites (`func_0023d700` -> ui.c `func_0024aa48` -> src/gfx/prim.nostrict*.c `func_002388b8`) are
    **`TRIANGLE|IIP|TME|ABE|FST` pairs** (`0xC0ADC000 << 32`, prim.nostrict.c:98), NREG 12: 3 A+D then 3 x
    (UV, RGBAQ, XYZF2); each triangle repeats TEXFLUSH, a `TEX0_1` with **PSM forced to PSMT8, CSA 0,
    CLD 1** (loads the whole CLUT) and then the real TEX0 (CLD 0): the text headers' TEX2 trick done with
    two TEX0s. The needles (`func_0023d7e8`) the same, Z -256. TEX0s come from TIM2 headers at run time;
  - arcs (`func_0023e160`, gauge.nostrict.c:297) are a **`TRIFAN|IIP|TME|ABE|FST`** (tag from parts,
    `0x82BB << 46`, :328) of (UV, XYZ2) after a one-register PACKED RGBAQ tag with no PRE (the colour);
    the texture state from earlier packets (`func_0023ee80`'s two TEX0s; `func_00240fa0` / `func_002410b8`
    / `func_00241260`'s one);
  - fades: `ALPHA_1` additive FIX 128 (`0x80_00000048`) before, back to `0x44` after;
  - face pictures (`func_00242c08` / `func_00242ef8`, also from shopbuy, shopsell, synth): two
    `func_0011fbb0` uploads (CLUT 16x16 CT32 to `0x3C00` with **DBW 0**, PSMT8 to `0x3A00`), then
    `SPRITE|TME|ABE|FST` NREG 8 with TEXFLUSH, `TEX0_1 0x20078005A1313A00` (CLD 1), **`TEX1_1 0`**
    (nearest), RGBAQ, UV, XYZ2 (ADC), UV, XYZ2.

**Corrections to §4.9** (kept there as written): its "two sends, a §4.8 header then a scratch packet"
holds for the windows only (not the field text, the selector, the face pictures); "Z constant `0x10000`
with ZTE 0" for the windows only (the field text and selector have ZTE 1 ZTST ALWAYS, the field text
ZMSK 1); "PRE on every primitive" fails for the REGLIST packets, where PRIM is a register write; ADC
also restarts strips inside one tag (`func_00208458`), so a port honours ADC on every XYZ(F)2; "no
TRIANGLE / TRIFAN" is true of src/text only (the HUD gauges use both). The fonts, icons and pictures
share `0x3600`..`0x3C00` and are uploaded again per draw: a texture cache keyed by address must check
contents (§5.2's page stamps).

### 4.11 Renderer A's draw state, from the C (session 80, static)

Renderer A (§2.2) writes **no GS register in its VIF chains** and no GIF tag of its own for the meshes:
the chains (`D_0048C630` / `C690` templates, the grid chains `D_0046E120` ... `D_00482260`, the program
chains `D_004941D0` .. `D_004942D0`) hold only REF / END, MPG, STCYCL, UNPACK, MSCAL, BASE, OFFSET and
MSCNT, sent on VIF1 by `func_00108d90` (CHCR `0x145`) / `func_00106db0` (`0x105`); the meshes reach the GS
by **XGKICK (PATH1)**. Context 2's state comes from three places:

- **The boot draw environment, both contexts** (`func_001100a8`, display.c:102, once at boot from
  `func_00120b10` via `func_001101e8`): one 31-A+D packet through `sceGsPutDrawEnv` (ch 2): the 13 values
  `D_002BC830` to context 1 (`D_002BC750`) **and context 2** (`D_002BC7C0`): FRAME `0x800D0`, ZBUF
  `0x31000070`, XYOFFSET `(0x7000, 0x7400)`, SCISSOR 512x384, TEST `0x5000D`, ALPHA `0x44`, FBA 0, TEX0
  `0x20000045DD308002` (a PSMT8 placeholder, CLD 1), TEX1 `0x60`, TEX2 PSMT8 CBP 0 CLD 1, MIPTBP1 / 2 0,
  CLAMP 5; then PRMODECONT 1, COLCLAMP 1, DTHE 0, PABE 0, DIMX -4. So **FRAME_2, ZBUF_2, XYOFFSET_2 and
  SCISSOR_2 are the 3D target from boot**; only the shadow pass (`func_00128738`) rewrites them, and
  restores the same values (§3.4).
- **Context-2 state packets in the draw list** (`func_00106bd8` -> `func_00106b98` -> `PlatDmaSend` on
  `D_002A6B84`, ch 2: **PATH3**), each a REFE to one A+D tag, ordered by key (§4.1):
  - key 10010 `D_0029B170` (`func_001008e8`, field.c:310), just before the P4 map meshes of `.bin`
    sections 2 / 3: `ALPHA_2 0x44`, **`TEST_2 0x31001`** (ATST NEVER, AFAIL FB_ONLY, ZTE 1, ZTST ALWAYS):
    no depth test, no Z write, no alpha discard (inferred: a sky / backdrop). This is §3.2's only
    `NEVER / FB_ONLY` value;
  - key 10010 `D_002BC9F0` (`func_00110ce0`, display.c:352, every frame): TEXFLUSH, **FOGCOL rewritten each
    frame** from `D_002BC0F0.camS.b[0..2]` (display.c:344, set by the script, vm_lib.c), `TEX1_2 0x60`,
    `ALPHA_2 0x44`, `TEST_2 0x5000D`; the same function writes the fog coefficients into `D_002BC170[3]` /
    `[7]` (VU qw4.w / qw5.w) from `camS.a`;
  - key 10020 `D_0029B1C0` (`func_00100988`, field.c:337), before the grid's opaque cells: `ALPHA_2 0x44`,
    **`TEST_2 0x5010D`** (ATST GREATER AREF 16, ZTST GEQUAL), `TEX1_2 0x60` (§3.3's CTXT2 AREF 16);
  - key 40000 `D_002BD140` (roommdl.c:138), once per opaque prop (objdraw.nostrict.c:374: alpha scale >= 1;
    below 1 it goes to key 50010): **`TEST_2 0x507FD`** (AREF 127);
  - key 50000 `D_0029B200`: **`ZBUF_2` ZMSK 1**, `TEST_2 0x5000D`: the translucent pass (P3 cells,
    `func_00108708`'s fade groups, translucent props at 50010);
  - key 50100 `D_0029B260`, the restore: `ALPHA_2 0x44`, `TEST_2 0x5000D`, `ZBUF_2` ZMSK 0, `TEX1_2 0x60`;
  - the shadow's `D_004F8270` (`func_00128b20`, keys `0xB1BB` / `0xEC53`): `TEST_1` / `TEST_2 0x50000`
    (ATE 0), `TEX1_1 0x60`.
- **The disc files** (inferred, not read): each batch's GIF tag and the clipper's qw48 fan template
  (`TRIFAN|IIP|TME|ABE|CTXT2`, with FGE `0x313EC000` from `D_004862B0` statically in the key-50000 grid
  chains and spliced by `func_001081c8` / `func_001083d8`, without `0x312EC000` from `D_004862E0` for
  roommdl's `func_00114c18`; the key-10020 grid chains' from map section 1 entry 0, written by
  `func_00106ed0`; props' from model header +0x80), P7's forced PRIM `0x313E4000`
  (`TRISTRIP|IIP|TME|FGE|ABE|CTXT2`), and the mesh textures: `FLUSH` + `DIRECT` (PATH2) inside the cell /
  +0x90 REFs, whose registers beyond the transfers are not read. **TEX0_2 / CLAMP_2 for the meshes come
  from there.** The only TEX0_2 the C writes is the shadow receivers' (`func_00128738`: CT32 256x256 at
  `0x3600` CLD 1, CLAMP_2 REGION_CLAMP, `ALPHA_2` FIX 64, `TEX1_2 0x61`; their batches built in
  shadow.nostrict.c:79-88 with PRIM `0x312E4000`, run by P1). The one C-side upload is the map's
  (`func_00106e18`, grideff.c:69, keys 10020 / 50000 when record 0 +0x7C != 1.0): CT32 DBW 2 at `0x3600`,
  128 x 128n from the file's tail, then TEXFLUSH (PATH3).

**Corrections**: §4.6's "never written by a static chain: TEX0_2, CLAMP_2, SCISSOR_2, TEX2_x, XYOFFSET_x,
PRMODECONT, DIMX, DTHE, COLCLAMP, PABE, FBA_x, MIPTBP*" holds for the DMA chains only: the boot
`sceGsPutDrawEnv` writes all of them for both contexts. It goes through the SDK, not PlatDmaSend, and the null
platform's PlatGsPutDrawEnv did nothing; **since session 80 it hands the packet to dmawalk.c's GIF reader**
(`kh1_dma_gif_direct`, a send line with chcr 0 named `D_004D8EF0`), so the fake disc now shows **87 sends,
22 chains, 40 registers, 61 values** (was 86 / 21 / 32 / 53: the 8 new registers are context 2's and
MIPTBP / TEX2 / XYOFFSET), the draw states unchanged. §4.6's "context 2's texture state is not from the
ELF" has two exceptions (the boot placeholder, the shadow pass). §5.1's `FOGCOL` "rgb (16,112,128) in
display.c" is only the initial value: display.c:344 rewrites it each frame. §3.3's field-dump "map draws"
(TEX0 `0x3600` PSMT8, AREF 120) are renderer B's context-1 state (§4.9), not renderer A's (inferred). §2.2's
qw48 template does not come only from the model header slots (see above). ~~The order between PATH1 (XGKICK)
and these PATH3 packets is not settled: `func_00106b98` does not wait for the path.~~ Settled in §4.12 (session
81): `func_00106b98` does not wait, but the walk that calls it does, before every node.

### 4.12 The order between the paths (session 81, static)

**Inside the draw list the order is strict, node by node.** `func_0015ea98` (mdlgs.nostrict.c), the walk that
both the start (`func_0015eb78`, task `0x9C40`) and the DMAC handler (`func_0015efc0`, ch 1 and ch 2) run,
spins on `sceGsSyncPath(1, 0)` **before each node**. Mode 1 (src/sdk/gcc991111_as296/text_00260000_s8_w10.c)
is non-zero while D1_CHCR STR, D2_CHCR STR, VIF1_STAT `& 0x1F000003` (VPS, FQC: VIF1 still holds data or is
waiting on an MSCAL), VU1 running (`vi29` bit 8) or GIF_STAT APATH (bits 10-11) is set. So node N's last VU1
program has stopped and its XGKICK has left the GIF before node N+1's callback starts: a context-2 state packet
(`func_00106b98`, §4.11's keys 10010 ... 50100) lands exactly between the mesh nodes its key sits between, and
renderer B's GIF state (§4.3 step 2) between its own steps. Any DMA end, the list's or another sender's on ch
2, re-enters the walk, which again waits for every path; a node can start early, never out of order. Renderer
A's own VIF chains end with `END` and no `FLUSH` (`vif_chain.py 0048c630`, `0046e120`), which is why the wait
is needed; inside a chain the `FLUSH` before each `DIRECT` (§4.11) orders PATH2 after the PATH1 before it.

**The immediate list waits for the draw list to drain.** `func_0015eea0` (task `0x27CB8`) calls
`sceGsSyncPath(0, 0)` (blocking) first and between nodes. On the main thread that returns only when the
draw list is done: between two nodes the handler itself waits and starts the next DMA before it returns,
so the main thread never sees the paths idle mid-list. The same holds for every send behind
`func_00106b18` (FlushCache, `sceGsSyncPath(0, 0)`, then the send) and for the HUD's `func_00237018`.

**Main-thread sends, by task key** (`python3 -I tools/host/sendorder.py`: each task registered with a literal
key whose calls reach a send, and its first sync or send in source order): every sending task before `0x9C40`
or after `0x27CB8` (the HUD at `0x28489` / `0x29811`, menus at `0x2BFxx`, the field effects at `0x2E6xx`) is
serial with the list by the waits above. Between the two keys only two tasks send: the particles
(`func_00175b70`, `0x27100`) sync first; **the in-game menu (`func_0020d2f8`, `0x270FF`, three registrations)
sends first** (session 84: but after the frame-end wait, below): `func_001f82b0` -> `func_001f8270` re-sends the window-font uploads `D_003F2670` / `2720`
(sceDmaSend waits only for ch 2 itself, func_00266ab0), and each window then sends its header (`D_003F1E70`:
`TEST_1`, `TEX0_1`, ...) before its own `sceGsSyncPath(0, 0)`. On the console that overlaps the list's tail
only if the list is still drawing 120,000 task keys later (timing; the uploads touch only the window font's
blocks, the header context-1 registers renderer B also writes). **What the port must serialise**: replay the
draw list to its end, then the immediate list, then the main-thread sends in task order; a main-thread send
made while a list is pending (the menu) runs after that list, which is the console's normal case. The GIF's
path arbitration (PATH1 over PATH2 over PATH3 at packet ends) never needs modelling. Approximate: sendorder.py
follows calls by name in source order (not branches) and skips registrations with a non-literal key.
Session 82: the pattern also reads a plain cast on the callback (`(s32) &func_X`): four more registrations
(168 in all, every one with a literal key; `--all` lists any it cannot read: none), one of them sending
(brightfade's `func_00106460` at `0x2E646`, after the immediate list, through `func_00106b18`'s sync). Still
3 RACE rows, all the in-game menu.

**The frame-end wait drains the list first** (session 84). Task **150000 (`0x249F0`)**, `func_0011eda8` ->
`func_0015ef60`, spins until the list's pending flag `D_00559DB4` is 0 (set by the hand-over, cleared by
`func_0015ea98` at the list's end), then `sceGsSyncPath(0, 0)`, then masks DMAC channels 1 and 2. It is
registered by `func_0011edc8` right after `func_0015ec68` registers `0x9C40` / `0x27CB8`, in the same task
list (`D_004E3A48`, run in key order). So **every task after `0x249F0` runs with the draw list done**,
the in-game menu at `0x270FF` included: its unsynced sends never overlap the list, on the console or the
port. No task between `0x9C40` and `0x249F0` sends. sendorder.py finds the wait from the C and counts RACE
only before it: 0. The port's replay point is that wait (`PlatGsListWait`, vita-port-plan 5.1x).

**The draw list's key map** (session 82, `python3 -I tools/host/drawkeys.py [--tsv OUT]`): every insert into
the draw list (`func_0015ed80(key, cb)`, `func_00106bd8(packet, key)`, which queues `func_00106b98` sending
`packet` on the GIF) and the immediate list (`func_0015ee78`), a key that is a wrapper's parameter followed to
its callers by name (`func_00100670`, `func_00107d30`, `func_001085e8`, `func_00106e98`, `func_00108f18`,
`func_00108fd0`, `func_00114f50`, `func_00114a38`), a variable assigned once from a literal read as it
(`D_004F82C4 = 60000`). Draw-list keys are their own space (not task keys). 38 rows, sorted; decimal here
because the C writes most of them so:

| Key | Inserted by | Callback / payload | What it is |
| --- | --- | --- | --- |
| 10000 + n | texanim.c `func_00101bb8` (n: the running count `D_004945F0`) | `func_001019c8` | texture animation steps, one node each, in the order made: GS-to-GS frame copies and scrolls (§4.13 "The texture steps"; n is never reset, so later steps sort after 10010 and up) |
| 10010 | field.c `func_001008e8`; display.c `func_00110ce0` | `func_00106b98` `D_0029B170` / `D_002BC9F0`; renderer A `func_00108d90` (via `func_00108f18`) | context-2 state packet (§4.11), then the first renderer A objects |
| 10020 | field.c `func_00100988` | packet `D_0029B1C0`; `func_00108d90` (`func_00100670`), `func_00106db0` (`func_00107d30`), `func_00106e18` (`func_00106e98`: an upload to `0x3600`) | state packet, then the field's renderer A chains |
| 20499 | mdldraw `func_00160370` | `func_0015f388` | renderer B's GS state reset |
| 40000 | roommdl.c `func_00114a38` | packet `D_002BD140` (before the first model: equal keys keep insertion order); objdraw `func_001369e8` > `func_00114a38` > `func_00108df8`: `func_00108d90` when `v[3] >= 1.0` | the room / object meshes, opaque |
| 45499 | shadow.c `func_00128440` | `func_001274c8` (`D_004F8270`) | shadow pass state (per frame; also resets the shadow count) |
| 50000 | field.c `func_00100988`; grideff `func_00108708` | packet `D_0029B200`; `func_00108d90`, `func_00106db0`, `func_00106e18` | state packet, then the fade groups (§4.11) |
| 50010 | objdraw `func_001369e8` (`v[3] < 1.0`) | `func_00108d90` | the translucent props |
| 50100 | field.c `func_00100988` | packet `D_0029B260` | state packet |
| 60000 + n | shadow.nostrict.c `func_00127568`, `func_00127c20`; shadow.c `func_00127b18` (n: `D_004F82C0`, reset to 0 by `func_00128440`) | `func_00127500` (a heap chain), `func_001274c8`, `func_00108d90` (`func_00114f50`, `func_001149e8` > `func_00108fd0`) | the shadows, in the order cast |
| 60499 | shadow.c `func_00128440` | `func_001274c8` (`D_004F8270`) | shadow pass end state |
| 70499 | mdldraw `func_00160370` | `func_0015f388` | renderer B's reset again |
| 90000 + 10 id + 0 ... 6 | texanim.c `func_00102118` (id: the animation's) | +0 `func_00101f80` (an upload chain), +1 packets `D_002A4310` / `D_002A44E0`, +2 / +5 `func_00101f30`, +3 `func_00101f80`, +4 `D_002A43A0` / `D_002A4570`, +6 `D_002A45C0` | per-animation CLUT cross-fade (§4.13) |
| *data* | mdldraw `func_00160370` | `func_0015ff78` (renderer B, one node per entry) | `e->x28`: the part's priority (session 83, below: 20000 opaque / 70000 translucent, or the caller's own, the shadows' 60000 + n) plus the model's depth rank, clamped to [prio - 500, prio + 499], except priorities 59500 ... 60499 (the shadow band) and models flagged `0x10000` (an explicit priority), which keep it; entries with `f` set (`x4 & 8`) or a model flagged `0x20000` go to the immediate list |

Immediate list: renderer B's entries at key 0 (`func_00161de8`) and their `e->x28`, and `func_0015f388` at 0
and `0x7FFFFFFF`. So within a frame the GIF sees: texture animation steps, the 10010 / 10020 state and field
chains, renderer B's opaque band (priorities around 20000-70000 bracketed by resets at 20499 and 70499), the
opaque room / objects at 40000, the shadow state, the fade groups and translucent props at 50000-50100, the
shadows at 60000+, the texture animation passes at 90000+, then the immediate list. Renderer B's priorities
interleave with all of these by value: a port keeps one sorted list for both renderers, as the console does.

**Renderer B's keys** (session 83, item 4b; mdldraw.nostrict.c `func_001606d0` and `func_00160370`, read from
the C). `func_001606d0(obj, matrix, prm, arg)` adds a model's parts to the frame's table with `e->x28 = prio`:

- **opaque pass** (every part not hidden by `prm->x28`'s bit `b1`): `prio = prm->x8` when it is positive,
  else **20000 when the model colour's alpha `prm->xf` is 0x80 or more** (`(s8) xf < 0`) **and 70000 when it
  is below** (a fading model). A part whose bit is set in `prm->x2c` gets `f = 1`, which sends it to the
  immediate list.
- **translucent pass** (parts with `b0 & 1`, not hidden and not `f`): `prm->x8` when positive, else **70000**.
- **the attached second model** (`prm->x14`, e.g. an object's extra mesh): the same, its alpha `prm->x1b`.

The callers: objdraw.nostrict.c `func_00136428` (every object model, through `func_001621e0`) passes `x8 =
-1` and the object colour's alpha (objdraw.c's `v[3]` from `func_00135df0`) as `xf` / `x1b`, so **objects sit at 20000 (opaque) or 70000 (fading, and every
translucent part)**; shadow.nostrict.c `func_00127960` passes `x8 = D_004F82C4 + D_004F82C0` (60000 + n, n
counting up by 10 per shadow model), inside the band that keeps its key; partymdl.c / journalmdl.c draw
through `func_00161de8`, which runs the entries at once on the immediate list at key 0 (the menus' models)
and never reaches `func_00160370`. `prm->xc` ... `xf` are the model colour (`DObj.x20` ... `x2c`), not keys.
`func_00160370` then sorts the frame's models by their root matrix's `[3][3]` (`x10->x0 + 0x3C`, a float;
largest first) and gives each its rank `x49` (0 for the farthest); a moved key is `prio + rank`. **That
float is the depth** (session 84, from the C): `func_001606d0` stores `m x bone 0` as the model's first
matrix, and objdraw's `m` is `D_002E26C0`, which camera/view.c `func_00125000` builds as `D_002E2740 x
D_002E2700`: the view-screen matrix (`D_002BBE20`, the first output of display.c's `func_00110618`; its w row
is (0, 0, 1, 0) in every draft of that unmatched function, as in libvu0's `sceVu0ViewScreenMatrix`) times
the camera matrix (`sceVu0CameraMatrix`). So `[3][3]` is the clip w of the model's origin, its camera-space
z. Shadow models (`func_00127960`, their own matrix) are in the same sort and take ranks too, so an object's
rank counts them; that only leaves gaps, the objects' order among themselves is still by depth. The rank is at most 77 (78 model
slots), so the [prio - 500, prio + 499] clamp never bites: **opaque models take 20000 ... 20077 and
translucent ones 70000 ... 70077, far to near**, just below the resets at 20499 / 70499 (inserted after the
entries, so they run after every entry of the same key). So the frame's order is: texture animation steps
(10000+), field state and chains (10010 / 10020), **renderer B's opaque models, back to front**, the reset,
room / objects of renderer A (40000), shadow state (45499), fades and translucent props (50000-50100),
shadows (60000+, renderer A's and renderer B's shadow models, cast order), shadow end (60499), **renderer B's
translucent and fading models, back to front**, the reset (70499), the texture animation passes (90000+),
then the immediate list. A model flagged `0x20000` (`func_001621f8`, no caller by name: a pointer use or an
overlay) goes to the immediate list whole.

**The draw list on the host** (session 83, item 4a). src/model/mdlgs.nostrict.c's two walks call
`PlatGsListNode(list, node)` around each node's callback and `PlatGsListEnd(list)` at the end (include/
platform/gs.h; on the PS2 build they are nothing: every out/build object is bit-identical). The null
platform prints `kh1-host: node draw|imm KEY cb CALLBACK arg PAYLOAD` at `KH1_HOST_TRACE=5` before the
node's sends, `kh1-host: node main` before the next main-thread send, `kh1-host: list ... end` and
`kh1-host: vblank N`; **`gsstate.py --nodes`** prints a frame's command order and checks every node
against the key map. Fake disc, stub:2 (6 frames): 13 nodes, **6 distinct, all in the key map**: frame 4's
list is display.c's state packet at 10010 (`D_002BC9F0`) alone; frames 5 and 6 run 10010, renderer B's
reset at 20499, the shadow state at 45499 / 60499 (`func_001274c8`, payload `D_004F8270`), the reset at
70499, and on the immediate list `func_0015f388` at `0x7FFFFFFF`. Between the lists the main thread sends
`D_0061E8B0` (opdma's ZMSK 0 bracket) and `D_00370170`; before the draw list `D_002A6540`, the frame copy
`D_002A6890`, `D_002A65C0`, `D_002A6500`; after the immediate list the HUD / window sends. No models or
texture animations run (no room files on the fake disc). `kh1_gs_flush_pending` (plat_null.c) is called
by every main-thread `PlatGsSyncPath(0)`, ch 1 / 2 `PlatDmaSend`, `PlatDmaPutVif1Chcr` and
`PlatGsPutDrawEnv` outside a node and a handler: **0 found the draw list pending** (the null DMAC runs the
handlers as each transfer ends, so the list is always drained by the time the main thread sends).

### 4.13 The texture animations: CLUT cross-fades (session 83, static)

texanim.c's second task kind (`func_00102978` registers one `func_00102118` task per entry of the room's
background file, `D_002A3F24` of them, from roombg.c `func_00101048`; the file's tables fill `D_0029BE20`
(per animation 32 rows of 16 colours) and `D_002A3E20` (per animation `{a, b, c, d}`: the period, **the CLUT
block offset `v`**, the last frame, the kind)) steps a **palette animation**. Each frame the task updates a
blend factor `f10 = 64 + 64 D_003732D0[...]` (0 ... 128 if the 4096-entry table is the sine, as its
use reads: an eased half period over about `a` steps of `D_002BBDFC`) and moves between two
palettes `p20` / `p24` (kind 0: rows `idx - 1` and `idx`, 16 colours each, ping-ponging between 1 and
`last`; kind 1: rows 0-15 and 16-31, two 256-colour palettes), then inserts seven draw list nodes at
`90000 + 10 id`:

| Key | Node | What the GS does |
| --- | --- | --- |
| +0 | `func_00101f80`, a 3-tag chain (`D_002A4230` / `D_002A4400` copied to the heap, its REFE pointed at `p20`) | upload palette A as CT32 into block `0x3600` (BW 1): 8x2 (16 colours) or 16x16 (256) |
| +1 | `func_00106b98` `D_002A4310` / `D_002A44E0` | `FRAME_1` block `0x3E00` FBW 1 CT32 **`FBMSK 0xFF000000`**, `ZBUF` ZMSK 1, `TEST` ZTST ALWAYS, `TEX1` point, TEXFLUSH, `TEX0_1` `0x3600` CT32 8x2 / 16x16 TCC 1 MODULATE, `ALPHA_1` `(Cs - Cd) As >> 7 + Cd` |
| +2 | `func_00101f30`, `func_00101fc8` / `func_00102070`'s REGLIST packet | **SPRITE TME FST, no ABE**, colour 0x80, at (`D_002A45D0[v % 32]`, `D_002A4650[v % 32] + v / 32 * 32`), 8x2 / 16x16, UV 1:1: copies A's colours over **the CLUT at block `0x3E00 + v`**, its alphas kept |
| +3 | `func_00101f80` (`D_002A4260` / `D_002A4430`, REFE at `p24`) | upload palette B into block `0x3A00` |
| +4 | `D_002A43A0` / `D_002A4570` | the same state with `TEX0_1` at `0x3A00` |
| +5 | `func_00101f30` | the same sprite **with ABE**, vertex alpha `f10 + 1`: `CLUT = A + (B - A) x As >> 7`, `As = At x (f10 + 1) >> 7` |
| +6 | `D_002A45C0` | back to the 3D target: `FRAME_1` `0x1A00` FBW 8, `ZBUF` ZMSK 0, `TEX1` bilinear |

The two tables `D_002A45D0` / `D_002A4650` are the CT32 block order inside a page (block n of a page at x 0,
8, 0, 8, 16, 24, ... y 0, 0, 8, 8, ...), so pixel (x, y) of the 64-wide frame at `0x3E00` is exactly block
`0x3E00 + v`: **`v` names a CLUT block, and the passes rewrite the room CLUT that roombg.c uploaded there**
(8x2 CT32 at `0x3E00 + i`, or the 16x16 ones at every 4th block from n0 to n1, which is why a 256-colour
animation's `v` is a multiple of 4). Who reads it: the room's background meshes, whose TEX0 CBP names these
blocks (the CBPs are in the disc's files: inferred from the upload addresses). Since the passes run at 90000+,
after every room draw (at most 70499), **the room draws see the CLUT the previous frame blended**: a frame of
lag, the console's own. The scratch blocks are free by then: `0x3600` is the field's upload slot
(`func_00106e18` at 10020 / 50000) and `0x3A00` the texspot / shadow buffer (§3.4), both rewritten before
their next use. A port can do the same on the CPU (the blend on 16 or 256 colours of the room's CLUT copy,
alpha kept, before the next frame's draws) or draw it, as host/null/gsmem.c now does (§5.2).

**The texture steps** (session 84, texanim.c's first kind, keys `10000 + n`). `func_00101e70` (from roombg.c
`func_00101048`) registers one `func_00101bb8` task per record of the background file's first table
(`D_002A3F20` records of 160 bytes, copied to `D_0029B420`). A record: `+0` the frame count `n` (u16), `+4`
the destination position (DSAX, DSAY), `+8` the speed `spd` (u16), `+0xA` the kind, `+0x10` BITBLTBUF,
`+0x18` TRXREG (width, height), `+0x20` kind 0's source positions (one word per frame, SSAX | SSAY << 16),
`+0x2C` / `+0x2E` kinds 1 / 2's source (x, y). Each frame `t += D_002BBDFC / spd` (the frame's time step) and
the frame is `t / 2`, wrapping to 0 at `n`; when it changes the task inserts **one node at `10000 + n`**
(`func_001019c8`: send the chain on ch 2, free its two heap blocks, return 2: go on in the interrupt). The
chain is a REF to a fixed GIF tag (`D_002A4160`: NLOOP 1, NREG 5, A+D, then TEXFLUSH; `D_002A4180`: NREG 9)
and a REFE to the step's A+D qwords. Every copy is **TRXDIR 2, local -> local**: nothing comes from the EE.

| Kind | Packet | What the GS does |
| --- | --- | --- |
| 0 (`func_00101a18`) | BITBLTBUF, TRXPOS (source = frame k's word, destination `+4`), TRXREG, TRXDIR 2 | a flipbook: copies frame k's rectangle from a sheet in GS memory over the displayed texture |
| 1, 2 (`func_00101a70`, the same code) | two copies: rows `y .. h-1` of the source to the destination's top, rows `0 .. y-1` below them (h = `n`, y = the frame) | a vertical scroll by y rows, wrapping |

At frame 0 both copies of a scroll are 0 rows high (`(h - 0) % h`), so the destination keeps the last
step's rows for one more step: the console's own small hitch at each wrap (read from the C; a 0-row
transfer copies nothing in gsmem.c and, as far as known, on the GS). These keys sort before the 10010 state
packet only for the first ten steps: **`D_004945F0` (n) counts up for the whole session and is never reset**
(no other write in the main ELF), so later steps land after 10010 / 10020 / 20499 ..., and after about 30,000
steps (one animation stepping every frame: about 8 minutes) after the room's opaque draws at 40000, which
then see the new frame one frame late. A port that keeps the C keeps this order; the draws do not depend on
it beyond that frame of lag. tests/host/gsmem_test.c checks the scroll's copies (`scroll(3, 8)`,
`scroll(0, 8)`).

### 4.14 The grid's three chains: `func_00107d30` cases 0 / 1 / 3 (session 85, static)

Read from the C (src/gfx/grideff.c, grideff.nostrict.c, src/game/field.c `func_00100988`); open question
6.8. The "grid" is the room's cell list from map `.bin` section 1 (`D_002A3F30`, docs/structs.md): +0 the
cell count (`D_00494BB0`, up to 1024), +4 the offset of a 16-byte entry table. Entry 0 is the chains' GIF
template tag (below); **entry `i + 1` is cell i: `{w0, w4}` a DMA tag for its first mesh (A) and `{w8,
w12}` one for its second mesh (B)**, each a `REF` into the section (the address words relocated by
`func_00106ed0`), 0 when the cell has no such mesh. The per-cell runtime record is `D_00494BA8[i]` (16
bytes, in chain 0's table area): +8 the cell's **group bit** `1 << t` (t from the cell's 128-byte texture
record, float at +0x5C), +12 its **state**.

**Six chains, double-buffered by the frame parity `D_00351BD0`.** Each is `ref` record qwc 9 (the 0x90-byte
matrix record: `D_0048BFD0` at parity 0, `D_0048C300` at parity 1, filled by `func_00107ec0`), `ref` qwc 42
(`D_0048C060` / `D_0048C390`: VU 8-47 + `MSCAL 0`), a third qword, then a table of `ref` tags the C fills
each frame and an `end` tag (`D_0047A1D0` / `D_00472150`'s first qword) after the last.

| Case | Chains (parity 0 / 1) | Table filled by | Program, key | Third qword | Draws |
|---|---|---|---|---|---|
| 1 | `D_0046E120` / `D_00472160` | `func_00107548`: visible cells of class 1, mesh A | table index 1 = **P2** (fog), 10020 | placeholder `REF 0 -> D_004862A0`, patched by `func_00106ed0` with section 1 entry 0's tag | the opaque cells, fogged |
| 0 | `D_004761A0` / `D_0047A1E0` | `func_00107548`: visible cells of class 0, mesh A | **P0**, or **P6** when `D_002BC0A8.flags_2.b4` (point light), 10020 | the same placeholder, patched the same | the opaque cells, unfogged |
| 3 | `D_0047E220` / `D_00482260` | `func_00107c48`: every visible cell with a mesh B | table index 3 = **P3** (env map / UV scroll), **50000** | static **`REF 2 -> D_004862B0`**: `STCYCL 1,1; UNPACK V4-32 1 -> @0 +TOPS` of the GIF tag `TRIFAN|IIP|TME|FGE|ABE|CTXT2` (`0x313EC000`, NLOOP 5, REGS `0x412`), `MSCNT`: the clipped-output template with fog, not the map's | the cells' second layer, translucent |

`func_00107548` (key 10020's setup, every frame) culls the cells: a cell whose group bit is not in
`D_002BCC98` gets state 0 (hidden); otherwise `func_00107ab8` (the camera test, read in session 90, §5.4: the cell's 8 box corners against the 4:3 frustum `D_002BBFE0`, far plane = the fog far) gives class 0,
1 or culled (state 0). A visible cell gets state 2, or 1 once its mesh A tag went into chain 0 or 1.
**`func_00107c48` (case 3) then walks the same cells: every cell with state non-zero (1 or 2: so a cell with
no mesh A can still have a B layer) whose entry has a mesh B tag gets state 3 and its B tag in chain 3's
table**; it returns the count, and `func_00100988` queues the P3 upload and chain 3 at key 50000 only if
it is non-zero (`D_0029B2F0`). Cases 0 / 1 sort the tags front to back when `D_002BC0A8.flags_3.b2`
(`func_001072c0` / `func_001073f0` on the cells' camera z); case 3 keeps the cell order.

**Key 50000's order** (draw-list nodes run in insertion order within a key): the state packet `D_0029B200`
(**`ZBUF_2` ZMSK 1**, `TEST_2 0x5000D`, §4.11), the map texture upload `func_00106e18` if the room has an
animated frame set, **P3 + chain 3**, then `func_00108708`'s fade groups, then 50100's restore. So mesh B
is drawn after every opaque draw (10020-40000), blended (ABE), fogged (FGE) and **without Z writes**, with
P3's texture coordinates: the sphere map from the normal (batch flag `0x11`) or the UV scroll (flag n,
§2.2.1's table). (Inferred from that: water surfaces, glass, glints and scrolling overlays laid over the
opaque cells. A boot that hides chain 3 would show which.)

**The fade groups reuse chain 3's head as a template** (`func_00108708`, `func_001081c8`,
`func_001083d8`). Up to 32 groups k (`D_00494C00[k]`: x the time left, y the intensity, z the rate) fade a
group of cells in or out: the script starts one with `func_00108650(k, n)` (vm_lib.c: hide the group, fade
out over 2n), others count up and set the group's bit in `D_002BCC98` at the end (`func_00108180`). For
each running group the C writes two chains into the parity's case 0 / 1 table area, starting in the table
of the **shorter** of the two lists at 64 bytes per entry of that list (`D_00476210[n]` / `D_0046E190[n]`
at parity 0, `D_0047A250[n]` / `D_004721D0[n]` at parity 1: past the list and its end tag): a copy of chain 3's first two qwords with the record replaced by a per-group
144-byte record (`D_002B2E60[k]` / `D_002B5260[k]`: the object matrix, `D_002BC170` with qw2.w = the
intensity y), the third qword `D_004862D0` (`REF 2 -> D_004862B0`, the same FGE fan template), then the
group's cells' **mesh A tags drawn by P7** (the forced `TRISTRIP|IIP|TME|FGE|ABE|CTXT2` PRIM) and a second
chain with their **mesh B tags drawn by P3**, all at key 50000 after chain 3. A Vita renderer can treat
chain 3 and the fade groups as one translucent pass over the grid: per cell, layer B with P3's texcoords,
and the fading groups' A and B layers scaled by y.

**Sizes**: each table is 0x4010 bytes (1025 tags), so 1024 cells and the end tag fit; the fade-group
chains share the case 0 / 1 tables' tail with the per-frame lists, unbounded by the C (the room data keeps
it in range on the console; shiftable-plan.md "Session 24" for why these chains are one piece each).

### 4.15 Frame pacing and the system-message band (session 86, static)

Read from the C; not checked on a console or a host run. Answers open questions 9 and 10.

**The vertical blank** (`func_00110218`, display.c) is the game's `sceGsSyncVCallback` handler, set by
`func_00110458` (`func_00266a10`). Each field it reads CSR.FIELD into `D_002BBDE8`, counts the
frame counters (`D_002BBDF0` the scene clock, held while `D_002BD114` (a system message, below) or
`D_002BCC24` is set; `D_002BBDF4` the play time; `D_002BBDF8` free-running; **`D_004D90F4` the fields
since the last frame end**) and calls `func_0010c378`, which signals semaphore `D_00495258` if
anything waits on it (`PlatIReferSemaStatus`, `PlatISignalSema`).

**The frame end** (`func_001104e0`; every main-loop state calls it once a frame, gamestate.c's state
macro, framectl.c, pause.c, the boot, the sound waits): `func_0010c348` signals the worker thread
(`D_00495260`: util/thread.c runs up to two queued callbacks, `D_002B75A0`) and waits for the next
field (`D_00495258`). Then, if fewer than `D_002BBE0C + 1` fields have passed, it waits
`D_002BBE0C` more. So **`D_002BBE0C` is the frame interval minus one**: 1 (30 fps: two fields a
frame) from a room's start (roomload.c `func_00113558`), the movie / title states (gamestate.c) and
the pause's resume; 0 (60 fps) in the pause (`func_00114250`), the game over and the reset
(`func_00110458`). A frame that already took longer does not wait more (no catch-up).

**The time step** `D_002BBDFC` = fields passed x `D_002BBDEC` x `D_002BBE00`: `D_002BBE00` the
script's game speed (vm_lib.c: percent / 100; objscmd.c sets it; 1.0 at a state reset); x 2 when
`D_002BBE10` (only ever cleared: no writer in the main ELF); capped at 5.0, or 128.0 while
`D_002BC740 == 1` (`D_0037A378.b0`, the field's flag that also makes the frame copy black:
`func_00106000`). 98 places in src/ read it: the game's per-frame delta in 1/60 s units. Then
`D_004D90F4` = 0.

**`D_002BBDEC` is not a 30 / 60 switch**: it is the time a field is worth in 1/60 s, written once,
1.0, by `func_00110068` (the only store in the main ELF). `func_0010fea0` sets the play-time cap
`D_004D90F0` from it: **`0x14996C4`** (21,600,964 fields: 100 hours at 60 Hz, plus 964) at 1.0,
**`0x112A84E`** (18,000,974: 100 hours at 50 Hz) otherwise, so the else is a 50 Hz build's value
(1.2: inferred, never set in this NTSC-J build). The vblank counts `D_002BBDF4` up to the cap; at it,
while the save's lap count (`D_002BCB60->w15c`, `func_00111798`) is below 3 it runs on 60 more fields,
then adds a lap (`func_001117b8`) and starts again from 0; from the third lap it holds at the cap.
playtime.c reads `D_002BBDF4 x D_002BBDEC` as hours (216,000) / minutes / seconds.

For the port: run the frame loop off the display's vertical blank with the same two numbers: wait one
field, then up to `D_002BBE0C` more, and feed the elapsed field count into the same formula. On a 60 Hz
Vita display with vsync the 30 fps states keep their pacing. The field parity `D_002BBDE8` is written
by the handler and read by nothing in the main ELF (the overlay check).

**The system-message band** (`func_0010f5f8`; the same writes in screen/fade.c `func_001137f8`):
`PMODE = 0xFF03` turns on both read circuits with circuit 1 on top at fixed alpha 0xFF (MMOD 0, ALP
0xFF: opaque); `DISPFB1 = 0x11B0` is FBP `0x1B0` = **block `0x3600`**, FBW 8 (512 pixels), PSMCT32;
`DISPLAY1 = 0x0007F9FF020D227C` is DX 636, DY 210, MAGH 4 (5 clocks a pixel), DW 2559 (512 pixels),
DH 127: **a 512 x 128 band** in the middle of the screen. Circuit 2 keeps showing the last game frame.
The band's pixels are drawn into the texture slot at block `0x3600` by `func_0010f580` / `func_0010f5a8`
/ `func_0010f5d0` (the static packets `D_002BBC20`, `D_002BBCF0`, `D_002BBD30`) and the message font
(`func_001fd100`, `func_001f1ed8` with the strings `func_001efc10(n)`). `func_0010f658(0)` ends it:
`PMODE = 0x22` (circuit 2 only, MMOD 1). Who shows it: `func_0010f918` (framectl.c), each frame from the
main loop, runs a loop of its own while any of `D_002C5968`'s three flags is up, with the game frozen
(`D_002BD114` = 1: the scene clock stops) but the pads, the sound and the frame end running:
- b0, **no controller** for 31 frames (pad/padread.nostrict.c): message 1;
- b1, **the disc error** (io/cdqueue.c, from the sound status block's +0x1C08 for more than 30 frames,
  docs/sound-spec.md 2): message 2;
- b2, **a read error** (io/discfile.c, which waits on the loader thread until it is cleared): message 3,
  then message 4 once pad 2's `0x2000` button is seen (`D_004D5B0C`), and the flag is cleared;
- and screen/fade.c's `func_001137f8` (the pause's colour overlay) draws five strings, `func_001efc10(5)`
  to `(9)`, 32 pixels apart at y 54 into the same band (inferred: the pause's title).
The pause screen (pause.c `func_00113e28`) is started with the flags (`fl`) when the loop starts and
ended with 0. For the port: one 512 x 128 overlay composited opaque over the frozen frame at the
DISPLAY1 rectangle (scaled with the frame), cleared when PMODE goes back to 0x22.

**The `0x118000` area** (open question 10's other half): `func_00106000` case 2 copies a 512- or
640-wide frame from `TBP0 0x1180` (`0x118000`) to the display (`func_001110d0` = the movie overlay's
`entry(3, 0)`, the movie's width) and sets the display to that width (`func_0010fee8(v, 448)`). Case 2 is
`D_002BBE04 == 2`, and **no code in the main ELF stores 2** (its writers store 0, 1, 3 and 4: the
script's screen effects 1 / 4 (objscmd.c `func_0012b450`, vm_lib.c), 3 after a movie (dkmovie.c
`func_001111b0`, gamestate.c's state macro), whose case 3 clears to black and goes back to 0). So the
movie frames reach the screen through `0x118000` and case 2 only when the movie overlay dkmovie.x sets it
(inferred; for the overlay check, vita-port-plan 5.2). `func_0010b6c0` (objwin.nostrict.c) also draws
there (§3.1).

### 4.16 The script's screen spin: `func_00102da8`, the frame copy's cases 1 / 4 (session 87, static)

Read from the C (src/gfx/sceneeff.c, src/screen/brightfade.c `func_00106000`, src/vm/objscmd.c
`func_0012b450`, src/vm/vm_lib.c) and the two static packets (`gs_packets.py -v 0x2a4ed0 0x2a4fc0`); not
checked on a console or a host run. The name "spin" is a guess from the code.

**Who turns it on.** `D_002BBE04` selects the end-of-frame copy (`func_00106000(D_002BBE04)`, gamestate.c,
once a frame). Two script commands store 1: the object script's `func_0012b450` (objscmd.c, the command
table `D_002E2810` + 0x508) from a 40-byte record, and the event script's `func_001cde38` (vm_lib.c) with
the defaults in brackets:

| Variable | From the record | Meaning |
| --- | --- | --- |
| `D_002BC080[0..3]` | `c[0..3] x 128` (128, 128, 128, 64) | RGBA of the copy: 128 = 1.0; the alpha is the blend weight |
| `D_002BC090`, `D_002BC094` | `+0x10`, `+0x14` (256, 192) | the centre, screen pixels |
| `D_002BC0A0`, `D_002BC0A4` | `+0x18`, `+0x1C` (0, 0) | an offset added to the centre |
| `D_002BC098` (f32) | `+0x20` degrees, to radians, wrapped to [-pi, pi] (`func_00120c88`) (0) | the end angle |
| `D_002BC09C` (s32) | `+0x24` (1) | frames to reach it |

vm_lib's `func_001cdea8` turns 1 into **4** (only when it is 1); `func_001cded0` and objscmd's
`func_0012b530` store 0 (off). `func_00106000`'s first switch calls `func_00102da8(D_002BBE04)` for 1 and
4 and clears the frame count `D_002BC730` for every other value, so each start ramps from 0 again.

**Each frame** (`func_00102da8`), before the global colour quads and the frame copy of §4.15:
1. **Case 4 only**: `D_002A4ED0` copies the **display buffer** (block 0, PSMCT24, 512 x 448: the frame
   on screen) into the 3D target at block `0x1A00` (FRAME FBP `0xD0`), one opaque `SPRITE|TME|FST`
   UV (1, 0)-(513, 448) to (0, 0)-(512, 384), bilinear: **this frame's render is replaced** by the last
   frame shown, shrunk 448 to 384 lines. Case 4 is a frozen picture that keeps spinning.
2. The angle: `f = D_002BC730 x (D_002BC098 / D_002BC09C)`; when it passes the end angle it is held there,
   otherwise the count goes up. So a positive angle ramps over `D_002BC09C` frames and stays. **A
   negative angle never ramps**: at count 0 `f = 0` is already above it, so it is used at once (and the
   count stays 0).
3. The quad: the screen rectangle (512 x 384) centred at (`D_002BC090 + D_002BC0A0`, `D_002BC094 +
   D_002BC0A4`) (`func_00102cc8`), its corners taken to the screen centre's origin (-256, -192), turned by
   `f` about Z (`PlatVu0RotMatrixZ` of the unit matrix `D_002BCAF0`, `func_00102d20`) and put back
   (x 16, + 4096 / 3072, then + 28664 / 29680: the `0x7000` / `0x7400` origin less half a pixel
   across and one pixel down).
4. `D_002A4FC0` draws it into the target: `TRISTRIP|TME|ABE|FST`, the texture the **display buffer**
   again (UV 0.5-512.5 x 0.5-448.5, bilinear, CLAMP), `ALPHA (Cs-Cd)*As>>7+Cd` with RGBAQ = `D_002BC080`
   (`D_002A4F60[3]`; the packet's own 16 alpha is overwritten), ZTST ALWAYS. The same strip is sent 16
   times, each under a 32-pixel-wide SCISSOR column (`D_002A46D0`-`D_002A48B0`, x 0-31 ... 480-511): the
   texture-cache-friendly way to draw a full-screen copy, one draw in a port.

Then the frame copy (`D_002A6540`, `D_002A6890`) shows the target. Because the texture is the frame
shown last, **the effect feeds back**: each frame holds a turned, faded copy of the one before, which held
one of the one before that. With case 1 that is a spinning trail over the live scene; with case 4 over
a still picture (the image swirls into itself). The corners the turned quad leaves uncovered keep this
frame's pixels.

**For the port.** Keep the last presented frame as a texture (the 512 x 448 image the copy wrote, or the
presented image at any size). Per frame with the effect on: (case 4) draw it over the whole scene target,
opaque; then one quad, 4:3 like the target, offset by (centre + offset - (256, 192)) and turned by `f`
about the target's centre, textured with the last frame, colour `rgb / 128` (modulate x 2 as in §5),
blend `SRC_ALPHA, ONE_MINUS_SRC_ALPHA` with alpha `a / 128`, depth test off; then the usual copy. Rule 7
(portability.md): with `D_002BC09C = 0` the EE's `x / 0` is the largest float and `0 x FLT_MAX = 0`, so
frame 0 is unturned and frame 1 is at the end angle; IEEE gives `0 x inf = NaN` for frame 0 (a NaN quad).
The two defaults (vm_lib 1 frame) never divide by 0; an object script record with `+0x24 = 0` would, so
clamp the count to at least 1 (or compute the step the EE way) in the port.

### 4.17 The other full-screen effects: the menu blur, depth blur, sway, lens grid, fades, letterbox (session 88, static)

Read from the C (src/gfx/sceneeff.c / sceneeff.nostrict.c, src/game/pause.c, src/game/field.c, src/game/roomload.c,
src/screen/brightfade.c, src/screen/display.c, src/vm/vm_lib.c / vm_lib.nofill.c) and the static packets
(`gs_packets.py -v 0x2a4b60 0x2a4dd0 0x2a5620 0x2a5a90 0x2a5ac0 0x2a5fd0 0x2a6110 0x2a6070 0x2a61e0 0x2b6760`); not
checked on a console or a host run. The names are guesses from the code. **Session 88 corrects three older
readings**: `func_00102a48` is not "rings of glow" but the field menus' blur, `func_00103058` uses no PSMT8H
texture (the block `0x1800` rows of §3.1 / §3.2 are `func_0010b6c0`'s and `func_0010ea70`'s), and P8's grid (§2.4)
is a script effect, not a test screen.

**Where they run.** Field init (`func_00100360`, field.c) registers `func_001039f8` (the fade) at task key
`0x280A3` for good and sets the sway speed `D_002A6200 = 0.05`. The field's per-frame task `func_00100448`
(key `0x1D4C0`) re-registers the others for one run each frame while their flag is set: `D_002A61F4` ->
`func_00103058` (depth blur, `0x280A2`), `D_002BC734` -> `func_001032b0` (sway, `0x280A4`), `D_002BC738` ->
`func_00103c48` (lens grid, `0x280A4`); each returns 4 (dropped after the run). So they draw after the immediate
list (`0x27CB8`) and before renderer B's build (`0x2E630`), into the 3D target, with the previous frame's draw
list finished (`func_00106b18`'s sync, §4.12). **The depth blur reads the Z buffer and runs first; the sway and
the grid then overwrite the Z buffer's memory with a colour copy** (`D_002A5CE0`: the target `0x1A00` copied as
PSMCT24 to FBP `0x70` = block `0xE00`, `ZBUF ZMSK=1` meanwhile), so every depth-tested draw later in that frame
(keys above `0x280A4`, for example a text window sent with flag `0x10`, `ZTST GEQUAL`, §3.2) tests against colour bytes. A port
copies the target to a separate texture instead and keeps its depth buffer; check on a boot whether anything
drawn after them looks wrong in the rooms that use them. `func_001103a0` (display.c, the state reset) clears
`D_002A61F4`, `D_002BC738`, the fade and the letterbox (`D_002A6204`, `D_002A61F0`, `D_002A6208`), not
`D_002BC734` (the room load sets that one).

**The menu blur** (`func_00102a48(c, o)`, pause.c). When a field menu opens (`func_00114280`, state 1 -> 2;
the menu `D_002BD118` picks: the in-game menu `func_0020d6c8` and four others) the task
`func_00113f60` (key `0x2E644`) captures the frame: `func_0010a3e8` draws the display buffer (block 0, read as
CT32, 512 x 448) at half size into block `0x3600` (FBP `0x1B0`, FBW 256, bilinear, `D_002B6760`) and stores that
256 x 192 PSMCT24 image to a heap buffer (`D_002B6778`, `0x24000` bytes, `PlatGsExecStoreImage`). Each call of
`func_00102a48` loads it back to `0x3600` (`func_0010a470`: the slot is shared, §3.1), scans the buffer for any
non-zero word (`0x9000` words, CPU) and, if all are zero, draws one opaque black sprite (`D_002A4DD0`); otherwise
`D_002A4B60` draws **nine sprites of the half-size image over the whole target** (512 x 384, bilinear, CLAMP, ZTST
ALWAYS, `ZMSK=1`; under the 16 scissor columns of §4.16): one opaque at (-2, -2) px, then four at alpha 64 at
(+-o, +-o) (order (-,-), (+,+), (-,+), (+,-)), then four at alpha 32 at (0, -o), (-o, 0), (0, +o), (+o, 0), each
blended `(Cs-Cd)*As>>7+Cd` (alpha 64 = half, 32 = a quarter), colour `c` (128 = 1.0; every caller passes 128).
`o` is in 1/16 pixel: the pause steps it 1 px (`0x10`, the capture frame and the next, `func_00113f18` at
`0x2E643`), then 2 px (`0x20`, `func_00113ee0` at key `0x2903` each frame while `D_004D9330 == 4`, the menu
open); closing steps back 1 px (`func_00114028`, `0x2E645`) and 0 (`func_00113fa8`, `0x2E643`, which frees the
buffer). `func_00114068` (2 px) has no main-ELF caller (overlay check). The sequential blends give the copies
the weights 0.0198 (the opaque one and the first diagonal), 0.0396, 0.0791, 0.158 (the diagonals in order) and
0.105, 0.141, 0.188, 0.25 (the sides): not a symmetric kernel (its centre is about 0.2 o right of the opaque
copy). **For the port**: keep the captured frame as a 256 x 192 texture (any size: it is shown bilinear-scaled)
and draw the same nine blended quads, or one pass with those nine weights; skip the CPU zero scan (a black
capture blurs to black anyway, the scan only saves the draws).

**The depth blur** (`func_00103058`, flag `D_002A61F4`). Event script commands (vm_lib.c): `func_001d1400` on,
`func_001d1418` off, `func_001d1428` the mode `D_002A61F8`, `func_001d1450` the depth `D_002A61FC` (a raw Z24
value, the packets' default 40000; larger Z is nearer, §3.2). The packets write `z` into every vertex, then:
- **Mode 0** (`D_002A5A90`, then `D_002A5AC0`): the target is drawn at half size into block `0x3600` (CT32,
  bilinear, FBW 512); then the nine-copy blur of the menu (fixed o = 2 px, alphas 128 / 64 / 32, base (-2, -2)
  px) is drawn back over the target at depth `z` with `ZTST GEQUAL`, `ZMSK=1`, `ATST GREATER 0` (always true: the
  texture is read as CT24, alpha from the vertex): **only pixels at or behind the depth are replaced by the
  blurred copy**, a hard-edged background blur (depth of field).
- **Mode 1** (`D_002A5620`, then `D_002A5AC0`): first the target's **alpha only** (`FBMSK=0xFFFFFF`) is set to 128
  everywhere (`D_002A5250`), then to 0 where `z` passes `GEQUAL` (`D_002A52B0`: behind the depth); the half-size
  copy then keeps that mask (CT32), and the blur reads it as texture alpha (`TCC=1`, `ZTST ALWAYS`): **the near
  part is blurred**, with its blurred edge spilling over the far pixels, and the far part stays sharp.
- Port: mode 0 = a depth-tested composite of a blurred half-size copy (depth >= threshold in GS terms = farther
  than the threshold); mode 1 = a mask from the depth buffer (near = 1), blurred with the image, used as the
  blend weight. Both need the scene's depth as a texture or a depth test against it at this point of the frame.

**The sway and colour pulse** (`func_001032b0`, flag `D_002BC734`). The room table sets the flag on a room load
(`func_001124f8`, roomload.c: `D_002BC734 = D_002BCDAC[room].fl.b1`, with `func_00103280(1, 1, 1, 1)`: no
pulse, and `func_00110e38(1, 0.9, 1, 0.05)`, another colour setting); the event script turns it on with four
values (`func_001d9780`, each / 100) or off (`func_001d9830`), and `func_001d5f18` sets the sway speed
(`D_002A6200`, / 100). Each frame: the target is copied into the Z buffer's memory (`D_002A5CE0`, above), then one
opaque `TRIFAN|TME|FST` quad over the whole target (`ZTST ALWAYS`, `ZMSK=1`, 16 scissor columns, `D_002A48D0`
restores `SCISSOR` and `ZMSK=0`) reads that copy back (`TEX0 TBP0=0xE00` CT24) from the inset rectangle
`[u0, 512 - u0] x [v0, 384 - v0]` texels with `u0 = (64 + 48 cos a) / 16`, `v0 = (64 + 48 sin a) / 16` (1 to 7
texels), `a += D_002A6200` radians a frame (not the time step), wrapped to [-pi, pi]. So **the picture is
zoomed by 0.3 % to 2.7 % across and 0.5 % to 3.6 % down, the two out of phase**: a slow breathing stretch (a
126-frame period at 0.05, about 4 s at 30 fps; an underwater room is a guess). The colour is the vertex RGB
(modulate): with `D_002A6210 = (r, g, b, s)` and `s != 1.0`, each channel's phase `D_002A6220[i] += s` (the three
start at 0, so they stay equal) and the channel is `(k + (1 - k) cos phase) x 128`, clamped at 0 (`k` the
channel's value): a pulse between `2k - 1` and 1.0. `s == 1.0` (the room load) means no pulse (128, 128, 128).

**The lens grid** (`func_00103c48`, flag `D_002BC738`, VU1 P8 of §2.4). `func_001d6658` (vm_lib.nofill.c) sets
the flag, the amplitude `D_00494A70` and the distance `D_00494A74`; `func_001d66b8` clears it. Each frame: the
target copy into the Z area (`D_002A5FD0`, as the sway), `D_002A6110` (`CLAMP` REGION_CLAMP U 0-510, ZTST
ALWAYS, `ZMSK=1`), then the P8 chain draws a 25 x 25 grid textured with the copy: positions x, y in -192 ... +192
(16 apart), UVs u 64 ... 448, v 0 ... 384 texels (the target's centre 384 x 384 square, the sides keep the scene),
`z = sc x (S[2048 + 81 i] + S[2048 + 81 m])` with `S` = `D_003732D0`, the 4096-entry sine table, so `z = -sc x
(sin(pi i 81 / 2048) + sin(pi m 81 / 2048))`. The camera (`func_00103b68`: position (0, 0, -512), looking down +z,
up +y, `D_002A6080`-`D_002A60B0`) and `ViewScreenMatrix(512, 1, 1, 2048, 2048, 1, 16777215, 1, 65536)` make the
flat grid at distance 0 a 1:1 copy; the world matrix moves it by (0, 0, `D_00494A74`) (farther: smaller). With
`sc > 0` the middle comes up to 2 sc nearer the camera: **a magnifying bulge**. The shape does not move by
itself (no time term: the script animates it by changing the values), and it is not symmetric: row and
column 0 sit at sin 0 but row and column 24 at sin(0.949 pi) = 0.16, so three edges lift a little. A port draws
the same 25 x 25 mesh (or the same function in a shader) over a copy of the target, keeping the table's indices.

**The fades** (`func_001039f8`, key `0x280A3`, always registered). A full-screen untextured `SPRITE|ABE`
(`D_002A6070`, ZTST ALWAYS) of black (`D_002A61F0 = 0`) or white (1) with alpha `D_002A6204`, drawn when it is not
0. The counters run in time steps (`D_002BBDFC`, 2 a frame at 30 fps): `func_001038b0(n)` (task `0x280A2`
`func_00103838`) takes the alpha from 0 to 255 over `2n` steps and holds it there (fade out), `func_00103988(n)`
(`func_00103920`) from 255 to 0 (fade in). Script commands: `func_001d5010` / `func_001d4fc0` black out / in,
`func_001d5118` white out, `func_001d5090` white in **plus a countdown** (`func_001d5060`, key 50000, once a frame,
not time-stepped) that sets the colour back to black after `n` frames; capture.c's `func_0010a0d8` starts a
one-frame fade out when the global colour `D_002BC070` is not 128. **The alpha goes to 255, not 128**: with
`COLCLAMP=1`, `(Cs-Cd)*As>>7+Cd` is already full black / white at 128, so the visible fade is the first half of a
fade out and the second half of a fade in (`n` steps of `2n`). Port: blend with `min(alpha, 128) / 128`
(clamping the result as the GS does gives the same picture). Rule 7: at 60 fps (a time step of 1) the white
fade in's countdown ends half-way through the fade and turns the remaining white overlay black (a dark flash);
at 30 fps the two end together. Tie the countdown to the fade, not to frames, in a port that runs at 60.

**The letterbox** (`D_002A6208`, drawn by brightfade.c `func_00106000` before the frame copy, `D_002A61E0`): two
untextured `SPRITE|ABE` bars, y 0-34 and 350-384 of the 384-line target (about 40 of 448 lines each after the
copy's stretch), blended `(Cd-Cs)*As>>7+0` with black: the destination times `As / 128`, so alpha 128 leaves
the picture and 0 makes the bars black. `func_00104300(n)` (bars in) sets the flag and adds `func_00104298` to
the list `D_002BC720`: the alpha goes 128 -> 0 over `2n` steps and stays 0; `func_001043f8(n)` (bars out,
`func_00104388`) takes it 0 -> 128 and then clears the flag. The event commands `func_001ceee8` (16) /
`func_001cef20` (n) / `func_001d07a8` (1) put them in and set bit 0 of `D_00389C90.f3078` (an event-mode flag),
`func_001cef80` / `func_001cefb8` / `func_001d07e0` take them out and clear it. Port: two black quads with alpha
`1 - a / 128` over the scene, before the HUD (the HUD draws later in the frame, over the bars).

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
| PSMT4/8 + CLUT | decode to RGBA8 at load, or a palette texture + shader lookup: **the room's CLUTs at `0x3E00` + v are animated every frame (§4.13)**, so either re-decode the textures that use an animated CLUT or keep those as index textures with a palette |
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
| The script's screen spin (`D_002BBE04` 1 / 4, §4.16): the last shown frame turned and blended back | keep the last presented frame as a texture; one turned quad before the final pass |
| Interlace/field mode, DISPLAY offsets | ignore; present progressive frames |
| `sceGsSyncPath` busy-waits | remove (single-threaded command replay) |

### 5.1 The GS register file the port keeps (session 78, draft)

The game writes GS registers as **state**, not with each draw: the HUD sends a whole environment
before it draws (§4.7), the text windows send a header and then sprites, opdma's set-up packet
heads the frame's lists (§4.8). So the port's GIF parser keeps a register file, updated by every
A+D / PACKED / REGLIST write and the GIF tag's PRE, and turns each vertex kick into a draw with the
state as it stands. Which registers it keeps, from every value the static chains, the seeds (§4.8),
the fake-disc run (§4.7) and the session 15 dump (§3.3) write:

| Register | Kept | Values seen | What the port does with it |
| --- | --- | --- | --- |
| `PRIM` | one (CTXT bit selects the context) | `TRISTRIP` / `TRIFAN` / `SPRITE` / `LINE` with IIP, TME, FGE, ABE, FST, CTXT2; the text windows only `SPRITE` / `TRISTRIP`, always ABE (§4.9) | primitive and vertex format; a PRIM write restarts the vertex queue; PRIM 0 with no vertex is harmless (opdma) |
| `PRMODECONT`, `PRMODE` | dropped | `PRMODECONT=1` always; `PRMODE` never written | PRIM's attribute bits always rule |
| `RGBAQ`, `ST`, `UV`, `XYZ(F)2/3`, `FOG` | the vertex being built | | vertex attributes (RGBA 0x80 = 1.0; ST/Q; XY 12.4 minus XYOFFSET) |
| `FRAME_1` / `FRAME_2` | per context | FBP `0x000` CT24, `0x8C` CT24 640, `0xD0` CT32 (3D target), `0x1B0`, `0x1D0` FBW 256 (off-screen), `0x1F0` FBW 64, `0x70` (Z area as colour); FBMSK 0, `0xFFFFFF`, `0xFF000000` | selects the render target (§3.1's addresses map to GPU targets); FBMSK to the colour write mask |
| `ZBUF_1` / `ZBUF_2` | per context | ZBP `0x70` Z24 (and `0x0` once); ZMSK 0/1; Z16S `0x380000` in the shadow pass (§3.3) | depth target and depth write |
| `TEST_1` / `TEST_2` | per context | renderer A's TEST_2 from the C: `0x31001`, `0x5010D` (AREF 16), `0x507FD` (AREF 127), `0x5000D`, `0x50000` (§4.11); 11 + 4 values: ATST ALWAYS/NEVER/GEQUAL/GREATER/LESS/NOTEQUAL, AREF 0/16/120/127/128, AFAIL KEEP/FB_ONLY/ZB_ONLY, DATE/DATM, ZTE 0/1, ZTST ALWAYS/GEQUAL/GREATER | alpha test as a shader discard against AREF/128; AFAIL as write masks on the failing fragments (two draws where it is not KEEP); DATE as stencil; ZTST to the depth function (ZTE 0 = ALWAYS) |
| `ALPHA_1` / `ALPHA_2` | per context | five equations (§3.2 ALPHA), FIX 0 / 128; the window bevel's subtractive `(0-Cs)*As+Cd`, written **inside a strip** (§4.9) | blend state (§5's rows); keep A/B/C/D and FIX as a key; a write between a strip's kicks splits the strip |
| `TEX0_1` / `TEX0_2` | per context | 24 static values (CT32, CT24, PSMT8, PSMT8H, PSMT4, PSMT4HL); `TEX0_2` only from the model data | the texture key (TBP0, TBW, PSM, TW, TH, CBP, CPSM, CSA) into the decoded-texture cache; TCC / TFX to the shader; CLD decides when the CLUT is (re)read |
| `TEX1_1` / `TEX1_2` | per context | MMAG/MMIN 0 or 1; LCM 0/1; MXL 0 everywhere | sampler filter; no mipmaps (drop LCM, MXL, L, K, MTBA) |
| `TEX2_1` / `TEX2_2` | into TEX0's PSM and CLUT fields | the HUD's environment (PSMT8, CBP 0, CLD 1); the text headers (PSMT8, CBP `0x3FFC` / `0x3DFC`, CLD 2); **one per glyph** (PSMT4HL or PSMT4HH, CSA 0 / 1, CLD 0) and per window part (PSMT4, CSA 0 / 3 / 4) (§4.9) | a palette or 4-bit-half change without a texture change: the texture key takes PSM and CSA from it |
| `CLAMP_1` / `CLAMP_2` | per context | REPEAT, CLAMP, REGION_CLAMP (U 1..255, 0..510, the atlas windows of §3.3), REGION_REPEAT (mask 255) | sampler wrap for REPEAT / CLAMP; REGION_* in the shader (clamp or mask the texel coordinate) |
| `XYOFFSET_1` / `XYOFFSET_2` | per context | (1792, 1856) main; (0, 0) texspot's 256 pass; 1920 the shadow pass | subtracted from vertex XY before the viewport transform |
| `SCISSOR_1` / `SCISSOR_2` | per context | 20 values (512x384, 512x448, 640x448, 256x256, sceneeff's 16 strips); per draw from the windows' clip rectangles (§4.9) | scissor rectangle |
| `FOGCOL` | one | per draw (renderer B); renderer A's once a frame at key 10010 from `D_002BC0F0` (§4.11; rgb (16,112,128) is only display.c's initial value) | fog colour uniform |
| `TEXA` | one | TA0/TA1 128/0, 0/128, 128/128; AEM 0 | the alpha a CT24 (TA0) or CT16 texel gets; apply when decoding or as a uniform |
| `TEXCLUT` | dropped | never written; CSM 0 everywhere | |
| `SCANMSK` | dropped | 0 only | |
| `DTHE`, `DIMX` | dropped | DTHE 0 (dither off) | |
| `COLCLAMP` | dropped | 1 (clamp): what a UNORM target does | |
| `PABE`, `FBA_1` / `FBA_2` | dropped | 0 | |
| `MIPTBP1_x` / `MIPTBP2_x` | dropped | 0 (no mipmaps) | |
| `TEXFLUSH` | dropped | 0, after each upload | the texture cache is invalidated by the upload itself |
| `BITBLTBUF`, `TRXPOS`, `TRXREG`, `TRXDIR` + IMAGE | one transfer state | host->local only; DBP the slots of §3.1, PSMCT32 / PSMT8 / PSMT4 / PSMT4HH / PSMT4HL | an upload: write the pixels into a 4 MB model of GS memory (swizzled per PSM), and drop the cached textures it overlaps (on the host since session 80: §5.2) |
| `SIGNAL`, `FINISH`, `LABEL`, `HWREG`, `TRXDIR` local->host | not seen | | |

**On the host** (session 79): host/null/gsregs.c is this table as code. host/null/dmawalk.c's GIF
reader hands it every A+D, PACKED (each descriptor's packed format: RGBA bytes with the Q the last
ST left, 1.0 at each GIF tag; XYZF's Z and F from bit 4; ADC to XYZ(F)3) and REGLIST write and each
tag's PRE; it keeps the registers above (per context; TEX2 into TEX0's PSM and CLUT fields; PRMODE
when PRMODECONT is 0, which nothing writes), counts the dropped ones, and counts each vertex kick
against the draw state in force (PRIM's attributes, the context the CTXT bit picks, with TEX0 /
TEX1 / CLAMP / TEXA left out without TME, ALPHA without ABE, FOGCOL without FGE) and each drawing
kick by the primitive's vertex count (lists start again, strips and fans keep their vertices,
XYZ(F)3 queues without drawing: a strip's ADC vertices enter the queue and the next XYZ2 draws with
them, as PCSX2's vertex kick does). The registers stay across sends, as on the GS. `kh1_gs_state()`
reads them, `kh1_gs_draws()` the states; `KH1_HOST_TRACE=5` prints each send's draw states and
`tools/host/gsstate.py RUN.txt --draws` lists a run's. tests/host/gsregs_test.c (in `make test`):
the HUD environment then a sprite in the next send, ZTE 0, PRIM 0 with no vertex, TEX2 changing
only PSM and the CLUT fields, CTXT 2, strip and list counts, REGLIST, ADC, PRMODE; session 81 added
§4.10's field text (a REGLIST header writing PRIM as a register, a REGLIST glyph tag with no PRE whose
PRE bit and PRIM field are ignored), the list frame's three ADC-restarted strips in one tag (18 kicks,
12 triangles) and an XYZ3 in a fan: the model already did what the GS does, nothing changed. It does
not see VU1's XGKICK output (renderer A / B meshes, PATH1): on the host a send meets the state the
sends before it left, in send order, which is the console's order too (§4.12).

GS memory itself has to be modelled, not just the uploads (done in §5.2, the targets since session 81): the game reads its own targets back
as textures (the 3D target `0x1A00` for the frame copy and post effects, the shadow / texspot
buffer `0x3A00`, the Z area drawn as colour at `0x0E00`), and packs the message font into the Z
buffer's top byte (PSMT4HL / HH at `0x1000`). The port maps each FRAME / ZBUF range to a GPU target
and resolves a TEX0 that lands in one to that target's texture; any other TEX0 decodes from the
memory model through the cache. Still to confirm on a run: the text windows' sprites (read from the C in §4.9; the run shows the
values the C computes), renderer A's mesh chains, and whether an overlay writes registers this
table drops (dktitle.x).

### 5.2 GS memory on the host (session 80)

host/null/gsmem.c is the memory model 5.1's last paragraph asks for, the third step of the port's GIF
parser after dmawalk.c's reader and gsregs.c's register file: 4 MB laid out the way the GS lays out each
pixel storage mode, written by the uploads and read back as RGBA8 for a TEX0.

- **Layout** (`kh1_gsmem_addr`): pages of 8 KB (CT32 / CT24 / T8H / T4HL / T4HH 64x32 pixels, CT16 64x64,
  T8 128x64, T4 128x128), 32 blocks a page (CT32 / T8: 8x4 blocks in the order x0 y0 x1 y1 x2; CT16 /
  T4: 4x8 in the order y0 x0 y1 x1 y2), pages across by BW (T8 / T4 by BW / 2), the block number added to
  BP and wrapped at 4 MB. Inside a block: CT32's word from x0 y0 x1 x2 y1 y2; CT16's halfword from x3 x0
  y0 x1 x2 y1 y2; T8's byte and T4's nibble read CT32's word order on 8 word rows with the halves swapped
  in rows 2-3 of even 4-row groups and 0-1 of odd ones, the byte from x3 and y1 (T4's nibble from x3 x4
  and y1). Written as bit formulas, not tables; checked against PCSX2's tables for every pixel of a page
  in each of the four orders (session 80, outside the repo). CT24 writes a CT32 word's low 24 bits, T8H
  its top byte, T4HL / T4HH that byte's nibbles: **the message font in the Z buffer's top byte leaves the
  Z bits alone** (tested).
- **Uploads**: a TRXDIR write starts the transfer BITBLTBUF / TRXPOS / TRXREG describe; host->local takes
  the IMAGE data (GIF FLG 2 / 3, and HWREG, never seen) left to right, top to bottom, packed (CT24 3
  bytes a pixel across words, T4 the low nibble first), and IMAGE data past the rectangle is counted as
  extra; local->local copies at once in TRXPOS.DIR's pixel order; local->host is counted, not done.
- **The CLUT buffer** is the GS's 512 halfwords (a CT32 entry in halfwords e and e + 256, CT16 in one). A
  TEX0 or TEX2 write with an indexed PSM loads it as CLD says (1 always, 2 / 3 also set CBP0 / CBP1, 4 / 5
  only when CBP differs from CBP0 / CBP1): a 4-bit CLUT 16 entries (8x2) at CSA x 16, an 8-bit one 256
  (16x16, entries 8-15 and 16-23 of each 32 swapped). So **the windows' glyphs** (4.9: the header loads
  the 8-bit CLUT at `0x3FFC` with CLD 2, each glyph reads PSMT4HL / HH at CSA 0 / 1 with CLD 0) **read
  buffer entries 0-15 and 16-31, i.e. the stored 16x16's swizzled first two rows** (tested).
- **The reader** (`kh1_gsmem_read_tex`): TBP0 / TBW / PSM / TW / TH to `1 << TW` x `1 << TH` RGBA8 words
  (R in the low byte, A the texel's own 0-0x80 scale; TCC and TFX are the shader's), indexed PSMs through
  the buffer at CSA (CPSM CT32 or CT16), CT24 / CT16 alpha from TEXA (TA0, AEM, TA1).
  `kh1_gsmem_tex_stamp` gives the newest write to any page the texture covers and
  `kh1_gsmem_clut_stamp` the buffer's load count: a decoded-texture cache keyed by TEX0 checks both
  instead of dropping textures on every upload.
- **Render targets** (session 81, `kh1_gsmem_draw` / `kh1_gsmem_tex_target` / `kh1_gsmem_targets`): every
  drawing kick tells the model its context's FRAME (unless FBMSK masks every bit) and ZBUF (with TEST.ZTE 1
  and ZMSK 0); a target is FBP / ZBP with FBW, its PSM and the rows SCISSOR's SCAY1 reaches (the columns to
  SCAX1). Per 8 KB page the model keeps **the word bits a draw changed** (CT32 `~FBMSK`, CT24 and Z24 the low
  24, 16-bit formats all) and the target that drew last; an upload or copy clears the bits it writes from each
  page it touches (CT24 the low 24, T8H the top byte, T4HL / HH a nibble of it; 16-, 8-, 4-bit layouts the
  whole page). A texture whose pages hold drawn bits it reads is **"target N"**: the GPU target's texture,
  not a decode. So the message font (PSMT4HL / HH at `0x1000`, inside the Z24 buffer at `0x0E00`) stays a
  texture while a CT32 / CT24 read of the same pages is the Z buffer. A drawn page's stamp moves once per
  marking, so the cache treats a target texture as uncacheable. VU1 program starts on VIF1 (MSCAL / MSCALF /
  MSCNT) mark context 2's FRAME_2 / ZBUF_2 (`kh1_gs_path1`): renderer A's meshes draw there (§4.11; an
  inference, the program's tags choose the context). A FRAME with FBW 0 (before the boot environment) marks
  nothing. tests/host/gsmem_test.c: frame and Z targets, the font in Z24's top byte, a draw reading its own
  target, an upload over a target, an HL upload keeping Z's bits, FBMSK / ZMSK / FBW 0, the SCISSOR extent,
  an MSCAL marking context 2.
- **CT16S and the Z formats** (session 82): CT16S orders a page's 32 blocks y0 x0 y2 y1 x1 (CT16 is y0 x0 y1
  x1 y2), the columns inside a block as CT16's. PSMZ32 / Z24 / Z16 / Z16S are CT32 / CT32 / CT16 / CT16S with
  the final block number XORed with `0x18` (PCSX2's swizzle32Z / 16Z / 16SZ), so inside a page **a Z32 / Z24
  pixel (x, y) is the CT32 / CT24 pixel (x ^ 32, y ^ 16), a Z16 / Z16S one the CT16 / CT16S pixel (x ^ 32,
  y ^ 32)**: the page's quarters swap diagonally. A CT24 texture read of a Z24 buffer (the capture's
  `D_002B66B0` reads `0x0E00` CT24, §5.2's targets) therefore sees each page's depth with its 32x16 quarters
  exchanged. Z uploads and reads now decode; a port that keeps depth in a GPU depth texture and samples it
  as colour must apply the same swap in the shader (a texel offset per page). Every pixel of a 704x256
  window at six base blocks (page-aligned and not) and four widths matched PCSX2's tables (30 M addresses,
  outside the repo). A CLUT in CT16S (the third CPSM) now loads too. gsmem_test.c: 61 checks.
- **Not modelled**: CSM 1 (TEXCLUT, never written), an 8-bit CLUT at CSA not 0, local->host, the pixels a
  draw writes (a target is tracked, not rendered), except (session 83) **point-sampled textured sprites**:
  `kh1_gsmem_sprite` (called by gsregs.c on each SPRITE's drawing kick) draws a SPRITE with FST, TEX1
  MMAG / MMIN 0, TFX MODULATE or DECAL, a texture of at most 64x64 not in a target, CLAMP REPEAT / CLAMP, no
  fog, no alpha / destination alpha test, no Z write, into a CT32 / CT24 FRAME (FBMSK, SCISSOR, XYOFFSET,
  ALPHA's `(A - B) C >> 7 + D` with COLCLAMP taken as 1, the source alpha written), at most 4096 pixels,
  into the model's pixels: the texture animations' CLUT passes (§4.13). Anything else is a target as
  before. gsmem_test.c: 65 checks (a 16-colour cross-fade into block `0x3E05` with its alphas kept and
  read back through a PSMT4 CLUT load; bilinear stays a target).

`KH1_HOST_TRACE=5` prints each send's uploads (`kh1-host:   upload host dbp ...`) and
`tools/host/gsstate.py RUN.txt --uploads` lists a run's. On the fake disc (stub:2) the same 86 sends
make three uploads, from three chains on the stack built by func_0011fbb0 in **func_001ef950**
(src/text/text.c, called from func_00109388 at boot, after it loads the file `D_00490940` names into a
func_001559f0 buffer): **the 16x16 CT32 CLUT at `0x3FFC` from the file's +0x10000, then the message
font as PSMT4HL (+0) and PSMT4HH (+0x8000), 256x256 each at `0x1000` BW 4** (the CLUT §4.9's headers
load; on the fake disc the pixels are zeros). tests/host/gsmem_test.c (36 checks then, 61 since session 82, in `make test`): addresses per PSM, an upload and
read back per PSM, CT24 packing, the font's halves over a Z pattern, 4- and 8-bit CLUT loads with CLD 0 /
1 / 2 / 4, the glyphs' CSA 1 read of an 8-bit CLUT, TEXA, a local copy, the cache stamp, IMAGE through
the GIF reader. Valgrind: 0 errors to the overlay fault.

**`KH1_HOST_TEXDUMP=DIR`** (with `KH1_HOST_TRACE` >= 2) writes each distinct texture a send drew with,
decoded from the model after the send, to `DIR/tex_TEX0_N.pam` (RGBA, A doubled; once per TEX0 + TEXA +
page contents + CLUT load for the indexed PSMs). Since session 81 a texture in a target's drawn bits is not
decoded: the line reads `kh1-host:   texture TEX0 in target N: not decoded`. On the fake disc (stub:2,
`KH1_HOST_TRACE=5`, `gsstate.py --targets --draws`) **three targets**: 1 the 3D target (block `0x1A00`, FBW
8, CT32, 384 rows: `D_002A6500`'s sprites, the capture's `D_002B66B0`, and the renderer A chain `D_00272C70` on
ch 1 by its MSCAL), 2 the Z24 buffer at `0x0E00` (384 rows), 3 the display buffer (block 0, CT24, 448
rows: `D_002BC980`, `D_002A6890`); and **two draw states read a target**: the frame copy `D_002A6890`
(brightfade.c, 80 SPRITE|TME|FST from `0x1A00` CT24 into FBP 0: target 1) and the capture `D_002B66B0`
(capture.c, 3 sprites from `0x0E00` CT24 into `0x1A00`: target 2, the Z buffer on the fake disc; the capture
itself writes there as CT24 at run time). The message font is not flagged. From the user's disc: the dumps
never go in the repo.

### 5.3 The 2D layers on the Vita's screen (session 89, static, draft)

**One coordinate space.** Every 2D drawer in the main ELF writes GS primitive coordinates in 1/16 pixels of
the **512 x 384 3D target** (FBP `0xD0`), with the target's top left at `(0x7000, 0x7400)` (`XYOFFSET`
1792 / 1856, §3.1): screen pixel `(x, y)` is `((x << 4) + 0x7000, (y << 4) + 0x7400)`. Read from the C:

| Drawer | Where the position comes from | Source |
| --- | --- | --- |
| Text windows, their frames, parts, rows, lists, icons, numbers | the window's origin `+0xb0 / +0xb4` (already in 1/16 GS units) plus offsets in pixels; scaled about an anchor when `+0x48` bit 0 (`+0x74 / +0x78`) | textwin, winpart, winmenu, wintext, winrow, winlist |
| Icons outside a window | `(x << 4) + 0x7000`, `(y << 4) + 0x7400` | wintext.nostrict.c `func_001fcdc8` |
| The message-font text | `x * 16 + 0x7000`, `y * 16 + 0x7400`; message codes 17 / 18 position in screen pixels (`- (origin - 0x7000)`) | text.nofill.c, text.nostrict_nofill.c, wintext.nostrict.c `func_001f94f0` |
| The field text, the value selector | the same, own static chains (§4.10) | fldtext.c `func_0010c540` area, selector.c |
| HUD sprites, gauges, arcs, needles | `pos * 16 + 0x7000 / 0x7400` | ui.c, gauge.nostrict*.c, prim.nostrict*.c |
| Notices, banners, pop-ups | pixels from layout tables (`D_00458548`, `D_00469C94`) through the same offset | notice.c, banner.c, popup.c |
| Markers on 3D things (lock-on, damage numbers, labels, marks over actors, objects' name windows; **not** the target's gauge, a fixed top-left part, §5.3.1) | a 3D point through `D_002E26C0` (view-screen) to GS units, then `- 0x7000 / 0x7400` (hudmath.c `func_00249558`) or `>> 4 - 1792 / 1856` (objwin.nostrict.c) | hudmath.c, objwin.nostrict.c, marker / dmgnum / lblnum / actmark / partymark |
| Menu backgrounds, the journal, the pointer, list menus | the same offsets | menubg, journal_s*, journalfx, pointer, listmenu |
| Full-screen passes: the clear (`D_002A6500`), the fades, flash, letterbox, blur, sway, lens grid, spin | the whole 512 x 384 (or its half, 256 x 192, for the menu blur's capture) | brightfade.c, sceneeff.c, §4.16 / 4.17 |

**Exceptions** (not in the 3D target): the frame copy's flash `D_002A6B80` (a quad over the 512 x 448
display buffer after the copy), the **system-message band** (its own 512 x 128 display on read circuit 1,
§4.15) and the screen/fade.c ending (the same writes), and the 640-wide buffer at `0x118000` (case 2 of
the frame copy: the movies and `D_002B73E0`). The window clip `SCISSOR_1` is in target pixels, clamped
to 512 x 384 and reset to it by `func_001f8f30`. A quirk to keep: winmenu.c's window y getter / setter
(`func_001fd268` / `func_001fd278`) use `0x7000`, not `0x7400` (a y 64 pixels off; no main-ELF caller,
so an overlay's, matched code).

**The target's pixels are square.** 512 / 384 is 4 : 3, which is the TV's shape; the frame copy's
stretch to 448 lines only fills NTSC's visible lines. So the port needs no aspect correction of the 2D
art: one uniform scale of the 512 x 384 space keeps every shape.

**What assumes 512 x 384** (each needs the port's real target size, not the constant): `SCISSOR_1`'s
full-screen value (gspkt.c's defaults, `func_001f8f30`), `XYOFFSET` itself, the frame copy's 16 strips of
32 pixels, the clear's 16-sprite sends, the menu blur's half-size capture and its 1 / 2 pixel offsets
(scale them with the target), the sway's and lens grid's copies into the Z buffer's memory, the spin's
turned quad, the letterbox bars (y 0-34 and 350-384, x 0-512), the guard band (`(2048, 2048, 1/512,
1/384)` in renderer B's qw 7, §2.3), the viewport `D_002BBF60` (clip to GS units) and every marker
projected through it.

**Plan for 960 x 544.** 544 x 4 / 3 = 725.3, so a 4:3 picture is about **725 x 544, scale 1.4167**, with
bars of 117 / 118 pixels.

1. **First bring-up: 4:3, pillarboxed.** Render the 3D target at 725 x 544 (or any multiple of 512 x
   384 for supersampling), keep the 2D in the same target with one affine map `(X / 16 - 1792) * s,
   (Y / 16 - 1856) * s` in the vertex shader of every GIF-path draw, scissor and full-screen pass, and
   present it centred in black bars. Nothing in the game code changes; the draw list's order between 2D
   and 3D (they share the target and the keys) stays as it is. The glyph and window-font textures are
   small (18-pixel cells, a 256 x 256 sheet): bilinear at 1.42 is soft but readable; a later step can
   swap in a higher-resolution font sheet keyed by the same cells.
2. **Option: a wide 3D view with the HUD anchored** (after the real-disc run). The 3D gets a hor+
   projection over the whole 960 x 544. *Corrected in session 90 (§5.4):* the projection
   (`D_002E26C0`, `D_002BBF60` x `D_002BC020`) stays as it is (hor+ keeps the vertical view, and the wide
   view, GS x 1709-2387, is already inside renderer A's guard box `D_002BC020`); **no CPU cull reads
   `D_002BC020`**. The culls (the grid's `func_00107548`, props, actors, shadows, ppp effects, the party
   warp) all test the 4:3 frustums `D_002BBE60` / `D_002BBEE0` (as `D_002BBFA0` / `D_002BBFE0`), so one
   constant in `func_00110618` (the x 320, still a non-match; in the port its C) widens them together;
   the markers and objwin have their own 4:3 bounds (port-side constants). `func_00121000` is not a cull.
   The 2D stays in the 4:3 canvas (scale 1.4167, centred at x 117), except:
   - the **full-screen passes** (clear, fades, flash, letterbox, the blur, sway, lens grid and spin
     copies) cover the whole 960 x 544;
   - **markers over 3D** (hudmath.c, objwin.nostrict.c; their hide-off-screen bounds widened, §5.4) come out of the wide projection
     in canvas units below 0 or above 512 at the sides, which the centred canvas map already places right:
     they must *not* be anchored or clamped;
   - **HUD elements are anchored to an edge**: a table kept by the port (not in the game code) of the HUD
     drawers and the side they keep, moving left-anchored ones by -82.8 and right-anchored by +82.8 canvas
     pixels (117 / 118 Vita pixels; first draft in §5.3.1). The rule to start from: an element whose rectangle lies in the left third goes left,
     the right third right, the rest centred (the HP / MP gauges, the command menu, the party gauges, the
     notices' layout tables). The real-disc run's draws (`gsstate.py --draws`) list the rectangles;
   - the **menus and text windows** stay in the centred canvas (a full-screen menu shows the 3D's wide
     sides behind its background, or the port dims the bars), and the system-message band and movies stay
     4:3 and centred.
3. Rule 7 (frame-time) and the PS2's overscan: the original HUD sits inside a TV's safe area, so on the
   Vita's fully visible screen it looks inset; the anchoring of step 2 is the place to move it outward if
   wanted.

#### 5.3.1 The HUD's anchor table (session 90, static, first draft)

Every gameplay HUD part in src/hud draws ui.c sprites (`UiSpr`, 0xC0 bytes) out of **sprite files linked into
the ELF's .data** (`D_0044A830` ... `D_00469CA0`, `func_0024aac8` fixes their offsets at set up). A sprite's
rectangle is in **target pixels**, and `func_0024a6b8` turns it into `(x << 4) + 0x7000`, `(y << 4) + 0x7400`;
each drawer then adds its own origin `(dx << 4, dy << 4)` to the four vertices (`func_00243380` notice,
`func_00248798` banner, `func_00243c10` pop-ups, `func_0023d700` gauges, `func_00246570` target gauge,
`func_00244968` counter). So **a part's screen rectangle = its sprites' rectangles + the drawer's origin**,
and both are readable without a boot. The values below were read from the ELF's words (a small reader of
the program headers; nothing written to the repo). Rectangles are the sprites' rest keys (the last key of
track c); the open / close animations slide them 4-64 pixels from there.

The rule (§5.3 step 2): x0 >= 341 right, x1 <= 171 left, else centre; y split the same way (128 / 256).
Where a rectangle straddles a line but grows from one edge, the side it grows from is proposed (marked).
In 960 x 544 with the 4:3 canvas at scale 1.4167 a left-anchored part moves by **-82.8 target pixels**
(117 Vita pixels) and a right-anchored one by **+82.8** (118).

| Element | Drawer | Position source | Rectangle (512 x 384) | Anchor |
| --- | --- | --- | --- | --- |
| Sora's HP / MP gauge (round, kind 0) | gauge.nostrict.c `func_00241260` (frame), `func_0023f688` / `func_0023e160` (arcs), `func_0023d7e8` (needles), `func_00242c08` (face) | base `D_00454600[0]` = (443, 316) + frame-size offset `D_00454650[unk94]` = (24, 24) / (0, 24) / (0, 0) (`func_0023d490` picks it from the maxima); sprites `D_0044A830` (39) in absolute pixels | (360, 257)-(503, 375) at the largest size; +24 / +24 at the smallest | right, bottom |
| Party gauge 1 (kind 1) | the same, sprites `D_0044C5A0` | `D_00454600[1]` = (399, 44) + `D_00454680[0]` = (0, 0) | (363, 9)-(435, 79) | right, top |
| Party gauge 2 (kind 2) | the same | `D_00454600[2]` = (399, 44) + `D_004546C0[0]` = (68, 20) | (431, 29)-(503, 99) | right, top |
| Kind 3 gauge (f32 values, `func_00241c00`, no main-ELF caller: an overlay's) | `func_002410b8`, sprites `D_0044F4D0` | `D_00454600[3]` = (443, 68) + `D_00454700[unk94]` = (0, 0) | (363, 9)-(503, 127) | right, top |
| World map's gauge (kind 4, `tt_gaugeWorldmap` `D_00454A20`) | `func_00240fa0`, `func_00240400` (parts by `D_00454A20.mode`), sprites `D_00451040` (69) | `D_00454600[4]` = (443, 316) + `D_00454650[unk94]` | (334, 257)-(503, 375) | right (grows left past 341), bottom |
| Command menu, top list | cmdmenu.c `func_0023a968` -> cmdmenu.nostrict.c `func_0023bb98` | constants (16, 260); rows `y + 20 + 22 i`; sprites `D_004409A0` (100 wide) | (16, 260)-(116, 280 + 22 n), n = 4: to 368 | left, bottom |
| Command menu, sub lists 1-4 (`D_00650120[1..4]`, `[6]` = `D_00650C00`) | the same | parent x + 11; y parent + 22 / + 44 / + 22 * cursor, or `348 - 22 n` when it would pass 369 | x 27-164 (`D_00443180` 112 wide), y up to 368 | left, bottom |
| Command menu, kind 5 frame | cmdmenu.nofill.c `func_0023a608` | constants (16, 282); `D_00448FA0` 110 x 86 | (16, 282)-(126, 368) | left, bottom |
| The "obtained" notice (most likely) | notice.c / notice.nostrict.c `func_002436c0`, `func_00243508` | constants (160, 344); sprites `D_00454A40` / `D_00455A10` (in), `D_004569E0` / `D_004577D0` (out); text at + sprite 0's (5, 0) + `D_00458548` (71, 4) | (160, 344)-(366, 368); text from (236, 348) | centre (straddles 171), bottom |
| The banner | banner.c `func_00248b58`, `func_002489c8` | constants (160, 344); sprites `D_00467410` (open), `D_00468220` (close), `D_00468E10` (kind 1); text + (5, 0) + `D_00469C94` (55, 4) | (160, 344)-(334, 368); text from (220, 348) | centre, bottom |
| Party pop-ups (title + n lines) | popup.nostrict.c `func_00244298` -> `func_00244188` -> popup.c `func_00243ef8` | constants: columns from (16, 16), 200 apart, 16 lines a column; lines 20 then 22 apart; sprites `D_00458560` (13) | column 1 (16, 16)-(208, 368); column 2 x 216-408; column 3 x 416-608 (off the target) | left, top (the stack grows rightwards) |
| Target's gauge | tgtgauge.c `func_00246750` | constants x 16, y 24 / 65 / 80 (`func_002485f0`: time / score shown) + 28 with the sign; sprites `D_0045D6E0`; bar width `max / 2` (<= 150) + 44 | (16, 24)-(<= 210, 37) at y 24 | left (grows right), top. **Not projected** |
| The sign over it (lock-on name plate? guess) | marker.nostrict_nofill.c `func_0023cb30` | constants (16, 24 / 65 / 80); sprites `D_00449990` by lists `D_0044A800` (8, 9, 10) / `D_0044A810` (5, 6, 7) | (16, 24)-(128, 48) | left, top |
| Munny counter (most likely: prize.nostrict.c calls it) | counter.nostrict.c `func_00244be0` | constants (25, 238); digits 13 apart, then the frame; sprites `D_00459D40` | (25, 238)-(~150, 258) for 5 digits | left, bottom (above the command menu) |
| Minigame time / score | timer.c `func_00248140`, timer.nostrict.c `func_00248238` (icon) | the caller's `MgHud` x / y (overlay) + absolute sprites `D_00466180` / `D_004667B0` / `D_00466DE0` (frames), `D_00465FD0` (score); texts at constants (69, 22), the record 43 lower; icon (12, 15) 64 x 64 | (0, 15)-(243, 78) with x / y 0 | left, top |
| Two-sprite one-shot (class1a.nostrict.c starts it) | oneshot.c `func_00249010` | absolute sprites `D_00469CA0` | (131, 284)-(195, 302) | centre by the rule; left (next to the command menu) is a guess |
| Lock-on mark, actor markers | marker.nostrict_nofill.c `func_0023c270` / `func_0023c5c8` | actor point -> `func_00237a48` (`D_002E26C0`) -> `func_00249558`, centred | projected | **not anchored** |
| Damage / heal numbers | dmgnum.nostrict.c | the same projection | projected | not anchored |
| Labelled numbers | lblnum.nostrict.c | the same | projected | not anchored |
| Marks over an actor / the party | actmark.nostrict.c, partymark.c | 54 pixels above the projected point 0x8004 | projected | not anchored |
| Objects' name windows | objwin.nostrict.c | projected (§5.3) | projected | not anchored |
| System-message band | §4.15 | its own 512 x 128 display | full width | centred, 4:3 |

Not found in the main ELF: **a minimap** (KH1 has none); **the Trinity prompt** (trinity.c draws no 2D: its
marks are 3D, the HUD part may be in the code loaded at `D_00F20000`); **a separate action prompt**: TRIANGLE
sets `D_002E3168 |= 1` and no HUD file draws a prompt of its own, so the action command most likely shows as
a row of the command menu's top list (as on the disc's screens; a guess). An **HP-orb counter**: none; the
counter above is the only one. The top list's title sprite has two sets (`D_00449530`, `func_0023a8d0`) picked
by `D_002C5958` bit 0, the battle flag sound-spec reads: the battle / field look of the same rectangle.

**Corrections to §5.3's table**: the target's gauge is a fixed top-left part (tgtgauge.c), not a marker over
3D: anchor it left. gauge.nostrict.c projects nothing (`func_00249820` is a copy of the centre, for the
party's faces one pixel higher); its rectangles are fixed.

**The sprite file** (`UiFile`, include/hud/ui.h): +0x8 the sprites' offset, +0xC their size (n x 0xC0), +0x10
/ +0x18 / +0x20 the keys of tracks a (0x20 bytes: frames, pad, four f32 colour), b (0x50: four colours), c
(0x20: frames, pad, **x, y, w, h as f32**). A sprite: +0x0 `r` = x, y, w, h (s32 pixels), +0x10 `t` = u0, v0,
u1, v1 (texels, u0 > u1 mirrors), +0x20 four RGBA, +0x60 flags (4 / 0x10: rect track; 2 / 8: colour; 0x40 /
0x80: four colours), +0x64 / +0x78 / +0x8C the tracks (time, key, count, key index, flags). Notice and banner
keys end in a negative frame count (-6 / -10: the hold key). Not identified: the words at +0x0 / +0x4 / +0x14 /
+0x1C of the header (+0x0 is 0 in all files read), and why `D_0045D6E0` sprites 11-13 are 2-4 pixels wide (end
caps, a guess). The index lists (`D_00458520`, `D_00469C20`, `D_00459C50`, `D_0044A800`, ...) are s32 sprite
numbers ended by -1, read by `func_0024afc0` / `func_0024af40`.

**The gauge tables** (data_0045.s, 16-byte entries x, y, 0, 0 or 1): `D_00454600[5]` the kinds' bases (the
arc centre is base + offset, `func_00240b68`: `unk80 = (p1 + p2) * 16 + 0x7000 / 0x7400`); `D_00454650[3]`
kind 0 / 4's offset by frame size; `D_00454680[4]` / `D_004546C0[4]` the party's offsets (only [0] read:
(0, 0), (68, 20); [1..3] = (12, 0), (12, 0), (24, 0) / (68, 20), (80, 20), (80, 20) unused in the main ELF);
`D_00454700[3]` kind 3's (zero). `D_00454730` / `D_00454780` / `D_004547C0` (5 / 4 / 4 entries) are the arcs'
**texture centre (u, v) and half side in 1/16 pixels** (`func_0023d208` puts the fan's square at centre +-
z): Sora's 45-59 pixels, the party's 26-35. `D_00454820` ... `D_004549E0` are the needles' corners (x, y and
u, v pairs). `D_00454A20` (`tt_gaugeWorldmap`: mode, barrier, scale, two values) is zero in the ELF.

**What the real-disc run must confirm** (`KH1_HOST_TRACE=5`, a field, a battle with lock-on and a pick-up,
the world map, a minigame): `gsstate.py --draws` lists draw states, not rectangles; it needs **a per-chain
vertex extent** (min / max of XYZ2 minus `0x7000 / 0x7400`, >> 4, per sending function: the HUD's sends all
go from `D_00351E10`, so the key is the drawing environment sent just before: `D_00651C00` gauges,
`D_00655F80` notice, `D_006694B0` banner, `D_006562C0` pop-ups, `D_00668120` target gauge, `D_006510A0` sign,
`D_0065FB30` counter, `D_00669070` timer, `D_006697C0` one-shot, `D_00648790` / cmdmenu's for the menu). Then:
each rectangle above against the drawn one; the party gauges really at the top right (the data say so);
which frame size Sora's gauge uses early on; what the banner, the sign, kind 3 and the one-shot show; the
timer's `MgHud` x / y; whether a pop-up column 3 is ever reached; the face pictures' sizes (TIM2 from the
disc, centred on the arc centre); and that no gameplay 2D part draws from an overlay outside this table.

### 5.4 The culls under a wider view (session 90, static, draft)

Read from the C, from `func_00110618`'s disassembly (still a non-match; nonmatchings/session6/w6_02 has the
same maths) and from `func_0024edf0` (src/asm/text_0024e0a4.s, C twin in host/port/asm_c.c). Renderer-spec 5.3
step 2. **No CPU cull in the main ELF uses `D_002BC020` or `D_002BBF60`.** The culls use two other outputs
of `func_00110618`, which are the exact 4:3 screen frustum.

**The six matrices** (`func_00110a48`, display.c:281: `func_00110618(BBE20, BBE60, BBEA0, BBEE0, BBF20,
BBF60, scrz = D_004F7650, ax 0.8, ay 0.84, cx 2048, cy 2048, zmin 1, zmax 16777000, near 1, far 4e8, fog far
D_004D90F8)`; `D_004D90F8` is `camS.a[1]`, display.c:343). A point at view `(X, Y, Z)` lands at GS pixel
`2048 + 0.8 scrz X / Z`, so the 512-pixel width is `|X / Z| <= 320 / scrz` and the 384 height is `|Y / Z| <=
229 / scrz` (0.84 x 229 = 192.4).

| Output | Built as | Half-extent at scrz (GS px) | World product (display.c:298-301, view.c:152-155) |
|---|---|---|---|
| `D_002BBE20` | view -> screen, far 4e8 | (projection) | `D_002E2740` = it; `D_002E26C0` = it x view |
| `D_002BBE60` | view -> clip, `scrz/320`, `scrz/229`, far 4e8 | 320 x 229 (256 x 192: **the 4:3 screen**) | `D_002BBFA0` |
| `D_002BBEA0` | view -> screen, fog far | (projection) | none (only saved / restored) |
| `D_002BBEE0` | view -> clip, `scrz/320`, `scrz/229`, fog far | 320 x 229 (**the 4:3 screen**) | `D_002BBFE0` |
| `D_002BBF20` | view -> clip, `scrz/2045`, `scrz/360.5`, far 4e8 | 2045 x 360.5 (1636 x 303 px: a guard box) | `D_002BC020` (renderer A VU 8-11) |
| `D_002BBF60` | clip -> screen: x 1636, y 302.8, +2048 | | renderer A VU 12-15 |

So `D_002BC020` is renderer A's guard-band box, already 6.4 times the screen's half-width. It is not a
frustum, and no CPU test reads it.

| Cull | Where | Test | Frustum source | Under hor+ |
|---|---|---|---|---|
| Grid cells (renderer A) | `func_00107548` grideff.c:353 -> `func_00107ab8` hand/vu0.c:7; from field.c:338 `func_00100988` | each cell's 8 box corners (its 128-byte record in map section 1, `src->e[i]`) times `D_002BBFE0 x D_0029B280`, `VCLIPW`: culled when all 8 are outside one x / y / near plane (`0x2F`); class 1 (P2, fogged) when a corner is past the fog far plane (`+z`), else class 0 | `D_002BBFE0` = 4:3 side planes. No cone, no table, no distance except the fog far plane | **pops in at the sides.** Widen with the shared constant change below |
| Props / room models | `func_00114a38` roommdl.c:120 (from `func_001369e8` objdraw.nostrict.c:366) | 8 corners from the model header times `D_002BBFA0 x D_0029B280`, `func_0024edf0`: drawn when it is 0 | `D_002BBFA0` | pops in; the same change |
| Actors (renderer B) | `func_00135bb0` objvis.nostrict.c:46, from `func_001368e8` / `func_00136ab8` objdraw.c:74/95, `func_00136768` objdraw.nostrict.c:329 | box `func_00135a68(x410 radius, x414 height)` times `D_002BBFA0 x` the actor matrix, `func_0024edf0`; always visible when `x370` bit 49 is set; hidden when bit 45 is set and the scale is 0. A pass sets `x370` bit 35 ("drawn") | `D_002BBFA0` | pops in; the same change. Bit 35 also drives gameplay (below) |
| Guard flag `0x100` (P18) | `func_00121000` vecutil.c:124, from `func_00136428` objdraw.nostrict.c:305 | all 8 corners `w >= 1` and inside 0..4095 after `D_002E26C0`: the box needs no VU clipping. **Not a visibility test** | `D_002E26C0` (GS range) | none |
| Renderer B per-triangle | P11-P17 on VU1 (§2.3), matrix `D_002E26C0` from `func_001621e0` objdraw.nostrict.c:313 | reject / clip against qw 7 `(2048, 2048, 1/512, 1/384)` | its own (header chain `0x00272CF0`) | the visible edge sits 339 px out, inside the 512-px band. The port clips in hardware (§5 table), so none |
| Shadows | `func_00127c20` shadow.nostrict.c:226/277 | 8 corners of the shadow's world box, `func_0024edf0(D_002BBFA0)` | `D_002BBFA0` | pops in; the same change |
| ppp effects | `func_001812d0` pppsys.c:544, from `func_00181738` pppsys.nostrict.c:304 and `func_00181b30` pppsys.c:696 | 8 points at `e->x8C` times `D_002BBFA0 x D_00615E70`; `x90 = 255` off-screen: not drawn, and **not updated** when `own->xf8` | `D_002BBFA0` | effects at the sides vanish or freeze; the same change |
| Party warp | `func_00169f28` partyctl.c:197/177 | picks the nearest leader trail point `D_00575090[i]` whose box is **off** screen (`func_0024edf0 != 0`) and has a clear line, then moves the member there | `D_002BBFA0` | a member would appear inside the wide sides; the same change |
| Markers (lock-on, target sign, damage numbers, labels, party marks) | `func_00249580` hudmath.c:94, from marker.nostrict_nofill.c:64/92, actmark.nostrict.c:87, lblnum.nostrict.c:73, dmgnum.nostrict.c:86, partymark.c:104 | `sceVu0ClipAll` of the point through `D_002E26C0` against `D_00469F90 = (1792, 1856, 0, 1)` .. `D_00469FA0 = (2304, 2240, 0, 4e8)`: hidden unless on the 512 x 384 | own data constants (the 4:3 screen in GS px) | **port-side constant**: x 1709.2 .. 2386.8 |
| Object windows' tail | `func_0010b390` objwin.nostrict.c:283/326-329 | `RotTransPers(D_002E26C0)`, then `>> 4 - 1792 / 1856`; `f6 = 1` when x < 0, x > 512, y < 0 or y > 384 | own constants (canvas px) | **port-side constant**: x -82.8 .. 594.8. `f6` picks the tail sprites `func_0010a5d0` draws (guess: the tail of a speaker who is off screen) |
| Draw-list / prim / kekoto triangles | `func_00237548`, `func_002378c8` drawlist.nostrict_nofill.c:20/119, prim.nostrict.c:41, ryjkekoto.nostrict.c:332, `func_00121120` vecutil.c:146 | `sceVu0ClipScreen`: inside the 4096 x 4096 GS range, w > 0 | GS range | none |
| Lock-on choice | `func_0012f3d0` / `func_0012f218` cmdmenu.nostrict.c:755/703; cycling `func_0012f5c0` / `func_0012f690`; R1 `func_0012f700` | distance minus radius (1200 cap for spawn flag `0x1000`), kind priority `D_002E319C`, line of sight `func_0012f0f8`: from the camera eye `D_002E2780` when the target's `x370` bit 35 (drawn) is set, else from the player | no screen, cone or FOV test; only bit 35, the actor frustum's result | none beyond step 1 |
| Action target / lock loss | `func_0012f868` cmdmenu.nostrict.c:817; `func_0012eb08` cmdmenu.c:370; `func_0012fa98` | distance <= 300 weighted by facing (`func_00121b38`), dy within +-350, line of sight; loss at > 1500 or dy > 1000 | none | none |

**Bit 35, "drawn this frame"** (cleared by `func_00136bc0` objdraw.c:140, set by the actor passes above; the
prop pass `func_001369e8` sets it whatever `func_00114a38` returns) is read by gameplay:
`func_00138130` objtask.c:299 steps an actor's motion (`func_00130f18`) only while it is drawn, when its
spawn record has `x4 & 0x20000`; `func_00153f88` hitreact.nostrict.c:97 starts action 25 on a
defeated actor only if it is drawn (or `D_002C5958` bit 0); and the script command `func_0012a030`
objscmd.c:866 (in the table at data_002E.s:353) returns it to the script; and `func_0012f218` lets a drawn target pass the lock-on line-of-sight test from the camera. So the actor frustum is a gameplay
input, not just a draw cull: with a 4:3 frustum under a wide view, those actors would freeze in plain sight.
Widening the frustum keeps the original rule ("on screen") true on the wide screen.

**`func_0024edf0`** returns 0 (visible) whenever `D_002BBDE0 != 3` (game state 3, inferred: field play), so
outside that state none of the `D_002BBFA0` culls apply.

#### What the port changes

1. **One constant in `func_00110618`**: the 320 (`sxd = n * 320 / d`) becomes `320 * k`, with `k = (960 / 544)
   / (4 / 3) = 1.3235` (423.5). The same value goes into `D_002BBE60[0][0]` and `D_002BBEE0[0][0]`, so the grid,
   props, actors, shadows, ppp effects, the party warp and bit 35 all widen together. Leave the 229 (y), the
   2045 / 360.5 guard box and the projection (`ax`) alone.
2. **The projection itself does not change.** Hor+ keeps the vertical field of view, so `D_002E26C0` and
   `D_002BBF60` x `D_002BC020` keep mapping a world point to the same GS pixel. The wide view is the 4:3
   canvas extended to x -82.8 .. 594.8, which is GS 1709.2 .. 2386.8, inside renderer A's guard box (412 ..
   3684). *Corrects 5.3 step 2:* narrowing `D_002BC020`'s x row and widening `D_002BBF60` only enlarges that
   box. It is harmless but not needed. And neither renderer B's visibility nor `func_00121000` uses
   `D_002BC020`: the first uses `D_002BBFA0`, the second `D_002E26C0` and is not a cull.
3. **Marker bounds**: patch `D_00469F90.x` / `D_00469FA0.x` to 1709.2 / 2386.8 on the port's data, or wrap
   `func_00249580`. Without this, 5.3's unanchored markers are hidden at the sides before they are drawn.
4. **`func_0010b390`'s 0 / 512** becomes -82.8 / 594.8 (a port `#ifdef`, matched build unchanged).
5. **Renderer B's guard band** (qw 7, P11-P14's whole-triangle reject): the port's renderer clips in hardware
   and drops it, as the §5 table already says. If kept, the margin past the visible edge shrinks from 256 to
   173 px.

*Corrections to existing text:* §2.2's table calls `D_002BC020` "frustum-normalised". It is the 1636 x 303 px
guard box, not the screen. §4.14's "`func_00107ab8` (the camera test, not read here)" is now read: an 8-corner
box against `D_002BBFE0` (the 4:3 frustum, far plane = fog far), as above. §5.3's "CPU culls that use the clip
matrix" should read "the 4:3 frustum `D_002BBE60` / `D_002BBEE0`".

#### Open (need the real disc or a boot)

- Confirm the pop-in and the fix: boot with `k = 1` and a 960-wide scissor, then with `k = 1.3235`, and
  compare the side cells, props and effects (Traverse Town first district is a good open room).
- Which actors have spawn flag `0x20000` (motion stepped only while drawn), and which scripts call
  `func_0012a030`. Both need the spawn / script files.
- `func_0010b390`'s `f6` meaning (the tail sprites `D_002B7210` ... `D_002B7350`), from a boot that shows an
  object window with its speaker off screen.
- Overlays and the runtime code at `0x00F20000` were not searched. The Gummi ship (gummi/ship.c sets
  `D_002BC140`) and the menus' model views may build their own frustum.
- `func_00110618` is still a non-match. The port needs its C (the session 6 draft is believed right in its
  maths) to carry the change in step 1.

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
   *Session 85 (§4.14):* traced from the C. The three are the map grid's cell lists from section 1: cases
   0 / 1 each visible cell's first mesh (P0 / P6 or P2, key 10020, the patched slot is the map's GIF
   template), case 3 each visible cell's second mesh (P3 env map / UV scroll, key 50000, no Z writes,
   blended, fogged), and the fade groups reuse case 3's head. What the second meshes are on screen
   (inferred: water / glass / glint layers) waits for a boot or a real-disc host run.
9. ~~VSync and frame pacing: the constants in `func_0010fea0`, the 30/60 fps
   switch (`D_002BBDEC`), and where the main loop waits for the vertical
   blank.~~ *Session 86 (§4.15):* read from the C. The frame end `func_001104e0` waits for one field
   and then `D_002BBE0C` more (1 = 30 fps in the field, 0 = 60 fps in the pause, game over and reset);
   `D_002BBDEC` is the 60 Hz field's worth in 1/60 s (1.0, written once), and `func_0010fea0`'s two
   constants are the play-time cap, 100 hours at 60 Hz / 50 Hz. Not checked on a console.
10. ~~`0x118000` display area and the special `PMODE/DISPFB1` setup of
    `func_0010f5f8`: which screens use them.~~ *Session 86 (§4.15):* `func_0010f5f8` is the
    system-message band (512 x 128 from block `0x3600` on circuit 1, opaque over the frozen frame): no
    controller, the disc error, a read error and its retry, and the pause's strings. `0x118000` is the
    movie copy's source (`func_00106000` case 2), which only the movie overlay can select (no main-ELF
    store of 2: the overlay check).
11. The runtime-loaded code at `0x00F20000` (docs/elf-notes.md) may draw;
    it is not covered here.
