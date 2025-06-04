#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

class ResourceManager {
public:
    static ResourceManager& getInstance();

    void loadFont(const std::string& name, const std::string& filename);
    sf::Font& getFont(const std::string& name);

private:
    ResourceManager() = default;
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts;
};
