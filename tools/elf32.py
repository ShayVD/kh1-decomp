"""Minimal little-endian ELF32 reader (stdlib only).

Enough for: program headers of the original game ELF, section headers and
symbol tables of our own objects and linked ELFs.
"""
from __future__ import annotations

import struct
from dataclasses import dataclass
from pathlib import Path

PT_LOAD = 1
PF_X = 1
SHT_SYMTAB = 2
SHT_NOBITS = 8
STT_FUNC = 2
SHN_UNDEF = 0


@dataclass(frozen=True)
class Segment:
    type: int
    offset: int
    vaddr: int
    filesz: int
    memsz: int
    flags: int


@dataclass(frozen=True)
class Section:
    index: int
    name: str
    type: int
    flags: int
    addr: int
    offset: int
    size: int


@dataclass(frozen=True)
class Symbol:
    name: str
    value: int
    size: int
    type: int
    bind: int
    shndx: int


class Elf:
    def __init__(self, data: bytes, path: Path | None = None):
        if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 1:
            raise ValueError(f"{path or 'data'}: not a little-endian ELF32 file")
        self.data = data
        self.path = path
        (self.e_type, self.e_machine, _ver, self.entry, phoff, shoff, self.e_flags,
         _ehsize, phentsize, phnum, shentsize, shnum, shstrndx) = struct.unpack_from(
            "<HHIIIIIHHHHHH", data, 16)
        self.segments = [
            Segment(*struct.unpack_from("<IIIxxxxIII", data, phoff + i * phentsize))
            for i in range(phnum)
        ]
        self.sections: list[Section] = []
        if shoff and shnum:
            raw = [struct.unpack_from("<IIIIIIIIII", data, shoff + i * shentsize) for i in range(shnum)]
            names_off = raw[shstrndx][4] if shstrndx < shnum else 0
            for i, (name, typ, flags, addr, off, size, *_rest) in enumerate(raw):
                self.sections.append(Section(i, self._cstr(names_off + name) if names_off else "",
                                             typ, flags, addr, off, size))

    @classmethod
    def load(cls, path: Path) -> "Elf":
        return cls(Path(path).read_bytes(), Path(path))

    def _cstr(self, off: int) -> str:
        end = self.data.index(b"\0", off)
        return self.data[off:end].decode("latin-1")

    def section(self, name: str) -> Section | None:
        return next((s for s in self.sections if s.name == name), None)

    def symbols(self) -> list[Symbol]:
        out: list[Symbol] = []
        for sec in self.sections:
            if sec.type != SHT_SYMTAB:
                continue
            strtab = self.sections[struct.unpack_from(
                "<I", self.data, self._shdr_off(sec.index) + 24)[0]]
            for i in range(sec.size // 16):
                name, value, size, info, _other, shndx = struct.unpack_from(
                    "<IIIBBH", self.data, sec.offset + i * 16)
                end = self.data.index(b"\0", strtab.offset + name)
                out.append(Symbol(self.data[strtab.offset + name:end].decode("latin-1"),
                                  value, size, info & 0xF, info >> 4, shndx))
        return out

    def _shdr_off(self, index: int) -> int:
        shoff = struct.unpack_from("<I", self.data, 32)[0]
        shentsize = struct.unpack_from("<H", self.data, 46)[0]
        return shoff + index * shentsize

    def vaddr_to_offset(self, vaddr: int) -> int | None:
        for seg in self.segments:
            if seg.type == PT_LOAD and seg.vaddr <= vaddr < seg.vaddr + seg.filesz:
                return seg.offset + (vaddr - seg.vaddr)
        return None

    def read(self, vaddr: int, size: int) -> bytes | None:
        off = self.vaddr_to_offset(vaddr)
        if off is None or self.vaddr_to_offset(vaddr + size - 1) is None:
            return None
        return self.data[off:off + size]
