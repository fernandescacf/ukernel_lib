/**
 * @file        interrupt.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        23 June, 2020
 * @brief       Interrupt Definition Header File
*/

#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_


/* Includes ----------------------------------------------- */
#include <types.h>



/* Exported types ----------------------------------------- */


/* Exported constants ------------------------------------- */


/* Exported macros ---------------------------------------- */


/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */

int32_t InterruptAttach (int32_t intr, uint32_t priority, void *(*handler)(void *, uint32_t), const void *area);

int32_t InterrupDetach(int32_t id);

int32_t InterruptMask( int32_t intr, int32_t id );

int32_t InterruptUnmask( int32_t intr, int32_t id );

int32_t InterruptWait(int32_t id);

#endif /* _INTERRUPT_H_ */
