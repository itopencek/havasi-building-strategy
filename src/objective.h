#include <ncurses.h>
#include <string>
#include <iostream>
#include "cost.h"
#include <fstream>
#ifndef _OBJECTIVE
#define _OBJECTIVE

/**
 * @class Objective
 * @brief maintains game objective
 * 
 * @var level - currently only true
 * @var difficulty - difficulty of game
 * @var questNumber - number of quest
 * @var type - type of quest
 * @var desc - description to display to user
 * @var name - name of objective file
 * @var cost - cost of some objectives
 * @var building - building needed for some objectives
 */
class Objective
{
public:
    Objective(bool level, int questNumber, int difficulty = 1)
        : level(level), difficulty(difficulty), questNumber(questNumber){};
    Objective(bool level, int questNumber, int difficulty, std::string name)
        : level(level), difficulty(difficulty), questNumber(questNumber), name(name){};

    /**
     * @brief checks if objective was fullfilled
     * @param[in] material - current amount of material
     * @param[in] building - most recent built building
     * @returns true if objective was fullfilled
     *          false if objective is not done yet
     */
    bool Check(const Cost &material, const char building) const;
    /**
     * @returns description to display to user
     */
    const std::string &GetDescription() const { return desc; };
    /**
     * @returns cost of current objective
     */
    const Cost &GetCost() const { return cost; };
    /**
     * @brief saves current objective
     * @param[in] ofs - file stream to write into
     * @returns false on error
     *          true if save was successful
     */
    bool Save(std::ofstream &ofs);
    /**
     * @brief loads objective from file
     * @returns false on error
     *          true if loading was successful
     */
    bool LoadObjective();

private:
    /**
     * @brief loading special type of quest
     * @param[in] ifs - file stream to load from
     * @returns false on error
     *          true on success
     */
    bool TypeGetResources(std::ifstream &ifs);
    /**
     * @brief loading special type of quest
     * @param[in] ifs - file stream to load from
     * @returns false on error
     *          true on success
     */
    bool TypeBuildBuilding(std::ifstream &ifs);
    bool level;
    int difficulty;
    int questNumber;
    int type;
    std::string desc;
    std::string name = "level0";
    Cost cost;
    char building;
};

#endif