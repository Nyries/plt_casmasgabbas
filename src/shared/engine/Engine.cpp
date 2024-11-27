//
// Created by louismmassin on 11/18/24.
//
#include <iostream>
#include "state.h"
#include "engine.h"

namespace engine {
    Engine::Engine(state::State &state): state(state), playerList(state.getPlayerList()), map(state.getMap()), currentPlayer(playerList->getCurrent()), envelope(state.getEnvelope()) {
    }

    void Engine::determineFirstPlayer() {
        int dices=0;
        int joueur=0;
        state::PlayerInfo* firstPlayer = nullptr;
        state::PlayerInfo* currentPlayer = &playerList->getCurrent();
        for (int i=0; i<playerList->size();i++){
            int dice1 = UtilityFunctions::randomInt(5)+1;
            int dice2 = UtilityFunctions::randomInt(5)+1;
            std::cout << "Player " << i+1 << ": " <<"dice1: " << dice1 << "; dice2: " << dice2 << std::endl;
            if (dices < dice1 + dice2) {
                dices = dice1 + dice2;
                firstPlayer = currentPlayer;
                joueur = i+1;
            }
            playerList->next();
            currentPlayer = &playerList->getCurrent();
        }


        if (firstPlayer != nullptr) {
            std::cout << "Le joueur " << joueur << " commence" << std::endl;
            for (int i=1; i<=joueur; i++ ){
                playerList->next();
            }
        }
    }


    void Engine::dealCards() {

        std::vector<state::SuspectCard> suspectCardsVector;
        std::vector<state::WeaponCard> weaponCardsVector;
        std::vector<state::RoomCard> roomCardsVector;

        // VECTOR OF SUSPECTS
        suspectCardsVector.emplace_back(state::ROSE);
        suspectCardsVector.emplace_back(state::PERVENCHE);
        suspectCardsVector.emplace_back(state::LEBLANC);
        suspectCardsVector.emplace_back(state::OLIVE);
        suspectCardsVector.emplace_back(state::MOUTARDE);
        suspectCardsVector.emplace_back(state::VIOLET);

        // VECTOR OF WEAPONS
        weaponCardsVector.emplace_back(state::CANDLESTICK);
        weaponCardsVector.emplace_back(state::PISTOL);
        weaponCardsVector.emplace_back(state::ROPE);
        weaponCardsVector.emplace_back(state::LEAD_PIPE);
        weaponCardsVector.emplace_back(state::KNIFE);
        weaponCardsVector.emplace_back(state::WRENCH);

        // VECTOR OF ROOMS

        roomCardsVector.emplace_back(state::STUDY);
        roomCardsVector.emplace_back(state::HALL);
        roomCardsVector.emplace_back(state::LIVING_ROOM);
        roomCardsVector.emplace_back(state::DINING_ROOM);
        roomCardsVector.emplace_back(state::KITCHEN);
        roomCardsVector.emplace_back(state::BATHROOM);
        roomCardsVector.emplace_back(state::GARAGE);
        roomCardsVector.emplace_back(state::GAME_ROOM);
        roomCardsVector.emplace_back(state::BEDROOM);


        int randomSuspect = UtilityFunctions::randomInt(5);
        int randomWeapon = UtilityFunctions::randomInt(5);
        int randomRoom = UtilityFunctions::randomInt(8);

        envelope.push_back(std::move(suspectCardsVector[randomSuspect]));
        suspectCardsVector.erase(suspectCardsVector.begin()+randomSuspect);

        envelope.push_back(std::move(weaponCardsVector[randomWeapon]));
        weaponCardsVector.erase(weaponCardsVector.begin()+randomWeapon);

        envelope.push_back(std::move(roomCardsVector[randomRoom]));
        roomCardsVector.erase(roomCardsVector.begin()+randomSuspect);


        std::vector<state::Card> allCards;
        allCards.reserve(suspectCardsVector.size()+weaponCardsVector.size()+roomCardsVector.size());

        allCards.insert(allCards.end(), suspectCardsVector.begin(), suspectCardsVector.end());
        allCards.insert(allCards.end(), weaponCardsVector.begin(), weaponCardsVector.end());
        allCards.insert(allCards.end(), roomCardsVector.begin(), roomCardsVector.end());

        while (!allCards.empty()) {
            int randomIndex = UtilityFunctions::randomInt(allCards.size());
            playerList->getCurrent().giveCard(allCards.at(randomIndex));
            allCards.erase(allCards.begin()+randomIndex);
            playerList->next();
        }
    }

    int Engine::movementDices () {
        int die1 = UtilityFunctions::randomInt(5)+1;
        int die2 = UtilityFunctions::randomInt(5)+1;
        int sumOfDice = die1 + die2;
        client.displayDieValue(sumOfDice);  // rajouter un pointeur
        return sumOfDice;
    }

    void Engine::distributionCharacters () {
        int numberOfPlayer = playerList->size();
        std::vector<state::Suspect> SuspectsVector = {state::ROSE,state::PERVENCHE, state::LEBLANC, state::OLIVE, state::MOUTARDE, state::VIOLET} ;
        state::PlayerInfo* currentPlayer = &playerList->getCurrent();
        int players = 1;
        while (players!=numberOfPlayer+1) {
            currentPlayer->setIdentity(SuspectsVector.at(players));
            playerList->next();
            currentPlayer = &playerList->getCurrent();
        }
    }






}
