/**
 * @file
 * Memory API header file.
 */

#ifndef TOOLKIT_MEMORY_H
#define TOOLKIT_MEMORY_H

#include "toolkit.h"

/* Map the error-checking memory allocating/freeing functions into the toolkit
 * variants. This is done for convenience, and because the functions can't be
 * defined as emalloc as they will conflict with functions from other libraries
 * such as libcheck. */
#ifndef NDEBUG
#define MEMORY_DEBUG_INFO , __FILE__, __LINE__
#define MEMORY_DEBUG_PROTO , const char *file, uint32_t line
#define MEMORY_DEBUG_PARAM , file, line
#else
#define MEMORY_DEBUG_INFO
#define MEMORY_DEBUG_PROTO
#define MEMORY_DEBUG_PARAM
#endif

#define emalloc(_size) memory_emalloc(_size MEMORY_DEBUG_INFO)
#define efree(_ptr) memory_efree(_ptr MEMORY_DEBUG_INFO)
#define ecalloc(_nmemb, _size) memory_ecalloc(_nmemb, _size MEMORY_DEBUG_INFO)
#define erealloc(_ptr, _size) memory_erealloc(_ptr, _size MEMORY_DEBUG_INFO)
#define ereallocz(_ptr, _old_size, _new_size) \
    memory_reallocz(_ptr, _old_size, _new_size MEMORY_DEBUG_INFO)

typedef enum memory_status {
    MEMORY_STATUS_DISABLED = -1,
    MEMORY_STATUS_OK = 0,
    MEMORY_STATUS_FREE = 1
} memory_status_t;

/* Prototypes */

TOOLKIT_FUNCS_DECLARE(memory);

void *memory_emalloc(size_t size MEMORY_DEBUG_PROTO);
void memory_efree(void *ptr MEMORY_DEBUG_PROTO);
void *memory_ecalloc(size_t nmemb, size_t size MEMORY_DEBUG_PROTO);
void *memory_erealloc(void *ptr, size_t size MEMORY_DEBUG_PROTO);
void *memory_reallocz(void *ptr, size_t old_size, size_t new_size
        MEMORY_DEBUG_PROTO);
void memory_check_all(void);
bool memory_check(void *ptr);
bool memory_get_status(void *ptr, memory_status_t *status);
bool memory_get_size(void *ptr, size_t *size);
size_t memory_check_leak(bool verbose);

#endif
