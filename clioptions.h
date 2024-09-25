/*************************************************************************
 *           Atrinik, a Multiplayer Online Role Playing Game             *
 *                                                                       *
 *   Copyright (C) 2009-2014 Alex Tokar and Atrinik Development Team     *
 *                                                                       *
 * Fork from Crossfire (Multiplayer game for X-windows).                 *
 *                                                                       *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the Free Software           *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.             *
 *                                                                       *
 * The author can be reached at admin@atrinik.org                        *
 ************************************************************************/

/**
 * @file
 * Command-line options API header file.
 *
 * @author Alex Tokar
 */

#ifndef TOOLKIT_CLIOPTIONS_H
#define TOOLKIT_CLIOPTIONS_H

#include "toolkit.h"

/**
 * Macro to simplify CLI option creation.
 *
 * Uses clioptions_create() to create the CLI and store it in 'cli'. Variable
 * to use for the handler function will be constructed from the name in the
 * form of 'clioptions_option_name' and the variable to use for the detailed
 * description from 'clioptions_option_name_desc'.
 *
 * @param[out] cli
 * Will contain the created CLI.
 * @param name
 * CLI option name; NOT a string.
 * @param desc_brief
 * Brief description about the CLI.
 */
#define CLIOPTIONS_CREATE(cli, name, desc_brief)                            \
do {                                                                        \
    cli = clioptions_create(STRINGIFY(name),                                \
                            CONCAT(clioptions_option_, name));              \
    clioptions_set_description(cli,                                         \
                               desc_brief,                                  \
                               CONCAT(CONCAT(clioptions_option_, name),     \
                                      _desc));                              \
} while (0)

/**
 * Like CLIOPTIONS_CREATE(), but will enable passing a required argument using
 * clioptions_enable_argument().
 *
 * @param[out] cli
 * Will contain the created CLI.
 * @param name
 * CLI option name; NOT a string.
 * @param desc_brief
 * Brief description about the CLI.
 */
#define CLIOPTIONS_CREATE_ARGUMENT(cli, name, desc_brief)                   \
do {                                                                        \
    cli = clioptions_create(STRINGIFY(name),                                \
                            CONCAT(clioptions_option_, name));              \
    clioptions_set_description(cli,                                         \
                               desc_brief,                                  \
                               CONCAT(CONCAT(clioptions_option_, name),     \
                                      _desc));                              \
    clioptions_enable_argument(cli);                                        \
} while (0)

/**
 * Command line option handler function.
 *
 * @param arg
 * Argument, if any.
 * @param errmsg
 * On failure, should contain an error message explaining the error. Will be
 * freed.
 * @return
 * True on success, false on failure.
 */
typedef bool (*clioptions_handler_func)(const char *arg,
                                        char      **errmsg);

/*
 * Opaque typedef for a single CLI option structure.
 */
typedef struct clioption clioption_t;

/* Prototypes */

TOOLKIT_FUNCS_DECLARE(clioptions);

/**
 * Creates a new CLI option.
 *
 * @param name
 * Name of the option. Must not be destroyed.
 * @param handler_func
 * The handler function for the option. Can be NULL.
 * @return
 * Created CLI option.
 */
extern clioption_t *
clioptions_create (const char             *name,
                   clioptions_handler_func handler_func);

/**
 * Get the value of the specified CLI option.
 *
 * @param name
 * CLI option name.
 * @return
 * Value of the option.
 */
extern const char *
clioptions_get(const char *name);

/**
 * Sets short name for the specified CLI.
 *
 * @param cli
 * CLI.
 * @param short_name
 * Short name to set. Must not be destroyed.
 */
extern void
clioptions_set_short_name(clioption_t *cli,
                          const char  *short_name);

/**
 * Sets description text for the specified CLI.
 *
 * This makes the CLI visible in the list of commands when using --help.
 *
 * @param cli
 * CLI.
 * @param desc_brief
 * Brief description text. Must not be destroyed.
 * @param desc
 * Description text. Must not be destroyed.
 */
extern void
clioptions_set_description(clioption_t *cli,
                           const char  *desc_brief,
                           const char  *desc);

/**
 * Marks the CLI as requiring an argument.
 *
 * @param cli
 * CLI.
 */
extern void
clioptions_enable_argument(clioption_t *cli);

/**
 * Marks the CLI as changeable at runtime.
 *
 * @param cli
 * CLI.
 */
extern void
clioptions_enable_changeable(clioption_t *cli);

/**
 * Parse CLI options from argv array.
 *
 * @param argc
 * Number of elements in argv.
 * @param argv
 * Variable length array of character pointers with the option/argument
 * combinations.
 */
extern void
clioptions_parse(int argc, char *argv[]);

/**
 * Load CLI options from a config file.
 *
 * @param path
 * File to load from.
 * @param category
 * Category of options to read; NULL for all.
 * @return
 * True on success, false on failure.
 */
extern bool
clioptions_load(const char *path, const char *category);

/**
 * Load a string as a CLI option, eg, "port = 13327".
 *
 * @param str
 * String to load.
 * @param errmsg
 * May contain an error message on failure; must be freed.
 * @return
 * True on success, false on failure.
 */
extern bool
clioptions_load_str(const char *str, char **errmsg);

#endif
