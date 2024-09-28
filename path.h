/**
 * @file
 * Path API header file.
 *
 * @author Alex Tokar
 */

#ifndef TOOLKIT_PATH_H
#define TOOLKIT_PATH_H

#include "toolkit.h"

/**
 * Prototype for the ::path_fopen function signature.
 *
 * @param filename
 * Filename.
 * @param modes
 * Modes to open the file in.
 */
typedef FILE *(*path_fopen_t)(const char *filename, const char *modes);

/* Prototypes */

path_fopen_t path_fopen;

TOOLKIT_FUNCS_DECLARE(path);

char *
path_join(const char *path, const char *path2);
char *
path_dirname(const char *path);
char *
path_basename(const char *path);
char *
path_normalize(const char *path);
void
path_ensure_directories(const char *path);
int
path_copy_file(const char *src, FILE *dst, const char *mode);
int
path_exists(const char *path);
int
path_touch(const char *path);
size_t
path_size(const char *path);
char *
path_file_contents(const char *path);
int
path_rename(const char *old, const char *new);

#endif
