/**
 * @file
 * Date and time API header file.
 *
 * @author Alex Tokar
 */

#ifndef TOOLKIT_DATETIME_H
#define TOOLKIT_DATETIME_H

#include "toolkit.h"

/* Prototypes */

TOOLKIT_FUNCS_DECLARE(datetime);

/**
 * Get the current UTC time as UNIX timestamp.
 *
 * @return
 * UTC time as UNIX timestamp.
 */
extern time_t
datetime_getutc(void);

/**
 * Converts UTC time to local time.
 *
 * @param t
 * UTC time.
 * @return
 * Converted local time.
 */
extern time_t
datetime_utctolocal(time_t t);

#endif
