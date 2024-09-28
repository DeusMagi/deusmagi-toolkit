/**
 * @file
 * Console API header file.
 *
 * @author Alex Tokar
 */

#ifndef TOOLKIT_CONSOLE_H
#define TOOLKIT_CONSOLE_H

#include "toolkit.h"

/**
 * Console command handler function.
 */
typedef void (*console_command_func)(const char *params);

/**
 * One console command.
 */
typedef struct console_command_struct {
    /** Name of the command. */
    char *command;

    /** The function that will handle the command. */
    console_command_func handle_func;

    /** Brief, one-line description of the command. */
    char *desc_brief;

    /** Detailed description of the command. */
    char *desc;
} console_command_struct;

/* Prototypes */

TOOLKIT_FUNCS_DECLARE(console);

/**
 * Start the console stdin-reading thread.
 *
 * @return
 * 1 on success, 0 on failure.
 */
extern int
console_start_thread(void);

/**
 * Add a possible command to the console.
 *
 * @param command
 * Command name, must be unique.
 * @param handle_func
 * Function that will handle the command.
 * @param desc_brief
 * Brief, one-line description of the command.
 * @param desc
 * More detailed description of the command.
 */
extern void
console_command_add(const char          *command,
                    console_command_func handle_func,
                    const char          *desc_brief,
                    const char          *desc);

/**
 * Process the console API. This should usually be part of the program's
 * main loop.
 */
extern void
console_command_handle(void);

#endif
