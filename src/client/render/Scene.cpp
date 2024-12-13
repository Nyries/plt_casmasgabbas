#include "Scene.h"

#include <iostream>

namespace render{
Scene::Scene(sf::RenderWindow &window): window(window)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    std::cout << desktop.width << "x" << desktop.height << std::endl;
    window.create(sf::VideoMode(desktop.height, desktop.height), "Cluedo plt", sf::Style::Close | sf::Style::Resize);
    loadMapImage("../ressources/maison_map_2.png");
    window.setPosition(sf::Vector2i(desktop.height/4,0));
    window.setSize(sf::Vector2u(desktop.height, desktop.height));
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60); // Réduit la charge sur le processeur.
    Background.setScale(desktop.height, desktop.height);
    sf::Vector2u textureSize = BackgroundTexture.getSize();
    std::cout << textureSize.x << "x" << textureSize.y << std::endl;

    window.draw(Background);
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.display();
    }
}
void Scene::loadMapImage(std::string mapImagePath)
{
    BackgroundTexture.loadFromFile(mapImagePath);
    Background.setTexture(BackgroundTexture);
    Background.setPosition(0,0);
    
}
}