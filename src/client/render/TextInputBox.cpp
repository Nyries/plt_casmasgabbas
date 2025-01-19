#include "TextInputBox.h"

#include <iostream>
#include <string>

namespace render {
TextInputBox::TextInputBox(float x, float y, float width, float height, const sf::Font &font) : m_isSelected(false), m_textString("") {
    m_box.setPosition(x, y);
    m_box.setSize(sf::Vector2f(width, height));
    m_box.setFillColor(sf::Color::White);
    m_box.setOutlineColor(sf::Color::Black);
    m_box.setOutlineThickness(1);

    m_text.setFont(font);
    m_text.setCharacterSize(20);
    m_text.setFillColor(sf::Color::Black);
    m_text.setPosition(x + 5, y + 5);

    m_cursor.setSize(sf::Vector2f(1, 20));
    m_cursor.setFillColor(sf::Color::Black);
    m_cursor.setPosition(x + 5, y + 5);

}
void TextInputBox::handleClick(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed){
        if (m_box.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
            m_isSelected = true;
            m_box.setFillColor(sf::Color::White);
        } else {
            m_isSelected = false;
            m_box.setFillColor(sf::Color(200, 200, 200));
        }
    }
}
void TextInputBox::handleTextEntered(const sf::Event &event)
{
        if (m_isSelected && event.type == sf::Event::TextEntered){
        std::cout << "Text entered: " << event.text.unicode << std::endl;
        if (event.text.unicode == 8 && m_textString.size() > 0){
            m_textString.pop_back();
        } else if (event.text.unicode < 128 && event.text.unicode != 13){
            m_textString += static_cast<char>(event.text.unicode);
        }
        updateText();
    } 
}
void TextInputBox::handleEnterPressed(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter){  
        m_isSelected = false;
        m_box.setFillColor(sf::Color(200, 200, 200));   
    }
}
void TextInputBox::draw(sf::RenderWindow &window)
{
    window.draw(m_box);
    window.draw(m_text);
    if (m_isSelected){
        m_cursor.setPosition(m_text.getGlobalBounds().left + m_text.getGlobalBounds().width + 5, m_text.getGlobalBounds().top);
        window.draw(m_cursor);
    }
}
std::string TextInputBox::getText() const
{
    return m_textString;
}
void TextInputBox::updateText()
{
    m_text.setString(m_textString);
}
} // namespace render