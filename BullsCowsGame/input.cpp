#include <algorithm>
#include <iostream>

#include "input.hpp"

std::string Input::get() const {
    std::string input;
    std::getline(std::cin, input);
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

bool Input::playAgain() const {
    return get() == "y";
}
