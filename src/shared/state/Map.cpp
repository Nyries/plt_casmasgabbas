//
// Created by louismmassin on 10/21/24.
//
#include "Map.h"
#include <json/json.h>
#include <fstream>
#include <iostream>

namespace state {
    Map::Map(std::string mapJsonPath){
        std::ifstream file(mapJsonPath);
        Json::Value jsonData;
        file >> jsonData;
        file.close();
        Json::Value mapData = jsonData["map"]; // Store the map data into a specific variable

        //Creating the rooms 
        roomList.emplace_back(STUDY);
        roomList.emplace_back(HALL);
        roomList.emplace_back(LIVING_ROOM);
        roomList.emplace_back(DINING_ROOM);
        roomList.emplace_back(KITCHEN);
        roomList.emplace_back(BATHROOM);
        roomList.emplace_back(GARAGE);
        roomList.emplace_back(GAME_ROOM);
        roomList.emplace_back(BEDROOM);

        roomList.at(2).addSecretPassage(roomList.at(8));
        roomList.at(8).addSecretPassage(roomList.at(2));
        roomList.at(4).addSecretPassage(roomList.at(6));
        roomList.at(6).addSecretPassage(roomList.at(4));

        //Creating the map grid from the json file
        mapGrid = std::vector<std::vector<Cell>>(jsonData["mapWidth"].asInt(), std::vector<Cell>(jsonData["mapHeight"].asInt(), Cell(0, 0, LocationType::INACCESSIBLE)));
        for (Json::Value cellData : mapData) {
            int x = cellData["x"].asInt();
            int y = cellData["y"].asInt();

            std::string locationType = cellData["LocationType"].asString();
            if (locationType == "INACCESSIBLE")
                mapGrid[x][y] = Cell(x, y, LocationType::INACCESSIBLE);
            else if (locationType == "CORRIDOR")
                mapGrid[x][y] = Cell(x, y, LocationType::CORRIDOR);
            else if (locationType == "DOOR"){
                for (Room room: roomList) {
                    if (room.getNameAsString() == cellData["RoomLink"].asString()) {
                        std::cout << "Room found :" << room.getNameAsString() << std::endl;
                        mapGrid[x][y] = Door(x, y, &room);
                    }
                }
            }
            else if (locationType == "ROOM")
                mapGrid[x][y] = Cell(x, y, LocationType::ROOM);
        }
    }
}