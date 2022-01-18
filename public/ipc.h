/**
 * @file        ipc.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        03 May, 2020
 * @brief       Interprocess Communication Definition Header File
*/

#ifndef _IPC_H_
#define _IPC_H_


/* Includes ----------------------------------------------- */
#include <types.h>
#include <io_types.h>


/* Exported types ----------------------------------------- */


/* Exported constants ------------------------------------- */

// Channel creation flags
//#define CHANNEL_IS_DIRECTORY		(1 << 0)
//#define CHANNEL_IS_DEVICE			(1 << 1)
#define CHANNEL_SCOID_DETACH_NOTIFY   (1 << 0)
#define CHANNEL_SCOID_ATTACH_NOTIFY   (1 << 1)
#define CHANNEL_FIXED_PRIORITY        (1 << 2)
#define CHANNEL_TASK_UNBLOCK          (1 << 3)
#define CHANNEL_COID_DEATH_NOTIFY     (1 << 4)

// Connection creation flags
#define CONNECTION_NOT_SHARED         (1 << 0)
#define CONNECTION_SERVER_BONDED      (1 << 1)
#define CONNECTION_PRIVATE            (1 << 2)

// IPC error codes
#define IPC_ERROR					(-1)
#define IPC_CHANNEL_DEAD			(-2)
#define IPC_CHONNECTION_DEAD		(-3)

// System pulses types
#define _NOTIFY_COID_ATTACH_			(0x1)
#define _NOTIFY_COID_DETACH_			(0x2)

/* Exported macros ---------------------------------------- */


/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */

/*
 * @brief   Routine to create a new IPC channel for the running process
 *
 * @param   flags - channel configuration flags
 *
 * @retval  Return chid or in case of error -1
 */
int32_t ChannelCreate(uint32_t flags);

/*
 * @brief   Routine to destroy the IPC channel
 *
 * @param   chid - id of the channel being destroyed
 *
 * @retval  Return success
 */
int32_t ChannelDestroy(int32_t chid);

/*
 * @brief   Routine to create a connection to the channel chid owned by the process pid
 *
 * @param   pid - channel owner process id
 *          chid - channel id
 *          index - base value for returned coid
 *          flags - connection configuration flags
 *
 * @retval  Return coid or in case of error -1
 */
int32_t ConnectAttach(pid_t pid, int32_t chid, uint32_t index, uint32_t flags);

/*
 * @brief   Routine to detach a connection from its channel
 *
 * @param   coid - connection id
 *
 * @retval  Return success
 */
int32_t ConnectDetach(int32_t coid);

/*
 * @brief   System call to send a message through an IPC channel
 *
 * @param   coid - connection id
 * 			hdr - message header
 *          smsg - message being sent
 *          rmsg - reply buffer
 *          offset - used to return the reply side
 *
 * @retval  Return success
 */
int32_t MsgSend(int32_t coid, const io_hdr_t *hdr, const char *smsg, const char *rmsg, uint32_t *offset);

/*
 * @brief   System call to received a message/notify through an IPC channel
 *
 * @param   chid - channel id
 * 			hdr - received message header
 *          msg - buffer to receive messages
 *          size - size of the receive buffer
 *          info - structure to be filled with sender connection information
 *
 * @retval  Return rcvid for a message, 0 if we received a pulse or -1 in case of error
 */
int32_t MsgReceive(int32_t chid, io_hdr_t *hdr, const char *msg, size_t size, uint32_t *offset, msg_info_t *info);

/*
 * @brief   System call to respond/reply to a received message
 *
 * @param   rcvid - received message id (who we are replying to)
 *          status - return for MsgSend
 *          msg - reply message buffer
 *          size - reply message size
 *
 * @retval  Return success
 */
int32_t MsgRespond(int32_t rcvid, int32_t status, const char *msg, size_t size);

/*
 * @brief   System call to write to a received message reply buffer
 *
 * @param   rcvid - received message id
 *          msg - data to be written to the reply buffer
 *          size - reply message size
 *          offset - offset to write the message in the reply buffer
 *
 * @retval  Return success
 */
int32_t MsgWrite(int32_t rcvid, const void *msg, size_t size, int32_t offset);

/*
 * @brief   System call to read to a received message send buffer
 *
 * @param   rcvid - received message id
 *          msg - memory buffer
 *          size - size of the memory buffer
 *          offset - offset to read from the message send buffer
 *
 * @retval  Return success
 */
int32_t MsgRead(int32_t rcvid, const void *msg, size_t size, int32_t offset);

/*
 * @brief   System call to send a notification through an IPC channel
 *
 * @param   coid - connection id
 *          priority - notification priority
 *          code - notification type
 *          value - 4 bytes of data being sent
 *
 * @retval  Return success
 */
int32_t MsgNotify(int32_t coid, int32_t priority, int32_t type, int32_t value);

#endif /* _IPC_H_ */
