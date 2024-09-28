/**
 * @file
 * File with common definitions/macros/calculations/algorithms for both the
 * server and the client.
 */

#ifndef TOOLKIT_COMMON_H
#define TOOLKIT_COMMON_H

/** Multiplier for spell points cost based on the attenuation. */
#define PATH_SP_MULT(op, spell) ((((op)->path_attuned & (spell)->path) ? 0.8 : 1) * (((op)->path_repelled & (spell)->path) ? 1.25 : 1))
/** Multiplier for spell damage based on the attenuation. */
#define PATH_DMG_MULT(op, spell) ((((op)->path_attuned & (spell)->path) ? 1.25 : 1) * (((op)->path_repelled & (spell)->path) ? 0.7 : 1))

#endif
