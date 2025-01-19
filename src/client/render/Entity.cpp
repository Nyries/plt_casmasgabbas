#include "Entity.h"

namespace render{
    Entity::Entity(sf::RenderWindow &window): window(window) {

    }

    void Entity::update()
    {

    }

    void Entity::addChild(std::unique_ptr<Entity>&& child)
    {
        children.push_back(std::move(child));
    }

    void Entity::drawChildren()
    {
        for (auto &child : children)
        {
            //std::cout << "Drawing child of type: " << typeid(*child).name() << std::endl;
            child->draw();
        }
    }
}