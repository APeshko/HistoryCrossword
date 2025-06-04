#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "StateManager.h"

class MainMenuState : public State {
public:
    MainMenuState(StateManager& manager);
    
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    
private:
    sf::Font font;
    sf::Text titleText;
    std::vector<sf::Text> menuItems;
    std::vector<sf::RectangleShape> buttons;
};

#endif // MAINMENUSTATE_H
