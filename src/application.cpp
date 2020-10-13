#include "application.h"
#include <iostream>
#include "tutorial.h"
#include "color.h"

Application::Application()
{
    // initialize screen
    initscr();
    cbreak();
    
    // get height and width of stdscr - terminal
    getmaxyx(stdscr, h, w);
    // waits miliseconds for user input after
    // that time continues
    // nodelay(stdscr,true) - doesnt wait at all
    timeout(refreshRate);
    //to enable keypad and F-keys
    keypad(stdscr, true);

    // resize terminal
    resizeterm(24, 80);
    // init color
    start_color();

    init_pair(WATER, COLOR_CYAN, COLOR_BLUE);
    init_pair(TREE, COLOR_WHITE, COLOR_GREEN);
    init_pair(MOUNTAIN, COLOR_BLACK, COLOR_WHITE);
    // init_pair(6, COLOR_MAGENTA, COLOR_WHITE);
    // color of default terminal
    assume_default_colors(COLOR_WHITE, COLOR_BLACK);
    // hide cursor
    curs_set(0);
    // getch wont show pressed key on window
    noecho();
}

void Application::Start()
{
    // setting up basic window
    mainWin = newwin(h, w, 0, 0);
    box(mainWin, 0, 0);

    // start menu
    menu = new Menu();
    // start game
    game = new Game(mainWin);

    std::string name = "";
    int choice = 0;
    Tutorial *tutorial;
    std::ifstream ifs;

    while (!choice)
    {
        switch (menu->Init(mainWin))
        {
        // new game
        case 0:
            choice = menu->NewGameMenu(mainWin);
            if (choice == 3)
                choice = 0;
            else
            {
                name = input->Read(mainWin, "Name of your game: ");
                choice += 10;
            }
            break;
        // load game
        case 1:
            do
            {
                name = input->Read(mainWin, "Name of your saved game: ");
                if (name == "-")
                {
                    choice = 0;
                    break;
                }
                else
                {
                    // check if file exists
                    // if does not then asks for name again
                    ifs.open("examples/saves/" + name);
                    if (!ifs.fail())
                    {
                        choice = 1;
                        break;
                    }
                }
            } while (true);
            break;
        // tutorial - not yet implemented
        case 2:
            tutorial = new Tutorial();
            tutorial->Start(mainWin);
            choice = 0;
            break;
        // exit
        case 3:
            werase(mainWin);
            delwin(mainWin);
            endwin();
            return;
            break;
        default:
            break;
        }
        wclear(mainWin);
        box(mainWin, 0, 0);
    }

    if (!game->Init(choice, name))
    {
        delwin(mainWin);
        endwin();
        std::cout << "There was an error loading your game!" << std::endl;
        std::cout << "Try reinstalling the game" << std::endl;
        exit(1);
    }

    wborder(mainWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    werase(mainWin);
    wrefresh(mainWin);
    delwin(mainWin);
    endwin();

    return;
}