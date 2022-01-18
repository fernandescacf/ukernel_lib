LOCAL_INC = -I../../public/
BUILD_DIR = ../../build

all: task mutex sem tls keys cond barrier
	$(LD) -r *.o -o $(BUILD_DIR)/task.o
	rm *.o

task:
	$(CC) $(CFLAGS) task.c $(LOCAL_INC) -o task.o

mutex:
	$(CC) $(CFLAGS) mutex.c $(LOCAL_INC) -o mutex.o

sem:
	$(CC) $(CFLAGS) semaphore.c $(LOCAL_INC) -o sem.o

tls:
	$(CC) $(CFLAGS) tls.c $(LOCAL_INC) -o tls.o

keys:
	$(CC) $(CFLAGS) keys.c $(LOCAL_INC) -o keys.o

cond:
	$(CC) $(CFLAGS) cond.c $(LOCAL_INC) -o cond.o

barrier:
	$(CC) $(CFLAGS) barrier.c $(LOCAL_INC) -o barrier.o