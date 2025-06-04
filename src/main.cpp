#include "../include/StateManager.h"
#include "../include/MainMenuState.h"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Исторический кроссворд");
    window.setFramerateLimit(60);
    
    StateManager manager(window);
    manager.changeState(std::make_unique<MainMenuState>(manager));
    
    sf::Clock clock;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            manager.handleEvent(event);
        }
        
        float dt = clock.restart().asSeconds();
        manager.update(dt);
        
        window.clear();
        manager.draw();
        window.display();
    }
    
    return 0;
}
