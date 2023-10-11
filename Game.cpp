#include "Game.h"
#include "math.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
Game::Game()
{
    window = nullptr;
          xScalingFactor = 50.0f;
        yScalingFactor = 50.0f;
}

Game::~Game()
{
    if(window != nullptr){
        delete window;
    }
}

void Game::run(){
    init();
    while (window->isOpen())
    {
        update();
        draw();
    }
}


void Game::init() {
    gameName = "graflib";
    videoMode.height = 800;
    videoMode.width = 800;
    window = new sf::RenderWindow(videoMode, gameName);

    // Initialize the CordinatSystem with your desired parameters
    cordinatSystem = CordinatSystem(800, 800, 300, 300, "X", "Y");
    cordinatSystem.initialize();
    // Set the path to your font file
    bool fontLoaded = cordinatSystem.setFont("Content/font/PlayfairDisplay-Bold.ttf");
    
    // Check if the font was loaded successfully
    if (fontLoaded) {
        // Set font size for labels and axis names
        cordinatSystem.setFontSize(20);
    }


    cordinatSystem.setShowMarks(true);
    cordinatSystem.setFirstMark(20); // Adjust as needed
    cordinatSystem.setFirstMarkValue(20); // Adjust as needed
    cordinatSystem.setPointInterval(2); // Adjust as needed
}



void Game::update(){
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window->close();
            }
            //Check for input events
        }

        //Do other update taskes
}
     /*   // aktiver kun ved funktionen x-exp(x)=0 ellers deaktiver
std::vector<sf::Vector2f> calculateFunctionPoints(int functionID) {
    std::vector<sf::Vector2f> points;

    float xScalingFactor = 50.0f;
    float yScalingFactor = 50.0f;

    if (functionID == 1) {
        // Calculate and plot the function x - exp(x) = 0
        for (float x = -5; x <= 5; x += 0.1) {
            float y = x - exp(x); // Calculate the function value
            float scaledX = (x + 5) * xScalingFactor;
            float scaledY = -y * yScalingFactor; // Negate y to flip the plot
            points.push_back(sf::Vector2f(scaledX + 50, scaledY + 500));
        }
    }

    return points;
}
*/

     //Aktiver for funktionen x=cos(x)
std::vector<sf::Vector2f> calculateFunctionPoints(int functionID) {
    std::vector<sf::Vector2f> points;

    float xScalingFactor = 50.0f;
    float yScalingFactor = 50.0f; // Set the y scaling factor

    if (functionID == 1) {
        // Calculate and plot the function x = cos(x)
        for (float x = -5; x <= 5; x += 0.1) {
            float y = cos(x) * yScalingFactor;
            float scaledX = (x + 5) * xScalingFactor;
            points.push_back(sf::Vector2f(scaledX + 50, -y + 500));
        }
        
    } else if (functionID == 2) {
        // Recursive equation: x_(n+1) = cos(x_n)
        float x_n = 0.0f; // Initial value
        for (int n = 0; n < 6; n++) {
            float y = cos(x_n) * yScalingFactor;
            float scaledX = (static_cast<float>(n) + 5) * xScalingFactor;
            points.push_back(sf::Vector2f(scaledX + 50, -y + 500));

            x_n = cos(x_n);
        }
    }
    return points;
}


