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

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    //test();
    client::Client client("../configurations/client.json");
    client.displayMap();
    //Map map("../configurations/map.json");
    //vector<vector<Cell>> mapGrid = map.getMapGrid();
    //state::State state("../configurations/state.json");
    //cout << mapGrid[25][27].getTypeAsString() << endl;
    //cout << 1/2 << endl;
    return 0;
}
