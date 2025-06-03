#ifndef CROSSWORDLEVEL_H
#define CROSSWORDLEVEL_H

#include "Screen.h"
#include "Crossword.h"
#include "ICrosswordRenderer.h"
#include <memory>

class CrosswordLevel : public Screen {
public:
    CrosswordLevel(std::unique_ptr<Crossword> crossword, std::unique_ptr<ICrosswordRenderer> renderer);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void onResize(const sf::Vector2u& newSize) override;

private:
    std::unique_ptr<Crossword> m_crossword;
    std::unique_ptr<ICrosswordRenderer> m_renderer;
};

#endif // CROSSWORDLEVEL_H
