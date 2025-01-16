#include "Grid.h"

#include <fstream>
#include <json/json.h>

namespace render {
    Grid::Grid(int rows, int cols, float width, float height) : rows(rows), cols(cols), cellWidth(width / cols), cellHeight(height / rows)
    {
        createGrid();
    }

    void Grid::createGrid()
    {
        cells.clear();
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                sf::Color color(255, 255, 153);
                RenderCell cell(x * cellWidth, y * cellHeight, cellWidth, cellHeight, x, y);
                cells.push_back(cell); 
            }
        }
    }

    void Grid::mergeCells(int startX, int startY, int endX, int endY, sf::Color& color)
    {
        float mergedWidth = (endX - startX + 1) * cellWidth;
        float mergedHeight = (endY - startY + 1) * cellHeight;

        // Créer une nouvelle cellule fusionnée
        sf::RectangleShape mergedCell;
        mergedCell.setPosition(startX * cellWidth, startY * cellHeight);
        mergedCell.setSize({mergedWidth, mergedHeight});
        mergedCell.setFillColor(color);
        mergedCell.setOutlineColor(sf::Color::Black);
        mergedCell.setOutlineThickness(1);

        // Marquer les cellules fusionnées comme inutilisées
        for (auto& cell : cells) {
            if (cell.gridX >= startX && cell.gridX <= endX &&
                cell.gridY >= startY && cell.gridY <= endY) {
                cell.isMerged = true;
            }
        }

        // Ajouter la cellule fusionnée à la liste
        RenderCell cell(mergedCell.getPosition().x, mergedCell.getPosition().y,
                        mergedCell.getSize().x, mergedCell.getSize().y, startX, startY);
        cells.push_back(cell);
    }

    void Grid::draw(sf::RenderWindow &window)
    {
        for (const auto& cell : cells) {
            if (!cell.isMerged) {
                window.draw(cell);
            }
        }
    }

    void Grid::setPosition(float x, float y)
    {
        for (auto& cell : cells) {
            cell.setPosition(cell.getPosition().x + x, cell.getPosition().y + y);
        }
    }

    void Grid::setScale(float factorX, float factorY)
    {
        float firstCellX = cells.front().getPosition().x;
        float firstCellY = cells.front().getPosition().y;

        for (auto& cell : cells) {
            cell.setScale(factorX, factorY);
            float newX = firstCellX + (cell.getPosition().x - firstCellX) * factorX;
            float newY = firstCellY + (cell.getPosition().y - firstCellY) * factorY;
            cell.setPosition(newX, newY);
        }
    }

void Grid::mergeFromJson(std::string mapJsonPath)
{
        std::ifstream file(mapJsonPath);
        Json::Value jsonData;
        file >> jsonData;
        file.close();
        Json::Value mapData = jsonData["map"];

        for (Json::Value cellData : mapData) {
            int x = cellData["x"].asInt();
            int y = cellData["y"].asInt();

            std::string locationType = cellData["LocationType"].asString();
            if (locationType == "INACCESSIBLE") {
                sf::Color color(255, 255, 255);
                getRenderCellUsingCoordinate(x, y).setFillColor(color);
                getRenderCellUsingCoordinate(x, y).setOutlineColor(color); 
            } else if (locationType == "CORRIDOR") {
                sf::Color color(255, 255, 153);
                getRenderCellUsingCoordinate(x, y).setFillColor(color);
            } else if (locationType == "DOOR") {
                sf::Color color(255, 0, 0);
                getRenderCellUsingCoordinate(x, y).setFillColor(color);
            } else if (locationType == "ROOM") {
                std::string roomType = cellData["RoomType"].asString();
                sf::Color color(153, 204, 255);
                getRenderCellUsingCoordinate(x, y).setFillColor(color);
                getRenderCellUsingCoordinate(x, y).setOutlineColor(color);
            }
        }
}

RenderCell &Grid::getRenderCellUsingCoordinate(int x, int y)
{
    for (auto &cell : cells) {
        if (cell.gridX == x && cell.gridY == y) {
            return cell;
        }
    }
}

/*void Grid::placePiece(const sf::Vector2i &mousePos, const sf::Color &pieceColor)
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
}*/
}
