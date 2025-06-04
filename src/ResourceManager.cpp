#include "ResourceManager.h"
#include <stdexcept>

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

void ResourceManager::loadFont(const std::string& name, const std::string& filename) {
    auto font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(filename)) {
        throw std::runtime_error("Failed to load font: " + filename);
    }
    fonts[name] = std::move(font);
}

sf::Font& ResourceManager::getFont(const std::string& name) {
    auto it = fonts.find(name);
    if (it == fonts.end()) {
        throw std::runtime_error("Font not found: " + name);
    }
    return *it->second;
}
