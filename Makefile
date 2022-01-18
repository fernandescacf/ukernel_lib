BUILD_CONFIG = default.config
BOARD_CONFIG = armA32.config

include config/${BUILD_CONFIG}
include config/${BOARD_CONFIG}

CFLAGS += -g -static -fPIC -march=$(ARCH)$(VERSION)
CFLAGS += $(BOARD_FLAGS)

export CFLAGS
export CC
export LD
export ARCH
export BOARD
export VARIANT

INCLUDES = -Ipublic/

all: start string mman task server interrupt stdio stdlib
	$(LD) -r build/*.o -o bin/neoklib.o
	$(AR) rcs bin/$(ARCH)$(VERSION)_neoklib.a bin/neoklib.o
#	$(CC) -nostartfiles -shared bin/neoklib.o -o bin/$(ARCH)$(VERSION)_neoklib.so
#	rm bin/*.o
	@echo 'Finished building'

start:
	@echo ' '
	@echo 'Building NEOK Library'
	@echo 'Board config: ${BOARD_CONFIG}'
	@echo 'Architecture: $(ARCH)$(VERSION)'
	@echo 'Board: $(BOARD) $(VARIANT)'
	@echo ' '
	$(MAKE) -C src/_start/

string:
	$(MAKE) -C src/string/

mman:
	$(MAKE) -C src/mman/

task:
	$(MAKE) -C src/task/

interrupt:
	$(MAKE) -C src/interrupt/

server:
	$(MAKE) -C src/server/

stdio:
	$(MAKE) -C src/stdio/

stdlib:
	$(MAKE) -C src/stdlib/
