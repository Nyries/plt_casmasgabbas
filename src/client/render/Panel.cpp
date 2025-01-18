#include "Panel.h"

namespace render{
Panel::Panel(sf::RenderWindow& window, float x, float y, float width, float height, sf::Color color): Entity(window)
{
    position = {x, y};
    shape.setPosition(position);
    shape.setSize({width, height});
    shape.setFillColor(color);
}

void Panel::draw()
{
    window.draw(shape);
    drawChildren();
}
sf::RectangleShape &Panel::getShape()
{
    return shape;
    // TODO: insert return statement here
}
void Panel::setPosition(float x, float y)
{
    position = {x, y};
    shape.setPosition(position);
    for (auto &child : children)
    {
        //child->setPosition(child->getPosition() + position);
    }
}
void Panel::setScale(float x, float y)
{
    shape.setScale(x, y);
    for (auto &child : children)
    {
        //child->setScale(child->getPosition().x * x, child->getPosition().y * y);
    }
}
}