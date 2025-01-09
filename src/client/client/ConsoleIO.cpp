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

    void ConsoleIO::displayMap(const state::Map& map) {
        std::vector<std::vector<std::string>> mapGrid = map.getDisplayMap();
        for (const std::vector<std::string>& row : mapGrid) {
            for (const std::string& cell : row) {
                std::cout << cell;
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    void ConsoleIO::displayHypothesis(const Player &player, const state::TripleClue &hypothesis) {
        std::cout << player.getName() << "suspects " << hypothesis.suspect << " with the " << hypothesis.weapon << " in the " << hypothesis.room << "!"<<std::endl;
    }

    void ConsoleIO::displayAccusation(const Player &player, const state::TripleClue &accusation) {
        std::cout << player.getName() << " is accusing " << accusation.suspect << " with the " << accusation.weapon << " in the " << accusation.room << "!"<<std::endl;
    }

}
