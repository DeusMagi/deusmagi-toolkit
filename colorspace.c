/**
 * @file
 * Colorspace related API.
 *
 * @author Alex Tokar
 */

#include "colorspace.h"

TOOLKIT_API();

TOOLKIT_INIT_FUNC(colorspace)
{
}
TOOLKIT_INIT_FUNC_FINISH

TOOLKIT_DEINIT_FUNC(colorspace)
{
}
TOOLKIT_DEINIT_FUNC_FINISH

/**
 * @author LIBGIMP (GNU LGPL 3.0)
 */
double
colorspace_rgb_max (const double rgb[3])
{
    TOOLKIT_PROTECT();

    if (rgb[0] > rgb[1]) {
        return (rgb[0] > rgb[2]) ? rgb[0] : rgb[2];
    } else {
        return (rgb[1] > rgb[2]) ? rgb[1] : rgb[2];
    }
}

/**
 * @author LIBGIMP (GNU LGPL 3.0)
 */
double
colorspace_rgb_min (const double rgb[3])
{
    TOOLKIT_PROTECT();

    if (rgb[0] < rgb[1]) {
        return (rgb[0] < rgb[2]) ? rgb[0] : rgb[2];
    } else {
        return (rgb[1] < rgb[2]) ? rgb[1] : rgb[2];
    }
}

/**
 * @author LIBGIMP (GNU LGPL 3.0)
 */
void
colorspace_rgb2hsv (const double rgb[3], double hsv[3])
{
    double max, min, delta;

    TOOLKIT_PROTECT();

    max = colorspace_rgb_max(rgb);
    min = colorspace_rgb_min(rgb);

    hsv[2] = max;
    delta = max - min;

    if (delta > 0.0001) {
        hsv[1] = delta / max;

        if (DBL_EQUAL(rgb[0], max)) {
            hsv[0] = (rgb[1] - rgb[2]) / delta;

            if (hsv[0] < 0.0) {
                hsv[0] += 6.0;
            }
        } else if (DBL_EQUAL(rgb[1], max)) {
            hsv[0] = 2.0 + (rgb[2] - rgb[0]) / delta;
        } else if (DBL_EQUAL(rgb[2], max)) {
            hsv[0] = 4.0 + (rgb[0] - rgb[1]) / delta;
        }

        hsv[0] /= 6.0;
    } else {
        hsv[0] = hsv[1] = 0.0;
    }
}

/**
 * @author LIBGIMP (GNU LGPL 3.0)
 */
void
colorspace_hsv2rgb (const double hsv[3], double rgb[3])
{
    int i;
    double f, w, q, t;
    double hue;

    TOOLKIT_PROTECT();

    if (DBL_EQUAL(hsv[1], 0.0)) {
        rgb[0] = hsv[2];
        rgb[1] = hsv[2];
        rgb[2] = hsv[2];
    } else {
        hue = hsv[0];

        if (DBL_EQUAL(hue, 1.0)) {
            hue = 0.0;
        }

        hue *= 6.0;

        i = (int) hue;
        f = hue - i;
        w = hsv[2] * (1.0 - hsv[1]);
        q = hsv[2] * (1.0 - (hsv[1] * f));
        t = hsv[2] * (1.0 - (hsv[1] * (1.0 - f)));

        switch (i) {
        case 0:
            rgb[0] = hsv[2];
            rgb[1] = t;
            rgb[2] = w;
            break;

        case 1:
            rgb[0] = q;
            rgb[1] = hsv[2];
            rgb[2] = w;
            break;

        case 2:
            rgb[0] = w;
            rgb[1] = hsv[2];
            rgb[2] = t;
            break;

        case 3:
            rgb[0] = w;
            rgb[1] = q;
            rgb[2] = hsv[2];
            break;

        case 4:
            rgb[0] = t;
            rgb[1] = w;
            rgb[2] = hsv[2];
            break;

        case 5:
            rgb[0] = hsv[2];
            rgb[1] = w;
            rgb[2] = q;
            break;
        }
    }
}
