#include <iostream>
//#include <fstream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}
// end of test SFML

#include <engine.h>
#include <state.h>
#include <client.h>
#include <engine.h>
#include <ai.h>

void test() {
    //put some code you want to run here
}

int main(int argc,char* argv[])
{

    test();//used for testing methods

    //main
    if (argc < 3) {
        throw std::invalid_argument("program needs at least 2 parameters");
    }
    if (std::string(argv[1]) == "solovsai") {
        //Initialisation
        const std::string mapJsonPath = "../configurations/map.json";
        std::unique_ptr<client::IO> tempIO;
        if (std::string(argv[2]) == "console") {
            tempIO = std::make_unique<client::ConsoleIO>();
        }
        else {
            throw std::invalid_argument(std::string("invalid argument: ") + argv[2]);
        }
        int playerCount = tempIO->introductionToTheGame();
        state::State myState(mapJsonPath, playerCount);
        engine::Engine myEngine(myState);

        //Construction de la liste des joueurs; le joueur humain est toujours le premier de la liste
        std::vector<state::PlayerInfo>& playerInfoVec = myState.getPlayerInfoVec();
        std::vector<std::unique_ptr<client::Player>> playerVec(playerCount);
        client::HumanPlayerConsole userPlayer(myEngine, playerInfoVec.at(0), "User");
        playerVec.front() = std::make_unique<client::HumanPlayerConsole>(std::move(userPlayer));;
        for (int i = 1; i < playerCount; i++) {
            client::AIPlayer aiPlayer(myEngine, playerInfoVec.at(i), "AI " + std::to_string(i), std::make_unique<ai::RandomAI>(myEngine, playerInfoVec.at(i)));
            playerVec.at(i) = std::make_unique<client::AIPlayer>(std::move(aiPlayer));
        }
        client::Client myClient(myState, myEngine, tempIO, playerVec);
        client::PlayerList& myPlayerList = myClient.getPlayerList();
        client::IO& io = myClient.getIO();

        //debut de la partie
        int firstPlayerIndex = myEngine.determineFirstPlayer();
        myPlayerList.setIterator(myPlayerList.getVector().at(firstPlayerIndex));
        myEngine.setCurrentPlayer(playerInfoVec.at(firstPlayerIndex));
        myEngine.distributionCharacters();
        myEngine.dealCards();
        //game loop
        while (!myState.getAccusationSuccess()) {
            client::Player& currentPlayer = myPlayerList.getCurrent();
            state::PlayerInfo& currentPlayerInfo =  currentPlayer.getPlayerInfo();
            io.displayMap(myState.getMap());
            if (currentPlayerInfo.getCanWin()) {
                const engine::CommandId currentAction = currentPlayer.chooseAction();
                switch (currentAction) {
                    case engine::HYPOTHESIS: {
                        const state::TripleClue hypothesis = currentPlayer.chooseHypothesis();
                        io.displayHypothesis(currentPlayer, hypothesis);
                        myEngine.addCommand(std::make_unique<engine::HypothesisCommand>(myEngine, currentPlayerInfo, hypothesis));
                        myEngine.executeCommands();
                        myClient.askHypothesisToNeighbors(currentPlayer, hypothesis);
                    }
                    break;
                    case engine::ACCUSATION: {
                        const state::TripleClue accusation = currentPlayer.chooseAccusation();
                        io.displayAccusation(currentPlayer, accusation);
                        myEngine.addCommand(std::make_unique<engine::AccusationCommand>(myEngine, currentPlayerInfo, accusation));
                    }
                    break;
                    case engine::SECRET_PASSAGE: {
                        myEngine.addCommand(std::make_unique<engine::SecretPassageCommand>(myEngine, currentPlayerInfo));
                    }
                    break;
                    case engine::MOVE_FROM_DICE: {
                        std::vector<int> diceResult = engine::Engine::dice();
                        int remainingMoves = diceResult.at(0) + diceResult.at(1);
                        io.displayDiceResult(myPlayerList, remainingMoves, currentPlayer);
                        while (remainingMoves > 0) {
                            if (currentPlayerInfo.getLocation().getType() == state::CORRIDOR or currentPlayerInfo.getLocation().getType() == state::DOOR) {
                                const auto& testCell = static_cast<const state::Cell&>(currentPlayerInfo.getLocation());
                                std::cout << "coords: " << testCell.getX() << ", " << testCell.getY() << std::endl;
                            }
                            const auto possibleMoves = myEngine.getPossibleMoves(currentPlayerInfo);
                            if (possibleMoves.empty()) {
                                break;
                            }
                            const engine::Move moveDirection = currentPlayer.chooseMoveDirection();
                            if (moveDirection == engine::EXIT_ROOM) {
                                auto& currentRoom = static_cast<state::Room&>(currentPlayerInfo.getLocation());
                                state::Door& newDoor = currentPlayer.chooseDoor(currentRoom.getDoorList());
                                myEngine.addCommand(std::make_unique<engine::MoveCommand>(myEngine, currentPlayerInfo, newDoor));
                            }
                            else {
                                state::Location& newLocation = myEngine.convertMoveToLocation(moveDirection);
                                myEngine.addCommand(std::make_unique<engine::MoveCommand>(myEngine, currentPlayerInfo, newLocation));
                            }
                            myEngine.executeCommands();
                            io.displayMap(myState.getMap());
                            if (currentPlayerInfo.getLocation().getType() == state::ROOM) {
                                const state::TripleClue hypothesis = currentPlayer.chooseHypothesis();
                                io.displayHypothesis(currentPlayer, hypothesis);
                                myEngine.addCommand(std::make_unique<engine::HypothesisCommand>(myEngine, currentPlayerInfo, hypothesis));
                                myEngine.executeCommands();
                                myClient.askHypothesisToNeighbors(currentPlayer, hypothesis);
                                break;
                            }
                            remainingMoves--;
                        }
                        break;
                    }
                    default:
                        throw std::runtime_error("switch case failed!");
                }
                myEngine.executeCommands();
            }
            if ( myState.getAccusationSuccess()) {
                io.displayGameEnd(currentPlayer);
                break;
            }
            myPlayerList.next();
            myEngine.setCurrentPlayer(myPlayerList.getCurrent().getPlayerInfo());

        }
    }
    return 0;
}