#include "Scene.h"

namespace render{
Scene::Scene(sf::RenderWindow &window): window(window)
{
    loadMapImage("../ressources/maison_map.png");

    Background.setPosition(400,    100);
    Background.setScale(0.45, 0.45);

}
void Scene::loadMapImage(std::string mapImagePath)
{
    BackgroundTexture.loadFromFile(mapImagePath);
    Background.setTexture(BackgroundTexture);
}
}