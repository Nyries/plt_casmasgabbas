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
#include <engine.h>

using namespace std;
using namespace state;
using namespace engine;

void test() {
    //put some code you want to run here
}

int main(int argc,char* argv[])
{
    /*
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
                myEngine.addCommand(&myHypothesisCommand);
            }
            break;
            case engine::ACCUSATION: {
                std::vector<int> accusation = myClient.chooseAccusation();
                engine::AccusationCommand myAccusationCommand(myClient.getClientPlayerInfo(), accusation);
                myEngine.addCommand(&myAccusationCommand);
            }
            break;
            case engine::SECRET_PASSAGE: {
                engine::SecretPassageCommand mySecretPassageCommand(myClient.getClientPlayerInfo());
                myEngine.addCommand(&mySecretPassageCommand);
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
                    engine::MoveCommand myMoveCommand(myClient.getClientPlayerInfo(), moveDirection);
                    myEngine.addCommand(&myMoveCommand);
                    myEngine.executeCommands();
                    remainingMoves--;
                }
            }
            break;
            default:
                throw std::runtime_error("switch case failed!");
        }
        myEngine.executeCommands();
    }*/
    try {
        PlayerInfo player("Player1", ROSE);
        Cell startCell(8, 8, CORRIDOR);
        player.setLocation(startCell);
        cout << "Initial position : (" << startCell.getX()
             << ", " << startCell.getY() << ")" << endl;


        MoveCommand moveUp(player, MOVE_UP);
        moveUp.execute();
        Cell *currentCell = static_cast<state::Cell*>(&player.getLocation());
        cout << "After MOVE UP: (" << currentCell->getX()
             << ", " << currentCell->getY() << ")" << endl;

        MoveCommand moveRight(player, MOVE_RIGHT);
        moveRight.execute();
        currentCell = static_cast<state::Cell*>(&player.getLocation());
        cout << "After MOVE RIGHT: (" << currentCell->getX()
             << ", " << currentCell->getY() << ")" << endl;

        MoveCommand moveDown(player, MOVE_DOWN);
        moveDown.execute();
        currentCell = static_cast<state::Cell*>(&player.getLocation());
        cout << "After MOVE DOWN: (" << currentCell->getX()
             << ", " << currentCell->getY() << ")" << endl;

        MoveCommand moveLeft(player, MOVE_LEFT);
        moveLeft.execute();
        currentCell = static_cast<state::Cell*>(&player.getLocation());
        cout << "After MOVE LEFT: (" << currentCell->getX()
             << ", " << currentCell->getY() << ")" << endl;

    } catch (const std::invalid_argument &e) {
        cerr << "Error : " << e.what() << endl;
    } catch (...) {
        cerr << "An unknown error occurred !" << endl;
    }
    return 0;
}


