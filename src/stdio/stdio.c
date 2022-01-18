#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <server.h>
#include <task.h>
#include <string.h>

#define STDIN   "/dev/stdin"
#define STDOUT  "/dev/stdout"

int32_t stdin  = 1;
int32_t stdout = 2;

void StdOpen()
{
    // By default stdin is 1 and stdout is 2 but if StdOpen is called
    // a different fd may be used
    stdin  = CONNECTION_FAIL;
    stdout = CONNECTION_FAIL;

    while(stdin == CONNECTION_FAIL)
    {
        SchedYield();

        stdin = ServerConnect(STDIN);
    }

    while(stdout == CONNECTION_FAIL)
    {
        SchedYield();

        stdout = ServerConnect(STDOUT);
    }
}

void StdClose()
{
    ServerDisconnect(stdin);
    ServerDisconnect(stdout);
}

int32_t stdio_read(char *str, uint32_t bytes)
{
    uint32_t size = 0;

	io_hdr_t hdr;
    hdr.type = _IO_READ;
    hdr.code = _IO_READ_TERMINATOR;     // Read till terminator character '\0'
    hdr.sbytes = 0;
    hdr.rbytes = bytes;

    MsgSend(stdin, &hdr, NULL, (const char *)str, &size);

    return size;
}

int32_t stdio_write(char *str, size_t len)
{
    return write(stdout, str, len);
}

int32_t getchar()
{
    char c = 0;

    read(stdin, &c, sizeof(c));

    return (int32_t)c;
}