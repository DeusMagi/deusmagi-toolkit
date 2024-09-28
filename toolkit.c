/**
 * @file
 * Toolkit system.
 *
 * @author Alex Tokar
 */

#include "toolkit.h"

/**
 * One toolkit API entry.
 */
typedef struct toolkit_api {
    char *name; ///< Name of the API.
    toolkit_func deinit_fnc; ///< Deinit function.
} toolkit_api_t;

/**
 * All the registered APIs.
 */
static toolkit_api_t *apis = NULL;
/**
 * Number of ::apis.
 */
static size_t apis_num = 0;

/**
 * Registers an API import.
 * @param name
 * Name of the API to register.
 * @param func
 * Deinitialization function.
 */
void toolkit_import_register(const char *name, toolkit_func func)
{
    HARD_ASSERT(name != NULL);
    HARD_ASSERT(func != NULL);

    if (toolkit_check_imported(func)) {
        return;
    }

    apis = realloc(apis, sizeof(*apis) * (apis_num + 1));

    if (apis == NULL) {
        log_error("OOM.");
        abort();
    }

    apis[apis_num].name = strdup(name);

    if (apis[apis_num].name == NULL) {
        log_error("OOM.");
        abort();
    }

    apis[apis_num].deinit_fnc = func;
    apis_num++;
}

/**
 * Checks if the specified API was registered, identified by its
 * deinitialization function.
 * @param func
 * Deinitialization function.
 * @return
 * Whether the API was registered.
 */
bool toolkit_check_imported(toolkit_func func)
{
    size_t i;

    for (i = 0; i < apis_num; i++) {
        if (apis[i].deinit_fnc == func) {
            return true;
        }
    }

    return false;
}

/**
 * Deinitializes all the registered APIs.
 */
void toolkit_deinit(void)
{
    size_t i, len;
    char buf[HUGE_BUF];

    buf[0] = '\0';

    for (i = apis_num; i > 0; i--) {
        len = strnlen(buf, sizeof(buf));
        snprintf(buf + len, sizeof(buf) - len, "%s%s",
                buf[0] != '\0' ? ", " : "", apis[i - 1].name);
    }

    LOG(DEVEL, "Deinitializing APIs in the following order: %s", buf);

    for (i = apis_num; i > 0; i--) {
        apis[i - 1].deinit_fnc();
        free(apis[i - 1].name);
    }

    if (apis != NULL) {
        free(apis);
        apis = NULL;
    }

    apis_num = 0;
}
