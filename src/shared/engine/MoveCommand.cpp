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
                auto& playerCell = dynamic_cast<state::Cell&>(playerLoc);
                if (newLocation.getType() == state::CORRIDOR or newLocation.getType() == state::DOOR) {
                    auto& newCell = dynamic_cast<state::Cell&>(newLocation);
                    if (!newCell.getOccupied()) {
                        auto neighborList = engine.getState().getMap().getNeighborsAsCell(playerCell.getX(), playerCell.getY());
                        auto it = std::find_if(neighborList.begin(), neighborList.end(),
                        [&newCell](const state::Cell* i) {
                            return i == &newCell;
                            });
                        if (it!=neighborList.end()) {
                            player.setLocation(newCell);
                        }
                    }

                }
                break;
            }
            case state::DOOR: {
                auto& playerDoor = dynamic_cast<state::Door&>(playerLoc);
                if (newLocation.getType() == state::CORRIDOR or newLocation.getType() == state::DOOR) {
                    auto& newCell = dynamic_cast<state::Cell&>(newLocation);
                    if (!newCell.getOccupied()) {
                        auto neighborList = engine.getState().getMap().getNeighborsAsCell(playerDoor.getX(), playerDoor.getY());
                        auto it = std::find_if(neighborList.begin(), neighborList.end(),
                        [&newCell](const state::Cell* i) {
                            return i == &newCell;
                            });
                        if (it!=neighborList.end()) {
                            player.setLocation(newCell);
                        }
                    }

                }
                if (newLocation.getType() == state::ROOM) {
                    auto& newRoom = dynamic_cast<state::Room&>(newLocation);
                    if (newRoom.getRoomName() != player.getPreviousHypothesisRoom()) {
                        std::vector<state::Door*>& doorList = newRoom.getDoorList();
                        auto it = std::find_if(doorList.begin(), doorList.end(),
                        [&playerDoor](const state::Door* i) {
                            return i == &playerDoor;
                            });
                        if (it!=doorList.end()) {
                            player.setLocation(newRoom);
                        }
                    }
                }
                break;
            }
            case state::ROOM: {
                if (newLocation.getType() == state::DOOR) {
                    auto& playerRoom = dynamic_cast<state::Room&>(playerLoc);
                    auto& newDoor = dynamic_cast<state::Door&>(newLocation);
                    if (!newDoor.getOccupied()) {
                        auto doorList = playerRoom.getDoorList();
                        auto it = std::find_if(doorList.begin(), doorList.end(),
                        [&newDoor](const state::Door* i) {
                            return i == &newDoor;
                            });
                        if (it!=doorList.end()) {
                            player.setLocation(newDoor);
                        }
                    }
                }
                break;
            }
            default:
                throw std::invalid_argument("invalid player location type");
        }

    }

}