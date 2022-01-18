/**
 * @file        ctype.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        26 June, 2020
 * @brief       ctype Definition Header File
*/

#ifndef _CTYPE_H_
#define _CTYPE_H_


/* Includes ----------------------------------------------- */
#include <types.h>


/* Exported types ----------------------------------------- */


/* Exported constants ------------------------------------- */


/* Exported macros ---------------------------------------- */

#define ISSPACE(c) (c == ' ')
#define ISDIGIT(c) ((c >= '0') && (c <= '9'))
#define ISLOWER(c) ((c >= 'a') && (c <= 'z'))
#define ISUPPER(c) ((c >= 'A') && (c <= 'Z'))
#define ISALPHA(c) (ISLOWER(c) || ISUPPER(c))

#define isspace(c) ISSPACE(c)
#define isdigit(c) ISDIGIT(c)
#define islower(c) ISLOWER(c)
#define isupper(c) ISUPPER(c)
#define isalpha(c) ISALPHA(c)

/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */



#endif /* _CTYPE_H_ */
