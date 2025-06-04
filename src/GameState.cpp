#include "GameState.h"
#include "CrosswordLevel.h"
#include "ResourceManager.h"
#include <algorithm>

GameState::GameState(StateMachine& machine, sf::RenderWindow& window, int level)
    : machine(machine), window(window), currentLevel(level) {
}

void GameState::onEnter() {
    createCrossword(currentLevel);
    setupUI();
}

void GameState::onExit() {
}

void GameState::createCrossword(int level) {
    std::vector<Word> words;
    
    switch (level) {
    case 1: words = CrosswordLevel::getLevel1Words(); break;
    case 2: words = CrosswordLevel::getLevel2Words(); break;
    case 3: words = CrosswordLevel::getLevel3Words(); break;
    default: words = CrosswordLevel::getLevel1Words(); break;
    }

    // Calculate required grid size
    int maxX = 0, maxY = 0;
    for (const auto& word : words) {
        for (const auto& pos : word.positions) {
            maxX = std::max(maxX, pos.x);
            maxY = std::max(maxY, pos.y);
        }
    }

    crossword = std::make_unique<Crossword>(maxY + 1, maxX + 1);
    crossword->setFont(ResourceManager::getInstance().getFont("arial"));
    crossword->loadFromWords(words);
}

void GameState::setupUI() {
    auto& font = ResourceManager::getInstance().getFont("arial");

    background.setSize(sf::Vector2f(window.getSize()));
    background.setFillColor(sf::Color(240, 240, 240));

    levelText.setString(L"Уровень " + std::to_wstring(currentLevel));
    levelText.setFont(font);
    levelText.setCharacterSize(36);
    levelText.setFillColor(sf::Color::Black);
    levelText.setStyle(sf::Text::Bold);
    levelText.setPosition(20, 20);

    backButton.setString(L"← Назад");
    backButton.setFont(font);
    backButton.setCharacterSize(28);
    backButton.setFillColor(sf::Color::Blue);
    backButton.setPosition(20, window.getSize().y - 50);

    checkButton.setString(L"Проверить");
    checkButton.setFont(font);
    checkButton.setCharacterSize(28);
    checkButton.setFillColor(sf::Color::Green);
    checkButton.setPosition(window.getSize().x - checkButton.getGlobalBounds().width - 20, window.getSize().y - 50);

    resultText.setString(L"");
    resultText.setFont(font);
    resultText.setCharacterSize(28);
    resultText.setFillColor(sf::Color::Black);
    resultText.setPosition(window.getSize().x / 2 - 100, window.getSize().y - 50);
}

void GameState::handleEvent(const sf::Event& event) {
    crossword->handleEvent(event, window);

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

            if (backButton.getGlobalBounds().contains(mousePos)) {
                machine.changeState(std::make_unique<MainMenuState>(machine, window));
            }
            else if (checkButton.getGlobalBounds().contains(mousePos)) {
                bool isCorrect = crossword->checkSolution();
                if (isCorrect) {
                    resultText.setString(L"Правильно!");
                    resultText.setFillColor(sf::Color::Green);
                }
                else {
                    resultText.setString(L"Есть ошибки!");
                    resultText.setFillColor(sf::Color::Red);
                }
            }
        }
    }
}

void GameState::update(float dt) {
}

void GameState::render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(levelText);
    window.draw(backButton);
    window.draw(checkButton);
    window.draw(resultText);
    crossword->render(window);
}
