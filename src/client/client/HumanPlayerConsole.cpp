//
// Created by louismmassin on 1/5/25.
//
#include "HumanPlayerConsole.h"

#include <iostream>
#include <utility>
#include <engine/Engine.h>

#include "state/Weapon.h"
#include "Client.h"
#include "ConsoleIO.h"

namespace client {
    HumanPlayerConsole::HumanPlayerConsole(engine::Engine &engine, state::PlayerInfo &playerInfo, std::string name): HumanPlayer(engine, playerInfo, move(name)) {
    }

    engine::CommandId HumanPlayerConsole::chooseAction()   {
        const std::vector<engine::CommandId> actions = engine.getPossibleActions (playerInfo);
        const int size = static_cast<int>(actions.size());

        for (int i=0; i<size; i++) {

            switch(actions.at(i)) {
                case engine::MOVE_FROM_DICE:
                    std::cout << "If you want to move from the dice, press " << i+1 << std::endl;
                break;
                case engine::HYPOTHESIS:
                    std::cout << "If you want to make a hypothesis, press " << i+1 << std::endl;
                break;
                case engine::ACCUSATION:
                    std::cout << "If you want to make an accusation, press " << i+1 << std::endl;
                break;
                case engine::SECRET_PASSAGE:
                    std::cout << "If you want to use the secret passage, press " << i+1 << std::endl;
                break;
                default:
                    throw std::runtime_error("Switch failed");
            }
        }

        std::cout << "What do you want to do ?" << std::endl;

        int choice = ConsoleIO::getValidKey(size);

        switch(choice) {
            case engine::MOVE_FROM_DICE:
                std::cout << "You chose to move from the dice " << std::endl;
            break;
            case engine::HYPOTHESIS:
                std::cout << "You chose to do a hypothesis " << std::endl;
            break;
            case engine::ACCUSATION:
                std::cout << "You chose to do an accusation " << std::endl;
            break;
            case engine::SECRET_PASSAGE:
                std::cout << "You chose to use the secret passage " << std::endl;
            break;
            default:
                throw std::runtime_error("Switch failed");
        }
        return actions.at(choice - 1);

    }

    engine::Move HumanPlayerConsole::chooseMoveDirection()   {
        auto possibleMoves = engine.getPossibleMoves(playerInfo);
        const int size = static_cast<int>(possibleMoves.size());

        for (int i=0; i<size; i++) {

            switch(possibleMoves.at(i)) {
                case engine::MOVE_UP:
                    std::cout << "If you want to move up, press " << i+1 << std::endl;
                break;
                case engine::MOVE_DOWN:
                    std::cout << "If you want to move down, press " << i+1 << std::endl;
                break;
                case engine::MOVE_LEFT:
                    std::cout << "If you want to move left, press " << i+1 << std::endl;
                break;
                case engine::MOVE_RIGHT:
                    std::cout << "If you want to move right, press " << i+1 << std::endl;
                break;
                case engine::ENTER_ROOM:
                    std::cout << "If you want to enter in the room, press " << i+1 << std::endl;
                break;
                case engine::EXIT_ROOM:
                    std::cout << "If you want to exit the room, press " << i+1 << std::endl;
                break;
                default:
                    throw std::runtime_error("Switch failed");
            }
        }

        std::cout << "What do you want to do ?" << std::endl;

        int choice = ConsoleIO::getValidKey(size) - 1;

        switch(possibleMoves.at(choice)) {
            case engine::MOVE_UP:
                std::cout << "You chose to move up " << std::endl;
            break;
            case engine::MOVE_DOWN:
                std::cout << "You chose to move down " << std::endl;
            break;
            case engine::MOVE_LEFT:
                std::cout << "You chose to move left " << std::endl;
            break;
            case engine::MOVE_RIGHT:
                std::cout << "You chose to move right " << std::endl;
            break;
            case engine::ENTER_ROOM:
                std::cout << "You chose to enter in the room " << std::endl;
            break;
            case engine::EXIT_ROOM:
                std::cout << "You chose to exit the room " << std::endl;
            break;
            default:
                throw std::runtime_error("Switch failed");
        }
        return possibleMoves.at(choice);
    }

