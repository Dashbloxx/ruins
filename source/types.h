#pragma once

/**
 *	@brief This enum defines different types of entities.
 */
typedef enum {
    ENTITY_TYPE_PLAYER
} entity_type_t;

/**
 *	@brief This enum defines different types of particles.
 */
typedef enum {
    PARTICLE_TYPE_DUST
} particle_type_t;

/**
 *	@brief This enum defines different types of items.
 */
typedef enum {
    ITEM_TYPE_GRASS_BLOCK,
    ITEM_TYPE_DIRT_BLOCK
} item_type_t;

/**
 *	@brief This struct stores a three-dimensional value using 64-bit decimal numbers.
 *
 *	It is recommended to use this for entity or particle positions. If you want to use a three-dimensional value
 *	for something like a block or a chunk, we recommend you to use `integer_vector3_t`.
 */
typedef struct {
	double x;
	double y;
	double z;
} precise_vector3_t;

/**
 *	@brief This struct stores a three-dimensional value using 64-bit integers.
 *
 *	It is recommended to use this for block positions or chunk positions. If you want to use a three-dimensional value
 *	for something like an entity, we recommend you to use `precise_vector3_t`.
 */
typedef struct {
	long long x;
	long long y;
	long long z;
} integer_vector3_t;

/**
 *	@brief This struct stores data that represents an entity.
 *
 *	It is recommended to use this for players, mobs, particles, items, etc.
 */
typedef struct {
	precise_vector3_t position;
	precise_vector3_t hitbox_size;
	unsigned int entity_type;
} entity_t;

/**
 *	@brief This enum defines different types blocks.
 */
typedef enum {
    BLOCK_TYPE_GRASS,
    BLOCK_TYPE_DIRT
} block_type_t;

/**
 *	@brief This struct stores data that represents chunks.
 *
 *	Each chunk is 16 * 16 * 16 blocks by size.
 */
typedef struct {
	integer_vector3_t position;
	block_type_t blocks[16][16][16];
} chunk_t;

/**
 *	@brief This enum defines different materials for items & blocks.
 */
typedef enum {
	MATERIAL_TYPE_WOOD,
	MATERIAL_TYPE_STONE,
	MATERIAL_TYPE_METAL,
	MATERIAL_TYPE_DIRT
} material_t;

/**
 *	@brief This struct contains the different properties of different blocks.
 */
typedef struct {
	unsigned int transparency;
    material_t material;
	char block_name[128];
} block_properties_t;

extern const block_properties_t block_properties[];