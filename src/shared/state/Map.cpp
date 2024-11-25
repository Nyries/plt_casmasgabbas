//
// Created by louismmassin on 10/21/24.
//
#include "Map.h"
#include <json/json.h>
#include <fstream>
#include <iostream>

namespace state {
    Map::Map(const std::string& mapJsonPath){
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
        height = jsonData["mapHeight"].asInt();
        width = jsonData["mapWidth"].asInt();
        mapGrid = std::vector<std::vector<Cell>>(width, std::vector<Cell>(height, Cell(0, 0, LocationType::INACCESSIBLE)));
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
    std::vector<std::vector<std::string>> Map::getDisplayMap()
    {
        std::vector<std::vector<std::string>> displayMap(2*height+1, std::vector<std::string>(2*width+1, ""));  
        
        for (int i=0; i< 2*height+1; i++){
            for (int j=0; j<2*width+1; j++){
                if (i%2==0){
                    displayMap[i][j] ='-';
                }
                else if (j%2==0){
                    displayMap[i][j] = '|';
                }
                else if (mapGrid[j/2][i/2].getType() == LocationType::CORRIDOR){
                    displayMap[i][j] = ' ';
                }
                else if (mapGrid[j/2][i/2].getType() == LocationType::ROOM){
                    displayMap[i][j] = 'R';
                }                
                else if (mapGrid[j/2][i/2].getType() == LocationType::INACCESSIBLE){
                    displayMap[i][j] = 'X';
                }
                else if (mapGrid[j/2][i/2].getType() == LocationType::DOOR){
                    displayMap[i][j] = 'D';
                }
            }
        }
        return displayMap;
    }
    std::vector<std::vector<Cell>> Map::getMapGrid()
    {
        return this->mapGrid;
    }
    int Map::getHeight()
    {
        return this->height;
    }
    int Map::getWidth()
    {
        return this->width;
    }
}