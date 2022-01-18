/**
 * @file        list.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        16 August, 2018
 * @brief       Generic list implementation
*/

/* Includes ----------------------------------------------- */
#include <list.h>
#include <stdlib.h>


/* Private types ------------------------------------------ */
typedef struct listNode
{
    listNode_t *next, *prev;
    void       *data;
}listNode_t;


/* Private constants -------------------------------------- */


/* Private macros ----------------------------------------- */


/* Private variables -------------------------------------- */


/* Private function prototypes ---------------------------- */

int32_t ListInsert(list_t *list, listNode_t *node)
{
    listNode_t *iterator = list->first;

    if(NULL == list->ListSort)
    {
        return E_FAULT;
    }

    while(NULL != iterator && 0 < list->ListSort(iterator->data, node->data))
    {
        iterator = iterator->next;
    }

    if(NULL == iterator)
    {
        //Insert new object at the end of the list
        node->next = NULL;
        node->prev = list->last;

        if(list->last)
        {
            list->last->next = node;
        }
        else
        {
            list->first = node;
        }

        list->last = node;
    }
    else
    {
        node->next = iterator;
        node->prev = iterator->prev;
        iterator->prev = node;

        if(node->prev)
        {
            node->prev->next = node;
        }
        else{
            list->first = node;
        }
    }

    list->count += 1;

    return E_OK;
}

listNode_t *ListSearch(list_t *list, void *value)
{
    listNode_t *iterator = list->first;
    int32_t count = list->count;

    if(NULL == list->ListCmp)
    {
        return NULL;
    }

    while(0 < count && 0 != list->ListCmp(iterator->data, value))
    {
        iterator = iterator->next;
        count -= 1;
    }

    if(0 == count)
    {
        return NULL;
    }
    else
    {
        list->current = iterator;
        return iterator;
    }
}

void *ListRemoveNode(list_t *list, listNode_t *node)
{
    if(NULL != node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
        list->first = node->next;
    }

    if(NULL != node->next)
    {
        node->next->prev = node->prev;
    }
    else
    {
        list->last = node->prev;
    }

    void *data = node->data;
    free(node);
    list->count -= 1;

    return data;
}


/* Private functions -------------------------------------- */

/**
 * ListInitialize Implementation (See header file for description)
*/
int32_t ListInitialize(list_t *list, int32_t (*ListSort)(void *, void *), int32_t (*ListCmp) (void *, void *))
{
    if(NULL == list)
    {
        return E_INVAL;
    }

    list->first = 0;
    list->last = 0;
    list->current = 0;
    list->count = 0;
    list->ListCmp = ListCmp;
    list->ListSort = ListSort;

    return E_OK;
}

int32_t ListSetSort(list_t *list, int32_t (*ListSort)(void *, void *))
{
    if(NULL == list)
    {
        return E_INVAL;
    }

    list->ListSort = ListSort;

    return E_OK;
}

int32_t ListSetCmp(list_t *list, int32_t (*ListCmp) (void *, void *))
{
    if(NULL == list)
    {
        return E_INVAL;
    }
    
    list->ListCmp = ListCmp;

    return E_OK;
}

int32_t ListInsertObject(list_t *list, void *obj)
{
    if(NULL == list)
    {
        return E_INVAL;
    }

    // Alloc node for the new object
    listNode_t *node = (listNode_t *)malloc(sizeof(listNode_t));

    if(NULL == node)
    {
        return E_NO_RES;
    }

    node->data = obj;
    node->next = NULL;
    node->prev = NULL;

    list->current = node;

    return ListInsert(list,node);
}

void *ListGetFirst(list_t *list)
{
    if(NULL == list)
    {
        return NULL;
    }

    if(NULL != list->first)
    {
        list->current = list->first;
        return list->current->data;
    }
    else
    {
        return NULL;
    }
}

void *ListGetLast(list_t *list)
{
    if(NULL == list)
    {
        return NULL;
    }

    if(NULL != list->last)
    {
        list->current = list->last;
        return list->current->data;
    }
    else
    {
        return NULL;
    }
}

void *ListGetNext(list_t *list)
{
    if(NULL == list)
    {
        return NULL;
    }

    if(NULL != list->current)
    {
        list->current = list->current->next;
        if(NULL != list->current)
        {
            return list->current->data;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

void *ListGetPrev(list_t *list)
{
    if(NULL == list)
    {
        return NULL;
    }

    if(NULL != list->current)
    {
        list->current = list->current->prev;
        if(NULL != list->current)
        {
            return list->current->data;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

void *ListGetObject(list_t *list, void *value)
{
    if(NULL == list)
    {
        return NULL;
    }

    list->current = ListSearch(list, value);
    return ((NULL != list->current) ? (list->current->data) : (NULL));

    return NULL;
}

void *ListRemoveCurrent(list_t *list)
{
    if(NULL == list || NULL == list->current)
    {
        return NULL;
    }

    void *data = ListRemoveNode(list, list->current);

    list->current = NULL;

    return data;
}

void *ListRemoveObject(list_t *list, void *value)
{
    if(NULL == list)
    {
        return NULL;
    }

    listNode_t *node = ListSearch(list, value);

    if(NULL == node)
    {
        return NULL;
    }

    list->current = NULL;

    return ListRemoveNode(list, node);
}
