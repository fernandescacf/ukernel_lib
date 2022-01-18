#include <io_types.h>
#include <ipc.h>
#include <unistd.h>
#include <task.h>

off_t lseek(int32_t fd, off_t offset, int32_t whence)
{
    // Add cancelation point
    TaskTestCancel();
    
    switch(whence)
    {
        case SEEK_SET:
        case SEEK_CUR:
        case SEEK_END:
            break;
        default:
            return -1;
    }

    io_hdr_t hdr;
    hdr.type = _IO_SEEK;
    hdr.code = whence;
    hdr.sbytes = sizeof(off_t);
    hdr.rbytes = sizeof(off_t);

    off_t off = 0;
    uint32_t size = 0;

    if(MsgSend(fd, &hdr, (const char *)&offset, (const char *)&off, &size) != E_OK || size != sizeof(off_t))
    {
        return -1;
    }

    return off;
}