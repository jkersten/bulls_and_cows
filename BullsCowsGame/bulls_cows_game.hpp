#pragma once

#include <vector>
#include <string>
#include <set>

#include "screen.hpp"
#include "input.hpp"
#include "shared.hpp"

class BullsCowsGame {
public:
    BullsCowsGame(const Screen &, const Input &, const std::vector<std::string> &);

    auto hiddenWordLength() const;
    auto currentTry() const;
    auto maxTries() const;
    
    void reset();
    void run();
    
    std::string getValidInput() const;
    std::set<ValidationError> validate(std::string input) const;
    BullsCowsCount countBullsAndCows(const std::string input) const;
    
private:
    const Screen &screen;
    const Input &input;
    std::vector<std::string> words;
    std::string hidden_word;
    static constexpr unsigned short MAX_TRIES = 10;
    unsigned short current_try;
    
    bool isIsogram(std::string word) const;
};
