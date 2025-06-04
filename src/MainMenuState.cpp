#include "MainMenuState.h"
#include "GameState.h"
#include "ResourceManager.h"

MainMenuState::MainMenuState(StateMachine& machine, sf::RenderWindow& window)
    : machine(machine), window(window) {
}

void MainMenuState::onEnter() {
    auto& font = ResourceManager::getInstance().getFont("arial");

    background.setSize(sf::Vector2f(window.getSize()));
    background.setFillColor(sf::Color(240, 240, 240));

    title.setString(L"Кроссворд по истории");
    title.setFont(font);
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);
    title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 50);

    level1Button.setString(L"1. Лёгкий уровень");
    level1Button.setFont(font);
    level1Button.setCharacterSize(32);
    level1Button.setFillColor(sf::Color::Black);
    level1Button.setPosition(window.getSize().x / 2 - level1Button.getGlobalBounds().width / 2, 200);

    level2Button.setString(L"2. Средний уровень");
    level2Button.setFont(font);
    level2Button.setCharacterSize(32);
    level2Button.setFillColor(sf::Color::Black);
    level2Button.setPosition(window.getSize().x / 2 - level2Button.getGlobalBounds().width / 2, 280);

    level3Button.setString(L"3. Сложный уровень");
    level3Button.setFont(font);
    level3Button.setCharacterSize(32);
    level3Button.setFillColor(sf::Color::Black);
    level3Button.setPosition(window.getSize().x / 2 - level3Button.getGlobalBounds().width / 2, 360);

    exitButton.setString(L"Выход");
    exitButton.setFont(font);
    exitButton.setCharacterSize(32);
    exitButton.setFillColor(sf::Color::Black);
    exitButton.setPosition(window.getSize().x / 2 - exitButton.getGlobalBounds().width / 2, 440);
}

void MainMenuState::onExit() {
}

void MainMenuState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

            if (level1Button.getGlobalBounds().contains(mousePos)) {
                machine.changeState(std::make_unique<GameState>(machine, window, 1));
            }
            else if (level2Button.getGlobalBounds().contains(mousePos)) {
                machine.changeState(std::make_unique<GameState>(machine, window, 2));
            }
            else if (level3Button.getGlobalBounds().contains(mousePos)) {
                machine.changeState(std::make_unique<GameState>(machine, window, 3));
            }
            else if (exitButton.getGlobalBounds().contains(mousePos)) {
                window.close();
            }
        }
    }
}

void MainMenuState::update(float dt) {
}

void MainMenuState::render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(title);
    window.draw(level1Button);
    window.draw(level2Button);
    window.draw(level3Button);
    window.draw(exitButton);
}
