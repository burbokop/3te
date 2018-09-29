#include "model.h"

#include <GL/glu.h>
#include <SDL2/SDL_image.h>

#include <debug.h>

#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

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
    Debug::log("Loading texture: " + std::string(path));
    SDL_Surface *tmp = IMG_Load(path);
    if(tmp != NULL) {
        Debug::log("Loading texture: part 1");
        GLuint *result = new GLuint;
        Debug::log("Loading texture: part 2");
        glGenTextures(1, result); //creates 1 texture;
        Debug::log("Loading texture: part 3");
        glBindTexture(GL_TEXTURE_2D, *result);
        //texture parameters
        Debug::log("Loading texture: part 4");
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tmp->w, tmp->h, GL_RGBA, GL_UNSIGNED_BYTE, tmp->pixels);
        Debug::log("Loading texture: part 5");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Debug::log("Loading texture: part 6");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        Debug::log("Loading texture: part 7");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        Debug::log("Loading texture: part 8");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //free pointer
        Debug::log("Loading texture: part 9");
        SDL_FreeSurface(tmp);
        Debug::log("Texture loading complete.");
        return result;
    }
    Debug::log("Texture loading error (fnf or unknown) file: " + std::string(path));
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
