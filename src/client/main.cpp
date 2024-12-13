#include <iostream>
//#include <fstream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>

#include "../shared/engine/MoveCommand.h"
#include "../shared/state/PlayerInfo.h"
#include "../shared/state/Location.h"
#include "../shared/state/Cell.h"

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
    try {
        client::Client client("../configurations/client.json");
        Map map("../configurations/map.json");
        vector<vector<Cell>> mapGrid = map.getMapGrid();
        Cell startCell = mapGrid[8][8];
        PlayerInfo player("Player1", ROSE);
        player.setLocation(startCell);


        auto *playerCell = dynamic_cast<state::Cell*>(&player.getLocation());
        std::cout << "Starting position : ("
                << playerCell->getX() << ", "
                << playerCell->getY() << ")" << std::endl;


        std::cout << "Trying to move up ..." << std::endl;
        engine::MoveCommand moveCommandUp(player, 1);
        moveCommandUp.execute();

        playerCell = dynamic_cast<state::Cell *>(&player.getLocation());
        std::cout << "After moving up : ("
                << playerCell->getX() << ", "
                << playerCell->getY() << ")" << std::endl;


        std::cout << "Trying to move right ..." << std::endl;
        engine::MoveCommand moveCommandRight(player, 2);
        moveCommandRight.execute();

        playerCell = dynamic_cast<state::Cell *>(&player.getLocation());
        std::cout << "After moving to the right : ("
                << playerCell->getX() << ", "
                << playerCell->getY() << ")" << std::endl;


        std::cout << "Trying to move down ..." << std::endl;
        engine::MoveCommand moveCommandDown(player, 3);
        moveCommandDown.execute();

        playerCell = dynamic_cast<state::Cell *>(&player.getLocation());
        std::cout << "After moving down : ("
                << playerCell->getX() << ", "
                << playerCell->getY() << ")" << std::endl;


        std::cout << "Trying to move left ..." << std::endl;
        engine::MoveCommand moveCommandLeft(player, 4);
        moveCommandLeft.execute();

        playerCell = dynamic_cast<state::Cell *>(&player.getLocation());
        std::cout << "After moving to the left : ("
                << playerCell->getX() << ", "
                << playerCell->getY() << ")" << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
