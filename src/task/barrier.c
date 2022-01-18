/**
 * @file        barrier.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        07 October, 2020
 * @brief       Task Barrier implementation
*/

/* Includes ----------------------------------------------- */
#include <cond.h>
#include <mutex.h>


/* Private types ------------------------------------------ */
typedef struct
{
    uint32_t cycle;
    uint32_t count;
    mutex_t  mutex;
    cond_t   cond;
}barrier_t;


/* Private constants -------------------------------------- */
#define BARRIAR_CYCLE_FLAG      (~0u ^ (~0u >> 1))
#define BARRIER_SERIAL_TASK     (-1)


/* Private macros ----------------------------------------- */



/* Private variables -------------------------------------- */



/* Private function prototypes ---------------------------- */


/* Private functions -------------------------------------- */

/**
 * BarrierInit Implementation (See header file for description)
*/
int32_t BarrierInit(barrier_t* barrier, uint32_t count)
{
    barrier->count = 0;
    barrier->cycle = 0;

    if(count == 0)
    {
        return E_INVAL;
    }

    int32_t ret = MutexInit(&barrier->mutex);
    if(ret != E_OK)
    {
        return ret;
    }

    ret = CondInit(&barrier->cond);
    if(ret != E_OK)
    {
        MutexDestroy(&barrier->mutex);
        return ret;
    }

    barrier->count = count;
    barrier->cycle = count;

    return E_OK;
}

/**
 * BarrierDestroy Implementation (See header file for description)
*/
int32_t BarrierDestroy(barrier_t* barrier)
{
    if((CondDestroy(&barrier->cond) == E_OK) && (MutexDestroy(&barrier->mutex) == E_OK))
    {
        return E_OK;
    }
    return E_BUSY;
}

/**
 * BarrierWait Implementation (See header file for description)
*/
int32_t BarrierWait(barrier_t* barrier)
{
    int32_t ret = MutexLock(&barrier->mutex);
    uint32_t cycle = (barrier->cycle & BARRIAR_CYCLE_FLAG);

    if(ret == E_OK)
    {
        if(--barrier->count == 0)
        {
            barrier->cycle = ((cycle == 0) ? (barrier->cycle | BARRIAR_CYCLE_FLAG) : (barrier->cycle & ~BARRIAR_CYCLE_FLAG));
            barrier->count = barrier->cycle & ~BARRIAR_CYCLE_FLAG;
            CondBroadcast(&barrier->cond);
            ret = BARRIER_SERIAL_TASK;
        }
        else
        {
            while ((ret == E_OK) && (cycle == (barrier->cycle & BARRIAR_CYCLE_FLAG)))
            {
                ret = CondWait(&barrier->cond, &barrier->mutex);
            }
        }

        MutexUnlock(&barrier->mutex);
    }

    return ret;
}