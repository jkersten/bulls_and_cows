#include "screen.hpp"
#include "input.hpp"
#include "bulls_cows_game.hpp"

int main() {
    Screen screen;
    Input input;
    BullsCowsGame game(&screen, &input, { "brick", "jumpy", "waltz", "nymph", "bling", "track", "fjord", "frogs", "dwarf", "worth", "sloth", "peach", "paths", "round" });
    
    game.run();
    return 0;
}
