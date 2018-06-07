#pragma once

struct BullsCowsCount {
    unsigned short bulls = 0;
    unsigned short cows = 0;
};

enum class ValidationError {
    NO_ISOGRAM
    ,TOO_SHORT
    ,TOO_LONG
};
