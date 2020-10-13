#include "field.h"
#include <unordered_map>

#ifndef _BARRACKS
#define _BARRACKS

/**
 * @class Barracks
 * @brief represents in-game building barracks
 */
class Barracks : public Field
{
public:
    Barracks(){};
    virtual char Type() const override { return 'b'; };
    virtual char Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price) override;
};

#endif