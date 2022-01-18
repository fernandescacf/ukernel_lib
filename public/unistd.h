/**
 * @file        unistd.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        26 June, 2020
 * @brief       Unistd Definition Header File
*/

#ifndef _UNISTD_H_
#define _UNISTD_H_


/* Includes ----------------------------------------------- */
#include <types.h>


/* Exported types ----------------------------------------- */


/* Exported constants ------------------------------------- */
#define SEEK_SET    0   /* Seek from beginning of file.  */
#define SEEK_CUR    1   /* Seek from current position.  */
#define SEEK_END    2   /* Seek from end of file.  */

/* Exported macros ---------------------------------------- */


/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */

int32_t close(int32_t fd);

int32_t read(int32_t fd, char *buffer, size_t size);

int32_t write(int32_t fd, char *buffer, size_t size);

int32_t truncate(const char *path, off_t length);

int32_t ftruncate(int32_t fd, off_t length);

off_t lseek(int32_t fd, off_t offset, int32_t whence);

#endif /* _UNISTD_H_ */
