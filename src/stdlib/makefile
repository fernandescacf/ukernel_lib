LOCAL_INC = -I../../public/
BUILD_DIR = ../../build


all: heap itoa strtoul list
	$(LD) -r *.o -o $(BUILD_DIR)/stdlib.o
	rm *.o

heap:
	$(CC) $(CFLAGS) heap.c $(LOCAL_INC) -o heap.o

itoa:
	$(CC) $(CFLAGS) itoa.c $(LOCAL_INC) -o itoa.o

strtoul:
	$(CC) $(CFLAGS) strtoul.c $(LOCAL_INC) -o strtoul.o

list:
	$(CC) $(CFLAGS) list.c $(LOCAL_INC) -o list.o