/**
 * @file
 * Process API header file.
 */

#ifndef TOOLKIT_PROCESS_H
#define TOOLKIT_PROCESS_H

#include "toolkit.h"
#include "packet_dec.h"

typedef struct process process_t;

/**
 * Callback definition used for acquiring data read from a process.
 *
 * @param process
 * Process.
 * @param data
 * Data that was read.
 * @param len
 * Length of the data.
 */
typedef void (*process_data_callback_t)(process_t *process,
                                        uint8_t   *data,
                                        size_t     len);

/* Prototypes */

TOOLKIT_FUNCS_DECLARE(process);

process_t *
process_create(const char *executable);
void
process_free(process_t *process);
void
process_add_arg(process_t *process, const char *arg);
const char *
process_get_str(process_t *process);
void
process_set_restart(process_t *process, bool val);
void
process_set_data_out_cb(process_t *process, process_data_callback_t cb);
void
process_set_data_err_cb(process_t *process, process_data_callback_t cb);
bool
process_is_running(process_t *process);
void
process_send(process_t *process, packet_struct *packet);
bool
process_start(process_t *process);
void
process_stop(process_t *process);
void
process_check(process_t *process);
void
process_check_all(void);

#endif
