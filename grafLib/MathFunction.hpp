#pragma once

#include <SFML/Graphics.hpp>

class MathFunction
{
private:
public:
    sf::Color color = sf::Color::White;
    
    virtual double getY(double x) = 0;
    virtual MathFunction* clone() = 0;
};
