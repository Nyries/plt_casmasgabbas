//
// Created by louismmassin on 12/16/24.
//
#include <iostream>
#include "state.h"
#include "SecretPassageCommand.h"
namespace engine {
    SecretPassageCommand::SecretPassageCommand(Engine &engine, state::PlayerInfo &player): Command(engine, SECRET_PASSAGE, player) {

    }

    void SecretPassageCommand::execute() {  // Normalement c'est ok
        state::Location &currentLocation = player.getLocation();
        if (currentLocation.getType() != state::ROOM) {
            throw std::invalid_argument("Invalid player's starting position");
        }

        state::Room *secretPassage = static_cast<state::Room &>(player.getLocation()).getSecretPassage();
        player.setLocation(*secretPassage);

    }


}