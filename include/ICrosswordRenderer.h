#ifndef ICROSSWORDRENDERER_H
#define ICROSSWORDRENDERER_H

#include <SFML/Graphics.hpp>
#include "Crossword.h"

class ICrosswordRenderer {
public:
    virtual ~ICrosswordRenderer() = default;
    virtual void render(sf::RenderWindow& window, const Crossword& crossword) = 0;
    virtual void handleEvent(const sf::Event& event, Crossword& crossword) = 0;
    virtual void onResize(const sf::Vector2u& newSize) = 0;
};

#endif // ICROSSWORDRENDERER_H
