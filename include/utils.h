#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace utils {
    sf::Font loadFont(const std::string& path);
    std::vector<std::string> splitString(const std::string& str, char delimiter);
    std::string toUpper(const std::string& str);
    std::string toLower(const std::string& str);
    bool isCyrillic(wchar_t c);
}

#endif // UTILS_H
