#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Screen.h"

class Game {
public:
    Game();
    void run();

private:
    void createWindow();
    void handleEvents();
    void update();
    void render();
    void switchScreen(std::unique_ptr<Screen> newScreen);
    void loadLevel(int level);

    sf::RenderWindow m_window;
    std::unique_ptr<Screen> m_currentScreen;
};

#endif // GAME_H
