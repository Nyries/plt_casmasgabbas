//
// Created by cassandre on 13/12/24.
//

#include "state.h"
#include "engine.h"
#include "CommandId.h"

namespace engine {
    // TO DO
    //Command::Command(): id(NO_COMMAND), player(player){}

    CommandId Command::getCommandId () {
        return id;
    }
    //virtual void Command::execute () {}



}