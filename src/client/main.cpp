#include <iostream>
#include <fstream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}
// end of test SFML

#include <engine.h>
#include <state.h>
#include <client.h>
#include <render.h>

using namespace std;

int main(int argc,char* argv[])
{
    testSFML();
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktop.height, desktop.height), "Cluedo plt", sf::Style::Close);
    render::Scene scene(window);



    return 0;
}
