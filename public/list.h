/**
 * @file        list.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        16 August, 2018
 * @brief       Generic list Definition Header File
*/

#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
    extern "C" {
#endif


/* Includes ----------------------------------------------- */
#include <types.h>


/* Exported types ----------------------------------------- */

typedef struct listNode listNode_t;

typedef struct
{
    uint32_t		count;
    listNode_t		*first, *last, *current;
    int32_t (*ListSort)	(void *, void *);
    int32_t (*ListCmp)	(void *, void *);
}list_t;

/* Exported constants ------------------------------------- */


/* Exported macros ---------------------------------------- */



/* Exported functions ------------------------------------- */

int32_t ListInitialize(list_t *list, int32_t (*ListSort)(void *, void *), int32_t (*ListCmp) (void *, void *));

int32_t ListSetSort(list_t *list, int32_t (*ListSort)(void *, void *));

int32_t ListSetCmp(list_t *list, int32_t (*ListCmp) (void *, void *));

int32_t ListInsertObject(list_t *list, void *obj);


void *ListGetFirst(list_t *list);

void *ListGetLast(list_t *list);

void *ListGetNext(list_t *list);

void *ListGetPrev(list_t *list);

void *ListGetObject(list_t *list, void *value);


void *ListRemoveCurrent(list_t *list);

void *ListRemoveObject(list_t *list, void *value);

#ifdef __cplusplus
    }
#endif

#endif // LIST_H
