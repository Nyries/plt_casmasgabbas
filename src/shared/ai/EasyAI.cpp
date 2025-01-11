//
// Created by cassandre on 09/01/25.
//


//
// Created by louismmassin on 1/4/25.
//
#include "EasyAI.h"

#include <engine/Engine.h>
#include <engine/UtilityFunctions.h>
#include <engine.h>
#include <algorithm>
#include <limits>
#include <state/RoomCard.h>
#include <state/SuspectCard.h>
#include <state/WeaponCard.h>

namespace ai {
    EasyAI::EasyAI(engine::Engine &engine, state::PlayerInfo &playerInfo):AI(engine, playerInfo) {
    }

    engine::CommandId EasyAI::chooseAction() {
        auto possibleActions = engine.getPossibleActions(playerInfo);

        if (findNumberInArray(knownSuspects,2)==1 and findNumberInArray(knownWeapons,2)==1 and findNumberInArray(knownRooms,2)==1) {
            return engine::ACCUSATION;
        }

        possibleActions.erase(std::remove(possibleActions.begin(), possibleActions.end(), engine::ACCUSATION), possibleActions.end());
        const int randomIndex = engine::UtilityFunctions::randomInt(possibleActions.size());
        return possibleActions.at(randomIndex);
    }

    int EasyAI::distanceBetweenTwoCells(const state::Cell& cell1, const state::Cell& cell2){
        int X1 = cell1.getX();
        int Y1 = cell1.getY();
        int X2 = cell2.getX();
        int Y2 = cell2.getY();

        if (X1 == X2 && Y1 == Y2) {
            return 0;
        }

        int mapWidth = const_cast<state::Map&>(map).getWidth();
        int mapHeight = const_cast<state::Map&>(map).getHeight();

        std::vector<std::pair<int, int>> directions = {
            {0, -1},  // up
            {0, 1},   // down
            {-1, 0},  // left
            {1, 0}    // right
        };

        std::vector<std::vector<int>> distances(mapWidth, std::vector<int>(mapHeight, std::numeric_limits<int>::max()));
        distances[X1][Y1] = 0;

        std::vector<std::pair<int, int>> toExplore;
        toExplore.push_back({X1, Y1});

        size_t currentIndex = 0;

        while (currentIndex < toExplore.size()) {
            auto [currentX, currentY] = toExplore[currentIndex];
            currentIndex++;

            std::vector<state::LocationType> neighbors = map.getNeighborsAsLocationType(currentX, currentY);


            for (size_t i = 0; i < directions.size(); i++) {
                int nextX = currentX + directions[i].first;
                int nextY = currentY + directions[i].second;

                // Vérifiez les limites de la carte et le type de cellule
                if (nextX >= 0 && nextY >= 0 && nextX < mapWidth && nextY < mapHeight &&
                    neighbors[i] != state::ROOM &&
                    neighbors[i] != state::INACCESSIBLE) {
                    // Si la cellule n’a pas encore été visitée ou qu'une distance plus courte est trouvée
                    if (distances[nextX][nextY] > distances[currentX][currentY] + 1) {
                        distances[nextX][nextY] = distances[currentX][currentY] + 1;
                        toExplore.push_back({nextX, nextY});

                        // Si on atteint la cellule cible
                        if (nextX == X2 && nextY == Y2) {
                            return distances[nextX][nextY];
                        }
                    }
                    }
            }
        } return -1;
    }

    engine::Move EasyAI::chooseMoveDirection() {



        if (playerInfo.getLocation().getType() == state::ROOM) {

            return engine::ENTER_ROOM;
        }

        if (playerInfo.getLocation().getType() == state::DOOR) {
            state::RoomName previousRoom = playerInfo.getPreviousHypothesisRoom();
            auto locationType = playerInfo.getLocation().getType();

            /*if (locationType == state::ROOM) {
                state::Room* room = playerInfo.getLocation().getRoom();

                if (room) {
                }
*/

        }





        auto possibleMoves = engine.getPossibleMoves(playerInfo);
        const int randomIndex = engine::UtilityFunctions::randomInt(possibleMoves.size());
        return possibleMoves.at(randomIndex);
    }

    state::TripleClue ai::EasyAI::chooseHypothesis() {
        state::TripleClue hypothesis{};
        int randomSuspect = engine::UtilityFunctions::randomInt(6) + 1;
        hypothesis.suspect = static_cast<state::Suspect>(randomSuspect);
        int randomWeapon = engine::UtilityFunctions::randomInt(6) + 1;
        hypothesis.weapon = static_cast<state::Weapon>(randomWeapon);
        state::Location randomPlace = playerInfo.getLocation();
        state::LocationType randomRoom = randomPlace.getType();
        hypothesis.room = static_cast<state::RoomName>(randomRoom);
        return hypothesis;
    }


    int ai::EasyAI::chooseACardToShowClient(const std::vector<const state::Card *> &cards) {
        const int randomIndex = engine::UtilityFunctions::randomInt(cards.size());
        return randomIndex;

    }


    void ai::EasyAI::seeACardFromPlayer(const state::Card &shownCard, const state::PlayerInfo &cardOwner) {

        if (shownCard.getType() == state::SUSPECT_CARD) {
            int number = std::stoi(shownCard.getValueAsString());
            knownSuspects[number] = 2;
        }

        if (shownCard.getType() == state::WEAPON_CARD) {
            int number = std::stoi(shownCard.getValueAsString());
            knownWeapons[number] = 2;
        }

        if (shownCard.getType() == state::ROOM_CARD) {
            int number = std::stoi(shownCard.getValueAsString());
            knownRooms[number] = 2;
        }
    }


    // Retourne l'index trouvé (position dans l'array) sert pour trouver un zéro ou un deux (pour accusation)
    template <size_t N>
    int EasyAI::findNumberInArray(std::array<int,N>& array, int number) {
        for (size_t i = 0; i < array.size(); ++i) {
            if (array[i] == number) {
                return i;
            }
        }
        return -1;
    }

    state::TripleClue ai::EasyAI::chooseAccusation() {

        state::TripleClue accusation{};
        int easySuspect = findNumberInArray(knownSuspects,2);
        accusation.suspect = static_cast<state::Suspect>(easySuspect+1);
        int easyWeapon = findNumberInArray(knownWeapons,2);
        accusation.weapon = static_cast<state::Weapon>(easyWeapon+1);
        int easyRoom = findNumberInArray(knownRooms,2);
        accusation.room = static_cast<state::RoomName>(easyRoom+1);
        return accusation;
    }

    state::Door &ai::EasyAI::chooseDoor(const std::vector<state::Door *> &doorList) {
                const int randomIndex = engine::UtilityFunctions::randomInt(doorList.size());
        return *doorList.at(randomIndex);
    }


}
