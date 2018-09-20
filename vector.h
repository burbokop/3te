#ifndef VECTOR_H
#define VECTOR_H

#define RELATIVISTIC_ADDITION_CONSTANT 0.7

namespace burbokop {

class Vector
{
private:
    double x;
    double y;
public:
    Vector();
    Vector(double x, double y);
    Vector(long x, long y);
    Vector(int x, int y);
    static Vector *createByAngle(double module, double angle);

    Vector *add(Vector *term);
    Vector *subtract(Vector *subtrahend);
    Vector *multiply(double multiplier);

    double scalarProduct(Vector *multiplier);
    Vector *normalized();
    double map(Vector *destination, double value);
    Vector *relativisticAddition(Vector *term, double c);

    double angle();
    double module();
    double tg();
    char quarter(char offset);


    void setX(double value);
    void setY(double value);

    int getIntX();
    int getIntY();
    long getLongX();
    long getLongY();
    double getDoubleX();
    double getDoubleY();
};
}
#endif // VECTOR_H
