//
// Created by louismmassin on 1/10/25.
//

#ifndef ROOMNAME_HPP
#define ROOMNAME_HPP

#include "RoomName.h"
#include <ostream>

namespace state{
    std::ostream& operator<<(std::ostream& os, RoomName roomName);
}
#endif //ROOMNAME_HPP