    state::TripleClue HumanPlayerConsole::chooseHypothesis()  {
	    state::TripleClue hypothesisChoice{};
	    std::cout << "You want to make an hypothesis ! " << std::endl;
	    std::cout << "If you are suspecting ROSE: press 1 " << std::endl;
		std::cout << "If you are suspecting PERVENCHE: press 2 " << std::endl;
		std::cout << "If you are suspecting LEBLANC: press 3 " << std::endl;
		std::cout << "If you are suspecting OLIVE: press 4 " << std::endl;
		std::cout << "If you are suspecting MOUTARDE: press 5 " << std::endl;
		std::cout << "If you are suspecting VIOLET: press 6 " << std::endl;

	    const int choice = ConsoleIO::getValidKey(6);

      	switch (choice) {
	    	case 1: // ROSE
	        	std::cout << "You chose ROSE ! \n";
	        	hypothesisChoice.suspect = state::ROSE;
	       	 	break;
	    	case 2: // PERVENCHE
	        	std::cout << "You chose PERVENCHE ! \n";
      			hypothesisChoice.suspect = state::PERVENCHE;
	        	break;
	    	case 3: // LEBLANC
	        	std::cout << "You chose LEBLANC ! \n";
      			hypothesisChoice.suspect = state::LEBLANC;
	        	break;
	    	case 4: // OLIVE
	        	std::cout << "You chose OLIVE ! \n";
      			hypothesisChoice.suspect = state::OLIVE;
	        	break;
	    	case 5: // MOUTARDE
	        	std::cout << "You chose MOUTARDE ! \n";
      			hypothesisChoice.suspect = state::MOUTARDE;
	        	break;
      		case 6: // VIOLET
      			std::cout << "You chose VIOLET ! \n";
      			hypothesisChoice.suspect = state::VIOLET;
      			break;
      		default: // OTHER ONE
	        	throw std::runtime_error("switch failed");
    	}
	    std::cout << "With which weapon ? " << std::endl;
	    std::cout << "If you think it is CANDLESTICK: press 1 " << std::endl;
		std::cout << "If you think it is PISTOL: press 2 " << std::endl;
		std::cout << "If you think it is ROPE: press 3 " << std::endl;
		std::cout << "If you think it is LEAD_PIPE: press 4 " << std::endl;
		std::cout << "If you think it is KNIFE: press 5 " << std::endl;
		std::cout << "If you think it is WRENCH: press 6 " << std::endl;

		int choice2 = ConsoleIO::getValidKey(6);

		switch (choice2) {

	    	case 1: // CANDLESTICK
	        	std::cout << "You chose CANDLESTICK ! \n";
				hypothesisChoice.weapon = state::CANDLESTICK;
	        	break;
			case 2: // PISTOL
	        	std::cout << "You chose PISTOL ! \n";
				hypothesisChoice.weapon = state::PISTOL;
	        	break;
	    	case 3: // ROPE
	        	std::cout << "You chose ROPE ! \n";
				hypothesisChoice.weapon = state::ROPE;
	        	break;
	    	case 4: // LEAD_PIPE
	        	std::cout << "You chose LEAD_PIPE ! \n";
				hypothesisChoice.weapon = state::LEAD_PIPE;
	       	 	break;
	    	case 5: // KNIFE
	        	std::cout << "You chose KNIFE ! \n";
				hypothesisChoice.weapon = state::KNIFE;
	        	break;
			case 6: // WRENCH
				std::cout << "You chose WRENCH ! \n";
				hypothesisChoice.weapon = state::WRENCH;
				break;
	    	default: // OTHER ONE
	    		throw std::runtime_error("Switch failed");
    	}

		const auto& currentRoom = static_cast<const state::Room&>(playerInfo.getLocation());
	    hypothesisChoice.room = currentRoom.getRoomName();

	    std::cout << playerInfo.getIdentity() << " suggests the Crime was committed by "
	    << hypothesisChoice.suspect << " in the " << hypothesisChoice.room
	    << " with the " << hypothesisChoice.weapon << std::endl;

	    return hypothesisChoice;
    }

