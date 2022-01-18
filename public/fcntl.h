/**
 * @file        fcntl.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        26 June, 2020
 * @brief       Fcntl Definition Header File
*/

#ifndef _FCNTL_H_
#define _FCNTL_H_


/* Includes ----------------------------------------------- */
#include <types.h>


/* Exported types ----------------------------------------- */


/* Exported constants ------------------------------------- */


/* Exported macros ---------------------------------------- */
#define O_RDONLY    0
#define O_WRONLY    1
#define O_RDWR      2
#define O_APPEND	8
#define O_CREAT     0x10
#define O_TRUNC     0x20


/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */

int32_t connect(const char *path, char **remaining);

int32_t open(const char *buff, int32_t flags);

#endif /* _FCNTL_H_ */
