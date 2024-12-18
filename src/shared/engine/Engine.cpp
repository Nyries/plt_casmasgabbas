//
// Created by louismmassin on 11/18/24.
//
#include <iostream>
#include "state.h"
#include "engine.h"
#include <tuple>
#include <algorithm>

namespace engine {
    Engine::Engine(state::State &state): state(state), playerList(state.getPlayerList()),  currentPlayer(playerList->getCurrent()), map(state.getMap()), envelope(state.getEnvelope()) {
    }

    /// refaire cette fonction en changeant: hasard du premier joueur puis jump à lui, liste des joueurs déjà existante
    /// c'est pas le deuxième qui à le meilleur score qui joue en deuxième


    std::vector<int> Engine::dice () {
        const int die1 = UtilityFunctions::randomInt(5)+1;
        const int die2 = UtilityFunctions::randomInt(5)+1;
        std::vector<int> dice;
        dice.push_back(die1);
        dice.push_back(die2);
        return dice;
    }


    std::vector<state::Card*> Engine::getPossessedCards (std::vector<state::Card> cards) {
        playerList->getCurrent();
        int askedPlayers = 0;
        std::vector<state::Card*> possessedCards;

        while (possessedCards.empty()){

            playerList->next();
            state::PlayerInfo& askedPlayer = playerList->getCurrent();

            for (auto & i : askedPlayer.getCards()) {

                if (i.getType() == state::SUSPECT_CARD) {
                    auto& castI = static_cast<state::SuspectCard&>(i);
                    auto& castCard = static_cast<state::SuspectCard&>(cards.at(0));
                    if(castI.getSuspectName()== castCard.getSuspectName()) {
                        possessedCards.push_back(&cards.at(0));
                    }
                }

                else if (i.getType() == state::WEAPON_CARD) {
                    auto& castI = static_cast<state::WeaponCard&>(i);
                    auto& castCard = static_cast<state::WeaponCard&>(cards.at(1));
                    if(castI.getWeaponName()== castCard.getWeaponName()) {
                        possessedCards.push_back(&cards.at(1));
                    }
                }

                else if (i.getType() == state::ROOM_CARD) {
                    auto& castI = static_cast<state::RoomCard&>(i);
                    auto& castCard = static_cast<state::RoomCard&>(cards.at(2));
                    if(castI.getRoomName()== castCard.getRoomName()) {
                        possessedCards.push_back(&cards.at(2));
                    }
                }

            }

            if (!possessedCards.empty() and askedPlayers != playerList->size()) {
                return possessedCards;
            }

            playerList->next();
            askedPlayers++;

            if (!possessedCards.empty() and askedPlayers == playerList->size()) {
                return possessedCards;

            }

            } return possessedCards;

        }

    state::Card Engine::showCard (std::vector<state::Card> cards, int index) {
        return cards.at(index);

    }


    std::vector<engine::CommandId> Engine::getPossibleActions (state::PlayerInfo& player) {
        std::vector<engine::CommandId> possibleCommands;

        // Si c'est ton tour
        if (&player==&(playerList->getCurrent())) {

            // Si tu es dans une salle
            if (player.getLocation().getType()== state::ROOM) {
                auto& currentRoom = static_cast<state::Room&>(currentPlayer.getLocation());
                // Si tu n'as pas encore fait d'hypotèse
                if (player.getPreviousHypothesisRoom() != currentRoom.getRoomName()) {
                    possibleCommands.push_back(engine::HYPOTHESIS);
                }
                // Si y a un passage secret
                if (currentRoom.getSecretPassage()!= nullptr) {
                    possibleCommands.push_back(engine::SECRET_PASSAGE);
                }
            }
            // on peut toujours se déplacer avec les dés ou faire une accusation
            possibleCommands.push_back(engine::MOVE_FROM_DICE);
            possibleCommands.push_back(engine::ACCUSATION);
        }

        return possibleCommands;
    }

    void Engine::addCommand(Command* newCommand) {
        commands.push_back( newCommand);
    }

    std::vector<Move> Engine::getPossibleMoves(state::PlayerInfo &player) {
        std::vector<Move> possibleMoves;
        state::Location playerLocation = player.getLocation();
        switch (playerLocation.getType()) {
            case state::CORRIDOR: {
                auto& playerCell = static_cast<state::Cell&>(playerLocation);
                const auto& neighbourList = state.getMap()->getNeighborsAsLocationType(playerCell.getX(), playerCell.getY());
                for (int i = 0; i < neighbourList.size(); i++) {
                    const state::LocationType type = neighbourList.at(i);
                    if (type == state::CORRIDOR or type == state::DOOR) {
                        switch (i) {
                            case 0:
                                possibleMoves.push_back(MOVE_UP);
                            break;
                            case 1:
                                possibleMoves.push_back(MOVE_DOWN);
                            break;
                            case 2:
                                possibleMoves.push_back(MOVE_LEFT);
                            break;
                            case 3:
                                possibleMoves.push_back(MOVE_RIGHT);
                            break;
                            default:
                                throw std::runtime_error("switch failed");
                        }
                    }
                }
            }
            break;
            case state::DOOR: {
                possibleMoves.push_back(ENTER_ROOM);
                auto& playerCell = static_cast<state::Cell&>(playerLocation);
                const auto& neighbourList = state.getMap()->getNeighborsAsLocationType(playerCell.getX(), playerCell.getY());
                for (int i = 0; i < neighbourList.size(); i++) {
                    const state::LocationType type = neighbourList.at(i);
                    if (type == state::CORRIDOR or type == state::DOOR) {
                        switch (i) {
                            case 0:
                                possibleMoves.push_back(MOVE_UP);
                            break;
                            case 1:
                                possibleMoves.push_back(MOVE_DOWN);
                            break;
                            case 2:
                                possibleMoves.push_back(MOVE_LEFT);
                            break;
                            case 3:
                                possibleMoves.push_back(MOVE_RIGHT);
                            break;
                            default:
                                throw std::runtime_error("switch failed");
                        }
                    }
                }
            }
            break;
            case state::ROOM: {
                possibleMoves.push_back(EXIT_ROOM);
            }
            break;
            default:
                throw std::runtime_error("switch case failed");
        }
        return possibleMoves;
    }

    void Engine::executeCommands() {
        for (Command* c: commands) {
            c->execute();
        }
        commands.clear();
    }

    void Engine::endTurn() {
        playerList->next();
        currentPlayer = playerList->getCurrent();
    }

    std::vector<state::Card> &Engine::getEnvelope() {
        return envelope;
    }


}