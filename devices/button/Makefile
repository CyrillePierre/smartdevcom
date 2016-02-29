# These variables are to be modified so it correspond to your system
IMAGE       = nucleo            # The Docker image name (given at build time by -t)
NUCLEO_DIR	= /media/nucleo
LIBS_DIR    = libs
DEVICE		= # À utiliser quand plusieurs Nucleo sont branchées

# These variables are not intended to be modified
PWD         = $(shell pwd)
UID         = $(shell id -u)
GID         = $(shell id -g)
MOUNTPOINT  = /firmware
MEDIA       = /$(shell lsblk|grep $(NUCLEO)|tr -d ' '|cut -d'/' -f2-)
DOCKERMOUNT = \
	-v $(PWD):$(MOUNTPOINT) \
	-v $(PWD)/../../protocol/src:$(MOUNTPOINT)/inc/protocol \
	-v $(PWD)/../../$(LIBS_DIR)/nucleo/src:$(MOUNTPOINT)/inc/nucleo \
	-v $(PWD)/../../$(LIBS_DIR)/nucleo/lib:$(MOUNTPOINT)/lib

DK_MAKEFILE = dk_makefile
MAKE        = make --no-print-directory
MAKEARGS    = UID="$(UID)" GID="$(GID)"
DOCKERMAKE  = $(MAKE) -C$(MOUNTPOINT) $(MAKEARGS) -f$(DK_MAKEFILE)
DOCKER      = docker run --rm $(DOCKERMOUNT) $(IMAGE) $(DOCKERMAKE)

all:
	@$(DOCKER) $@

upload :
	mount $(DEVICE) $(NUCLEO_DIR)
	cp bin/nucleo.bin $(NUCLEO_DIR)
	sleep .3
	umount $(NUCLEO_DIR)

%:
	@$(DOCKER) $@
