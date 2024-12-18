#include "Grid.h"

namespace render {
Grid::Grid(unsigned int x, unsigned int y, unsigned int rows, unsigned int cols, float cellSize, const sf::Color& gridColor)
        : m_rows(rows), m_cols(cols), m_cellSize(cellSize) {
        // Créer les cases de la grille
        this->setPosition(x, y);
        for (unsigned int row = 0; row < rows; ++row) {
            for (unsigned int col = 0; col < cols; ++col) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(x + col * cellSize, y + row * cellSize);
                cell.setFillColor(sf::Color::Transparent);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(gridColor);
                m_cells.push_back(cell);
            }
        }
}

void Grid::draw(sf::RenderWindow &window)
{
        for (const auto& cell : m_cells) {
            window.draw(cell);
        }
 
        for (const auto& piece : m_pieces) {
            window.draw(piece);
        }
}

void Grid::placePiece(const sf::Vector2i &mousePos, const sf::Color &pieceColor)
{
        unsigned int col = mousePos.x / m_cellSize;
        unsigned int row = mousePos.y / m_cellSize;

        if (row < m_rows && col < m_cols) {
            sf::CircleShape piece(m_cellSize / 2.5f); // Rayon légèrement plus petit que la case
            piece.setFillColor(pieceColor);
            piece.setPosition(col * m_cellSize + m_cellSize / 5, row * m_cellSize + m_cellSize / 5);
            m_pieces.push_back(piece);
        }
}
}
