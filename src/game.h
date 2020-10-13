#include <ncurses.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "map.h"
#include "menu.h"
#include "cost.h"
#include "objective.h"
#include "gamefiles.h"

#ifndef _GAME
#define _GAME

/**
 * @class Game
 * @brief class, which takes care of game, which is currently played
 * 
 * @var name
 * @var menu 
 * @var refreshRate - default refresh rate
 * @var speed - number, which multiplies refreshRate
 * @var displaySpeed - speed, but to display to player, when speed is lowered
 *                     displaySpeed is highered
 * @var mainWin - main window, in which is everything displayed
 * @var bottomWin - window at the bottom of screen
 * @var mapWindow - window used for map and gameplay
 * @var material - current amount of resources
 * @var generate - amount of resources to be added on next tick
 * @var price - map of buidlings and their prices
 * @var obj - objective for current game   
 * @var gamefiles - class for work with files                   
 */
class Game
{
public:
    Game(WINDOW *win);
    ~Game();
    /** 
     * @brief renders basic windows, selects specific map and objective
     * initializes game loop
     * @param[in] choice - user's choice on what mission to load or exit game
     * @param[in] loadName - name of game
     * @returns true - if everything worked correctly
     *          false - if there was an error   
    */
    bool Init(const int choice, const std::string &loadName);
    /**
     * @brief increases production per of given resource by
     *        given amount
     * @param[in] type - resource type, which production is increased
     * @param[in] building - building which is generating resource
     * @param[in] y,x - position of building on map
     * @returns true - if everything worked correctly
     *          false - if there was an error
     */
    bool IncreaseProduction(const char type, const int y, const int x, const char building);

private:
    /**
     * @brief game loop, reacts to users input, creates game flow
     * @param[in] win - window in which game is happening
     * @returns false - if there was an error
     *          true - if game ended correctly
     */
    bool GameLoop(WINDOW *win);
    /**
     * @brief finds out if current position of character is out of game window
     * @returns false - if current position is on the border of window
     *          true - otherwise
     */
    bool OutOfMap(WINDOW *win, const int y, const int x) const;
    /**
     * @brief deletes window and its border
     * @param[in] win - window to delete
     */
    void DeleteWin(WINDOW *win) const;
    /**
     * @brief prits char and its color on given position
     * @param[in] win - window to print it in
     * @param[in] y,x - position in which to write character
     * @param[in] a - character to write
     */
    void PrintChar(WINDOW *win, const int y, const int x, const char a) const;
    /**
     * @brief prints current materials on window, also
     *        adds new material
     * @param[in] add - false when only text should be
     *                  rendered
     *                  true when new material should be
     *                  added
     */
    void Generate(const bool add);
    /**
     * @brief basic menu after pressing ESC in-game
     * @param[in] win - window to render menu in
     * @returns true - if exiting game
     *          false - otherwise
     */
    bool GameMenu(WINDOW *win);
    /**
     * @brief changes game speed
     * @param[in] increase - if price should be increased
     *            or lowered
     * @returns true - if game speed should be changed
     *          false - if game speed shouldn't be changed
     */
    bool ChangeRefresh(const bool increase);

    std::string name = "";
    Menu *menu;
    const int refreshRate = 50;
    float speed = 1;
    float displaySpeed = 1;
    WINDOW *mainWin;
    WINDOW *bottomWin;
    WINDOW *mapWin;
    Map *map;
    Cost material;
    Cost generate;
    std::unordered_map<char, Cost> price;
    Objective *obj;
    GameFiles *gameFiles = new GameFiles();
};

#endif