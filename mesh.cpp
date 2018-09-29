#include "mesh.h"

#include <iostream>
#include <string.h>
#include <GL/glu.h>

#include "debug.h"

#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

using namespace burbokop::utilities3d;

Mesh::Mesh()
{
    this->vertices = new std::vector<MeshVertex*>();

    this->useNormals = true;
    this->useTexture = true;
    this->visualizeNormals = false;
    this->visualizeVertices = true;
    this->resetColor = true;
    this->structure = GL_TRIANGLES;
}

Mesh *Mesh::loadMesh(const char *path)
{
    Debug::log("Loading mesh: " + std::string(path));
    std::vector <Vector3d*> *vertices = new std::vector<Vector3d*>();
    std::vector <Vector*> *uv_map = new std::vector<Vector*>();
    std::vector <Vector3d*> *normals = new std::vector<Vector3d*>();
    std::vector <Vector3d*> *indices = new std::vector<Vector3d*>();


    Debug::log("Open file: " + std::string(path));
    FILE *file = fopen(path, "r");
    if(file == NULL) {
        return NULL;
    }

    Debug::log("Parsing file: " + std::string(path));
    while(true) {
        std::string line;
        if (fscanf(file, "%s", line.c_str()) == EOF) break;
        else if (strcmp(line.c_str(), "v" ) == 0) {
            float x = 0;
            float y = 0;
            float z = 0;
            fscanf(file, "%f %f %f\n", &x, &y, &z);
            vertices->push_back(new Vector3d(x, y, z));
        }
        else if (strcmp(line.c_str(), "vt") == 0){
            float x = 0;
            float y = 0;
            fscanf(file, "%f %f\n", &x, &y);
            uv_map->push_back(new Vector(x, y));
        }

        else if (strcmp(line.c_str(), "vn") == 0){
            float x = 0;
            float y = 0;
            float z = 0;
            fscanf(file, "%f %f %f\n", &x, &y, &z);
            normals->push_back(new Vector3d(x, y, z));
        }
        else if (strcmp(line.c_str(), "f" ) == 0){
            int iv1x = 0;
            int iv1y = 0;
            int iv1z = 0;
            int iv2x = 0;
            int iv2y = 0;
            int iv2z = 0;
            int iv3x = 0;
            int iv3y = 0;
            int iv3z = 0;
            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &iv1x, &iv1y, &iv1z, &iv2x, &iv2y, &iv2z, &iv3x, &iv3y, &iv3z);

            indices->push_back(new Vector3d(iv1x, iv1y, iv1z));
            indices->push_back(new Vector3d(iv2x, iv2y, iv2z));
            indices->push_back(new Vector3d(iv3x, iv3y, iv3z));
        }
    }


    Mesh *result = new Mesh();

    Debug::log("Creating mesh.");
    unsigned int exceptionAppearance = 0;
    for(unsigned int i = 0; i < indices->size(); i++) {

        Vector3d *in_tmp = indices->at(i);

        Vector3d *ik_position = new Vector3d();
        Vector *ik_uv_tp = new Vector();
        Vector3d *ik_normal = new Vector3d();

        try {
            ik_position = vertices->at(in_tmp->getIntX() - 1);
            ik_uv_tp = uv_map->at(in_tmp->getIntY() - 1);
            ik_normal = normals->at(in_tmp->getIntZ() - 1);
        } catch(const std::exception e) {
            exceptionAppearance++;
            std::cout << "Exception: " << e.what() << " in indexing (iteration: " + std::to_string(i) + ", appearance: " + std::to_string(exceptionAppearance) + ")\n";
        }


        result->vertices->push_back(new MeshVertex(ik_position, ik_normal, ik_uv_tp));
    }
    Debug::log("Mesh loading complete.");
    return result;
}

void Mesh::setParameter(char parameter, char value)
{
    if(parameter == TTE_MESH_OPTION_USE_NORMALS) {
        this->useNormals = value;
    }
    else if(parameter == TTE_MESH_OPTION_USE_TEXTURE) {
        this->useTexture = value;
    }
    else if(parameter == TTE_MESH_OPTION_VISUALIZE_NORMALS) {
        this->visualizeNormals = value;
    }
    else if(parameter == TTE_MESH_OPTION_VISUALIZE_VERTICES) {
        this->visualizeVertices = value;
    }
    else if(parameter == TTE_MESH_OPTION_RESET_COLOR) {
        this->resetColor = value;
    }
    else if(parameter == TTE_MESH_OPTION_STRUCTURE) {
        this->structure = value;
    }
}

void Mesh::render()
{
    if(this->visualizeVertices) {
        if(this->useTexture) glEnable(GL_TEXTURE_2D);
        glBegin(this->structure);
        if(this->resetColor) glColor3f(1.0f, 1.0f, 1.0f);
        for (unsigned int i = 0; i < this->vertices->size(); ++i) {
            MeshVertex *currentVertex = this->vertices->at(i);
            if(this->useNormals) glNormal3d(currentVertex->getNormal()->getDoubleX(), currentVertex->getNormal()->getDoubleY(), currentVertex->getNormal()->getDoubleZ());
            if(this->useTexture) glTexCoord2d(currentVertex->getUv()->getDoubleX(), currentVertex->getUv()->getDoubleY());
            glVertex3d(currentVertex->getPosition()->getDoubleX(), currentVertex->getPosition()->getDoubleY(), currentVertex->getPosition()->getDoubleZ());
        }
        glEnd();
    }

    if(this->visualizeNormals) {
        glDisable(GL_TEXTURE_2D);
        glBegin(GL_LINES);
        for (unsigned int i = 0; i < this->vertices->size(); ++i) {
            MeshVertex *currentVertex = this->vertices->at(i);
            glColor3f(0.0f, 0.1f, 0.1f);
            glVertex3d(currentVertex->getPosition()->getDoubleX(), currentVertex->getPosition()->getDoubleY(), currentVertex->getPosition()->getDoubleZ());
            glColor3f(0.0f, 1.0f, 1.0f);
            glVertex3d(currentVertex->getPosition()->getDoubleX() + currentVertex->getNormal()->getDoubleX(), currentVertex->getPosition()->getDoubleY() + currentVertex->getNormal()->getDoubleY(), currentVertex->getPosition()->getDoubleZ() + currentVertex->getNormal()->getDoubleZ());
        }
        glEnd();
    }

    glFlush();
}

void Mesh::print()
{
    for (unsigned int i = 0; i < this->vertices->size(); ++i) {
        MeshVertex *currentVertex = this->vertices->at(i);
        std::cout << "vertex" << i << " c:" << currentVertex->getPosition()->getDoubleX()
            << currentVertex->getPosition()->getDoubleX() << " "
            << currentVertex->getPosition()->getDoubleY() << " "
            << currentVertex->getPosition()->getDoubleZ() << " t:"
            << currentVertex->getUv()->getDoubleX() << " "
            << currentVertex->getUv()->getDoubleY() << "\n";
    }
}
