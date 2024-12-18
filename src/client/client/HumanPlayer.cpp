//
// Created by louismmassin on 12/18/24.
//
#include "HumanPlayer.h"

#include <iostream>
#include <utility>
#include <engine/Engine.h>

#include "state/Weapon.h"
#include "Client.h"

namespace client {
    HumanPlayer::HumanPlayer(engine::Engine *engine, state::PlayerInfo &playerInfo, std::string name): Player(engine, playerInfo, true, std::move(name)) {

    }

    engine::CommandId HumanPlayer::chooseAction()  {
        const std::vector<engine::CommandId> actions = engine->getPossibleActions (playerInfo);
        const int size = static_cast<int>(actions.size());

        for (int i=0; i<size; i++) {

            switch(actions.at(i)) {
                case 1: // MOVE_FROM_DICE
                    std::cout << "If you want to move from the dice, press " << i+1 << std::endl;
                break;
                case 2: // HYPOTHESIS
                    std::cout << "If you want to make a hypothesis, press " << i+1 << std::endl;
                break;
                case 3: // ACCUSATION
                    std::cout << "If you want to make an accusation, press " << i+1 << std::endl;
                break;
                case 4: // SECRET_PASSAGE
                    std::cout << "If you want to use the secret passage, press " << i+1 << std::endl;
                break;
                default:
                    throw std::runtime_error("Switch failed");
            }
        }

        std::cout << "What do you want to do ?" << std::endl;

        int choice = Client::getValidKey(size);

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

    engine::Move HumanPlayer::chooseMoveDirection()  {
        auto possibleMoves = engine->getPossibleMoves(playerInfo);
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

        int choice = Client::getValidKey(size);

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
        return possibleMoves.at(choice - 1);
    }

    std::vector<int> HumanPlayer::chooseHypothesis() {
	    std::vector<int> hypothesisChoice;
	    std::cout << "You want to make an hypothesis ! " << std::endl;
	    std::cout << "If you are suspecting ROSE: press 1 " << std::endl;
		std::cout << "If you are suspecting PERVENCHE: press 2 " << std::endl;
		std::cout << "If you are suspecting LEBLANC: press 3 " << std::endl;
		std::cout << "If you are suspecting OLIVE: press 4 " << std::endl;
		std::cout << "If you are suspecting MOUTARDE: press 5 " << std::endl;
		std::cout << "If you are suspecting VIOLET: press 6 " << std::endl;

	    const int choice = Client::getValidKey(6);

      	switch (choice) {
	    	case 1: // ROSE
	        	std::cout << "You chose ROSE ! \n";
	        	hypothesisChoice.push_back(state::ROSE);
	       	 	break;
	    	case 2: // PERVENCHE
	        	std::cout << "You chose PERVENCHE ! \n";
	        	hypothesisChoice.push_back(state::PERVENCHE);
	        	break;
	    	case 3: // LEBLANC
	        	std::cout << "You chose LEBLANC ! \n";
	        	hypothesisChoice.push_back(state::LEBLANC);
	        	break;
	    	case 4: // OLIVE
	        	std::cout << "You chose OLIVE ! \n";
	        	hypothesisChoice.push_back(state::OLIVE);
	        	break;
	    	case 5: // MOUTARDE
	        	std::cout << "You chose MOUTARDE ! \n";
	        	hypothesisChoice.push_back(state::MOUTARDE);
	        	break;
      		case 6: // VIOLET
      			std::cout << "You chose VIOLET ! \n";
      			hypothesisChoice.push_back(state::VIOLET);
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

		int choice2 = Client::getValidKey(6);

		switch (choice2) {

	    	case 1: // CANDLESTICK
	        	std::cout << "You chose CANDLESTICK ! \n";
	        	hypothesisChoice.push_back(state::CANDLESTICK);
	        	break;
	   		 case 2: // PISTOL
	        	std::cout << "You chose PISTOL ! \n";
	        	hypothesisChoice.push_back(state::PISTOL);
	        	break;
	    	case 3: // ROPE
	        	std::cout << "You chose ROPE ! \n";
	       	 	hypothesisChoice.push_back(state::ROPE);
	        	break;
	    	case 4: // LEAD_PIPE
	        	std::cout << "You chose LEAD_PIPE ! \n";
	        	hypothesisChoice.push_back(state::LEAD_PIPE);
	       	 	break;
	    	case 5: // KNIFE
	        	std::cout << "You chose KNIFE ! \n";
	        	hypothesisChoice.push_back(state::KNIFE);
	        	break;
			case 6: // WRENCH
				std::cout << "You chose WRENCH ! \n";
				hypothesisChoice.push_back(state::WRENCH);
				break;
	    	default: // OTHER ONE
	    		throw std::runtime_error("Switch failed");
    	}

		auto& currentRoom = static_cast<state::Room&>(playerInfo.getLocation());
	    hypothesisChoice.push_back(currentRoom.getRoomName());

	    std::cout << playerInfo.getIdentity() << " suggests the Crime was committed by "
	    << hypothesisChoice.at(0) << " in the " << hypothesisChoice.at(2)
	    << " with the " << hypothesisChoice.at(1) << std::endl;

	    return hypothesisChoice;
    }

	int HumanPlayer::chooseACardToShowClient(std::vector<state::Card *> cards)  {   //cette fonction va de paire avec celle dans engine qui prend en
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

	std::vector<int> HumanPlayer::chooseAccusation() {

	    std::vector<int> accusationChoice;
	    std::cout << "You want to make an accusation ! " << std::endl;
	    std::string stringNumber;
	    std::cout << "If you are accusating ROSE: press 1 " << std::endl;
		std::cout << "If you are accusating PERVENCHE: press 2 " << std::endl;
		std::cout << "If you are accusating LEBLANC: press 3 " << std::endl;
		std::cout << "If you are accusating OLIVE: press 4 " << std::endl;
		std::cout << "If you are accusating MOUTARDE: press 5 " << std::endl;
		std::cout << "If you are accusating VIOLET: press 6 " << std::endl;

		int choice = Client::getValidKey(6);
		switch (choice) {
			case 1: // ROSE
				std::cout << "You chose ROSE ! \n";
				accusationChoice.push_back(state::ROSE);
				break;
			case 2: // PERVENCHE
				std::cout << "You chose PERVENCHE ! \n";
				accusationChoice.push_back(state::PERVENCHE);
				break;
			case 3: // LEBLANC
				std::cout << "You chose LEBLANC ! \n";
				accusationChoice.push_back(state::LEBLANC);
				break;
			case 4: // OLIVE
				std::cout << "You chose OLIVE ! \n";
				accusationChoice.push_back(state::OLIVE);
				break;
			case 5: // MOUTARDE
				std::cout << "You chose MOUTARDE ! \n";
				accusationChoice.push_back(state::MOUTARDE);
				break;
			case 6: // VIOLET
				std::cout << "You chose VIOLET ! \n";
				accusationChoice.push_back(state::VIOLET);
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

		int choice2 = Client::getValidKey(6);
		switch (choice2){
			case 1: // CANDLESTICK
				std::cout << "You chose CANDLESTICK ! \n";
				accusationChoice.push_back(state::CANDLESTICK);
				break;
			case 2: // PISTOL
				std::cout << "You chose PISTOL ! \n";
				accusationChoice.push_back(state::PISTOL);
				break;
			case 3: // ROPE
				std::cout << "You chose ROPE ! \n";
				accusationChoice.push_back(state::ROPE);
				break;
			case 4: // LEAD_PIPE
				std::cout << "You chose LEAD_PIPE ! \n";
				accusationChoice.push_back(state::LEAD_PIPE);
				break;
			case 5: // KNIFE
				std::cout << "You chose KNIFE ! \n";
				accusationChoice.push_back(state::KNIFE);
				break;
			case 6: // WRENCH
				std::cout << "You chose WRENCH ! \n";
				accusationChoice.push_back(state::WRENCH);
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


		int choice3 = Client::getValidKey(9);
		switch (choice3) {
			case 1: // STUDY
				std::cout << "You chose STUDY ! \n";
				accusationChoice.push_back(state::STUDY);
				break;
			case 2: // HALL
				std::cout << "You chose HALL ! \n";
				accusationChoice.push_back(state::HALL);
				break;
			case 3: // LIVING_ROOM
				std::cout << "You chose LIVING_ROOM ! \n";
				accusationChoice.push_back(state::LIVING_ROOM);
				break;
			case 4: // DINING_ROOM
				std::cout << "You chose DINING_ROOM ! \n";
				accusationChoice.push_back(state::DINING_ROOM);
				break;
			case 5: // KITCHEN
				std::cout << "You chose KITCHEN ! \n";
				accusationChoice.push_back(state::KITCHEN);
				break;
			case 6: // BATHROOM
				std::cout << "You chose BATHROOM ! \n";
				accusationChoice.push_back(state::BATHROOM);
				break;
			case 7: // GARAGE
				std::cout << "You chose GARAGE ! \n";
				accusationChoice.push_back(state::GARAGE);
				break;
			case 8: // GAME_ROOM
				std::cout << "You chose GAME_ROOM ! \n";
				accusationChoice.push_back(state::GAME_ROOM);
				break;
			case 9: // BEDROOM
				std::cout << "You chose BEDROOM ! \n";
				accusationChoice.push_back(state::BEDROOM);
				break;
			default: // OTHER ONE
				throw std::runtime_error("Switch failed");
			}

	    std::cout << playerInfo.getIdentity() << " accuses "
	    << accusationChoice.at(0) << " of committing the crime in the " << accusationChoice.at(2)
	    << " with the " << accusationChoice.at(1) << std::endl;
	   return accusationChoice;
    }
}
