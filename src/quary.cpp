#include "quary.h"

char Quary::Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price)
{
    mvwprintw(win, 0, 1, "Quary | Game paused");

    const int NUMBER_OF_CHOICES = 3;
    Cost stone(0, 20, 0, 0, 0);
    std::string choices[NUMBER_OF_CHOICES] = {"Get Back", "Sell for 20 wood | " + stone.PrintCost(), "Sell for 20 food | " + stone.PrintCost()};

    int choice = Field::ChoosingMenu(win, NUMBER_OF_CHOICES, choices);

    if (choice == 0)
        return 0;

    if (material >= stone)
    {
        material -= stone;
        if (choice == 1)
            material.Increase(20, 'w');
        else
            material.Increase(20, 'f');
        return 1;
    }
    else
    {
        Field::DisplayText("Quary | Game paused", win, "Not enough resources");
        return 0;
    }
}