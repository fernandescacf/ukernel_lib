/**
 * @file        server.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        03 May, 2020
 * @brief       Server implementation
*/

/* Includes ----------------------------------------------- */
#include <server.h>


/* Private types ------------------------------------------ */


/* Private constants -------------------------------------- */
#define SERVER_INSTALL     0x3C
#define SERVER_TERMINATE   0x3D
#define SERVER_CONNECT     0x3E
#define SERVER_DISCONNECT  0x3F

#define OBJECT_SHARE       0x12
#define OBJECT_UNSHARE     0x13

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
 * ServerInstall Implementation (See header file for description)
*/
int32_t ServerInstall(int32_t chid, const char *path)
{
    return (int32_t)syscall2 (SERVER_INSTALL, (void*)chid, (void*)path);
}

/**
 * ServerTerminate Implementation (See header file for description)
*/
int32_t ServerTerminate(int32_t chid)
{
    return (int32_t)syscall1 (SERVER_TERMINATE, (void*)chid);
}

/**
 * ServerConnect Implementation (See header file for description)
*/
int32_t ServerConnect(const char *path)
{
    return (int32_t)syscall1 (SERVER_CONNECT, (void*)path);
}

/**
 * ServerDisconnect Implementation (See header file for description)
*/
int32_t ServerDisconnect(int32_t coid)
{
    return (int32_t)syscall1 (SERVER_DISCONNECT, (void*)coid);
}

/**
 * ShareObject Implementation (See header file for description)
*/
void *ShareObject(void *addr, int32_t scoid, uint32_t flags)
{
    return (void*)syscall3 (OBJECT_SHARE, (void*)addr, (void*)scoid, (void*)flags);
}

/**
 * UnshareObject Implementation (See header file for description)
*/
int32_t UnshareObject(int32_t scoid)
{
    return (int32_t)syscall1 (OBJECT_UNSHARE, (void*)scoid);
}