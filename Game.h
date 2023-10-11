#ifndef GAME_H
#define GAME_H

#include <string>

#include "grafLib\CordinatSystem.hpp"

#include <SFML/Graphics.hpp>
#pragma once

class Game
{
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    std::string gameName;

    sf::RenderTexture p1;
    sf::RenderTexture p2;
    

public:
    Game();
    

    ~Game();
    void run();
private:

    CordinatSystem cordinatSystem;
    float xScalingFactor;
    float yScalingFactor;
    void init();
    void update();
    void draw();
};

#endif