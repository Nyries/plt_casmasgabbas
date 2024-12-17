//
// Created by louismmassin on 12/16/24.
//
#include "AccusationCommand.h"

#include "Engine.h"

namespace engine{
    AccusationCommand::AccusationCommand(Engine &engine, state::PlayerInfo &player, std::vector<int> &accusation): Command(engine, ACCUSATION , player), envelope(engine.getEnvelope())  {

    }


}
