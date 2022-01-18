/**
 * @file        semaphore.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        05 July, 2020
 * @brief       Semaphore Definition Header File
*/

#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_


/* Includes ----------------------------------------------- */
#include <types.h>


/* Exported types ----------------------------------------- */
typedef void *sem_t;


/* Exported constants ------------------------------------- */


/* Exported macros ---------------------------------------- */


/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */

int32_t SemInit(sem_t *sem, int32_t pshared, uint32_t value);

int32_t SemWait(sem_t *sem);

int32_t SemPost(sem_t *sem);

int32_t SemDestroy(sem_t *sem);

#endif /* _SEMAPHORE_H_ */
