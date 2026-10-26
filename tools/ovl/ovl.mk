# Build and verify one EE overlay (docs/overlays.md): make -f tools/ovl/ovl.mk OVL=xs_bambi
# Same model as the main build: each decompiled function in ovl/$(OVL)/ is compiled with
# -ffunction-sections, linked at its original address, patched into a copy of the user's
# overlay (out/ovl/$(OVL).elf, made by tools/ovl/build.py wrap) and compared. Writes only
# under out/ovl/$(OVL)/. Driven by `make ovl` in the top-level Makefile.
.DEFAULT_GOAL := verify
.SUFFIXES:
ifeq ($(OVL),)
$(error OVL is not set)
endif
export KH1_OVL := $(OVL)

PY        ?= python3
KH1       := $(PY) tools/kh1tool.py
TOOLCHAIN := tools/toolchain
BINUTILS  ?= mips-linux-gnu-
AS        := $(BINUTILS)as
LD        := $(BINUTILS)ld
INCLUDES  := -Iinclude -Isrc -Iovl/$(OVL)
O         := out/ovl/$(OVL)
GEN       := $(O)/gen
WRAPPED   := out/ovl/$(OVL).elf
PATCHED   := $(O)/$(OVL).elf
LINKED    := $(O)/linked.elf

SRCS    := $(shell find ovl/$(OVL) -type f \( -name '*.c' -o -name '*.s' \) -not -name '.*' 2>/dev/null | sort)
HEADERS := $(shell find include ovl/$(OVL) -type f -name '*.h' 2>/dev/null)

$(shell mkdir -p $(GEN); echo "$(SRCS)" | cmp -s - $(GEN)/srclist || echo "$(SRCS)" > $(GEN)/srclist)
-include $(GEN)/objects.mk

.PHONY: verify build report progress

$(GEN)/objects.mk $(GEN)/symbols.ld: $(GEN)/srclist $(SRCS) kh1.toml functions.tsv tools/kh1tool.py
	@$(KH1) gen

$(GEN)/link.ld: kh1.ld
	@sed 's|out/gen/|$(GEN)/|g' kh1.ld > $@

$(PATCHED): $(WRAPPED) ovl/$(OVL)/layout.tsv $(GEN)/link.ld $(GEN)/symbols.ld $(OBJS) tools/kh1tool.py
	@$(KH1) link-script
	@if [ -n "$(strip $(OBJS))" ]; then \
		$(LD) -EL -e 0 --no-check-sections --no-warn-mismatch -T $(GEN)/link.ld -o $(LINKED) $(OBJS); \
	fi
	@$(KH1) patch

build: $(PATCHED)

verify: $(PATCHED)
	@$(KH1) verify

report: $(PATCHED)
	@$(KH1) objdiff
	@$(KH1) objdiff-report

progress: $(PATCHED)
	@$(KH1) progress
