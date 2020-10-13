#include "barracks.h"

char Barracks::Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price)
{
    mvwprintw(win, 0, 1, "Barracks | Game paused");
    std::string choices[2] = {"Get back", "Train 1 troop | " + price['t'].PrintCost()};
    int NUM_OF_CHOICES = 2;
    Cost troop(10, 20, 30, 0, 1);

    int choice = Field::ChoosingMenu(win, NUM_OF_CHOICES, choices);
    if (choice == 0)
        return 0;

    if (material >= troop)
    {
        material -= troop;
        material.Increase(1, 't');
    }
    else
    {
        Field::DisplayText("Barracks | Game paused", win, "Not enough resources");
        return 0;
    }

    return 1;
}