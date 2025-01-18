//
// Created by louismmassin on 1/15/25.
//
#include "client/RenderIO.h"

namespace client {
    RenderIO::RenderIO(): window(sf::VideoMode(800, 600), "Cluedo plt"), render(window) {

    }

    render::Render &RenderIO::getRender() {
        return render;
    }


    void RenderIO::updateIO() {
        render.updateWindow();
    }


    int RenderIO::introductionToTheGame() {
        return render.introductionToTheGame();
    }

    void RenderIO::diceThrow() {
        render.diceThrow();
    }

    void RenderIO::updatePlayerPositions() {
        render.updatePlayerPositions();
    }

    void RenderIO::displayHypothesis(const Player &player, const state::TripleClue &hypothesis) {
        render.displayHypothesis(player, hypothesis);

    }

    void RenderIO::displayAccusation(const Player &player, const state::TripleClue &accusation) {
        render.displayAccusation(player, accusation);
    }

    void RenderIO::displayGameEnd(const Player &winner) {
        render.displayGameEnd(winner);
    }

}