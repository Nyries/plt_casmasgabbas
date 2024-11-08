//
// Created by louismmassin on 11/8/24.
//
#include "Player.h"
#include "UtilityFunctions.cpp"

namespace state {
    Player::Player(State& currentGame, std::string name, Suspect identity): currentGame(currentGame),
        name(std::move(name)), identity(identity), canWin(true) {
    }

    void Player::movement() {
        int movementValue = UtilityFunctions::randomInt(6) + 1 + UtilityFunctions::randomInt(6) + 1;
        for (int i=0; i<movementValue; i++) {
            Location* startPoint = Player::location;
            if (startPoint->getType() == ROOM) {
                // On laisse le joueur choisir une porte de sortie comme point de départ
            }
            // Puis on se déplace depuis une cellule
            
        }
    }
}