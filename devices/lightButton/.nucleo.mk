# information about Nucleo F401RE
FLASHSIZE   = 524288
RAMSIZE     = 98304
NODEP       = true

PROGRAM = build/nucleo.elf

FLAGS = -D__HEAP_SIZE=0x0000 -D__STACK_SIZE=0x0100 -DSTM32F401RE \
        -fno-strict-aliasing -DSTM32F4XX -Wall -fdata-sections -ffunction-sections \
        -DTARGET_NUCLEO_F401RE --specs=nosys.specs -mcpu=cortex-m4 -mlittle-endian \
        -mthumb -mthumb-interwork -DSTM32F401xE -Tsrc/stm32f401re_flash.ld \
        -Wl,--gc-sections,--defsym=__HEAP_SIZE=0x0000,--defsym=__STACK_SIZE=0x0100 $(DFLAGS)
CPPFLAGS = -std=c++14

LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys $(LDFLAGS)

MAXDEPTH = 5

SOURCES_DIRS = mbed src inc
INCLUDES_DIRS = mbed inc

EXCLUDE_DIRS = mbed/targets/cmsis/TARGET_STM/TARGET_NUCLEO_F401RE/* \
               lib/Emulator lib/Emulator/* tests tests/*

EXCLUDE_FILES = src/periodiccaller.cpp mbed/targets/cmsis/TARGET_STM/TARGET_NUCLEO_F401RE/TOOLCHAIN_ARM_STD/sys.cpp mbed/targets/cmsis/TARGET_STM/TARGET_NUCLEO_F401RE/TOOLCHAIN_ARM_MICRO/sys.cpp

OBJECT_FILES = mbed/TARGET_NUCLEO_F401RE/TOOLCHAIN_GCC_ARM/*.o

CCOMPILER   = arm-none-eabi-gcc
CXXCOMPILER = arm-none-eabi-g++
ARMSIZE     = arm-none-eabi-size
SHOWSIZE    = ./.memory $(ARMSIZE) $(PROGRAM) $(FLASHSIZE) $(RAMSIZE)

SRCEXTS = .cpp .c .S
HDREXTS = .h

RM = rm -rf

CHOWN = chown $(UID):$(GID)
CHOWNR= chown -R $(UID):$(GID)

# Generating directory tree for building
BUILDING_SRC_DIRS =$(shell find mbed -type d -links 2)
BUILDING_SRC_DIRS+=$(shell find src -type d -links 2)
BUILDING_DIRS=$(addsuffix /,$(addprefix build/,$(BUILDING_SRC_DIRS)))

include .generic.mk

ALL_INCLUDES_DIRS += /usr/include/newlib/c++/4.8 /usr/include/newlib/c++/4.8/arm-none-eabi

hex: $(PROGRAM:%.elf=%.hex)
	@$(SHOWSIZE)

bin: $(PROGRAM:%.elf=%.bin)
	@$(CHOWNR) build

%.hex: %.elf
	@arm-none-eabi-objcopy -Oihex $< $@
	@$(ECHO) Generating $@

%.bin: %.elf
	@arm-none-eabi-objcopy -O binary $< $@
	@$(ECHO) Generating $@

flash: $(PROGRAM:%.elf=%.hex)
	@$(ECHO) Flashing $<
	@sudo openocd -f .openocd.cfg

memory: $(PROGRAM)
	@$(SHOWSIZE)

build/%.o:%.cpp
	@$(COMPILECPP) $< -o $@
	@$(ECHO) Compiling $<

build/%/:
	@mkdir -p $@

gen_builddirs: $(BUILDING_DIRS)