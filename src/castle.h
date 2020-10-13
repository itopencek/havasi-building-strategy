#include "field.h"
#include <unordered_map>

#ifndef _CASTLE
#define _CASTLE

/**
 * @class Castle
 * @brief child of Field, represents in-game building castle
 */
class Castle : public Field
{
public:
    Castle(){};
    virtual char Type() const override { return 'c'; };
    virtual char Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price) override;
};

#endif