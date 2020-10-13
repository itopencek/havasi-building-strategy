#include <ncurses.h>

#ifndef _TUTORIAL
#define _TUTORIAL

/**
 * @class Tutorial
 * @brief explains basics of the game to user in text form
 */
class Tutorial
{
public:
    Tutorial(){};
    /**
     * @brief initializes tutorial, shows first page of tutorial
     * @param[in] win - window to display tutorial in
     */
    void Start(WINDOW *win);

private:
    /**
     * @brief shows second page of tutorial
     * @param[in] win - window to display tutorial in
     */
    void Second(WINDOW *win);
};

#endif