//
// Created by louismmassin on 12/16/24.
//
#include <iostream>
#include "state.h"
#include "AccusationCommand.h"

#include "Engine.h"

namespace engine{
    AccusationCommand::AccusationCommand(Engine &engine, state::PlayerState &player, const state::TripleClue &accusation): Command(engine, player, ACCUSATION), accusation(accusation) , envelope(engine.getEnvelope())  {

    }



    void AccusationCommand::execute () {

        if (accusation.suspect == envelope.suspect
            and accusation.weapon == envelope.weapon
            and accusation.room == envelope.room) {
            player.setCanWin(true);
            engine.getState().setAccusationSuccess(true);
        }
        else {
            player.setCanWin(false);
        }
    }
}