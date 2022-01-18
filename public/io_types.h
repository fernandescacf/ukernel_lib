/**
 * @file        io_types.h
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        05 May, 2020
 * @brief       IO Types Definition Header File
*/

#ifndef _IO_TYPES_H_
#define _IO_TYPES_H_

#ifdef __cplusplus
    extern "C" {
#endif


/* Includes ----------------------------------------------- */
#include <types.h>
#include <task.h>


/* Exported types ----------------------------------------- */

// Message info structure
typedef struct
{
    pid_t       pid;
    uint32_t    tid;
    int32_t     chid;
    int32_t     coid;
    int32_t     scoid;
}msg_info_t;

typedef struct
{
	int32_t type;
	int32_t code;
	size_t  sbytes;
	size_t  rbytes;
}io_hdr_t;

// Notify structure
typedef struct
{
	int32_t type;
	int32_t data;
	int32_t scoid;
}notify_t;

// System Types For _IO_INFO reply
typedef struct
{
	int32_t  type;
	uint32_t nentries;
	uint32_t sentries;
	uint32_t len;
	char name[1];
}nentry_t;

typedef struct
{
	int32_t  type;
	pid_t    pid;
	int32_t  chid;
	uint32_t len;
	char name[1];
}sentry_t;

typedef struct
{
	int32_t  type;
	size_t   size;
	uint32_t len;
	char name[1];
}fentry_t;

typedef struct
{
	int32_t  type;
//  uint32_y entries;
	uint32_t len;
	char name[1];
}dentry_t;

typedef union
{
	int32_t  type;
	nentry_t namespace;
	sentry_t server;
	fentry_t file;
	dentry_t dir;
}io_entry_t;

/* Exported constants ------------------------------------- */
// System Request Types
#define _IO_INFO		0x00
#define _IO_READ		0x01
#define _IO_WRITE		0x02
#define _IO_OPEN		0x03
#define _IO_CLOSE		0x04
#define _IO_MMAP		0x05
#define _IO_IOCTL		0x06
#define _IO_SEEK		0x07
#define _IO_SPACE		0x08

// _IO_INFO reply types
#define INFO_NAMESPACE	0x1
#define INFO_SERVER	    0x2
#define INFO_FILE	    0x3
#define INFO_DIR	    0x4
// _IO_INFO codes
#define INFO_NAMESPACE_LS	 0
#define INFO_DIRECTORY_LS	 0
// codes[0x1...0x7FFFFFFF] -> used to specify namespace entries
#define INFO_BEST_MATCH		-1
#define INFO_LIST_ALL		-2

// _IO_READ codes
#define _IO_READ_SIZE			0x0		// Read specified bytes
#define _IO_READ_TERMINATOR		0x1		// Read till terminator byte

/* Exported macros ---------------------------------------- */


/* Exported functions ------------------------------------- */


#ifdef __cplusplus
    }
#endif

#endif /* _IO_TYPES_H_ */
