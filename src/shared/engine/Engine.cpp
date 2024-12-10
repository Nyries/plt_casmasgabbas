//
// Created by louismmassin on 11/18/24.
//
#include <iostream>
#include "state.h"
#include "engine.h"
#include <tuple>
#include <algorithm>

namespace engine {
    Engine::Engine(state::State &state): state(state), playerList(state.getPlayerList()), map(state.getMap()), currentPlayer(playerList->getCurrent()), envelope(state.getEnvelope()) {
    }

    /// refaire cette fonction en changeant: hasard du premier joueur puis jump à lui, liste des joueurs déjà existante
    /// c'est pas le deuxième qui à le meilleur score qui joue en deuxième

    std::vector<std::tuple<std::string, int,int>> Engine::determinePlayerOrder(std::vector<std::tuple<std::string, int, int>> players, int numberOfPlayers)
    {
        for (int i=0; i<numberOfPlayers; i++){
            std::vector<int> diceValues = dice();
            int sumDice = diceValues.at(0) + diceValues.at(1);
            players.at(i) = std::make_tuple(std::get<0>(players.at(i)), sumDice, 0);
        }
        std::sort(players.begin(), players.end(), [](const std::tuple<std::string, int, int>& a, const std::tuple<std::string, int, int>& b) {
            return std::get<1>(b) < std::get<1>(a);
        });
        return players;
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


        int randomSuspect = UtilityFunctions::randomInt(5);
        int randomWeapon = UtilityFunctions::randomInt(5);
        int randomRoom = UtilityFunctions::randomInt(8);

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
            playerList->getCurrent().giveCard(allCards.at(randomIndex));
            allCards.erase(allCards.begin()+randomIndex);
            playerList->next();
        }
    }

    void Engine::distributionCharacters () {
        const int numberOfPlayer = playerList->size();
        const std::vector<state::Suspect> SuspectsVector = {state::VIOLET, state::ROSE,state::PERVENCHE, state::LEBLANC, state::OLIVE, state::MOUTARDE} ;
        state::PlayerInfo* currentPlayer = &playerList->getCurrent();
        int players = 1;
        while (players!=numberOfPlayer+1) {
            currentPlayer->setIdentity(SuspectsVector.at(players));
            playerList->next();
            currentPlayer = &playerList->getCurrent();
            players++;
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

    std::vector<state::Card*> Engine::getPossessedCards (std::vector<state::Card> cards) {
        playerList->getCurrent();
        int askedPlayers = 0;
        std::vector<state::Card*> possessedCards = {};

        while (possessedCards.empty()){

            playerList->next();
            state::PlayerInfo& askedPlayer = playerList->getCurrent();

            for (auto & i : askedPlayer.getCards()) {

                if (i.getType() == state::SUSPECT_CARD) {
                    if(i.getSuspectName()== cards.at(0).getSuspectName()) {
                        possessedCards.push_back(&cards.at(0));
                    }
                }

                else if (i.getType() == state::WEAPON_CARD) {
                    if(i.getWeaponName()== cards.at(1).getWeaponName()) {
                        possessedCards.push_back(&cards.at(1));
                    }
                }

                else if (i.getType() == state::ROOM_CARD) {
                    if(i.getRoomName()== cards.at(2).getRoomName()) {
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

            }

        }

    state::Card Engine::showCard (std::vector<state::Card> cards, int index) {
        return cards.at(index);

    }


    }











