# Build options can be changed by modifying the makefile or by building with 'make SETTING=value'.
# It is also possible to override the settings in Defaults in a file called .make_options as 'SETTING=value'.

-include .make_options

MAKEFLAGS += --no-builtin-rules --no-print-directory

# Returns the path to the command $(1) if exists. Otherwise returns an empty string.
find-command = $(shell which $(1) 2>/dev/null)

#### Defaults ####

# If COMPARE is 1, check the output md5sum after building
COMPARE ?= 1
# If NON_MATCHING is 1, define the NON_MATCHING C flag when building
NON_MATCHING ?= 0
# if WERROR is 1, pass -Werror to CC_CHECK, so warnings would be treated as errors
WERROR ?= 0
# Keep .mdebug section in build
KEEP_MDEBUG ?= 0
# Check code syntax with host compiler
RUN_CC_CHECK ?= 1
CC_CHECK_COMP ?= gcc
# Dump build object files
OBJDUMP_BUILD ?= 0
# Number of threads to compress with
N_THREADS ?= $(shell nproc)
# If COMPILER is GCC, compile with GCC instead of IDO.
COMPILER ?= ido
# Whether to colorize build messages
COLOR ?= 1
# Whether to hide commands or not
VERBOSE ?= 0
# Command for printing messages during the make.
PRINT ?= printf

# Set prefix to mips binutils binaries (mips-linux-gnu-ld => 'mips-linux-gnu-') - Change at your own risk!
# Auto-detect prefix for MIPS toolchain
ifneq      ($(call find-command,mips-linux-gnu-ld),)
  MIPS_BINUTILS_PREFIX := mips-linux-gnu-
else ifneq ($(call find-command,mips64-linux-gnu-ld),)
  MIPS_BINUTILS_PREFIX := mips64-linux-gnu-
else ifneq ($(call find-command,mips64-elf-ld),)
  MIPS_BINUTILS_PREFIX := mips64-elf-
else
  $(error Unable to detect a suitable MIPS toolchain installed)
endif

VERSION ?= us
REV ?= rev1

BASEROM              := baserom.$(VERSION).$(REV).z64
BASEROM_UNCOMPRESSED := baserom.$(VERSION).$(REV).uncompressed.z64
TARGET               := starfox64

### Output ###

BUILD_DIR := build
TOOLS	  := tools
PYTHON	  := python3
ROM       := $(BUILD_DIR)/$(TARGET).$(VERSION).$(REV).uncompressed.z64
ROMC 	  := $(BUILD_DIR)/$(TARGET).$(VERSION).$(REV).z64
ELF       := $(BUILD_DIR)/$(TARGET).$(VERSION).$(REV).elf
LD_MAP    := $(BUILD_DIR)/$(TARGET).$(VERSION).$(REV).map
LD_SCRIPT := linker_scripts/$(VERSION)/$(REV)/$(TARGET).ld

#### Setup ####

# If gcc is used, define the NON_MATCHING flag respectively so the files that
# are safe to be used can avoid using GLOBAL_ASM which doesn't work with gcc.
ifeq ($(COMPILER),gcc)
  $(warning WARNING: GCC support is experimental. Use at your own risk.)
  CFLAGS += -DCOMPILER_GCC
  NON_MATCHING := 1
endif

# Detect compiler and set variables appropriately.
ifeq ($(COMPILER),gcc)
  CC       := $(MIPS_BINUTILS_PREFIX)gcc
else
ifeq ($(COMPILER),ido)
  CC       := $(TOOLS)/ido_recomp/$(DETECTED_OS)/7.1/cc
  CC_OLD   := $(TOOLS)/ido_recomp/$(DETECTED_OS)/5.3/cc
else
$(error Unsupported compiler. Please use either ido or gcc as the COMPILER variable.)
endif
endif

ifeq ($(COMPILER),gcc)
  OPTFLAGS := -Os
else
  OPTFLAGS := -O2 -g3
endif

