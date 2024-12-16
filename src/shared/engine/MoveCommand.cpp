//
// Created by louismmassin on 12/16/24.
//

#include <iostream>
#include "state.h"
#include "MoveCommand.h"
namespace engine {
    MoveCommand::MoveCommand(state::PlayerInfo &player, Move direction): Command(MOVE_FROM_DICE,player), direction(direction) {
    }

    void engine::MoveCommand::execute() {
        state::Location &currentLocation = player.getLocation();
        if (currentLocation.getType() != state::CORRIDOR) {
            throw std::invalid_argument("Invalid player's starting position");
        }
        auto *currentCell = dynamic_cast<state::Cell*>(&currentLocation);
        int x = currentCell->getX();
        int y = currentCell->getY();

        switch (direction) {
            case 1: // Haut
                y -= 1;
                break;
            case 2: // Droite
                x += 1;
                break;
            case 3: // Bas
                y += 1;
                break;
            case 4: // Gauche
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