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
#include <iostream>
#include <state/RoomCard.h>
#include <state/SuspectCard.h>
#include <state/WeaponCard.h>

namespace ai {
    MediumAI::MediumAI(engine::Engine &engine, state::PlayerState &playerState):AI(engine, playerState), doorDestination(nullptr){
    }

    engine::CommandId MediumAI::chooseAction() {

        auto possibleActions = engine.getPossibleActions(playerState);

        if (std::count(knownSuspects.begin(), knownSuspects.end(), 0)==1) {
            *std::find(knownSuspects.begin(), knownSuspects.end(), 0)=3;
        }

        if (std::count(knownWeapons.begin(), knownWeapons.end(), 0)==1) {
            *std::find(knownWeapons.begin(), knownWeapons.end(), 0)=3;
        }

        if (std::count(knownRooms.begin(), knownRooms.end(), 0)==1) {
            *std::find(knownRooms.begin(), knownRooms.end(), 0)=3;
        }


        if (std::find(knownSuspects.begin(), knownSuspects.end(), 3) != knownSuspects.end()
            and std::find(knownWeapons.begin(), knownWeapons.end(), 3) != knownWeapons.end()
            and std::find(knownRooms.begin(), knownRooms.end(), 3) != knownRooms.end())
        {
            return engine::ACCUSATION;
        }

        possibleActions.erase(std::remove(possibleActions.begin(), possibleActions.end(), engine::ACCUSATION), possibleActions.end());

        if (playerState.getLocation().getType()==state::ROOM){auto& playerRoom = static_cast<state::Room&>(playerState.getLocation());
            if (playerRoom.getRoomName() != playerState.getPreviousHypothesisRoom()) {
                return engine::HYPOTHESIS;
            }
            possibleActions.erase(std::remove(possibleActions.begin(), possibleActions.end(), engine::HYPOTHESIS), possibleActions.end());
        }

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
         // JOUEUR DANS UNE PIECE ?

               const auto& possibleMoves = engine.getPossibleMoves(playerState);
        if (possibleMoves.empty()) {
            throw std::runtime_error("no possible moves");
        }
        if (possibleMoves.size()== 1) {
            return possibleMoves.front();
        }
        if (std::find(possibleMoves.begin(), possibleMoves.end(), engine::ENTER_ROOM) != possibleMoves.end()) {
            const auto& currentDoor = dynamic_cast<const state::Door&>(playerState.getLocation());
            if (&currentDoor == doorDestination) {
                return engine::ENTER_ROOM;
            }
        }
        const auto& currentCell = dynamic_cast<const state::Cell&>(playerState.getLocation());
        int minValue = 999;
        engine::Move minMove = engine::MOVE_UP;
        for (engine::Move move: possibleMoves) {
            switch (move) {
                case engine::MOVE_UP: {
                    int currentValue = distanceMatrix[currentCell.getY() - 1][currentCell.getX()];
                    if (currentValue < minValue) {
                        minMove = move;
                        minValue = currentValue;
                    }
                    break;
                }
                case engine::MOVE_DOWN: {
                    int currentValue = distanceMatrix[currentCell.getY() + 1][currentCell.getX()];
                    if (currentValue < minValue) {
                        minMove = move;
                        minValue = currentValue;
                    }
                    break;
                }
                case engine::MOVE_LEFT: {
                    int currentValue = distanceMatrix[currentCell.getY()][currentCell.getX() - 1];
                    if (currentValue < minValue) {
                        minMove = move;
                        minValue = currentValue;
                    }
                    break;
                }
                case engine::MOVE_RIGHT: {
                    int currentValue = distanceMatrix[currentCell.getY()][currentCell.getX() + 1];
                    if (currentValue < minValue) {
                        minMove = move;
                        minValue = currentValue;
                    }
                    break;
                }
                default:
                    break;
            }
        }
        return minMove;
    }


