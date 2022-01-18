/**
 * @file        barrier.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        07 October, 2020
 * @brief       Task Barrier Definition Header File
*/

#ifndef _BARRIER_H_
#define _BARRIER_H_

/* Includes ----------------------------------------------- */
#include <cond.h>
#include <mutex.h>


/* Exported types ------------------------------------------ */
typedef struct
{
    uint32_t cycle;
    uint32_t count;
    mutex_t  mutex;
    cond_t   cond;
}barrier_t;


/* Exported constants -------------------------------------- */
#define BARRIER_SERIAL_TASK     (-1)


/* Exported macros ---------------------------------------- */


/* Exported functions ------------------------------------- */

int32_t BarrierInit(barrier_t* barrier, uint32_t count);

int32_t BarrierDestroy(barrier_t* barrier);

int32_t BarrierWait(barrier_t* barrier);

#endif /* _BARRIER_H_ */