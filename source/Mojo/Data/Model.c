#include <Mojo/Data/Model.h>

struct mjmModel {
    uint32_t num_meshes;
    mjmMesh* meshes;
};

mjmModel* mjmLoadFromFile( const char* path )
{
    return NULL;
}

mjmModel* mjmLoadFromMemory( const void* memory )
{
    return NULL;
}

void mjmDestroy( mjmModel* model )
{
}

const mjmMesh* mjmGetMeshByName( const mjmModel* model, const char* name )
{
    uint32_t i;

    if( !model || !name ) return NULL;

    for( i = 0; i < model->num_meshes; ++i ) {
        if( strcmp(name, model->meshes[i].name) != 0 ) continue;
        return (const mjmMesh*)&model->meshes[i];
    }

    return NULL;
}

