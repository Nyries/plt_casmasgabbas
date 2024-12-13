#include <iostream>
#include <fstream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}
// end of test SFML

#include <state.h>
#include <client.h>
#include <render.h>

using namespace std;

int main(int argc,char* argv[])
{
    //test();
    //client::Client client("../configurations/client.json");
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktop.height, desktop.height), "Cluedo plt", sf::Style::Close);
    render::Scene scene(window);
    /*window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60); // Réduit la charge sur le processeur.

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
    }*/


    //Map map("../configurations/map.json");
    //vector<vector<Cell>> mapGrid = map.getMapGrid();
    //state::State state("../configurations/state.json");
    //cout << mapGrid[25][27].getTypeAsString() << endl;
    //cout << 1/2 << endl;
    return 0;
}
