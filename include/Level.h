#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>

struct Level {
    std::vector<std::string> words;
    std::vector<std::string> definitions;
    std::vector<std::pair<int, int>> positions;
    std::vector<bool> orientations; // true - horizontal, false - vertical
    int gridSize;
};

namespace Levels {
    Level getLevel1();
    Level getLevel2();
    Level getLevel3();
}

#endif // LEVEL_H
