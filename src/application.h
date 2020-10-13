#include <ncurses.h>
#include "menu.h"
#include "game.h"
#include "gamefiles.h"
#include "readinput.h"

#ifndef _APPLICATION
#define _APPLICATION

/**
 * @class Application
 * @brief takes care of starting the whole game
 * 
 * @var h,w - size of main window
 * @var refreshRate - starting refresh rate
 * @var mainWin - main window
 * @var menu - starting menu
 * @var game - new game
 * @var input - reading user's input
 */
class Application
{
public:
    Application();
    /**
     * @brief starts application, first menu and initializes game
     */
    void Start();

private:
    int h, w;
    const int refreshRate = 25;
    WINDOW *mainWin;
    Menu *menu;
    Game *game;
    ReadInput *input = new ReadInput();
};

#endif