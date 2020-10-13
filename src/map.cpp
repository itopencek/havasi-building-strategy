#include "map.h"
#include "color.h"
#include "empty.h"
#include "tree.h"
#include "mountain.h"
#include "water.h"
#include "woodcutter.h"
#include "fishingbooth.h"
#include "quary.h"
#include "barracks.h"
#include "castle.h"
#include "house.h"

bool Map::Load(const std::string &mapName)
{
    // dont forget we are reading from main
    std::ifstream ifs("examples/maps/" + mapName);
    std::string line;
    int row = 0;
    char single;

    // get the first line
    if (!getline(ifs, line))
        return false;

    std::istringstream iss(line);

    iss >> x >> y;

    if (iss.fail())
        return false;
    // maximum allowed size of map
    if (x > 10 || y > 55 || y < 12 || x < 1)
        return false;

    data.push_back(std::vector<std::shared_ptr<Field>>());

    while (ifs.get(single))
    {
        if (ifs.fail())
            return false;
        if (single == '\n')
        {
            row++;
            data.push_back(std::vector<std::shared_ptr<Field>>());
        }
        else
        {
            // not ready to load gamesaves
            switch (single)
            {
            case ' ':
                data[row].push_back(std::make_shared<Empty>());
                break;
            case 'T':
                data[row].push_back(std::make_shared<Tree>());
                break;
            case 'W':
                data[row].push_back(std::make_shared<Water>());
                break;
            case 'M':
                data[row].push_back(std::make_shared<Mountain>());
                break;
            case 'w':
                data[row].push_back(std::make_shared<Woodcutter>());
                break;
            case 'f':
                data[row].push_back(std::make_shared<FishingBooth>());
                break;
            case 'b':
                data[row].push_back(std::make_shared<Barracks>());
                break;
            case 'q':
                data[row].push_back(std::make_shared<Quary>());
                break;
            case 'c':
                data[row].push_back(std::make_shared<Castle>());
                break;
            case 'h':
                data[row].push_back(std::make_shared<House>());
                break;
            default:
                return false;
                break; // useless break
            }
        }
    }

    return true;
}

bool Map::Render(WINDOW *win)
{
    int curY, curX;
    getmaxyx(win, curY, curX);
    // if map is bigger than window
    // -2 because of borders
    // reversed x,y
    if (y > curX || x > curY)
        return false; // map is bigger than available space in window

    // check if size is real
    if (data.size() != (unsigned int)x)
        return false;
    // prints row by row
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            wmove(win, i + 1, j + 1);
            // map error - not real row size
            if (data[i].size() != (unsigned int)y)
                return false;
            switch (data[i][j]->Type())
            {
            case ' ':
                waddch(win, data[i][j]->Type());
                break;
            case 'W':
                wattron(win, COLOR_PAIR(WATER));
                waddch(win, data[i][j]->Type());
                wattroff(win, COLOR_PAIR(WATER));
                break;
            case 'T':
                wattron(win, COLOR_PAIR(TREE));
                waddch(win, data[i][j]->Type());
                wattroff(win, COLOR_PAIR(TREE));
                break;
            case 'M':
                wattron(win, COLOR_PAIR(MOUNTAIN));
                waddch(win, data[i][j]->Type());
                wattroff(win, COLOR_PAIR(MOUNTAIN));
                break;
            default:
                waddch(win, data[i][j]->Type());
                break;
            }
        }
    }

    wrefresh(win);
    return true;
}

char Map::GetField(const int y, const int x) const
{
    return data[y - 1][x - 1]->Type();
}

bool Map::Write(const int y, const int x, char building)
{
    switch (building)
    {
    case 'w':
        data[y - 1][x - 1] = std::make_shared<Woodcutter>();
        break;
    case 'f':
        data[y - 1][x - 1] = std::make_shared<FishingBooth>();
        break;
    case 'q':
        data[y - 1][x - 1] = std::make_shared<Quary>();
        break;
    case 'b':
        data[y - 1][x - 1] = std::make_shared<Barracks>();
        break;
    case 'c':
        data[y - 1][x - 1] = std::make_shared<Castle>();
        break;
    case 'h':
        data[y - 1][x - 1] = std::make_shared<House>();
        break;
    default:
        // should never happen
        return false;
        break;
    }
    return true;
}

bool Map::SaveMap(std::ofstream &of)
{
    of << x << " " << y << std::endl;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            of << data[i][j]->Type();
        }
        of << std::endl;
    }

    return true;
}

bool Map::IsBuilt(const char building) const
{
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            if (data[i][j]->Type() == building)
                return true;
    return false;
}

int Map::Generate(const int y, const int x, const char type) const
{
    int generate = 0;
    int a = x - 2 < 0 ? 0 : x - 2;
    int b = y - 2 < 0 ? 0 : y - 2;
    // Map::y and Map::x are now correct
    int c = x > Map::y - 1 ? Map::y - 1 : x;
    int d = y > Map::x - 1 ? Map::x - 1 : y;

    // going through all 9 fields
    for (int i = a; i <= c; i++)
        for (int j = b; j <= d; j++)
            if (data[j][i]->Type() == type)
                generate += 1;

    return generate;
}