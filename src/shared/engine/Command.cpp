//
// Created by louismmassin on 12/16/24.
//
#include "Command.h"
namespace engine {
    Command::Command(Engine& engine, CommandId id, state::PlayerInfo &player): engine(engine), id(id), player(player) {

    }

    CommandId Command::getCommandId(){
        return id;
    }

    void Command::execute() {

    }


}