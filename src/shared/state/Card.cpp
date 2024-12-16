//
// Created by louismmassin on 11/4/24.
//

#include "Card.h"
namespace state {
    Card::Card(CardType type): type(type) {
    }

    CardType Card::getType() {
        return type;
    }




}