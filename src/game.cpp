#include "game.h"
#include "color.h"

Game::Game(WINDOW *win) : mainWin(win)
{
    map = new Map();
}
Game::~Game() {}
bool Game::Init(const int choice, const std::string &loadName)
{
    if (!gameFiles->LoadPrice(material, generate, price))
        return false;

    name = loadName;

    switch (choice)
    {
    // err
    case 0:
        break;
    // load
    case 1:
        if (!gameFiles->LoadGame(name, material, generate, map, obj, price))
            return false;
        break;
    // old map
    case 2:
        map->Load("map01");
        obj = new Objective(true, 1);
        break;
    // end
    case 3:
        DeleteWin(mapWin);
        DeleteWin(bottomWin);
        return true;
        break;
    // free build
    case 10:
        map->Load("map02");
        obj = new Objective(true, 1);
        if (!obj->LoadObjective())
            return false;
        break;
    // mission 1
    case 11:
        map->Load("map03");
        obj = new Objective(true, 1, 1, "level1");
        if (!obj->LoadObjective())
            return false;
        break;
    // mission 2
    case 12:
        map->Load("map02");
        obj = new Objective(true, 1);
        if (!obj->LoadObjective())
            return false;
        break;
    default:
        break;
    }

    // render map
    wrefresh(mainWin);
    mapWin = newwin(map->GetX() + 2, map->GetY() + 2, 0, 0);
    box(mapWin, 0, 0);

    if (!map->Render(mapWin))
        return false;

    mvwprintw(mapWin, 0, 1, "Game Map");

    // initialize bottom window
    bottomWin = newwin((mainWin->_maxy / 2), mainWin->_maxx + 1, (mainWin->_maxy / 2) + 2, 0);
    box(bottomWin, 0, 0);
    wrefresh(bottomWin);

    // load objective description
    mvwprintw(mainWin, map->GetX() + 2, 1, obj->GetDescription().c_str());
    wrefresh(mainWin);

    GameLoop(mapWin);

    DeleteWin(mapWin);
    DeleteWin(bottomWin);

    return true;
}

bool Game::GameLoop(WINDOW *win)
{
    const char hero = '@';
    char building;
    int x = 1, y = 1;
    int time = 0;
    int single, prev;
    bool freeplay = false;
    curs_set(0); // hide cursor

    prev = mvwinch(win, y, x);
    mvwaddch(win, y, x, hero);

    // adding bottom bar showing what the player is standing on
    const char *text = "Current: ' '";
    mvwprintw(win, getmaxy(win) - 1, 1, text);
    mvwaddch(win, getmaxy(win) - 1, 11, prev);

    wrefresh(win);
    // main loop
    do
    {
        single = getch();
        time++;
        if (time == 75)
        {
            Generate(true);
            time = 0;
        }
        Generate(false);
        wrefresh(mainWin);
        // checks user input
        switch (single)
        {
        case KEY_UP:
        case 'w':
            if (!OutOfMap(win, y - 1, x))
            {
                PrintChar(win, y, x, prev);
                prev = mvwinch(win, y -= 1, x);
                mvwaddch(win, y, x, hero);
                mvwaddch(win, getmaxy(win) - 1, 11, prev);
            }
            break;
        case KEY_LEFT:
        case 'a':
            if (!OutOfMap(win, y, x - 1))
            {
                PrintChar(win, y, x, prev);
                prev = mvwinch(win, y, x -= 1);
                mvwaddch(win, y, x, hero);
                mvwaddch(win, getmaxy(win) - 1, 11, prev);
            }
            break;
        case KEY_DOWN:
        case 's':
            if (!OutOfMap(win, y + 1, x))
            {
                PrintChar(win, y, x, prev);
                prev = mvwinch(win, y += 1, x);
                mvwaddch(win, y, x, hero);
                mvwaddch(win, getmaxy(win) - 1, 11, prev);
            }
            break;
        case KEY_RIGHT:
        case 'd':
            if (!OutOfMap(win, y, x + 1))
            {
                PrintChar(win, y, x, prev);
                prev = mvwinch(win, y, x += 1);
                mvwaddch(win, y, x, hero);
                mvwaddch(win, getmaxy(win) - 1, 11, prev);
            }
            break;
        // pressed esc
        case 27:
            if (GameMenu(bottomWin))
                return false;
            break;
        // pressed enter
        case 10:
            building = map->GetSpecial(y, x, bottomWin, material, generate, price);
            if (building != 0 && building != 1)
            {
                map->Write(y, x, building);
                if (building == 'q')
                    IncreaseProduction('s', y, x, building);
                if (building != 'b' && building != 'c' && building != 'h' && building != 'q')
                    IncreaseProduction(building, y, x, building);
                if (building == 'h')
                    material.Increase(2, 'p');
                map->Render(win);
                prev = mvwinch(win, y, x);
                mvwaddch(win, y, x, hero);
                mvwaddch(win, getmaxy(win) - 1, 11, prev);
            }
            // checks game end
            if (!freeplay && obj->Check(material, building))
            {
                mvwprintw(bottomWin, 2, 1, "You have completed your objective");
                mvwprintw(bottomWin, 3, 1, "Press enter to continue playing");
                mvwprintw(bottomWin, 4, 1, "Press esc to quit");
                wrefresh(bottomWin);
                int a;
                do
                {
                    a = getch();
                    if (a == 10)
                    {
                        freeplay = true;
                        break;
                    }
                    if (a == 27)
                        return true;
                } while (true);
            }
            wclear(bottomWin);
            box(bottomWin, 0, 0);
            wrefresh(bottomWin);
            break;
        case 'e':
            if (ChangeRefresh(true))
                timeout(refreshRate * speed);
            break;
        case 'q':
            if (ChangeRefresh(false))
                timeout(refreshRate * speed);
            break;
        default:
            break;
        }
        wrefresh(win);
    } while (true); // pressed esc = 27

    curs_set(1); // returning back
    return false;
}

