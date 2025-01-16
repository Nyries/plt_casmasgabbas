#include "TextBox.h"

#include <iostream>

render::TextBox::TextBox(const sf::Vector2f &size, const std::string &fontPath, const std::string &textString)
{
    setSize(size);
    setFillColor(sf::Color::White);
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(2);

    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
    }

    text.setFont(font);
    text.setString(textString);
    text.setFillColor(sf::Color::Black);
    
    // Positionner le texte au centre du rectangle
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text.setPosition(getPosition().x + size.x / 2, getPosition().y + size.y / 2);
}

void render::TextBox::draw(sf::RenderWindow &window)
{
    window.draw(*this);
    window.draw(text);
}
