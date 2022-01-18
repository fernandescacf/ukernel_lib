/**
 * @file        tls.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        21 September, 2020
 * @brief       Task Local Storage implementation
*/

/* Includes ----------------------------------------------- */
#include <types.h>
#include <tls.h>


/* Private types ------------------------------------------ */


/* Private constants -------------------------------------- */


/* Private macros ----------------------------------------- */


/* Private variables -------------------------------------- */


/* Private function prototypes ---------------------------- */


/* Private functions -------------------------------------- */

/**
 * gettls Implementation
*/
tls_t* gettls()
{
    tls_t* tls = 0;
    asm volatile(
		"mrc	p15, 0, %[_tls], c13, c0, 2		\n\t"
		: [_tls] "=r" (tls)
	);
    return tls;
}

/**
 * gettls Implementation (See task.h file for description)
*/
uint32_t _gettid()
{
    return TLS()->tid;
}

/**
 * __geterrno Implementation
*/
int32_t *__geterrno(void)
{
    return &TLS()->errno;
}