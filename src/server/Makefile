LOCAL_INC = -I../../public/
BUILD_DIR = ../../build


all: ipc server dispatch
	$(LD) -r *.o -o $(BUILD_DIR)/server.o
	rm *.o

ipc:
	$(CC) $(CFLAGS) ipc.c $(LOCAL_INC) -o ipc.o

server:
	$(CC) $(CFLAGS) server.c $(LOCAL_INC) -o server.o

dispatch:
	$(CC) $(CFLAGS) dispatch.c $(LOCAL_INC) -o dispatch.o