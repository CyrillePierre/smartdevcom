# These variables are to be modified so it correspond to your system
IMAGE       = nucleo            # The Docker image name (given at build time by -t)
NUCLEO_DIR	= /media/nucleo

# These variables are not intended to be modified
PWD         = $(shell pwd)
UID         = $(shell id -u)
GID         = $(shell id -g)
MOUNTPOINT  = /firmware
DOCKERMOUNT = \
	-v $(PWD):$(MOUNTPOINT) \
	-v $(PWD)/../../protocol/src:$(MOUNTPOINT)/src/inc

DK_MAKEFILE = dk_makefile
MAKE        = make --no-print-directory
MAKEARGS    = UID="$(UID)" GID="$(GID)"
DOCKERMAKE  = $(MAKE) -C$(MOUNTPOINT) $(MAKEARGS) -f$(DK_MAKEFILE)
DOCKER      = docker run --rm $(DOCKERMOUNT) $(IMAGE) $(DOCKERMAKE)

all:
	@$(DOCKER) all

upload :
	mountpoint -q $(NUCLEO_DIR) && umount $(NUCLEO_DIR) || :
	mount $(NUCLEO_DIR)
	cp bin/nucleo.bin $(NUCLEO_DIR)
	umount $(NUCLEO_DIR)

%:
	@$(DOCKER) $@
