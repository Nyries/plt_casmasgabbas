//
// Created by louismmassin on 12/16/24.
//
#include <iostream>
#include "state.h"
#include "AccusationCommand.h"

#include "Engine.h"

namespace engine{
    AccusationCommand::AccusationCommand(Engine &engine, state::PlayerInfo &player, const state::TripleClue &accusation): Command(engine, player, ACCUSATION), accusation(accusation) , envelope(engine.getEnvelope())  {

    }



    void AccusationCommand::execute () {

        for (int i=0; i<envelope.size();i++) {
            if (accusation.suspect == static_cast<state::SuspectCard&>(envelope.at(0)).getSuspectName() and
                accusation.weapon == static_cast<state::WeaponCard&>(envelope.at(1)).getWeaponName() and
                accusation.room == static_cast<state::RoomCard&>(envelope.at(2)).getRoomName()){

                player.setCanWin(true);
                engine.getState().setAccusationSuccess(true);
            }
        }
        player.setCanWin(false);

    }
}