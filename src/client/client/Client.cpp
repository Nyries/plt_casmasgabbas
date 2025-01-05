//
// Created by cassandre on 18/11/24.
//

#include "client.h"
#include "state.h"
#include "engine.h"

#include <algorithm>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <fstream>
#include <json/json.h>

using namespace std;

namespace client{
	Client::Client (state::State& state, engine::Engine& engine, std::vector<Player*>& playerVec): state(state), engine(engine), playerList(playerVec)
{

	}

	int Client::introductionToTheGame(){
		int numberOfPlayers;
		std::cout << "You're playing cluedo." << std::endl;
		std::cout << "Mr LENOIR died in is house this night." << std::endl;
		std::cout << "You will have to find the murderer." << std::endl;
		std::cout << "How many detectives are you ?" << std::endl;
		std::cin >> numberOfPlayers;
		while (numberOfPlayers < 3 or numberOfPlayers > 6){
			std::cout << "You have to be between 3 and 6 players to play CLUEDO." <<  endl << "How many detectives are you ?" << std::endl;
			std::cin >> numberOfPlayers;
		}
		std::cout << "Good Luck for your investigation! " << std::endl;
		return numberOfPlayers;
	}

	void Client::createParty(int numberOfPlayers){
		string name;
		for (int i=0; i < numberOfPlayers; i++){
			std::cout << "What is the name of player " + std::to_string(i+1) << std::endl;
			cin >> name;
			get<0>(players.at(i)) = name;
		}
		cout << "We are now going to throw the dice to determine the player order" << endl << "Drawing dices..." << endl;
		engine.determineFirstPlayer();

		determinePlayerSuspect();
		cout << "The suspects have been attributed to each player" << endl;
		cout << "Summary of the game creation" << endl;
		for (int i=0; i < numberOfPlayers; i++){
			cout << "Player " << get<0>(players.at(i)) << " is number " << i+1 << " and has suspect " << intToSuspect(get<2>(players.at(i))) << endl;
		}
		//Choosing the suspect

		//choosingSuspect(playerNames, numberOfPlayers);
	}

    void Client::determinePlayerSuspect()
    {
		vector<int> suspectInt;
		for (int i=1; i<=6; i++){
			suspectInt.push_back(i);
		}
		for (int i = 0; i < (int)players.size(); i++)
		{	std::cout << get<0>(players.at(i)) << ", which suspect do you want to be ?" << std::endl;
			if (find(suspectInt.begin(), suspectInt.end(), 1) != suspectInt.end())
			{std::cout << "If you want to be ROSE: press 1 " << std::endl;}
			if (find(suspectInt.begin(), suspectInt.end(), 2) != suspectInt.end())
			{std::cout << "If you want to be PERVENCHE: press 2 " << std::endl;}
			if (find(suspectInt.begin(), suspectInt.end(), 3) != suspectInt.end())
			{std::cout << "If you want to be LEBLANC: press 3 " << std::endl;}
			if (find(suspectInt.begin(), suspectInt.end(), (4)) != suspectInt.end())
			{std::cout << "If you want to be OLIVE: press 4 " << std::endl;}
			if (find(suspectInt.begin(), suspectInt.end(), 5) != suspectInt.end())
			{std::cout << "If you want to be MOUTARDE: press 5 " << std::endl;}
			if (find(suspectInt.begin(), suspectInt.end(), 6) != suspectInt.end())
			{std::cout << "If you want to be VIOLET: press 6 " << std::endl;}

			int choice  = getValidKey(6);
			suspectInt.erase(remove(suspectInt.begin(), suspectInt.end(), choice), suspectInt.end());
			get<2>(players.at(i)) = choice;
		}
	}

    std::string Client::intToSuspect(int input)
    {
		switch (input){
			case 1:
				return "ROSE";
			case 2:
				return "PERVENCHE";
			case 3:
				return "LEBLANC";
			case 4:
				return "OLIVE";
			case 5:
				return "MOUTARDE";
			case 6:
				return "VIOLET";
		}
        return std::string();
    }

	int Client::moveDisplay(std::vector<state::Cell*> accessibleCells){

		std::cout << "Where do you want to go ?" << std::endl;

		int choice = 0;
		std::string moveDirection;

		if (accessibleCells.at(0)!=nullptr){std::cout << "If you to go UP: press 1 " << std::endl;}
		if (accessibleCells.at(1)!=nullptr){std::cout << "If you to go LEFT: press 2 " << std::endl;}
		if (accessibleCells.at(2)!=nullptr){std::cout << "If you to go DOWN: press 3 " << std::endl;}
		if (accessibleCells.at(3)!=nullptr){std::cout << "If you to go RIGHT: press 4  " << std::endl;}

		std::cout << " Choose your direction ! " << std::endl;
		state::Cell* direction = nullptr;

		choice = getValidKey(4);
		direction = accessibleCells.at(choice-1);

		while (direction == nullptr) {
			std::cout << "You can't go there ! Choose another direction" << std::endl;
			choice = getValidKey(4);
			direction = accessibleCells.at(choice-1);
		}

		switch (choice) {
		    case 1: // UP
		        std::cout << "You moved UP ! \n";
		        return 1;
		    case 2: // LEFT
	    		std::cout << "You chose LEFT ! \n";
		        return 2;
		    case 3: // DOWN
	    		std::cout << "You chose DOWN ! \n";
		        return 3;
		    case 4: // RIGHT
		        std::cout << "You chose RIGHT ! \n";
		        return 4;
		    default: // OTHER ONE
		        std::cout << "Invalid choice ! Try again \n";
   		}
			return int();
	}

	void Client::displayPressKey(std::string key){

		std::cout << " press " << key << " " << std::endl;
	}

	int Client::getValidKey(int max){
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
		catch(const exception& e){
			std::cout << "Invalid key" << std::endl;
    		return getValidKey(max);
	    }
	}
  
	void Client::displayMap()
	{
		std::vector<std::vector<std::string>> mapGrid = state.getMap().getDisplayMap();
		for (const std::vector<std::string>& row : mapGrid) {
			for (const std::string& cell : row) {
				std::cout << cell;
			}
			std::cout << std::endl;
		}
	}

	void Client::showMeCardClient (state::Card card) {
		/// Analyse du type de la carte, puis affichage de la carte selon son type
		if (card.getType() == state::SUSPECT_CARD) {
			auto& shownCard = static_cast<state::SuspectCard&>(card);
			std::cout <<  " You show " << shownCard.getSuspectName() << std::endl;
		}
		else if (card.getType() == state::WEAPON_CARD) {
			auto& shownCard = static_cast<state::WeaponCard&>(card);
			std::cout <<  " You show " << shownCard.getWeaponName() << std::endl;
		}
		else {
			auto& shownCard = static_cast<state::RoomCard&>(card);
			std::cout <<  " You show " << shownCard.getRoomName() << std::endl;
		}
	}

	void Client::throwDiceClient () {
		std::cout << "Press 1 to throw the dice ! " << std::endl;
		int keyValue;
		std::cin >> keyValue;
		while (keyValue != 1) {
			std::cout << "Wrong value, press 1 " << std::endl;
		}
		//std::vector<int> diceValues = getEngine().dice();
		std::cout << "Dice are thrown" << std::endl;

		// finir avec lancer les dés et afficher la valeur



		}

	engine::Engine &Client::getEngine() {
		return engine;
	}

	PlayerList &Client::getPlayerList() {
		return playerList;
	}


}