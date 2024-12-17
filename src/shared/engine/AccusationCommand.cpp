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


    }


    void AccusationCommand::execute () {    // TO SEE AGAIN

        std::vector<state::Card> cards = player.getCards();
        for (int i=0; i<envelope.size();i++) {
            if (cards.at(0)==envelope.at(0) and cards.at(1)==envelope.at(1) and cards.at(2)==envelope.at(2)) {
                player.setCanWin(true);
            }
        }
        player.setCanWin(false);

    }
}