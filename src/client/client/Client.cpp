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
	Client::Client(std::string clientJsonPath)
{
		this->clientJsonPath = clientJsonPath;
	    std::ifstream clientJsonFile(clientJsonPath);

		if (!clientJsonFile.is_open()) {
			std::cerr << "Error: could not open file " << clientJsonPath << std::endl;
			return;
		}
        Json::Value clientJsonData;
        clientJsonFile >> clientJsonData;
        clientJsonFile.close();
		state = new state::State(clientJsonData["stateJsonPath"].asString());
		engine = new engine::Engine(*state);
		int numberOfPlayers = introductionToTheGame();
		players = vector<tuple<string, int, int>>(numberOfPlayers, make_tuple("name", 0, 0));
		createParty(numberOfPlayers);
		state->setCircularPlayerList(players);
		playerList = state->getPlayerList();
		currentPlayer = &playerList->getCurrent();
	}

	int Client::introductionToTheGame(){
		int numberOfPlayers;
		std::cout << "You're playing to the cluedo." << std::endl;
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
		//test for the player name well initialized
		/*for (int i=0; i < numberOfPlayers; i++){
			cout << "name : " << get<0>(players.at(i)) << endl;
		}*/
		//Draw for suspect attribution as well as determining first player
		cout << "We are now going to draw the dices to determine the player order" << endl << "Drawing dices..." << endl;
		players = engine->determinePlayerOrder(players, numberOfPlayers);
		//test for the order well
		/*for (int i=0; i < numberOfPlayers; i++){
			cout << "name : " << get<0>(players.at(i)) << ", dice : " << get<1>(players.at(i)) << endl;
		}*/
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
		{
			std::cout << get<0>(players.at(i)) << ", which suspect do you want to be ?" << std::endl;
			if (find(suspectInt.begin(), suspectInt.end(), 1) != suspectInt.end())
			{
				std::cout << "If you want to be VIOLET: press 1 " << std::endl;
			}
			if (find(suspectInt.begin(), suspectInt.end(), 2) != suspectInt.end())
			{
				std::cout << "If you want to be ROSE: press 2 " << std::endl;
			}
			if (find(suspectInt.begin(), suspectInt.end(), 3) != suspectInt.end())
			{
				std::cout << "If you want to be PERVENCHE: press 3 " << std::endl;
			}
			if (find(suspectInt.begin(), suspectInt.end(), 4) != suspectInt.end())
			{
				std::cout << "If you want to be LEBLANC: press 4 " << std::endl;
			}
			if (find(suspectInt.begin(), suspectInt.end(), (5)) != suspectInt.end())
			{
				std::cout << "If you want to be OLIVE: press 5 " << std::endl;
			}
			if (find(suspectInt.begin(), suspectInt.end(), 6) != suspectInt.end())
			{
				std::cout << "If you want to be MOUTARDE: press 6 " << std::endl;
			}


			int choice;
			std::string stringNumber;
			std::cin >> stringNumber;
			choice = stoi(stringNumber);
			while (choice < 1 or choice > 6 or find(suspectInt.begin(), suspectInt.end(), choice) == suspectInt.end())
			{
				std::cout << "Invalid choice, try again" << std::endl;
				std::cin >> stringNumber;
				choice = stoi(stringNumber);
			}
			suspectInt.erase(remove(suspectInt.begin(), suspectInt.end(), choice), suspectInt.end());
			get<2>(players.at(i)) = choice;
		}
	}

    std::string Client::intToSuspect(int input)
    {
		switch (input){
			case 1:
			return "VIOLET";
			case 2:
				return "ROSE";
			case 3:
				return "PERVENCHE";
			case 4:
				return "LEBLANC";
			case 5:
				return "OLIVE";
			case 6:
				return "MOUTARDE";

		}
        return std::string();
    }

    std::vector<int> Client::chooseHypothesis(){
    std::vector<int> hypothesisChoice;
    std::cout << "You want to make an hypothesis ! " << std::endl;
    int choice;
    std::string stringNumber;
	std::cout << "If you are suspecting VIOLET: press 1 " << std::endl;
    std::cout << "If you are suspecting ROSE: press 2 " << std::endl;
	std::cout << "If you are suspecting PERVENCHE: press 3 " << std::endl;
	std::cout << "If you are suspecting LEBLANC: press 4 " << std::endl;
	std::cout << "If you are suspecting OLIVE: press 5 " << std::endl;
	std::cout << "If you are suspecting MOUTARDE: press 6 " << std::endl;



    bool validChoice = true;

    std::cin >> stringNumber;
	choice = convertToInteger(stringNumber);

    while (validChoice) {
      	switch (choice) {
      		case 1: // VIOLET
      			std::cout << "You chose VIOLET ! \n";
      			hypothesisChoice.push_back(state::VIOLET);
      			break;

	    	case 2: // ROSE
	        	std::cout << "You chose ROSE ! \n";
	        	hypothesisChoice.push_back(state::ROSE);
	       	 	break;

	    	case 3: // PERVENCHE
	        	std::cout << "You chose PERVENCHE ! \n";
	        	hypothesisChoice.push_back(state::PERVENCHE);
	        	break;
	    	case 4: // LEBLANC
	        	std::cout << "You chose LEBLANC ! \n";
	        	hypothesisChoice.push_back(state::LEBLANC);
	        	break;
	    	case 5: // OLIVE
	        	std::cout << "You chose OLIVE ! \n";
	        	hypothesisChoice.push_back(state::OLIVE);
	        	break;
	    	case 6: // MOUTARDE
	        	std::cout << "You chose MOUTARDE ! \n";
	        	hypothesisChoice.push_back(state::MOUTARDE);
	        	break;


	    	default: // OTHER ONE
	        	std::cout << "Invalide choice ! Try again \n";
                validChoice = false;
    	}
    }


    std::cout << "With which weapon ? " << std::endl;
    int choice2;
    std::string stringNumber2;
	std::cout << "If you think it is WRENCH: press 1 " << std::endl;
    std::cout << "If you think it is CANDLESTICK: press 2 " << std::endl;
	std::cout << "If you think it is PISTOL: press 3 " << std::endl;
	std::cout << "If you think it is ROPE: press 4 " << std::endl;
	std::cout << "If you think it is LEAD_PIPE: press 5 " << std::endl;
	std::cout << "If you think it is KNIFE: press 6 " << std::endl;


    bool validChoice2 = true;

    while (validChoice2){

		std::cin >> stringNumber2;
		choice2 = convertToInteger(stringNumber2);

		switch (choice2) {
			case 1: // WRENCH
				std::cout << "You chose WRENCH ! \n";
				hypothesisChoice.push_back(state::WRENCH);
				break;
	    	case 2: // CANDLESTICK
	        	std::cout << "You chose CANDLESTICK ! \n";
	        	hypothesisChoice.push_back(state::CANDLESTICK);
	        	break;
	   		 case 3: // PISTOL
	        	std::cout << "You chose PISTOL ! \n";
	        	hypothesisChoice.push_back(state::PISTOL);
	        	break;
	    	case 4: // ROPE
	        	std::cout << "You chose ROPE ! \n";
	       	 	hypothesisChoice.push_back(state::ROPE);
	        	break;
	    	case 5: // LEAD_PIPE
	        	std::cout << "You chose LEAD_PIPE ! \n";
	        	hypothesisChoice.push_back(state::LEAD_PIPE);
	       	 	break;
	    	case 6: // KNIFE
	        	std::cout << "You chose KNIFE ! \n";
	        	hypothesisChoice.push_back(state::KNIFE);
	        	break;


	    	default: // OTHER ONE
	        	std::cout << "Invalide choice ! Try again \n";
	        	validChoice2 = false;
    	}

    }

	auto& currentRoom = static_cast<state::Room&>(currentPlayer->getLocation());
    hypothesisChoice.push_back(currentRoom.getRoomName());

    std::cout << currentPlayer->getIdentity() << " suggests the Crime was committed by "
    << hypothesisChoice.at(0) << " in the " << hypothesisChoice.at(2)
    << " with the " << hypothesisChoice.at(1) << std::endl;

    return hypothesisChoice;
 }


