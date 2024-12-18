//
// Created by cassandre on 17/12/24.
//

#include "state.h"
#include "engine.h"
#include "AI.h"

#include <algorithm>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <fstream>
#include <json/json.h>

using namespace std;

namespace ai {
    //ai::AI(){}


    string AI::intToSuspect (int input)
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
            default:
                return {};
        }
    }

//////////////////////////////////////////////



	int AI::convertToInteger(string command) {
    	int number = stoi(command);
    	if (isdigit(number)){
    		return number;
    	}
    	return -1;
    }


    engine::Engine& AI::getEngine () {
        return *engine;
    }

    engine::CommandId AI::chooseAction () {
        const vector<engine::CommandId> actions = engine->getPossibleActions (*playerInfo);

        const int size = static_cast<int>(actions.size());

        const int AIactionChoice = engine::UtilityFunctions::randomInt(size)+1;

        return actions.at(AIactionChoice);

    }


    state::PlayerInfo& AI::getClientPlayerInfo () {
        return *playerInfo;

    }
    engine::Move AI::chooseMoveDirection (const vector<engine::Move>& possibleMoves) {
        const int size = static_cast<int>(possibleMoves.size());
        const int AImoveDirectionChoice = engine::UtilityFunctions::randomInt(size)+1;

        return possibleMoves.at(AImoveDirectionChoice);

    }




}