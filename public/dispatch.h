/**
 * @file        dispatch.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        27 June, 2020
 * @brief       Dispatch Helper Definition Header File
*/

#ifndef _DISPATCH_H_
#define _DISPATCH_H_


/* Includes ----------------------------------------------- */
#include <types.h>
#include <io_types.h>


/* Exported types ----------------------------------------- */
typedef struct
{
    int32_t (*io_info) (int32_t, int32_t, io_hdr_t*, char*, uint32_t);
    int32_t (*io_read) (int32_t, int32_t, io_hdr_t*, char*, uint32_t);
    int32_t (*io_write)(int32_t, int32_t, io_hdr_t*, char*, uint32_t);
    int32_t (*io_open) (int32_t, int32_t, io_hdr_t*, char*, uint32_t);
    int32_t (*io_close)(int32_t, int32_t, io_hdr_t*, char*, uint32_t);
    int32_t (*io_mmap) (int32_t, int32_t, io_hdr_t*, char*, uint32_t);
    int32_t (*io_ioctl)(int32_t, int32_t, io_hdr_t*, char*, uint32_t);
    int32_t (*io_seek) (int32_t, int32_t, io_hdr_t*, char*, uint32_t);
    int32_t (*io_space)(int32_t, int32_t, io_hdr_t*, char*, uint32_t);
    int32_t (*io_undef)(int32_t, int32_t, io_hdr_t*, char*, uint32_t);
}io_funcs_t;

typedef struct
{
    int32_t (*ctrl_connect)    (notify_t*);
    int32_t (*ctrl_disconnect) (notify_t*);
    int32_t (*ctrl_default)    (notify_t*);
}ctrl_funcs_t;

typedef struct 
{
    int32_t         chid;
    int32_t         sid;
    const char*     path;
    io_funcs_t*     io_funcs;
    ctrl_funcs_t*   ctrl_funcs;
    uint32_t        flags;
    uint32_t        msg_size;
    uint32_t        recv_size;
    int32_t         tasks;
    task_t*         tasksPool;
}dispatch_t;

typedef struct 
{
    uint32_t flags;
    uint32_t msg_size;
    uint32_t recv_size;
    uint32_t tasks;
}dispatch_attr_t;


/* Exported constants ------------------------------------- */


/* Exported macros ---------------------------------------- */


/* Private functions -------------------------------------- */


/* Exported functions ------------------------------------- */

dispatch_t* DispatcherAttach(const char* path, dispatch_attr_t* attr, io_funcs_t *io_funcs, ctrl_funcs_t *ctrl_funcs);

int32_t DispatcherDetach(dispatch_t* dispatch);

int32_t DispatcherHandle(dispatch_t* dispatch);

int32_t DispatcherStart(dispatch_t* dispatch, bool_t wait);


#endif /* _DISPATCH_H_ */
