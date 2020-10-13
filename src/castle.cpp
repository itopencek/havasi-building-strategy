#include "castle.h"

char Castle::Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price)
{
    mvwprintw(win, 0, 1, "Castle | Game paused");
    Cost lowerCost(50, 50, 50, 0, 0);
    std::string choices[2] = {"Get back", "Lower price of House | " + lowerCost.PrintCost()};
    int NUM_OF_CHOICES = 2;

    int choice = Field::ChoosingMenu(win, NUM_OF_CHOICES, choices);
    if (choice == 0)
        return 0;

    if (material >= lowerCost)
    {
        material -= lowerCost;
        price['h'].Set(5, 0, 5, 0, 0);
    }
    else
    {
        Field::DisplayText("Castle | Game paused", win, "Not enough resources");
        return 0;
    }

    return 1;
}