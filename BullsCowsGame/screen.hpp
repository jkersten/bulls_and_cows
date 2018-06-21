#pragma once

#include <iostream>
#include <string>
#include <set>

#include "shared.hpp"

class Screen {
public:
    void intro(size_t word_length, unsigned short max_tries) const;
    void guess(unsigned short guess) const;
    void bullsAndCows(BullsCowsCount count) const;
    void bullsAndCows(std::string guess, std::string hidden_word) const;
    void showErrors(std::set<ValidationError> errors, std::string input) const;
    void won() const;
    void lost(std::string hidden_word) const;
};
