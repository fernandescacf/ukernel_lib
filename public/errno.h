/**
 * @file        errno.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        21 September, 2020
 * @brief       Errno Definition Header File
*/

#ifndef _ERRNO_H_
#define _ERRNO_H_


/* Includes ----------------------------------------------- */
#include <types.h>


/* Exported types ----------------------------------------- */


/* Exported constants ------------------------------------- */


/* Exported macros ---------------------------------------- */
#define errno (*__geterrno())


/* Exported functions ------------------------------------- */
extern int *__geterrno(void);



#endif /* _ERRNO_H_ */
