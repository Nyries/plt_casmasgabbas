//
// Created by louismmassin on 11/18/24.
//
#include <fstream>
#include <random>

#include "engine.h"

namespace engine {
    int UtilityFunctions::randomInt(int range) {
        static std::random_device generator;
        static std::uniform_int_distribution<int> distribution(0,range - 1);
        const int randomResult = distribution(generator);
        return randomResult;
    }

    Json::Value UtilityFunctions::jsonConversion(std::string jsonPath) {
        Json::Value root;
        std::ifstream file(jsonPath, std::ifstream::binary);
        if (!file) {
            throw std::runtime_error("Failed to open JSON file: " + jsonPath);
        }

        file >> root; // Parse le fichier JSON
        return root;
    }

}