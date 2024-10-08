/**
 * @file
 * Cross-platform support header file.
 */

#ifndef TOOLKIT_PORTING_H
#define TOOLKIT_PORTING_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifdef __GNUC__
#define likely(x)           __builtin_expect(!!(x), 1)
#define unlikely(x)         __builtin_expect(!!(x), 0)
#else
/* If we're not using GNU C, ignore __attribute__ */
#define  __attribute__(x)
/* Ignore likely/unlikely branch prediction when not using GNU C.*/
#define likely(x)           (x)
#define unlikely(x)         (x)
#endif

#ifdef WIN32
#ifndef WINVER
#define WINVER 0x502
#endif
#endif

#include "cmake.h"

#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <setjmp.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <inttypes.h>

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#ifdef HAVE_TIME_H
#include <time.h>
#endif

#ifdef HAVE_STDDEF_H
#include <stddef.h>
#endif

#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

#ifdef HAVE_CRYPT_H
#include <crypt.h>
#endif

#ifdef HAVE_SYS_SOCKET_H
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#endif

#ifdef HAVE_DIRENT_H
#include <dirent.h>
#define NAMLEN(dirent) (strlen((dirent)->d_name))
#elif defined(HAVE_SYS_NDIR_H) || defined(HAVE_SYS_DIR_H) || defined(HAVE_NDIR_H)
#define dirent direct
#define NAMLEN(dirent) ((dirent)->d_namlen)
#ifdef HAVE_SYS_NDIR_H
#include <sys/ndir.h>
#endif
#ifdef HAVE_SYS_DIR_H
#include <sys/dir.h>
#endif
#ifdef HAVE_NDIR_H
#include <ndir.h>
#endif
#endif

#ifdef HAVE_X11
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#ifdef HAVE_X11_XMU
#include <X11/Xmu/Atoms.h>
#endif
#endif

#include <pthread.h>

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <shellapi.h>

#ifdef __MINGW32__
#include <ws2tcpip.h>

#ifndef AI_NUMERICSERV
#define AI_NUMERICSERV 0x00000008
#endif

#ifndef IPV6_V6ONLY
#define IPV6_V6ONLY 27
#endif
#endif

#define mkdir(__a, __b) mkdir(__a)
#define sleep(_x) Sleep((_x) * 1000)

#ifdef __MINGW32__
#define _set_fmode(_mode) \
        { \
            _fmode = (_mode); \
        }
#endif

#undef X509_NAME
#endif

#define GETTIMEOFDAY(last_time) gettimeofday(last_time, NULL);

#ifdef HAVE_SRANDOM
#define RANDOM() random()
#define SRANDOM(xyz) srandom(xyz)
#else
#ifdef HAVE_SRAND48
#define RANDOM() lrand48()
#define SRANDOM(xyz) srand48(xyz)
#else
#ifdef HAVE_SRAND
#define RANDOM() rand()
#define SRANDOM(xyz) srand(xyz)
#else
#error "Could not find a usable random routine"
#endif
#endif
#endif

#ifdef HAVE_STRICMP
#define strcasecmp _stricmp
#endif

#ifdef HAVE_STRNICMP
#define strncasecmp _strnicmp
#endif

#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif

#ifndef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

#ifndef FABS
#define FABS(x) ((x) < 0 ? -(x) : (x))
#endif

#ifndef ABS
#define ABS(x) ((x) < 0 ? -(x) : (x))
#endif

/* Make sure M_PI is defined. */
#ifndef M_PI
#define M_PI 3.141592654
#endif

#ifndef F_OK
#define F_OK 6
#endif

#ifndef R_OK
#define R_OK 6
#endif

#ifndef W_OK
#define W_OK 2
#endif

#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT 0
#endif

/** Used for faces. */
typedef uint16_t Fontindex;

/** Object unique IDs. */
typedef uint32_t tag_t;

/* Only C99 has lrint. */
#if !defined(_ISOC99_SOURCE) && (!defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE < 200112L)
#define lrint(x) (floor((x) + ((x) > 0) ? 0.5 : -0.5))
#endif

#if defined(HAVE_X11)
typedef Display *x11_display_type;
typedef Window x11_window_type;
#elif defined(WIN32)
typedef HWND x11_display_type;
typedef HWND x11_window_type;
#else
typedef void *x11_display_type;
typedef void *x11_window_type;
#endif

#ifndef HAVE_STRTOK_R
extern char *_strtok_r(char *s, const char *delim, char **save_ptr);
#undef strtok_r
#define strtok_r _strtok_r
#endif

#ifndef HAVE_TEMPNAM
extern char *_tempnam(const char *dir, const char *pfx);
#undef tempnam
#define tempnam _tempnam
#endif

#ifndef HAVE_STRDUP
extern char *_strdup(const char *s);
#undef strdup
#define strdup _strdup
#endif

#ifndef HAVE_STRNDUP
extern char *_strndup(const char *s, size_t n);
#undef strndup
#define strndup _strndup
#endif

#ifndef HAVE_STRERROR
extern char *_strerror(int errnum);
#undef strerror
#define strerror _strerror
#endif

#ifndef HAVE_STRCASESTR
extern const char *_strcasestr(const char *haystack, const char *needle);
#undef strcasestr
#define strcasestr _strcasestr
#endif

#ifndef HAVE_GETTIMEOFDAY

struct timezone {
    /* Minutes west of Greenwich. */
    int tz_minuteswest;
    /* Type of DST correction. */
    int tz_dsttime;
};

extern int _gettimeofday(struct timeval *tv, struct timezone *tz);
#undef gettimeofday
#define gettimeofday _gettimeofday
#endif

#ifndef HAVE_GETLINE
extern ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
#undef getline
#define getline _getline
#endif

#ifndef HAVE_USLEEP
extern int _usleep(uint32_t usec);
#undef usleep
#define usleep _usleep
#endif

#ifndef HAVE_STRNLEN
extern size_t _strnlen(const char *s, size_t max);
#undef strnlen
#define strnlen _strnlen
#endif

#ifndef HAVE_MKSTEMP
extern int _mkstemp(char *tmpl);
#undef mkstemp
#define mkstemp _mkstemp
#endif

#ifndef HAVE_SINCOS
extern void _sincos(double x, double *s, double *c);
#undef sincos
#define sincos _sincos
#endif

#endif
