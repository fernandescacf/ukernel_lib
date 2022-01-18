/**
 * @file        mutex.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        06 May, 2020
 * @brief       Mutexs Definition Header File
*/

#ifndef _MUTEX_H_
#define _MUTEX_H_


/* Includes ----------------------------------------------- */
#include <types.h>


/* Exported types ----------------------------------------- */
typedef void* mutex_t;


/* Exported constants ------------------------------------- */
#define MUTEX_INITIALIZER	(void*)(0x10101010)


/* Exported macros ---------------------------------------- */


/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */

int32_t MutexInit(mutex_t* mutex);

int32_t MutexLock(mutex_t* mutex);

int32_t MutexUnlock(mutex_t* mutex);

int32_t MutexTrylock(mutex_t* mutex);

int32_t MutexDestroy(mutex_t* mutex);

#endif /* _MUTEX_H_ */
