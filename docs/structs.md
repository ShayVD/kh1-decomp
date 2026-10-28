# Recovered structs

Struct layouts recovered so far. Field names are offsets (`unkXXX`) until
their meaning is known; rename them as evidence appears, keeping `make`
byte-identical.

## `Actor` (include/actor.h), session 3

The biggest group from `tools/structs.py`: 324 functions in
`0x001063C8`-`0x001DCB00` that hand the same first argument to each other.
Recovered from 23 matched functions plus 171 unmatched m2c drafts; 90
fields up to `0x414`, so the struct is at least `0x418` bytes. "Actor" is a
provisional name: it is the object most game logic passes around (it has
float fields in the `0x280`-`0x414` range, flag words, and pointers to other
objects of the same kind, e.g. `+0x98` is read and used with the same
`0x16C`/`0x280` fields), but what it represents is not confirmed.

Known so far (from the access patterns, not names):

- `+0x000` s32 bit flags (`& 0x800000` tests).
- `+0x160` is a 64-bit flag word (`|= 1`, `|= 0x40`; `+0x370` is another,
  `>> 0x23 & 1`) whose halves are also read as s32. Session 4: it is a
  union, `unk160_64` (s64) over `unk160`/`unk164` (s32); `+0x000` the same
  (`unk000_64`). `tools/structs.py` makes such a union whenever an 8-aligned
  offset is accessed both as 64-bit and as 32-bit words.
- `+0x098` is `struct Actor *` (another object of the same kind:
  `--self-ptr 0x98`). Accesses through it, and temps that only hold it, are
  rewritten too; no matched function used it yet at the end of session 4.
- Functions whose `arg0` is a `T *` used only as `*arg0` join the struct
  (`*arg0` is field `+0x000`).
- 29 matched functions take `Actor *` (session 4).
- `+0x288`/`+0x28C`/`+0x290` are written together (`func_00131c08`
  sets them from three float arguments).

To extend: rerun `tools/structs.py apply --seed func_00131c08 --struct Actor
--header include/actor.h --self-ptr 0x98 --write` after new matches (it regenerates the
header from all evidence and only rewrites functions still using
`M2C_FIELD(arg0, …)`), then `make`.

## `PppClass` / `PppEntry` (include/ppp.h), session 5

Session 4's "CompClass" is the ppp particle/effect program system. The
0x28-byte records are `PppClass` entries of the class table `D_00370200`
(236 records indexed by class id, record 0 empty); word 0 points to the
class name (`"pppMove"`, `"pppDrawMdl"`...). The 0x10-byte record whose
`+0xC` is `s32 *offsets` is a program's component, `PppEntry`
{cls, stride, data, offsets}. `func_00182d58` relocates a loaded program
(class ids become `&D_00370200[id]`). The slots, from their callers:
`+0x04` frame (every frame, `fn(obj, data, entry)`), `+0x0C` draw,
`+0x1C` con (object created), `+0x20` reset (timer back to 0), `+0x24`
des (before free), each `fn(obj, entry)`; `+0x08` and `+0x10` are never
set, `+0x14` (returns a float) is set by 3 classes and `+0x18` by
`pppKeAcmSolid` only. The callbacks find their data at
`obj + entry->offsets[0]`, so the data behind it has a per-class type.

`Actor +0x098` is `pair`: `func_00137308(a, b)` sets it both ways.

## Model files (session 16, static)

From the loaders in `src/` (static only; one embedded model in the ELF,
`D_002E31F0`, was used to check the renderer B layout). All offsets are
bytes, little-endian. "rel X" = offset from X that the loader turns into a
pointer by adding X (relocation). `tools/vu/model_header.py FILE` prints these
structures for a file you extracted yourself (never commit its output).
**(inferred)** marks meanings not read directly from code.

### File names

Files are read by name through `func_00120748(name, dst, callback, 0)` (the
KINGDOM.IDX hash of `tools/shift/extract_kingdom.py`; no path prefix is added).

