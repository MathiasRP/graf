#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "MathFunction.hpp"

class CordinatSystem
{
private:
    struct FunctionElements{
        sf::VertexArray verticies;
        MathFunction* function;
        sf::Text nameText;
    };

    sf::Font font;
    bool fontLoaded = false;

    sf::Text x_name;
    sf::Text firstMark_x;
    int x_offset;
    sf::Text y_name;
    sf::Text firstMark_y;
    int y_offset;

    int height;
    int width;

    bool showMarks;
    int firstMark;
    int firstMarkValue;
    
    std::vector<sf::RectangleShape> marks;

    int pointInterval;

    sf::Vector2i position;
    sf::RectangleShape x_line;
        
    sf::RectangleShape y_line;

    sf::RectangleShape background;
    
    std::vector<FunctionElements> funtions;

    void setSize();
    void setPos();

    void reloadMarks();

    void resetAllFuntions();
    void setFunction(int index);

    void setTextPos();
public:
    CordinatSystem(int height = 50, int width = 50, int x_offset = 10, int y_offset = 10, std::string x_name = "x", std::string y_name = "y");
    ~CordinatSystem();

    void setBackgroundColor(sf::Color& color);
    void setSize(int height, int width);
    void setPosition(sf::Vector2i& pos);
    void setPosition(int x, int y);

    bool setFont(std::string filePath);
    void setFontSize(int size);

    void setX_Name(std::string name);
    void setX_Offset(int offset);
    void setX_Color(sf::Color color);
    void setY_Name(std::string name);
    void setY_Offset(int offset);
    void setY_Color(sf::Color color);
    void move(sf::Vector2f& vector);

    void setFirstMark(int pixel);
    void setShowMarks(bool show);
    void setFirstMarkValue(int value);

    void setPointInterval(int interval);

    void addFunction(MathFunction* func, std::string name = "");
    void removeFuntion(int index);
    size_t countFuntions();
    MathFunction* operator[](int index);

    void initialize();
    void update();
    void draw(sf::RenderTarget& target);
};


