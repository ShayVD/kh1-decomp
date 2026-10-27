#!/usr/bin/env python3
"""List or copy the saves on a PS2 memory card image (an emulator's card file, e.g. PCSX2's
Mcd001.ps2) into the port's card directory (host/port/mc_dir.c).

    python3 -I tools/host/ps2mc.py list CARD.ps2
    python3 -I tools/host/ps2mc.py extract CARD.ps2 OUTDIR [--match BISLPS-25198-]

The card is the user's own file and the saves are their own data: never commit either.
`extract` writes OUTDIR/<save dir>/<file> for every top-level directory whose name starts with
--match (default: this game's, BISLPS-25198-), with each file's and directory's modified time set
from the card's (the load screen lists the newest save first).  A PCSX2 folder card (a directory
holding _pcsx2_superblock) needs no tool: its save directories are copied as they are.

The format (the PS2 card's file system, as the homebrew mcfs readers document it): pages of 512
bytes, each followed by a 16-byte spare (ECC) area in an 8,650,752-byte image and not in an
8,388,608-byte one; the superblock in page 0 gives the page and cluster sizes, the indirect FAT
cluster list, the allocatable area's first cluster and the root directory's cluster.  A FAT entry
has bit 31 set when the cluster is in use and the next cluster (relative to the allocatable area)
in the low 31 bits, 0x7FFFFFFF ending the chain.  A directory is a chain of 512-byte entries: the
mode (0x8000 exists, 0x20 a directory, 0x10 a file), the length (bytes, or a directory's entry
count with "." and ".."), the created time, the first cluster, the modified time and the name at
0x40.  Times are the card's (JST): resv, sec, min, hour, day, month, u16 year."""
import argparse
import calendar
import os
import struct
import sys

MAGIC = b"Sony PS2 Memory Card Format "


class Card:
    def __init__(self, data):
        if not data.startswith(MAGIC):
            raise SystemExit("not a PS2 memory card image (no superblock magic)")
        self.data = data
        (self.page_len, self.ppc, self.ppb, _unused, self.clusters, self.alloc_off, _alloc_end,
         self.root) = struct.unpack_from("<4H4I", data, 0x28)
        self.ifc = struct.unpack_from("<32I", data, 0x50)
        raw = self.page_len + (16 if len(data) >= (self.clusters * self.ppc) * (self.page_len + 16) else 0)
        self.raw_page = raw
        self.cluster_len = self.page_len * self.ppc
        self.per_cluster = self.cluster_len // 4
        self.fat_cache = {}

    def cluster(self, n):
        """Absolute cluster n's bytes, the spare areas left out."""
        out = b""
        for p in range(n * self.ppc, (n + 1) * self.ppc):
            out += self.data[p * self.raw_page:p * self.raw_page + self.page_len]
        return out

    def fat(self, n):
        """The FAT entry of cluster n (relative to the allocatable area)."""
        fat_i, ent = divmod(n, self.per_cluster)
        ind_i, ind_e = divmod(fat_i, self.per_cluster)
        key = (ind_i, ind_e)
        if key not in self.fat_cache:
            ind = struct.unpack("<%dI" % self.per_cluster, self.cluster(self.ifc[ind_i]))
            self.fat_cache[key] = struct.unpack("<%dI" % self.per_cluster, self.cluster(ind[ind_e]))
        return self.fat_cache[key][ent]

    def chain(self, first, length):
        out = b""
        n = first
        while len(out) < length:
            out += self.cluster(n + self.alloc_off)
            e = self.fat(n)
            if not e & 0x80000000 or (e & 0x7FFFFFFF) == 0x7FFFFFFF:
                break
            n = e & 0x7FFFFFFF
        return out[:length]

    def entries(self, first, count):
        raw = self.chain(first, count * 512)
        out = []
        for i in range(count):
            e = raw[i * 512:(i + 1) * 512]
            if len(e) < 512:
                break
            mode, length = struct.unpack_from("<H2xI", e, 0)
            created = e[8:16]
            clus = struct.unpack_from("<I", e, 0x10)[0]
            modified = e[0x18:0x20]
            name = e[0x40:0x60].split(b"\0", 1)[0].decode("ascii", "replace")
            if mode & 0x8000:
                out.append(dict(mode=mode, length=length, cluster=clus, created=created,
                                modified=modified, name=name))
        return out

    def root_entries(self):
        first = self.entries(self.root, 1)
        return self.entries(self.root, first[0]["length"]) if first else []


def card_time(t):
    """A card time (JST) as a Unix time; 0 when unset."""
    _r, sec, mn, hr, day, mon, year = struct.unpack("<6BH", t)
    if not year or not mon or not day:
        return 0
    return calendar.timegm((year, mon, day, hr, mn, sec)) - 9 * 3600


def walk_saves(card, match):
    for d in card.root_entries():
        if not d["mode"] & 0x20 or d["name"] in (".", "..") or not d["name"].startswith(match):
            continue
        files = [f for f in card.entries(d["cluster"], d["length"])
                 if f["mode"] & 0x10 and f["name"] not in (".", "..")]
        yield d, files


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("cmd", choices=("list", "extract"))
    ap.add_argument("card")
    ap.add_argument("out", nargs="?")
    ap.add_argument("--match", default="BISLPS-25198-", help="top-level directory prefix ('' for all)")
    a = ap.parse_args()
    card = Card(open(a.card, "rb").read())
    if a.cmd == "list":
        for d in card.root_entries():
            if d["name"] in (".", ".."):
                continue
            kind = "dir " if d["mode"] & 0x20 else "file"
            print("%s %-32s %s" % (kind, d["name"], d["length"]))
        return
    if not a.out:
        raise SystemExit("extract needs OUTDIR")
    n = 0
    for d, files in walk_saves(card, a.match):
        dd = os.path.join(a.out, d["name"])
        os.makedirs(dd, exist_ok=True)
        for f in files:
            p = os.path.join(dd, f["name"])
            with open(p, "wb") as o:
                o.write(card.chain(f["cluster"], f["length"]))
            t = card_time(f["modified"])
            if t:
                os.utime(p, (t, t))
        t = card_time(d["modified"])
        if t:
            os.utime(dd, (t, t))
        print("%s: %s" % (d["name"], ", ".join("%s %d" % (f["name"], f["length"]) for f in files)))
        n += 1
    print("%d save(s) copied to %s" % (n, a.out))
    if not n:
        sys.exit(1)


if __name__ == "__main__":
    main()
