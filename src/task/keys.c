/**
 * @file        keys.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        29 September, 2020
 * @brief       Task Local Storage Keys handling implementation
*/

/* Includes ----------------------------------------------- */
#include <types.h>
#include <task.h>
#include <tls.h>
#include <mutex.h>
#include <stdlib.h>
#include <string.h>


/* Private types ------------------------------------------ */
typedef void    (*key_destructor_t)(void*);

typedef struct
{
    uint32_t count;
    void**   data;
}keyinfo_t;

/* Private constants -------------------------------------- */
#define KEY_INVAL    (void*)(-1)
#define KEYS_MAX     (126)


/* Private macros ----------------------------------------- */



/* Private variables -------------------------------------- */

static struct
{
    mutex_t key_mux;
    uint32_t count;
    key_destructor_t* destructors;
    mutex_t array_mux;
    uint32_t size;
    keyinfo_t* array;
}keys = 
{
    MUTEX_INITIALIZER,
    0,
    NULL,
    MUTEX_INITIALIZER,
    0,
    NULL
};

/* Private function prototypes ---------------------------- */

/* @brief   Architecture specific routine to get the running task tls
 *
 * @param   None
 *
 * @retval	Pointer to taks local storage
 */


/* Private functions -------------------------------------- */

int32_t key_create(key_t* key, void (*destructor)(void *))
{
    int32_t ret = MutexLock(&keys.key_mux);

    if(ret != E_OK)
    {
        return ret;
    }

    if(keys.destructors == NULL)
    {
        keys.destructors = (key_destructor_t*)malloc(sizeof(key_destructor_t) * KEYS_MAX);

        if(keys.destructors == NULL)
        {
            MutexUnlock(&keys.key_mux);
            return E_NO_MEMORY;
        }

        memset(keys.destructors, (int32_t)KEY_INVAL, sizeof(key_destructor_t) * KEYS_MAX);
    }

    // Ensure that we were not called with a invalid destructor
    if(destructor == KEY_INVAL)
    {
        MutexUnlock(&keys.key_mux);
        return E_INVAL;
    }

    if(keys.count >= KEYS_MAX)
    {
        MutexUnlock(&keys.key_mux);
        return E_AGAIN;
    }

    int32_t i;
    for(i = 0; i < KEYS_MAX; ++i)
    {
        if(keys.destructors[i] == KEY_INVAL)
        {
            break;
        }
    }

    // If this happen we have some how curropted the keys
    if(i >= KEYS_MAX)
    {
        MutexUnlock(&keys.key_mux);
        return E_AGAIN;
    }

    keys.destructors[i] = destructor;
    *key = (key_t)i;
    keys.count += 1;

    MutexUnlock(&keys.key_mux);

    return E_OK;
}

int32_t key_set(key_t key, const void* value)
{
    volatile tls_t* tls = gettls();

    if(key < 0 || key >= KEYS_MAX || keys.destructors == NULL || keys.destructors[key] == KEY_INVAL)
    {
        return E_INVAL;
    }

    if(key < tls->numkeys)
    {
        tls->keydata[key] = (void *)value;
        return E_OK;
    }

    int32_t ret = MutexLock(&keys.array_mux);

    if(ret != E_OK)
    {
        return ret;
    }

    uint32_t index = (tls->tid & 0xFFFF) + 1;

    if(tls->keydata == NULL)
    {
        // We need to set the keys array for the running task
        if(index >= keys.size)
        {
            keyinfo_t* info = (keyinfo_t*)realloc(keys.array, index * sizeof(keyinfo_t));

            if(info == NULL)
            {
                MutexUnlock(&keys.array_mux);
                return E_NO_MEMORY;
            }

            keys.array = info;
            memset(&(keys.array[keys.size]), 0, sizeof(keyinfo_t) * (index - keys.size));
            keys.size = index;
        }

        // If this tid was already used, re-use the data (cleaned)
        tls->keydata = keys.array[index - 1].data;
        tls->numkeys = keys.array[index - 1].count;
        memset(tls->keydata, 0x0, sizeof(keyinfo_t) * tls->numkeys);

        if(key < tls->numkeys)
        {
            MutexUnlock(&keys.array_mux);
            tls->keydata[key] = (void *)value;
            return E_OK;
        }
    }

    // Not enough space on the key array so grow it
    keyinfo_t* info = realloc(tls->keydata, (key + 1) * sizeof(keyinfo_t));

    if(info == NULL)
    {
        MutexUnlock(&keys.array_mux);
        return E_NO_MEMORY;
    }

    tls->keydata = (void*)info;
    keys.array[index - 1].data = (void*)info;
    memset(&(tls->keydata[tls->numkeys]), 0, sizeof(keyinfo_t) * ((key + 1) - tls->numkeys));
    tls->numkeys = key + 1;
    keys.array[index - 1].count = key + 1;

	MutexUnlock(&keys.array_mux);
    tls->keydata[key] = (void *)value;

    return E_OK;
}

void* key_get(key_t key)
{
	if(key < gettls()->numkeys)
    {
		return gettls()->keydata[key];
    }
	return NULL;
}

int32_t key_delete(key_t key)
{
    int ret = MutexLock(&keys.key_mux);

    if(ret != E_OK)
    {
        return ret;
    }

    if(key < 0 || key >= KEYS_MAX || keys.destructors == NULL || keys.destructors[key] == KEY_INVAL)
    {
        MutexUnlock(&keys.key_mux);
        return E_INVAL;
    }

    keys.destructors[key] = KEY_INVAL;
    keys.count -= 1;

    int32_t i;
    for (i = 0; i < keys.size; ++i)
    {
        if(keys.array[i].data != NULL && key < keys.array[i].count)
        {
            keys.array[i].data = NULL;
        }
    }

    MutexUnlock(&keys.key_mux);

    return E_OK;
}

void _keys_flush()
{
    tls_t* tls = TLS();

    uint32_t num = ((tls->numkeys < keys.count) ? (tls->numkeys): (keys.count));
    uint32_t i = 0;
    for(; i < num; ++i)
    {
        if((keys.destructors[i] != NULL) && (keys.destructors[i] != KEY_INVAL) && (tls->keydata[i] != NULL))
        {
            void* data = tls->keydata[i];
            key_destructor_t destructor = keys.destructors[i];
            tls->keydata[i] = NULL;
            destructor(data);
        }
    }
}