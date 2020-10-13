#include "field.h"
#include <unordered_map>

#ifndef _FISHINGBOOTH
#define _FISHINGBOOTH

/**
 * @class FishingBooth
 * @brief class, which represents in-game building fishingbooth
 */
class FishingBooth : public Field
{
public:
    FishingBooth(){};
    virtual ~FishingBooth(){};
    virtual char Type() const override { return 'f'; };
    virtual char Special(WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price) override;
};

#endif