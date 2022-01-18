/**
 * @file        dispatch.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        27 June, 2020
 * @brief       Dispatch IO Helper implementation
*/

/* Includes ----------------------------------------------- */
#include <dispatch.h>
#include <ipc.h>
#include <server.h>
#include <task.h>
#include <stdlib.h>
#include <string.h>


/* Private types ------------------------------------------ */


/* Private constants -------------------------------------- */
#define DISPATCHER_FLAGS        (0x0)
#define DISPATCHER_MSG_SIZE     (256)
#define DISPATCHER_RECV_SIZE    (256)
#define DISPATCHER_TASKS        (1)

/* Private macros ----------------------------------------- */


/* Private variables -------------------------------------- */

const dispatch_attr_t DISPATCH_ATTR = {DISPATCHER_FLAGS, DISPATCHER_MSG_SIZE, DISPATCHER_RECV_SIZE, DISPATCHER_TASKS};


/* Private function prototypes ---------------------------- */

void PulseHandler(notify_t* notify, ctrl_funcs_t* ctrl_funcs)
{
    if(notify->type == _NOTIFY_COID_ATTACH_)
    {
        if(ctrl_funcs->ctrl_connect != NULL)
        {
            ctrl_funcs->ctrl_connect(notify);
        }
    }
    else if(notify->type == _NOTIFY_COID_DETACH_)
    {
        if(ctrl_funcs->ctrl_disconnect != NULL)
        {
            ctrl_funcs->ctrl_disconnect(notify);
        }
    }
    else if(ctrl_funcs->ctrl_default != NULL)
    {
        ctrl_funcs->ctrl_default(notify);
    }
}

void MessageHandler(int32_t rcvid, io_hdr_t* hdr, msg_info_t* info, char* buffer, uint32_t size, io_funcs_t* io_funcs)
{
    if(hdr->type < (sizeof(io_funcs_t) / sizeof(void*)) - 1)
    {
        int32_t (**io_table) (int32_t, int32_t, io_hdr_t*, char*, uint32_t);
        io_table = (int32_t (**) (int32_t, int32_t, io_hdr_t*, char*, uint32_t))io_funcs;

        if(io_table[hdr->type] != NULL)
        {
            io_table[hdr->type](rcvid, info->scoid, hdr, buffer, size);
            return;
        }
    }
    else
    {
        if(io_funcs->io_undef != NULL)
        {
            (void)io_funcs->io_undef(rcvid, info->scoid, hdr, buffer, size);
            return;
        }
    }

    MsgRespond(rcvid, E_INVAL, NULL, 0);
}

void* Dispatcher(void* arg)
{
    dispatch_t* dispatch = (dispatch_t*)arg;

    char*      buffer = (char*)malloc(dispatch->msg_size);
    uint32_t   offset;
    io_hdr_t   hdr;
    msg_info_t info;

    while(TRUE)
    {
        memset(&hdr, 0x0, sizeof(hdr));
        memset(&info, 0x0, sizeof(msg_info_t));
        offset = 0;

        int32_t rcvid = MsgReceive(dispatch->chid, &hdr, (const char *)buffer, dispatch->recv_size, &offset, &info);

        if(rcvid == 0)
        {
            PulseHandler((notify_t*)&hdr, dispatch->ctrl_funcs);
        }
        else
        {
            MessageHandler(rcvid, &hdr, &info, buffer, offset, dispatch->io_funcs);
        }
    }

    return NULL;
}

/* Private functions -------------------------------------- */

dispatch_t* DispatcherAttach(const char* path, dispatch_attr_t* attr, io_funcs_t *io_funcs, ctrl_funcs_t *ctrl_funcs)
{
    if((path == NULL) || (io_funcs == NULL) || (ctrl_funcs == NULL))
    {
        return NULL;
    }

    if(attr == NULL)
    { 
        attr = (dispatch_attr_t*)&DISPATCH_ATTR;
    }

    int32_t chid = ChannelCreate(CHANNEL_SCOID_ATTACH_NOTIFY | CHANNEL_SCOID_DETACH_NOTIFY);
    int32_t sid  = ServerInstall(chid, path);

    char *name = (char*)malloc(strlen(path) + 1);
    strcpy(name, path);

    task_t* tasksPool = (task_t*)malloc(sizeof(task_t) * attr->tasks);
    memset(tasksPool, 0x0, (sizeof(task_t) * attr->tasks));

    dispatch_t* dispatch = (dispatch_t*)malloc(sizeof(dispatch_t));
    dispatch->chid = chid;
    dispatch->sid  = sid;
    dispatch->path = (const char*)name;
    dispatch->io_funcs = io_funcs;
    dispatch->ctrl_funcs = ctrl_funcs;
    dispatch->flags = attr->flags;
    dispatch->msg_size = attr->msg_size;
    dispatch->recv_size = attr->recv_size;
    dispatch->tasks = attr->tasks;
    dispatch->tasksPool = tasksPool;

    return dispatch;
}

int32_t DispatcherStart(dispatch_t* dispatch, bool_t wait)
{
    if(dispatch == NULL)
    {
        return E_INVAL;
    }

    uint32_t i = 0;
    for(; i < dispatch->tasks; i++)
    {
        TaskCreate(&dispatch->tasksPool[i], NULL, Dispatcher, (void*)dispatch);
    }
    if(wait == TRUE)
    {
        for(i = 0; i < dispatch->tasks; i++)
        {
            TaskJoin(dispatch->tasksPool[i], NULL);
        }
    }

    return E_OK;
}

int32_t DispatcherHandle(dispatch_t* dispatch)
{
    char*      buffer = (char*)malloc(dispatch->msg_size);
    uint32_t   offset;
    io_hdr_t   hdr;
    msg_info_t info;

    memset(&hdr, 0x0, sizeof(hdr));
    memset(&info, 0x0, sizeof(msg_info_t));
    offset = 0;

    int32_t rcvid = MsgReceive(dispatch->chid, &hdr, (const char *)buffer, dispatch->recv_size, &offset, &info);

    if(rcvid == 0)
    {
        PulseHandler((notify_t*)&hdr, dispatch->ctrl_funcs);
    }
    else
    {
        MessageHandler(rcvid, &hdr, &info, buffer, offset, dispatch->io_funcs);
    }

    free(buffer);

    return E_OK;
}