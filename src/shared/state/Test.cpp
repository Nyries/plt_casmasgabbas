//
// Created by louismmassin on 11/15/24.
//

#include <json/json.h>
#include <fstream>
#include <iostream>
namespace state {
    void test() {
        std::ifstream file("../src/client/map.json");
        if (!file.is_open()) {
            std::cout << "Error opening file" << std::endl;
            return;
        }
        Json::Value jsonData;
        file >> jsonData;
        std::cout << jsonData["map"].size() << std::endl;
    };
}