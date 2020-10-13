#include <ncurses.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <unordered_map>
#include "field.h"

#ifndef _MAP
#define _MAP

/**
 * @class Map
 * @brief takes care of game map
 * @details can load, save, write into map, check any position, render map
 * 
 * @var data - vector of vectors which hold shared pointer to Field - data of current
 *             block
 * @var y,x - size of map
 */
class Map
{
public:
    Map(){};
    /**
     * @brief loads maps from file
     * @returns false on error
     *          true on success
     */
    bool Load(const std::string &mapName);
    /**
     * @brief renders map
     * also refreshes the window at the end
     * 
     * @param[in] win - window to render map into
     * @returns false - on error
     *          true - otherwise
     */
    bool Render(WINDOW *win);
    int GetY() const { return y; };
    int GetX() const { return x; };
    /**
     * @returns type of field
     */
    char GetField(const int y, const int x) const;
    /**
     * @brief adds new building into map
     * @param[in] y,x - coords
     * @param[in] building - building to add
     * @returns true - if there was no error
     *          false - on error
     */
    bool Write(const int y, const int x, char building);
    /**
     * @brief finds out how many types of field are 1 block
     *        around given position
     * @param[in] y,x - coords
     * @param[in] type - field to look for
     * @returns number of fields found
     */
    int Generate(const int y, const int x, const char type) const;
    /**
     * @brief calls Special method of field on given coords
     * @param[in] y,x - coords
     * @param[in] win - window into which new menu can be displayed
     * @param[in,out] material - current amount of resources
     * @param[in,out] generate - current amount of resources generated
     * @param[in,out] price - map of buidlings and their prices
     * @returns character
     */
    char GetSpecial(const int y, const int x, WINDOW *win, Cost &material, Cost &generate, std::unordered_map<char, Cost> &price)
    {
        return data[y - 1][x - 1]->Special(win, material, generate, price);
    };
    bool SaveMap(std::ofstream &of);
    /**
     * @returns true - if buidling is already built
     *          false otherwise
     */
    bool IsBuilt(const char building) const;

private:
    std::vector<std::vector<std::shared_ptr<Field>>> data;
    int y, x;
};

#endif