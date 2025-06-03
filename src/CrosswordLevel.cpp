#include "CrosswordLevel.h"

CrosswordLevel::CrosswordLevel(std::unique_ptr<Crossword> crossword, std::unique_ptr<ICrosswordRenderer> renderer)
    : m_crossword(std::move(crossword)), m_renderer(std::move(renderer)) {}

void CrosswordLevel::handleEvent(const sf::Event& event) {
    m_renderer->handleEvent(event, *m_crossword);
}

void CrosswordLevel::update(float dt) {
    // No update logic needed for now
}

void CrosswordLevel::render(sf::RenderWindow& window) {
    m_renderer->render(window, *m_crossword);
}

void CrosswordLevel::onResize(const sf::Vector2u& newSize) {
    m_renderer->onResize(newSize);
}
