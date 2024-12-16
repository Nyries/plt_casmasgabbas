//
// Created by louismmassin on 12/16/24.
//
#include "AccusationCommand.h"
namespace engine{
    AccusationCommand::AccusationCommand(state::PlayerInfo &player, std::vector<int> &accusation): Command(ACCUSATION, player), accusation(move(accusation)) {

    }

}