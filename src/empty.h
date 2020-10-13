#include "field.h"
#include <ncurses.h>
#include <unordered_map>

#ifndef _EMPTY
#define _EMPTY
/**
 * @class Empty
 * @brief child of Field, represents empty fiel in-game
 */
class Empty : public Field
{
public:
    Empty(){};
    virtual char Type() const override { return ' '; };
    virtual char Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price) override;
};

#endif