#include <ncurses.h>
#include <unordered_map>
#include <string>
#include "cost.h"

#ifndef _FIELD
#define _FIELD
/**
 * @class Field
 * @brief parent class with some abstract methods, also has normal methods
 */
class Field
{
public:
    Field(){};
    /**
     * @brief abstract class
     * @returns type of field
     */
    virtual char Type() const = 0;
    /**
     * @brief abstract class, special menu for fields
     * @param[in] win - window to display menu in
     * @param[in,out] material - current amount of resources
     * @param[in,out] generate - current amount of generated resources
     * @param[in,out] price - current prices of buildings
     * @returns building
     */
    virtual char Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price) = 0;

    /**
     * @brief creates menu, where user can choose an option
     * @param[in] win - window to create menu in
     * @param[in] NUM_OF_CHOICES - number of choices
     * @param[in] choices - array of choices
     * @returns number of option chosen by user
     */
    int ChoosingMenu(WINDOW *win, const int NUM_OF_CHOICES, std::string choices[]) const;
    /**
     * @brief displays message to user
     * @param[in] title - title text
     * @param[in] win - window to display it in
     * @param[in] text - text to display with default value
     * @returns true
     */
    bool DisplayText(const char *title, WINDOW *win, const char *text) const;
    /**
     * @brief clears window, border and refreshes it
     * @param[in] win - window to clear
     * @returns true
     */
    bool Clear(WINDOW *win) const;
};

#endif