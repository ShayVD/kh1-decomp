# kh1-decomp build. `make` builds and verifies; `make help` lists targets.
.DEFAULT_GOAL := verify
.SUFFIXES:

PY        ?= python3
KH1       := $(PY) tools/kh1tool.py
ORIG      := $(shell $(KH1) config target.elf)
TOOLCHAIN := tools/toolchain
BINUTILS  ?= mips-linux-gnu-
AS        := $(BINUTILS)as
LD        := $(BINUTILS)ld
INCLUDES  := -Iinclude -Isrc
GEN       := out/gen
PATCHED   := out/kh1.elf
LINKED    := out/linked.elf

SRCS    := $(shell find src -type f \( -name '*.c' -o -name '*.cpp' -o -name '*.cc' -o -name '*.s' \) -not -name '.*' 2>/dev/null | sort)
ifneq ($(KH1_SKIP),)
SRCS    := $(shell echo "$(SRCS)" | tr ' ' '\n' | grep -Ev '$(KH1_SKIP)')
endif
HEADERS := $(shell find include src -type f -name '*.h' 2>/dev/null)

# Regenerate the per-source rules only when the set of sources changes.
$(shell mkdir -p $(GEN); echo "$(SRCS)" | cmp -s - $(GEN)/srclist || echo "$(SRCS)" > $(GEN)/srclist)

ifeq ($(filter clean distclean help toolchain check layout rank,$(MAKECMDGOALS)),)
-include $(GEN)/objects.mk
endif

.PHONY: all build verify check layout rank objdiff report progress progress-update toolchain test clean distclean help shift data-relocs

all: verify

help:
	@echo "make toolchain        fetch compilers + objdiff-cli into tools/toolchain/"
	@echo "make check            hash $(ORIG) against the pin in kh1.toml"
	@echo "make layout           regenerate layout.tsv from $(ORIG)"
	@echo "make build            compile src/, link, patch into $(PATCHED)"
	@echo "make verify           build, then require byte-identical output (default)"
	@echo "make rank             rank undecompiled game functions, easiest first (ARGS=--help)"
	@echo "make objdiff          write objdiff.json for the objdiff GUI"
	@echo "make report           objdiff-cli per-function match report"
	@echo "make progress         print the progress tracker"
	@echo "make progress-update  rewrite docs/progress.md + history (end of session)"
	@echo "make test             tool self-tests (no game ELF needed)"
	@echo "make shift            shiftable build: fresh ELF linked symbolically, M0 check (docs/shiftable-plan.md)"
	@echo "make shift SHIFT_MODE=m1|m2|m12   code rotated / data moved / both, inverse-map comparator against M0"
	@echo "make shift SHIFT_MODE=m12 SHIFT_DRAFTS=1   near-miss C drafts in place of their asm exports (static diff)"
	@echo "make data-relocs      regenerate data_relocs.tsv (pointers in the data blob)"

$(ORIG):
	@echo "error: $(ORIG) not found. Copy the ELF from your own disc to the repo root." >&2
	@echo "       It is gitignored and must never be committed." >&2
	@exit 1

$(GEN)/objects.mk $(GEN)/symbols.ld: $(GEN)/srclist $(SRCS) kh1.toml functions.tsv tools/kh1tool.py
	@$(KH1) gen

# Data pieces (phase 4, step 4): src/data/data_*.s name each shared data table as a
# PIECE, an .incbin of out/data/pieces/<name>.bin cut from the user's ELF here (never
# committed). Their objects wait for the cut.
PIECE_SRCS   := $(filter src/data/data_%.s,$(SRCS))
PIECES_STAMP := out/data/pieces.stamp
$(PIECES_STAMP): $(ORIG) $(PIECE_SRCS) tools/shift/cut_pieces.py
	@$(PY) -I tools/shift/cut_pieces.py --stamp $@ $(PIECE_SRCS)
$(patsubst %,out/build/%.o,$(PIECE_SRCS)): $(PIECES_STAMP) include/data/piece.inc

build: $(PATCHED)

$(PATCHED): $(ORIG) layout.tsv kh1.ld $(GEN)/symbols.ld $(OBJS) tools/kh1tool.py
	@$(KH1) link-script
	@if [ -n "$(strip $(OBJS))" ]; then \
		$(LD) -EL -e 0 --no-check-sections --no-warn-mismatch -T kh1.ld -o $(LINKED) $(OBJS); \
	fi
	@$(KH1) patch

verify: $(PATCHED)
	@$(KH1) verify

check: $(ORIG)
	@$(KH1) check

layout: $(ORIG)
	@$(KH1) layout

