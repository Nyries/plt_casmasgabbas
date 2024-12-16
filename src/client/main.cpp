#include <iostream>
//#include <fstream>

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

void test() {
    //put some code you want to run here
}

int main(int argc,char* argv[])
{
    test();//used for testing methods
    //Ebauche du main
    const std::string clientJsonPath = "../configurations/client.json";
    client::Client myClient(clientJsonPath);
    engine::Engine& myEngine = myClient.getEngine();
    while (myClient.getClientPlayerInfo().getCanWin()) {
        const engine::CommandId currentAction = myClient.chooseAction();
        switch (currentAction) {
            case engine::HYPOTHESIS: {
                std::vector<int> hypothesis = myClient.chooseHypothesis();
                engine::HypothesisCommand myHypothesisCommand(myClient.getClientPlayerInfo(), hypothesis);
                myEngine.addCommand(myHypothesisCommand);
            }
            break;
            case engine::ACCUSATION: {
                std::vector<int> accusation = myClient.chooseAccusation();
                engine::AccusationCommand myAccusationCommand(myClient.getClientPlayerInfo(), accusation);
                myEngine.addCommand(myAccusationCommand);
            }
            break;
            case engine::SECRET_PASSAGE: {
                engine::SecretPassageCommand mySecretPassageCommand(myClient.getClientPlayerInfo());
                myEngine.addCommand(mySecretPassageCommand);
            }
            break;
            case engine::MOVE_FROM_DICE: {
                std::vector<int> diceResult = myEngine.dice();
                myClient.throwDiceClient();
                int remainingMoves = diceResult.at(0) + diceResult.at(1);
                while (remainingMoves > 0) {
                    const auto possibleMoves = myEngine.getPossibleMoves(myClient.getClientPlayerInfo());
                    if (possibleMoves.empty()) {
                        break;
                    }
                    const engine::Move moveDirection = myClient.chooseMoveDirection(possibleMoves);
                    engine::MoveCommand(myClient.getClientPlayerInfo(), moveDirection);
                    myEngine.executeCommands();
                    remainingMoves--;
                }
            }
            break;
            default:
                throw std::runtime_error("switch case failed!");
        }
        myEngine.executeCommands();
  /*
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
*/
    }
    return 0;
}


