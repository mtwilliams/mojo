#ifndef MOJO_DATA_MODEL_H
#define MOJO_DATA_MODEL_H

#include <Mojo/Core.h>

typedef enum MJM_FLAGS {
    /* everything following the header is zlib compressed: */
    MJM_COMPRESSED = (1 << 0),

    /* the model was compiled to target left-handed coordinate systems: */
    MJM_LEFT_HANDED = (1 << 1),

    /* the model was compiled to target the current endianess: */
    MJM_TARGETED_ENDIANESS = (1 << 2),

    /* reserved for the user: */
    MJM_USER_FLAG0 = (1 << 24),
    MJM_USER_FLAG1 = (1 << 25),
    MJM_USER_FLAG2 = (1 << 26),
    MJM_USER_FLAG3 = (1 << 27),
    MJM_USER_FLAG4 = (1 << 28),
    MJM_USER_FLAG5 = (1 << 29),
    MJM_USER_FLAG6 = (1 << 30),
    MJM_USER_FLAG7 = (1 << 31),
} MJM_FLAGS;

typedef enum MJM_BLOCK_TYPES {
    /* see mjmBlock_Meshes: */
    MJM_BLK_MESHES = 0x01,

    /* see mjmBlock_Materials: */
    MJM_BLK_MATERIALS = 0x02,
} MJM_BLOCK_TYPES;

typedef struct mjmHeader {
    /* magic value used to determine if a file is a MJM: */
    uint8_t magic[3];
    
    /* the version of the model format: */
    uint8_t version;

    /* the uncompressed length of the model: */
    uint32_t length;

    /* see MJM_FLAGS: */
    uint32_t flags;
} mjmHeader;

typedef struct mjmBlockDesc {
    /* see MJM_BLOCK_TYPES: */
    uint8_t type;

    /* the offset from the start of the file to the start of the block: */
    uint32_t offset;

    /* the uncompressed length of the block: */
    uint32_t length;

    /* the compressed length of the block (for skipping?): */
    /* uint32_t c_length; */
} mjmBlockDesc;

typedef enum MJM_VERTEX_FORMAT {
    /* has positions (float3): */
    MJM_VF_POSITIONS = (1 << 0),

    /* has normals (float3): */
    MJM_VF_NORMALS = (1 << 1),

    /* has colors (ubyte4): */
    MJM_VF_COLORS = (1 << 2),

    /* has texture coords (float2): */
    MJM_VF_TEX_COORDS = (1 << 3),

    /* has tangents and bitangents (float3, float3): */
    MJM_VF_TANS_AND_BTANS = (1 << 4),
} MJM_VERTEX_FORMAT;

typedef struct mjmBone {
    /* shut up msvc */
    float weights[4];
} mjmBone;

typedef struct mjmMesh {
    /* a null terminated UTF-8 string: */
    const char* name;

    /* the bones associated with this mesh, see mjmBone:
       Note: a value of zero indicates there are no bones associated with this mesh. */
    uint32_t num_bones;

    /* the bones [0, num_bones - 1], see mjmBone: */
    mjmBone* bones;

    /* see MJM_VERTEX_FORMAT:
       Note: this is a collection of flags, not an enum! */
    uint32_t vert_format;

    /* the data is stored by flag order (skipping non-set flags):
       for example, MJM_VF_POSITIONS | MJM_VF_COLORS | MJM_VF_TEX_COORDS would be:
         { float3 pos; ubyte4 color; float2 uv/st; } */
    uint8_t* vertices;
} mjmMesh;

typedef struct mjmBlock_Meshes {
    /* the number of meshes in this block: */
    uint8_t num_meshes;

    /* the meshes [0, num_meshes - 1], see mjmMesh: */
    mjmMesh meshes[1];
} mjmBlock_Meshes;

typedef struct mjmBlock_Materials {
    /* the number of materials in this block: */
    uint8_t num_materials;
} mjmBlock_Materials;

typedef struct mjmModel mjmModel;

extern mjmModel* mjmLoadFromFile( const char* path );
extern mjmModel* mjmLoadFromMemory( const void* memory );
extern void mjmDestroy( mjmModel* model );

extern const mjmMesh* mjmGetMeshByName( const mjmModel* model, const char* name );

#endif /* MOJO_DATA_MODEL_H */