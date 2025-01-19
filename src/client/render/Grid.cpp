#include "Grid.h"

#include "RenderCell.h"

namespace render {

Grid::Grid (sf::RenderWindow& window, int rows, int cols, float width, float height) : Entity(window), rows(rows), cols(cols), cellWidth(width / cols), cellHeight(height / rows)
{
        this->children.clear();
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                sf::Color color(255, 255, 153);
                this->children.push_back(std::make_unique<RenderCell>(window, x * cellWidth, y * cellHeight, cellWidth, cellHeight, x, y, color));}
        }
}
void Grid::draw()
{
    for (auto &child : children)
    {
        child->draw();
    }
}
}