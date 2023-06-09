#include "types.h"

/**
 *	@brief This struct contains the different property values of different blocks.
 */
const block_properties_t block_properties[] = {
    [BLOCK_TYPE_GRASS] = { .transparency = 0, .material = MATERIAL_TYPE_DIRT, "Grass" },
    [BLOCK_TYPE_DIRT] = { .transparency = 0, .material = MATERIAL_TYPE_DIRT, "Dirt" },
};