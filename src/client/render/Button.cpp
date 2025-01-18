#include "Button.h"

namespace render {
Button::Button(sf::RenderWindow& window, float x, float y, float width, float height, const std::string &label, const sf::Font &font): Entity(window)
{
        m_box.setSize(sf::Vector2f(width, height));
        m_box.setPosition(x, y);
        m_box.setFillColor(sf::Color(200, 200, 200)); 

        m_text.setFont(font);
        m_text.setString(label);
        m_text.setCharacterSize(24);
        m_text.setFillColor(sf::Color::Black);

        sf::FloatRect textBounds = m_text.getLocalBounds();
        m_text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        m_text.setPosition(x + width / 2.0f, y + height / 2.0f);
}

void Button::draw()
{
        window.draw(m_box);
        window.draw(m_text);
}

bool Button::isClicked() const
{
        sf::Vector2i mousePos(sf::Mouse::getPosition(window));
        return m_box.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Button::setFillColor(const sf::Color &color)
{
        m_box.setFillColor(color);
}
}