/**
 * @file
 * Signals API header file.
 *
 * @author Alex Tokar
 */

#ifndef TOOLKIT_SIGNALS_H
#define TOOLKIT_SIGNALS_H

#include "toolkit.h"

/* Prototypes */

TOOLKIT_FUNCS_DECLARE(signals);

/**
 * Set the prefix to use for generated traceback files.
 *
 * @param prefix
 * Prefix to use
 */
extern void
signals_set_traceback_prefix(const char *prefix);

#endif
