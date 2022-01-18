#include <io_types.h>
#include <ipc.h>
#include <fcntl.h>
#include <unistd.h>

int32_t ftruncate(int32_t fd, off_t length)
{
    io_hdr_t hdr;
    hdr.type = _IO_SPACE;
    hdr.code = 0;
    hdr.sbytes = sizeof(off_t);
    hdr.rbytes = 0;

    return MsgSend(fd, &hdr, (const char *)&length, NULL, NULL);
}

int32_t truncate(const char *path, off_t length)
{
    int32_t fd = open(path, O_RDWR);

    if(fd == -1)
    {
        return -1;
    }

    int32_t ret = ftruncate(fd, length);

    close(fd);

    return ret;
}