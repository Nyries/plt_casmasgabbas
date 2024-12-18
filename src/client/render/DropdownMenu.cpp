#include "DropdownMenu.h"

namespace render{
    DropdownMenu::DropdownMenu(float x, float y, const std::vector<std::string> &options)
    : m_position(x, y), m_options(options), m_isOpen(false) {

        // Créer le fond du menu déroulant
        m_box.setSize(sf::Vector2f(200, 40));
        m_box.setPosition(m_position);
        m_box.setFillColor(sf::Color(200, 200, 200));

        // Créer le texte pour afficher le choix
        m_text.setFont(m_font);
        m_text.setString(options.empty() ? "Select an option" : options[0]);
        m_text.setCharacterSize(20);
        m_text.setFillColor(sf::Color::Black);
        m_text.setPosition(m_position.x + 10, m_position.y + 5); // Légèrement décalé dans la boîte

        // Charger la police pour le texte
        if (!m_font.loadFromFile("../ressources/fonts/Futura-Condensed-Extra-Bold.ttf")) {
            // Gérer l'erreur si la police ne se charge pas
        }

        // Créer les boutons pour les choix
        for (size_t i = 0; i < m_options.size(); ++i) {
            sf::RectangleShape choiceBox(sf::Vector2f(200, 40));
            choiceBox.setPosition(m_position.x, m_position.y + (i + 1) * 40);
            choiceBox.setFillColor(sf::Color(240, 240, 240));

            sf::Text choiceText;
            choiceText.setFont(m_font);
            choiceText.setString(m_options[i]);
            choiceText.setCharacterSize(20);
            choiceText.setFillColor(sf::Color::Black);
            choiceText.setPosition(m_position.x + 10, m_position.y + (i + 1) * 40 + 5);

            m_choices.push_back(std::make_pair(choiceBox, choiceText));
        }
    }

    void DropdownMenu::draw(sf::RenderWindow& window) {
        // Dessiner le fond et le texte de la barre déroulante
        window.draw(m_box);
        window.draw(m_text);

        // Si le menu est ouvert, dessiner les choix
        if (m_isOpen) {
            for (const auto& choice : m_choices) {
                window.draw(choice.first);
                window.draw(choice.second);
            }
        }
    }

    void DropdownMenu::handleClick(const sf::Vector2i& mousePos) {
        // Vérifier si l'utilisateur a cliqué sur le menu déroulant
        if (m_box.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            // Ouvrir/fermer la liste déroulante
            m_isOpen = !m_isOpen;
        }

        // Si le menu est ouvert, vérifier si l'utilisateur a cliqué sur un choix
        if (m_isOpen) {
            for (size_t i = 0; i < m_choices.size(); ++i) {
                if (m_choices[i].first.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Changer le texte du menu en fonction du choix sélectionné
                    m_text.setString(m_options[i]);
                    m_isOpen = false;
                    break;
                }
            }
        }
    }

}