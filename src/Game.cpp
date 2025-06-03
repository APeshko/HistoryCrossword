#include "Game.h"
#include "MainMenu.h"
#include "CrosswordLevel.h"
#include "SimpleRenderer.h"
#include <memory>

Game::Game() {
    createWindow();
    switchScreen(std::make_unique<MainMenu>());
}

void Game::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        sf::Time dt = clock.restart();
        handleEvents();
        update();
        render();
    }
}

void Game::createWindow() {
    m_window.create(sf::VideoMode(1000, 700), "Исторический кроссворд");
    m_window.setFramerateLimit(60);
}

void Game::handleEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        else if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            m_window.setView(sf::View(visibleArea));
            if (m_currentScreen) {
                m_currentScreen->onResize(m_window.getSize());
            }
        }

        if (m_currentScreen) {
            m_currentScreen->handleEvent(event);
        }
    }
}

void Game::update() {
    if (m_currentScreen) {
        m_currentScreen->update(1.0f / 60.0f); // Fixed delta time for simplicity
    }
}

void Game::render() {
    if (m_currentScreen) {
        m_currentScreen->render(m_window);
    }
    m_window.display();
}

void Game::switchScreen(std::unique_ptr<Screen> newScreen) {
    m_currentScreen = std::move(newScreen);
    if (m_currentScreen) {
        m_currentScreen->onResize(m_window.getSize());
        
        // Set up level callback if it's MainMenu
        if (auto* menu = dynamic_cast<MainMenu*>(m_currentScreen.get())) {
            menu->setLevelCallback([this](int level) { loadLevel(level); });
        }
    }
}

void Game::loadLevel(int level) {
    std::vector<std::string> grid;
    std::vector<std::string> acrossClues;
    std::vector<std::string> downClues;

    switch (level) {
        case 1:
            // Level 1 - Древний мир
            grid = {
                "D..E..M..O..S",
                "....A....A....",
                "P..H..A..R..A..O..H",
                "....T....R....",
                "H..A..M..M..U..R..A..B..I",
                "....O....A....",
                "P..A..P..Y..R..U..S",
                "....N....D....",
                "S..P..A..R..T..A",
                "....I....E....",
                "O..L..I..M..P..I..A",
                "....A....R....",
                "A..T..H..E..N..S"
            };
            acrossClues = {
                "1. Народное собрание в Древней Греции",
                "3. Титул древнеегипетского правителя",
                "5. Вавилонский царь, создатель знаменитых законов",
                "7. Материал для письма в Древнем Египте",
                "9. Город-государство в Древней Греции с военизированным обществом",
                "11. Место проведения Олимпийских игр в Древней Греции",
                "13. Главный город Аттики, центр древнегреческой культуры"
            };
            downClues = {
                "2. Богиня мудрости в Древней Греции",
                "4. Река в Древнем Египте",
                "6. Древнегреческий поэт, автор 'Илиады' и 'Одиссеи'",
                "8. Древнегреческий бог солнца",
                "10. Древнегреческий философ, учитель Александра Македонского",
                "12. Древнеримский император, построивший Колизей"
            };
            break;
            
        case 2:
            // Level 2 - Средние века
            grid = {
                "F..E..U..D..A..L..I..S..M",
                "....R....C....",
                "C..R..U..S..A..D..E..S",
                "....A....H....",
                "I..N..Q..U..I..S..I..T..I..O..N",
                "....N....U....",
                "K..N..I..G..H..T",
                "....K....R....",
                "M..A..G..N..A..C..A..R..T..A",
                "....I....C....",
                "B..L..A..C..K..D..E..A..T..H",
                "....N....H....",
                "C..H..A..R..L..E..M..A..G..N..E"
            };
            acrossClues = {
                "1. Общественный строй, основанный на вассальной зависимости",
                "3. Религиозные войны за освобождение Святой земли",
                "5. Церковный суд для борьбы с ересью",
                "7. Воин-всадник в средневековой Европе",
                "9. Великая хартия вольностей в Англии",
                "11. Эпидемия чумы в XIV веке",
                "13. Король франков, император Запада"
            };
            downClues = {
                "2. Средневековый замок",
                "4. Средневековый городской совет",
                "6. Средневековый университет",
                "8. Средневековая торговая гильдия",
                "10. Средневековый крестьянин",
                "12. Средневековый монашеский орден"
            };
            break;
            
        case 3:
            // Level 3 - Новое время
            grid = {
                "R..E..N..A..I..S..S..A..N..C..E",
                "....E....M....",
                "I
