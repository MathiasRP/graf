#include "ExponentFunction.hpp"
#include <math.h>

ExponentFunction::ExponentFunction(float a, float b)
{
    this->a = a;
    this->b = b;
}

ExponentFunction::~ExponentFunction()
{
}

void ExponentFunction::setA(float b){
    this->b = b;
}

void ExponentFunction::setB(float a){
    this->a = a;
}

double ExponentFunction::getY(double x){
    return b * pow(a, x);
}

MathFunction* ExponentFunction::clone(){
    ExponentFunction* newFunc = new ExponentFunction(this->a, this->b);
    newFunc->color = this->color;
    return newFunc;
}