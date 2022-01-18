#include <io_types.h>
#include <ipc.h>
#include <unistd.h>
#include <task.h>

int32_t read(int32_t fd, char *buffer, size_t size)
{
    // Add cancelation point
    TaskTestCancel();
    
    io_hdr_t hdr;
    hdr.type = _IO_READ;
    hdr.code = _IO_READ_SIZE;
    hdr.sbytes = 0;
    hdr.rbytes = size;

    return MsgSend(fd, &hdr, NULL, (const char *)buffer, NULL);
}