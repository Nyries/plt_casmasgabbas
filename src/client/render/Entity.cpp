#include "Entity.h"

namespace render{
void Entity::update()
{

}

void Entity::addChild(std::unique_ptr<Entity> child)
{
    children.push_back(std::move(child));
}

void Entity::drawChildren(sf::RenderWindow &window)
{
    for (auto &child : children)
    {
        child->draw(window);
    }
}
}