| File | Name built by | Loaded / parsed by |
| --- | --- | --- |
| map file | `func_00112400(room)`: `D_002BCCE0` = world prefix + `"00_"` + `sprintf("%2d", room + 1)` with a leading space turned into `0`, then `func_001017e8` appends `".bin"` | `func_001012e0` (renderer A meshes, collision, map textures) |
| map image | same prefix + `".img"` (`func_001012e0`, `func_001015a8`), loaded right after the `.bin` | `func_00101048` (GS upload: CLUTs to blocks `0x3E00+i`, up to 16 PSMT8/PSMT4 64 KB pages to `0x2600 + 256*i`) |
| world file | world prefix + `".wdt"` (`func_00112320`, `D_002BCCA0`) | `func_00112968` |
| area set | world prefix + room `"%2d"` + `".ard"` (`D_002BCD60`), loaded over the `.img` buffer after its upload | `func_001136d8` -> `func_00122198` -> `func_00132c70` -> `func_00132790` |
| character model | a 32-byte name in the area set's name section (e.g. `xa_ex_4020.mdls`, a `.mdls` file) | `func_00155ef8` -> callback `func_00155c68` -> `func_00155b70` |
| motion set | the paired name (e.g. `xa_su_dumbo_e0.mset`) | `func_00155ef8` -> `func_00155cf8` -> `func_00155be0` |

World prefixes (`D_002BCC28[world]`, `D_002BC128` = world index): 0 `dh`,
1 `di`, 2 `dc`, 3 `tw`, 4 `aw`, 5 `tz`, 6 `po`, 7 `xx`, 8 `al`, 9 `lm`,
10 `nm`, 11 `he`, 12 `pi`, 13 `pp`, 15 `pc`, 16 `ew` (14, 17-19 are `xx`).
So room 1 of world 3 gives `tw00_01.bin`, `tw00_01.img`, `tw01.ard`,
`tw.wdt` (names derived from the code, not yet checked against the index).
Concrete character names in the ELF (the summon set `D_003031F0`, an area
set embedded in the ELF): `xa_ex_4020.mdls` .. `xa_ex_4070.mdls` with
`xa_su_<name>_e0.mset`; the common set `D_002E31F0` lists `ex_6050.moa`
etc. with their models embedded. Summon data files: `xs_<name>.dat`
(`func_0013bb60`, relocated by `func_0013ba18`).

### Map `.bin` (`func_001012e0`)

| Off | Type | Meaning |
| --- | --- | --- |
| +0x00 | s32 | version (sections 5-6 need >= 6, 7-8 >= 8, 9 >= 10) |
| +0x10 + 8*i | {s32 off, s32 size} x 10 | section i, rel file |

| i | Used by | Meaning |
| --- | --- | --- |
| 0 | `func_00105288(p, 1)` | collision mesh: 17-word header of rel offsets/sizes (20-byte faces, 16-byte entries, 12/8-byte tables); the inner pointer lists are relocated too |
| 1 | `func_00106ed0(p, size)` | **the grid** (renderer-spec §4.14; layout below, checked on every map of the disc in session 142). The address words of the tag table are relocated by the section's address |
| 2, 3 | `func_00108cf8(p, slot 0/1, 4)` | **renderer A mesh headers** (below), drawn with program table index 4 = **P4** (double-sided), objects `D_00494D80[0/1]`, key 10010 (`func_001008e8`; slot 1 only when `D_002BC0A8.b5`). *Session 142, from the disc:* these are **the sky**: section 2 a dome 14,000 to 40,000 units across (sky gradient, clouds), section 3 a second layer inside it (a cloud band, a skyline, the night's shapes). Every map has both. They carry their own textures (below) |
| 4 | `D_002A3F48`, `func_00105c70` | table of 16-byte vectors (inferred: positions) |
| 5, 7 | `func_001763f0` | ppp effect programs |
| 6, 8 | `D_0029B414`, `D_0029B41C` | not traced |
| 9 | `func_00105d88` | second collision mesh, same header as section 0 |

**Section 1, the grid** (`func_00106ed0`, session 142 from the C and the 130 map files of the disc):

| Off (from the section) | Type | Meaning |
| --- | --- | --- |
| +0x00 | s32 | cell count n (`D_00494BB0`; 117 to 1,015 on the disc, the C allows 1,024) |
| +0x04 | s32 | offset of the tag table (relocated) |
| +0x10 + 128 i | f32[8][4] | cell i's box: 8 corners, tested by `func_00107ab8` (renderer-spec §5.4). The corners' unused `.w` words carry the cell's values, read at load and then overwritten with 1.0: corner 0 `.w` non-zero = "not read yet" (every cell on the disc); corners 1-3 `.w` = the cell's centre x, y, z, copied to `D_00472190[i]` for the front-to-back sort (`func_00107548`); corner 4 `.w` = the cell's fade group t (0-31; the group bit `1 << t` in `D_00494BA8[i]`); cell 0's corner 6 `.w` = the animated texture's frame count + 20, or 1.0 for none (26 maps have 1-4 frames, stored at the file's end and uploaded to block `0x3600` by `func_00106e18`) |
| table + 0 | DMA tag | entry 0: `REF 2` to the chains' clipped-output template, `STCYCL 1,1; UNPACK V4-32 1 -> @0 +TOPS` of a GIF tag (NLOOP 5) `TRIFAN|IIP|TME|FGE|CTXT2` (121 maps) or `TRIFAN|IIP|FGE|CTXT2` (9), `MSCNT` |
| table + 16 (i + 1) | 2 DMA tags | cell i: `{w0, w4}` = mesh A (`REF`, 0 = none), `{w8, w12}` = mesh B (`REF`, 0 = none). On the disc 60,380 cells have A only, 13,338 B only, 12,032 both |