std::vector<int> Client::chooseAccusation(void){

    std::vector<int> accusationChoice;
    std::cout << "You want to make an accusation ! " << std::endl;
    int choice;
    std::string stringNumber;
	std::cout << "If you are accusating VIOLET: press 1 " << std::endl;
    std::cout << "If you are accusating ROSE: press 2 " << std::endl;
	std::cout << "If you are accusating PERVENCHE: press 3 " << std::endl;
	std::cout << "If you are accusating LEBLANC: press 4 " << std::endl;
	std::cout << "If you are accusating OLIVE: press 5 " << std::endl;
	std::cout << "If you are accusating MOUTARDE: press 6 " << std::endl;



	bool validChoice = true;

	std::cin >> stringNumber;
	choice = convertToInteger(stringNumber);

	while (validChoice) {
		switch (choice) {
			case 1: // VIOLET
				std::cout << "You chose VIOLET ! \n";
				accusationChoice.push_back(state::VIOLET);
				break;
			case 2: // ROSE
				std::cout << "You chose ROSE ! \n";
			accusationChoice.push_back(state::ROSE);
			break;
			case 3: // PERVENCHE
				std::cout << "You chose PERVENCHE ! \n";
			accusationChoice.push_back(state::PERVENCHE);
			break;
			case 4: // LEBLANC
				std::cout << "You chose LEBLANC ! \n";
			accusationChoice.push_back(state::LEBLANC);
			break;
			case 5: // OLIVE
				std::cout << "You chose OLIVE ! \n";
			accusationChoice.push_back(state::OLIVE);
			break;
			case 6: // MOUTARDE
				std::cout << "You chose MOUTARDE ! \n";
			accusationChoice.push_back(state::MOUTARDE);
			break;


			default: // OTHER ONE
				std::cout << "Invalide choice ! Try again \n";
				validChoice = false;
		}

	}

    std::cout << "With which weapon ? " << std::endl;
    int choice2;
    std::string stringNumber2;
	std::cout << "If you think it is WRENCH: press 1 " << std::endl;
    std::cout << "If you think it is CANDLESTICK: press 2 " << std::endl;
	std::cout << "If you think it is PISTOL: press 3 " << std::endl;
	std::cout << "If you think it is ROPE: press 4 " << std::endl;
	std::cout << "If you think it is LEAD_PIPE: press 5 " << std::endl;
	std::cout << "If you think it is KNIFE: press 6 " << std::endl;




	bool validChoice2 = true;

	while (validChoice2) {

		std::cin >> stringNumber2;
		choice2 = convertToInteger(stringNumber2);

		switch (choice2) {
			case 1: // WRENCH
				std::cout << "You chose WRENCH ! \n";
				accusationChoice.push_back(state::WRENCH);
				break;
			case 2: // CANDLESTICK
				std::cout << "You chose CANDLESTICK ! \n";
				accusationChoice.push_back(state::CANDLESTICK);
				break;
			case 3: // PISTOL
				std::cout << "You chose PISTOL ! \n";
				accusationChoice.push_back(state::PISTOL);
				break;
			case 4: // ROPE
				std::cout << "You chose ROPE ! \n";
				accusationChoice.push_back(state::ROPE);
				break;
			case 5: // LEAD_PIPE
				std::cout << "You chose LEAD_PIPE ! \n";
				accusationChoice.push_back(state::LEAD_PIPE);
				break;
			case 6: // KNIFE
				std::cout << "You chose KNIFE ! \n";
				accusationChoice.push_back(state::KNIFE);
				break;
			default: // OTHER ONE
				std::cout << "Invalide choice ! Try again \n";
				validChoice2 = false;
		}

	}

	std::cout << "Where does it happen ? " << std::endl;
	int choice3;
	std::string stringNumber3;
	std::cout << "If you think it is in the BEDROOM: press 1 " << std::endl;
	std::cout << "If you think it is in the STUDY: press 2 " << std::endl;
	std::cout << "If you think it is in the HALL: press 3 " << std::endl;
	std::cout << "If you think it is in the LIVING_ROOM: press 4 " << std::endl;
	std::cout << "If you think it is in the DINING_ROOM: press 5 " << std::endl;
	std::cout << "If you think it is in the KITCHEN: press 6 " << std::endl;
	std::cout << "If you think it is in the BATHROOM: press 7 " << std::endl;
	std::cout << "If you think it is in the GARAGE: press 8 " << std::endl;
	std::cout << "If you think it is in the GAME_ROOM: press 9 " << std::endl;


	bool validChoice3 = true;

	while (validChoice3) {

		std::cin >> stringNumber3;
		choice3 = convertToInteger(stringNumber3);

		switch (choice3) {
			case 1: // BEDROOM
				std::cout << "You chose BEDROOM ! \n";
				accusationChoice.push_back(state::BEDROOM);
				break;
			case 2: // STUDY
				std::cout << "You chose STUDY ! \n";
				accusationChoice.push_back(state::STUDY);
				break;
			case 3: // HALL
				std::cout << "You chose HALL ! \n";
				accusationChoice.push_back(state::HALL);
				break;
			case 4: // LIVING_ROOM
				std::cout << "You chose LIVING_ROOM ! \n";
				accusationChoice.push_back(state::LIVING_ROOM);
				break;
			case 5: // DINING_ROOM
				std::cout << "You chose DINING_ROOM ! \n";
				accusationChoice.push_back(state::DINING_ROOM);
				break;
			case 6: // KITCHEN
				std::cout << "You chose KITCHEN ! \n";
				accusationChoice.push_back(state::KITCHEN);
				break;
			case 7: // BATHROOM
				std::cout << "You chose BATHROOM ! \n";
			accusationChoice.push_back(state::BATHROOM);
			break;
			case 8: // GARAGE
				std::cout << "You chose GARAGE ! \n";
			accusationChoice.push_back(state::GARAGE);
			break;
			case 9: // GAME_ROOM
				std::cout << "You chose GAME_ROOM ! \n";
			accusationChoice.push_back(state::GAME_ROOM);
			break;
			default: // OTHER ONE
				std::cout << "Invalide choice ! Try again \n";
				validChoice3 = false;
			}

		}

    std::cout << currentPlayer->getIdentity() << " accuses "
    << accusationChoice.at(0) << " of committing the crime in the " << accusationChoice.at(2)
    << " with the " << accusationChoice.at(1) << std::endl;

   return accusationChoice;
 }

