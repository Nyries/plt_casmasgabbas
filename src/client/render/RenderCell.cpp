#include "RenderCell.h"

namespace render {

RenderCell::RenderCell ( int gridX, int gridY, float x, float y, float width, float height, sf::Color color)
: Panel(x, y, width, height, color), gridX(gridX), gridY(gridY){

    }
}