#include "ColorChart.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

namespace render
{
    ColorChart::colors = {
        {"cluedoRed", sf::Color(180, 0, 0)},
        {"cluedoBlue", sf::Color(0, 64, 128)},
        {"cluedoLightBlue", sf::Color(61, 173, 243)},
        {"cluedTurquoise", sf::Color(0, 128, 128)},
        {"cluedoBeige", sf::Color(191, 128, 128)},
        {"cluedoGreenGray", sf::Color(132, 145, 134)}
    };
    std::vector<sf::Color> ColorChart::getColors()
    {
        return std::vector<sf::Color>();
    }

} // namespace render
