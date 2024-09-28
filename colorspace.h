/**
 * @file
 * Colorspace API header file.
 *
 * @author Alex Tokar
 */

#ifndef TOOLKIT_COLORSPACE_H
#define TOOLKIT_COLORSPACE_H

#include "toolkit.h"

/* Prototypes */

TOOLKIT_FUNCS_DECLARE(colorspace);

/**
 * Return the biggest color value in the specified RGB array.
 *
 * @param rgb
 * RGB array.
 * @return
 * Biggest color value.
 */
extern double
colorspace_rgb_max(const double rgb[3]);

/**
 * Return the smallest color value in the specified RGB array.
 *
 * @param rgb
 * RGB array.
 * @return
 * Smallest color value.
 */
extern double
colorspace_rgb_min(const double rgb[3]);

/**
 * Converts RGB (red,green,blue) colorspace to HSV (hue,saturation,value).
 *
 * @param rgb
 * RGB array.
 * @param[out] hsv
 * HSV array.
 */
extern void
colorspace_rgb2hsv(const double rgb[3], double hsv[3]);

/**
 * Converts HSV (hue,saturation,value) colorspace to RGB (red,green,blue).
 *
 * @param hsv
 * HSV array.
 * @param[out] rgb
 * RGB array.
 */
extern void
colorspace_hsv2rgb(const double hsv[3], double rgb[3]);

#endif
