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
                        mapGrid[x][y] = Door(x, y, &room);
                    }
                }
            }
            else if (locationType == "ROOM")
                mapGrid[x][y] = Cell(x, y, LocationType::ROOM);
        }
    }
    
    Map::~Map() =default;

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
    
    std::vector<Room> Map::getRoomList()
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
        /**The order of the list is as follow: up, down, left, right*/
        std::vector<Cell*> neighbors(4, new Cell(0, 0, LocationType::INACCESSIBLE));
        // Case where coordX or coordY are not in the bounds of the map
        if (coordX < 0 or coordX > width or coordY < 0 or coordY > height){
            return neighbors;
        }
        // Cases where coordX or coordY are on the edge of the map
        else if (coordX == 0){
            neighbors.at(0) = &mapGrid[coordX][coordY-1];
            neighbors.at(1) = &mapGrid[coordX][coordY+1];
            neighbors.at(2) = new Cell(coordX-1, coordY, LocationType::INACCESSIBLE);
            neighbors.at(3) = &mapGrid[coordX+1][coordY];
        }
        else if (coordY == 0){
            neighbors.at(0) = new Cell(coordX, coordY-1, LocationType::INACCESSIBLE);
            neighbors.at(1) = &mapGrid[coordX][coordY+1];
            neighbors.at(2) = &mapGrid[coordX-1][coordY];
            neighbors.at(3) = &mapGrid[coordX+1][coordY];
        }
        else if (coordX == width){
            neighbors.at(0) = &mapGrid[coordX][coordY-1];
            neighbors.at(1) = &mapGrid[coordX][coordY+1];
            neighbors.at(2) = &mapGrid[coordX-1][coordY];
            neighbors.at(3) = new Cell(coordX+1, coordY, LocationType::INACCESSIBLE);
        }
        else if (coordY == height){
            neighbors.at(0) = &mapGrid[coordX][coordY-1];
            neighbors.at(1) = new Cell(coordX, coordY+1, LocationType::INACCESSIBLE);
            neighbors.at(2) = &mapGrid[coordX+1][coordY];
            neighbors.at(3) = &mapGrid[coordX-1][coordY];
        }
        // General Case in the middle of the map
        else {
            neighbors.at(0) = &mapGrid[coordX][coordY-1];
            neighbors.at(1) = &mapGrid[coordX][coordY+1];
            neighbors.at(2) = &mapGrid[coordX-1][coordY];
            neighbors.at(3) = &mapGrid[coordX+1][coordY];
        }
    }
    std::vector<LocationType> Map::getNeighborsAsLocationType(int coordX, int coordY)
    {
        /**The order of the list is as follow: up, down, left, right*/
        std::vector<LocationType> neighbors(4, LocationType::INACCESSIBLE);
        std::vector<Cell*> neighboringCells = this->getNeighborsAsCell(coordX ,coordY);
        for (int i=0; i<4; i++){
            neighbors.at(i) = neighboringCells.at(i)->getType();
        }
        return neighbors;
    }
}