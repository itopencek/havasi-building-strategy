#include "menu.h"

int Menu::Init(WINDOW *win) const
{
    curs_set(0);
    int returnValue = 0;
    returnValue = StartMenu(win);
    werase(win);
    box(win, 0, 0);

    return returnValue;
}

int Menu::NewGameMenu(WINDOW *win) const
{
    const int NUM_OF_CHOICES = 4;
    std::string choices[NUM_OF_CHOICES] = {"Easy map", "Mission 1", "Mission 2", "Get Back"};
    int result = Template(choices, NUM_OF_CHOICES, win);
    return result;
}

int Menu::StartMenu(WINDOW *win) const
{
    const int NUM_OF_CHOICES = 4;
    std::string choices[NUM_OF_CHOICES] = {"New Game", "Load Game", "Tutorial", "Exit"};
    int result = Template(choices, NUM_OF_CHOICES, win);
    return result;
}

int Menu::Template(const std::string choices[], const int NUM_OF_CHOICES, WINDOW *win) const
{
    int single = 0;
    int highlight = 0;

    do
    {
        for (int i = 0; i < NUM_OF_CHOICES; i++)
        {
            if (i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, i + 1, 1, choices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        single = getch();
        // checks user input
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

    return highlight;
}