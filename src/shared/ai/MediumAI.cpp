//
// Created by cassandre on 13/01/25.
//


#include "MediumAI.h"
#include <engine/Engine.h>
#include <engine/UtilityFunctions.h>
#include <engine.h>
#include <algorithm>
#include <limits>
#include <queue>
#include <state/RoomCard.h>
#include <state/SuspectCard.h>
#include <state/WeaponCard.h>

namespace ai {
    MediumAI::MediumAI(engine::Engine &engine, state::PlayerState &playerState):AI(engine, playerState), doorDestination(nullptr) {
    }

    engine::CommandId MediumAI::chooseAction() {
        auto possibleActions = engine.getPossibleActions(playerState);

        if (std::find(knownSuspects.begin(), knownSuspects.end(), 2) != knownSuspects.end()
            and std::find(knownWeapons.begin(), knownWeapons.end(), 2) != knownWeapons.end()
            and std::find(knownRooms.begin(), knownRooms.end(), 2) != knownRooms.end())
        {
            return engine::ACCUSATION;
        }

        possibleActions.erase(std::remove(possibleActions.begin(), possibleActions.end(), engine::ACCUSATION), possibleActions.end());


        auto& playerRoom = static_cast<state::Room&>(playerState.getLocation());
        if (playerRoom.getRoomName() != playerState.getPreviousHypothesisRoom()) {
            return engine::HYPOTHESIS;
        }

        possibleActions.erase(std::remove(possibleActions.begin(), possibleActions.end(), engine::HYPOTHESIS), possibleActions.end());

        const int randomIndex = engine::UtilityFunctions::randomInt(possibleActions.size());
        return possibleActions.at(randomIndex);
    }