ifeq ($(COMPILER),gcc)
  CFLAGS += -G 0 -ffast-math -fno-unsafe-math-optimizations -march=vr4300 -mfix4300 -mabi=32 -mno-abicalls -mdivide-breaks -fno-zero-initialized-in-bss -fno-toplevel-reorder -ffreestanding -fno-common -fno-merge-constants -mno-explicit-relocs -mno-split-addresses $(CHECK_WARNINGS) -funsigned-char
  MIPS_VERSION := -mips3
else
  # we support Microsoft extensions such as anonymous structs, which the compiler does support but warns for their usage. Surpress the warnings with -woff.
  CFLAGS += -G 0 -non_shared -fullwarn -verbose -Xcpluscomm $(IINC) -nostdinc -Wab,-r4300_mul -woff 649,838,712,516
  MIPS_VERSION := -mips2
  WARNINGS := -fullwarn -verbose -woff 624,649,838,712,516,513,596,564,594,709
endif

ifeq ($(COMPILER),ido)
  # Have CC_CHECK pretend to be a MIPS compiler
  MIPS_BUILTIN_DEFS := -D_MIPS_ISA_MIPS2=2 -D_MIPS_ISA=_MIPS_ISA_MIPS2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 -D_MIPS_SZINT=32 -D_MIPS_SZLONG=32 -D_MIPS_SZPTR=32
  CC_CHECK  = gcc -fno-builtin -fsyntax-only -funsigned-char -std=gnu90 -D_LANGUAGE_C -DNON_MATCHING $(MIPS_BUILTIN_DEFS) $(IINC) $(CHECK_WARNINGS)
  ifeq ($(shell getconf LONG_BIT), 32)
    # Work around memory allocation bug in QEMU
    export QEMU_GUEST_BASE := 1
  else
    # Ensure that gcc (warning check) treats the code as 32-bit
    CC_CHECK += -m32
  endif
else
  CC_CHECK  = @:
endif

BUILD_DEFINES ?=

# Version check
ifeq ($(VERSION),jp)
    BUILD_DEFINES   += -DVERSION_JP=1
endif

ifeq ($(VERSION),us)
    BUILD_DEFINES   += -DVERSION_US=1
endif

ifeq ($(VERSION),eu)
    BUILD_DEFINES   += -DVERSION_EU=1
	REV := rev0
endif

ifeq ($(VERSION),au)
	BUILD_DEFINES	+= -DVERSION_AU=1
	REV := rev0
endif

ifeq ($(VERSION),ln)
	BUILD_DEFINES	+= -DVERSION_LN=1
	REV := rev0
endif

ifeq ($(NON_MATCHING),1)
    BUILD_DEFINES   += -DNON_MATCHING -DAVOID_UB
    CPPFLAGS += -DNON_MATCHING -DAVOID_UB
endif

MAKE = make
CPPFLAGS += -fno-dollars-in-identifiers -P
LDFLAGS  := --no-check-sections --accept-unknown-input-arch --emit-relocs

UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)
ifeq ($(OS),Windows_NT)
$(error Native Windows is currently unsupported for building this repository, use WSL instead c:)
else ifeq ($(UNAME_S),Linux)
    DETECTED_OS := linux
    #Detect aarch64 devices (Like Raspberry Pi OS 64-bit)
    #If it's found, then change the compiler to a version that can compile in 32 bit mode.
    ifeq ($(UNAME_M),aarch64)
        CC_CHECK_COMP := arm-linux-gnueabihf-gcc
    endif
else ifeq ($(UNAME_S),Darwin)
    DETECTED_OS := macos
    MAKE := gmake
    CPPFLAGS += -xc++
endif

# Support python venv's if one is installed.
PYTHON_VENV = .venv/bin/python3
ifneq "$(wildcard $(PYTHON_VENV) )" ""
  PYTHON = $(PYTHON_VENV)
endif

ifeq ($(VERBOSE),0)
  V := @
endif

