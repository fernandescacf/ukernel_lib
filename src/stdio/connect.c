#include <io_types.h>
#include <server.h>
#include <ipc.h>
#include <string.h>
#include <fcntl.h>
#include <task.h>


#define REMAINING_PATH_OFFSET(pathLen, replySize, nameLen)  \
            (pathLen - (replySize - offsetof(sentry_t, name) - nameLen))


int32_t connect(const char *path, char **remaining)
{
    // Add cancelation point
    TaskTestCancel();
    
    // Reply buffer
    char reply[256];
    // Message header
    io_hdr_t hdr;
    hdr.type = _IO_INFO;
    hdr.code = INFO_BEST_MATCH;
    hdr.sbytes = strlen(path) + 1;
    hdr.rbytes = sizeof(reply);
    uint32_t replySize;

    // Query System for the path we want to connect
    if(MsgSend(SYSTEM_SERVER, &hdr, path, reply, &replySize) == E_OK)
    {
        io_entry_t *entry = (io_entry_t *)reply;
        // Add termination character (not added by default)
        reply[replySize] = 0;

        // If we found a server we connect to it
        if (entry->type == INFO_SERVER)
        {
            // If request return remaining path
            if(remaining != NULL)
            {
                *remaining = (char*)&path[REMAINING_PATH_OFFSET(hdr.sbytes, replySize, entry->server.len)];
            }
            
            return ConnectAttach(entry->server.pid, entry->server.chid, 0x0, CONNECTION_NOT_SHARED | CONNECTION_SERVER_BONDED);
        }
    }

    return -1;
}