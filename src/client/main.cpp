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
                    myClient.moveFromDiceStart(diceResult);
                    int remainingMoves = diceResult.at(0) + diceResult.at(1);
                    while (remainingMoves > 0) {
                        const auto possibleMoves = myEngine.getPossibleMoves(myClient.getClientPlayerInfo());
                        int moveDirection = myClient.chooseMoveDirection(possibleMoves);
                        engine::MoveCommand(myClient.getClientPlayerInfo(), moveDirection);
                        myEngine.executeCommands();
                        remainingMoves--;
                    }
                }
                    break;
                default:
                    throw std::runtime_error("switch case failed!");
                    break;
            }

        myEngine.executeCommands();
    }


    return 0;
}
