# These variables are to be modified so it correspond to your system
IMAGE       = nucleo            # The Docker image name (given at build time by -t)
NUCLEO      = NODE_F401RE       # The Nucleo directory name when mounted
NUCLEO_DIR	= /media/nucleo
DEBUGGER    = gdb               # The debugger to use with make debug
#DEBUGMODE   = 1                # comment this line to enter in release mode

# These variables are to use or deploy libraries
LDFLAGS     = -lm
# Default value: your project directory's name
LIBNAME     = $(shell basename $(shell pwd))
# List here your sources to add to the library file (e.g.: $(wildcard src/*.cpp))
LIBSRC      =
LIBOBJ      = $(addprefix build/,$(LIBSRC:.cpp=.o))

# These variables are not intended to be modified
PWD         = $(shell pwd)
UID         = $(shell id -u)
GID         = $(shell id -g)
MOUNTPOINT  = /firmware
MEDIA       = /$(shell lsblk|grep $(NUCLEO)|tr -d ' '|cut -d'/' -f2-)
DOCKERMOUNT = \
	-v $(PWD):$(MOUNTPOINT) \
	-v $(PWD)/../../protocol/src:$(MOUNTPOINT)/src/inc

ifneq ($(DEBUGMODE),)
DFLAGS      = -DDEBUG -O0 -ggdb
else
DFLAGS      = -DNDEBUG -Os
endif

DK_MAKEFILE = dk_makefile
MAKE        = make --no-print-directory
MAKEARGS    = UID="$(UID)" GID="$(GID)" LDFLAGS="$(LDFLAGS)" DFLAGS="$(DFLAGS)"
DOCKERMAKE  = $(MAKE) -C$(MOUNTPOINT) $(MAKEARGS) -f$(DK_MAKEFILE)
DOCKER      = docker run --rm $(DOCKERMOUNT) $(IMAGE) $(DOCKERMAKE)
BINARY      = build/nucleo.bin
ELF         = build/nucleo.elf
CP          = cp -p
AR          = ar rvs

all:
	@$(DOCKER) all
ifneq ($(LIBOBJ),)
	@$(AR) build/lib$(LIBNAME).a $(LIBOBJ)
endif

upload :
	mountpoint -q $(NUCLEO_DIR) && umount LABEL=$(NUCLEO) || :
	mount LABEL=$(NUCLEO)
	cp bin/nucleo.bin $(NUCLEO_DIR)
	umount LABEL=$(NUCLEO)

%:
	@$(DOCKER) $@
