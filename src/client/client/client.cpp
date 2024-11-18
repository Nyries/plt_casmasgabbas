//
// Created by cassandre on 18/11/24.
//

#include "client.h"
#include "state.h"
#include <iostream>


int introductionToTheGame(void){

	std::cout << "You're playing to the cluedo." << std::endl;
	std::cout << "Mr LENOIR died in is house this night." << std::endl;
	std::cout << "You will have to find the murderer." << std::endl;
	std::cout << "How many detectives are you ?" << std::endl;
	std::cin >> numberPlayer;
	std::cout << "Good Luck for your investigation! " << std::endl;

}


vector<Card> hypothesis(void){

    vector<Card> hypothesisChoice;
    std::cout << "You want to make an hypothesis ! " << std::endl;
    int choice;
    string stringNumber;
    std::cout << "If you are suspecting ROSE: press 1 " << std::endl;
	std::cout << "If you are suspecting PERVENCHE: press 2 " << std::endl;
	std::cout << "If you are suspecting LEBLANC: press 3 " << std::endl;
	std::cout << "If you are suspecting OLIVE: press 4 " << std::endl;
	std::cout << "If you are suspecting MOUTARDE: press 5 " << std::endl;
	std::cout << "If you are suspecting VIOLET: press 6 " << std::endl;


	std::cin >> stringNumber;
	choice = convertToInteger(stringNumber);


	switch (choice) {
	    case 1: // ROSE
	        std::cout << "You chose ROSE ! \n";
	        hypothesisChoice.push_back(ROSE);
	        break;
	    case 2: // PERVENCHE
	        std::cout << "You chose PERVENCHE ! \n";
	        hypothesisChoice.push_back(PERVENCHE);
	        break;
	    case 3: // LEBLANC
	        std::cout << "You chose LEBLANC ! \n";
	        hypothesisChoice.push_back(LEBLANC);
	        break;
	    case 4: // OLIVE
	        std::cout << "You chose OLIVE ! \n";
	        hypothesisChoice.push_back(OLIVE);
	        break;
	    case 5: // MOUTARDE
	        std::cout << "You chose MOUTARDE ! \n";
	        hypothesisChoice.push_back(MOUTARDE);
	        break;
	    case 6: // VIOLET
	        std::cout << "You chose VIOLET ! \n";
	        hypothesisChoice.push_back(VIOLET);
	        break;

	    default: // OTHER ONE
	        std::cout << "Invalide choice ! Try again \n";
	        continue;
    }
    break;

    std::cout << "With which weapon ? " << std::endl;
    int choice2;
    string stringNumber2;
    std::cout << "If you think it is CANDLESTICK: press 1 " << std::endl;
	std::cout << "If you think it is PISTOL: press 2 " << std::endl;
	std::cout << "If you think it is ROPE: press 3 " << std::endl;
	std::cout << "If you think it is LEAD_PIPE: press 4 " << std::endl;
	std::cout << "If you think it is KNIFE: press 5 " << std::endl;
	std::cout << "If you think it is WRENCH: press 6 " << std::endl;

	std::cin >> stringNumber2;
	choice2 = convertToInteger(stringNumber2);

	switch (choice2) {
	    case 1: // CANDLESTICK
	        std::cout << "You chose CANDLESTICK ! \n";
	        hypothesisChoice.push_back(CANDLESTICK);
	        break;
	    case 2: // PISTOL
	        std::cout << "You chose PISTOL ! \n";
	        hypothesisChoice.push_back(PISTOL);
	        break;
	    case 3: // ROPE
	        std::cout << "You chose ROPE ! \n";
	        hypothesisChoice.push_back(ROPE);
	        break;
	    case 4: // LEAD_PIPE
	        std::cout << "You chose LEAD_PIPE ! \n";
	        hypothesisChoice.push_back(LEAD_PIPE);
	        break;
	    case 5: // KNIFE
	        std::cout << "You chose KNIFE ! \n";
	        hypothesisChoice.push_back(KNIFE);
	        break;
	    case 6: // WRENCH
	        std::cout << "You chose WRENCH ! \n";
	        hypothesisChoice.push_back(WRENCH);
	        break;

	    default: // OTHER ONE
	        std::cout << "Invalide choice ! Try again \n";
	        continue;
    }
    break;

    hypothesisChoice.push_back(player.getCurrent().getLocation()); // a revoir

    std::cout << player.getCurrent().getIdentity() << " suggests the Crime was committed by "
    << hypothesisChoice.at(0) << " in the " << hypothesisChoice.at(2)
    << " with the " hypothesisChoice.at(1) << std::endl;


 }


