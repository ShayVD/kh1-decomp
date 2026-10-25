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
`0xB`. The IOP module (on the disc, the user's own copy) settles all of these.

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

