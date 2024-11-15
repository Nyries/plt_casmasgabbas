//
// Created by louismmassin on 11/15/24.
//

#include <json/json.h>
#include <fstream>
#include <iostream>
namespace state {
    void test() {
        std::ifstream file("../map.json");
        Json::Value jsonData;
        file >> jsonData;
        std::cout << jsonData["map"].size() << std::endl;
    };
}