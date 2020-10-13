#include "field.h"

#ifndef _MOUNTAIN
#define _MOUNTAIN

/**
 * @class Mountain
 * @brief represents in-game object Mountain
 */
class Mountain : public Field
{
public:
    Mountain(){};
    virtual char Type() const override { return 'M'; };
    virtual char Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price)
        override { return !DisplayText("Mountain", win, "This mountain is generating stone"); };
};

#endif