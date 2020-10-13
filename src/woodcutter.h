#include "field.h"
#include <ncurses.h>
#include <unordered_map>

#ifndef _WOODCUTTER
#define _WOODCUTTER

/**
 * @class Woodcutter
 * @brief represents in-game building Woodcutter
 */
class Woodcutter : public Field
{
public:
    Woodcutter(){};
    virtual char Type() const override { return 'w'; };
    virtual char Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price) override;
};

#endif