    int MediumAI::distanceBetweenTwoCells(const state::Cell &cell1, const state::Cell &cell2) {
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


    engine::Move MediumAI::chooseMoveDirection() {
        auto& cell1 = static_cast<state::Cell&>(playerState.getLocation());
        auto& cell2 = doorDestination;

        // POSITION DEPART ET ARRIVEE
        int startX = cell1.getX();;
        int startY = cell1.getY();
        int targetX = cell2->getX();
        int targetY = cell2->getY();

        // JOUEUR DANS UNE PIECE ?

        if (playerState.getLocation().getType() == state::ROOM) {
            return engine::EXIT_ROOM;
        }

        // SI JOUEUR SUR UNE PORTE IL RENTRE OU PAS

        if (playerState.getLocation().getType() == state::DOOR) {
            auto& door = static_cast<state::Door&>(playerState.getLocation());
            const state::Room* connectedRoom = door.getRoom();
            if (connectedRoom->getRoomName()!=playerState.getPreviousHypothesisRoom()) {
                return engine::ENTER_ROOM;
            }
        }

        // DIRECTION DES DEPLACEMENTS
        std::vector<std::pair<int, int>> directions = {
            {0, -1},  // UP
            {0, 1},   // DOWN
            {-1, 0},  // LEFT
            {1, 0}    // RIGHT
        };

        // Définir les coûts pour les déplacements
        int mapWidth = const_cast<state::Map&>(map).getWidth();
        int mapHeight = const_cast<state::Map&>(map).getHeight();


        std::vector<std::vector<int>> distances(mapWidth, std::vector<int>(mapHeight, std::numeric_limits<int>::max()));
        distances[startX][startY] = 0;

        std::vector<std::pair<int, int>> toExplore;
        toExplore.push_back({startX, startY});

        // TROUVER LES DISTANCES AVEC TOUTES LES CELLULES
        while (!toExplore.empty()) {
            auto [currentX, currentY] = toExplore.front();
            toExplore.pop_back();

            // CHECK LES VOISINS
            std::vector<state::LocationType> neighbors = map.getNeighborsAsLocationType(currentX, currentY);
            for (size_t i = 0; i < directions.size(); i++) {
                int nextX = currentX + directions[i].first;
                int nextY = currentY + directions[i].second;

                // CHECK LE TYPE DES CELLULES + LIMITES MAP
                if (nextX >= 0 && nextY >= 0 && nextX < mapWidth && nextY < mapHeight &&
                    neighbors[i] != state::ROOM &&
                    neighbors[i] != state::INACCESSIBLE) {
                    if (distances[nextX][nextY] > distances[currentX][currentY] + 1) {
                        distances[nextX][nextY] = distances[currentX][currentY] + 1;
                        toExplore.push_back({nextX, nextY});
                    }
                }
            }
        }

        // REVENIR A LA CELLULE PRECEDENTE
        for (size_t i = 0; i < directions.size(); i++) {
            int prevX = targetX - directions[i].first;
            int prevY = targetY - directions[i].second;

            if (prevX >= 0 && prevY >= 0 && prevX < mapWidth && prevY < mapHeight &&
                distances[prevX][prevY] == distances[targetX][targetY] - 1) {
                // RENVOYER LA DIRECTION
                if (directions[i] == std::make_pair(0, -1)) return engine::MOVE_DOWN;
                if (directions[i] == std::make_pair(0, 1)) return engine::MOVE_UP;
                if (directions[i] == std::make_pair(1, 0)) return engine::MOVE_RIGHT;
                if (directions[i] == std::make_pair(-1, 0)) return engine::MOVE_LEFT;
            }
        }

    }

    state::TripleClue MediumAI::chooseHypothesis() {

        state::TripleClue hypothesis{};

        for (int i = 0; i < knownSuspects.size(); ++i) {
            if (knownSuspects[i] == 0) {
                 int mediumSuspect = i;
                 hypothesis.suspect = static_cast<state::Suspect>(mediumSuspect);
            }
        }
        for (int i = 0; i < knownSuspects.size(); ++i) {
            if (knownSuspects[i] == 0) {
                int mediumWeapon = i;
                hypothesis.suspect = static_cast<state::Suspect>(mediumWeapon);
            }
        }
        auto locationEnum = playerState.getLocation().getType();
        if (locationEnum == state::ROOM) {
            auto& easyRoom = static_cast<state::Room&>(playerState.getLocation());
            hypothesis.room = easyRoom.getRoomName();
        } else {
            throw std::runtime_error("error");
        }
        return hypothesis;
    }

    int MediumAI::chooseACardToShowClient(const std::vector<const state::Card *> &cards, state::PlayerState &client) {
        const int randomIndex = engine::UtilityFunctions::randomInt(cards.size());
        return randomIndex;
    }

    void MediumAI::seeACardFromPlayer(const state::Card &shownCard, const state::PlayerState &cardOwner) {

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

    state::TripleClue MediumAI::chooseAccusation() {

        state::TripleClue accusation{};
        int easySuspect = std::distance(knownSuspects.begin(), std::find(knownSuspects.begin(), knownSuspects.end(), 2));
        accusation.suspect = static_cast<state::Suspect>(easySuspect+1);
        int easyWeapon = std::distance(knownWeapons.begin(), std::find(knownWeapons.begin(), knownWeapons.end(), 2));
        accusation.weapon = static_cast<state::Weapon>(easyWeapon+1);
        int easyRoom = std::distance(knownRooms.begin(), std::find(knownRooms.begin(), knownRooms.end(), 2));
        accusation.room = static_cast<state::RoomName>(easyRoom+1);
        return accusation;

    }

    state::Door &MediumAI::chooseDoor(const std::vector<state::Door *> &doorList) {
        state::Location position = playerState.getLocation();
        state::Room room = static_cast<state::Room&>(position);

        std::vector<state::Door*> roomDoors = room.getDoorList();
        std::vector<state::Door*> allDoors;

        for (int i = 1; i <= static_cast<int>(state::BEDROOM); ++i) {
            state::Room currentRoom = static_cast<state::RoomName>(i);
            if (currentRoom.getRoomName() != room.getRoomName()) {
                std::vector<state::Door*> roomDoors2 = currentRoom.getDoorList();
                allDoors.insert(allDoors.end(), roomDoors2.begin(), roomDoors2.end());
            }
        }

        std::vector<std::tuple<int, state::Door*, state::Door*>> distance;

        for (int i = 0; i<roomDoors.size();i++) {
            for (int j = 0; j<allDoors.size();i++) {
                state::Door* door1 = roomDoors.at(i);
                state::Door* door2 = roomDoors.at(j);
                auto* door1Cell = static_cast<state::Cell *>(door1);
                auto* door2Cell = static_cast<state::Cell *>(door2);  // transforme en cellule pour calculer la distance
                distance.push_back(std::make_tuple(distanceBetweenTwoCells(*door1Cell,*door2Cell), door1, door2));
            }
        }

        std::vector<std::tuple<int, state::Door*, state::Door*>> choice;

        for (const auto& t : distance) {
            int firstValue = std::get<0>(t);
            if (firstValue + 2 <= previousDiceResult) {
                choice.push_back(t);
            }
        }

        if (choice.size() > 0) {
            const int randomIndex = engine::UtilityFunctions::randomInt(choice.size());
            doorDestination = std::get<2>(choice[randomIndex]);  // de type state::Door*  faire une variable global, attribut
            return *std::get<1>(choice[randomIndex]);
        }

        if (choice.size() == 0) {   // distance ne sera jamais vide, c'est impossible

            int min = std::get<0>(distance.at(0));
            int index = 0;
            for (int i = 1; i<distance.size(); i++) {
                if (std::get<0>(distance.at(i))<min) {
                    min = std::get<0>(distance.at(i));
                    index = i;
                }
            }
            doorDestination = std::get<2>(choice[index]);
            return *std::get<1>(choice[index]);
        }
    }

    void MediumAI::getDiceResult(int result, const state::PlayerState &player) {
        if (playerState.getIdentity() == player.getIdentity()) {
            previousDiceResult = result;
        }
    }

    void MediumAI::startOfTheGame() {

    }

}

