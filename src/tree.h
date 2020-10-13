#include "field.h"

#ifndef _TREE
#define _TREE

/**
 * @class Tree
 * @brief represents in-game object Tree
 */
class Tree : public Field
{
public:
    Tree(){};
    virtual char Type() const override { return 'T'; };
    virtual char Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price)
        override { return !DisplayText("Tree", win, "This tree is generating wood"); }
};

#endif