/**
 * @file        mman.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        03 May, 2020
 * @brief       Memory Management Definition Header File
*/

#ifndef _MMAN_H_
#define _MMAN_H_


/* Includes ----------------------------------------------- */
#include <types.h>


/* Exported types ----------------------------------------- */


/* Exported constants ------------------------------------- */
// mmap defines
#define PROT_READ		(1 << 0)	// Data can be read
#define PROT_WRITE		(1 << 1)	// Data can be written
#define PROT_EXEC		(1 << 2)	// Data can be execute.
#define PROT_NOCACHE	(1 << 3)	// Don't use caches
#define PROT_NONE		(0 << 0)	// Data cannot be accessed

#define MAP_SHARED		(1 << 0)	// Changes are shared
#define MAP_PRIVATE 	(1 << 1)	// Changes are private
#define MAP_FIXED		(1 << 2)	// Interpret address exactly
#define MAP_ANON		(1 << 5)	// Map anonymous memory not associated with any specific file
#define MAP_ANONYMOUS	MAP_ANON
#define MAP_PHYS		(1 << 6)	// Map physical memory

#ifndef NOFD
    #define NOFD		(-1)
#endif

/* Exported macros ---------------------------------------- */


/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */
void* mmap(void *addr, size_t len, int32_t prot, uint32_t flags, int32_t fd, uint32_t off);

int32_t munmap(void *addr, size_t len);


#endif /* _MMAN_H_ */
