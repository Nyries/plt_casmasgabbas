//
// Created by cassandre on 18/12/24.
//


#include "state.h"
#include "engine.h"
#include "RandomAI.h"
#include "ai.h"

#include <algorithm>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <fstream>
#include <json/json.h>


using namespace std;

namespace ai {

    //ai::RandomAI(){}


   vector<int> RandomAI::chooseHypothesis () {
        vector<int> hypothesisChoice;

        const int suspectChoice = engine::UtilityFunctions::randomInt(5)+1;
        hypothesisChoice.push_back(suspectChoice);
        const int weaponChoice = engine::UtilityFunctions::randomInt(5)+1;
        hypothesisChoice.push_back(weaponChoice);
        auto& currentRoom = static_cast<state::Room&>(playerInfo->getLocation());
        hypothesisChoice.push_back(currentRoom.getRoomName());

        cout << playerInfo->getIdentity() << " suggests the Crime was committed by "
        << hypothesisChoice.at(0) << " in the " << hypothesisChoice.at(2)
        << " with the " << hypothesisChoice.at(1) << endl;

        return hypothesisChoice;
    }


    vector<int> RandomAI::chooseAccusation () {
       vector<int> accusationChoice;

       const int suspectChoice = engine::UtilityFunctions::randomInt(5)+1;
       accusationChoice.push_back(suspectChoice);
       const int weaponChoice = engine::UtilityFunctions::randomInt(5)+1;
       accusationChoice.push_back(weaponChoice);
       const int roomChoice = engine::UtilityFunctions::randomInt(8)+1;
       accusationChoice.push_back(roomChoice);

       cout << playerInfo->getIdentity() << " accuses "
       << accusationChoice.at(0) << " of committing the crime in the " << accusationChoice.at(2)
       << " with the " << accusationChoice.at(1) << std::endl;

       return accusationChoice;
   }


    engine::CommandId RandomAI::chooseAction () {
       vector<engine::CommandId> possibleActions = engine->getPossibleActions (*playerInfo);
       const int size = static_cast<int>(possibleActions.size());
       const int AIActionChoice = engine::UtilityFunctions::randomInt(size)+1;

       return possibleActions.at(AIActionChoice);
   }



    engine::Move RandomAI::chooseMoveDirection () {

        vector<engine::Move> possibleMoves = engine->getPossibleMoves(*playerInfo);
        const int size = static_cast<int>(possibleMoves.size());
        const int AIMoveDirectionChoice = engine::UtilityFunctions::randomInt(size)+1;

        return possibleMoves.at(AIMoveDirectionChoice);

    }




}

