#pragma once

#include "MathFunction.hpp"

class ExponentFunction : public MathFunction
{
private:
    float a;
    float b;
public:
    ExponentFunction(float a = 1, float b = 1);
    ~ExponentFunction();

    void setA(float b);
    void setB(float a);

    double getY(double x);
    MathFunction* clone();
};


