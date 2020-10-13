#include "woodcutter.h"

char Woodcutter::Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price)
{
    mvwprintw(win, 0, 1, "Woodcutter | Game paused");

    const int NUMBER_OF_CHOICES = 2;
    std::string choices[NUMBER_OF_CHOICES] = {"Get Back", "Better axes | " + price['w'].PrintCost()};
    Cost cost(100, 100, 0, 0);

    int choice = Field::ChoosingMenu(win, NUMBER_OF_CHOICES, choices);

    if (choice == 0)
        return 0;

    if (material >= cost)
    {
        material -= cost;
        generate.Increase(3, 'w');
        return 1;
    }
    else
    {
        Field::DisplayText("Woodcutter | Game paused", win, "Not enough resources");
        return 0;
    }
}