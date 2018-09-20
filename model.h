#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"

#include <GL/gl.h>

namespace burbokop {
namespace utilities3d {

class Model
{
private:
    Mesh *mesh;
    GLuint *texture;
public:
    Model();
    Model(Mesh *mesh, GLuint *texture);
    static GLuint *loadTexture(const char *path);
    static Model *loadModel(const char *modelPath, const char *texturePath);
    void render();
    Mesh *getMesh();
    GLuint *getTexture();
};
}
}


#endif // MODEL_H
