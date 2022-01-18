/**
 * @file        server.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        03 May, 2020
 * @brief       Server Definition Header File
*/

#ifndef _SERVER_H_
#define _SERVER_H_


/* Includes ----------------------------------------------- */
#include <types.h>
#include <ipc.h>


/* Exported types ----------------------------------------- */


/* Exported constants ------------------------------------- */
#define SYSTEM_SERVER       0x0

#define CONNECTION_FAIL     -1

/* Exported macros ---------------------------------------- */


/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */
int32_t ServerInstall(int32_t chid, const char *path);

int32_t ServerTerminate(int32_t chid);

int32_t ServerConnect(const char *path);

int32_t ServerDisconnect(int32_t coid);

void *ShareObject(void *addr, int32_t scoid, uint32_t flags);

int32_t UnshareObject(int32_t scoid);

#endif /* _SERVER_H_ */
