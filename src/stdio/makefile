LOCAL_INC = -I../../public/
BUILD_DIR = ../../build

all: stdio printf scanf connect open close read write truncate lseek
	$(LD) -r *.o -o $(BUILD_DIR)/stdio.o
	rm *.o

stdio:
	$(CC) $(CFLAGS) stdio.c $(LOCAL_INC) -o stdio.o

printf:
	$(CC) $(CFLAGS) printf.c $(LOCAL_INC) -o printf.o

scanf:
	$(CC) $(CFLAGS) scanf.c $(LOCAL_INC) -o scanf.o

connect:
	$(CC) $(CFLAGS) connect.c $(LOCAL_INC) -o connect.o

open:
	$(CC) $(CFLAGS) open.c $(LOCAL_INC) -o open.o

close:
	$(CC) $(CFLAGS) close.c $(LOCAL_INC) -o close.o

read:
	$(CC) $(CFLAGS) read.c $(LOCAL_INC) -o read.o

write:
	$(CC) $(CFLAGS) write.c $(LOCAL_INC) -o write.o

truncate:
	$(CC) $(CFLAGS) truncate.c $(LOCAL_INC) -o truncate.o

lseek:
	$(CC) $(CFLAGS) lseek.c $(LOCAL_INC) -o lseek.o