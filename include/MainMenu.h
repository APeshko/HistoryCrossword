#ifndef MAINMENU_H
#define MAINMENU_H

#include "Screen.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

class MainMenu : public Screen {
public:
    using LevelCallback = std::function<void(int level)>;

    MainMenu();
    void setLevelCallback(LevelCallback callback);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void onResize(const sf::Vector2u& newSize) override;

private:
    void setupUI();
    void centerUI();

    sf::Font m_font;
    sf::Text m_titleText;
    std::vector<sf::RectangleShape> m_levelButtons;
    std::vector<sf::Text> m_levelButtonTexts;
    LevelCallback m_levelCallback;
    sf::Vector2u m_windowSize;
};

#endif // MAINMENU_H