rank: $(ORIG)
	@$(KH1) rank $(ARGS)

objdiff: $(PATCHED)
	@$(KH1) objdiff

# objdiff's GUI rebuilds a unit by running `make out/objdiff/base/<unit>.o`.
out/objdiff/base/%.o: FORCE
	@$(MAKE) --no-print-directory objdiff
FORCE:

report: objdiff
	@$(KH1) objdiff-report

progress: $(PATCHED)
	@$(KH1) progress

progress-update: report
	@$(KH1) progress --write

toolchain:
	@tools/setup_toolchain.sh

test:
	@$(PY) tools/test_mangle_gcc2.py
	@tests/selftest.sh
	@tools/check_no_assets.sh && echo "no-assets check: PASS"

# ---- Shiftable build (docs/shiftable-plan.md). Separate from `make`, which it
# needs first (objects, out/gen/placements.tsv and rodata.tsv). Writes only
# under out/shift/. SHIFT_ASM_DIR: directory of symbolic asm exports of the
# functions no source places; empty = a temporary export from the original
# ELF into out/shift/asm/ (build output only). SHIFT_ALIASES: files of
# `alias = canonical;` lines.
SHIFT         := out/shift
SHIFT_ASM_DIR ?= shift/unmatched
SHIFT_ALIASES ?= shift/aliases.ld
# SHIFT_MODE: m0 = original addresses (byte-identical check), m1 = code rotated
# (data fixed), m2 = data and bss moved by 0x1000, m12 = both; m1/m2/m12 build m0 first
# and run the inverse-map comparator against it. SHIFT_DRAFTS=1 (moved modes only, into
# out/shift/<mode>-drafts): link the near-miss C drafts of shift/drafts.tsv in place of
# their asm exports and report a static word diff (tools/shift/drafts.py); never matched. SHIFT_RELOC_TIER: data_relocs.tsv rows with
# tier <= N become relocations (0 = none). SHIFT_VARIANTS=0: no KH1_SHIFTABLE objects.
SHIFT_MODE       ?= m0
SHIFT_RELOC_TIER ?= 3
SHIFT_VARIANTS   ?= 1
SHIFT_DRAFTS     ?= 0
# SHIFT_DATA_SHIFT (m2/m12): how far .data/.bss move; a larger value makes a bigger ELF
# (file-backed zeros), e.g. to test tools/shift/patch_iso.py --append. Output gets -dsN.
SHIFT_DATA_SHIFT ?= 0x1000
# SHIFT_FLOAT=1 (moved modes; output gets -float): the variables C defines leave their
# original place (data after the blob, bss after the original .bss); phase 4.
SHIFT_FLOAT      ?= 0
# SHIFT_FLOAT_BSS_BUDGET: bytes of floated bss (smallest runs first); the rest stays in place, since
# floated bss pushes _end and crt0's 0xA000-byte heap towards the fixed arena at 0x006A0000.
# Names that are really parts of another object stay in place: cover_check.py (declared
# objects), reach_check.py (displacements, calls, arrays indexed into the next name) and
# tools/shift/float_keep.txt (IOP-written blocks, a packet buffer). Session 18: 0x10000 plays in
# PCSX2; session 19: 0x11800 plays (title, save load, field) with the reach_check bounds and
# float_keep's packet buffer. Session 20: with the stricter reach_check rules only 6 large bss names
# are over 0x11800, and 0x16000 floats nothing more (the next one is 0x14014 bytes).
SHIFT_FLOAT_BSS_BUDGET ?= 0x11800
# SHIFT_FLOAT_DATA_BUDGET: bytes of floated data variables and pieces (smallest first); floated
# data goes after the blob and pushes .bss and _end up by as much (same arena limit).
# Session 20: 0x4000 (753 data names) plays in PCSX2 (title, load menu, save 05, field, menus) with
# reach_check's indexed-argument, idx-base, stored and uncached rules, float_keep's arena and table
# records, and pointer-table-only names kept (docs/shiftable-plan.md "Session 20: the data float").
# _end is 0x688824; _end + 0xA000 leaves 0xD7DC below 0x6A0000.
SHIFT_FLOAT_DATA_BUDGET ?= 0x4000
# SHIFT_REACH_FLAGS: extra reach_check.py options (--no-bounds: the session 18 idx-next rule).
SHIFT_REACH_FLAGS ?=
# SHIFT_FLOAT_SKIP: names that stay in place (space-separated; for bisecting).
SHIFT_FLOAT_SKIP ?=
# SHIFT_FLOAT_ONLY: if set, only these bss names float (bisecting; the budget still applies).
SHIFT_FLOAT_ONLY ?=
# SHIFT_FLOAT_ONLY_DATA: if set, only these data names float (@FILE reads names from FILE; bisecting).
SHIFT_FLOAT_ONLY_DATA ?=
# SHIFT_FLOAT_PTR_ONLY=1: also float data names that only a piece's .word names (no code user). Off by
# default since session 20: entries a pointer table points at one by one (D_0048F700 ...) can be walked
# by stride, and floating them drops a digit from the load menu's slot labels.
SHIFT_FLOAT_PTR_ONLY ?= 0
# Overlay fixups (m1/m2 only): SHIFT_OVERLAYS = directory of the user's .x files
# (tools/shift/extract_kingdom.py; missing = empty table); SHIFT_OVL_TIER: data words
# with tier <= N are fixed (default 2: code evidence); SHIFT_OVL_FIXUPS=0: no hook, no table.
SHIFT_OVERLAYS   ?= out/overlays
SHIFT_OVL_TIER   ?= 2
SHIFT_OVL_FIXUPS ?= 1
SHIFT_PY      := $(PY) -I
SHIFT_OUT      = $(if $(filter m0,$(SHIFT_MODE)),$(SHIFT),$(SHIFT)/$(SHIFT_MODE)$(if $(filter 1,$(SHIFT_DRAFTS)),-drafts)$(if $(filter 1,$(SHIFT_FLOAT)),-float)$(if $(filter-out 0x1000,$(SHIFT_DATA_SHIFT)),-ds$(SHIFT_DATA_SHIFT)))
ASFLAGS_SHIFT  = $(shell $(KH1) config toolchain.asflags)

