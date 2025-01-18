#include "RenderCell.h"

namespace render {

RenderCell::RenderCell (sf::RenderWindow& window, int gridX, int gridY, float x, float y, float width, float height, sf::Color color)
: Panel(window, x, y, width, height, color), gridX(gridX), gridY(gridY){

    }
/*
void RenderCell::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}
*/
}