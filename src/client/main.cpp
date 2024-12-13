#include <iostream>
#include <fstream>

// The following lines are here to check that SFML is installed and working
#include <engine.h>
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
    client::Client myClient("../configurations/client.json");
    //sf::RenderWindow window(sf::VideoMode(1600, 900), "Cluedo plt");
    //window.setVerticalSyncEnabled(true);
    //render::Scene scene(window);
    //Map map("../configurations/map.json");
    //vector<vector<Cell>> mapGrid = map.getMapGrid();
    //state::State state("../configurations/state.json");
    //cout << mapGrid[25][27].getTypeAsString() << endl;
    //cout << 1/2 << endl;



    std::cout << "end" << std::endl;

    return 0;
}
