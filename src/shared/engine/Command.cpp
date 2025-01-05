//
// Created by louismmassin on 12/16/24.
//
#include "Command.h"
namespace engine {
    Command::Command(Engine& engine, state::PlayerInfo &player, CommandId id): engine(engine), player(player), id(id) {

    }

    CommandId Command::getCommandId(){
        return id;
    }

    void Command::execute() {
        //TODO
    }


}