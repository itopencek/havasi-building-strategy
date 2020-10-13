#include "field.h"

#ifndef _WATER
#define _WATER

/**
 * @class Water
 * @brief represents in-game object Water
 */
class Water : public Field
{
public:
    Water(){};
    virtual char Type() const override { return 'W'; };
    virtual char Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price)
        override { return !DisplayText("Water", win, "This water is generating food"); }
};

#endif