#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <memory>
#include <SFML/Graphics.hpp>

class State {
public:
    virtual ~State() = default;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    
    void setManager(class StateManager* manager) { this->manager = manager; }
    StateManager* getManager() const { return manager; }
    
protected:
    StateManager* manager = nullptr;
};

class StateManager {
public:
    StateManager(sf::RenderWindow& window);
    
    void changeState(std::unique_ptr<State> state);
    void handleEvent(const sf::Event& event);
    void update(float dt);
    void draw();
    
    sf::RenderWindow* getWindow() { return &window; }
    
private:
    sf::RenderWindow& window;
    std::unique_ptr<State> currentState;
};

#endif // STATEMANAGER_H
