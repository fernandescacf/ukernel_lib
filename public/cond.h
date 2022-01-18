/**
 * @file        cond.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        06 October, 2020
 * @brief       Conditional variables Definition Header File
*/

#ifndef _COND_H_
#define _COND_H_


/* Includes ----------------------------------------------- */
#include <types.h>
#include <mutex.h>


/* Exported types ----------------------------------------- */
typedef void* cond_t;


/* Exported constants ------------------------------------- */
#define COND_INITIALIZER	(void*)(0x01010101)


/* Exported macros ---------------------------------------- */


/* Exported functions ------------------------------------- */

int32_t CondInit(cond_t* cond);

int32_t CondWait(cond_t* cond, mutex_t* mutex);

int32_t CondSignal(cond_t* cond);

int32_t CondBroadcast(cond_t* cond);

int32_t CondDestroy(cond_t* cond);

#endif /* _COND_H_ */
