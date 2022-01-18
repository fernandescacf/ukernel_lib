#include <io_types.h>
#include <ipc.h>
#include <unistd.h>
#include <task.h>

int32_t write(int32_t fd, char *buffer, size_t size)
{
    // Add cancelation point
    TaskTestCancel();

    io_hdr_t hdr;
    hdr.type = _IO_WRITE;
    hdr.code = 0;
    hdr.sbytes = size;
    hdr.rbytes = 0;

    return MsgSend(fd, &hdr, (const char *)buffer, NULL, NULL);
}