//
// Created by louismmassin on 11/8/24.
//
#include "State.h"

#include <iostream>

#include "RoomCard.h"
#include "SuspectCard.h"
#include "UtilityFunctions.h"
#include "WeaponCard.h"

namespace state {
    State::State(int playerCount, std::string dataFilePath): players(*this, playerCount), accusationSuccess(false),
                                                             map(std::move(dataFilePath)) {
        //TODO: Initialization of the Rooms
    }


    void State::determineFirstPlayer() {
        int dices=0;
        int joueur=0;
        Player* firstPlayer = nullptr;
        Player* currentPlayer = &players.getCurrent();
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

        std::vector<SuspectCard> suspectsVector;
        std::vector<WeaponCard> weaponsVector;
        std::vector<RoomCard> roomsVector;

        // VECTOR OF SUSPECTS
        suspectsVector.emplace_back(ROSE);
        suspectsVector.emplace_back(PERVENCHE);
        suspectsVector.emplace_back(LEBLANC);
        suspectsVector.emplace_back(OLIVE);
        suspectsVector.emplace_back(MOUTARDE);
        suspectsVector.emplace_back(VIOLET);

        // VECTOR OF WEAPONS
        weaponsVector.emplace_back(CANDLESTICK);
        weaponsVector.emplace_back(PISTOL);
        weaponsVector.emplace_back(ROPE);
        weaponsVector.emplace_back(LEAD_PIPE);
        weaponsVector.emplace_back(KNIFE);
        weaponsVector.emplace_back(WRENCH);

        // VECTOR OF ROOMS

        roomsVector.emplace_back(STUDY);
        roomsVector.emplace_back(HALL);
        roomsVector.emplace_back(LIVING_ROOM);
        roomsVector.emplace_back(DINING_ROOM);
        roomsVector.emplace_back(KITCHEN);
        roomsVector.emplace_back(BATHROOM);
        roomsVector.emplace_back(GARAGE);
        roomsVector.emplace_back(GAME_ROOM);
        roomsVector.emplace_back(BEDROOM);


        int randomSuspect = UtilityFunctions::randomInt(5);
        int randomWeapon = UtilityFunctions::randomInt(5);
        int randomRoom = UtilityFunctions::randomInt(8);

        envelope.push_back(std::move(suspectsVector[randomSuspect]));
        suspectsVector.erase(suspectsVector.begin()+randomSuspect);

        envelope.push_back(std::move(weaponsVector[randomWeapon]));
        weaponsVector.erase(weaponsVector.begin()+randomWeapon);

        envelope.push_back(std::move(roomsVector[randomRoom]));
        roomsVector.erase(roomsVector.begin()+randomSuspect);


        std::vector<Card> allCards;
        allCards.reserve(suspectsVector.size()+weaponsVector.size()+roomsVector.size());

        allCards.insert(allCards.end(), suspectsVector.begin(), suspectsVector.end());
        allCards.insert(allCards.end(), weaponsVector.begin(), weaponsVector.end());
        allCards.insert(allCards.end(), roomsVector.begin(), roomsVector.end());

        while (!allCards.empty()) {
            int randomIndex = UtilityFunctions::randomInt(allCards.size());
            players.getCurrent().giveCard(allCards.at(randomIndex));
            allCards.erase(allCards.begin()+randomIndex);
            players.next();
        }
    }
}

