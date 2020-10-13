#include <ncurses.h>
#include <string>

#ifndef _MENU
#define _MENU

/**
 * @class Menu
 * @brief creates various menus for user to choose from
 */
class Menu
{
public:
    Menu(){};
    ~Menu(){};
    /**
     * @brief initializes window for new menu, starts StartMenu
     * @param[in] win - window where to display menu
     * @returns number of chosen option by user
     */
    int Init(WINDOW *win) const;
    /**
     * @brief menu after user has chosen to start a new game
     * @param[in] win - window where to display menu
     * @returns number of chosen option by user
     */
    int NewGameMenu(WINDOW *win) const;

private:
    /**
     * @brief start game menu
     * @param[in] win - window where to display menu
     * @returns number of chosen option by user
     */
    int StartMenu(WINDOW *win) const;
    /**
     * @brief template for menu
     * @param[in] choices - arr, text to display to user as options
     * @param[in] NUM_OF_CHOICES - length of arr choices
     * @param[in] win - window to display menu in
     */
    int Template(const std::string choices[], const int NUM_OF_CHOICES, WINDOW *win) const;
};

#endif