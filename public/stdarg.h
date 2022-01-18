/**
 * @file        stdarg.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        26 June, 2020
 * @brief       stdarg Definition Header File
*/

#ifndef _STDARG_H_
#define _STDARG_H_


/* Includes ----------------------------------------------- */
#include <types.h>


/* Exported types ----------------------------------------- */
typedef char *va_list;


/* Exported constants ------------------------------------- */


/* Exported macros ---------------------------------------- */
#define ALIGNBND (sizeof(signed int) - 1)
#define bnd(X, bnd) (((sizeof(X)) + (bnd)) & (~(bnd)))
#define va_arg(ap, T) (*(T *)(((ap) += (bnd(T, ALIGNBND))) - (bnd(T, ALIGNBND))))
#define va_end(ap) (void)0
#define va_start(ap, A) (void)((ap) = (((char *)&(A)) + (bnd(A, ALIGNBND))))


/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */



#endif /* _STDARG_H_ */
