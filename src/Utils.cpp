#include "Utils.h"
#include <algorithm>
#include <cctype>

namespace Utils {
    sf::Vector2f getCenterPosition(const sf::FloatRect& bounds, const sf::Vector2u& windowSize) {
        float x = (windowSize.x - bounds.width) / 2.0f;
        float y = (windowSize.y - bounds.height) / 2.0f;
        return {x, y};
    }

    void centerText(sf::Text& text, const sf::Vector2u& windowSize, float yOffset) {
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, 
                      textBounds.top + textBounds.height / 2.0f);
        text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + yOffset);
    }

    std::vector<std::string> splitString(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = str.find(delimiter);
        
        while (end != std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + 1;
            end = str.find(delimiter, start);
        }
        
        tokens.push_back(str.substr(start));
        return tokens;
    }

    std::string trim(const std::string& str) {
        auto start = std::find_if(str.begin(), str.end(), [](int ch) { return !std::isspace(ch); });
        auto end = std::find_if(str.rbegin(), str.rend(), [](int ch) { return !std::isspace(ch); }).base();
        return start < end ? std::string(start, end) : std::string();
    }

    bool isAllLetters(const std::string& str) {
        return std::all_of(str.begin(), str.end(), [](char c) { 
            return std::isalpha(c) || c == ' '; 
        });
    }
}
