#include <io_types.h>
#include <ipc.h>
#include <unistd.h>
#include <task.h>

int32_t close(int32_t fd)
{
    // Add cancelation point
    TaskTestCancel();

    // Send close message
    io_hdr_t hdr;
    hdr.type = _IO_CLOSE;
    hdr.code = 0;
    hdr.sbytes = 0;
    hdr.rbytes = 0;

    (void)MsgSend(fd, &hdr, NULL, NULL, NULL);

    // Disconnect from server channel
    return ConnectDetach(fd);
}