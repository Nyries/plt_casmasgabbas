//
// Created by louismmassin on 12/16/24.
//
#include "HypothesisCommand.h"
namespace engine {
    HypothesisCommand::HypothesisCommand(state::PlayerInfo &player, std::vector<int> &hypothesis): Command(HYPOTHESIS,player), hypothesis(move(hypothesis)) {

    }

    void HypothesisCommand::execute() {

    }

}