#ifndef MESH_H
#define MESH_H

#include "meshvertex.h"

#include <vector>

#define TTE_MESH_OPTION_USE_NORMALS 1
#define TTE_MESH_OPTION_USE_TEXTURE 2
#define TTE_MESH_OPTION_VISUALIZE_NORMALS 3
#define TTE_MESH_OPTION_VISUALIZE_VERTICES 4
#define TTE_MESH_OPTION_RESET_COLOR 5
#define TTE_MESH_OPTION_STRUCTURE 6

namespace burbokop {
namespace utilities3d {

class Mesh
{
private:
    std::vector <MeshVertex*> *vertices;

    bool useNormals;
    bool useTexture;
    bool visualizeNormals;
    bool visualizeVertices;
    bool resetColor;
    char structure;

public:
    Mesh();
    static Mesh *loadMesh(const char *path);
    void setParameter(char parameter, char value);
    void render();
    void print();
};
}
}
#endif // MESH_H