bool Game::OutOfMap(WINDOW *win, const int y, const int x) const
{
    int rX, rY, lX, lY;
    // rx is width
    // ry is height
    getmaxyx(win, rY, rX);
    getbegyx(win, lY, lX);
    if (x == rX - 1 || x == lX || y == rY - 1 || y == lY)
        return true;
    else
        return false;
}

void Game::DeleteWin(WINDOW *win) const
{
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
}

void Game::PrintChar(WINDOW *win, const int y, const int x, const char a) const
{
    switch (a)
    {
    case 'W':
        wattron(win, COLOR_PAIR(WATER));
        mvwaddch(win, y, x, a);
        wattroff(win, COLOR_PAIR(WATER));
        break;
    case 'M':
        wattron(win, COLOR_PAIR(MOUNTAIN));
        mvwaddch(win, y, x, a);
        wattroff(win, COLOR_PAIR(MOUNTAIN));
        break;
    case 'T':
        wattron(win, COLOR_PAIR(TREE));
        mvwaddch(win, y, x, a);
        wattroff(win, COLOR_PAIR(TREE));
        break;
    case '@':
        mvwaddch(win, y, x, a);
        break;
    default:
        mvwaddch(win, y, x, a);
        break;
    }
}

void Game::Generate(const bool add)
{
    if (add)
        material += generate;

    mvwprintw(mainWin, 1, getmaxx(mainWin) - 15, "Wood  %6d", material[0]);
    mvwprintw(mainWin, 2, getmaxx(mainWin) - 15, "Stone %6d", material[1]);
    mvwprintw(mainWin, 3, getmaxx(mainWin) - 15, "Food  %6d", material[2]);
    mvwprintw(mainWin, 4, getmaxx(mainWin) - 15, "Troops %4d", material[3]);
    mvwprintw(mainWin, 5, getmaxx(mainWin) - 15, "People %4d", material[4]);
    mvwprintw(mainWin, 6, getmaxx(mainWin) - 15, "Speed:  %.1fx", displaySpeed);
    wrefresh(mainWin);
}

bool Game::IncreaseProduction(const char type, const int y, const int x, const char building)
{
    // by what thing is production generated
    // T - tree, W - water, M - mountain
    char generatedBy;
    switch (building)
    {
    case 'w':
        generatedBy = 'T';
        break;
    case 'q':
        generatedBy = 'M';
        break;
    case 'f':
        generatedBy = 'W';
        break;
    default:
        return false;
        break;
    }
    int amount = map->Generate(y, x, generatedBy);

    generate.Increase(amount, type);

    return true;
}

bool Game::GameMenu(WINDOW *win)
{
    mvwprintw(win, 0, 1, "Menu | Game paused");
    const int NUM_OF_CHOICES = 3;
    const char *choices[NUM_OF_CHOICES] = {"Get back", "Save game", "Exit game"};
    int single;
    int highlight = 0;
    do
    {
        for (int i = 0; i < NUM_OF_CHOICES; i++)
        {
            if (i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, i + 1, 1, choices[i]);
            wattroff(win, A_REVERSE);
        }
        single = getch();

        switch (single)
        {
        case KEY_UP:
        case 'w':
            highlight--;
            if (highlight < 0)
                highlight = 0;
            break;
        case KEY_DOWN:
        case 's':
            highlight++;
            if (highlight >= NUM_OF_CHOICES)
                highlight = NUM_OF_CHOICES - 1;
            break;
        default:
            break;
        }
        wrefresh(win);
    } while (single != 10);

    switch (highlight)
    {
    // get back
    case 0:
        break;
    // save game
    case 1:
        if (gameFiles->SaveGame(name, material, generate, map, obj, price))
            break;
        break;
    // exit
    case 2:
        return true;
        break;
    default:
        break;
    }

    werase(win);
    box(win, 0, 0);
    wrefresh(win);

    return false;
}

bool Game::ChangeRefresh(const bool increase)
{
    if (!increase)
    {
        if (speed < 1.75)
        {
            speed += 0.25;
            displaySpeed -= 0.25;
            return true;
        }
    }
    else if (speed > 0.25)
    {
        speed -= 0.25;
        displaySpeed += 0.25;
        return true;
    }
    return false;
}