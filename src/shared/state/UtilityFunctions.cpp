//
// Created by louismmassin on 10/23/24.
//
#include "UtilityFunctions.h"

#include <random>

namespace state {
    int UtilityFunctions::randomInt(int range) {
        static std::random_device generator;
        std::uniform_int_distribution<int> distribution(0,range -1);
        int randomResult = distribution(generator);
        return randomResult;
    }

}