    state::TripleClue MediumAI::chooseHypothesis() {

        state::TripleClue hypothesis{};

        if (std::find(knownSuspects.begin(), knownSuspects.end(), 3)==knownSuspects.end()) {
            std::vector<size_t> indexZeroSuspect;
            for (size_t i = 0; i < knownSuspects.size(); i++) {
                if (knownSuspects.at(i) == 0) {
                    indexZeroSuspect.push_back(i);
                }
            }
            const int randomSuspect = engine::UtilityFunctions::randomInt(indexZeroSuspect.size());
            const int mediumSuspect = indexZeroSuspect.at(randomSuspect);
            hypothesis.suspect = static_cast<state::Suspect>(mediumSuspect+1);
        } else {
            std::vector<size_t> indexMyCardsSuspect;
            for (size_t i = 0; i < knownSuspects.size(); i++) {
                if (knownSuspects.at(i) == 1 or knownSuspects.at(i) == 3) {
                    indexMyCardsSuspect.push_back(i);
                }
            }
            const int mediumSuspect = engine::UtilityFunctions::randomInt(indexMyCardsSuspect.size());
            hypothesis.suspect = static_cast<state::Suspect>(mediumSuspect+1);
        }


        if (std::find(knownWeapons.begin(), knownWeapons.end(), 3)==knownWeapons.end()) {
            std::vector<size_t> indexZeroWeapon;
            for (size_t i = 0; i < knownWeapons.size(); i++) {
                if (knownWeapons.at(i) == 0) {
                    indexZeroWeapon.push_back(i);
                }
            }
            const int randomWeapon = engine::UtilityFunctions::randomInt(indexZeroWeapon.size());
            const int mediumWeapon = indexZeroWeapon.at(randomWeapon);
            hypothesis.weapon = static_cast<state::Weapon>(mediumWeapon+1);
        } else {
            std::vector<size_t> indexMyCardsWeapon;
            for (size_t i = 0; i < knownWeapons.size(); i++) {
                if (knownWeapons.at(i) == 1 or knownWeapons.at(i) == 3) {
                    indexMyCardsWeapon.push_back(i);
                }
            }
            const int mediumWeapon = engine::UtilityFunctions::randomInt(indexMyCardsWeapon.size());
            hypothesis.weapon = static_cast<state::Weapon>(mediumWeapon+1);
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

    int MediumAI::chooseACardToShowClient (const std::vector<const state::Card*>& cards, const state::PlayerState& client) {
        const int randomIndex = engine::UtilityFunctions::randomInt(cards.size());
        return randomIndex;
    }

    void MediumAI::seeACardFromPlayer(const state::Card &shownCard, const state::PlayerState &cardOwner) {

        if (shownCard.getType() == state::SUSPECT_CARD) {
            const auto& suspectCard = static_cast<const state::SuspectCard&>(shownCard);
            knownSuspects[suspectCard.getSuspectName()-1] = 2;
        }

        if (shownCard.getType() == state::WEAPON_CARD) {
            const auto& weaponCard = static_cast<const state::WeaponCard&>(shownCard);
            knownWeapons[weaponCard.getWeaponName()-1] = 2;
        }

        if (shownCard.getType() == state::ROOM_CARD) {
            const auto& roomCard = static_cast<const state::RoomCard&>(shownCard);
            knownRooms[roomCard.getRoomName()-1] = 2;
        }
        std::cout << cardOwner.getIdentity() << " showed a card to " << playerState.getIdentity()  << std::endl;
    }

    state::TripleClue MediumAI::chooseAccusation() {

        state::TripleClue accusation{};
        int easySuspect = std::distance(knownSuspects.begin(), std::find(knownSuspects.begin(), knownSuspects.end(), 3));
        accusation.suspect = static_cast<state::Suspect>(easySuspect+1);
        int easyWeapon = std::distance(knownWeapons.begin(), std::find(knownWeapons.begin(), knownWeapons.end(), 3));
        accusation.weapon = static_cast<state::Weapon>(easyWeapon+1);
        int easyRoom = std::distance(knownRooms.begin(), std::find(knownRooms.begin(), knownRooms.end(), 3));
        accusation.room = static_cast<state::RoomName>(easyRoom+1);
        return accusation;

    }

    state::Door &MediumAI::chooseDoor(const std::vector<state::Door *> &doorList) {
        state::Location& position = playerState.getLocation();
        state::Room& room = static_cast<state::Room&>(position);

        std::vector<state::Door*> roomDoors = room.getDoorList();
        std::vector<state::Door*> allDoors;


        auto roomList = map.getRoomList();
        std::vector<state::Room> roomsToGo;

        // DISJONCTION DE CAS

        // ON A DEJA TROUVE LA PIECE DU MEURTRE

        if (std::find(knownRooms.begin(), knownRooms.end(), 3) != knownRooms.end()) {
            for (int i = 0; i < knownRooms.size(); i++) {
                if (knownRooms.at(i) == 1 or knownRooms.at(i)==3) {
                    roomsToGo.emplace_back(roomList.at(i));
                }
            }
        }
        else {  // ON N A PAS TROUVE LA PIECE DU MEURTRE

            for (int i = 0; i < knownRooms.size(); i++) {
                if (knownRooms.at(i) == 0) {
                    roomsToGo.emplace_back(roomList.at(i));
                }
            }
        }

        if (roomsToGo.size()==1) {
            roomsToGo = roomList;
        }



        // RETIRER LES SALLES DEJA EXPLOREES





        for (long unsigned int i = 0; i < roomsToGo.size(); ++i) {
            auto currentRoom = roomsToGo.at(i);
            if (currentRoom.getRoomName() != room.getRoomName()) {
                std::vector<state::Door*> &roomDoors2 = currentRoom.getDoorList();
                allDoors.insert(allDoors.end(), roomDoors2.begin(), roomDoors2.end());
            }
        }

        std::vector<std::tuple<int, state::Door*, state::Door*>> distance;

        for (long unsigned i = 0; i<roomDoors.size();i++) {
            for (long unsigned j = 0; j<allDoors.size();j++) {
                state::Door* door1 = roomDoors.at(i);
                state::Door* door2 = allDoors.at(j);
                distance.push_back(std::make_tuple(distanceBetweenTwoCells(*door1,*door2), door1, door2));
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
            for (long unsigned i = 1; i<distance.size(); i++) {
                if (std::get<0>(distance.at(i))<min) {
                    min = std::get<0>(distance.at(i));
                    index = i;
                }
            }
            doorDestination = std::get<2>(distance[index]);
            return *std::get<1>(distance[index]);
        }
        throw std::runtime_error("error");
    }

    void MediumAI::getDiceResult(int result, const state::PlayerState &player) {

        for (auto& row : distanceMatrix) {
            std::fill(row.begin(), row.end(), -1);
        }

        if (playerState.getIdentity() == player.getIdentity()) {
            previousDiceResult = result;
        }

        auto& target = static_cast<state::Cell &>(*doorDestination);

        // POSITION ARRIVEE
        int targetY = target.getY();
        int targetX = target.getX();

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

        distanceMatrix[targetY][targetX] = 0;

        std::vector<std::pair<int, int>> toExplore;
        toExplore.push_back({targetY, targetX});
        // TROUVER LES DISTANCES AVEC TOUTES LES CELLULES
        while (!toExplore.empty()) {
            auto [currentY, currentX] = toExplore.back();
            toExplore.pop_back();
            // CHECK LES VOISINS
            std::vector<state::LocationType> neighbors = map.getNeighborsAsLocationType(currentX, currentY);

            for (size_t i = 0; i < directions.size(); i++) {
                int nextY = currentY + directions[i].second;
                int nextX = currentX + directions[i].first;


                // CHECK LE TYPE DES CELLULES + LIMITES MAP
                if (nextX >= 0 && nextY >= 0 && nextX < mapWidth && nextY < mapHeight &&
                    neighbors[i] != state::ROOM &&
                    neighbors[i] != state::INACCESSIBLE) {
                    if (distanceMatrix[nextY][nextX] < 0 || distanceMatrix[nextY][nextX] > distanceMatrix[currentY][currentX] + 1) {
                        distanceMatrix[nextY][nextX] = distanceMatrix[currentY][currentX] + 1;
                        toExplore.push_back({nextY, nextX});
                    }
                    }
            }
        }

    }

    void MediumAI::startOfTheGame() {

        // PARTIE MISE A JOUR DE doorDestination

        // RECUPERER TOUTES LES PORTES DU JEU
        std::vector<state::Door*> allDoors;
        for (int i = 0; i < 9; i++) {
            auto RoomList = map.getRoomList();
            auto currentRoom = RoomList.at(i);
            std::vector<state::Door*> roomDoors = currentRoom.getDoorList();
            allDoors.insert(allDoors.end(), roomDoors.begin(), roomDoors.end());
        }

        std::vector<std::tuple<int, state::Door*>> distance;

        // CALCULER TOUTES LES DISTANCES ENTRE LA POSITION DU JOUEUR ET LES PORTES
        for (long unsigned i = 0; i<allDoors.size();i++) {

            auto& positionPlayerPtr = static_cast<state::Cell&>(playerState.getLocation());

            state::Door* door2 = allDoors.at(i);
            auto* door2CellPtr = static_cast<state::Cell *>(door2);  // transforme en cellule pour calculer la distance
            state::Cell& cell2 = *door2CellPtr;


            distance.push_back(std::make_tuple(distanceBetweenTwoCells(positionPlayerPtr,cell2), door2));
        }


        int min = std::get<0>(distance.at(0));
        int index = 0;
        for (long unsigned i = 1; i<distance.size(); i++) {
            if (std::get<0>(distance.at(i))<min) {
                min = std::get<0>(distance.at(i));
                index = i;
            }
        }
        doorDestination = std::get<1>(distance[index]);


        // PARTIE MISE A JOUR DES ARRAYS KNOWN

        auto suspectCards = playerState.getSuspectCards();
        auto weaponCards = playerState.getWeaponCards();
        auto roomCards = playerState.getRoomCards();

        for (long unsigned i = 0; i<suspectCards.size();i++) {
            int suspect = suspectCards.at(i).getSuspectName();
            knownSuspects.at(suspect-1) = 1;
        }
        for (long unsigned i = 0; i<weaponCards.size();i++) {
            int weapon = weaponCards.at(i).getWeaponName();
            knownWeapons.at(weapon-1) = 1;
        }
        for (long unsigned i = 0; i<roomCards.size();i++) {
            int room = roomCards.at(i).getRoomName();
            knownRooms.at(room-1) = 1;
        }

        // INITIALISATION DE LA MATRICE QUI VA SUIVRE QUELLE CARTE EST MONTREE A QUI
        // INUTILE POUR EASYAI ET MEDIUMAI

    }

}

