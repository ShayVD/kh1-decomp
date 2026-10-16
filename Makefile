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

SRCS    := $(shell find src -type f \( -name '*.c' -o -name '*.cpp' -o -name '*.cc' -o -name '*.s' \) 2>/dev/null | sort)
HEADERS := $(shell find include src -type f -name '*.h' 2>/dev/null)

# Regenerate the per-source rules only when the set of sources changes.
$(shell mkdir -p $(GEN); echo "$(SRCS)" | cmp -s - $(GEN)/srclist || echo "$(SRCS)" > $(GEN)/srclist)

ifeq ($(filter clean distclean help toolchain check layout,$(MAKECMDGOALS)),)
-include $(GEN)/objects.mk
endif

.PHONY: all build verify check layout objdiff report progress progress-update toolchain test clean distclean help

all: verify

help:
	@echo "make toolchain        fetch compilers + objdiff-cli into tools/toolchain/"
	@echo "make check            hash $(ORIG) against the pin in kh1.toml"
	@echo "make layout           regenerate layout.tsv from $(ORIG)"
	@echo "make build            compile src/, link, patch into $(PATCHED)"
	@echo "make verify           build, then require byte-identical output (default)"
	@echo "make objdiff          write objdiff.json for the objdiff GUI"
	@echo "make report           objdiff-cli per-function match report"
	@echo "make progress         print the progress tracker"
	@echo "make progress-update  rewrite docs/progress.md + history (end of session)"
	@echo "make test             tool self-tests (no game ELF needed)"

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

clean:
	rm -rf out/build $(PATCHED) $(LINKED) $(GEN) out/objdiff

distclean:
	rm -rf out objdiff.json
