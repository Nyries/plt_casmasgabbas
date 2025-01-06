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
#include <ai.h>

void test() {
    //put some code you want to run here
}

int main(int argc,char* argv[])
{
    test();//used for testing methods

    //Ebauche du main
    if (argc < 2) {
        throw std::invalid_argument("program needs at least 1 parameter");
    }
    if (std::string(argv[1]) == "solovsai") {
        //Initialisation
        const std::string mapJsonPath = "../configurations/map.json";
        int playerCount = client::Client::introductionToTheGame();
        state::State myState(mapJsonPath, playerCount);
        engine::Engine myEngine(myState);

        //Construction de la liste des joueurs; le joueur humain est toujours le premier de la liste
        std::vector<state::PlayerInfo>& playerInfoVec = myState.getPlayerInfoVec();
        std::vector<std::unique_ptr<client::Player>> playerVec(playerCount);
        client::HumanPlayerConsole userPlayer(myEngine, playerInfoVec.at(0), "User");
        playerVec.front() = std::make_unique<client::HumanPlayerConsole>(std::move(userPlayer));;
        for (int i = 1; i < playerCount; i++) {
            client::AIPlayer aiPlayer(myEngine, playerInfoVec.at(i), "AI " + i, std::make_unique<ai::RandomAI>(myEngine, playerInfoVec.at(i)));
            playerVec.at(i) = std::make_unique<client::AIPlayer>(std::move(aiPlayer));
        }
        client::Client myClient(myState, myEngine, playerVec);
        client::PlayerList& myPlayerList = myClient.getPlayerList();

        //debut de la partie
        myEngine.determineFirstPlayer();
        myEngine.distributionCharacters();


        //game loop
        while (!myState.getAccusationSuccess()) {
            client::Player& currentPlayer = myPlayerList.getCurrent();
            state::PlayerInfo& currentPlayerInfo =  currentPlayer.getPlayerInfo();
            const engine::CommandId currentAction = currentPlayer.chooseAction();
            switch (currentAction) {
                case engine::HYPOTHESIS: {
                    const state::TripleClue hypothesis = currentPlayer.chooseHypothesis();
                    myEngine.addCommand(std::make_unique<engine::HypothesisCommand>(myEngine, currentPlayerInfo, hypothesis));
                    myEngine.executeCommands();
                    myClient.askHypothesisToNeighbors(currentPlayer, hypothesis);

                }
                break;
                case engine::ACCUSATION: {
                    const state::TripleClue accusation = currentPlayer.chooseAccusation();
                    myEngine.addCommand(std::make_unique<engine::AccusationCommand>(myEngine, currentPlayerInfo, accusation));
                }
                break;
                case engine::SECRET_PASSAGE: {
                    myEngine.addCommand(std::make_unique<engine::SecretPassageCommand>(myEngine, currentPlayerInfo));
                }
                break;
                case engine::MOVE_FROM_DICE: {
                    std::vector<int> diceResult = engine::Engine::dice();
                    myClient.throwDiceClient();
                    int remainingMoves = diceResult.at(0) + diceResult.at(1);
                    while (remainingMoves > 0) {
                        const auto possibleMoves = myEngine.getPossibleMoves(currentPlayerInfo);
                        if (possibleMoves.empty()) {
                            break;
                        }
                        const engine::Move moveDirection = currentPlayer.chooseMoveDirection();
                        myEngine.addCommand(std::make_unique<engine::MoveCommand>(myEngine, currentPlayerInfo, moveDirection));
                        myEngine.executeCommands();
                        remainingMoves--;
                    }
                }
                break;
                default:
                    throw std::runtime_error("switch case failed!");
            }
            myEngine.executeCommands();
            myPlayerList.next();
            myState.setCurrentPlayer(myPlayerList.getCurrent().getPlayerInfo());
        }
    }
    std::cout << "game end!";
    return 0;
}