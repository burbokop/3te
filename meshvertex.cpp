#include "meshvertex.h"

#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

using namespace burbokop::utilities3d;

Vector3d *MeshVertex::getPosition() const
{
    return position;
}

void MeshVertex::setPosition(Vector3d *value)
{
    position = value;
}

Vector3d *MeshVertex::getNormal() const
{
    return normal;
}

void MeshVertex::setNormal(Vector3d *value)
{
    normal = value;
}

burbokop::Vector *MeshVertex::getUv() const
{
    return uv;
}

void MeshVertex::setUv(Vector *value)
{
    uv = value;
}

MeshVertex::MeshVertex()
{
    this->position = new Vector3d();
    this->normal = new Vector3d();
    this->uv = new Vector();
}

MeshVertex::MeshVertex(Vector3d *position, Vector3d *normal, Vector *uv)
{
    this->position = position;
    this->normal = normal;
    this->uv = uv;
}
