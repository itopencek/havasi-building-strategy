#include <string>
#include <ncurses.h>

#ifndef _READINPUT
#define _READINPUT

/**
 * @class ReadInput
 * @brief allows user to write his own text input
 */
class ReadInput
{
public:
    /**
     * @brief creates input box for user to write input
     * @param[in] win - window to create input box in
     * @param[in] text - text to display, when asking for input
     * @returns user input
     */
    std::string Read(WINDOW *win, const char *text) const;
};

#endif