//
// Created by louismmassin on 12/16/24.
//
#include <iostream>
#include "state.h"
#include "AccusationCommand.h"

#include "Engine.h"

namespace engine{
    AccusationCommand::AccusationCommand(Engine &engine, state::PlayerInfo &player, std::vector<int> &accusation): Command(engine, ACCUSATION , player), envelope(engine.getEnvelope())  {
    }



    void AccusationCommand::execute () {

        for (int i=0; i<envelope.size();i++) {
            if (accusation.at(0) == static_cast<state::SuspectCard&>(envelope.at(0)).getSuspectName() and
                accusation.at(1) == static_cast<state::WeaponCard&>(envelope.at(1)).getWeaponName() and
                accusation.at(2) == static_cast<state::RoomCard&>(envelope.at(2)).getRoomName()){

                player.setCanWin(true);
            }
        }
        player.setCanWin(false);

    }
}