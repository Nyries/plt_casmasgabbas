//
// Created by louismmassin on 12/16/24.
//

#include <iostream>
#include "state.h"
#include "MoveCommand.h"

#include <algorithm>

#include "Engine.h"
#include "state/LocationType.h"

namespace engine {
    MoveCommand::MoveCommand(Engine &engine, state::PlayerState &player, state::Location& newLocation): Command(engine, player, ACCUSATION), newLocation(newLocation) {

    }
    
    void MoveCommand::execute() {
        state::Location& playerLoc = player.getLocation();
        switch (playerLoc.getType()) {
            case state::CORRIDOR:{
                if (newLocation.getType() == state::CORRIDOR or newLocation.getType() == state::DOOR) {
                    auto& newCell = static_cast<state::Cell&>(newLocation);
                    auto& playerCell = static_cast<state::Cell&>(playerLoc);
                    auto neighborList = engine.getState().getMap().getNeighborsAsCell(playerCell.getX(), playerCell.getY());
                    auto it = std::find_if(neighborList.begin(), neighborList.end(),
                    [&newCell](const state::Cell* i) {
                        return i == &newCell;
                        });
                    if (it!=neighborList.end()) {
                        player.setLocation(newCell);
                    }
                }
                break;
            }
            case state::DOOR: {
                if (newLocation.getType() == state::CORRIDOR or newLocation.getType() == state::DOOR) {
                    auto& newCell = static_cast<state::Cell&>(newLocation);
                    auto& playerCell = static_cast<state::Cell&>(playerLoc);
                    auto neighborList = engine.getState().getMap().getNeighborsAsCell(playerCell.getX(), playerCell.getY());
                    auto it = std::find_if(neighborList.begin(), neighborList.end(),
                    [&newCell](const state::Cell* i) {
                        return i == &newCell;
                        });
                    if (it!=neighborList.end()) {
                        player.setLocation(newCell);
                    }
                }
                if (newLocation.getType() == state::ROOM) {
                    auto& newRoom = static_cast<state::Room&>(newLocation);
                    auto& playerDoor = static_cast<state::Door&>(playerLoc);
                    std::vector<state::Door*>& doorList = newRoom.getDoorList();
                    auto it = std::find_if(doorList.begin(), doorList.end(),
                    [&playerDoor](const state::Door* i) {
                        return i == &playerDoor;
                        });
                    if (it!=doorList.end()) {
                        player.setLocation(newRoom);

                    }
                }
                break;
            }
            case state::ROOM: {
                if (newLocation.getType() == state::DOOR) {
                    auto& playerRoom = static_cast<state::Room&>(playerLoc);
                    auto& newDoor = static_cast<state::Door&>(newLocation);
                    auto doorList = playerRoom.getDoorList();
                    auto it = std::find_if(doorList.begin(), doorList.end(),
                    [&newDoor](const state::Door* i) {
                        return i == &newDoor;
                        });
                    if (it!=doorList.end()) {
                        player.setLocation(newDoor);
                    }
                }
                break;
            }
            default:
                throw std::invalid_argument("invalid player location type");
        }

    }

}