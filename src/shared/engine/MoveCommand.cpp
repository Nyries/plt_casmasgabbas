//
// Created by louismmassin on 12/16/24.
//
#include "MoveCommand.h"
namespace engine {
    MoveCommand::MoveCommand(state::PlayerInfo &player, Move direction): Command(MOVE_FROM_DICE,player), direction(direction) {

    }

}