The REFs point at renderer A batch streams (renderer-spec §2.2 "Map meshes on the disc").

**The map image** `<ww>00_<nn>.img` (`func_00101048`, session 142; all 130 checked): a header of ten
words `{o0, n0, o8, -, o10, -, o18, -, o20, n20}`, offsets from the file:

| Part | Meaning |
| --- | --- |
| `o0`, `n0` bytes | 160-byte texture-animation records, copied to `D_0029B420` (renderer-spec §4.13); 18 maps have some |
| `o8` | the room's setup (`func_00100b18`): `+0x00` u8[16] the kind of each texture page (19 = PSMT8, 20 = PSMT4, other = none), `+0x14` u16 n0 / `+0x16` u16 n1 (CLUT counts), `+0x21..0x25` five bytes and `+0x34..0x3C` three floats into `D_002BC0F0.view30` and `D_0029B270` (the fog: e.g. `16, 64, 255, 0, 0` and `-0.00013, 200000, 300000` in di00_01), `+0x40` f32[16][2] the **UV-scroll rates** of P3's 16 slots, stored x 1/16384 into `D_002A4060` (slot k is the batch flag k + 1; 76 maps scroll something) |
| `o10` | CLUTs, one per 256 bytes: the first n0 are 8 x 2 CT32 (16 colours) loaded to block `0x3E00 + i`, the rest up to n1, 4 at a time, 16 x 16 CT32 (256 colours) to `0x3E00 + i` |
| `o18` | 16 pages of 64 KB: kind 19 = a 256 x 256 PSMT8 picture (TBW 256) to block `0x2600 + 256 i`, kind 20 = a 512 x 256 PSMT4 (TBW 512) to the same block; then at `+0x100000` a 256 x 1024 **PSMT8H** picture at block 0 (TBW 256), the upper bytes of the frame buffer's words |
| `o20`, `n20` bytes | 0x810-byte CLUT-animation records (`D_0029BE20` / `D_002A3E20`, renderer-spec §4.13); 13 maps |

So the grid's TEX0 values point at blocks `0x0000-0x0FFF` (PSMT8H), `0x2600-0x35FF` (the pages) and CBP
`0x3E00-0x3FFF`; `tools/vu/amesh_render.py` loads an .img this way and draws the room (renderer-spec §2.2).

### Renderer A mesh header (`func_001089f8`, `func_00108b60`, `func_00114a38`)

| Off | Type | Meaning |
| --- | --- | --- |
| +0x00 | f32[8][4] | 8 bounding-box corners. `func_00114a38` transforms them by the object matrix and frustum-tests them (`func_0024edf0`) before queuing the draw. `func_001089d0` sets `.w = 1.0` for corners 0-5 at load |
| +0x80 | DMA tag (qword) | copied to chain slot +0x30; word 1 (ADDR) is rel file |
| +0x90 | DMA tag (qword) | copied to chain slot +0x40; word 1 rel file |

