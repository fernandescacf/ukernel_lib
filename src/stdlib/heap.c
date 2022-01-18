/**
 * @file        k_heap.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        5 May, 2015
 * @brief       heap source file
*/

/* Includes ----------------------------------------------- */
#include <stdlib.h>
#include <string.h>
#include <mman.h>
#include <mutex.h>

/* Private types ------------------------------------------ */

typedef struct MEM_BLOCK{
    uint32_t size;
    struct MEM_BLOCK * next;
}mem_block;

/* Private constants -------------------------------------- */


/* Private macros ----------------------------------------- */


/* Private variables -------------------------------------- */
static mem_block *free_list_first = NULL;
static mem_block *allocated_list_first = NULL;
static mem_block *allocated_list_last = NULL;
static mutex_t heap_lock;


/* Private function prototypes ---------------------------- */

static inline void * sbrk(void)
{
	return mmap( 0, 0x1000, (PROT_READ|PROT_WRITE), (MAP_PRIVATE | MAP_ANON), NOFD, 0x0);
}

void * _malloc(uint32_t size);

void * _realloc(void * ptr, uint32_t size);

void _free(void * ptr);

/* Private functions -------------------------------------- */

void *malloc(uint32_t size){
	if(free_list_first == NULL){
		MutexInit(&heap_lock);
	}
	MutexLock(&heap_lock);
	void *ptr = _malloc(size);
	MutexUnlock(&heap_lock);
	return ptr;
}

void *realloc(void * ptr, uint32_t size){
	if(free_list_first == NULL){
		MutexInit(&heap_lock);
	}
	MutexLock(&heap_lock);
	void *_ptr = _realloc(ptr,size);
	MutexUnlock(&heap_lock);
	return _ptr;
}

void free(void * ptr){
	MutexLock(&heap_lock);
	_free(ptr);
	MutexUnlock(&heap_lock);
}

/**
 * k_malloc Implementation (See header file for description)
*/
void * _malloc(uint32_t size){

     mem_block * iterator;
     mem_block * prev;
     mem_block * allocated_block = NULL;

     if(size == 0)
     {
    	return NULL;
     }

     /* 4 bit alignment */
     if(size & 0x3)
     	size = ((size & 0xFFFFFFFC) + 0x4);

    // initialize the list of free memory blocks
    if(free_list_first == NULL)
    {
        free_list_first = (mem_block *)sbrk();
        free_list_first->size = 4096;//HEAP_SIZE;
        free_list_first->next = NULL;
    }

    iterator = free_list_first;
    prev = NULL;

    // find a free block with enough size
    while(iterator != NULL && iterator->size < (size + sizeof(mem_block))){
        prev = iterator;
        iterator = iterator->next;
    }

    // allocate the funded block
    if(iterator != NULL){
        allocated_block = iterator;
        if(iterator->size > (size + 2*sizeof(mem_block))){
            // break the block of memory
            iterator = (mem_block *)((uint32_t)iterator + size + sizeof(mem_block));
            iterator->size = allocated_block->size - (size + sizeof(mem_block));
            iterator->next = allocated_block->next;
            if(prev != NULL){
                prev->next = iterator;
            }
            else{
                free_list_first = iterator;
            }
            allocated_block->size = (size + sizeof(mem_block));
            allocated_block->next = NULL;
        }
        else{ //otherwise allocate the whole block
            if(prev != NULL){
                prev->next = iterator->next;
            }
            else{
                free_list_first = iterator->next;
            }
            allocated_block = iterator;
            allocated_block->next = NULL;
        }

        if(free_list_first == allocated_block){
            free_list_first = iterator;
        }

        // case if there isn't any block allocated
        if(allocated_list_first != NULL){
            allocated_list_last->next = allocated_block;
            allocated_list_last = allocated_block;
        }
        else{ // add the new block to the en «d of the allocated blocks list
            allocated_list_first = allocated_block;
            allocated_list_last = allocated_block;
        }
    }
    else{
    	// Not enough memory
    	mem_block *ptr = (mem_block*)sbrk();
    	ptr->size = (size + sizeof(mem_block));
    	// I'm assuming that the 4096 will always be enough but the may not be true
    	// so in the future change this!!!!
    	prev->next = (mem_block *)((uint32_t)ptr + ptr->size);
    	prev->next->next = NULL;
    	prev->next->size = 4096 - ptr->size;
    	return (void*)((uint32_t)ptr + sizeof(mem_block));
    }
    if(allocated_block != NULL){
        return (void *)((uint32_t)allocated_block + sizeof(mem_block));
    }
    else{
        return NULL;
    }
}

