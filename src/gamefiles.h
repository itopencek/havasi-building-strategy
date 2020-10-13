#include "cost.h"
#include <unordered_map>
#include <ncurses.h>
#include <string>
#include "map.h"
#include "objective.h"

#ifndef _GAMEFILES
#define _GAMEFILES

/**
 * @class GameFiles
 * @brief class to work with files, to save and load data
 * 
 * @var materialPath - path to starting material
 * @var buildingPath - path to starting prices of buildings
 */
class GameFiles
{
public:
    /**
     * @brief loads starting prices from a file
     * @param[in,out] material - current resources
     * @param[in,out] generate - currently generated amount
     * @param[in,out] price - prices of buildings
     * @returns false - if there is error
     *          true - if everything was loaded correctly
     */
    bool LoadPrice(Cost &material, Cost &generate, std::unordered_map<char, Cost> &price);
    /**
     * @brief saves current game into a file
     * @param[in] name - name of game file
     * @param[in,out] material - current resources
     * @param[in,out] generate - currently generated amount
     * @param[in,out] map - map used for game
     * @param[in,out] obj - current game objective
     * @param[in,out] price - prices of buildings
     * @returns true - if everything worked correctly
     *          false - if there was an error
     */
    bool SaveGame(const std::string &name, const Cost &material, const Cost &generate, Map *map, Objective *obj, std::unordered_map<char, Cost> &price);
    /**
     * @brief loads game from a given file
     * @param[in,out] saveName - name of game file
     * @param[in,out] material - current resources
     * @param[in,out] generate - currently generated amount
     * @param[in,out] map - map used for game
     * @param[in,out] obj - current game objective
     * @param[in,out] price - prices of buildings
     * @returns true - if game is loaded
     *          false - on error, game cannot be loaded
     */
    bool LoadGame(std::string &saveName, Cost &material, Cost &generate, Map *&map, Objective *&obj, std::unordered_map<char, Cost> &price);

private:
    const char *materialPath = "examples/prices/starting_mat";
    const char *buildingPath = "examples/prices/buildings";
};

#endif