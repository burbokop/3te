#include "model.h"

#include <GL/glu.h>
#include <SDL2/SDL_image.h>


using namespace burbokop::utilities3d;


Mesh *Model::getMesh()
{
    return mesh;
}

GLuint *Model::getTexture()
{
    return texture;
}

Model::Model()
{
    this->mesh = NULL;
    this->texture = NULL;
}

burbokop::utilities3d::Model::Model(burbokop::utilities3d::Mesh *mesh, GLuint *texture)
{
    this->mesh = mesh;
    this->texture = texture;
}

GLuint *burbokop::utilities3d::Model::loadTexture(const char *path)
{
    SDL_Surface *tmp = IMG_Load(path);
    if(tmp != NULL) {
        GLuint *result = new GLuint;
        glGenTextures(1, result); //creates 1 texture;
        glBindTexture(GL_TEXTURE_2D, *result);
        //texture parameters
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tmp->w, tmp->h, GL_RGBA, GL_UNSIGNED_BYTE, tmp->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //free pointer
        SDL_FreeSurface(tmp);
        return result;
    }
    return NULL;
}

burbokop::utilities3d::Model *burbokop::utilities3d::Model::loadModel(const char *modelPath, const char *texturePath)
{
    return new Model(Mesh::loadMesh(modelPath), Model::loadTexture(texturePath));
}

void burbokop::utilities3d::Model::render()
{
    if(this->texture != NULL) glBindTexture(GL_TEXTURE_2D, *this->texture);
    if(this->mesh != NULL) this->mesh->render();
}
