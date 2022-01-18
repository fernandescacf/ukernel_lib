/**
 * @file        interrupt.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        23 June, 2020
 * @brief       Task implementation
*/

/* Includes ----------------------------------------------- */
#include <interrupt.h>


/* Private types ------------------------------------------ */


/* Private constants -------------------------------------- */
#define INTRATTACH		   0x50
#define INTRDETACH		   0x51
#define INTRMASK		   0x52
#define INTRUNMASK         0x53
#define INTRWAIT		   0x54

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
int32_t InterruptAttach (int32_t intr, uint32_t priority, void *(*handler)(void *, uint32_t), const void *area)
{
	return (int32_t)syscall4(INTRATTACH, (void*)intr, (void*)priority, (void*)handler, (void*)area);
}

int32_t InterrupDetach(int32_t id)
{
	return (int32_t)syscall1(INTRDETACH, (void*)id);
}

int32_t InterruptMask( int32_t intr, int32_t id )
{
	return (int32_t)syscall2(INTRMASK, (void*)intr, (void*)id);
}

int32_t InterruptUnmask( int32_t intr, int32_t id )
{
	return (int32_t)syscall2(INTRUNMASK, (void*)intr, (void*)id);
}

int32_t InterruptWait(int32_t id)
{
	return (int32_t)syscall1(INTRWAIT, (void*)id);
}
