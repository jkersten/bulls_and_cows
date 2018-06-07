#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

struct BullsCowsCount {
    unsigned short bulls = 0;
    unsigned short cows = 0;
};

enum class ValidationError {
    NO_ISOGRAM
    ,TOO_SHORT
    ,TOO_LONG
};

class Screen {
public:
    void intro(size_t word_length, unsigned short max_tries) const {
        std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
        std::cout << "Can you guess the " << word_length << " letter isogram within " << max_tries << " tries?\n";
    }
    
    void guess(unsigned short guess) const {
        std::cout <<"\nGuess " << guess << ": _____\b\b\b\b\b";
    }
    
    void bullsAndCows(BullsCowsCount count) {
        std::cout << "  Bulls: " << count.bulls << std::endl;
        std::cout << "  Cows: " << count.cows << std::endl;
    }
    
    void showErrors(std::set<ValidationError> errors, std::string input) const {
        for (auto error : errors) {
            switch(error) {
                case ValidationError::NO_ISOGRAM:
                    std::cout << "  '" << input << "' is not an isogram\n";
                    break;
                case ValidationError::TOO_SHORT:
                    std::cout << "  '" << input << "' is too short\n";
                    break;
                case ValidationError::TOO_LONG:
                    std::cout << "  '" << input << "' is too long\n";
                    break;
            }
        }
    }
    
    void won() const {
        std::cout << "\n--------------------------------------------------\n";
        std::cout << "CONGRATULATIONS! You've found the word!\n";
        std::cout << "Do you want to start a new game? (y/n)\n";
        std::cout << "--------------------------------------------------\n";
    }
private:
    
} screen;

class Input {
public:
    std::string get() const {
        std::string input;
        std::getline(std::cin, input);
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        return input;
    }
    
    bool playAgain() const {
        return get() == "y";
    }
} input;



class BullsCowsGame {
public:
    BullsCowsGame(Screen *screen, Input *input, std::vector<std::string> words = { "brick", "jumpy", "waltz", "nymph", "bling", "track", "fjord", "frogs", "dwarf", "worth", "sloth", "peach", "paths", "round", "plane" }) {
        this->words = words;
        this->screen = screen;
        this->input = input;
    }
    
    auto hiddenWordLength() const { return hidden_word.length(); }
    auto currentTry() const { return current_try; }
    auto maxTries() const { return MAX_TRIES; }
    
    void reset() {
        hidden_word = words[rand() % words.size()];
        current_try = 1;
    }
    
    void run() {
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
    
    std::string getValidInput() const {
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
    
    std::set<ValidationError> validate(std::string input) const {
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
    
    BullsCowsCount countBullsAndCows(const std::string input) const {
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
    
private:
    Screen *screen;
    Input *input;
    std::vector<std::string> words;
    std::string hidden_word;
    static constexpr unsigned short MAX_TRIES = 10;
    unsigned short current_try;

    bool isIsogram(std::string word) const {
        std::set<char> unique;
        for (char c : word) {
            if (!unique.insert(c).second) {
                return false;
            }
        }
        return true;
    }
} game(&screen, &input);

int main() {
    game.run();
    return 0;
}
