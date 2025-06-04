#include "../include/GameState.h"
#include "../include/Level.h"
#include <vector>

GameState::GameState(StateManager& manager, int level) 
    : State(manager), currentLevel(level), isComplete(false) {
    
    font = utils::loadFont("fonts/arial.ttf");
    
    levelText.setFont(font);
    levelText.setCharacterSize(36);
    levelText.setFillColor(sf::Color::Black);
    levelText.setString("Уровень " + std::to_string(currentLevel));
    levelText.setPosition(20, 20);
    
    completeText.setFont(font);
    completeText.setCharacterSize(24);
    completeText.setFillColor(sf::Color::Green);
    completeText.setString("Кроссворд решен!");
    completeText.setPosition(20, 70);
    
    backText.setFont(font);
    backText.setCharacterSize(24);
    backText.setFillColor(sf::Color::Blue);
    backText.setString("Назад в меню");
    backText.setPosition(20, 120);
    
    createCrossword();
}

void GameState::createCrossword() {
    Level level;
    
    switch (currentLevel) {
        case 1: level = Levels::getLevel1(); break;
        case 2: level = Levels::getLevel2(); break;
        case 3: level = Levels::getLevel3(); break;
        default: level = Levels::getLevel1(); break;
    }
    
    std::vector<CrosswordDefinition> definitions;
    
    for (size_t i = 0; i < level.words.size(); ++i) {
        CrosswordDefinition def;
        def.word = level.words[i];
        def.definition = level.definitions[i];
        def.startX = level.positions[i].first;
        def.startY = level.positions[i].second;
        def.horizontal = level.orientations[i];
        
        definitions.push_back(def);
    }
    
    crossword = std::make_unique<Crossword>(definitions, level.gridSize);
}

void GameState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*manager.getWindow());
        
        if (backText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            manager.changeState(std::make_unique<MainMenuState>(manager));
            return;
        }
    }
    
    if (!isComplete) {
        crossword->handleEvent(event, *manager.getWindow());
        
        if (crossword->isComplete()) {
            isComplete = true;
        }
    }
}

void GameState::update(float dt) {
    // Nothing to update for now
}

void GameState::draw(sf::RenderWindow& window) {
    window.clear(sf::Color(240, 240, 240));
    
    drawHeader(window);
    crossword->draw(window, font);
    
    if (isComplete) {
        window.draw(completeText);
    }
    
    window.draw(backText);
}

void GameState::drawHeader(sf::RenderWindow& window) {
    window.draw(levelText);
    
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(20);
    infoText.setFillColor(sf::Color::Black);
    infoText.setString("Кликните на клетку и введите букву. Backspace - удалить букву.");
    infoText.setPosition(20, 60);
    
    window.draw(infoText);
}
