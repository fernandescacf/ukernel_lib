/**
 * @file        stdlib.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        08 May, 2020
 * @brief       Standart Library Definition Header File
*/

#ifndef __STDLIB_H_
#define __STDLIB_H_


/* Includes ----------------------------------------------- */
#include <types.h>


/* Exported types ----------------------------------------- */



/* Exported constants ------------------------------------- */


/* Exported macros ---------------------------------------- */


/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */

/**
 * @brief   Allocates a block of size bytes of memory
 * 			returning a pointer to the beginning of the block
 * @param   size - Size of the memory block in bytes
 * @retval  Pointer to the memory block allocated
 */
void * malloc(uint32_t size);

/**
 * @brief   Changes the size of the memory block pointed to by ptr
 * 			the memory block may be moved to a new location
 * @param   ptr - Pointer to a memory block previously allocated
 *			size - New size for the memory block in bytes
 * @retval  Pointer to the reallocated memory block
 */
void * realloc(void * ptr, uint32_t size);

/**
 * @brief   Allocates a block of memory for an array of num elements
 * 			each of them size bytes long and initializes all to zero
 * @param   num - Number of elements to allocate
 *			size - Size of each element
 * @retval  Pointer to the memory block allocated
 */
void * calloc(uint32_t num, uint32_t size);

/**
 * @brief   Deallocate a block of memory
 * @param   ptr - Pointer to a memory block
 * @retval  No return value
 */
void free(void * ptr);


char *itoa(int32_t num, char *str, int32_t base);

ulong_t strtoul(const char *nptr, char **endptr, int32_t base);

#endif /* __STDLIB_H_ */
