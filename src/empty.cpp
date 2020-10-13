#include "empty.h"

char Empty::Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price)
{

    mvwprintw(win, 0, 1, "Build Menu | Game Paused");

    const int NUM_OF_CHOICES = 7;
    std::string choices[NUM_OF_CHOICES] = {"Get Back", "[w] - woodcutter | " + price['w'].PrintCost(),
                                           "[q] - quary | " + price['q'].PrintCost(),
                                           "[f] - fishing booth | " + price['f'].PrintCost(),
                                           "[b] - barracks | " + price['b'].PrintCost(),
                                           "[c] - castle | " + price['c'].PrintCost(),
                                           "[h] - house | " + price['h'].PrintCost()};
    char choices_end[NUM_OF_CHOICES] = {0, 'w', 'q', 'f', 'b', 'c', 'h'};
    int choice = Field::ChoosingMenu(win, NUM_OF_CHOICES, choices);

    if (choices_end[choice] > 0)
    {
        if (material >= price[choices_end[choice]])
        {
            material -= price[choices_end[choice]];
            return choices_end[choice];
        }
        else
            Field::DisplayText("Build menu | Game paused", win, "Not enough resources");
    }

    return 0;
}