int Client::moveDisplay(std::vector<state::Cell*> accessibleCells){
/*
	std::cout << "Where do you want to go ?" << std::endl;


	int choice;
	std::string moveDirection;

	if (accessibleCells.at(0)!=nullptr){
		std::cout << "If you to go UP: press 1 " << std::endl;
	}

	if (accessibleCells.at(1)!=nullptr){
		std::cout << "If you to go DOWN: press 2 " << std::endl;
	}

	if (accessibleCells.at(2)!=nullptr){
		std::cout << "If you to go LEFT: press 3 " << std::endl;
	}

	if (accessibleCells.at(3)!=nullptr){
		std::cout << "If you to go RIGHT: press 4  " << std::endl;
	}

	std::cin >> moveDirection;
	choice = convertToInteger(moveDirection);


	///////// ATTENTION CECI EST A CHANGER (NE PAS FAIRE LE SWITCH CASE)
	//////// DANS TOUTES LES POSSIBILITÉS

	switch (choice) {
	    case 1: // UP
	        std::cout << "You moved UP ! \n";
	        return 1;
	        break;
	    case 2: // DOWN
	        std::cout << "You chose DOWN ! \n";
	        return 2;
	        break;
	    case 3: // LEFT
	        std::cout << "You chose LEFT ! \n";
	        return 3;
	        break;
	    case 4: // RIGHT
	        std::cout << "You chose RIGHT ! \n";
	        return 4;
	        break;

	    default: // OTHER ONE
	        std::cout << "Invalide choice ! Try again \n";
   	}
*/

	return int();
}


