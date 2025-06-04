#pragma once
#include <vector>
#include <string>

struct Word {
    std::string word;
    std::string clue;
    bool isHorizontal;
};

namespace CrosswordLevel {
    std::vector<Word> getLevel1Words();
    std::vector<Word> getLevel2Words();
    std::vector<Word> getLevel3Words();
}
