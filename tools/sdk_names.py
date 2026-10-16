#!/usr/bin/env python3
"""Suggest names for SCE SDK functions in the sdk segment.

Two evidence sources, both from the user's own ELF, nothing from Sony:
1. EE kernel syscall stubs (`li $v1,N; syscall`). Syscall numbers and names
   follow the public ps2sdk kernel documentation (ee/kernel/include/kernel.h).
   Negative numbers are the interrupt-context `i` variants.
2. Error strings: SCE libraries print messages that start with the calling
   function's name ("sceGsSyncPath: DMA Ch.1 does not terminate"). A function
   whose only such prefix is one sce name is named after it.

Prints functions.tsv lines with the evidence as a comment; review before use.
"""
from __future__ import annotations

import re
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kh1tool as K  # noqa: E402
import mips  # noqa: E402

SYSCALLS = {
    0x01: "ResetEE", 0x02: "SetGsCrt", 0x04: "Exit", 0x06: "LoadExecPS2", 0x07: "ExecPS2",
    0x10: "AddIntcHandler", 0x11: "RemoveIntcHandler", 0x12: "AddDmacHandler",
    0x13: "RemoveDmacHandler", 0x14: "_EnableIntc", 0x15: "_DisableIntc", 0x16: "_EnableDmac",
    0x17: "_DisableDmac", 0x18: "SetAlarm", 0x19: "ReleaseAlarm",
    -0x1A: "_iEnableIntc", -0x1B: "_iDisableIntc", -0x1C: "_iEnableDmac", -0x1D: "_iDisableDmac",
    -0x1E: "iSetAlarm", -0x1F: "iReleaseAlarm",
    0x20: "CreateThread", 0x21: "DeleteThread", 0x22: "StartThread", 0x23: "ExitThread",
    0x24: "ExitDeleteThread", 0x25: "TerminateThread", -0x26: "iTerminateThread",
    0x27: "DisableDispatchThread", 0x28: "EnableDispatchThread", 0x29: "ChangeThreadPriority",
    -0x2A: "iChangeThreadPriority", 0x2B: "RotateThreadReadyQueue", -0x2C: "iRotateThreadReadyQueue",
    0x2D: "ReleaseWaitThread", -0x2E: "iReleaseWaitThread", 0x2F: "GetThreadId",
    0x30: "ReferThreadStatus", -0x31: "iReferThreadStatus", 0x32: "SleepThread",
    0x33: "WakeupThread", -0x34: "iWakeupThread", 0x35: "CancelWakeupThread",
    -0x36: "iCancelWakeupThread", 0x37: "SuspendThread", -0x38: "iSuspendThread",
    0x39: "ResumeThread", -0x3A: "iResumeThread", 0x3C: "SetupThread", 0x3D: "SetupHeap",
    0x3E: "EndOfHeap", 0x40: "CreateSema", 0x41: "DeleteSema", 0x42: "SignalSema",
    -0x43: "iSignalSema", 0x44: "WaitSema", 0x45: "PollSema", -0x46: "iPollSema",
    0x47: "ReferSemaStatus", -0x48: "iReferSemaStatus", 0x4A: "SetOsdConfigParam",
    0x4B: "GetOsdConfigParam", 0x4C: "GetGsHParam", 0x4D: "GetGsVParam", 0x4E: "SetGsHParam",
    0x4F: "SetGsVParam", 0x64: "FlushCache", -0x68: "iFlushCache", 0x70: "GsGetIMR",
    -0x70: "iGsGetIMR", 0x71: "GsPutIMR", -0x71: "iGsPutIMR", 0x72: "SetPgifHandler",
    0x73: "SetVSyncFlag", 0x74: "SetSyscall", 0x76: "sceSifDmaStat", -0x76: "isceSifDmaStat",
    0x77: "sceSifSetDma", -0x77: "isceSifSetDma", 0x78: "sceSifSetDChain",
    -0x78: "isceSifSetDChain", 0x79: "sceSifSetReg", 0x7A: "sceSifGetReg", 0x7B: "ExecOSD",
    0x7C: "Deci2Call", 0x7D: "PSMode", 0x7E: "MachineType", 0x7F: "GetMemorySize",
}
SECOND = {0x10: "AddIntcHandler2", 0x12: "AddDmacHandler2"}  # same number, second stub
PREFIX_RE = re.compile(r"^\s*(?:#\s*)?(?:Error\s*:?\s*)?(_?sce[A-Z]\w+)\s*[:(]")


def cstr(elf, addr: int) -> str | None:
    b = elf.read(addr, 128)
    if not b:
        return None
    s = b.split(b"\0")[0]
    if len(s) < 4 or any(c < 9 or c > 126 for c in s):
        return None
    return s.decode()


def hi_lo_targets(f: K.Func, insns) -> list[int]:
    out, live = [], {}
    for i in insns:
        o = mips.op(i.word)
        if o == mips.OP_LUI:
            live[mips.rt(i.word)] = (i.word & 0xFFFF) << 16
        elif o == 0x09 and mips.rs(i.word) in live:
            out.append((live[mips.rs(i.word)] + mips.imm(i.word)) & 0xFFFFFFFF)
    return out


def main() -> int:
    cfg = K.load_config()
    elf = K.require_orig(cfg)
    seg = next(s for s in cfg["segment"] if s["name"] == "sdk")
    lo, hi = K.parse_int(seg["start"]), K.parse_int(seg["end"])
    registry = K.load_registry()
    named = set(registry.values())
    out: list[tuple[int, str, str]] = []
    seen_nums: dict[int, int] = defaultdict(int)
    by_name: dict[str, list[int]] = defaultdict(list)
    for f in K.load_layout():
        if not lo <= f.addr < hi:
            continue
        insns = mips.decode(f.addr, elf.read(f.addr, f.size))
        if len(insns) >= 2 and insns[1].word == 0x0C and insns[0].word >> 16 == 0x2403:
            n = mips.imm(insns[0].word)
            seen_nums[n] += 1
            # Only the libkernl stub table: later copies of the same number
            # are inline syscalls inside other functions (setup code).
            name = SECOND.get(n) if seen_nums[n] == 2 else SYSCALLS.get(n) if seen_nums[n] == 1 else None
            if name:
                out.append((f.addr, name, f"syscall {n:#x}"))
            continue
        prefixes = set()
        for a in hi_lo_targets(f, insns):
            s = cstr(elf, a)
            m = PREFIX_RE.match(s) if s else None
            if m:
                prefixes.add(m.group(1))
        if len(prefixes) == 1:
            p = prefixes.pop()
            by_name[p].append(f.addr)
    for name, addrs in by_name.items():
        if len(addrs) == 1:
            out.append((addrs[0], name, "error-string prefix"))
    for addr, name, why in sorted(out):
        flag = "" if addr not in named else "  # already named"
        print(f"{name}\t{addr:08x}\t# {why}{flag}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
