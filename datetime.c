/**
 * @file
 * Date and time API.
 *
 * @author Alex Tokar
 */

#include "datetime.h"

TOOLKIT_API();

TOOLKIT_INIT_FUNC(datetime)
{
}
TOOLKIT_INIT_FUNC_FINISH

TOOLKIT_DEINIT_FUNC(datetime)
{
}
TOOLKIT_DEINIT_FUNC_FINISH

time_t
datetime_getutc (void)
{
    TOOLKIT_PROTECT();

    time_t t;
    time(&t);
    struct tm *tm = gmtime(&t);

    return mktime(tm);
}

time_t
datetime_utctolocal (time_t t)
{
    TOOLKIT_PROTECT();
    return t - (datetime_getutc() - time(NULL));
}
