#include <engine.h>
#include <state.h>
#include <client.h>
#include <render.h>
#include <ai.h>
#include <iostream>

#include <SFML/Graphics.hpp>

void test() {
    //put some code you want to run here
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cluedo plt");
    render::Scene scene(window);

}

void gameLoop(state::State& myState, engine::Engine& myEngine, client::Client& myClient) {
    client::PlayerList& myPlayerList = myClient.getPlayerList();
    client::IO& io = myClient.getIO();
    io.startOfTheGame(myPlayerList);
    while (!myState.getAccusationSuccess()) {
        client::Player& currentPlayer = myPlayerList.getCurrent();
        state::PlayerState& currentPlayerState =  currentPlayer.getPlayerState();
        if (currentPlayerState.getCanWin()) {
            const engine::CommandId currentAction = currentPlayer.chooseAction();
            switch (currentAction) {
                case engine::HYPOTHESIS: {
                    const state::TripleClue hypothesis = currentPlayer.chooseHypothesis();
                    io.displayHypothesis(currentPlayer, hypothesis);
                    myEngine.addCommand(std::make_unique<engine::HypothesisCommand>(myEngine, currentPlayerState, hypothesis));
                    myEngine.executeCommands();
                    myClient.askHypothesisToNeighbors(currentPlayer, hypothesis);
                }
                break;
                case engine::ACCUSATION: {
                    const state::TripleClue accusation = currentPlayer.chooseAccusation();
                    io.displayAccusation(currentPlayer, accusation);
                    myEngine.addCommand(std::make_unique<engine::AccusationCommand>(myEngine, currentPlayerState, accusation));
                }
                break;
                case engine::SECRET_PASSAGE: {
                    myEngine.addCommand(std::make_unique<engine::SecretPassageCommand>(myEngine, currentPlayerState));
                }
                break;
                case engine::MOVE_FROM_DICE: {
                    std::vector<int> diceResult = engine::Engine::dice();
                    int remainingMoves = diceResult.at(0) + diceResult.at(1);
                    io.displayDiceResult(myPlayerList, remainingMoves, currentPlayer);
                    while (remainingMoves > 0) {
                        if (currentPlayerState.getLocation().getType() == state::CORRIDOR or currentPlayerState.getLocation().getType() == state::DOOR) {
                            const auto& testCell = dynamic_cast<const state::Cell&>(currentPlayerState.getLocation());
                            std::cout << "coords: " << testCell.getX() << ", " << testCell.getY() << std::endl;
                        }
                        const auto possibleMoves = myEngine.getPossibleMoves(currentPlayerState);
                        if (possibleMoves.empty()) {
                            break;
                        }
                        const engine::Move moveDirection = currentPlayer.chooseMoveDirection();
                        if (moveDirection == engine::EXIT_ROOM) {
                            auto& currentRoom = dynamic_cast<state::Room&>(currentPlayerState.getLocation());
                            state::Door& newDoor = currentPlayer.chooseDoor(currentRoom.getDoorList());
                            myEngine.addCommand(std::make_unique<engine::MoveCommand>(myEngine, currentPlayerState, newDoor));
                        }
                        else {
                            state::Location& newLocation = myEngine.convertMoveToLocation(moveDirection);
                            myEngine.addCommand(std::make_unique<engine::MoveCommand>(myEngine, currentPlayerState, newLocation));
                        }
                        myEngine.executeCommands();
                        if (currentPlayerState.getLocation().getType() == state::ROOM) {
                            const state::TripleClue hypothesis = currentPlayer.chooseHypothesis();
                            io.displayHypothesis(currentPlayer, hypothesis);
                            myEngine.addCommand(std::make_unique<engine::HypothesisCommand>(myEngine, currentPlayerState, hypothesis));
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
        myEngine.setCurrentPlayer(myPlayerList.getCurrent().getPlayerState());
    }
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
        } else if (std::string(argv[2]) == "render") {
            tempIO = std::make_unique<client::RenderIO>();
        }
        else {
            throw std::invalid_argument(std::string("invalid argument: ") + argv[2]);
        }
        int playerCount = tempIO->introductionToTheGame();
        state::State myState(mapJsonPath, playerCount);
        engine::Engine myEngine(myState);

        //Construction de la liste des joueurs; le joueur humain est toujours le premier de la liste
        std::vector<state::PlayerState>& playerStateVec = myState.getPlayerStateVec();
        std::vector<std::unique_ptr<client::Player>> playerVec(playerCount);
        client::HumanPlayerConsole userPlayer(myEngine, playerStateVec.at(0), "User");
        playerVec.front() = std::make_unique<client::HumanPlayerConsole>(std::move(userPlayer));;
        for (int i = 1; i < playerCount; i++) {
            client::AIPlayer aiPlayer(myEngine, playerStateVec.at(i), "AI " + std::to_string(i), std::make_unique<ai::RandomAI>(myEngine, playerStateVec.at(i)));
            playerVec.at(i) = std::make_unique<client::AIPlayer>(std::move(aiPlayer));
        }
        client::Client myClient(myState, myEngine, tempIO, playerVec);

        //debut de la partie
        client::PlayerList& myPlayerList = myClient.getPlayerList();
        int firstPlayerIndex = myEngine.determineFirstPlayer();
        myPlayerList.setCurrent(myPlayerList.getVector().at(firstPlayerIndex));
        myEngine.setCurrentPlayer(playerStateVec.at(firstPlayerIndex));
        myEngine.distributionCharacters();
        myEngine.dealCards();

        gameLoop(myState, myEngine, myClient);
        return 0;
    }
}