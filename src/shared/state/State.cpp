//
// Created by louismmassin on 11/8/24.
//
#include "State.h"
#include "UtilityFunctions.cpp"
#include "CircularPlayerList.cpp"

#include <iostream>

#include "RoomCard.h"
#include "SuspectCard.h"
#include "UtilityFunctions.h"
#include "WeaponCard.h"

namespace state {
    State::State(int playerCount, std::string dataFilePath): players(*this, playerCount), accusationSuccess(false), map(dataFilePath) {
    }

    void State::determineFirstPlayer() {
        int dices=0;
        int joueur=0;
        PlayerInfo* firstPlayer = nullptr;
        PlayerInfo* currentPlayer = &players.getCurrent();
        for (int i=0; i<players.size();i++){
            int dice1 = UtilityFunctions::randomInt(5)+1;
            int dice2 = UtilityFunctions::randomInt(5)+1;
            std::cout << "Joueur " << i+1 << ": " <<"dice1: " << dice1 << "; dice2: " << dice2 << std::endl;
            if (dices < dice1 + dice2) {
                dices = dice1 + dice2;
                firstPlayer = currentPlayer;
                joueur = i+1;
            }
            players.next();
            currentPlayer = &players.getCurrent();
        }


        if (firstPlayer != nullptr) {
            std::cout << "Le joueur " << joueur << " commence" << std::endl;
            for (int i=1; i<=joueur; i++ ){
                players.next();
            }
        }
    }


    void State::dealCards() {

        std::vector<SuspectCard> suspectCardsVector;
        std::vector<WeaponCard> weaponCardsVector;
        std::vector<RoomCard> roomCardsVector;

        // VECTOR OF SUSPECTS
        suspectCardsVector.emplace_back(ROSE);
        suspectCardsVector.emplace_back(PERVENCHE);
        suspectCardsVector.emplace_back(LEBLANC);
        suspectCardsVector.emplace_back(OLIVE);
        suspectCardsVector.emplace_back(MOUTARDE);
        suspectCardsVector.emplace_back(VIOLET);

        // VECTOR OF WEAPONS
        weaponCardsVector.emplace_back(CANDLESTICK);
        weaponCardsVector.emplace_back(PISTOL);
        weaponCardsVector.emplace_back(ROPE);
        weaponCardsVector.emplace_back(LEAD_PIPE);
        weaponCardsVector.emplace_back(KNIFE);
        weaponCardsVector.emplace_back(WRENCH);

        // VECTOR OF ROOMS

        roomCardsVector.emplace_back(STUDY);
        roomCardsVector.emplace_back(HALL);
        roomCardsVector.emplace_back(LIVING_ROOM);
        roomCardsVector.emplace_back(DINING_ROOM);
        roomCardsVector.emplace_back(KITCHEN);
        roomCardsVector.emplace_back(BATHROOM);
        roomCardsVector.emplace_back(GARAGE);
        roomCardsVector.emplace_back(GAME_ROOM);
        roomCardsVector.emplace_back(BEDROOM);


        int randomSuspect = UtilityFunctions::randomInt(5);
        int randomWeapon = UtilityFunctions::randomInt(5);
        int randomRoom = UtilityFunctions::randomInt(8);

        envelope.push_back(std::move(suspectCardsVector[randomSuspect]));
        suspectCardsVector.erase(suspectCardsVector.begin()+randomSuspect);

        envelope.push_back(std::move(weaponCardsVector[randomWeapon]));
        weaponCardsVector.erase(weaponCardsVector.begin()+randomWeapon);

        envelope.push_back(std::move(roomCardsVector[randomRoom]));
        roomCardsVector.erase(roomCardsVector.begin()+randomSuspect);


        std::vector<Card> allCards;
        allCards.reserve(suspectCardsVector.size()+weaponCardsVector.size()+roomCardsVector.size());

        allCards.insert(allCards.end(), suspectCardsVector.begin(), suspectCardsVector.end());
        allCards.insert(allCards.end(), weaponCardsVector.begin(), weaponCardsVector.end());
        allCards.insert(allCards.end(), roomCardsVector.begin(), roomCardsVector.end());

        while (!allCards.empty()) {
            int randomIndex = UtilityFunctions::randomInt(allCards.size());
            players.getCurrent().giveCard(allCards.at(randomIndex));
            allCards.erase(allCards.begin()+randomIndex);
            players.next();
        }
    }

}

