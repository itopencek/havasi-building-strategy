#include "readinput.h"

std::string ReadInput::Read(WINDOW *win, const char *text) const
{
    curs_set(1);
    mvwprintw(win, 1, 1, text);
    mvwprintw(win, 2, 1, "Press ENTER to continue");
    mvwprintw(win, 3, 1, "Press ESC to get back");
    mvwprintw(win, 4, 1, "                        ");
    // need to refresh stdscr and win, both must stay
    refresh();
    wrefresh(win);
    const int sR = 1;
    std::string tmp = text;
    std::string data;
    int sC = tmp.length() + 1;

    char single = ERR;
    move(sR, sC);
    sC++;
    do
    {
        if (single != ERR)
        {
            if ((single >= 48 && single <= 57) || (single >= 97 && single <= 122) || single == 46)
            {
                data += single;
                mvwaddch(win, sR, sC, single);
                sC++;
                wrefresh(win);
            }
            if (single == 27)
                return "-";
        }
        single = getch();
    } while (single != 10);

    werase(win);
    box(win, 0, 0);
    wrefresh(win);

    curs_set(0);
    return data;
}