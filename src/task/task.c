/**
 * @file        task.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        03 May, 2020
 * @brief       Task implementation
*/

/* Includes ----------------------------------------------- */
#include <task.h>


/* Private types ------------------------------------------ */


/* Private constants -------------------------------------- */
#define TASKEXIT		   0x20
#define TASKCREATE		   0x21
#define TASKJOIN		   0x22
#define TASKCANCEL         0x23
#define SLEEP			   0x28
#define SCHEDYIELD		   0x29
#define KILLPROCESS        0x2A
#define SPAWN			   0x2D
#define WAITPID            0x2C
#define TIMEOUTSET         0x49

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

/* @brief   System call to terminate running task. No clean up will be performed
 *
 * @param   ret - Value to be passed to joined tasks
 *
 * @retval	No return
 */
void TaskDestroy(void *ret)
{
	(void)syscall1 (TASKEXIT, (void*)ret);
}

/* Private functions -------------------------------------- */

/**
 * TaskCreate Implementation (See header file for description)
*/
int32_t TaskCreate(task_t *task, taskAttr_t *attr, void *(*start_routine) (void *), void *arg)
{
	return (int32_t)syscall5 (TASKCREATE, (void*)task, (void*)attr, (void*)start_routine, (void*)TaskExit, (void*)arg);
}

/**
 * TaskJoin Implementation (See header file for description)
*/
int32_t TaskJoin(task_t task, void **value_ptr)
{
    // Add cancelation point
    TaskTestCancel();

    return (int32_t)syscall2 (TASKJOIN, (void*)task, (void*)value_ptr);
}

/**
 * TaskExit Implementation (See header file for description)
*/
void TaskExit(void* ret)
{
	// Get access to clean up routines
	extern void _keys_flush();
	
	// Get task TLS
	tls_t* tls = TLS();
	struct __cleanup_handler *handler = NULL;

	// Set TLS flags
	tls->flags |= TASK_CANCEL_DISABLE;
	tls->flags &= ~TASK_CANCEL_ASYNC;

	// Call keys clean up handlers
	_keys_flush();

	// Pop task exit clean up handlers
	while((handler = tls->cleanup))
	{
		tls->cleanup = handler->next;
		handler->routine(handler->arg);
	}

	// Signal task termination
	TaskDestroy(ret);
}

/**
 * TaskExit Implementation (See header file for description)
*/
int32_t TaskCancel(task_t task)
{
	return (int32_t)syscall1 (TASKCANCEL, (void*)task);
}

/**
 * TaskSelf Implementation (See header file for description)
*/
task_t TaskSelf()
{
	return (task_t)_gettid();
}

/**
 * SchedYield Implementation (See header file for description)
*/
int32_t SchedYield( void )
{
	TaskTestCancel();
	return (int32_t)syscall (SCHEDYIELD);
}

/**
 * Spawn Implementation (See header file for description)
*/
pid_t Spawn(void *exec, const char *cmd, uint32_t fd_count, int32_t* fd_map)
{
	return (pid_t)syscall5 (SPAWN, (void*)exec, (void*)cmd, NULL, (void*)fd_count, (void*)fd_map);
}

/**
 * Kill Implementation (See header file for description)
*/
void Kill(pid_t pid)
{
	(void)syscall1 (KILLPROCESS, (void*)pid);
}

/**
 * WaitPid Implementation (See header file for description)
*/
int32_t WaitPid(pid_t pid)
{
	// Add cancelation point
    TaskTestCancel();
	
    return (int32_t)syscall1 (WAITPID, (void*)pid);
}

/**
 * uSleep Implementation (See header file for description)
*/
void uSleep(uint32_t usec)
{
    // Add cancelation point
    TaskTestCancel();

    (void)syscall1 (SLEEP, (void*)usec);
}

/**
 * GetTid Implementation (See header file for description)
*/
uint32_t GetTid()
{
	return _gettid();
}

/**
 * TaskTestCancel Implementation (See header file for description)
*/
void TaskTestCancel()
{
	if((TLS()->flags & (TASK_CANCEL_STATE_MASK | TASK_CANCEL_PENDING)) == (TASK_CANCEL_ENABLE | TASK_CANCEL_PENDING))
	{
		TaskExit(TASK_CANCELED_RET);
	}
}

void TimeoutSet(uint32_t time, int32_t type)
{
	(void)syscall2(TIMEOUTSET, (void*)time, (void*)type);
}