#include "Panel.h"

#include <iostream>

namespace render{
Panel::Panel(float x, float y, float width, float height, sf::Color color)
{
    position = {x, y};
    shape.setPosition(position);
    shape.setSize({width, height});
    shape.setFillColor(color);
}

void Panel::draw(sf::RenderWindow &window)
{
    window.draw(shape);
    std::cout << "Drawing panel at " << position.x << ", " << position.y << std::endl;
    drawChildren(window);
}
}