ifeq ($(COLOR),1)
NO_COL  := \033[0m
RED     := \033[0;31m
GREEN   := \033[0;32m
BLUE    := \033[0;34m
YELLOW  := \033[0;33m
BLINK   := \033[33;5m
endif

# Common build print status function
define print
  @$(PRINT) "$(GREEN)$(1) $(YELLOW)$(2)$(GREEN) -> $(BLUE)$(3)$(NO_COL)\n"
endef

#### Tools ####
ifneq ($(shell type $(MIPS_BINUTILS_PREFIX)ld >/dev/null 2>/dev/null; echo $$?), 0)
$(error Unable to find $(MIPS_BINUTILS_PREFIX)ld. Please install or build MIPS binutils, commonly mips-linux-gnu. (or set MIPS_BINUTILS_PREFIX if your MIPS binutils install uses another prefix))
endif


### Compiler ###

IDO              := $(TOOLS)/ido-recomp/$(DETECTED_OS)/cc
AS              := $(MIPS_BINUTILS_PREFIX)as
LD              := $(MIPS_BINUTILS_PREFIX)ld
OBJCOPY         := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP         := $(MIPS_BINUTILS_PREFIX)objdump
ICONV           := iconv
ASM_PROC        := $(PYTHON) $(TOOLS)/asm-processor/build.py
CAT             := cat
TORCH           := $(TOOLS)/Torch/cmake-build-release/torch

# Prefer clang as C preprocessor if installed on the system
ifneq (,$(call find-command,clang))
  CPP      := clang
  CPPFLAGS := -E -P -x c -Wno-trigraphs -Wmissing-prototypes -Wstrict-prototypes -D_LANGUAGE_ASSEMBLY
else
  CPP      := cpp
  CPPFLAGS := -P -Wno-trigraphs -Wmissing-prototypes -Wstrict-prototypes -D_LANGUAGE_ASSEMBLY
endif

ASM_PROC_FLAGS  := --input-enc=utf-8 --output-enc=euc-jp --convert-statics=global-with-filename

SPLAT           ?= $(PYTHON) $(TOOLS)/splat/split.py
SPLAT_YAML      ?= $(TARGET).$(VERSION).$(REV).yaml

COMPTOOL		:= $(TOOLS)/comptool.py
COMPTOOL_DIR	:= baserom
MIO0			:= $(TOOLS)/mio0


IINC := -Iinclude -Ibin/$(VERSION).$(REV) -I.
IINC += -Ilib/ultralib/include -Ilib/ultralib/include/PR -Ilib/ultralib/include/ido

ifeq ($(KEEP_MDEBUG),0)
  RM_MDEBUG = $(OBJCOPY) --remove-section .mdebug $@
else
  RM_MDEBUG = @:
endif

# Check code syntax with host compiler
CHECK_WARNINGS := -Wall -Wextra -Wimplicit-fallthrough -Wno-unknown-pragmas -Wno-missing-braces -Wno-sign-compare -Wno-uninitialized
# Have CC_CHECK pretend to be a MIPS compiler
MIPS_BUILTIN_DEFS := -DMIPSEB -D_MIPS_FPSET=16 -D_MIPS_ISA=2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 -D_MIPS_SZINT=32 -D_MIPS_SZPTR=32
ifneq ($(RUN_CC_CHECK),0)
#   The -MMD flags additionaly creates a .d file with the same name as the .o file.
    CHECK_WARNINGS    := -Wno-unused-variable -Wno-int-conversion
    CC_CHECK          := $(CC_CHECK_COMP)
    CC_CHECK_FLAGS    := -MMD -MP -fno-builtin -fsyntax-only -funsigned-char -fdiagnostics-color -std=gnu89 -DNON_MATCHING -DAVOID_UB -DCC_CHECK=1

    # Ensure that gcc treats the code as 32-bit
    ifeq ($(UNAME_M),aarch64)
        CC_CHECK_FLAGS += -march=armv7-a+fp
    else
        CC_CHECK_FLAGS += -m32
    endif
	ifneq ($(WERROR), 0)
        CHECK_WARNINGS += -Werror
    endif
else
    CC_CHECK          := @:
endif

ASFLAGS         := -march=vr4300 -32 -G0
COMMON_DEFINES  := -D_MIPS_SZLONG=32
GBI_DEFINES     := -DF3DEX_GBI
RELEASE_DEFINES := -DNDEBUG
AS_DEFINES      := -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_ULTRA64
C_DEFINES       := -DLANGUAGE_C -D_LANGUAGE_C -DBUILD_VERSION=VERSION_H ${RELEASE_DEFINES}
ENDIAN          := -EB

ICONV_FLAGS     := --from-code=UTF-8 --to-code=EUC-JP

# Use relocations and abi fpr names in the dump
OBJDUMP_FLAGS := --disassemble --reloc --disassemble-zeroes -Mreg-names=32 -Mno-aliases

ifneq ($(OBJDUMP_BUILD), 0)
    OBJDUMP_CMD = $(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)
    OBJCOPY_BIN = $(OBJCOPY) -O binary $@ $@.bin
else
    OBJDUMP_CMD = @:
    OBJCOPY_BIN = @:
endif

# rom compression flags
COMPFLAGS := --threads $(N_THREADS)
ifeq ($(NON_MATCHING),0)
    COMPFLAGS += --matching
endif

#### Files ####

$(shell mkdir -p asm bin linker_scripts/$(VERSION)/$(REV)/auto)

SRC_DIRS      := $(shell find src -type d)
# Temporary, until we decide how we're gonna handle other versions
ifeq ($(VERSION), jp)
SRC_DIRS      := $(shell find srcjp -type d)
endif
ifeq ($(VERSION), eu)
SRC_DIRS      := $(shell find srceu -type d)
endif
ASM_DIRS      := $(shell find asm/$(VERSION)/$(REV) -type d -not -path "asm/$(VERSION)/$(REV)/nonmatchings/*")
BIN_DIRS      := $(shell find bin -type d)


C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
C_FILES       := $(filter-out %.inc.c,$(C_FILES))
S_FILES       := $(foreach dir,$(ASM_DIRS) $(SRC_DIRS),$(wildcard $(dir)/*.s))
BIN_FILES     := $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
O_FILES       := $(foreach f,$(C_FILES:.c=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(S_FILES:.s=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(BIN_FILES:.bin=.o),$(BUILD_DIR)/$f)


# Automatic dependency files
DEP_FILES := $(O_FILES:.o=.d) \
             $(O_FILES:.o=.asmproc.d)

# create build directories
$(shell mkdir -p $(BUILD_DIR)/linker_scripts/$(VERSION)/$(REV) $(BUILD_DIR)/linker_scripts/$(VERSION)/$(REV)/auto $(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS),$(BUILD_DIR)/$(dir)))

ifeq ($(COMPILER),ido)

# directory flags
build/src/libultra/gu/%.o: OPTFLAGS := -O3 -g0
build/src/libultra/io/%.o: OPTFLAGS := -O1 -g0
build/src/libultra/os/%.o: OPTFLAGS := -O1 -g0
build/src/libultra/rmon/%.o: OPTFLAGS := -O1 -g0
build/src/libultra/debug/%.o: OPTFLAGS := -O1 -g0
build/src/libultra/host/%.o:	OPTFLAGS := -O1 -g0
build/src/audio/%.o: OPTFLAGS := -O2 -g0

# per-file flags
build/src/audio/audio_effects.o: CFLAGS += -use_readwrite_const
build/src/audio/audio_heap.o: CFLAGS += -use_readwrite_const
build/src/audio/audio_load.o: CFLAGS += -use_readwrite_const
build/src/audio/audio_seqplayer.o: CFLAGS += -use_readwrite_const
build/src/audio/audio_playback.o: CFLAGS += -use_readwrite_const
build/src/audio/audio_synthesis.o: CFLAGS += -use_readwrite_const

build/src/libc_sprintf.o: OPTFLAGS := -O2 -g0
build/src/libc_math64.o: OPTFLAGS := -O2 -g0

build/src/libultra/libc/ldiv.o: OPTFLAGS := -O2 -g0
build/src/libultra/libc/string.o: OPTFLAGS := -O2 -g0
build/src/libultra/libc/xlitob.o: OPTFLAGS := -O2 -g0
build/src/libultra/libc/xldtob.o: OPTFLAGS := -O3 -g0
build/src/libultra/libc/xprintf.o: OPTFLAGS := -O3 -g0
build/src/libultra/libc/ll.o: OPTFLAGS := -O1 -g0
build/src/libultra/libc/ll.o: MIPS_VERSION := -mips3 -32

# cc & asm-processor
CC := $(ASM_PROC) $(ASM_PROC_FLAGS) $(IDO) -- $(AS) $(ASFLAGS) --
build/src/libultra/gu/sqrtf.o: CC := $(IDO)
build/src/libultra/gu/sinf.o: CC := $(IDO)
build/src/libultra/gu/lookat.o: CC := $(IDO)
build/src/libultra/gu/ortho.o: CC := $(IDO)
build/src/libultra/libc/ll.o: CC := $(IDO)
build/src/libultra/gu/perspective.o: CC := $(IDO)
build/src/libultra/gu/mtxutil.o: CC := $(IDO)
build/src/libultra/gu/cosf.o: CC := $(IDO)
build/src/libultra/libc/xprintf.o: CC := $(IDO)
build/src/libultra/libc/xldtob.o: CC := $(IDO)
else
# directory flags
build/src/libultra/gu/%.o:    OPTFLAGS := -Os
build/src/libultra/io/%.o:    OPTFLAGS := -Os
build/src/libultra/os/%.o:    OPTFLAGS := -Os
build/src/libultra/rmon/%.o:  OPTFLAGS := -Os
build/src/libultra/debug/%.o: OPTFLAGS := -Os
build/src/libultra/host/%.o:  OPTFLAGS := -Os

# per-file flags
build/src/audio/audio_load.o:      OPTFLAGS := -Os
build/src/audio/audio_heap.o:      OPTFLAGS := -Os
build/src/audio/audio_effects.o:   OPTFLAGS := -Os
build/src/audio/audio_general.o:   OPTFLAGS := -Os
build/src/audio/audio_playback.o:  OPTFLAGS := -Os
build/src/audio/audio_seqplayer.o: OPTFLAGS := -Os
build/src/audio/audio_thread.o:    OPTFLAGS := -Os

build/src/libc_sprintf.o: OPTFLAGS := -Os
build/src/libc_math64.o:  OPTFLAGS := -Os

build/src/libultra/libc/ldiv.o:    OPTFLAGS := -Os
build/src/libultra/libc/string.o:  OPTFLAGS := -Os
build/src/libultra/libc/xlitob.o:  OPTFLAGS := -Os
build/src/libultra/libc/xldtob.o:  OPTFLAGS := -Os
build/src/libultra/libc/xprintf.o: OPTFLAGS := -Os
build/src/libultra/libc/ll.o:      OPTFLAGS := -O2
build/src/libultra/libc/ll.o: MIPS_VERSION := -mips3

# cc & asm-processor
build/src/libultra/gu/sqrtf.o:       OPTFLAGS := -Os
build/src/libultra/gu/sinf.o:        OPTFLAGS := -Os
build/src/libultra/gu/lookat.o:      OPTFLAGS := -Os
build/src/libultra/gu/ortho.o:       OPTFLAGS := -Os
build/src/libultra/gu/perspective.o: OPTFLAGS := -Os
build/src/libultra/gu/mtxutil.o:     OPTFLAGS := -Os
build/src/libultra/gu/cosf.o:        OPTFLAGS := -Os
build/src/libultra/libc/xprintf.o:   OPTFLAGS := -Os
build/src/libultra/libc/xldtob.o:    OPTFLAGS := -Os
endif

all: uncompressed

toolchain:
	@$(MAKE) -s -C $(TOOLS)

torch:
	@$(MAKE) -s -C $(TOOLS) torch
	rm -f torch.hash.yml

init:
	@$(MAKE) clean
	@$(MAKE) decompress
	@$(MAKE) extract -j $(N_THREADS)
	@$(MAKE) assets -j $(N_THREADS)
	@$(MAKE) uncompressed -j $(N_THREADS)
	@$(MAKE) compressed

SF := ___  ___\n/ __||  _|\n\__ \|  _|\n|___/|_|\n
uncompressed: $(ROM)
ifneq ($(COMPARE),0)
	@echo "$(GREEN)Calculating Rom Header Checksum... $(YELLOW)$<$(NO_COL)"
	@$(PYTHON) $(COMPTOOL) -r $(ROM) .
	@md5sum --status -c $(TARGET).$(VERSION).$(REV).uncompressed.md5 && \
	$(PRINT) "$(BLUE)$(TARGET).$(VERSION).$(REV).uncompressed.z64$(NO_COL): $(GREEN)OK$(NO_COL)\n$(YELLOW) $(SF)" || \
	$(PRINT) "$(BLUE)$(TARGET).$(VERSION).$(REV).uncompressed.z64 $(RED)FAILED$(NO_COL)\n\
	$(RED)CAN'T LET YOU DO THAT, STARFOX.$(NO_COL)\n"
	@md5sum --status -c $(TARGET).$(VERSION).$(REV).uncompressed.md5
endif

compressed: $(ROMC)
ifeq ($(COMPARE),1)
	@echo "$(GREEN)Calculating Rom Header Checksum... $(YELLOW)$<$(NO_COL)"
	@$(PYTHON) $(COMPTOOL) -r $(ROMC) .
	@md5sum --status -c $(TARGET).$(VERSION).$(REV).md5 && \
	$(PRINT) "$(BLUE)$(TARGET).$(VERSION).$(REV).z64$(NO_COL): $(GREEN)OK$(NO_COL)\n" || \
	$(PRINT) "$(BLUE)$(TARGET).$(VERSION).$(REV).z64 $(RED)FAILED$(NO_COL)\n"
	@md5sum --status -c $(TARGET).$(VERSION).$(REV).uncompressed.md5
endif

#### Main Targets ###

decompress: $(BASEROM)
	@echo "Decompressing ROM..."
	@$(PYTHON) $(COMPTOOL) $(DECOMPRESS_OPT) -dse $(COMPTOOL_DIR) -m $(MIO0) $(BASEROM) $(BASEROM_UNCOMPRESSED)

compress: $(BASEROM)
	@echo "Compressing ROM..."
	@$(PYTHON) $(COMPTOOL) $(COMPRESS_OPT) -c -m $(MIO0) $(ROM) $(ROMC)

extract:
	@$(RM) -r asm/$(VERSION)/$(REV) bin/$(VERSION)/$(REV)
	@echo "Unifying yamls..."
	@$(CAT) yamls/$(VERSION)/$(REV)/header.yaml yamls/$(VERSION)/$(REV)/main.yaml yamls/$(VERSION)/$(REV)/assets.yaml yamls/$(VERSION)/$(REV)/overlays.yaml > $(SPLAT_YAML)
	@echo "Extracting..."
	@$(SPLAT) $(SPLAT_YAML)

assets:
	@echo "Extracting assets from ROM..."
	@$(TORCH) code $(BASEROM_UNCOMPRESSED)
	@$(TORCH) header $(BASEROM_UNCOMPRESSED)
	@$(TORCH) modding export $(BASEROM_UNCOMPRESSED)

mod:
	@$(TORCH) modding import code $(BASEROM_UNCOMPRESSED)

clean:
	rm -f torch.hash.yml
	@git clean -fdx asm/$(VERSION)/$(REV)
	@git clean -fdx bin/$(VERSION)/$(REV)
	@git clean -fdx build/
	@git clean -fdx src/assets/
	@git clean -fdx include/assets/
	@git clean -fdx linker_scripts/$(VERSION)/$(REV)/*.ld

format:
	@$(PYTHON) $(TOOLS)/format.py -j $(N_THREADS)

checkformat:
	@$(TOOLS)/check_format.sh -j $(N_THREADS)

# asm-differ expected object files
expected:
	mkdir -p expected/build
	rm -rf expected/build/
	cp -r build/ expected/build/

context:
	@echo "Generating ctx.c ..."
	@$(PYTHON) ./$(TOOLS)/m2ctx.py $(filter-out $@, $(MAKECMDGOALS))

disasm:
	@$(RM) -r asm/$(VERSION)/$(REV) bin/$(VERSION)/$(REV)
	@echo "Unifying yamls..."
	@$(CAT) yamls/$(VERSION)/$(REV)/header.yaml yamls/$(VERSION)/$(REV)/main.yaml yamls/$(VERSION)/$(REV)/assets.yaml yamls/$(VERSION)/$(REV)/overlays.yaml > $(SPLAT_YAML)
	@echo "Extracting..."
	@$(SPLAT) $(SPLAT_YAML) --disassemble-all

#### Various Recipes ####

# Final ROM
$(ROMC): $(BASEROM_UNCOMPRESSED)
	$(call print,Compressing ROM...,$<,$@)
	@$(PYTHON) $(COMPTOOL) -c -m $(MIO0) $(ROM) $(ROMC)

# Uncompressed ROM
$(ROM): $(ELF)
	$(call print,ELF->ROM:,$<,$@)
	$(V)$(OBJCOPY) -O binary $< $@

# Link
$(ELF): $(LIBULTRA_O) $(O_FILES) $(LD_SCRIPT) $(BUILD_DIR)/linker_scripts/$(VERSION)/$(REV)/hardware_regs.ld $(BUILD_DIR)/linker_scripts/$(VERSION)/$(REV)/undefined_syms.ld $(BUILD_DIR)/linker_scripts/$(VERSION)/$(REV)/pif_syms.ld
	$(call print,Linking:,$<,$@)
	$(V)$(LD) $(LDFLAGS) -T $(LD_SCRIPT) \
		-T $(BUILD_DIR)/linker_scripts/$(VERSION)/$(REV)/hardware_regs.ld -T $(BUILD_DIR)/linker_scripts/$(VERSION)/$(REV)/undefined_syms.ld -T $(BUILD_DIR)/linker_scripts/$(VERSION)/$(REV)/pif_syms.ld \
		-Map $(LD_MAP) -o $@

# PreProcessor
$(BUILD_DIR)/%.ld: %.ld
	$(call print,PreProcessor:,$<,$@)
	$(V)$(CPP) $(CPPFLAGS) $(BUILD_DEFINES) $(IINC) $< > $@

# Binary
$(BUILD_DIR)/%.o: %.bin
	$(call print,Binary:,$<,$@)
	$(V)$(OBJCOPY) -I binary -O elf32-big $< $@

# Assembly
$(BUILD_DIR)/%.o: %.s
	$(call print,Assembling:,$<,$@)
	$(V)$(CPP) $(CPPFLAGS) $(BUILD_DEFINES) $(IINC) -I $(dir $*) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(AS_DEFINES) $< | $(ICONV) $(ICONV_FLAGS) | $(AS) $(ASFLAGS) $(ENDIAN) $(IINC) -I $(dir $*) -o $@
	$(V)$(OBJDUMP_CMD)

# C
$(BUILD_DIR)/%.o: %.c
	$(call print,Compiling:,$<,$@)
	@$(CC_CHECK) $(CC_CHECK_FLAGS) $(IINC) -I $(dir $*) $(CHECK_WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(MIPS_BUILTIN_DEFS) -o $@ $<
	$(V)$(CC) -c $(CFLAGS) $(BUILD_DEFINES) $(IINC) $(WARNINGS) $(MIPS_VERSION) $(ENDIAN) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(OPTFLAGS) -o $@ $<
	$(V)$(OBJDUMP_CMD)
	$(V)$(RM_MDEBUG)

# Patch ll.o
build/src/libultra/libc/ll.o: src/libultra/libc/ll.c
	$(call print,Patching:,$<,$@)
	@$(CC_CHECK) $(CC_CHECK_FLAGS) $(IINC) -I $(dir $*) $(CHECK_WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(MIPS_BUILTIN_DEFS) -o $@ $<
	$(V)$(CC) -c $(CFLAGS) $(BUILD_DEFINES) $(IINC) $(WARNINGS) $(MIPS_VERSION) $(ENDIAN) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(OPTFLAGS) -o $@ $<
	$(V)$(PYTHON) $(TOOLS)/set_o32abi_bit.py $@
	$(V)$(OBJDUMP_CMD)
	$(V)$(RM_MDEBUG)

-include $(DEP_FILES)

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true

.PHONY: all uncompressed compressed clean init extract expected format checkformat decompress compress assets context disasm toolchain
