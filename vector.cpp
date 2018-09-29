#include "vector.h"

#include <math.h>

#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

using namespace burbokop;

Vector::Vector() {
    this->x = 0;
    this->y = 0;
}

Vector::Vector(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector::Vector(long x, long y) {
    this->x = (double)x;
    this->y = (double)y;
}

Vector::Vector(int x, int y) {
    this->x = (double)x;
    this->y = (double)y;
}

Vector *Vector::createByAngle(double module, double angle)
{
    return new Vector(module * std::cos(angle), module * std::sin(angle));
}

Vector *Vector::add(Vector *term) {
    Vector *result = new Vector(0, 0);
    result->x = this->x + term->x;
    result->y = this->y + term->y;
    return result;
}

Vector *Vector::subtract(Vector *subtrahend) {
    Vector *result = new Vector(0, 0);
    result->x = this->x - subtrahend->x;
    result->y = this->y - subtrahend->y;
    return result;
}

Vector *Vector::multiply(double multiplier) {
    Vector *result = new Vector(0, 0);
    result->x = this->x * multiplier;
    result->y = this->y * multiplier;
    return result;
}

double Vector::scalarProduct(Vector *multiplier) {
    return this->x * multiplier->x + this->y * multiplier->y;
}

Vector *Vector::normalized() {
    Vector *result = new Vector(0, 0);
    result->x = this->x / this->module();
    result->y = this->y / this->module();
    return result;
}

double Vector::map(Vector *destination, double value) {
    double result = 0;
    double kd = destination->y - destination->x;
    double kt = this->y - this->x;

    if(kt == 0) result = value * kd;
    else result = value * kd / kt;

    result += destination->x;

    return result;
}

Vector *Vector::relativisticAddition(Vector *term, double c) {
    Vector *result = this;
    c = c * RELATIVISTIC_ADDITION_CONSTANT;
    if(term->module() != 0)
    {
        Vector *d = this->add(term);

        double k = std::sqrt(1 + this->module() * term->module() / (c * c));
        double u = d->module() / k;

        result->x = u * d->x / d->module();
        result->y = u * d->y / d->module();
    }
    return result;
}

double Vector::angle() {
    double cos = this->normalized()->scalarProduct(new Vector(1, 0));
    if(this->y >= 0) return std::acos(cos);
    else return -std::acos(cos);
}

double Vector::module() {
    return std::sqrt(this->x * this->x + this->y * this->y);
}

double Vector::tg()
{
    if(this->y != 0) return -(this->x / this->y);
    return 0.0;
}

char Vector::quarter(char offset)
{
    if(this->y >= 0) {
        if(this->x >= 0) {
            return (0 + offset) % 4;
        }
        else {
            return (1 + offset) % 4;
        }
    }
    else {
        if(this->x >= 0) {
            return (3 + offset) % 4;
        }
        else {
            return (2 + offset) % 4;
        }
    }
}

void Vector::setX(double value)
{
    this->x = value;
}

void Vector::setY(double value)
{
    this->y = value;
}

int Vector::getIntX() {
    return (int)this->x;
}

int Vector::getIntY() {
    return (int)this->y;
}

long Vector::getLongX() {
    return (long)this->x;
}

long Vector::getLongY() {
    return (long)this->y;
}

double Vector::getDoubleX() {
    return this->x;
}

double Vector::getDoubleY() {
    return this->y;
}
