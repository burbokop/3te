#ifndef IVECTOR_H
#define IVECTOR_H


class IVector
{
public:
    virtual IVector *add(IVector *term) = 0;
    virtual IVector *subtract(IVector *subtrahend) = 0;
    virtual IVector *multiply(double multiplier) = 0;

    virtual double scalarProduct(IVector *multiplier) = 0;
    virtual IVector *normalized() = 0;
    virtual double map(IVector *destination, double value) = 0;
    virtual IVector *relativisticAddition(IVector *term, double c) = 0;

    virtual double angle() = 0;
    virtual double module() = 0;
    virtual double tg() = 0;
    virtual char quarter(char offset) = 0;
};

#endif // IVECTOR_H
