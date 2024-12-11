//
// Created by louismmassin on 10/21/24.
//
#include "Location.h"
namespace state{
	Location::Location(LocationType type): type(type) {

	}

    Location::~Location()=default;


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

    void Location::setType(LocationType type)
    {
		this->type = type;
    }

    void Location::setTypeAsString(std::string type)
    {
		if (type == "INACCESSIBLE"){
			this->type = LocationType::INACCESSIBLE;}
		else if (type == "CORRIDOR"){
			this->type = LocationType::CORRIDOR;}
		else if (type == "DOOR"){
			this->type = LocationType::DOOR;}
		else if (type == "ROOM"){
			this->type = LocationType::ROOM;}
		else{
			this->type = LocationType::INACCESSIBLE;}

    }
}