//
// Created by bastien on 04/12/24.
//

#include "state.h"
//#include "engine.h"
#include "MoveCommand.h"

#include <iostream>
#include <algorithm>

namespace engine {
    MoveCommand::MoveCommand(state::PlayerInfo &player, int direction) {
        state::Location &currentLocation = player.getLocation();
        if (currentLocation.getType() != state::CORRIDOR) {
            throw std::invalid_argument("La position du joueur n'est pas de type 'Cell'");
        }
        auto *currentCell = static_cast<state::Cell*>(&currentLocation);
        if (!currentCell) {
            throw std::invalid_argument("Current location is not of type 'Cell'.");
        }
        int x = currentCell->getCoordX();
        int y = currentCell->getCoordY();

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
        currentCell->setCoordX(x);
        currentCell->setCoordY(y);
        player.setLocation(*currentCell);
    }

    void engine::MoveCommand::execute() {
        Command::execute();
    }
}