//
// Created by louismmassin on 11/18/24.
//
#include <random>

#include "engine.h"

namespace engine {
    int UtilityFunctions::randomInt(int range) {
        static std::random_device generator;
        static std::uniform_int_distribution<int> distribution(0,range -1);
        const int randomResult = distribution(generator);
        return randomResult;
    }

    Json::Value UtilityFunctions::jsonConversion(std::string jsonPath) {

    }

}