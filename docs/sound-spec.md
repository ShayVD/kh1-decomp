# Sound: the EE side of the IOP driver, as the Vita audio layer's interface

Session 85 (static, read from the C; nothing here was checked on a console or a host run). This is the
contract a Vita audio layer has to honour if it keeps src/sound/snd_rpc.c and implements
`PlatSifCallRpc` for server 17 (vita-port-plan §1 iop.h, §3 "Sound"), or the list of entry points it has
to provide if it replaces snd_rpc.c whole. No IRX is needed to write the EE side: what the IOP does with a
command is inferred from what the EE sends and what it later reads back. The sequence format (`.bgm`), the
wave bank format (`.wd`) and the SE tables are not documented here (they need the IOP module, a session of
its own).

Files: src/sound/snd_rpc.c (the driver's EE side, 0x001ec7c0-0x001edc50, 51 functions), src/sound/sndctl.c
(the game's sound layer over it), src/sound/objse.c / objse.nostrict.c (object sounds and voices),
src/event/sound.c (the script's sound commands), src/event/voice.nofill.c (event voices).

## 1. Transport

- **Bind**: `func_001ec7d0(mode)` binds SIF RPC server **17** (`D_003E3C88`; it retries until the client's
  server pointer is set and prints "SslInit Bind Error" if the bind fails), clears the shared blocks and the
  queue, then sends **RPC 0** with `{&status (D_0063D640), mode, &message (D_0063F640)}`. `mode` is 0 at boot
  (gamestate.c `func_00109288`), 1 on the soft reset (`func_00109658`), 2 on a room load
  (roomload.c `func_00112840`, `func_00112e98`). What the IOP does with it is not known (inferred: how much
  to reset).
- **Direct calls**: every call goes through the one 0x2000-byte buffer `D_00633640`, as both send and
  receive: the arguments are in words 0..3, **the answer is word 0**. Unanswered, a call reads back its own
  first argument (the null platform relies on this). The calls are synchronous (mode 0, no end callback).
- **Queued commands**: most commands are not sent at once. `func_001ed000(cmd, a..g)` writes an 8-word
  record into the queue `D_00635640[1024][8]` (count `D_003E3CB0`; on 1024 the count wraps to 0 and it prints
  "sound:cue buff over"), unused records are all -1. `func_001edba0` sends the queue as **RPC 30**
  (`0x1E`) if record 0 is in use, then refills it with -1 and zeroes the count. **The send is 0x2000
  bytes: only the first 256 records reach the IOP**; records 257-1024 of one flush are written and then
  thrown away by the refill (a frame never queues that many in practice: inferred). A port that reads the
  whole queue changes nothing for any count up to 256.
- **When the queue is flushed**: once a frame at the end of the sound-effect update (sndctl.c
  `func_0011de90`), and by hand after the boot bank load (`func_0011cd20`), the sound init
  (`func_0011c9c0`) and the pause (pause.c `func_00113e28`).
- **Return values**: every queuing function returns `D_00633640[0]`, the last direct call's answer, which no
  caller reads. The one direct-call answer the main ELF reads is RPC `0x30`'s.
- **Group mask** `D_003E3C80` (`func_001ec7c0(mask)`): a set bit drops the command group before it is
  queued: **1** music start (cmd `0xC`), **2** SE start (cmd 5), **4** stream start (cmd `0x12`), **8**
  object SE start (cmd `0x29`). Callers: 0 at room start (roomload.c `func_00113558`) and in two VM
  library entries (vm_lib.c), `0xE` in objscmd.c `func_0012aed0` after system sound `0x41`: every new
  sound except music is muted until the next room (inferred: a game over or a scene cut).

## 2. The status block the IOP writes (`D_0063D640`, 0x2000 bytes)

The IOP writes it by DMA; each reader calls `PlatFlushCache(0)` first. A Vita mixer writes it in place.

| Offset | Layout | Read by | Meaning |
|---|---|---|---|
| +0x0000 | 24 x 0xB4 `SndSe` | `func_001ecb08` | SE voices: +0 `used` (s8), +4 sub index, +0xC bank, +0x10 SE id |
| +0x1800 | 4 x 0x48 `SndStream` | `func_001ecd08`, `func_001eced0` | streams: +0 kind (bit 7 masked: 0 object SE, 1 voice), +2 / +3 the object SE's (bank, id), +4 `used`, +0x10 the voice's id (its data pointer), +0x18 returned by `func_001eced0` (no caller in the main ELF; inferred: play position) |
| +0x1C08 | s32 (`D_0063F248`) | `func_001ecfb0` <- io/cdqueue.c `func_0011fec0` | **disc error**: 1 for more than 30 frames raises the disc-error state (`D_002C5968.b1`) and the re-read check |
| +0x1F00 | s32 (`D_0063F540`) | `func_001ecfd8` (10 callers) | **bank transfers not yet done** (below) |

**The transfer count** (+0x1F00) is the one word the game waits on. The EE adds one for each transfer it
queues (commands 3, 4, `0xB` and `0x28`: `func_001ed658`, `func_001ed220`, `func_001ed460`, `func_001ed780`)
and the IOP's copy of the block replaces the word once it has the queue, counting down as each transfer
finishes (inferred). Boot (`func_0011cd20`) spins until it is non-zero after flushing; the bank task
`func_0011cba0`, the object sounds (objse.c, objse.nostrict.c), the summons (summon.c), the object loads
(objreq.c) and the soft reset wait for it to be 0. The null platform (host/null/plat_null.c) takes the sent
transfers off it a frame later (session 86: command `0x28` too, which it had left out: a party voice
bank's count would never have come back, not yet reached on the fake disc); a Vita layer has to do the same once the data is copied, or every bank load
hangs.

**The message buffer** `D_0063F640` (256 bytes): `func_001ecf40(dst)` copies a string the IOP left there
and clears it (no caller in the main ELF; inferred: driver debug text).

## 3. Commands

"Q" = queued (8-word record, sent at the next flush), "R" = a direct RPC. Arguments are in order after the
command number. Banks / slots: **0 and 1** the two music tracks (field and battle, `D_002C1364` names the
playing one), **2** the system SE bank loaded at boot (`D_009A0000`, gamestate.nostrict.c), **-1** the
room's SE bank (roomload.c), **-8** the event SE bank ("eventse/%s_%03d.dat", event/sound.c), **-3 ... -7**
object / party banks (objreq.c, `func_00146928`), **-9** cleared at room load (the meanings of -1 / -3 ...
-9 are from the callers, inferred). A system SE (id < 1000) always plays from bank 2; other ids from -8 or
-1 (sndctl.c `func_0011d080` / `func_0011d140`).

### Bank and data transfers (counted in +0x1F00)

| Cmd | | EE function | Arguments | Senders | Meaning |
|---|---|---|---|---|---|
| `0x26` | Q | `func_001ed128` | type, slot | sndctl.c init and loads, roomload.c, objreq.c | free a slot before a load: type 0 wave data, 1 sequence, 2 / 3 SE tables (from which transfer follows each, inferred); slot as above |
| 3 | Q +1 | `func_001ed658` | slot, EE address, size | music / wave / SE / object loads | **wave data** to sound RAM (the `.wd` file, or chunk 1 of a music `.dat`, or the non-"SeSep" entries of an SE `.dat`) |
| 4 | Q +1 | `func_001ed220` | slot, EE address, size | boot SE bank, SE `.dat` loads, objreq.c | **SE tables** (the "SeSep" entries of an SE file, or chunk 0 of the boot bank) |
| `0xB` | Q +1 | `func_001ed460` | slot, EE address, size | music `.dat` chunk 0, `amusic/music%03d.bgm` (`func_0011eb88`) | **sequence data** |
| `0x28` | Q +1 | `func_001ed780` | address, size, `D_002C5C48` | objse.c `func_001570d0` | a party member's voice bank (`.vsb`, objse.nostrict.c `func_001571a8`) |

The EE reads the data from its own memory, so the buffer must stay valid until the count says the
transfer is done: the music file buffer `D_00F20000` / `D_003DABD4`, the room's bank and the boot bank
`D_009A0000` are reused right after. A music `.dat` (`amusic/music%03d.dat`) is a header with two
`{offset, size}` chunks at +0x10 (sequence, wave); if the wave chunk's word 1 is above `0x7547F`
(480,383 bytes) the track takes both music slots (both are freed and the load goes to slot 0:
`func_0011cbe0`, `func_0011ec08`). `amusic/wave%04d.wd` goes to slot 0 or 1 by command 3 alone.

### Music (tracks 0 / 1)

| Cmd | | EE function | Arguments | Senders | Meaning |
|---|---|---|---|---|---|
| `0xC` | Q, mask 1 | `func_001ed4b8` (`func_0011c7a8`) | track, start volume, volume, fade frames, flag, frames2 | sndctl.c `func_0011e480` / `func_0011e4d0` / `func_0011e610`, event/sound.c | **start a track**: volumes 0..0x3FFF (0x3000 is the game's full volume), the script gives the fade as frames x 8; `func_0011e610` starts at the target volume (0x3000) or at 0 with a fade; flag 1 / frames2 240 in the battle-to-field switch (inferred: resume from the paused position / crossfade time) |
| `0xD` | Q | `func_001ed520` (`func_0011c7d8`) | track | sound init, event/sound.c, music loads | **stop a track** |
| `0xE` | Q | `func_001ed560` (`func_0011c7c0`) | track, volume, frames | room change (0, 0, 360), event/sound.c (volume, frames x 8), objscmd.c, the field / battle switch | **fade a track** to a volume |
| `0x2F` | R | `func_001ed5a8` (`func_0011c7f0`) | track | event/sound.c `func_001e8b08` | a request the script then polls with `0x30` (inferred: prepare / pause the track) |
| `0x30` | R | `func_001ed600` (`func_0011c808`) | track | event/sound.c `func_001e8b50` | **answer read**: 0 = not yet, the script command retries next frame; the null platform answers 1 |

The field / battle switch (`func_0011e538`, every frame unless `D_002BCDC4`): when the battle flag
`D_002C5958.b0` changes and the two tracks differ, it fades one track out over 960 / 720 frames and starts
the other (`func_0011e480` battle, `func_0011e4d0` field).

### Sound effects (the slots in sndctl.c `D_004E3450`, 40 static or 128 on the heap)

| Cmd | | EE function | Arguments | Senders | Meaning |
|---|---|---|---|---|---|
| 5 | Q, mask 2 | `func_001ed278` (`func_0011c838`) | bank, id, sub, left, right | `func_0011de90` (positional slots), `func_0011d768` (system SE, about 300 call sites), `func_0011d080` | **play an SE**: volumes 0..0x3FFF per side (0x3FFF centre full) |
| 8 | Q | `func_001ed3c0` (`func_0011c880`) | bank, id, sub, left, right | `func_0011de90`, `func_0011d790` | **set an SE's volume / pan** (`func_0011d790`: 0x1FFF both sides = half volume) |
| 6 | Q | `func_001ed2d8` (`func_0011c850`) | bank, id, sub | `func_0011de90`, the slot stops, init (`-100, -1, -1`: all) | **stop an SE** |
| 7 | Q | `func_001ed370` (`func_0011c868`) | bank, id, sub, -1, frames | `func_0011d108`, `func_0011d3c8`, `func_0011d4e0`, `func_0011d688` | **stop an SE with a fade** |
| 2 | Q | `func_001ed320` | bank, id, sub, value | `func_0011d2d0` <- ppp/pppsys.nostrict.c (value 0 / 1) | a per-voice switch from the effect system (inferred: pause / resume or loop on / off) |
| 9 | Q | `func_001ed410` | 4 words | none in the main ELF | (overlay check) |

Status: `func_001ecb08(bank, id, sub)` answers 1 if any `SndSe` entry with `used` matches (a negative id or
sub is a wildcard; `func_0011e368` asks `(-8, -1, -1)`: "is any event SE playing"). **Its wildcard loops
fall through**: after one finds nothing, the exact-match loop runs on with the pointer already past the 24
entries, so it reads "entries" 24-47 at the same 0xB4 stride (+0x10E0 to +0x2114: the stream area, the
words at +0x1C08 / +0x1F00, and 0x114 bytes past the block, into the message buffer `D_0063F640` and what
follows it). A match there needs a negative id or sub stored at the right place, so it answers 0 in
practice, but a port must keep 0x118 readable bytes after the block. Since session 86 the block's piece
(src/data/data_0063.s) holds the message buffer too (0x2100 bytes, as on the PS2), and the host adds 0x18
zero bytes after it (census.py HOST_TAIL) for entry 47, which on the PS2 reads the text words
`D_0063F744` ... `D_0063F754` and cannot match (`D_0063F754` is never written, so a match needs id 0 and a
negative sub against the pointer `D_0063F748`). tools/host/walkcheck.py finds such walks. Quirk to keep:
`func_0011d2d0` (cmd 2) searches the static table `D_004E3458`, not the live pointer `D_004E3450`, so in a
room that uses the 128 heap slots (roombg.c `func_0011c898(1)`) it finds stale or no slots.

### Streams: voices and object SEs (4 stream entries in the status block)

| Cmd | | EE function | Arguments | Senders | Meaning |
|---|---|---|---|---|---|
| `0x12` | Q, mask 4 | `func_001ecc68` (`func_0011e220`) | VAG address, size, left, right, pitch, hdr[30], hdr[31] | voice.nofill.c, objse.c `func_001577a0` | **play a voice** from EE memory: `pitch = rate * 4096 / 48000` from the VAG header's big-endian rate at +0x10 (4096 = 48 kHz), bytes +0x1E / +0x1F of the header passed through (inferred: flags); the address is the voice's id in the status block |
| `0x14` | Q | `func_001ed6f0` | VAG address, left, right | objse.nostrict.c `func_001576a8` | **move a voice** (volume / pan from the object's screen position) |
| `0x13` | Q | `func_001ed6b0` | VAG address (-1 all) | objse.c `func_001575b0`, voice.nofill.c | **stop a voice** |
| `0x15` | Q | `func_001ed738` | 3 words | none in the main ELF | (overlay check) |
| `0x29` | Q, mask 8 | `func_001ece70` | bank, id, 0, 0 | objse.c `func_001577a0` | **play an object SE as a stream** |
| `0x2A` | Q | `func_001ed7d8` | bank, id, left, right | objse.nostrict.c `func_001576a8` | **move an object SE** |
| `0x2B` | Q | `func_001ed828` | bank, id | objse.c `func_001575b0` | **stop an object SE** |

Status: `func_001ecd08(bank, id, voice)`: `(-1, -1, 0)` the number of streams in use; `(-1, -1, v)` 1 if voice
`v` plays; `(b, i, *)` 1 if object SE (b, i) plays. objse's slots stay in state 4 until it answers 0, and
`func_0011e248` (music / voice busy, with a two-frame grace per started voice, `D_004E39F8`) gates new
loads on it.

### Global settings

| Cmd | | EE function | Arguments | Senders | Meaning |
|---|---|---|---|---|---|
| `0xF` | R | `func_001ed1c8` | 0 / 1 / 2 | pause.c `func_00113df8` / `func_00113e28` | **pause**: 2 on entering, 0 / 1 when the last pause ends (inferred: 2 pause all, 1 resume, 0 resume without music) |
| `0x27` | R | `func_001ed170` | value | init (10), room load (the room table's +0x14, `D_002C1380`) | a per-room setting (inferred: the SPU reverb type / depth) |
| `0x23` | R | `func_001edaf0` | 1 / 0 | config.c, loadmenu.c | **stereo / mono** (config option 4: 1 when the setting is 0) |
| `0x24` | R | `func_001edb48` | `0x7B` / 9 | dkmovie.c before (`func_00111060`) and after (`func_001111b0`) a movie | a mode switch around the IPU movie's own audio (inferred) |
| 1, `0x16`-`0x19`, `0x1B`, `0x1D`, `0x1F`-`0x22`, `0x32` | R | `func_001ed0d0`, `func_001ed870` ... `func_001eda90`, `func_001ec9a8` ... `func_001ecab0` | 0-4 words | none in the main ELF | (overlay check: dktitle.x and the other overlays may call them; vita-port-plan 5.2) |

## 4. What the Vita layer has to do

1. Answer RPC 0 by keeping the status block's address, and write that block: `used` / ids for the SE and
   stream entries (the game polls them to end its slots), 0 at +0x1C08 (no disc error on a memory-card or
   file-system build), and the transfer count at +0x1F00.
2. On RPC 30 walk the records until the first -1 (at most 256), in order, and decode them as above. Copy
   transfer data out of EE memory before the count drops: the buffers are reused.
3. Answer RPC `0x30` (non-zero when the track is ready) and treat the other direct calls as fire and forget.
4. Map volumes 0..0x3FFF per side linearly (inferred) and pitch 4096 = 48 kHz.

Open: the meaning of `0xC`'s last three words, cmd 2's value, RPC `0x24` / `0x27`, the slot numbers -1 /
-3 ... -9, and every command with no caller in the main ELF; the file formats behind commands 3, 4 and
`0xB`. The IOP module (on the disc, the user's own copy) settles all of these; since 2026-10-29 the port runs
it (section 6).

## 5. The null server on the host (session 86)

host/null/sound.c is the EE half of the Vita audio layer without the audio: plat_null.c's
`PlatSifCallRpc` hands it every call. It keeps the status block as section 4 asks (the transfer count; command
5 takes the first free of the 24 SE entries, 6 / 7 free it (7 after its frames), an SE ends by itself
after 60 frames since its length is in the wave bank; `0x12` takes a free stream for the VAG's length,
size / 16 x 28 samples at pitch x 48000 / 4096 Hz, `0x29` for 60 frames; `0x13` / `0x2B` stop them;
the bind (RPC 0) ends every voice), so objse's slots, `func_0011e248` and the event scripts' SE waits
see sounds end as on the console (before, every `used` read 0: everything ended at once). Bank -100
matches every bank and a negative id or sub any (from the init's `(-100, -1, -1)` and
`func_001ecb08`'s wildcards: inferred). With 24 voices in use a new SE is dropped (the IOP's choice is
not known). `KH1_HOST_SND=trace` (or `KH1_HOST_TRACE=6`) prints each record and RPC:

    kh1-host: snd FRAME q 0x05 se-play bank=2 id=12 sub=0 left=16383 right=16383
    kh1-host: snd FRAME rpc 0x27 room-setting 10 0 ...
    kh1-host: snd FRAME end se bank=2 id=12 sub=0

and `python3 -I tools/host/sndlog.py RUN.txt [--frames]` sums them up (commands, RPCs, transfers by
kind and slot, music starts, SEs by (bank, id), voices, the most records one frame sent).
tests/host/sound_test.c (tests/selftest.sh) checks the server on made-up queues (18 checks). On the
fake disc's boot (`KH1_HOST_OVL=stub:2`): 43 commands to the room load (38 `0x26` frees, a wave and an
SE-table transfer to slot 2, two music stops, an SE stop) and the RPCs bind x2, `0x27` x2, pause x1; no
SE plays before the fault.


## 6. The IOP on the port (2026-10-29)

The port plays the game's sound with **the user's own IOP sound driver**: LIBSSL.IRX ("Ohori_Sound_Driver",
SquareSounds SoundDriver, built Apr 26 2002), read from the disc image's root at run time (85,501 bytes on
SLPS_251.98 and on the English patch's image). Nothing from it is in the repo or the VPK: the port carries
a small IOP (an R3000A interpreter and the system calls the driver imports) and an SPU2, and the driver
does the rest, so the sequence, wave bank and SE table formats (section 3's open list) never had to be
reimplemented. src/sound/snd_rpc.c and sndctl.c are unchanged; `PlatSifCallRpc` (host/null/plat_null.c)
hands server 17's calls to host/port/snd.c once the driver is running, and to the null server (section 5)
when it is not (no disc image, no LIBSSL.IRX on it, or the sound switched off).

Files (none in the PS2 build):

| File | What |
|---|---|
| host/port/iop.c, iop.h | 2 MiB of IOP RAM; the IRX loader (R_MIPS_32 / 26 / HI16 / LO16, the import tables, magic `0x41E00000`, stubs `jr ra; li $0, N`); a MIPS I interpreter with delay slots; IOP threads, semaphores, the timer and the SIF RPC server, as high-level answers to the driver's imports |
| host/port/spu2.c | the SPU2: 2 MiB of sound RAM, 2 cores x 24 voices, ADPCM, ADSR, the reverb, and libsd's exports (`kh1_sd_call`) |
| host/port/snd.c | the glue: starts the driver at the game's bind (RPC 0), runs RPCs, ticks and mixes; the host runner's WAV |
| host/vita/audio.c | the Vita's output: a thread on its own core, sceAudioOut's main port, 48 kHz, 256-sample buffers |
| tools/host/sndplay.c | a standalone player: a `.bgm` + `.wd`, a music `.dat`, or SEs from `se000.dat`, to a WAV, without the game |

### The driver's structure (read from the IRX with m2c; addresses are the IRX's own)

- Start: creates its threads, sets the timer handler (0x14e0), registers RPC server 17 (function 0x3174,
  buffer 0xf5c0) on its own thread (0x17f0), which then sits in `sceSifRpcLoop`.
- The timer handler calls func_00650 and returns 0x25800 (the next compare): **a 240 Hz tick**, 200 samples
  at 48 kHz. It signals the tick thread (0x15c4), which waits on a semaphore and works the sequencer and the
  voices; the queue the game sent is run by the RPC function itself (RPC 30, jump table 0xe688), so the
  commands of section 3 take effect between ticks, as on the console.
- The status block (section 2) is written back by `sceSifSetDma` to the EE address the bind gave. On the
  port EE addresses are the 32-bit host pointers; iop.c's SetDma copies straight to them.

Imports the driver uses and how iop.c answers them (export numbers):

| Library | Numbers |
|---|---|
| thbase | 4 CreateThread, 6 StartThread, 0xE ChangeThreadPriority, 0x14 GetThreadId, 0x21 DelayThread |
| thsemap | 4 CreateSema, 7 iSignalSema, 8 WaitSema |
| thvpool | 4, 5, 7, 9, 0xB (a pool kept on the IOP heap) |
| timrman | 4, 10, 20 SetTimerHandler, 22, 23 |
| sifcmd | 0xE, 0x11 RegisterRpc, 0x12, 0x13, 0x16 RpcLoop, 0x17 GetOtherData |
| sifman | 5, 7 SetDma, 8, 0x1D |
| sysmem | 6, 7, 8 (allocations), 14 Kprintf (printed at `KH1_HOST_IOP=1`) |
| sysclib | 12 memcpy, 22 strcmp |
| intrman | 6, 9, 17, 18 |
| loadcore | 5 FlushDcache |
| cdvdman | 0x1C, answered 0 |
| libsd | 4 Init, 5 / 6 Set / GetParam, 7 / 8 Set / GetSwitch, 9 / 10 Set / GetAddr, 11 SetCoreAttr, 17 VoiceTrans, 18 BlockTrans, 19 / 20 the transfers' status, 23 / 24 Set / GetEffectAttr, 25 ClearEffectWorkArea, 26 SetTransIntrHandler, 27 SetSpu2IntrHandler, 30 StopTrans |

libsd's parameter words: register `(p >> 8) & 0xFF`, core `p & 1`, voice `(p >> 1) & 0x1F`. Voice registers
0 VOLL, 1 VOLR, 2 PITCH, 3 ADSR1, 4 ADSR2, 5 ENVX, 6 VOLXL, 7 VOLXR; core registers 8 MMIX, 9 / 0xA MVOL,
0xB / 0xC EVOL, 0xD / 0xE AVOL (a plain s16, no sweep bit: the driver writes 0x7FFF, which read as a sweep
was nearly silent), 0xF / 0x10 BVOL; switches 0x13 PMON ... 0x15 KON, 0x16 KOFF, 0x17 ENDX, 0x18-0x1B
VMIXL / VMIXEL / VMIXR / VMIXER; addresses (bytes) 0x1C ESA, 0x1D EEA, 0x1F IRQA, 0x20 SSA, 0x21 LSAX,
0x22 NAX. SetCoreAttr's entry `2 | core` is the effect enable.

### The SPU2 model

ADPCM (filters {0, 60, 115, 98, 122} / {0, 0, -52, -55, -60}, a shift over 12 read as 9; the loop flags
bit 0 end, bit 1 repeat, bit 2 start), the noise generator (since 2026-10-30, below), the ADSR envelope's rates as the PSX's, 4-point Catmull-Rom
interpolation at 256 steps (the console's is Gaussian), core 0's output into core 1 through AVOL, and the reverb: the
PSX algorithm at half rate over the core's work area, with **the presets read from the disc's own
LIBSD.IRX** (found by the signature `7d 00 5b 00 80 6d`, 0x44 bytes a mode; mode m at the room preset +
(m - 1) x 0x44: 1 room, 2-4 studio, 5 hall, 6 space, 7 echo, 8 delay, 9 pipe). The driver sets mode 5 on
core 0 and 4 on core 1. Without LIBSD.IRX the reverb is off and the rest plays.

**Not modelled** (be direct): BlockTrans (the core's PCM input: the movies' sound, dkmovie.x; answered
0), pitch modulation (the driver sets PMON on 7 notes in the first 20,000 frames of Dive), the IRQ address, the echo / delay modes' feedback, Gaussian interpolation.
Nothing here was compared against a console recording.

### Threads and cost

- The host runner (`KH1_HOST_SND=iop`, or `wav:FILE` to also write what it plays) runs every call at once
  and four ticks a vblank (host/null/main.c).
- The Vita (host/vita/audio.c) uses three threads. A tick thread runs the driver's ticks up to 8 ticks
  (33 ms) ahead of a mixer thread. spu2.c's deferred mode logs each tick's SPU2 writes (SetParam,
  SetSwitch, SetAddr, SetCoreAttr, ClearEffectWorkArea) with a mark at the tick's end, and the mixer
  applies one tick's writes, then mixes its 200 samples into a ring 64 ms ahead of the output. Both
  threads run below the game's threads on any core, so they take the time the game leaves on two cores
  at once. The driver's only read of the mix's state, GetParam ENVX (2,402 reads in 30 s of music110;
  nothing else is read), answers the envelope the mixer published after its last tick. Sound RAM
  transfers and the reverb's attributes still take effect at once. An output thread, paced by
  sceAudioOut, copies 256 samples at a time from the ring and plays silence for any gap (counted as
  "short" on the watchdog's sound line). The game thread's per-frame queue send (RPC 30) goes into a
  16-deep FIFO and returns at once; the tick thread runs the FIFO before each tick. The other RPCs (the
  game reads their answer) take the lock, drain the FIFO and run at once. A sound the game starts
  plays about 100 ms later. `SNDPLAY_THREADS=1` runs tools/host/sndplay.c the same way; over 30 s of
  music110 its output is the same as the one-thread run.
- First Vita run (2026-10-29, the first version: one thread on core 2 above the GPU thread): once the
  title music started, the thread needed about 80% of core 2 (4.7 s of 6 s for 19 voices). It fell behind,
  so the sound broke up, and it starved the GPU frame's thread, so the picture lagged. Since then:
  - the interpreter is direct-threaded, with no per-instruction checks of the pc (import stubs and the
    C-call return address are two made-up opcodes in RAM), and does one divide for div / divu (the A9 has
    no divider);
  - the mix runs voice by voice over each stretch between ticks, with no aliasing reloads, inlined
    envelopes and a 256-step table for the interpolation;
  - the threads were split as above.
  The host does the same work in 0.55 times the time it took before. The output is the same apart from
  the interpolation table's rounding, and the game's run over the Dive script is line for line the same.
- Second Vita run (the two threads): no lag; the title's music (19-26 voices, about 5.4 million IOP
  instructions a second) kept the mixer busy the whole time and it fell short in a few 2 s windows
  (4-24 of about 400 buffers), heard as small breaks. In Dive (3 voices) none fell short. Since then
  three of the driver's functions run as C (iop.c `natives[]`, a fourth since): func_00150, func_00434 and func_004f0,
  the leaf functions the per-tick voice loop calls for every voice to set or clear the voice's bit in
  the masks of registers to send. They were about 28% of the instructions with 18 voices playing.
  Each one is patched only when an FNV-1a of its relocated words matches the known LIBSSL.IRX, so
  another driver is still interpreted, and `KH1_HOST_IOP=nonative` turns them off. The output is the same
  byte for byte (sndplay over music110.dat; the Dive run's WAV and log).
- Third Vita run (build c): no lag; the title's music still left the one sound thread busy the whole
  time and 5-16 buffers in 400 short in some 2 s windows; the New Game load into Dive (game, GS worker
  and sound all busy for about 10 s) 17-61 short. Hence the split of the ticks and the mix onto two
  threads above.
- Fourth Vita run (build d, the two threads): no short buffers on the title's music (about 1.1 s ticking
  and 1.2 s mixing per 2 s, on two cores) or in Dive. The New Game load into Dive still fell short for
  about 10 s (14-51 buffers in 400 per 2 s). There the driver does about twice its usual work: 45% of
  its instructions in that load are func_0d8dc, a linear search of its table of loaded banks, run for
  each bank chunk it takes in. func_0d8dc now runs as C too (iop.c `native_0d8dc`: the same scan, with
  the pool's FreeVpl / pAllocateVpl answered by the same import code, patched only when its hash
  matches and its two stubs are thvpool 9 and 7). The Dive run's log and WAV stay byte-identical.
- Cost on the host: about 2.5 million IOP instructions a second of sound over the Dive run (3.7 G in
  25 minutes), plus the mix. **Not measured on a Vita yet** after these changes; the watchdog's sound
  line (vita-build.md "Sound") prints the mixer's milliseconds per 2 s.

### The driver as C and the mix in passes (2026-10-31, native-plan stage 8 steps 1-2)

The Vita's sound threads were about 800 ms ticking and 630 ms mixing per 2.4 s window in the Dive (Shay's logs of
2026-10-31, `sndprio=-4`), on cores the game, the GS worker and the GPU thread also need. Both are now much cheaper,
with the output unchanged byte for byte.

**The driver as C** (tools/host/iop_translate.py, host/port/iop.c `KH1_IOP_REC`). A profile of the IOP instructions
per function (sndplay over music110) put func_0a2a8 (the per-voice update) at 35% and six more functions at another
55%: too many to write by hand, as func_00150 and the other three natives were. So the build translates the whole
driver instead, as tools/vu/vu1_translate.py does the VU1 programs:

- The build looks for `LIBSSL.IRX` in the repo's root (copy it from your own disc's root; `.gitignore` refuses
  `*.IRX`). tools/host/census.py (host and Vita builds alike) runs the translator into out/gen/iop_rec.c, never
  committed, and compiles iop.c with `-DKH1_IOP_REC`. Without the file the build is as before.
- The translator loads and relocates the IRX at iop.c's base as the loader does, finds its import stubs, takes
  every `jal` target (and the lui / addiu code pointers that start right after a `jr ra`: the timer handler, the
  threads, the RPC function) as a function, follows its branches and its jump tables (the module's relocated
  code pointers inside the function), and writes each as one C function over the interpreter's state: the
  registers it uses in locals (handed back through the context at every call and at its return), the delay slots
  in place, iop.c's own memory helpers (the same bounds checks and alignment), and the same instruction count
  (each block adds its length, an import's stub one, as run() counts).
- A call to another translated function is a C call; to an import, iop.c's hle(); to a function left to the
  interpreter, or through a register, the interpreter nested (rec_interp: $ra is the magic return address for the
  call and given back after it). Functions that can block their thread (WaitSema, DelayThread, the RPC loop,
  directly or through a call) stay interpreted: 5 of 98 (the tick thread's loop func_015c4, the bank compaction
  func_0df50 and func_072fc / 0b118 / 0b370); their callees are C.
- At load, iop.c compares an FNV-1a of the relocated text with the translated one's; only on a match does each
  translated function's first word become `OP_REC | index` (primary opcode 0x3C), which run() answers by calling the
  C. Another driver runs on the interpreter (and the four natives) as before. `KH1_HOST_IOP=norec` (or `nonative`)
  turns it off. The log says `kh1-iop: the driver runs as C (93 functions translated at build time)`.

**The mix in passes** (host/port/spu2.c voice_render; the old loop is kept under `KH1_SPU2_SLOWMIX`). A voice's
stretch between two ticks is mixed in three passes, the numbers the same as the sample-by-sample loop's:

1. the envelope, env_at[i]: its level changes only when its counter overflows, and between overflows a phase's
   condition (attack's top, decay's sustain level, release's 0) cannot newly hold, so the samples between are
   filled at once; it stops where the release ends the voice;
2. the wave up to there (the interpolation or the noise, the pitch counter, the ADPCM blocks and their flags), the
   voice's state in locals; a block end that stops the voice stops it here (env 0, off) as block_end() does, and the
   envelope's leftover state is then never read (key-on resets it);
3. the volumes and the four sums: with no sweep the volumes are constants and the loop is NEON on the Vita (a sum
   the voice is not routed to goes to a sink).

decode_block keeps the ADPCM history in locals and the reverb step its buffer and position (the stores through the
voice and the reverb made the compiler reload them).

**Checked** (host, the English patch's image): `make` byte-identical; sndplay's WAV of all 39 music `.dat` files on
the disc (20 s each) and of 12 system SEs from se000.dat byte-identical to the old code's, one-thread and
`SNDPLAY_THREADS=1`; the host runner over tests/host/pads/dive_en.txt to frame 91,000 with `KH1_HOST_SND=wav:`
byte-identical WAV (291 MB) and log, and to frame 20,000 the same IOP instruction count as the fully interpreted
driver (`nonative`); the x86 build and an ARM (cortex-a9, NEON) build under qemu-arm give the same WAV.

**Cost**, ARM instructions under qemu-arm for 3 s of music110 (19-26 voices; the TB log of `-d in_asm,exec,nochain`
counted per function): the driver 400 M -> 70 M (5.7x), the mix 824 M -> 395 M (2.1x), 1,236 M -> 486 M in all. What
is left of the mix: the wave pass (the interpolation, ~150 M), the reverb's two cores at half rate (~120 M: about 290
instructions a step, straight-line), the ADPCM decode (~51 M). **Not measured on a Vita yet**: the watchdog's sound
line gives the two threads' milliseconds per window.

### Checked (2026-10-29, on the English patch's image)

- `tools/host/sndplay.c`: the title's and other tracks (`music097.bgm` + `wave0099.wd` and others) and
  system SEs from se000.dat render at sensible levels; the reverb adds energy without running away.
- The host runner over tests/host/pads/dive_en.txt (91,000 frames): the driver starts at the bind, 44,020
  RPCs; the title music from about 15 s, then Dive's music, SEs and the event voices into Destiny
  Islands, with sound in every 10 s of the 25-minute WAV.
- **Timing moves with real sound**: the run is frame-identical to the null server's until frame 63,559,
  where the next event voice set (voice/event/di/di_002.vset) loads 24 frames later, since the event
  waits for the line before to finish playing (the null server ends a stream by its computed length).
  The pad script, timed against the null server, then drifts and misses the last room change near frame
  77,600. Pad scripts stay on the null server (the host's default); a script for the driver would need
  retiming.
- `make` byte-identical, `make test` and the selftests pass (the null server is still the host's default,
  so tests/host/sound_test.c is unchanged).

### The pool's block limit: most room SEs were silent (2026-10-30)

Reported on the Vita as "not all of the sound effects work". A host run of the Dive script (`KH1_HOST_SND=iop`,
frames 0-20,000) counted, for each SE play the game queued, whether a key-on followed within 8 ticks: of 325
plays, nearly all on banks -1 (the room's) and -8 (the event's) started no voice; system SEs (bank 2) did.

The cause was iop.c's model of thvpool, not the driver or the SPU2. The driver keeps every bank chunk in one
pool (CreateVpl, 0x3C000 bytes) with an entry in its table at +0xCADF0, one pool block each, and a room's SE
bank is split into one entry per SE ("SeSep": 62-88 for Dive's rooms). iop.c's pool kept its blocks in a side
table of **64**, so once the boot bank, the music and the room's first SEs had taken them, every further
pAllocateVpl failed though most of the pool was free. The driver then runs its "Rearranging" compaction
(func_0df50, Kprintf'd), which cannot help, and drops the chunk. So the room's SE table was cut short, its wave
banks (the `.wd` chunks behind them) never registered (no "WaveStandby bank(-1)" line at `KH1_HOST_IOP=1`), the
battle track's bank (slot 1) never loaded, and later SE banks (-3, -6, -8) loaded with count 0. A play of an
SE whose table entry did load still failed: its note asks for its wave bank by number (func_051cc ->
func_0dda8(0, bank, program)), finds none, keys the voice off and frees it, the SE's tracks end at once, and
two frames later the game (objreq.nostrict.c func_001474a0, polling `func_0011d6f0`) sees it ended and sends a
stop (command 6).

The side table now holds 2048 blocks (more than the driver's 1,536 entries). The same run: no
"Rearranging", every bank's Standby line, 3,277 key-ons instead of 934, and the few plays left without one are
event-bank ids the loaded event bank does not have (20209 ...: one each). The driver does more work with the
SEs playing: 1.30 G IOP instructions over the run instead of 0.80 G.

The same run turned up **noise**: sceSdSetCoreAttr(SD_C_NOISE_CLK | 1, 0x2E-0x3F) on core 1 and NON on 274 key-ons
(wind and whooshes). spu2.c now has the PSX / PS2 noise generator per core (psx-spx "SPU Noise Generator":
the clock's bits 0-1 the step - 4, bits 2-5 the shift; a 16-bit level shifted left with the parity of bits
15, 12, 11 and 10, inverted), and a voice with its NON bit plays the noise in place of its wave under its own
envelope and volumes; the wave runs on underneath for its loop and end flags. Not compared against a
console.

Section 3's open questions can now be answered from the driver's own code (the m2c output of the IRX is
easy to make again, but it is the user's copy and stays out of the repo); that is not done here.
