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
	Client::Client (state::State& state, engine::Engine& engine, std::unique_ptr<IO>& io, std::vector<std::unique_ptr<client::Player>>& playerVec): state(state), engine(engine), io(std::move(io)), playerList(playerVec)
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
		/*
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
		*/
	}

    void Client::determinePlayerSuspect()
    {
		/*
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
		*/
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

	void Client::displayPressKey(std::string key){

		std::cout << " press " << key << " " << std::endl;
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

	engine::Engine &Client::getEngine() {
		return engine;
	}

	PlayerList &Client::getPlayerList() {
		return playerList;
	}

	void Client::askHypothesisToNeighbors(Player &hypothesisPlayer, state::TripleClue hypothesis) {
		const auto& itCurrent = playerList.getIterator();
		auto it = itCurrent;
		playerList.incrementIterator(it);
		while (it != itCurrent) {
			auto& player = **it;
			std::vector<const state::Card*> possessedCards = engine.getPossessedCards(hypothesis, player.getPlayerState());
			if (!possessedCards.empty()) {
				int chosenIndex = player.chooseACardToShowPlayer(possessedCards,player);
				hypothesisPlayer.seeACardFromPlayer(*possessedCards.at(chosenIndex), player);
				break;
			}
			std::cout << player.getName() << " has nothing to show to " << hypothesisPlayer.getName() << std::endl;
			playerList.incrementIterator(it);
		}
	}

	IO &Client::getIO() {
		return *io;
	}

}