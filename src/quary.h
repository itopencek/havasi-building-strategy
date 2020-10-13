#include "field.h"
#include <unordered_map>

#ifndef _QUARY
#define _QUARY

/**
 * @class Quary
 * @brief represents in-game building Quary
 */
class Quary : public Field
{
public:
    Quary(){};
    virtual char Type() const override { return 'q'; };
    virtual char Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price) override;
};

#endif