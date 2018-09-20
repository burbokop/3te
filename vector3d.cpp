#include "vector3d.h"

#include <math.h>

using namespace burbokop::utilities3d;

Vector3d::Vector3d() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3d::Vector3d(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3d::Vector3d(long x, long y, long z) {
    this->x = (double)x;
    this->y = (double)y;
    this->z = (double)z;
}

Vector3d::Vector3d(int x, int y, int z) {
    this->x = (double)x;
    this->y = (double)y;
    this->z = (double)z;
}

Vector3d *Vector3d::createByAngle(double module, double angle)
{
    return new Vector3d(module * std::cos(angle), module * std::sin(angle), 0.0);
}

Vector3d *Vector3d::createByArray(bool *array, double angle)
{
    const float pi = 3.14159;

    Vector3d *result = new Vector3d();
    if(array[3]) {
        result->x += std::sin(angle);
        result->y += -std::cos(angle);
    }
    else if(array[2]) {
        result->x += std::cos(angle + pi / 2);
        result->y += std::sin(angle + pi / 2);
    }

    if(array[0]) {
        result->x += std::cos(angle);
        result->y += std::sin(angle);
    }
    else if(array[1]) {
        result->x += std::cos(angle + pi);
        result->y += std::sin(angle + pi);
    }

    if(array[4]) {
        result->z += 1;
    }
    else if(array[5]) {
        result->z += -1;
    }
    result = result->normalized();
    return result;
}

Vector3d *Vector3d::add(Vector3d *term) {
    Vector3d *result = new Vector3d();
    result->x = this->x + term->x;
    result->y = this->y + term->y;
    result->z = this->z + term->z;
    return result;
}

Vector3d *Vector3d::subtract(Vector3d *subtrahend) {
    Vector3d *result = new Vector3d();
    result->x = this->x - subtrahend->x;
    result->y = this->y - subtrahend->y;
    result->z = this->z - subtrahend->z;
    return result;
}

Vector3d *Vector3d::multiply(double multiplier) {
    Vector3d *result = new Vector3d();
    result->x = this->x * multiplier;
    result->y = this->y * multiplier;
    result->z = this->z * multiplier;
    return result;
}

Vector3d *Vector3d::multiply(Vector3d *multiplier)
{
    return new Vector3d(this->y * multiplier->z - this->z * multiplier->y, this->z * multiplier->x - this->x * multiplier->z, this->x * multiplier->y - this->y * multiplier->x);
}

double Vector3d::scalarProduct(Vector3d *multiplier) {
    return this->x * multiplier->x + this->y * multiplier->y + this->z * multiplier->z;
}

Vector3d *Vector3d::matrixProduct(double *matrix)
{
    return 0;
}

Vector3d *Vector3d::normalized() {
    Vector3d *result = new Vector3d();
    double module = this->module();
    if(module != 0) {
        result->x = this->x / module;
        result->y = this->y / module;
        result->z = this->z / module;
    }
    else {
        result->x = 0;
        result->y = 0;
        result->z = 0;
    }
    return result;
}

double Vector3d::map(Vector3d *destination, double value) {
    double result = 0;
    double kd = destination->y - destination->x;
    double kt = this->y - this->x;

    if(kt == 0) result = value * kd;
    else result = value * kd / kt;

    result += destination->x;

    return result;
}

Vector3d *Vector3d::relativisticAddition(Vector3d *term, double c) {
    Vector3d *result = this;
    c = c * RELATIVISTIC_ADDITION_CONSTANT;
    if(term->module() != 0)
    {
        Vector3d *d = this->add(term);

        double k = std::sqrt(1 + this->module() * term->module() / (c * c));
        double u = d->module() / k;

        result->x = u * d->x / d->module();
        result->y = u * d->y / d->module();
        result->z = u * d->z / d->module();
    }
    return result;
}

double Vector3d::angle() {
    double cos = this->normalized()->scalarProduct(new Vector3d(0, 1, 0));
    if(this->y >= 0) return std::acos(cos);
    else return -std::acos(cos);
}

double Vector3d::module() {
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

void Vector3d::setX(double value)
{
    this->x = value;
}

void Vector3d::setY(double value)
{
    this->y = value;
}

void Vector3d::setZ(double value)
{
    this->z = value;
}

int Vector3d::getIntX() {
    return (int)this->x;
}

int Vector3d::getIntY() {
    return (int)this->y;
}

int Vector3d::getIntZ() {
    return (int)this->z;
}

long Vector3d::getLongX() {
    return (long)this->x;
}

long Vector3d::getLongY() {
    return (long)this->y;
}

long Vector3d::getLongZ() {
    return (long)this->z;
}

double Vector3d::getDoubleX() {
    return this->x;
}

double Vector3d::getDoubleY() {
    return this->y;
}

double Vector3d::getDoubleZ() {
    return this->z;
}
