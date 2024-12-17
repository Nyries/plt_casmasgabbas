//
// Created by louismmassin on 12/16/24.
//

#include <iostream>
#include "state.h"
#include "MoveCommand.h"
namespace engine {
    MoveCommand::MoveCommand(Engine &engine, state::PlayerInfo &player, Move direction): Command(engine, ACCUSATION, player), direction(direction) {

    }
    
    void MoveCommand::execute() {
        state::Location &currentLocation = player.getLocation();
        if (currentLocation.getType() != state::CORRIDOR) {
            throw std::invalid_argument("Invalid player's starting position");
        }
        auto *currentCell = static_cast<state::Cell*>(&currentLocation);
        int x = currentCell->getX();
        int y = currentCell->getY();

        switch (direction) {
            case MOVE_UP:
                y -= 1;
                break;
            case MOVE_RIGHT:
                x += 1;
                break;
            case MOVE_DOWN:
                y += 1;
                break;
            case MOVE_LEFT:
                x -= 1;
                break;
            default:
                throw std::invalid_argument("Valeur de direction invalide.");
        }

        currentCell->setX(x);
        currentCell->setY(y);

        player.setLocation(*currentCell);
    }
}