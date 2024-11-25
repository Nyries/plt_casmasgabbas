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

    std::string Location::getTypeAsString()
    {
		if (type == LocationType::INACCESSIBLE){
			return "INACCESSIBLE";
		}
		else if (type == LocationType::CORRIDOR){
			return "CORRIDOR";
		}
		else if (type == LocationType::DOOR){
			return "DOOR";
		}
		else if (type == LocationType::ROOM){
			return "ROOM";
		}
		else{
        	return "Mouais";
		}
    }
}