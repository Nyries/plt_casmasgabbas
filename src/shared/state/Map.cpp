//
// Created by louismmassin on 10/21/24.
//
#include "Map.h"
#include "LocationType.h"

namespace state {
    Map::Map(std::string jsonPath) {
        std::ifstream file(jsonPath);
        Json::Value jsonData;
        file >> jsonData;
        file.close();
        Json::Value mapData = jsonData["map"]; // Store the map data into a specific variable
        for (Json::Value cellData : mapData) {
            int x = cellData["x"].asInt();
            int y = cellData["y"].asInt();
            std::string locationType = cellData["LocationType"].asString();
            if (locationType == "UNATTEIGNABLE")
                Map::mapArray[x][y] = Cell(INACCESSIBLE, x, y);
            else if (locationType == "PORTE")
                Map::mapArray[x][y] = Cell(DOOR, x, y);
            else if (locationType == "COULOIR")
                Map::mapArray[x][y] = Cell(CORRIDOR, x, y);
            else if (locationType == "SALLE")
                Map::mapArray[x][y] = Cell(ROOM, x, y);
        }
        

    }

}

