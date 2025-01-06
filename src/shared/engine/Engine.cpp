//
// Created by louismmassin on 11/18/24.
//
#include "Engine.h"

#include <iostream>
#include "state.h"
#include "engine.h"
#include <tuple>
#include <algorithm>

namespace engine {
    Engine::Engine(state::State &state): state(state), playerInfoVec(state.getPlayerInfoVec()), map(state.getMap()), envelope(state.getEnvelope()), currentPlayer(playerInfoVec) {
    }

    int Engine::determineFirstPlayer() {
        int firstPlayerIndex = UtilityFunctions::randomInt(playerInfoVec.size());
        return firstPlayerIndex;
    }

    void Engine::dealCards() {

        std::vector<state::SuspectCard> suspectCardsVector;
        std::vector<state::WeaponCard> weaponCardsVector;
        std::vector<state::RoomCard> roomCardsVector;

        // VECTOR OF SUSPECTS
        suspectCardsVector.emplace_back(state::VIOLET);
        suspectCardsVector.emplace_back(state::ROSE);
        suspectCardsVector.emplace_back(state::PERVENCHE);
        suspectCardsVector.emplace_back(state::LEBLANC);
        suspectCardsVector.emplace_back(state::OLIVE);
        suspectCardsVector.emplace_back(state::MOUTARDE);

        // VECTOR OF WEAPONS
        weaponCardsVector.emplace_back(state::WRENCH);
        weaponCardsVector.emplace_back(state::CANDLESTICK);
        weaponCardsVector.emplace_back(state::PISTOL);
        weaponCardsVector.emplace_back(state::ROPE);
        weaponCardsVector.emplace_back(state::LEAD_PIPE);
        weaponCardsVector.emplace_back(state::KNIFE);


        // VECTOR OF ROOMS
        roomCardsVector.emplace_back(state::BEDROOM);
        roomCardsVector.emplace_back(state::STUDY);
        roomCardsVector.emplace_back(state::HALL);
        roomCardsVector.emplace_back(state::LIVING_ROOM);
        roomCardsVector.emplace_back(state::DINING_ROOM);
        roomCardsVector.emplace_back(state::KITCHEN);
        roomCardsVector.emplace_back(state::BATHROOM);
        roomCardsVector.emplace_back(state::GARAGE);
        roomCardsVector.emplace_back(state::GAME_ROOM);


        int randomSuspect = UtilityFunctions::randomInt(6);
        int randomWeapon = UtilityFunctions::randomInt(6);
        int randomRoom = UtilityFunctions::randomInt(9);

        envelope.push_back(std::move(suspectCardsVector[randomSuspect]));
        suspectCardsVector.erase(suspectCardsVector.begin()+randomSuspect);

        envelope.push_back(std::move(weaponCardsVector[randomWeapon]));
        weaponCardsVector.erase(weaponCardsVector.begin()+randomWeapon);

        envelope.push_back(std::move(roomCardsVector[randomRoom]));
        roomCardsVector.erase(roomCardsVector.begin()+randomSuspect);


        std::vector<state::Card> allCards;
        allCards.reserve(suspectCardsVector.size()+weaponCardsVector.size()+roomCardsVector.size());

        allCards.insert(allCards.end(), suspectCardsVector.begin(), suspectCardsVector.end());
        allCards.insert(allCards.end(), weaponCardsVector.begin(), weaponCardsVector.end());
        allCards.insert(allCards.end(), roomCardsVector.begin(), roomCardsVector.end());

        while (!allCards.empty()) {
            const int randomIndex = UtilityFunctions::randomInt(allCards.size());
            auto it = playerInfoVec.begin() + randomIndex;
            it->giveCard(allCards.at(randomIndex));
            allCards.erase(allCards.begin()+randomIndex);
        }
    }

    void Engine::distributionCharacters () {
        const int numberOfPlayer = playerInfoVec.size();
        const std::vector<state::Suspect> SuspectsVector = {state::ROSE,state::PERVENCHE, state::LEBLANC, state::OLIVE, state::MOUTARDE, state::VIOLET} ;
        engine::CircularIterator<state::PlayerInfo> it(playerInfoVec, playerInfoVec.begin() + (&getCurrentPlayer() - &playerInfoVec.front())); //iterateur initialisé au joueur actuel
        for (int i = 0; i < numberOfPlayer; i++) {
            it->setIdentity(SuspectsVector.at(i));
            it->setLocation(state.suspectToStartingCell(SuspectsVector.at(i)));
            ++it;
        }
    }

    std::vector<int> Engine::dice () {
        const int die1 = UtilityFunctions::randomInt(5)+1;
        const int die2 = UtilityFunctions::randomInt(5)+1;
        std::vector<int> dice;
        dice.push_back(die1);
        dice.push_back(die2);
        return dice;
    }

    std::vector<state::Card*> Engine::getPossessedCards (state::TripleClue inputClues, state::PlayerInfo& player) {
        std::vector<state::Card*> possessedCards;
        for (auto & i : player.getCards()) {

            if (i.getType() == state::SUSPECT_CARD) {
                auto& castI = static_cast<state::SuspectCard&>(i);
                if(castI.getSuspectName()== inputClues.suspect) {
                    possessedCards.push_back(&i);
                }
            }

            else if (i.getType() == state::WEAPON_CARD) {
                auto& castI = static_cast<state::WeaponCard&>(i);
                if(castI.getWeaponName()== inputClues.weapon) {
                    possessedCards.push_back(&i);
                }
            }

            else if (i.getType() == state::ROOM_CARD) {
                auto& castI = static_cast<state::RoomCard&>(i);
                if(castI.getRoomName()== inputClues.room) {
                    possessedCards.push_back(&i);
                }
            }
        }
        return possessedCards;
    }

    state::Card Engine::showCard (std::vector<state::Card> cards, int index) {
        return cards.at(index);
    }


    std::vector<engine::CommandId> Engine::getPossibleActions (state::PlayerInfo& player) {
        std::vector<engine::CommandId> possibleCommands;

        // Si c'est ton tour
        if (&player == &getCurrentPlayer()) {

            // Si tu es dans une salle
            if (player.getLocation().getType()== state::ROOM) {
                auto& currentRoom = static_cast<state::Room&>(player.getLocation());
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

        if (possibleCommands.empty()) {
            throw std::runtime_error("no possible action found");
        }
        return possibleCommands;
    }

    void Engine::addCommand(std::unique_ptr<Command> newCommand) {
        commands.push_back( std::move(newCommand));
    }

    std::vector<Move> Engine::getPossibleMoves(state::PlayerInfo &player) {
        std::vector<Move> possibleMoves;
        state::Location playerLocation = player.getLocation();
        switch (playerLocation.getType()) {
            case state::CORRIDOR: {
                auto& playerCell = static_cast<state::Cell&>(playerLocation);
                const auto& neighbourList = state.getMap().getNeighborsAsLocationType(playerCell.getX(), playerCell.getY());
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
                const auto& neighbourList = state.getMap().getNeighborsAsLocationType(playerCell.getX(), playerCell.getY());
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
        for (auto& c: commands) {
            c->execute();
        }
        commands.clear();
    }

    std::vector<state::Card> &Engine::getEnvelope() {
        return envelope;
    }

    state::State &Engine::getState() {
        return state;
    }

    state::PlayerInfo &Engine::getCurrentPlayer() {
        return *currentPlayer;
    }

    void Engine::setCurrentPlayer(state::PlayerInfo &player) {
        currentPlayer.setElement(player);
    }



}