void Client::displayPressKey(std::string key){

	std::cout << " press " << key << " " << std::endl;
}

int Client::getValidKey(int max){
  	std::string playerKey;
    try{
    	std::cin >> playerKey;
    	int keyVal = stoi(playerKey);
        if(keyVal >= 0 && keyVal <= max){
        	return keyVal;
        }
        else{
        	std::cout << "Invalid key" << std::endl;
            return getValidKey(max);
        }
    }
	catch(const exception& e){
		std::cout << "Invalid key" << std::endl;
    	return getValidKey(max);
    }
}


/// convertit un string en entier (si on peut)

int Client::convertToInteger(std::string command){
	int number = std::stoi(command);
	if (std::isdigit(number)){
		return number;
	}
		return -1;
}
  
void Client::displayMap()
{
	std::vector<std::vector<std::string>> mapGrid = state->getMap()->getDisplayMap();
	for (std::vector<std::string> row : mapGrid) {
		for (std::string cell : row) {
			std::cout << cell;
		}
		std::cout << std::endl;
	}
}

int Client::choseACardToShowClient (std::vector<state::Card*> cards) {   //cette fonction va de paire avec celle dans engine qui prend en
		// argument un index, c'est la valeur de la carte qui va être montrée. D'abord cette fonction est appelée, puis on prend
		// ce qu'elle renvoie et on le met en argument de la fonction qui va montrer physiquement la carte.
		std::cout << "Which card do you want to show ?" << std::endl;
		int size = cards.size();
		if (size==1) {
			std::cout << "You don't really have the choice. Press 1 to show your card " << std::endl;
		}
		else {
			std::cout << "You have the choice between " << cards.size() << " cards" << std::endl;
			std::cout << "If you want to show " << cards.at(0) << " press 1" << std::endl;
			std::cout << "If you want to show " << cards.at(1) << " press 2" << std::endl;
			if (size == 3) {
				std::cout << "If you want to show " << cards.at(2) << " press 3" << std::endl;
			}
		}
		int cardNumber;
		std::cin >> cardNumber;

		std::cout << "You will show " << cards.at(cardNumber) << std::endl;

	return cardNumber;
}


void Client::showMeCardClient (state::Card card) {
		if (card.getType() == state::SUSPECT_CARD) {
			std::cout <<  " You show " << card.getSuspectName() << std::endl;
		}
		else if (card.getType() == state::WEAPON_CARD) {
			std::cout <<  " You show " << card.getWeaponName() << std::endl;
		}
		else {
			std::cout <<  " You show " << card.getRoomName() << std::endl;
		}
	}

void Client::throwDiceClient () {
	std::cout << "Press 1 to throw the dice ! " << std::endl;
	int keyValue;
	std::cin >> keyValue;
	while (keyValue != 1) {
		std::cout << "Wrong value, press 1 " << std::endl;
	}

	std::cout << "Dice are thrown" << std::endl;
	// finir avec lancer les dés et afficher la valeur



	}

state::PlayerInfo &Client::getClientPlayerInfo() {
	return *clientPlayer;
}

int Client::chooseMoveDirection(const std::vector<int> &possibleMoves) {

}


	void Client::moveFromDiceStart(const std::vector<int> &diceResult) {

	}

engine::Engine &Client::getEngine() {
	return *engine;
}

	engine::CommandId Client::chooseAction() {

	}



}