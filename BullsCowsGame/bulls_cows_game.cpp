#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bulls_cows_game.hpp"

BullsCowsGame::BullsCowsGame(Screen *screen, Input *input, std::vector<std::string> words = { "brick", "jumpy", "waltz", "nymph", "bling", "track", "fjord", "frogs", "dwarf", "worth", "sloth", "peach", "paths", "round", "plane" }) {
    this->words = words;
    this->screen = screen;
    this->input = input;
    srand((unsigned int)time(NULL));
}

auto BullsCowsGame::hiddenWordLength() const { return hidden_word.length(); }
auto BullsCowsGame::currentTry() const { return current_try; }
auto BullsCowsGame::maxTries() const { return MAX_TRIES; }

void BullsCowsGame::reset() {
    hidden_word = words[rand() % words.size()];
    current_try = 1;
}

void BullsCowsGame::run() {
    do {
        reset();
        screen->intro(hiddenWordLength(), maxTries());
        
        for (current_try = 1; current_try <= maxTries(); ++current_try) {
            std::string input = getValidInput();
            auto result = countBullsAndCows(input);
            
            if (result.bulls == hiddenWordLength()) {
                screen->won();
                break;
            } else {
                screen->bullsAndCows(result);
            }
        }
    } while(this->input->playAgain());
}

std::string BullsCowsGame::getValidInput() const {
    std::string text = "";
    std::set<ValidationError> errors;
    do {
        screen->guess(currentTry());
        text = input->get();
        errors = validate(text);
        screen->showErrors(errors, text);
    } while(!errors.empty());
    return text;
}

std::set<ValidationError> BullsCowsGame::validate(std::string input) const {
    std::set<ValidationError> result;
    if (!isIsogram(input)) {
        result.insert(ValidationError::NO_ISOGRAM);
    }
    if (input.length() < hidden_word.length()) {
        result.insert(ValidationError::TOO_SHORT);
    }
    if (input.length() > hidden_word.length()) {
        result.insert(ValidationError::TOO_LONG);
    }
    return result;
}

BullsCowsCount BullsCowsGame::countBullsAndCows(const std::string input) const {
    BullsCowsCount result;
    for (auto ic = 0; ic < hidden_word.length(); ++ic) {
        for (auto wc = 0; wc < hidden_word.length(); ++wc) {
            if (input[ic] == hidden_word[wc]) {
                if (ic == wc) {
                    result.bulls++;
                } else {
                    result.cows++;
                }
            }
        }
    }
    return result;
}

bool BullsCowsGame::isIsogram(std::string word) const {
    std::set<char> unique;
    for (char c : word) {
        if (!unique.insert(c).second) {
            return false;
        }
    }
    return true;
}
