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
    Engine::Engine(state::State &state): state(state), playerStateVec(state.getPlayerStateVec()), map(state.getMap()), envelope(state.getEnvelope()), currentPlayer(playerStateVec.begin()) {
    }

    int Engine::determineFirstPlayer() {
        int firstPlayerIndex = UtilityFunctions::randomInt(playerStateVec.size());
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

        int remainingSuspects = 6;
        int remainingWeapons = 6;
        int remainingRooms = 9;
        auto it = getIterator();
        for (int i = remainingSuspects + remainingWeapons + remainingRooms; i > 0; i--) {
            const int randomIndex = UtilityFunctions::randomInt(remainingSuspects + remainingWeapons + remainingRooms);
            if (randomIndex < remainingSuspects) {
                it->addSuspectCard(suspectCardsVector.at(randomIndex));
                suspectCardsVector.erase(suspectCardsVector.begin() + randomIndex);
                remainingSuspects--;
            }
            else if (randomIndex < remainingSuspects + remainingWeapons) {
                it->addWeaponCard(weaponCardsVector.at(randomIndex - remainingSuspects));
                weaponCardsVector.erase(weaponCardsVector.begin() + randomIndex - remainingSuspects);
                remainingWeapons--;
            }
            else {
                it->addRoomCard(roomCardsVector.at(randomIndex - remainingSuspects - remainingWeapons));
                roomCardsVector.erase(roomCardsVector.begin() + randomIndex - remainingSuspects - remainingWeapons);
                remainingRooms--;
            }
            incrementIterator(it);
        }
    }

    void Engine::distributionCharacters () {
        const int numberOfPlayer = playerStateVec.size();
        const std::vector<state::Suspect> SuspectsVector = {state::ROSE,state::PERVENCHE, state::LEBLANC, state::OLIVE, state::MOUTARDE, state::VIOLET} ;
        auto it = getIterator(); //iterateur initialisé au joueur actuel
        for (int i = 0; i < numberOfPlayer; i++) {
            it->setIdentity(SuspectsVector.at(i));
            state::Cell& startingCell = state.convertSuspectToStartingCell(SuspectsVector.at(i));
            it->setLocation(startingCell);
            incrementIterator(it);
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

    std::vector<const state::Card*> Engine::getPossessedCards (state::TripleClue inputClues, state::PlayerState& player) const{
        std::vector<const state::Card*> possessedCards;
        const auto& suspectCards = player.getSuspectCards();
        for (const state::SuspectCard& card : suspectCards) {
            if (card.getSuspectName() == inputClues.suspect) {
                possessedCards.push_back(&card);
            }
        }
        const auto& weaponCards = player.getWeaponCards();
        for (const state::WeaponCard& card: weaponCards) {
            if (card.getWeaponName() == inputClues.weapon) {
                possessedCards.push_back(&card);
            }
        }
        const auto& roomCards = player.getRoomCards();
        for (const state::RoomCard& card: roomCards) {
            if (card.getRoomName() == inputClues.room) {
                possessedCards.push_back(&card);
            }
        }

        return possessedCards;
    }

    state::Card Engine::showCard (std::vector<state::Card> cards, int index) {
        return cards.at(index);
    }


    std::vector<engine::CommandId> Engine::getPossibleActions (const state::PlayerState& player) const {
        std::vector<engine::CommandId> possibleCommands;
        // Si c'est ton tour)
        if (&player == &(*currentPlayer)) {

            // Si tu es dans une salle
            if (player.getLocation().getType()== state::ROOM) {
                const auto& currentRoom = dynamic_cast<const state::Room&>(player.getLocation());
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

    std::vector<Move> Engine::getPossibleMoves(const state::PlayerState &player) const{
        std::vector<Move> possibleMoves;
        const state::Location& playerLocation = player.getLocation();
        switch (playerLocation.getType()) {
            case state::CORRIDOR: {
                const auto& playerCell = dynamic_cast<const state::Cell&>(playerLocation);
                const auto& neighbourList = state.getMap().getNeighborsAsCell(playerCell.getX(), playerCell.getY());
                for (int i = 0; i < (int)neighbourList.size(); i++) {
                    const state::LocationType type = neighbourList.at(i)->getType();
                    if ((type == state::CORRIDOR or type == state::DOOR) and !neighbourList.at(i)->getOccupied()) {
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
                const auto& playerCell = dynamic_cast<const state::Cell&>(playerLocation);
                const auto& neighbourList = state.getMap().getNeighborsAsLocationType(playerCell.getX(), playerCell.getY());
                for (unsigned long i = 0; i < neighbourList.size(); i++) {
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

    state::TripleClue Engine::getEnvelope() const {
        return envelope;
    }

    state::State &Engine::getState() {
        return state;
    }

    state::PlayerState &Engine::getCurrentPlayer() {
        return *currentPlayer;
    }

    void Engine::setCurrentPlayer(state::PlayerState &player) {
        currentPlayer = std::find_if(playerStateVec.begin(), playerStateVec.end(), [&player](const auto& i) {
            return &i == &player;
        });
        if (currentPlayer == playerStateVec.end()) {
            throw std::runtime_error("element not found in vector");
        }
    }

    state::Location& Engine::convertMoveToLocation(const Move move) {
        state::Location& playerLoc = currentPlayer->getLocation();
        if (move == ENTER_ROOM && playerLoc.getType() == state::DOOR) {
            auto& playerDoor = dynamic_cast<state::Door&>(playerLoc);
            return *playerDoor.getRoom();
        }
        if (move!= ENTER_ROOM && move != EXIT_ROOM && (playerLoc.getType() == state::DOOR || playerLoc.getType() == state::CORRIDOR)) {
            auto& playerCell = dynamic_cast<state::Cell&>(playerLoc);
            auto neighborList = state.getMap().getNeighborsAsCell(playerCell.getX(), playerCell.getY());
            if (move == MOVE_UP) {
                return *neighborList.at(0);
            }
            if (move == MOVE_DOWN) {
                return *neighborList.at(1);
            }
            if (move == MOVE_LEFT) {
                return *neighborList.at(2);
            }
            if (move == MOVE_RIGHT) {
                return *neighborList.at(3);
            }
        }
        throw std::invalid_argument("invalid move relative to player's location type");
    }

    std::vector<state::PlayerState>::iterator Engine::getIterator() {
        return currentPlayer;
    }

    void Engine::incrementIterator(std::vector<state::PlayerState>::iterator &it) {
        ++it;
        if (it == playerStateVec.end()) {
            it = playerStateVec.begin();
        }
    }


}











