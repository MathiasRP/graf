#include "LinesFunction.hpp"

LinesFunction::LinesFunction(float a, float b)
{
    this->a = a;
    this->b = b;
}

LinesFunction::~LinesFunction()
{
}

void LinesFunction::setA(float a){
    this->a = a;
}

void LinesFunction::setB(float b){
    this->b = b;
}

double LinesFunction::getY(double x){
    return x * this->a + this->b;
}

MathFunction* LinesFunction::clone(){
    LinesFunction* newFunc = new LinesFunction(this->a, this->b);
    newFunc->color = this->color;

    return newFunc;
}