#include <io_types.h>
#include <ipc.h>
#include <fcntl.h>
#include <string.h>


int32_t open(const char *buff, int32_t flags)
{
    char *remaining = NULL;

    int32_t fd = connect(buff, &remaining);

    if(fd == -1)
    {
        return -1;
    }

    // We were able to connect to a server, now we can send the open request
    io_hdr_t hdr;
    hdr.type = _IO_OPEN;
    hdr.code = flags;
    hdr.sbytes = strlen(remaining) + 1;
    hdr.rbytes = 0;

    if(MsgSend(fd, &hdr, (const char *)remaining, NULL, NULL) != E_OK)
    {
        // Open failed disconnect from server channel
        ConnectDetach(fd);
        return -1;
    }

    return fd;
}