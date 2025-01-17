#include "Grid.h"

#include "RenderCell.h"

namespace render {

Grid::Grid (int rows, int cols, float width, float height) : rows(rows), cols(cols), cellWidth(width / cols), cellHeight(height / rows)
{
        this->children.clear();
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                sf::Color color(255, 255, 153);
                this->children.push_back(std::make_unique<RenderCell>(x * cellWidth, y * cellHeight, cellWidth, cellHeight, x, y, color));}
        }
}
void Grid::draw(sf::RenderWindow& window)
{
    for (auto &child : children)
    {
        child->draw(window);
    }
}
}