#ifndef VECTOR3D_H
#define VECTOR3D_H

#define RELATIVISTIC_ADDITION_CONSTANT 0.7

namespace burbokop {
namespace utilities3d {

class Vector3d
{
private:
    double x;
    double y;
    double z;
public:
    Vector3d();
    Vector3d(double x, double y, double z);
    Vector3d(long x, long y, long z);
    Vector3d(int x, int y, int z);
    static Vector3d *createByAngle(double module, double angle);
    static Vector3d *createByArray(bool *array, double angle);

    Vector3d *add(Vector3d *term);
    Vector3d *subtract(Vector3d *subtrahend);
    Vector3d *multiply(double multiplier);
    Vector3d *multiply(Vector3d *multiplier);

    double scalarProduct(Vector3d *multiplier);

    Vector3d *matrixProduct(double *matrix);

    Vector3d *normalized();
    double map(Vector3d *destination, double value);
    Vector3d *relativisticAddition(Vector3d *term, double c);

    double angle();
    double module();

    void setX(double value);
    void setY(double value);
    void setZ(double value);

    int getIntX();
    int getIntY();
    int getIntZ();
    long getLongX();
    long getLongY();
    long getLongZ();
    double getDoubleX();
    double getDoubleY();
    double getDoubleZ();
};
}
}

#endif // VECTOR3D_H