The 0x60-byte per-object chain (renderer-spec §2.2) is then: +0x00 program
REF, +0x10 REF to the matrix block, +0x20 REF 42 qw (camera block, `MSCAL`),
+0x30 and +0x40 the two tags above, +0x50 END. The tags are copied with their
VIF words; which one points at the clip GIF template and which at the strip
batches is not fixed by the code (inferred: +0x80 plays the role of
`D_00486300`, the qw48 template upload, and +0x90 is the mesh stream).
*Session 142:* confirmed on all 260 far meshes of the disc: +0x80 is `REF 2`, `STCYCL 1,1; UNPACK V4-32 1
-> @0 +TOPS; MSCNT` of a GIF tag (NLOOP 5) `TRIFAN|IIP|TME|ABE|CTXT2` (246) or `TRIFAN|IIP|TME|CTXT2` (14);
+0x90 is the batch stream, which also uploads its own textures inline (`FLUSH; DIRECT`: BITBLTBUF /
TRXPOS / TRXREG / TRXDIR then an IMAGE packet, the picture to block `0x3400` and its CLUT to `0x3A00`,
then `TEXFLUSH`, `TEX0_2`, `CLAMP_2`): 337 textures, PSMT8 (275) or PSMT4 (62), 16 x 16 up to 256 x 256.

Prop models in an area set (`func_00132718`, section 2 of `.ard`) start with
an offset table: +0x00 s32 n, +0x18 rel offset of the mesh header drawn with
**P2** (`func_00114a38` -> `func_00108df8`, objects `D_002A6C60`), +0x20 rel
offset of a mesh header drawn with **P5** as a flat-colour silhouette
(`func_001149e8` -> `func_00108fd0`, objects `D_002AA060`; used by the shadow
pass, see renderer-spec §3.4). `func_001089d0` is applied to the +0x18 mesh
when n >= 2.

### Area set `.ard` (`func_00132790`)

An offset table `s32 off[64]`; section n = `[off[n], off[n+1])`, empty when the
difference is <= 0.

| Section | Meaning |
| --- | --- |
| 1 | list {s32 count, s32 rel[count]} of embedded character containers, each relocated by `func_00132678` (below) |
| 2 | same list of prop containers (`func_00132718`) |
| 3, 4, 5 | pointers kept in the area object (`D_00525298 +0x20/24/28`), not traced |
| 6 | 32-byte file-name strings; placement entries point at them by index (`f60` model name, `f64` motion name) |
| 7 + idx | per-room placement table (`idx` = `D_002BC134`): a header of rel offsets; its section 1 is {count, 0x78-byte entries}. Entry +0x02 u8 kind (4/8/9 = character from section 1, 5/10 = prop from section 2, by index `+0x56`), +0x54 s8 (negative = pick a sub-section), +0x60/+0x64 name indices (x32 into section 6) |
| 32 | fallback for the room table's section 4 |

Embedded character container (`func_00132678`): `off[0]` = section count, then
section 1 = model chunk chain, section 2 = a second chunk chain, section 3 =
attachment table (`func_0015c9f8`: four counts, 20-byte entries), section 4 =
ppp effects. `.mdls` (`func_00155b70`): section 1 = model chunk chain,
section 2 = ppp effects, section 5 = attachment table. `.mset`
(`func_00155be0`): section 1 = chunk chain (`MMTN`), section 3 = a table of
up to 10 nested `.mset`-shaped blocks.

### Renderer B model: chunk chain (`func_00161a08`, `func_001681b8`)

Chunks are `{char tag[4], u32 size, data[size]}`; the next one starts at
+size+8 and the chain ends at an unknown tag. Tags: `MOBJ` (model), `MENV`
(model without its own bone table: `t->x4 = 0`, `t->x8 = header`), `MMTN`
(motion; no relocation), `TEXA` (texture animation, found by `func_001684e0`
and relocated by `func_001680d8`), `BONE` (found from `MOBJ`, its pointer is
stored after the part table), `URSL` (eye overlay, `func_00175708`, below).

**`MOBJ` header** (offsets from the chunk start; offset/size pairs):