vector<Card> accusation(void){

    vector<Card> accusationChoice;
    std::cout << "You want to make an accusation ! " << std::endl;
    int choice;
    string stringNumber;
    std::cout << "If you are accusating ROSE: press 1 " << std::endl;
	std::cout << "If you are accusating PERVENCHE: press 2 " << std::endl;
	std::cout << "If you are accusating LEBLANC: press 3 " << std::endl;
	std::cout << "If you are accusating OLIVE: press 4 " << std::endl;
	std::cout << "If you are accusating MOUTARDE: press 5 " << std::endl;
	std::cout << "If you are accusating VIOLET: press 6 " << std::endl;

	std::cin >> stringNumber;
	choice = convertToInteger(stringNumber);

	switch (choice) {
	    case 1: // ROSE
	        std::cout << "You chose ROSE ! \n";
	        accusationChoice.push_back(ROSE);
	        break;
	    case 2: // PERVENCHE
	        std::cout << "You chose PERVENCHE ! \n";
	        accusationChoice.push_back(PERVENCHE);
	        break;
	    case 3: // LEBLANC
	        std::cout << "You chose LEBLANC ! \n";
	        accusationChoice.push_back(LEBLANC);
	        break;
	    case 4: // OLIVE
	        std::cout << "You chose OLIVE ! \n";
	        accusationChoice.push_back(OLIVE);
	        break;
	    case 5: // MOUTARDE
	        std::cout << "You chose MOUTARDE ! \n";
	        accusationChoice.push_back(MOUTARDE);
	        break;
	    case 6: // VIOLET
	        std::cout << "You chose VIOLET ! \n";
	        accusationChoice.push_back(VIOLET);
	        break;

	    default: // OTHER ONE
	        std::cout << "Invalide choice ! Try again \n";
	        continue;
    }
    break;

    std::cout << "With which weapon ? " << std::endl;
    int choice2;
    string stringNumber2;
    std::cout << "If you think it is CANDLESTICK: press 1 " << std::endl;
	std::cout << "If you think it is PISTOL: press 2 " << std::endl;
	std::cout << "If you think it is ROPE: press 3 " << std::endl;
	std::cout << "If you think it is LEAD_PIPE: press 4 " << std::endl;
	std::cout << "If you think it is KNIFE: press 5 " << std::endl;
	std::cout << "If you think it is WRENCH: press 6 " << std::endl;

	std::cin >> stringNumber2;
	choice2 = convertToInteger(stringNumber2);

	switch (choice2) {
	    case 1: // CANDLESTICK
	        std::cout << "You chose CANDLESTICK ! \n";
	        accusationChoice.push_back(CANDLESTICK);
	        break;
	    case 2: // PISTOL
	        std::cout << "You chose PISTOL ! \n";
	        accusationChoice.push_back(PISTOL);
	        break;
	    case 3: // ROPE
	        std::cout << "You chose ROPE ! \n";
	        accusationChoice.push_back(ROPE);
	        break;
	    case 4: // LEAD_PIPE
	        std::cout << "You chose LEAD_PIPE ! \n";
	        accusationChoice.push_back(LEAD_PIPE);
	        break;
	    case 5: // KNIFE
	        std::cout << "You chose KNIFE ! \n";
	        accusationChoice.push_back(KNIFE);
	        break;
	    case 6: // WRENCH
	        std::cout << "You chose WRENCH ! \n";
	        accusationChoice.push_back(WRENCH);
	        break;

	    default: // OTHER ONE
	        std::cout << "Invalide choice ! Try again \n";
	        continue;
    }
    break;

    accusationChoice.push_back(player.getCurrent().getLocation()); // a revoir

    std::cout << player.getCurrent().getIdentity() << " accuses "
    << accusationChoice.at(0) << " of committing the crime in the " << accusationChoice.at(2)
    << " with the " accusationChoice.at(1) << std::endl;

 }

int moveDisplay(vector<cell*> accessibleCells){

	std::cout << "Where do you want to go ?" << std::endl;

	int choice;
	string moveDirection;

	if (accessibleCells.at(0)!=null_ptr){
		std::cout << "If you to go UP: press 1 " << std::endl;
	}

	if (accessibleCells.at(1)!=null_ptr){
		std::cout << "If you to go DOWN: press 2 " << std::endl;
	}

	if (accessibleCells.at(2)!=null_ptr){
		std::cout << "If you to go LEFT: press 3 " << std::endl;
	}

	if (accessibleCells.at(3)!=null_ptr){
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
            continue;
   	}
   	break;

}


void pressKey(char key){
	std::cout >> " press " >> key >> " " >> std::endl;
}

char goodKey(char key){
	std::cin << playerKey;
	if (playerKey!=key){
		goodKey(key);
	}
}

/// dis si un nombre est constitué de chiffres

bool isANumber(const std::string& command){
	if (str.empty()) return false;

	for (char c: command){
		if (!std::isdigit(command)){
			return false;
		}
	}
	return true;
}

/// convertit un string en entier (si on peut)

int convertToInteger(std::string command){
	if (isANumber(command)){
		return std::stoi(command);
	}
}
