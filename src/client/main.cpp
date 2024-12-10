#include <iostream>
#include <fstream>

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
    //test();
    //client::Client client("../configurations/client.json");
    //Map map("../configurations/map.json");
    //vector<vector<Cell>> mapGrid = map.getMapGrid();
    //state::State state("../configurations/state.json");
    //cout << mapGrid[25][27].getTypeAsString() << endl;
    //cout << 1/2 << endl;
    try {
        // Initialisation du joueur et de la position
        state::Cell startCell(0, 0, state::CORRIDOR); // Cellule de départ à (0, 0)
        state::PlayerInfo player("Player1", startCell); // Crée un joueur avec cette position

        std::cout << "Position initiale : ("
                  << player.getLocation().getCoordX() << ", "
                  << player.getLocation().getCoordY() << ")" << std::endl;

        // Déplacement du joueur vers le haut
        engine::MoveCommand moveCommandUp(player, 1);
        moveCommandUp.execute();

        std::cout << "Après déplacement vers le haut : ("
                  << player.getLocation().getCoordX() << ", "
                  << player.getLocation().getCoordY() << ")" << std::endl;

        // Déplacement du joueur vers la droite
        engine::MoveCommand moveCommandRight(player, 2);
        moveCommandRight.execute();

        std::cout << "Après déplacement vers la droite : ("
                  << player.getLocation().getCoordX() << ", "
                  << player.getLocation().getCoordY() << ")" << std::endl;

        // Déplacement du joueur vers le bas
        engine::MoveCommand moveCommandDown(player, 3);
        moveCommandDown.execute();

        std::cout << "Après déplacement vers le bas : ("
                  << player.getLocation().getCoordX() << ", "
                  << player.getLocation().getCoordY() << ")" << std::endl;

        // Déplacement du joueur vers la gauche
        engine::MoveCommand moveCommandLeft(player, 4);
        moveCommandLeft.execute();

        std::cout << "Après déplacement vers la gauche : ("
                  << player.getLocation().getCoordX() << ", "
                  << player.getLocation().getCoordY() << ")" << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
