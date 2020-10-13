#include "field.h"
#include <unordered_map>

#ifndef _HOUSE
#define _HOUSE

/**
 * @class House
 * @brief class, which represents in-game building house
 */
class House : public Field
{
public:
    House(){};
    virtual char Type() const override { return 'h'; };
    virtual char Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price) override;
};

#endif