#include "RenderCell.h"

#include <SFML/Graphics.hpp>

render::RenderCell::RenderCell (float x, float y, float width, float height, int gridX, int gridY)
: gridX(gridX), gridY(gridY){
        setPosition(x, y);
        setSize({width, height});
        setFillColor(sf::Color(255, 255, 153, 70));
        setOutlineColor(sf::Color::Black);
        setOutlineThickness(1);
    }
