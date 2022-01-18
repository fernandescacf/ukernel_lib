/**
 * @file        semaphore.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        05 July, 2020
 * @brief       Semaphore implementation
*/

/* Includes ----------------------------------------------- */
#include <semaphore.h>



/* Private types ------------------------------------------ */


/* Private constants -------------------------------------- */
#define SEM_INIT       0x45
#define SEM_WAIT       0x46
#define SEM_POST       0x47
#define SEM_DESTROY    0x48

/* Private macros ----------------------------------------- */



/* Private variables -------------------------------------- */



/* Private function prototypes ---------------------------- */

extern void* __attribute__ (( naked )) syscall1(uint32_t sysnum, void *arg1);
extern void* __attribute__ (( naked )) syscall3(uint32_t sysnum, void *arg1, void *arg2, void *arg3);


/* Private functions -------------------------------------- */

/**
 * SemInit Implementation (See header file for description)
*/
int32_t SemInit(sem_t *sem, int32_t pshared, uint32_t value)
{
    return (int32_t)syscall3(SEM_INIT, (void*)sem, (void*)pshared, (void*)value);
}

/**
 * SemWait Implementation (See header file for description)
*/
int32_t SemWait(sem_t *sem)
{
    return (int32_t)syscall1(SEM_WAIT, (void*)sem);
}

/**
 * SemPost Implementation (See header file for description)
*/
int32_t SemPost(sem_t *sem)
{
    return (int32_t)syscall1(SEM_POST, (void*)sem);
}

/**
 * SemDestroy Implementation (See header file for description)
*/
int32_t SemDestroy(sem_t *sem)
{
    return (int32_t)syscall1(SEM_DESTROY, (void*)sem);
}