/**
 * k_realloc Implementation (See header file for description)
*/
void * _realloc(void * ptr, uint32_t size){
    mem_block * iterator;
    mem_block * prev;
    mem_block * aux;
    mem_block * reallocated_block = (mem_block *)((uint32_t)ptr - sizeof(mem_block));

    if(ptr == NULL)
    {
        // if ptr is null allocate a new block
        return _malloc(size);
    }
    if(size == 0)
    {
        // if size is zero free the block
        _free(ptr);
        return NULL;
    }
    if((size + sizeof(mem_block)) == reallocated_block->size)
    {
        // if sizes are equal do nothing
        return ptr;
    }
    if(reallocated_block->size > (size + sizeof(mem_block)))
    {
        // new size smaller than older size
        if((reallocated_block->size - (size + sizeof(mem_block))) > sizeof(mem_block))
        {
            // split block if the remaining space is enough for a new free block
            iterator = (mem_block *)((uint32_t)reallocated_block + size + sizeof(mem_block));
            iterator->size = reallocated_block->size - (size + sizeof(mem_block));
            iterator->next = NULL;
            reallocated_block->size = size + sizeof(mem_block);
            allocated_list_last->next = iterator;
            allocated_list_last = iterator;
            _free((void *)((uint32_t)iterator + sizeof(mem_block)));
        }
        reallocated_block = (mem_block *)ptr;
    }
    else
    {
        //new size bigger than older size
        iterator = free_list_first;
        prev = NULL;
        while(iterator != NULL && (uint32_t)iterator != ((uint32_t)reallocated_block + reallocated_block->size))
        {
            prev = iterator;
            iterator = iterator->next;
        }
        if(iterator != NULL && iterator->size >= (size - reallocated_block->size + sizeof(mem_block)))
        {
            // expand volume
            if(iterator->size - (size - reallocated_block->size + sizeof(mem_block)) > sizeof(mem_block))
            {
                // split block if the remaining space is enough for a new free block
                uint32_t aux_size = iterator->size;
                mem_block * aux_next = iterator->next;
                aux = (mem_block*)((uint32_t)iterator + (size - reallocated_block->size + sizeof(mem_block)));
                aux->size = aux_size - (size - reallocated_block->size + sizeof(mem_block));
                aux->next = aux_next;
                reallocated_block->size = size + sizeof(mem_block);
                if(prev != NULL)
                {
                    prev->next = aux;
                }
                else
                {
                    free_list_first = aux;
                }
            }
            else
            {
                reallocated_block->size += iterator->size;
                if(prev != NULL)
                {
                    prev->next = iterator->next;
                }
                else
                {
                    free_list_first = iterator->next;
                }
            }
            reallocated_block = (mem_block *)ptr;
        }
        else
        {
            // allocate new block and free the old one
            iterator = (mem_block*)_malloc(size);
            if(iterator == NULL)
            {
                return NULL;
            }
            // copy old block to new block
            uint8_t *old_block_ptr = (uint8_t *)((uint32_t)reallocated_block + sizeof(mem_block));
//            uint8_t *new_block_ptr = (uint8_t *)iterator;
            memcpy(iterator, old_block_ptr, (reallocated_block->size - sizeof(mem_block)));
//            uint32_t i;
//            for(i=sizeof(mem_block); i<reallocated_block->size; i++)
//            {
//                (*new_block_ptr) = (*old_block_ptr);	// deve dar assim -> *new_block_ptr = *old_block_ptr++;
//                new_block_ptr++;						// ou usar a funcao -> sw_memmove()
//                old_block_ptr++;
//            }
            // free old block
            _free((void*)((uint32_t)reallocated_block + sizeof(mem_block)));
            reallocated_block = iterator;
        }
    }
    return (void *)reallocated_block;
}

/**
 * k_calloc Implementation (See header file for description)
*/
void * calloc(uint32_t num, uint32_t size){
	return NULL;
}

/**
 * k_free Implementation (See header file for description)
*/
void _free(void * ptr){
    mem_block * iterator;
    mem_block * prev;
    mem_block * free_block = (mem_block *)((uint32_t)ptr- sizeof(mem_block));

    iterator = allocated_list_first;
    prev = NULL;
    while(iterator != NULL && iterator != free_block){
        prev = iterator;
        iterator = iterator->next;
    }

    if(iterator != NULL){
        if(prev != NULL){
            prev->next = iterator->next;
            if(prev->next == NULL){
                allocated_list_last = prev;
            }
        }
        else{
            allocated_list_first = iterator->next;
        }
        iterator = free_list_first;
        prev = NULL;
        while(iterator != NULL && (uint32_t)iterator < (uint32_t)free_block){
            prev = iterator;
            iterator = iterator->next;
        }
        if(iterator != NULL){
            if(prev != NULL){
                if(((uint32_t)prev + prev->size) == (uint32_t)free_block){
                    // join blocks
                    prev->size += free_block->size;
                    free_block = prev;
                }
                else{
                    prev->next = free_block;
                }
            }
            else{ // insert in the beginning
                free_list_first = free_block;
            }
            if(((uint32_t)free_block + free_block->size) == (uint32_t)iterator){
                //join blocks
                free_block->size += iterator->size;
                free_block->next = iterator->next;
            }
            else{
                free_block->next = iterator;
            }
        }
        else{ // insert in the end
            if(((uint32_t)prev + prev->size) == (uint32_t)free_block){
                prev->size += free_block->size;
            }
            else{
                free_block->next = NULL;
                prev->next = free_block;
            }
        }
    }
}

