#include "MainMenuState.h"
#include "ResourceManager.h"
#include "StateMachine.h"
#include <SFML/Graphics.hpp>
#include <stdexcept>

int main() {
    try {
        sf::RenderWindow window(sf::VideoMode(800, 600), L"Кроссворд по истории");
        window.setVerticalSyncEnabled(true);

        // Загрузка шрифта (нужно поместить файл arial.ttf в папку fonts)
        ResourceManager::getInstance().loadFont("arial", "fonts/arial.ttf");

        StateMachine machine;
        machine.pushState(std::make_unique<MainMenuState>(machine, window));

        sf::Clock clock;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                machine.handleEvent(event);
            }

            float dt = clock.restart().asSeconds();
            machine.update(dt);

            window.clear();
            machine.render(window);
            window.display();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
