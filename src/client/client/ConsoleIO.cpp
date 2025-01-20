//
// Created by louismmassin on 1/7/25.
//
#include "ConsoleIO.h"

#include <iostream>
#include <vector>

#include "Player.h"
#include "state/Suspect.cpp"
#include "state/Weapon.cpp"
#include "state/RoomName.cpp"

namespace client {
    ConsoleIO::ConsoleIO() {

    }

    void ConsoleIO::updateIO() {

    }


    int ConsoleIO::getValidKey(int max) {
        try{
            std::string playerKey;
            std::cin >> playerKey;
            int keyVal = stoi(playerKey);
            if(keyVal > 0 && keyVal <= max){
                return keyVal;
            }
            std::cout << "Invalid key" << std::endl;
            return getValidKey(max);
        }
        catch(const std::exception& e){
            std::cout << "Invalid key" << std::endl;
            return getValidKey(max);
        }
    }


    int ConsoleIO::introductionToTheGame() {
        int numberOfPlayers;
        std::cout << "You're playing cluedo." << std::endl;
        std::cout << "Mr LENOIR died in is house this night." << std::endl;
        std::cout << "You will have to find the murderer." << std::endl;
        std::cout << "How many detectives are you ?" << std::endl;
        std::cin >> numberOfPlayers;
        while (numberOfPlayers < 3 or numberOfPlayers > 6){
            std::cout << "You have to be between 3 and 6 players to play CLUEDO." <<  std::endl << "How many detectives are you ?" << std::endl;
            std::cin >> numberOfPlayers;
        }
        std::cout << "Good Luck for your investigation! " << std::endl;
        return numberOfPlayers;
    }

    void ConsoleIO::diceThrow() {

        std::cout << "Press 1 to throw the dice ! " << std::endl;
        getValidKey(1);
        std::cout << "Dice are thrown" << std::endl;
    }

    void ConsoleIO::updatePlayerPositions() {
        auto displayMap = map->getDisplayMap();
        for (const auto& row: displayMap) {
            for (const auto& element: row) {
                if (element == "X" or element == " " or element == "|" or element == "~") {
                    std::cout << element;
                }
                else if (element == "D") {
                    std::cout << "\033[32m" << element << "\033[0m";
                }
                else {
                    std::cout << "\033[34m" << element << "\033[0m";
                }
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }


    void ConsoleIO::displayHypothesis(const Player &player, const state::TripleClue &hypothesis) {
        std::cout << player.getName() << " suggests the crime was committed by "
                << hypothesis.suspect << " in the " << hypothesis.room
                << " with the " << hypothesis.weapon << "!" << std::endl;    }

    void ConsoleIO::displayAccusation(const Player &player, const state::TripleClue &accusation) {
        std::cout << player.getName() << " is accusing " << accusation.suspect << " with the " << accusation.weapon << " in the " << accusation.room << "!"<<std::endl;
    }

    void ConsoleIO::displayGameEnd(const Player &winner) {
        std::cout << winner.getName() << " won the game !" << std::endl;
    }

    void ConsoleIO::seeHypothesisResponse(PlayerList& playerList, const state::TripleClue &hypothesis, const Player &askedPlayer, bool response) {
        if (response) {
            std::cout << askedPlayer.getName() << " showed a card " << std::endl;
        }
        else {
            std::cout << askedPlayer.getName() << " didn't show a card " << std::endl;
        }
        IO::seeHypothesisResponse(playerList, hypothesis, askedPlayer, response);
    }

    void ConsoleIO::displayDiceResult(PlayerList &playerList, int result, const Player &player) {
        IO::displayDiceResult(playerList, result, player);
        std::cout << player.getName() << " threw the dice and got " << result << "!" << std::endl;
    }

    void ConsoleIO::setMap(const state::Map &map) {
        this->map = &map;
    }





}
