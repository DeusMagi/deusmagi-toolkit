/**
 * @file
 * Logger API header file.
 *
 * @author Alex Tokar
 */

#ifndef TOOLKIT_LOGGER_H
#define TOOLKIT_LOGGER_H

#include "toolkit.h"

typedef void (*logger_print_func)(const char *str);

/**
 * Possible log levels.
 */
typedef enum logger_level {
    LOG_CHAT,
    LOG_INFO,
    LOG_SYSTEM,
    LOG_ERROR,
    LOG_BUG,
    LOG_DEBUG,
    LOG_DEVEL,
    LOG_PACKET,
    LOG_DUMPRX,
    LOG_DUMPTX,
    LOG_HTTP,

    LOG_MAX
} logger_level;

#define log_error(...) \
    do { \
        logger_traceback(); \
        LOG(ERROR, ##__VA_ARGS__); \
    } while (0)
#define LOG(_level, ...) \
    do { \
        logger_print(LOG_ ## _level, __FUNCTION__, __LINE__, ## __VA_ARGS__); \
    } while(0)

/* Prototypes */

TOOLKIT_FUNCS_DECLARE(logger);

void logger_open_log(const char *path);
FILE *logger_get_logfile(void);
logger_level logger_get_level(const char *name);
void logger_set_filter_stdout(const char *str);
void logger_set_filter_logfile(const char *str);
void logger_set_print_func(logger_print_func func);
void logger_do_print(const char *str);
void logger_print(logger_level level, const char *function, uint64_t line,
        const char *format, ...) __attribute__((format(printf, 4, 5)));
void logger_traceback(void);

#endif
