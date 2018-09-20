#ifndef MESHVERTEX_H
#define MESHVERTEX_H

#include "vector.h"
#include "vector3d.h"

namespace burbokop {
namespace utilities3d {

class MeshVertex
{
private:
    Vector3d *position;
    Vector3d *normal;
    Vector *uv;
public:
    MeshVertex();
    MeshVertex(Vector3d *position, Vector3d *normal, Vector *uv);

    Vector3d *getPosition() const;
    Vector3d *getNormal() const;
    Vector *getUv() const;
    void setPosition(Vector3d *value);
    void setNormal(Vector3d *value);
    void setUv(Vector *value);
};
}
}

#endif // MESHVERTEX_H
