#include <fstream>

#include "screen.hpp"
#include "input.hpp"
#include "bulls_cows_game.hpp"

int main() {
    std::vector<std::string> words;
    
    std::ifstream file("/Users/joost/projects/BullsCowsGame/BullsCowsGame/words_nl.txt");
    if (file.is_open()) {
        std::string word;
        while (std::getline(file, word)) {
            if (word.length() > 0) {
                words.push_back(word);
            }
        }
        file.close();
    } else {
        std::cout << "Failed to open words.txt\n";
    }

    Screen screen;
    Input input;
    BullsCowsGame game(screen, input, words);
    
    game.run();
    return 0;
}
