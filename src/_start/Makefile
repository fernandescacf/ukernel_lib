LOCAL_INC = -I../../public/
BUILD_DIR = ../../build


all: start syscall dummy
	$(LD) -r *.o -o $(BUILD_DIR)/start.o
	rm *.o

start:
	$(CC) $(CFLAGS) start.S $(LOCAL_INC) -o start.o

syscall:
	$(CC) $(CFLAGS) syscall.S $(LOCAL_INC) -o syscall.o

dummy:
	$(CC) $(CFLAGS) dummy.c $(LOCAL_INC) -o dummy.o