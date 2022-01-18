/**
 * @file        tls.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        21 September, 2020
 * @brief       Task Local Storage Header File
*/

#ifndef _TLS_H_
#define _TLS_H_


/* Includes ----------------------------------------------- */
#include <types.h>



/* Exported types ----------------------------------------- */
typedef struct
{
    uint32_t tid;
    uint32_t flags;
    int32_t  errno;
    uint32_t numkeys;
    void**   keydata;
    void*    cleanup;
}tls_t;


/* Exported constants ------------------------------------- */


/* Exported macros ---------------------------------------- */
#define TLS()   gettls()


/* Exported functions ------------------------------------- */

/* @brief   Architecture specific routine to get the running task tls
 *
 * @param   None
 *
 * @retval	Pointer to taks local storage
 */
extern tls_t* gettls(void);

/* @brief   Starts a new task in the calling process
 *
 * @param   task    - Pointer to a task handler
 *          attr    - Task creation attributes
 *          routine - Task body
 *          arg     - Argument to be passed to routine()
 *
 * @retval	Returns Success
 */
uint32_t _gettid();

/* @brief   Get pointer to running task errno
 *
 * @param   None
 *
 * @retval	Returns pointer to errno
 */
int32_t *__geterrno(void);

#endif /* _TLS_H_ */