	int HumanPlayerConsole::chooseACardToShowClient(const std::vector<state::Card*>& cards)  {   //cette fonction va de paire avec celle dans engine qui prend en
    	// argument un index, c'est la valeur de la carte qui va être montrée. D'abord cette fonction est appelée, puis on prend
    	// ce qu'elle renvoie et on le met en argument de la fonction qui va montrer physiquement la carte.
    	std::cout << "Which card do you want to show ?" << std::endl;
    	const unsigned long size = cards.size();
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

	state::TripleClue HumanPlayerConsole::chooseAccusation()  {

	    state::TripleClue accusationChoice{};
	    std::cout << "You want to make an accusation ! " << std::endl;
	    std::string stringNumber;
	    std::cout << "If you are accusating ROSE: press 1 " << std::endl;
		std::cout << "If you are accusating PERVENCHE: press 2 " << std::endl;
		std::cout << "If you are accusating LEBLANC: press 3 " << std::endl;
		std::cout << "If you are accusating OLIVE: press 4 " << std::endl;
		std::cout << "If you are accusating MOUTARDE: press 5 " << std::endl;
		std::cout << "If you are accusating VIOLET: press 6 " << std::endl;

		int choice = ConsoleIO::getValidKey(6);
		switch (choice) {
			case 1: // ROSE
				std::cout << "You chose ROSE ! \n";
				accusationChoice.suspect = state::ROSE;
				break;
			case 2: // PERVENCHE
				std::cout << "You chose PERVENCHE ! \n";
				accusationChoice.suspect = state::PERVENCHE;
				break;
			case 3: // LEBLANC
				std::cout << "You chose LEBLANC ! \n";
				accusationChoice.suspect = state::LEBLANC;
				break;
			case 4: // OLIVE
				std::cout << "You chose OLIVE ! \n";
				accusationChoice.suspect = state::OLIVE;
				break;
			case 5: // MOUTARDE
				std::cout << "You chose MOUTARDE ! \n";
				accusationChoice.suspect = state::MOUTARDE;
				break;
			case 6: // VIOLET
				std::cout << "You chose VIOLET ! \n";
				accusationChoice.suspect = state::VIOLET;
				break;

			default: // OTHER ONE
				throw std::runtime_error("Switch failed");
		}

	    std::cout << "With which weapon ? " << std::endl;
	    std::cout << "If you think it is CANDLESTICK: press 1 " << std::endl;
		std::cout << "If you think it is PISTOL: press 2 " << std::endl;
		std::cout << "If you think it is ROPE: press 3 " << std::endl;
		std::cout << "If you think it is LEAD_PIPE: press 4 " << std::endl;
		std::cout << "If you think it is KNIFE: press 5 " << std::endl;
		std::cout << "If you think it is WRENCH: press 6 " << std::endl;

		int choice2 = ConsoleIO::getValidKey(6);
		switch (choice2){
			case 1: // CANDLESTICK
				std::cout << "You chose CANDLESTICK ! \n";
				accusationChoice.weapon = state::CANDLESTICK;
				break;
			case 2: // PISTOL
				std::cout << "You chose PISTOL ! \n";
				accusationChoice.weapon = state::PISTOL;
				break;
			case 3: // ROPE
				std::cout << "You chose ROPE ! \n";
				accusationChoice.weapon = state::ROPE;
				break;
			case 4: // LEAD_PIPE
				std::cout << "You chose LEAD_PIPE ! \n";
				accusationChoice.weapon = state::LEAD_PIPE;
				break;
			case 5: // KNIFE
				std::cout << "You chose KNIFE ! \n";
				accusationChoice.weapon = state::KNIFE;
				break;
			case 6: // WRENCH
				std::cout << "You chose WRENCH ! \n";
				accusationChoice.weapon = state::WRENCH;
				break;
			default: // OTHER ONE
				throw std::runtime_error("Switch failed");
		}

		std::cout << "Where does it happen ? " << std::endl;
		std::cout << "If you think it is in the STUDY: press 1 " << std::endl;
		std::cout << "If you think it is in the HALL: press 2 " << std::endl;
		std::cout << "If you think it is in the LIVING_ROOM: press 3 " << std::endl;
		std::cout << "If you think it is in the DINING_ROOM: press 4 " << std::endl;
		std::cout << "If you think it is in the KITCHEN: press 5 " << std::endl;
		std::cout << "If you think it is in the BATHROOM: press 6 " << std::endl;
		std::cout << "If you think it is in the GARAGE: press 7 " << std::endl;
		std::cout << "If you think it is in the GAME_ROOM: press 8 " << std::endl;
		std::cout << "If you think it is in the BEDROOM: press 9 " << std::endl;


		int choice3 = ConsoleIO::getValidKey(9);
		switch (choice3) {
			case 1: // STUDY
				std::cout << "You chose STUDY ! \n";
				accusationChoice.room = state::STUDY;
				break;
			case 2: // HALL
				std::cout << "You chose HALL ! \n";
			accusationChoice.room = state::HALL;
				break;
			case 3: // LIVING_ROOM
				std::cout << "You chose LIVING_ROOM ! \n";
			accusationChoice.room = state::LIVING_ROOM;
				break;
			case 4: // DINING_ROOM
				std::cout << "You chose DINING_ROOM ! \n";
			accusationChoice.room = state::DINING_ROOM;
				break;
			case 5: // KITCHEN
				std::cout << "You chose KITCHEN ! \n";
			accusationChoice.room = state::KITCHEN;
				break;
			case 6: // BATHROOM
				std::cout << "You chose BATHROOM ! \n";
			accusationChoice.room = state::BATHROOM;
				break;
			case 7: // GARAGE
				std::cout << "You chose GARAGE ! \n";
			accusationChoice.room = state::GARAGE;
				break;
			case 8: // GAME_ROOM
				std::cout << "You chose GAME_ROOM ! \n";
			accusationChoice.room = state::GAME_ROOM;
				break;
			case 9: // BEDROOM
				std::cout << "You chose BEDROOM ! \n";
			accusationChoice.room = state::BEDROOM;
				break;
			default: // OTHER ONE
				throw std::runtime_error("Switch failed");
			}

	    std::cout << playerInfo.getIdentity() << " accuses "
	    << accusationChoice.suspect << " of committing the crime in the " << accusationChoice.room
	    << " with the " << accusationChoice.weapon << std::endl;
	   return accusationChoice;
    }

	void HumanPlayerConsole::seeACardFromPlayer(const state::Card &shownCard, const Player &cardOwner) {
		std::cout << cardOwner.getName() << "showed you the card" << std::endl;
	}

	state::Door &HumanPlayerConsole::chooseDoor(const std::vector<state::Door *> &doorList) {
		std::cout <<"Select door:\n";
    	for (int i = 0; i < doorList.size(); i++) {
    		std::cout << i + 1 << " coordinates " << doorList.at(i)->getX() << "," << doorList.at(i)->getY() << "\n";
    	}
    	std::cout << std::endl;
    	int choice = ConsoleIO::getValidKey(doorList.size());
    	return *doorList.at(choice - 1);
	}

	void HumanPlayerConsole::makePlayerThrowDice() {
    	std::cout << "Press 1 to throw the dice ! " << std::endl;
    	ConsoleIO::getValidKey(1);
    	std::cout << "Dice are thrown" << std::endl;
	}

	void HumanPlayerConsole::displayDiceResult(int result, const Player &player) {
    	std::cout << player.getName() << " threw the dice and got " << result << "!" << std::endl;
	}


}
