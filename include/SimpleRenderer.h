#ifndef SIMPLERENDERER_H
#define SIMPLERENDERER_H

#include "ICrosswordRenderer.h"
#include <SFML/Graphics.hpp>

class SimpleRenderer : public ICrosswordRenderer {
public:
    SimpleRenderer();
    void render(sf::RenderWindow& window, const Crossword& crossword) override;
    void handleEvent(const sf::Event& event, Crossword& crossword) override;
    void onResize(const sf::Vector2u& newSize) override;

private:
    void drawGrid(sf::RenderWindow& window, const Crossword& crossword);
    void drawClues(sf::RenderWindow& window, const Crossword& crossword);
    void drawInputText(sf::RenderWindow& window, const Crossword& crossword);
    void drawCompletedMessage(sf::RenderWindow& window, const Crossword& crossword);

    sf::Font m_font;
    sf::Vector2u m_windowSize;
    sf::RectangleShape m_cellShape;
    sf::Text m_clueText;
    sf::Text m_inputText;
    sf::Text m_completedText;
    sf::RectangleShape m_backButton;
    sf::Text m_backButtonText;

    static constexpr float CELL_SIZE = 40.0f;
    static constexpr float PADDING = 20.0f;
    static constexpr float CLUE_AREA_WIDTH = 300.0f;
};

#endif // SIMPLERENDERER_H
