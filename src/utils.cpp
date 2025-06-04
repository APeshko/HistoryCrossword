#include "../include/utils.h"
#include <fstream>
#include <algorithm>

namespace utils {
    sf::Font loadFont(const std::string& path) {
        sf::Font font;
        if (!font.loadFromFile(path)) {
            throw std::runtime_error("Failed to load font: " + path);
        }
        return font;
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

    std::string toUpper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    std::string toLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    bool isCyrillic(wchar_t c) {
        return (c >= 0x0400 && c <= 0x04FF) || (c >= 0x0500 && c <= 0x052F);
    }
}
