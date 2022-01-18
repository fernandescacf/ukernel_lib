/**
 * @file        mutex.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        06 May, 2020
 * @brief       Mutexs implementation
*/

/* Includes ----------------------------------------------- */
#include <mutex.h>



/* Private types ------------------------------------------ */


/* Private constants -------------------------------------- */
#define MUTEX_INIT     0x40
#define MUTEX_LOCK     0x41
#define MUTEX_UNLOCK   0x42
#define MUTEX_TRYLOCK  0x43
#define MUTEX_DESTROY  0x44

/* Private macros ----------------------------------------- */



/* Private variables -------------------------------------- */



/* Private function prototypes ---------------------------- */

extern void* __attribute__ (( naked )) syscall1(uint32_t sysnum, void *arg1);


/* Private functions -------------------------------------- */

/**
 * MutexInit Implementation (See header file for description)
*/
int32_t MutexInit(mutex_t *mutex)
{
    return (int32_t)syscall1(MUTEX_INIT, (void*)mutex);
}

/**
 * MutexLock Implementation (See header file for description)
*/
int32_t MutexLock(mutex_t *mutex)
{
    return (int32_t)syscall1(MUTEX_LOCK, (void*)mutex);
}

/**
 * MutexUnlock Implementation (See header file for description)
*/
int32_t MutexUnlock(mutex_t *mutex)
{
    return (int32_t)syscall1(MUTEX_UNLOCK, (void*)mutex);
}

/**
 * MutexTrylock Implementation (See header file for description)
*/
int32_t MutexTrylock(mutex_t *mutex)
{
    return (int32_t)syscall1(MUTEX_TRYLOCK, (void*)mutex);
}

/**
 * MutexDestroy Implementation (See header file for description)
*/
int32_t MutexDestroy(mutex_t *mutex)
{
    return (int32_t)syscall1(MUTEX_DESTROY, (void*)mutex);
}