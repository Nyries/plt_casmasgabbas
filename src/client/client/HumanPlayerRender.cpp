//
// Created by louismmassin on 1/15/25.
//
#include "client/HumanPlayerRender.h"

#include <render/Render.h>

#include "HumanPlayerConsole.h"

namespace client {
    HumanPlayerRender::HumanPlayerRender(engine::Engine &engine, state::PlayerState &playerState, std::string name, render::Render& render): HumanPlayer(engine, playerState, name), render(render){

    }

    void HumanPlayerRender::startOfTheGame() {
        render.startOfTheGame();
    }


    engine::CommandId HumanPlayerRender::chooseAction() {
        return render.chooseAction();
    }

    engine::Move HumanPlayerRender::chooseMoveDirection() {
        return render.chooseMoveDirection();
    }

    state::Door &HumanPlayerRender::chooseDoor(const std::vector<state::Door *> &doorList) {
        return render.chooseDoor(doorList);
    }


    state::TripleClue HumanPlayerRender::chooseHypothesis() {
        return render.chooseHypothesis();
    }

    int HumanPlayerRender::chooseACardToShowPlayer(const std::vector<const state::Card *> &cards, const Player &player) {
        return render.chooseACardToShowPlayer(cards, player);
    }


    void HumanPlayerRender::seeACardFromPlayer(const state::Card &shownCard, const Player &cardOwner) {
        return render.seeACardFromPlayer(shownCard, cardOwner);
    }

    state::TripleClue HumanPlayerRender::chooseAccusation() {
        return render.chooseAccusation();
    }

    void HumanPlayerRender::makePlayerThrowDice() {
        return render.makePlayerThrowDice();
    }

    void HumanPlayerRender::displayDiceResult(int result, const Player &player) {
        return render.displayDiceResult(result, player);
    }

    void HumanPlayerRender::seeHypothesisResponse(const state::TripleClue &hypothesis, const Player &askedPlayer, bool response) {

    }


}
