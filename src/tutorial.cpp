#include "tutorial.h"

void Tutorial::Start(WINDOW *win)
{
    mvwprintw(win, 1, 1, "Welcome to this building strategy!");
    mvwprintw(win, 3, 1, "There are several types of buildings:");
    mvwprintw(win, 4, 1, "[w] - Woodcutter - generates wood");
    mvwprintw(win, 5, 1, "[q] - Quary - generates stone");
    mvwprintw(win, 6, 1, "[f] - Fishingbooth - generates food");
    mvwprintw(win, 7, 1, "[h] - House - adds new people to your village");
    mvwprintw(win, 8, 1, "[b] - Barracks - allow you to train troops");
    mvwprintw(win, 9, 1, "[c] - Castle - place for you to live in");
    mvwprintw(win, 10, 1, "Types of resources are: Wood,Stone,Food");
    mvwprintw(win, 11, 1, "You also need to have enough people");
    mvwprintw(win, 12, 1, "and can train troops");
    mvwprintw(win, 14, 1, "Press enter to continue");
    wrefresh(win);
    // waiting for user to press ENTER
    while (getch() != 10)
    {
    }
    wclear(win);
    Second(win);
}

void Tutorial::Second(WINDOW *win)
{
    mvwprintw(win, 1, 1, "In-game your cursor is @");
    mvwprintw(win, 2, 1, "You can move with wasd or arrow-keys");
    mvwprintw(win, 3, 1, "You can also decrease or increase game speed");
    mvwprintw(win, 4, 1, "Using keys q,e");
    mvwprintw(win, 5, 1, "You can open building menu in-game by standing on empty");
    mvwprintw(win, 6, 1, "fields and pressing ENTER");
    mvwprintw(win, 7, 1, "Pressing ENTER on other building will open their menus!");
    mvwprintw(win, 8, 1, "Pressing ESC at any time will open menu");
    mvwprintw(win, 9, 1, "Your building are generating resources based on number of");
    mvwprintw(win, 10, 1, "trees/mountains/water nearby");
    mvwprintw(win, 12, 1, "TT");
    mvwprintw(win, 13, 1, "Tw -> this woodcutter would generate 4 wood");
    mvwprintw(win, 14, 1, "Tw -> this one only 2");
    mvwprintw(win, 16, 1, "Press ENTER to exit tutorial");
    box(win, 0, 0);
    wrefresh(win);
    // waiting for user to press ENTER
    while (getch() != 10)
    {
    }
    wclear(win);
    box(win, 0, 0);
}