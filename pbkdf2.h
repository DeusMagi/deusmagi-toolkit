/**
 * @file
 * PBKDF2 API header file.
 *
 * @author Alex Tokar
 */

#ifndef TOOLKIT_PBKDF2_H
#define TOOLKIT_PBKDF2_H

#include "toolkit.h"

/* Prototypes */

TOOLKIT_FUNCS_DECLARE(pbkdf2);

extern void
PKCS5_PBKDF2_HMAC_SHA2(const unsigned char *password,
                       size_t               plen,
                       unsigned char       *salt,
                       size_t               slen,
                       const unsigned long  iteration_count,
                       const unsigned long  key_length,
                       unsigned char       *output);

#endif
