#include "screen.hpp"

void Screen::intro(size_t word_length, unsigned short max_tries) const {
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the " << word_length << " letter isogram within " << max_tries << " tries?\n";
}
    
void Screen::guess(unsigned short guess) const {
    std::cout <<"\nGuess " << guess << ": _____\b\b\b\b\b";
}

void Screen::bullsAndCows(BullsCowsCount count) const {
    std::cout << "  Bulls: " << count.bulls << std::endl;
    std::cout << "  Cows: " << count.cows << std::endl;
}

void Screen::showErrors(std::set<ValidationError> errors, std::string input) const {
    for (auto error : errors) {
        switch(error) {
            case ValidationError::NO_WORD:
                std::cout << "  '" << input << "' is not a word\n";
                break;
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
    
void Screen::won() const {
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "CONGRATULATIONS! You've found the word!\n";
    std::cout << "Do you want to start a new game? (y/n)\n";
    std::cout << "--------------------------------------------------\n";
}

void Screen::lost(std::string hidden_word) const {
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "Oh no you've lost!\n";
    std::cout << "The word we were looking for was '" << hidden_word << "'\n";
    std::cout << "Better luck next time! Play again? (y/n)\n";
    std::cout << "--------------------------------------------------\n";
}
