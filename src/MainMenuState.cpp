#include "../include/MainMenuState.h"

MainMenuState::MainMenuState(StateManager& manager) : State(manager) {
    font = utils::loadFont("fonts/arial.ttf");
    
    titleText.setFont(font);
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::Blue);
    titleText.setString("Исторический кроссворд");
    titleText.setPosition(150, 50);
    
    std::vector<std::string> items = {
        "Уровень 1: Киевская Русь",
        "Уровень 2: Монголо-татарское иго",
        "Уровень 3: Эпоха Петра I",
        "Выход"
    };
    
    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(32);
        text.setFillColor(sf::Color::Black);
        text.setString(items[i]);
        text.setPosition(200, 150 + i * 60);
        
        menuItems.push_back(text);
        
        sf::RectangleShape button(sf::Vector2f(400, 50));
        button.setPosition(150, 150 + i * 60);
        button.setFillColor(sf::Color(200, 230, 255, 150));
        button.setOutlineThickness(2);
        button.setOutlineColor(sf::Color::Blue);
        
        buttons.push_back(button);
    }
}

void MainMenuState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*manager.getWindow());
        
        for (size_t i = 0; i < buttons.size(); ++i) {
            if (buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if (i < 3) {
                    manager.changeState(std::make_unique<GameState>(manager, static_cast<int>(i + 1)));
                } else if (i == 3) {
                    manager.getWindow()->close();
                }
                break;
            }
        }
    }
}

void MainMenuState::update(float dt) {
    // Nothing to update for now
}

void MainMenuState::draw(sf::RenderWindow& window) {
    window.clear(sf::Color(240, 240, 240));
    
    // Draw background
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(240, 240, 240));
    window.draw(background);
    
    // Draw title
    window.draw(titleText);
    
    // Draw buttons
    for (const auto& button : buttons) {
        window.draw(button);
    }
    
    // Draw menu items
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}
