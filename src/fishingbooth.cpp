#include "fishingbooth.h"

char FishingBooth::Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price)
{
    mvwprintw(win, 0, 1, "FishingBooth | Game paused");
    Cost food(10, 10, 0, 0, 0);
    std::string choices[2] = {"Get back", "Buy 20 food | " + food.PrintCost()};
    int NUM_OF_CHOICES = 2;

    int choice = Field::ChoosingMenu(win, NUM_OF_CHOICES, choices);
    if (choice == 0)
        return 0;

    if (material >= food)
    {
        material -= food;
        material.Increase(20, 'f');
    }
    else
    {
        Field::DisplayText("FishingBooth | Game paused", win, "Not enough resources");
        return 0;
    }

    return 1;
}