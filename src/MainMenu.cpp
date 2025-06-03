#include "MainMenu.h"
#include "Utils.h"
#include <iostream>

MainMenu::MainMenu() {
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    setupUI();
}

void MainMenu::setLevelCallback(LevelCallback callback) {
    m_levelCallback = callback;
}

void MainMenu::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        for (size_t i = 0; i < m_levelButtons.size(); ++i) {
            if (m_levelButtons[i].getGlobalBounds().contains(mousePos) && m_levelCallback) {
                m_levelCallback(static_cast<int>(i) + 1);
                break;
            }
        }
    }
}

void MainMenu::update(float dt) {
    // No update logic needed for now
}

void MainMenu::render(sf::RenderWindow& window) {
    window.clear(sf::Color(240, 240, 240));

    window.draw(m_titleText);

    for (const auto& button : m_levelButtons) {
        window.draw(button);
    }

    for (const auto& text : m_levelButtonTexts) {
        window.draw(text);
    }
}

void MainMenu::onResize(const sf::Vector2u& newSize) {
    m_windowSize = newSize;
    centerUI();
}

void MainMenu::setupUI() {
    // Title
    m_titleText.setFont(m_font);
    m_titleText.setString("Исторический кроссворд");
    m_titleText.setCharacterSize(48);
    m_titleText.setFillColor(sf::Color::Black);

    // Level buttons
    for (int i = 1; i <= 3; ++i) {
        sf::RectangleShape button({300, 80});
        button.setFillColor(sf::Color(200, 200, 255));
        button.setOutlineThickness(2);
        button.setOutlineColor(sf::Color::Black);

        sf::Text text;
        text.setFont(m_font);
        text.setString("Уровень " + std::to_string(i));
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);

        m_levelButtons.push_back(button);
        m_levelButtonTexts.push_back(text);
    }

    centerUI();
}

void MainMenu::centerUI() {
    Utils::centerText(m_titleText, m_windowSize, -150);

    float startY = m_windowSize.y / 2 - 100;
    for (size_t i = 0; i < m_levelButtons.size(); ++i) {
        m_levelButtons[i].setPosition(
            m_windowSize.x / 2 - m_levelButtons[i].getSize().x / 2,
            startY + i * 100
        );

        m_levelButtonTexts[i].setPosition(
            m_windowSize.x / 2 - m_levelButtonTexts[i].getLocalBounds().width / 2,
            startY + i * 100 + m_levelButtons[i].getSize().y / 2 - m_levelButtonTexts[i].getLocalBounds().height / 2 - 5
        );
    }
}
