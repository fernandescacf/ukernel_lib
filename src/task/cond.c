/**
 * @file        cond.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        06 October, 2020
 * @brief       Conditional variables implementation
*/

/* Includes ----------------------------------------------- */
#include <cond.h>


/* Private types ------------------------------------------ */


/* Private constants -------------------------------------- */
#define COND_INIT     0x4B
#define COND_WAIT     0x4C
#define COND_SIGNAL   0x4D
#define COND_DESTROY  0x4E

#define SIGNAL_BROADCAST    (0)

/* Private macros ----------------------------------------- */



/* Private variables -------------------------------------- */



/* Private function prototypes ---------------------------- */

extern void* __attribute__ (( naked )) syscall1(uint32_t sysnum, void *arg1);
extern void* __attribute__ (( naked )) syscall2(uint32_t sysnum, void *arg1, void *arg2);


/* Private functions -------------------------------------- */

/**
 * CondInit Implementation (See header file for description)
*/
int32_t CondInit(cond_t* cond)
{
    return (int32_t)syscall1(COND_INIT, (void*)cond);
}

/**
 * CondWait Implementation (See header file for description)
*/
int32_t CondWait(cond_t* cond, mutex_t* mutex)
{
    return (int32_t)syscall2(COND_WAIT, (void*)cond, (void*)mutex);
}

/**
 * CondSignal Implementation (See header file for description)
*/
int32_t CondSignal(cond_t* cond)
{
    return (int32_t)syscall2(COND_SIGNAL, (void*)cond, (void*)1);
}

/**
 * CondBroadcast Implementation (See header file for description)
*/
int32_t CondBroadcast(cond_t* cond)
{
    return (int32_t)syscall2(COND_SIGNAL, (void*)cond, (void*)SIGNAL_BROADCAST);
}

/**
 * CondDestroy Implementation (See header file for description)
*/
int32_t CondDestroy(cond_t* cond)
{
    return (int32_t)syscall1(COND_DESTROY, (void*)cond);
}