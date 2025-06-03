#include "SimpleRenderer.h"
#include "Utils.h"
#include <iostream>

SimpleRenderer::SimpleRenderer() {
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    m_cellShape.setSize({CELL_SIZE, CELL_SIZE});
    m_cellShape.setOutlineThickness(1);
    m_cellShape.setOutlineColor(sf::Color::Black);

    m_clueText.setFont(m_font);
    m_clueText.setCharacterSize(20);
    m_clueText.setFillColor(sf::Color::Black);

    m_inputText.setFont(m_font);
    m_inputText.setCharacterSize(24);
    m_inputText.setFillColor(sf::Color::Blue);

    m_completedText.setFont(m_font);
    m_completedText.setCharacterSize(32);
    m_completedText.setFillColor(sf::Color::Green);
    m_completedText.setString("Поздравляем! Кроссворд решен!");
    Utils::centerText(m_completedText, m_windowSize, -100);

    m_backButton.setSize({150, 50});
    m_backButton.setFillColor(sf::Color(200, 200, 200));
    m_backButton.setOutlineThickness(2);
    m_backButton.setOutlineColor(sf::Color::Black);

    m_backButtonText.setFont(m_font);
    m_backButtonText.setCharacterSize(24);
    m_backButtonText.setString("Назад");
    m_backButtonText.setFillColor(sf::Color::Black);
}

void SimpleRenderer::render(sf::RenderWindow& window, const Crossword& crossword) {
    window.clear(sf::Color::White);

    drawGrid(window, crossword);
    drawClues(window, crossword);
    drawInputText(window, crossword);

    if (crossword.isCompleted()) {
        drawCompletedMessage(window, crossword);
    }

    // Draw back button
    m_backButton.setPosition(20, 20);
    window.draw(m_backButton);

    m_backButtonText.setPosition(
        m_backButton.getPosition().x + m_backButton.getSize().x / 2 - m_backButtonText.getLocalBounds().width / 2,
        m_backButton.getPosition().y + m_backButton.getSize().y / 2 - m_backButtonText.getLocalBounds().height / 2 - 5
    );
    window.draw(m_backButtonText);
}

void SimpleRenderer::drawGrid(sf::RenderWindow& window, const Crossword& crossword) {
    const auto& grid = crossword.getGrid();
    float startX = (m_windowSize.x - CLUE_AREA_WIDTH - grid[0].size() * CELL_SIZE) / 2;
    float startY = (m_windowSize.y - grid.size() * CELL_SIZE) / 2;

    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == '#') continue;

            m_cellShape.setPosition(startX + x * CELL_SIZE, startY + y * CELL_SIZE);
            
            if (crossword.isCellSelected(x, y)) {
                m_cellShape.setFillColor(sf::Color(200, 230, 255));
            } else if (crossword.isCellInCurrentWord(x, y)) {
                m_cellShape.setFillColor(sf::Color(230, 255, 230));
            } else {
                m_cellShape.setFillColor(sf::Color::White);
            }

            window.draw(m_cellShape);

            // Draw letter if present
            if (grid[y][x] != '.') {
                m_inputText.setString(std::string(1, grid[y][x]));
                m_inputText.setPosition(
                    startX + x * CELL_SIZE + CELL_SIZE / 2 - m_inputText.getLocalBounds().width / 2,
                    startY + y * CELL_SIZE + CELL_SIZE / 2 - m_inputText.getLocalBounds().height / 2 - 5
                );
                window.draw(m_inputText);
            }
        }
    }
}

void SimpleRenderer::drawClues(sf::RenderWindow& window, const Crossword& crossword) {
    float clueAreaX = m_windowSize.x - CLUE_AREA_WIDTH + PADDING;
    float clueAreaY = PADDING;

    // Draw across clues
    m_clueText.setString("По горизонтали:");
    m_clueText.setPosition(clueAreaX, clueAreaY);
    window.draw(m_clueText);
    clueAreaY += 30;

    for (const auto& clue : crossword.getAcrossClues()) {
        m_clueText.setString(clue);
        m_clueText.setPosition(clueAreaX, clueAreaY);
        window.draw(m_clueText);
        clueAreaY += 25;
    }

    clueAreaY += 20;

    // Draw down clues
    m_clueText.setString("По вертикали:");
    m_clueText.setPosition(clueAreaX, clueAreaY);
    window.draw(m_clueText);
    clueAreaY += 30;

    for (const auto& clue : crossword.getDownClues()) {
        m_clueText.setString(clue);
        m_clueText.setPosition(clueAreaX, clueAreaY);
        window.draw(m_clueText);
        clueAreaY += 25;
    }
}

void SimpleRenderer::drawInputText(sf::RenderWindow& window, const Crossword& crossword) {
    if (crossword.hasSelectedCell()) {
        auto [x, y] = crossword.getSelectedCell();
        const auto& grid = crossword.getGrid();
        
        float startX = (m_windowSize.x - CLUE_AREA_WIDTH - grid[0].size() * CELL_SIZE) / 2;
        float startY = (m_windowSize.y - grid.size() * CELL_SIZE) / 2;

        m_inputText.setString(crossword.getCurrentInput());
        m_inputText.setPosition(
            startX + x * CELL_SIZE + CELL_SIZE / 2 - m_inputText.getLocalBounds().width / 2,
            startY + y * CELL_SIZE + CELL_SIZE / 2 - m_inputText.getLocalBounds().height / 2 - 5
        );
        window.draw(m_inputText);
    }
}

void SimpleRenderer::drawCompletedMessage(sf::RenderWindow& window, const Crossword& crossword) {
    sf::RectangleShape overlay(sf::Vector2f(m_windowSize.x, m_windowSize.y));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    Utils::centerText(m_completedText, m_windowSize, -100);
    window.draw(m_completedText);
}

void SimpleRenderer::handleEvent(const sf::Event& event, Crossword& crossword) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        // Check back button
        if (m_backButton.getGlobalBounds().contains(mousePos)) {
            crossword.requestBack();
            return;
        }

        const auto& grid = crossword.getGrid();
        float startX = (m_windowSize.x - CLUE_AREA_WIDTH - grid[0].size() * CELL_SIZE) / 2;
        float startY = (m_windowSize.y - grid.size() * CELL_SIZE) / 2;

        for (size_t y = 0; y < grid.size(); ++y) {
            for (size_t x = 0; x < grid[y].size(); ++x) {
                if (grid[y][x] == '#') continue;

                sf::FloatRect cellRect(
                    startX + x * CELL_SIZE,
                    startY + y * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE
                );

                if (cellRect.contains(mousePos)) {
                    crossword.selectCell(x, y);
                    return;
                }
            }
        }
    }
    else if (event.type == sf::Event::TextEntered && crossword.hasSelectedCell()) {
        if (event.text.unicode == 8) { // Backspace
            crossword.removeLetter();
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 128) {
            char c = static_cast<char>(event.text.unicode);
            if (isalpha(c)) {
                crossword.addLetter(toupper(c));
            }
        }
    }
}

void SimpleRenderer::onResize(const sf::Vector2u& newSize) {
    m_windowSize = newSize;
    Utils::centerText(m_completedText, m_windowSize, -100);
}
