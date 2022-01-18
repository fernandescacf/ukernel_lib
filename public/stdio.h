/**
 * @file        stdio.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        09 May, 2020
 * @brief       Standart Input/Output Definition Header File
*/

#ifndef __STDIO_H_
#define __STDIO_H_


/* Includes ----------------------------------------------- */
#include <types.h>
#include "experimental/stdio.h"



/* Exported types ----------------------------------------- */


/* Exported constants ------------------------------------- */
extern int32_t stdin;
extern int32_t stdout;


/* Exported macros ---------------------------------------- */


/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */

void StdOpen();

void StdClose();

int sprintf(char *str, const char *format, ...);

int printf(char *str, ...);

int scanf(char *str, ...);

int getchar();

#endif /* __STDIO_H_ */
