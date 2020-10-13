/**
 * @author Ivan Havasi
 * @brief semester work - building startegy game
 */
#include <ncurses.h>
#include <iostream>
#include "application.h"

int main()
{
    Application *app = new Application();
    app->Start();
    return 0;
}