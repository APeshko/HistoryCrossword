#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Crossword.h"
#include "StateManager.h"

class GameState : public State {
public:
    GameState(StateManager& manager, int level);
    
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    
private:
    void createCrossword();
    void drawHeader(sf::RenderWindow& window);
    
    int currentLevel;
    std::unique_ptr<Crossword> crossword;
    sf::Font font;
    sf::Text levelText;
    sf::Text completeText;
    sf::Text backText;
    bool isComplete;
};

#endif // GAMESTATE_H
