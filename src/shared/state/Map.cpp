//
// Created by louismmassin on 10/21/24.
//
#include "Map.h"
#include <json/json.h>
#include <fstream>
#include <iostream>
#include <memory>

namespace state {
    Map::Map(const std::string& mapJsonPath){
        //system("ls ../../../test/shared;");
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

        roomList.at(2).setSecretPassage(roomList.at(8));
        roomList.at(4).setSecretPassage(roomList.at(6));

        //Creating the map grid from the json file
        height = jsonData["mapHeight"].asInt();
        width = jsonData["mapWidth"].asInt();
        mapGrid.resize(width);
        for (auto& vec: mapGrid) {
            vec.resize(height);
        }
        for (Json::Value cellData : mapData) {
            int x = cellData["x"].asInt();
            int y = cellData["y"].asInt();

            std::string locationType = cellData["LocationType"].asString();
            if (locationType == "INACCESSIBLE")
                mapGrid[x][y] = std::make_unique<Cell>(x, y, LocationType::INACCESSIBLE);
            else if (locationType == "CORRIDOR")
                mapGrid[x][y] = std::make_unique<Cell>(x, y, LocationType::CORRIDOR);
            else if (locationType == "DOOR"){
                for (Room& room: roomList) {
                    if (room.getNameAsString() == cellData["RoomLink"].asString()) {
                        mapGrid[x][y] = std::make_unique<Door>(x, y, &room);

                    }
                }
            }
            else if (locationType == "ROOM")
                mapGrid[x][y] = std::make_unique<Cell>(x, y, LocationType::ROOM);
        }
    }
    std::vector<std::vector<std::string>> Map::getDisplayMap() const
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
                else if (mapGrid[j/2][i/2]->getType() == LocationType::CORRIDOR){
                    const auto& castCell = static_cast<const Cell&>(*mapGrid[j/2][i/2]);
                    if (castCell.getOccupied()) {
                        displayMap[i][j] = 'O';
                    }
                    else{
                        displayMap[i][j] = ' ';
                    }
                }
                else if (mapGrid[j/2][i/2]->getType() == LocationType::ROOM){
                    displayMap[i][j] = 'R';
                }                
                else if (mapGrid[j/2][i/2]->getType() == LocationType::INACCESSIBLE){
                    displayMap[i][j] = 'X';
                }
                else if (mapGrid[j/2][i/2]->getType() == LocationType::DOOR){
                    const auto& castCell = static_cast<const Door&>(*mapGrid[j/2][i/2]);
                    if (castCell.getOccupied()) {
                        displayMap[i][j] = 'O';
                    }
                    else{
                        displayMap[i][j] = 'D';
                    }
                }
            }
        }
        return displayMap;
    }


    std::vector<Room>& Map::getRoomList()
    {
        return roomList;
    }

    int Map::getHeight()
    {
        return this->height;
    }
    int Map::getWidth()
    {
        return this->width;
    }
    std::vector<Cell*> Map::getNeighborsAsCell(int coordX, int coordY)
    {
        if (coordX < 1 or coordX > mapGrid.size() - 2 or coordY < 1 or coordY > mapGrid.front().size() - 2) {
            throw std::invalid_argument("invalid coordinates");
        }
        //order: up, down, left, right
        std::vector<Cell*> neighborList(4);
        neighborList.at(0) = &*mapGrid[coordX][coordY - 1];
        neighborList.at(1) = &*mapGrid[coordX][coordY + 1];
        neighborList.at(2) = &*mapGrid[coordX - 1][coordY];
        neighborList.at(3) = &*mapGrid[coordX + 1][coordY];
        return neighborList;
    }


    std::vector<LocationType> Map::getNeighborsAsLocationType(int coordX, int coordY) const
    {
        /**The order of the list is as follow: up, down, left, right*/
        std::vector<LocationType> neighbors(4, LocationType::INACCESSIBLE);
        neighbors.at(0) = getCell(coordX, coordY - 1).getType();
        neighbors.at(1) = getCell(coordX, coordY + 1).getType();
        neighbors.at(2) = getCell(coordX - 1, coordY).getType();
        neighbors.at(3) = getCell(coordX + 1, coordY).getType();
        return neighbors;
    }

    Cell &Map::getCell(int coordX, int coordY) {
        return *mapGrid.at(coordX).at(coordY);
    }

    const Cell &Map::getCell(int coordX, int coordY) const {
        return *mapGrid.at(coordX).at(coordY);
    }


}
