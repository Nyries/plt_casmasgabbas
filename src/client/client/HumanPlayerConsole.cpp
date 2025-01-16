//
// Created by louismmassin on 1/5/25.
//
#include "HumanPlayerConsole.h"

#include <iostream>
#include <utility>
#include <engine/Engine.h>

#include "Client.h"
#include "ConsoleIO.h"
#include "state/Suspect.hpp"
#include "state/Weapon.hpp"
#include "state/RoomName.hpp"

namespace client {
    HumanPlayerConsole::HumanPlayerConsole(engine::Engine &engine, state::PlayerState &playerState, std::string name): HumanPlayer(engine, playerState, move(name)) {
    }

    engine::CommandId HumanPlayerConsole::chooseAction()   {
        const std::vector<engine::CommandId> actions = engine.getPossibleActions (playerState);
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

        switch(actions.at(choice - 1)) {
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
        auto possibleMoves = engine.getPossibleMoves(playerState);
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
	    std::cout << "You want to make a hypothesis ! \n";
    	for (int i = 0; i < 6; i++) {
    		std::cout << "If you are suspecting " << static_cast<state::Suspect>(i+1) << ": press " << (i+1) << "\n";
    	}
    	std::cout << std::endl;

	    const int choice = ConsoleIO::getValidKey(6);
    	hypothesisChoice.suspect = static_cast<state::Suspect>(choice);

	    std::cout << "You chose " << hypothesisChoice.suspect << "!\n";

	    std::cout << "With which weapon ?\n";
    	for (int i = 0; i < 6; i++) {
    		std::cout << "If you think it was a " << static_cast<state::Weapon>(i+1) << ": press " << (i+1) << "\n";
    	}
    	std::cout << std::endl;

		int choice2 = ConsoleIO::getValidKey(6);
    	hypothesisChoice.weapon = static_cast<state::Weapon>(choice2);

    	std::cout << "You chose the " << hypothesisChoice.weapon << "!\n";

		const auto& currentRoom = dynamic_cast<const state::Room&>(playerState.getLocation());
	    hypothesisChoice.room = currentRoom.getRoomName();

	    return hypothesisChoice;
    }

	int HumanPlayerConsole::chooseACardToShowPlayer(const std::vector<const state::Card *> &cards, const Player& player) {
    	// argument un index, c'est la valeur de la carte qui va être montrée. D'abord cette fonction est appelée, puis on prend
    	// ce qu'elle renvoie et on le met en argument de la fonction qui va montrer physiquement la carte.
    	std::cout << "Which card do you want to show ?" << std::endl;
    	const unsigned long size = cards.size();
    	if (size==1) {
    		std::cout << "You don't really have the choice. Press 1 to show your card " << std::endl;
    	}
    	else {
    		std::cout << "You have the choice between " << cards.size() << " cards" << std::endl;
    		std::cout << "If you want to show " << cards.at(0)->getValueAsString() << " press 1" << std::endl;
    		std::cout << "If you want to show " << cards.at(1)->getValueAsString() << " press 2" << std::endl;
    		if (size == 3) {
    			std::cout << "If you want to show " << cards.at(2)->getValueAsString() << " press 3" << std::endl;
    		}
    	}
    	int cardNumber = ConsoleIO::getValidKey(cards.size()) - 1;

    	std::cout << "You will show " << cards.at(cardNumber)->getValueAsString() << std::endl;

    	return cardNumber;
	}


	state::TripleClue HumanPlayerConsole::chooseAccusation()  {
    	state::TripleClue accusationChoice{};
    	std::cout << "You want to make an accusation ! \n";
    	for (int i = 0; i < 6; i++) {
    		std::cout << "If you want to accuse " << static_cast<state::Suspect>(i+1) << ": press " << (i+1) << "\n";
    	}
    	std::cout << std::endl;

    	const int choice = ConsoleIO::getValidKey(6);
    	accusationChoice.suspect = static_cast<state::Suspect>(choice);

    	std::cout << "You chose " << accusationChoice.suspect << "!\n";

    	std::cout << "With which weapon ?\n";
    	for (int i = 0; i < 6; i++) {
    		std::cout << "If you think it was a " << static_cast<state::Weapon>(i+1) << ": press " << (i+1) << "\n";
    	}
    	std::cout << std::endl;

    	int choice2 = ConsoleIO::getValidKey(6);
    	accusationChoice.weapon = static_cast<state::Weapon>(choice2);

    	std::cout << "You chose the " << accusationChoice.weapon << "!\n";

    	std::cout << "In which room ?\n";
    	for (int i = 0; i < 9; i++) {
    		std::cout << "If you think it was in the " << static_cast<state::RoomName>(i+1) << ": press " << (i+1) << "\n";
    	}
    	std::cout << std::endl;

    	int choice3 = ConsoleIO::getValidKey(6);
    	accusationChoice.room = static_cast<state::RoomName>(choice3);

    	std::cout << "You chose the " << accusationChoice.room << "!\n";

    	return accusationChoice;
    }

	void HumanPlayerConsole::seeACardFromPlayer(const state::Card &shownCard, const Player &cardOwner) {
    	std::cout << cardOwner.getName() << " showed you the card " << shownCard.getValueAsString() << std::endl;

    }

	state::Door &HumanPlayerConsole::chooseDoor(const std::vector<state::Door *> &doorList) {
		std::cout <<"Select door:\n";
    	for (int i = 0; i < (int)doorList.size(); i++) {
    		std::cout << "Door " << i + 1 << ": coordinates " << doorList.at(i)->getX() << "," << doorList.at(i)->getY() << "\n";
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

	void HumanPlayerConsole::startOfTheGame() {
    	std::cout << "You play as " << playerState.getIdentity();
    	std::cout << ", your cards are: \n";
    	const auto& suspectCards = playerState.getSuspectCards();
    	for (const auto& card: suspectCards) {
    		std::cout << card.getSuspectName() << "\n";
    	}
    	const auto& weaponCards = playerState.getWeaponCards();
    	for (const auto& card: weaponCards) {
    		std::cout << card.getWeaponName() << "\n";
    	}
    	const auto& roomCards = playerState.getRoomCards();
    	for (const auto& card: roomCards) {
    		std::cout << card.getRoomName() << "\n";
    	}
    	std::cout << std::endl;
	}


}
