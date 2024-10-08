/**
 * @file
 * BinReloc - a library for creating relocatable executables
 * Written by: Hongli Lai <h.lai@chello.nl>
 * http://autopackage.org/
 *
 * This source code is public domain. You can relicense this code
 * under whatever license you want.
 *
 * See http://autopackage.org/docs/binreloc/ for
 * more information and how to use this.
 */

#ifndef TOOLKIT_BINRELOC_H
#define TOOLKIT_BINRELOC_H

#include "toolkit.h"

#ifndef WIN32
#define ENABLE_BINRELOC
#endif

/** These error codes can be returned by br_init(), br_init_lib(), gbr_init() or
 * gbr_init_lib(). */
typedef enum {
    /** Cannot allocate memory. */
    BR_INIT_ERROR_NOMEM,
    /** Unable to open /proc/self/maps; see errno for details. */
    BR_INIT_ERROR_OPEN_MAPS,
    /** Unable to read from /proc/self/maps; see errno for details. */
    BR_INIT_ERROR_READ_MAPS,
    /** The file format of /proc/self/maps is invalid; kernel bug? */
    BR_INIT_ERROR_INVALID_MAPS,
    /** BinReloc is disabled (the ENABLE_BINRELOC macro is not defined). */
    BR_INIT_ERROR_DISABLED
} BrInitError;

/* Prototypes */ 

TOOLKIT_FUNCS_DECLARE(binreloc);

/**
 * Finds the canonical filename of the current application.
 *
 * @param default_exe
 * A default filename which will be used as fallback.
 * @return
 * A string containing the application's canonical filename,
 * which must be freed when no longer necessary. If BinReloc is not
 * initialized, or if initialization failed, then a copy of default_exe
 * will be returned. If default_exe is NULL, then NULL will be returned.
 */
extern char *
binreloc_find_exe(const char *default_exe);

/**
 * Locate the directory in which the current application is installed.
 *
 * The prefix is generated by the following pseudo-code evaluation:
 * @code
 * dirname(exename)
 * @endcode
 *
 * @param default_dir
 * A default directory which will used as fallback.
 * @return
 * A string containing the directory, which must be freed when no
 * longer necessary. If BinReloc is not initialized, or if the
 * initialization failed, then a copy of default_dir will be returned. If
 * default_dir is NULL, then NULL will be returned.
 */
extern char *
binreloc_find_exe_dir(const char *default_dir);

/**
 * Locate the prefix in which the current application is installed.
 *
 * The prefix is generated by the following pseudo-code evaluation:
 * @code
 * dirname(dirname(exename))
 * @endcode
 *
 * @param default_prefix
 * A default prefix which will used as fallback.
 * @return
 * A string containing the prefix, which must be freed when no
 * longer necessary. If BinReloc is not initialized, or if the
 * initialization failed, then a copy of default_prefix will be returned.
 * If default_prefix is NULL, then NULL will be returned.
 */
extern char *
binreloc_find_prefix(const char *default_prefix);

/**
 * Locate the application's binary folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * @code
 * prefix + "/bin"
 * @endcode
 *
 * @param default_bin_dir
 * A default path which will used as fallback.
 * @return
 * A string containing the bin folder's path, which must be freed
 * when no longer necessary. If BinReloc is not initialized, or if the
 * initialization failed, then a copy of default_bin_dir will be
 * returned. If default_bin_dir is NULL, then NULL will be returned.
 */
extern char *
binreloc_find_bin_dir(const char *default_bin_dir);

/**
 * Locate the application's superuser binary folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * @code
 * prefix + "/sbin"
 * @endcode
 *
 * @param default_sbin_dir
 * A default path which will used as fallback.
 * @return
 * A string containing the sbin folder's path, which must be
 * freed when no longer necessary. If BinReloc is not initialized, or if
 * the initialization failed, then a copy of default_sbin_dir will be
 * returned. If default_bin_dir is NULL, then NULL will be returned.
 */
extern char *
binreloc_find_sbin_dir(const char *default_sbin_dir);

/**
 * Locate the application's data folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * @code
 * prefix + "/share"
 * @endcode
 *
 * @param default_data_dir
 * A default path which will used as fallback.
 * @return
 * A string containing the data folder's path, which must be
 * freed when no longer necessary. If BinReloc is not initialized, or if
 * the initialization failed, then a copy of default_data_dir will be
 * returned. If default_data_dir is NULL, then NULL will be returned.
 */
extern char *
binreloc_find_data_dir(const char *default_data_dir);

/**
 * Locate the application's localization folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * @code
 * prefix + "/share/locale"
 * @endcode
 *
 * @param default_locale_dir
 * A default path which will used as fallback.
 * @return
 * A string containing the localization folder's path, which must
 * be freed when no longer necessary. If BinReloc is not initialized, or
 * if the initialization failed, then a copy of default_locale_dir will
 * be returned. If default_locale_dir is NULL, then NULL will be
 * returned.
 */
extern char *
binreloc_find_locale_dir(const char *default_locale_dir);

/**
 * Locate the application's library folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * @code
 * prefix + "/lib"
 * @endcode
 *
 * @param default_lib_dir
 * A default path which will used as fallback.
 * @return
 * A string containing the library folder's path, which must be
 * freed when no longer necessary. If BinReloc is not initialized, or if
 * the initialization failed, then a copy of default_lib_dir will be
 * returned. If default_lib_dir is NULL, then NULL will be returned.
 */
extern char *
binreloc_find_lib_dir(const char *default_lib_dir);

/**
 * Locate the application's libexec folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * @code
 * prefix + "/libexec"
 * @endcode
 *
 * @param default_libexec_dir
 * A default path which will used as fallback.
 * @return
 * A string containing the libexec folder's path, which must be
 * freed when no longer necessary. If BinReloc is not initialized, or if
 * the initialization failed, then a copy of default_libexec_dir will be
 * returned. If default_libexec_dir is NULL, then NULL will be
 * returned.
 */
char *
binreloc_find_libexec_dir(const char *default_libexec_dir);

/**
 * Locate the application's configuration files folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * @code
 * prefix + "/etc"
 * @endcode
 *
 * @param default_etc_dir
 * A default path which will used as fallback.
 * @return
 * A string containing the etc folder's path, which must be freed
 * when no longer necessary. If BinReloc is not initialized, or if the
 * initialization failed, then a copy of default_etc_dir will be
 * returned. If default_etc_dir is NULL, then NULL will be returned.
 */
extern char *
binreloc_find_etc_dir(const char *default_etc_dir);

#endif
