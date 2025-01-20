//
// Created by louismmassin on 1/19/25.
//
#include "Move.hpp"
namespace engine{
    std::string toString(Move move){
        switch(move){
            case MOVE_UP:
                return "move up";
            case MOVE_DOWN:
                return "move down";
            case MOVE_LEFT:
                return "move left";
            case MOVE_RIGHT:
                return "move right";
            case ENTER_ROOM:
                return "enter the room";
            case EXIT_ROOM:
                return "exit the room";
        }
    }
}