/*
 // Aktiver for funktionen 3x^2+x=12 
std::vector<sf::Vector2f> calculateFunctionPoints(int functionID) {
    std::vector<sf::Vector2f> points;

    float xScalingFactor = 50.0f;
    float yScalingFactor = 50.0f;  

    if (functionID == 1) {
        yScalingFactor = 50.0f; 
        // Beregner første funktion: 3x^2 + x
        for (float x = -5; x <= 5; x += 0.1) {
            float y = (3 * x * x + x) * yScalingFactor;
            float scaledX = (x + 5) * xScalingFactor;
            points.push_back(sf::Vector2f(scaledX + 50, -y + 500));
        }
    } else if (functionID == 2) {
        yScalingFactor = 100.0f; // 
        //// Beregner y-values for den anden ligning x_(n+1)= (12 - x_n) / 3
        float x = 0.0f; 
        for (int i = 0; i <= 100; i++) { // 
            float y = x * yScalingFactor;
            float scaledX = (x + 5) * xScalingFactor;
            points.push_back(sf::Vector2f(scaledX + 50, -y + 500));
            x = (12 - x) / 3; // 
        }
    } else if (functionID == 3) {
        yScalingFactor = 25.0f; 
        // Beregner y-values for den tredje ligning x_(n+1)= (12 - x_n) / 3
        float x = 0.0f; 
        for (int i = 0; i <= 100; i++) { 
            float y = x * yScalingFactor;
            float scaledX = (x + 5) * xScalingFactor;
            points.push_back(sf::Vector2f(scaledX + 50, -y + 500));
            x = (12 - x) / 3; 
        }
    } else if (functionID == 4) {
        yScalingFactor = 60.0f; 
        // Beregner y-values for den fjerde ligning x_(n+1)= (12 - x_n) / 3
        float x = 0.0f; 
        for (int i = 0; i <= 100; i++) { 
            float y = x * yScalingFactor;
            float scaledX = (x + 5) * xScalingFactor;
            points.push_back(sf::Vector2f(scaledX + 50, -y + 500));
            x = (12 - x) / 3; 
        }
    } else if (functionID == 5) {
        yScalingFactor = 62.0f; 
        // Beregner y-values for den fjerde ligning x_(n+1)= (12 - x_n) / 3
        float x = 0.0f; 
        for (int i = 0; i <= 100; i++) { 
            float y = x * yScalingFactor;
            float scaledX = (x + 5) * xScalingFactor;
            points.push_back(sf::Vector2f(scaledX + 50, -y + 500));
            x = (12 - x) / 3; 
        }
    }


    return points;
}
*/


void Game::draw() {
    window->clear();

    // Draw the coordinate system 
    cordinatSystem.draw(*window);
//Aktiver 2 første for x=cos(x), 5 første for 3x^2+x=12, kun den første hvis x-e^x=0 skal bruges.
    // Calculate the points and draw lines for the first function graph (3x^2 + x)
    std::vector<sf::Vector2f> functionPoints1 = calculateFunctionPoints(1);

    for (size_t i = 1; i < functionPoints1.size(); ++i) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = functionPoints1[i - 1];
        line[1].position = functionPoints1[i];
        line[0].color = sf::Color::Red;  // Adjust line color as needed
        line[1].color = sf::Color::Red;
        window->draw(line);
    }


    // Calculate the points and draw lines for the second function graph (Recursive sequence)
    std::vector<sf::Vector2f> functionPoints2 = calculateFunctionPoints(2);

    for (size_t i = 1; i < functionPoints2.size(); ++i) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = functionPoints2[i - 1];
        line[1].position = functionPoints2[i];
        line[0].color = sf::Color::Blue;  // Adjust line color as needed
        line[1].color = sf::Color::Blue;
        window->draw(line);
    }
/*
    // Calculate the points and draw lines for the third function graph
    std::vector<sf::Vector2f> functionPoints3 = calculateFunctionPoints(3);

    for (size_t i = 1; i < functionPoints3.size(); ++i) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = functionPoints3[i - 1];
        line[1].position = functionPoints3[i];
        line[0].color = sf::Color::Green;  // Adjust line color as needed
        line[1].color = sf::Color::Green;
        window->draw(line);
    }

    // Calculate the points and draw lines for the fourth function graph
    std::vector<sf::Vector2f> functionPoints4 = calculateFunctionPoints(4);

    for (size_t i = 1; i < functionPoints4.size(); ++i) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = functionPoints4[i - 1];
        line[1].position = functionPoints4[i];
        line[0].color = sf::Color::Red;  // Adjust line color as needed
        line[1].color = sf::Color::Red;
        window->draw(line);
    }
    // Calculate the points and draw lines for the fourth function graph
    std::vector<sf::Vector2f> functionPoints5 = calculateFunctionPoints(5);

    for (size_t i = 1; i < functionPoints5.size(); ++i) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = functionPoints5[i - 1];
        line[1].position = functionPoints5[i];
        line[0].color = sf::Color::Cyan;  // Adjust line color as needed
        line[1].color = sf::Color::Cyan;
        window->draw(line);
    }
*/
    window->display();
}

