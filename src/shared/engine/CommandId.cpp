//
// Created by louismmassin on 1/19/25.
//
#include "CommandId.hpp"
namespace engine {
    std::string toString(engine::CommandId action) {
        switch (action) {
            case MOVE_FROM_DICE:
                return "move with the dice";
            case SECRET_PASSAGE:
                return "take the secret passage";
            case HYPOTHESIS:
                return "make a hypothesis";
            case ACCUSATION:
                return "make an accusation";
            case NO_COMMAND:
                return "no action";
        }
    }

}