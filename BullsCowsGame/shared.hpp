#pragma once

#include <set>

struct BullsCowsCount {
    std::set<char> bulls;
    std::set<char> cows;
};

enum class ValidationError {
     NO_ISOGRAM
    ,NO_WORD
    ,TOO_SHORT
    ,TOO_LONG
};
