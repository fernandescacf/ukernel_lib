/**
 * @file        task.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        03 May, 2020
 * @brief       Task Definition Header File
*/

#ifndef _TASK_H_
#define _TASK_H_


/* Includes ----------------------------------------------- */
#include <types.h>
#include <tls.h>


/* Exported types ----------------------------------------- */
// Process ID type
typedef uint32_t pid_t;

// Task Handler type
typedef void*    task_t;

// Task Attributes
typedef struct
{
	uint16_t priority;
	uint16_t detached;
	size_t	 stackSize;
}taskAttr_t;

// Key Type
typedef int32_t key_t;

// Clean up handler type
struct __cleanup_handler
{
    struct __cleanup_handler* next;
    void (*routine)(void* arg);
    void* arg;
};

/* Exported constants ------------------------------------- */
#define TASK_CANCEL_STATE_MASK  (1 << 0)
#define TASK_CANCEL_ENABLE      (0 << 0)
#define TASK_CANCEL_DISABLE     (1 << 0)
#define TASK_CANCEL_TYPE_MASK   (1 << 1)
#define TASK_CANCEL_DEFERRED    (0 << 1)
#define TASK_CANCEL_ASYNC       (1 << 1)
#define TASK_CANCEL_PENDING     (1 << 4)
#define TASK_CANCELED_RET       ((void*)(-1))

// Timeout related defines
#define TIMER_NO_RELOAD         (0x0)
#define TIMER_AUTO_RELOAD       (0x1)

/* Exported macros ---------------------------------------- */
#define TaskCleanupPush(func, val) \
    do { \
        struct __cleanup_handler __cleanup_handler; \
        __cleanup_handler.routine = (func); \
        __cleanup_handler.arg = (val); \
        __cleanup_handler.next = (struct __cleanup_handler *)TLS()->cleanup; \
        TLS()->cleanup = (void*)&__cleanup_handler;

#define TaskCleanupPop(ex) \
        TLS()->cleanup = (void *)__cleanup_handler.next; \
        ((ex) ? __cleanup_handler.routine(__cleanup_handler.arg) : (void)0);\
    }while(0)


/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */

/* @brief   Starts a new task in the calling process
 *
 * @param   task    - Pointer to a task handler
 *          attr    - Task creation attributes
 *          routine - Task body
 *          arg     - Argument to be passed to routine()
 *
 * @retval	Returns Success
 */
int32_t TaskCreate(task_t *task, taskAttr_t *attr, void *(*routine) (void *), void *arg);

/* @brief   Suspends calling task until the target task is terminated. If target
 *          task is already terminated the calling task will not be suspended
 *
 * @param   task      - Target task we want to join
 *          value_ptr - If not NULL will the value passed to TaskExit() will be made
 *                      available at *value_ptr
 *
 * @retval	Returns Success
 */
int32_t TaskJoin(task_t task, void **value_ptr);

/* @brief   Terminates the calling task and make the value value_ptr available to
 *          any successful join with the terminating task
 *
 * @param   value_ptr - Value to be passed to joined tasks
 *
 * @retval	No return
 */
void TaskExit(void *value_ptr);

/* @brief   Terminates the execution of the specified task.
 *          Note: Calling task cannot use taskCancel to terminate itself
 *
 * @param   task - task being terminated
 *
 * @retval	Success
 */
int32_t TaskCancel(task_t task);

/* @brief   Routine to get the calling task ID
 *
 * @param   None
 *
 * @retval	Task ID
 */
task_t TaskSelf();

/* @brief   Create a cancelation point within the calling task.
 *          If cancelability is disabled  or no cancellation request is pending,
 *          this call has no effect.
 *
 * @param   None
 *
 * @retval	No return
 */
void TaskTestCancel();

/* @brief   Suspends calling task
 *
 * @param   No Parameters
 *
 * @retval	Returns Success
 */
int32_t SchedYield( void );

/* @brief   Creates and executes a new child process
 *
 * @param   exec  - Pointer to the elf file location in RAM
 *          cmd   - Execution command (argv)
 *
 * @retval	Returns Success
 */
pid_t Spawn(void *exec, const char *cmd, uint32_t fd_count, int32_t* fd_map);

/* @brief   Kills process with the specified PID.
 *          Only child processes from the running process can be killed
 *
 * @param   pid  - Child process PID
 *
 * @retval	No return
 */
void Kill(pid_t pid);

/* @brief   Suspends execution of the calling process until specified
 *          child terminates
 *
 * @param   pid  - Child process PID
 *
 * @retval	Returns Success
 */
int32_t WaitPid(pid_t pid);

/* @brief   Suspends calling task execution for usec micro seconds
 *
 * @param   usec  - Sleep time in micro seconds
 *
 * @retval	No return
 */
void uSleep(uint32_t usec);

void TimeoutSet(uint32_t time, int32_t type);

uint32_t GetTid();

int32_t key_create(key_t* key, void (*destructor)(void *));

int32_t key_set(key_t key, const void* value);

void* key_get(key_t key);

int32_t key_delete(key_t key);

#endif /* _TASK_H_ */
