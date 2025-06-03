#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace Utils {
    sf::Vector2f getCenterPosition(const sf::FloatRect& bounds, const sf::Vector2u& windowSize);
    void centerText(sf::Text& text, const sf::Vector2u& windowSize, float yOffset = 0);
    std::vector<std::string> splitString(const std::string& str, char delimiter);
    std::string trim(const std::string& str);
    bool isAllLetters(const std::string& str);
}

#endif // UTILS_H
