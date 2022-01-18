/**
 * @file        ipc.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        03 May, 2020
 * @brief       Interprocess Communication implementation
*/

/* Includes ----------------------------------------------- */
#include <ipc.h>


/* Private types ------------------------------------------ */


/* Private constants -------------------------------------- */
#define CHANNEL_CREATE	   0x30
#define CHANNEL_DESTROY	   0x31
#define CONNECT_ATTACH	   0x32
#define CONNECT_DETACH	   0x33
#define MESSAGE_SEND	   0x34
#define MESSAGE_RECEIVE	   0x35
#define MESSAGE_RESPOND	   0x36
#define MESSAGE_WRITE	   0x37
#define MESSAGE_READ	   0x38
#define MESSAGE_NOTIFY     0x39


/* Private macros ----------------------------------------- */


/* Private variables -------------------------------------- */


/* Private function prototypes ---------------------------- */

extern void* __attribute__ (( naked )) syscall (uint32_t sysnum);
extern void* __attribute__ (( naked )) syscall1(uint32_t sysnum, void *arg1);
extern void* __attribute__ (( naked )) syscall2(uint32_t sysnum, void *arg1, void *arg2);
extern void* __attribute__ (( naked )) syscall3(uint32_t sysnum, void *arg1, void *arg2, void *arg3);
extern void* __attribute__ (( naked )) syscall4(uint32_t sysnum, void *arg1, void *arg2, void *arg3, void *arg4);
extern void* __attribute__ (( naked )) syscall5(uint32_t sysnum, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5);
extern void* __attribute__ (( naked )) syscall6(uint32_t sysnum, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6);


/* Private functions -------------------------------------- */

/**
 * ChannelCreate Implementation (See header file for description)
*/
int32_t ChannelCreate(uint32_t flags)
{
	return (int32_t)syscall1(CHANNEL_CREATE, (void*)flags);
}

/**
 * ChannelDestroy Implementation (See header file for description)
*/
int32_t ChannelDestroy(int32_t chid)
{
	return (int32_t)syscall1(CHANNEL_DESTROY, (void*)chid);
}

/**
 * ConnectAttach Implementation (See header file for description)
*/
int32_t ConnectAttach(pid_t pid, int32_t chid, uint32_t index, uint32_t flags)
{
	return (int32_t)syscall4(CONNECT_ATTACH, (void*)pid, (void*)chid, (void*)index, (void*)flags);
}

/**
 * ConnectDetach Implementation (See header file for description)
*/
int32_t ConnectDetach(int32_t coid)
{
	return (int32_t)syscall1(CONNECT_DETACH, (void*)coid);
}

/**
 * MsgSend Implementation (See header file for description)
*/
int32_t MsgSend(int32_t coid, const io_hdr_t *hdr, const char *smsg, const char *rmsg, uint32_t *offset)
{
	return (int32_t)syscall5(MESSAGE_SEND, (void*)coid, (void*)hdr, (void*)smsg, (void*)rmsg, (void*)offset);
}

/**
 * MsgReceive Implementation (See header file for description)
*/
int32_t MsgReceive(int32_t chid, io_hdr_t *hdr, const char *msg, size_t size, uint32_t *offset, msg_info_t *info)
{
	return (int32_t)syscall6(MESSAGE_RECEIVE, (void*)chid, (void*)hdr, (void*)msg, (void*)size, (void*)offset, (void*)info);
}

/**
 * MsgRespond Implementation (See header file for description)
*/
int32_t MsgRespond(int32_t rcvid, int32_t status, const char *msg, size_t size)
{
	return (int32_t)syscall4(MESSAGE_RESPOND, (void*)rcvid, (void*)status, (void*)msg, (void*)size);
}

/**
 * MsgWrite Implementation (See header file for description)
*/
int32_t MsgWrite(int32_t rcvid, const void *msg, size_t size, int32_t offset)
{
	return (int32_t)syscall4(MESSAGE_WRITE, (void*)rcvid, (void*)msg, (void*)size, (void*)offset);
}

/**
 * MsgRead Implementation (See header file for description)
*/
int32_t MsgRead(int32_t rcvid, const void *msg, size_t size, int32_t offset)
{
	return (int32_t)syscall4(MESSAGE_READ, (void*)rcvid, (void*)msg, (void*)size, (void*)offset);
}

/**
 * MsgNotify Implementation (See header file for description)
*/
int32_t MsgNotify(int32_t coid, int32_t priority, int32_t type, int32_t value)
{
	return (int32_t)syscall4(MESSAGE_NOTIFY, (void*)coid, (void*)priority, (void*)type, (void*)value);
}