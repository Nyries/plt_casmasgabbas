#include "Grid.h"

namespace render {
Grid::Grid(unsigned int x, unsigned int y, unsigned int rows, unsigned int cols, float cellSize, const sf::Color& gridColor)
        : m_xpos(x), m_ypos(y), m_rows(rows), m_cols(cols), m_cellSize(cellSize) {
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
    if (row > 0 && row < m_rows+2 && col > 1 && col < m_cols+2) {
        // Check if a piece already exists at the position
        auto it = std::find_if(m_pieces.begin(), m_pieces.end(), [&](const sf::CircleShape& piece) {
            return piece.getPosition() == sf::Vector2f(col * m_cellSize + m_cellSize / 5, row * m_cellSize + m_cellSize / 5);
        });

        if (it != m_pieces.end()) {
            // If the piece exists, remove it
            m_pieces.erase(it);
        } else {
            // If the piece does not exist, add a new piece
            sf::CircleShape piece(m_cellSize / 2.5f); // Radius slightly smaller than the cell
            piece.setFillColor(pieceColor);
            piece.setPosition(col * m_cellSize + m_cellSize / 5, row * m_cellSize + m_cellSize / 5);
            m_pieces.push_back(piece);
        }
    }
}
void Grid::deletePiece(const sf::Vector2i &mousePos)
{
        unsigned int col = mousePos.x / m_cellSize;
        unsigned int row = mousePos.y / m_cellSize;
        if (row > 0 && row < m_rows+2 && col > 1 && col < m_cols+2) {
            // Check if a piece exists at the position
            auto it = std::find_if(m_pieces.begin(), m_pieces.end(), [&](const sf::CircleShape& piece) {
                return piece.getPosition() == sf::Vector2f(col * m_cellSize + m_cellSize / 5, row * m_cellSize + m_cellSize / 5);
            });

            if (it != m_pieces.end()) {
                // If the piece exists, remove it
                m_pieces.erase(it);
            }
        }
}
}
