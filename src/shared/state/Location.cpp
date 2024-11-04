//
// Created by louismmassin on 10/21/24.
//
#include "Location.h"
namespace state{
	Location::Location(LocationType type): type(type) {

	}

	LocationType Location::getType(){
          return type;
    }
}