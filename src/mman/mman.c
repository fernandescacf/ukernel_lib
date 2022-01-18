/**
 * @file        mman.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        03 May, 2020
 * @brief       Memory Management implementation
*/

/* Includes ----------------------------------------------- */
#include <mman.h>
#include <ipc.h>
#include <io_types.h>


/* Private types ------------------------------------------ */


/* Private constants -------------------------------------- */
#define MMAP               0x10
#define MUNMAP             0x11

/* Private macros ----------------------------------------- */


/* Private variables -------------------------------------- */


/* Private function prototypes ---------------------------- */

extern void* __attribute__ (( naked )) syscall2(uint32_t sysnum, void *arg1, void *arg2);
extern void* __attribute__ (( naked )) syscall6(uint32_t sysnum, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6);

/* Private functions -------------------------------------- */

void *_mmap(void *addr, size_t len, int32_t prot, uint32_t flags, int32_t fd, uint32_t off)
{
	return (void*)syscall6(MMAP, (void*)addr, (void*)len, (void*)prot, (void*)flags, (void*)fd, (void*)off);
}

void *mmap(void *addr, size_t len, int32_t prot, uint32_t flags, int32_t fd, uint32_t off)
{
	// If we are mapping a fd we first need to request the server to share the fd with us
	if(fd != NOFD)
	{
		io_hdr_t hdr;
		hdr.type = _IO_MMAP;
		hdr.code = 0;
		hdr.sbytes = 0;
		hdr.rbytes = 0;

		if(MsgSend(fd, &hdr, NULL, NULL, NULL) != E_OK)
		{
			return NULL;
		}
	}

	// Map in current process space
    return _mmap(addr, len, prot, flags, fd, off);
}

int32_t munmap(void *addr, size_t len)
{
	return (int32_t)syscall2(MUNMAP, (void*)addr, (void*)len);
}