shift: $(PATCHED)
ifneq ($(SHIFT_MODE),m0)
	@$(MAKE) --no-print-directory shift SHIFT_MODE=m0 SHIFT_DRAFTS=0 SHIFT_FLOAT=0
else ifeq ($(SHIFT_DRAFTS),1)
	$(error SHIFT_DRAFTS=1 needs SHIFT_MODE=m1, m2 or m12: drafts are not at the original addresses)
endif
	@mkdir -p $(SHIFT)/asm $(SHIFT_OUT)
	@$(SHIFT_PY) tools/shift/extract_data.py
	@set -e; rm -f $(SHIFT)/asm/*.o; \
	if [ -n "$(SHIFT_ASM_DIR)" ]; then \
		for s in $(SHIFT_ASM_DIR)/*.s; do $(AS) $(ASFLAGS_SHIFT) -o $(SHIFT)/asm/$$(basename $$s).o $$s; done; \
	else \
		missing="$$($(SHIFT_PY) tools/shift/shift_ld.py missing)"; \
		if [ -n "$$missing" ]; then \
			echo "shift: temporary asm export of $$(echo $$missing | wc -w) unplaced functions"; \
			$(SHIFT_PY) tools/asm_export.py $(SHIFT)/asm/unplaced.s $$missing \
				--header "temporary export for the shift build (out/ only, never commit)"; \
			$(AS) $(ASFLAGS_SHIFT) -o $(SHIFT)/asm/unplaced.s.o $(SHIFT)/asm/unplaced.s; \
		fi; \
	fi; \
	ovl=""; vdef=""; vdir=$(SHIFT)/variants; \
	if [ "$(SHIFT_MODE)" != m0 ] && [ "$(SHIFT_OVL_FIXUPS)" = 1 ]; then \
		$(SHIFT_PY) tools/shift/overlay_relocs.py --overlays $(SHIFT_OVERLAYS) --out-dir $(SHIFT_OUT) \
			--tier $(SHIFT_OVL_TIER); \
		$(AS) $(ASFLAGS_SHIFT) -o $(SHIFT_OUT)/ovl_fixups.o $(SHIFT_OUT)/ovl_fixups.s; \
		$(TOOLCHAIN)/ee-gcc2.96/bin/ee-gcc -S -x c -O2 -G0 -o $(SHIFT_OUT)/ovl_fixup.s shift/ovl_fixup.c; \
		$(TOOLCHAIN)/ee-gcc2.96/bin/ee-gcc -c -x assembler -O2 -G0 -o $(SHIFT_OUT)/ovl_fixup.o $(SHIFT_OUT)/ovl_fixup.s; \
		$(KH1) fix-obj $(SHIFT_OUT)/ovl_fixup.o; \
		ovl="--ovl-fixups $(SHIFT_OUT)/ovl_fixups.o --ovl-hook $(SHIFT_OUT)/ovl_fixup.o --ovl-labels $(SHIFT_OUT)/ovl_labels.txt"; \
		vdef="--define KH1_OVL_FIXUPS"; vdir=$(SHIFT_OUT)/variants; \
	fi; \
	variants=""; if [ "$(SHIFT_VARIANTS)" = 1 ]; then variants="$$($(SHIFT_PY) tools/shift/variants.py build --out-dir $$vdir $$vdef)"; fi; \
	drafts=""; if [ "$(SHIFT_DRAFTS)" = 1 ]; then drafts="$$($(SHIFT_PY) tools/shift/drafts.py build --out-dir $(SHIFT_OUT)/drafts)"; fi; \
	if [ "$(SHIFT_FLOAT)" = 1 ]; then $(SHIFT_PY) tools/shift/cover_check.py --out $(SHIFT_OUT)/float_covered.txt > $(SHIFT_OUT)/float_covered.log; \
		$(SHIFT_PY) tools/shift/reach_check.py $(SHIFT_REACH_FLAGS) --elf $(ORIG) --overlays $(SHIFT_OVERLAYS) --out $(SHIFT_OUT)/float_reach.txt \
			> $(SHIFT_OUT)/float_reach.log 2>&1; cat $(SHIFT_OUT)/float_reach.txt >> $(SHIFT_OUT)/float_covered.txt; \
		grep -v '^#' tools/shift/float_keep.txt >> $(SHIFT_OUT)/float_covered.txt; \
		if [ "$(SHIFT_FLOAT_PTR_ONLY)" != 1 ]; then awk -F'\t' 'NR > 1 && $$8 ~ /^(src\/data\/[^;]*\.s;?)+$$/ { print $$2 }' \
			$(SHIFT)/data_owners.tsv >> $(SHIFT_OUT)/float_covered.txt; fi; fi; \
	$(SHIFT_PY) tools/shift/shift_ld.py gen --mode $(SHIFT_MODE) --out-dir $(SHIFT_OUT) --data-shift $(SHIFT_DATA_SHIFT) \
		--reloc-tier $(SHIFT_RELOC_TIER) $$variants $$ovl $$drafts $(if $(filter 1,$(SHIFT_FLOAT)),--float-vars --float-skip-file $(SHIFT_OUT)/float_covered.txt --float-bss-budget $(SHIFT_FLOAT_BSS_BUDGET) --float-data-budget $(SHIFT_FLOAT_DATA_BUDGET) $(foreach n,$(SHIFT_FLOAT_SKIP),--float-skip $(n)) $(foreach n,$(SHIFT_FLOAT_ONLY),--float-only $(n)) $(foreach n,$(SHIFT_FLOAT_ONLY_DATA),--float-only-data $(n))) \
		$$(for o in $(SHIFT)/asm/*.o; do [ -e $$o ] && echo --asm-obj $$o; done) \
		$(foreach f,$(SHIFT_ALIASES),--aliases $(f))
	@$(AS) $(ASFLAGS_SHIFT) -o $(SHIFT_OUT)/blob.o $(SHIFT_OUT)/blob.s
	@$(LD) -EL -q --no-warn-mismatch -T $(SHIFT_OUT)/kh1-shift.ld -Map $(SHIFT_OUT)/kh1-shift.map \
		-o $(SHIFT_OUT)/kh1-shift.linked.elf @$(SHIFT_OUT)/objects.lst
	@$(SHIFT_PY) tools/shift/shift_elf.py write --linked $(SHIFT_OUT)/kh1-shift.linked.elf --out $(SHIFT_OUT)/kh1-shift.elf
	@$(SHIFT_PY) tools/shift/lo16_check.py --link $(SHIFT_OUT)
ifeq ($(SHIFT_MODE),m0)
	@$(SHIFT_PY) tools/shift/shift_elf.py verify
else
	@$(SHIFT_PY) tools/shift/shift_cmp.py --ref $(SHIFT) --new $(SHIFT_OUT)
ifeq ($(SHIFT_OVL_FIXUPS),1)
	@$(SHIFT_PY) tools/shift/ovl_proof.py --ref $(SHIFT) --new $(SHIFT_OUT) --overlays $(SHIFT_OVERLAYS)
endif
ifeq ($(SHIFT_DRAFTS),1)
	@$(SHIFT_PY) tools/shift/drafts.py report --ref $(SHIFT) --new $(SHIFT_OUT)
endif
endif

data-relocs: $(PATCHED)
	@$(SHIFT_PY) tools/shift/find_data_relocs.py

clean:
	rm -rf out/build $(PATCHED) $(LINKED) $(GEN) out/objdiff out/shift

distclean:
	rm -rf out objdiff.json
