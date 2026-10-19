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

.PHONY: all build verify check layout rank objdiff report progress progress-update toolchain test clean distclean help shift

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

$(ORIG):
	@echo "error: $(ORIG) not found. Copy the ELF from your own disc to the repo root." >&2
	@echo "       It is gitignored and must never be committed." >&2
	@exit 1

$(GEN)/objects.mk $(GEN)/symbols.ld: $(GEN)/srclist $(SRCS) kh1.toml functions.tsv tools/kh1tool.py
	@$(KH1) gen

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
SHIFT_PY      := $(PY) -I
ASFLAGS_SHIFT  = $(shell $(KH1) config toolchain.asflags)

shift: $(PATCHED)
	@mkdir -p $(SHIFT)/asm
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
	$(SHIFT_PY) tools/shift/shift_ld.py gen $$(for o in $(SHIFT)/asm/*.o; do [ -e $$o ] && echo --asm-obj $$o; done) \
		$(foreach f,$(SHIFT_ALIASES),--aliases $(f))
	@$(AS) $(ASFLAGS_SHIFT) -o $(SHIFT)/blob.o $(SHIFT)/blob.s
	@$(LD) -EL --no-warn-mismatch -T $(SHIFT)/kh1-shift.ld -Map $(SHIFT)/kh1-shift.map \
		-o $(SHIFT)/kh1-shift.linked.elf @$(SHIFT)/objects.lst
	@$(SHIFT_PY) tools/shift/shift_elf.py write
	@$(SHIFT_PY) tools/shift/shift_elf.py verify

clean:
	rm -rf out/build $(PATCHED) $(LINKED) $(GEN) out/objdiff out/shift

distclean:
	rm -rf out objdiff.json
