#pragma once

#include "MathFunction.hpp"

class LinesFunction : public MathFunction
{
private:
    float a;
    float b;
public:
    LinesFunction(float a = 1, float b = 0);
    ~LinesFunction();

    void setA(float a);
    void setB(float b);

    double getY(double x);
    MathFunction* clone();
};