/**
 * @file        itoa.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        08 May, 2020
 * @brief       Converts an integer value to a null-terminated string
*/

/* Includes ----------------------------------------------- */
#include <stdlib.h>


/* Private types ------------------------------------------ */


/* Private constants -------------------------------------- */


/* Private macros ----------------------------------------- */


/* Private variables -------------------------------------- */


/* Private function prototypes ---------------------------- */


/* Private functions -------------------------------------- */
char *itoa(int32_t num, char *str, int32_t base)
{
    int32_t i = 0, skip = 0, rem, len = 0;
    uint32_t n, value;

	if(num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return str;
	}

    if(num < 0 && base == 10) 
    { 
        num = -num;
        str[0] = '-';
        len = skip = 1;
    }
     

    value = n = num;
    while (n != 0)
    {
        len++;
        n /= base;
    }

    for ( ; (i + skip) < len; i++)
    {
        rem   = value % base;
        value = value / base;
        str[len - (i + 1)] = (rem > 9)? (rem-10) + 'a' : rem + '0';
    }

    str[len] = '\0';

    return str;
}