/**
 * @file
 * Toolkit math API header file.
 *
 * @author Alex Tokar
 */

#ifndef TOOLKIT_MATH_H
#define	TOOLKIT_MATH_H

#include "toolkit.h"

/* Prototypes */

TOOLKIT_FUNCS_DECLARE(math);

unsigned long
isqrt (unsigned long n);
int
rndm(int min, int max);
int
rndm_chance(uint32_t n);
uint64_t
rndm_u64(void);
void *
sort_linked_list(void          *p,
                 unsigned      index,
                 int          (*compare)(void *, void *, void *),
                 void          *pointer,
                 unsigned long *pcount,
                 void          *end_marker);
size_t
nearest_pow_two_exp(size_t n);
bool
math_point_in_ellipse(int    x,
                      int    y,
                      double cx,
                      double cy,
                      int    dx,
                      int    dy,
                      double angle);
bool
math_point_edge_ellipse(int    x,
                        int    y,
                        double cx,
                        double cy,
                        int    dx,
                        int    dy,
                        double angle,
                        int   *deg);
bool
math_base64_decode(const char     *str,
                   unsigned char **buf,
                   size_t         *buf_len);

#endif
