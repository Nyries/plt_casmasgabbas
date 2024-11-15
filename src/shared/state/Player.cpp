//
// Created by louismmassin on 11/8/24.
//
#include "Player.h"
#include "UtilityFunctions.cpp"
#include "Room.cpp"
#include "Cell.h"

namespace state {
    Player::Player(State& currentGame, std::string name, Suspect identity): currentGame(currentGame),
        name(std::move(name)), identity(identity), canWin(true) {
    }

    void Player::movement() {
        int movementValue = UtilityFunctions::randomInt(6) + 1 + UtilityFunctions::randomInt(6) + 1;
        Room* currentRoom = dynamic_cast<Room*>(location);  // nullptr if location isn't Room*
        if (currentRoom) {
            /// to be modified
            Door* selectedDoor = currentRoom->getDoorList()[0];  // selects the first Door from the list
            /// ----
            location = selectedDoor;
        }
        // Movement from a Cell
        Cell* currentCell = dynamic_cast<Cell*>(location);
        for (int i=0; i<movementValue; i++) {
            std::vector<Cell*> adjacentCells = currentCell->getAccessibleCells();  /// to be implemented
            std::vector<Cell*> accessibleCells;

            for (Cell* cell : adjacentCells) {  // Accessible cells
                if ((cell->getType() == LocationType::CORRIDOR || cell->getType() == LocationType::DOOR) && !cell->getOccupied()) {
                    accessibleCells.push_back(cell);
                }
            }
            if (accessibleCells.empty()) break;  // if the player is locked by another player

            /// to be modified
            Cell* nextCell = accessibleCells[0];
            /// ----
            location = nextCell;

            if (Door* door = dynamic_cast<Door*>(nextCell)) {

                break;
            }
        }
    }
}
