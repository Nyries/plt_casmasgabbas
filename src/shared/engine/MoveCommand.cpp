//
// Created by bastien on 04/12/24.
//

#include "state.h"
//#include "engine.h"
#include "MoveCommand.h"

#include <iostream>
#include <algorithm>

namespace engine {
    MoveCommand::MoveCommand(state::PlayerInfo& player, int direction): Command(MOVE_FROM_DICE, player), direction(direction) {
        state::Location &currentLocation = player.getLocation();
        if (currentLocation.getType() != state::CORRIDOR) {
            throw std::invalid_argument("Current location is not of type 'Cell'.");
        }
        auto *currentCell = static_cast<state::Cell*>(&currentLocation);
        if (!currentCell) {
            throw std::runtime_error("Cast failed");
        }
        int x = currentCell->getX();
        int y = currentCell->getY();

        switch (direction) {
            case 1: // Haut
                y -= 1;
                break;
            case 2: // Gauche
                x -= 1;
                break;
            case 3: // Bas
                y += 1;
                break;
            case 4: // Droite
                x += 1;
                break;
            default:
                throw std::invalid_argument("Valeur de direction invalide.");
        }
        currentCell->setX(x);
        currentCell->setY(y);
        player.setLocation(*currentCell);
    }

    void engine::MoveCommand::execute() {
        state::Location &currentLocation = player.getLocation();
        if (currentLocation.getType() != state::CORRIDOR) {
            throw std::invalid_argument("Invalid player's starting position");
        }
        auto *currentCell = static_cast<state::Cell*>(&currentLocation);
        int x = currentCell->getX();
        int y = currentCell->getY();

    }
}