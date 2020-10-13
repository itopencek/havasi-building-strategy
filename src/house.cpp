#include "house.h"

char House::Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price)
{
    mvwprintw(win, 0, 1, "House | Game paused");

    const int NUMBER_OF_CHOICES = 2;
    Cost *stoneWalls = new Cost(0, 100, 0, 0, 0);
    std::string choices[NUMBER_OF_CHOICES] = {"Get Back", "Stone walls | " + stoneWalls->PrintCost()};
    Cost cost(0, 100, 0, 0);

    int choice = Field::ChoosingMenu(win, NUMBER_OF_CHOICES, choices);

    if (choice == 0)
        return 0;

    if (material >= cost)
    {
        material -= cost;
        material.Increase(2, 'p');
        return 1;
    }
    else
    {
        Field::DisplayText("House | Game paused", win, "Not enough resources");
        return 0;
    }
}