| Off | Type | Meaning |
| --- | --- | --- |
| +0x00 | char[4] | `MOBJ` |
| +0x04 | u32 | chunk size |
| +0x08 / +0x0C | rel / u32 bytes | texture records, 16 bytes each (count = size >> 4) |
| +0x10 / +0x14 | rel / size | pixel data; record j's pixels start after the previous records' `qwc*16` bytes |
| +0x18 / +0x1C | rel / size | CLUTs, 1024 bytes (256 x CT32) per texture record |
| +0x20 / +0x24 | rel / size | part table `t` (the main mesh) |
| +0x28 / +0x2C | rel / nonzero | alternative part table `t2` (shares `t`'s bones): the **shadow mesh**. Used when the draw asks for it (`Prm.x0 & 1`, only the shadow pass `func_00127960`), which also sets `x48` bit 2. Its parts have `g = 2`: XYZ-only vertices, drawn by P10 into the `0x3A0000` buffer (session 17, confirmed in RAM: the three characters' `t2` tables have one part each, all `g = 2`, and their shadow draw instances use them) |
| +0x30 / +0x34 | rel / nonzero | object list: rel offsets terminated by -1; each entry has 7 self-relative pointers (+0x14, +0x1C, +0x24, +0x28, +0x30, +0x38, +0x3C) and +0x3C points at 12-byte {id (-1 ends), x4, rel x8} records (purpose unknown) |

After relocation the six offset words hold pointers, and an `Obj->x0` of the
draw code reads `+0x20` as `{t, -, t2, +0x2C}` (inferred from
`func_001606d0`/`func_00162070`).

**Texture record** (16 bytes, read by `func_0015f488`):

| Off | Type | Meaning |
| --- | --- | --- |
| +0x0 | u16 | image size in qwords (GIF IMAGE NLOOP) |
| +0x2 / +0x3 | u8 / u8 | TEX0 TW / TH (log2 size) |
| +0x4 / +0x6 | u16 / u16 | width / height (TRXREG) |
| +0x8 | rel | pixel pointer (PSMT8, uploaded to block `0x3600`) |
| +0xC | rel | CLUT pointer (CT32 16x16 to block `0x3700`) |

**Part table `t`**:

| Off | Type | Meaning |
| --- | --- | --- |
| +0x00 | s16 | bone count n (matrices built per draw: 64 bytes each, 128 when lit) |
| +0x04 | rel t | bone table, 48 bytes per bone: scale (w = bone index), rotation (Euler radians, X then Y then Z, renderer-spec §2.4; max |a| = pi in RAM), translation, then u32: bits 0-9 parent (0x3FF = none), bit 30 = the bone gets its own matrix |
| +0x08 | rel t | unknown block (its `+0x08` becomes the second model's bone count) |
| +0x0C | s32 | part count |
| +0x10 + 16*i | part record | below |
| after parts | ptr | `BONE` chunk, written at load |

Part record (16 bytes; draw entry byte 7 = `4*i + 1`, so `table + byte7*4`
lands at record i - 0x0C, which is why `func_0015f488` and `func_0015ff78`
read +0x10/+0x14/+0x18):

| Off | Type | Meaning |
| --- | --- | --- |
| +0x0 | u8 | flags: bit 0 = also draw a translucent pass (second entry with `x5 = 1`, `ATST LESS`) |
| +0x1 | u8 | part id: bit index into the draw's hide mask `Prm.x28` and flag mask `Prm.x2c`; passed to the step-3 callback as `D_0055C680.xa` |
| +0x2 | u8 | `g`: entry `x4 >> 4`, the mesh layout. Bit 1 = XYZ-only vertices and 5-qword matrix records (`func_0015fd20`), and lets `x48` bit 2 through; bit 0 = skinned vertices (program choice bit 1). 0 = 3-qword vertices, 8-qword matrix records (renderer-spec §2.3) |
| +0x3 | u8 | written at load with the low byte of +0x4 (the texture index); read as entry `x6`: the attachment slot (`D_0055BEC0[x6]`) and the texture index handed to the step-3 callback (`D_0055C680.xc`) |
| +0x4 | u32 -> ptr | texture record index -> pointer |
| +0x8 | u32 -> ptr | index of the record whose CLUT is used -> pointer |
| +0xC | rel t | mesh DMA chain, sent with TTE in step 4 |

**Mesh chain** (session 17: rule settled and checked on every mesh in RAM,
renderer-spec §2.3 "Input"): DMA `CNT` packets (the last may be `END`), each
`STCYCL 1,1; UNPACK V4-32 n -> 0 +TOPS; MSCNT` with `n` = qwc - 1. The
unpacked qwords are records `{u32 op, u32 arg, u32 z, u32 w}`: op 0 = matrix
slot `z` for bone `arg` (+ the draw's bone base `DObj.x18`), 1 + 4 qwords when
`g & 2`, else 1 + 7 (`func_0015fd20` fills 4 or, for lit draws, 7 each
frame); op 1 = vertex group, `arg` = record length in bytes, `z` = vertex
count, `w` = strip parity, a GIF tag follows; op 2 (skinned only) = bone index
list of `arg` bytes; op 0x8000 = end of the packet, `arg` = 48 (bytes to the
next packet's first record) or 0 (end of the mesh). `tools/vu/rb_stream.py`
decodes and checks them.

**Draw instance** (`DObj`, `D_0055C698.obj[parity][78]`, filled by
`func_001606d0` from the caller's 0x48-byte parameter block `Prm`; this is
`s->x0` of renderer-spec §4.3):

| Off | Type | From | Meaning |
| --- | --- | --- | --- |
| +0x00 | u64 | `Prm.x38` | ZBUF_1 value |
| +0x08 | u64 | `Prm.x40` | FRAME_1 value |
| +0x10 | ptr | per frame | {bone matrices (n x 64 or x 128), 16-float light block} |
| +0x14 | ptr | `t` or `t2` | part table |
| +0x18 | s32 | | bone base (second model: `n - t2.n`) |
| +0x20-0x2C | s32 x4 | `Prm.xc..xf` | material RGBA (VU qw1); `+0x2C` is also AREF |
| +0x30-0x38 | s32 x3 | `Prm.x10..x12` | FOGCOL RGB |
| +0x3C | s32 | `Prm.x13 << 4` | VU qw6.w (fog bits) |
| +0x40 / +0x44 | fn / arg | `Prm.x20 / x24` | step-3 callback `x40(&D_0055C680, x44)` |
| +0x48 | u8 | `Prm.x0` | program bits: 16 if `x0 & 0x100` (box inside the guard band), else 8 if `x0 & 0x200` (clip), +4 with `t2` (`x0 & 1`), +1 lit (`Prm.x4` set and no `t2`) |

Draw entries (`Dsl`, `dsl[parity][480]`): +0 DObj, +4 bits 0-2 attachment
count, bit 3 = `Prm.x2c` has the part's bit (`fl & 8`: P19/P20 and the
ZBUF/FRAME-only GS packet), bits 4-7 = `g`; +5 translucent pass; +6 texture index;
+7 `4*i + 1`; +0x28 key.

The masks come from the actor (`func_00136428`, session 17): `Prm.x28` =
`o->x38c` (parts hidden), `Prm.x2c` = `o->x394` (parts drawn screen-mapped
by P19/P20; set and cleared only by script commands through `func_00135a10`
/ `func_00135a38`, bit `n - 1` for part `n`); the shadow pass uses `o->x390`
as its hide mask (`-1` when bit 30 is set).

### Checked against real files and RAM (session 16, PCSX2)

Files pulled from the user's disc (never committed): `tw00_01.bin`/`.img`, `tw01.ard`, `tw.wdt`,
`xa_ex_4030.mdls`; RAM from a PCSX2 savestate (`.p2s` is a zip of zstd members, method 93: extract
the raw member and run `zstd -d`; `eeMemory.bin` is the 32 MB EE RAM, `vu1Memory.bin` VU1 data).

- **Map `.bin`**: the section sizes chain exactly; a mesh section is `REF qwc x 16 + 0xC0` bytes. In
  RAM (End of the World field) the file sits at `0x9B2E80`, version 10. Its mesh DMA tags are **not**
  relocated in place (they still hold `+0xA0`/`+0xC0`): the code relocates copies.
- **Renderer A VIF batch** (inside the REF at +0x90): `UNPACK V4-32 num=1 -> 0 +TOPS` (header qword),
  `STCYCL cl=3 wl=1`, `UNPACK V4-32 num=N -> 1` (xyzw), `UNPACK V4-8 usn -> 2` (RGBA8), `UNPACK V2-16
  -> 3` (ST), `MSCNT`; repeated per batch. Textures are inline as `FLUSH` + `DIRECT` (PATH2): 5
  qwords of GIF setup + the image, then 5 + 65 for the CLUT, then 4. The REF at +0x80 (qwc 2, data at
  +0xA0) is `STCYCL 1,1; UNPACK V4-32 num=1 -> 0; MSCNT`.
- **`.mdls`** (`xa_ex_4030`): 6 PSMT8 128x128 textures (qwc 1024 each), pixels 0x18000 bytes, CLUTs
  0x1800 bytes.
- **MOBJ in RAM**: the chunk offset fields are relocated **in place** to absolute addresses. 12 MOBJs
  live in that field: three characters (7 textures, ~0x75000-0x84000 bytes) at `0xFE0080`,
  `0x12E0080`, `0x1520080`; six at `0xD00E00`-`0xD88E80`; and the embedded ex_6050 at its data address
  (`D_002E31F0`, + the build's data shift).
- **Character mesh chain**: one `CNT` qwc 239, `STCYCL 1,1; UNPACK V4-32 num=238 +TOPS; MSCNT`. The
  stream opens with op 0 records (bones 0x21, 0x20, 0x43), each followed by 7 empty qwords (lit:
  matrix + 3 light rows, filled per frame), then op 1 with arg 0x1A0. Skipping op 1 by `arg` bytes
  lands on an op 8 at +0x1930, so the record length rule above is not exact yet (`tools/vu/vif_chain.py
  --file F --rel BASE --stream` walks these).
  *Session 17:* settled. Op 1 is exactly `arg` bytes; +0x1930 is past the end of that 239-qword packet
  (0xEF0 bytes), so the walk had run over the packet's `0x8000` record, whose `arg` (48) steps over
  the `MSCNT` qword and the next DMA tag to the next packet's first record. `tools/vu/rb_stream.py FILE
  --scan --ram` walks all 15 model chunks of the new savestate (12 `MOBJ`, 3 `MENV` weapons; 50 parts,
  390 packets, 7,530 records, 24,854 vertices) with zero errors; `--mobj 80` does the same for
  `xa_ex_4030.mdls` (7 parts) and the ELF's three embedded models also pass. Only ops 0, 1 and 0x8000
  occur; every main part has `g = 0`, every alternate (shadow) part `g = 2`, no part is skinned.
  *Session 142 (the disc):* `rb_stream.py --scan` over all 500 `.mdls` and 233 `.ard` files walks
  1,489 `MOBJ` / `MENV` chunks (7,974 parts) with zero errors: `g = 0` 6,737 parts, `g = 2` 665, and
  **572 skinned parts (`g = 1`)**, all in the boss-series models `xa_<ww>_7xxx.mdls` (41 files, e.g.
  `xa_al_7000`, `xa_ex_7010`) plus `xa_lm_3000`. Their packets open with an op 2 bone-index list,
  then op 0 records: `w = 0` loads matrix slot `z` (0-2), `w = 1` is the palette base, `w = 2` the
  palette entries after it (8 qwords apart; their `z` just counts on and is not read). A vertex has
  1 to 6 influences (256,490 / 54,684 / 16,579 / 2,528 / 414 / 28 vertices); each influence takes the
  next index of the op 2 list: 0-2 = a slot, `0x100 + 8 j` = palette entry j of the current base
  (renderer-spec §2.3).
  The savestate (session 16 M12-float build, End of the World) also shows the draw instances: see
  renderer-spec §2.3.1.

### `URSL` (eye overlay, `func_00175708`)

+0x08 rel image header (16 bytes, uploaded by `func_0015fa20`), +0x10 rel
pixels, +0x18 rel CLUT, +0x20 rel {s32 n0, rel table0, s32 n1, rel table1}
(two lists used by `func_00174fc0` to place the left and right sprites).
