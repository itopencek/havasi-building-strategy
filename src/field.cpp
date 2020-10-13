#include "field.h"

int Field::ChoosingMenu(WINDOW *win, const int NUM_OF_CHOICES, std::string choices[]) const
{
    int single;
    int highlight = 0;
    // menu
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
        // pressed ESC, return get back
        case 27:
            return 0;
        default:
            break;
        }
        wrefresh(win);
    } while (single != 10);

    werase(win);
    box(win, 0, 0);
    wrefresh(win);

    return highlight;
}

bool Field::DisplayText(const char *title, WINDOW *win, const char *text = "Not enough resources") const
{
    mvwprintw(win, 0, 1, title);
    wattron(win, A_REVERSE);
    mvwprintw(win, 1, 1, "Get back");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 2, 1, text);
    wrefresh(win);
    while (getch() != 10)
    {
    }
    werase(win);
    box(win, 0, 0);
    wrefresh(win);
    return true;
}

bool Field::Clear(WINDOW *win) const
{
    werase(win);
    box(win, 0, 0);
    wrefresh(win);
    return true;
}