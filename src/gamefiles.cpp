#include "gamefiles.h"
#include <sstream>
#include <fstream>

bool GameFiles::LoadPrice(Cost &material, Cost &generate, std::unordered_map<char, Cost> &price)
{
    const int NUM = 7;
    char buildings[NUM] = {'b', 'w', 'q', 'f', 'c', 'h', 't'};
    std::ifstream ifs;
    std::string line;
    std::stringstream iss;
    char building;
    int w, s, f, t, p;
    if (ifs.fail())
        return false;

    generate.Set(0, 0, 0, 0, 0);

    // load starting material
    ifs.open(materialPath);
    if (!getline(ifs, line))
        return false;
    iss.str(line);
    iss >> w >> s >> f >> t >> p;
    if (iss.fail())
        return false;
    material.Set(w, s, f, t, p);
    ifs.close();

    iss.str("");
    iss.clear();

    // load prices of buildings
    ifs.open(buildingPath);
    for (int i = 0; i < NUM; i++)
    {
        if (!getline(ifs, line))
            return false;
        iss.str(line);
        iss >> building >> w >> s >> f >> t >> p;
        if (iss.fail() || building != buildings[i])
            return false;

        price[building].Set(w, s, f, t, p);
        iss.str("");
        iss.clear();
    }
    ifs.close();

    return true;
}

bool GameFiles::SaveGame(const std::string &name, const Cost &material, const Cost &generate, Map *map, Objective *obj, std::unordered_map<char, Cost> &price)
{
    std::string path = "examples/saves/" + name;
    std::ofstream of;
    of.open(path);
    of << name << std::endl;

    // save map
    if (!map->SaveMap(of))
        return false;

    // add current material
    of << "m";
    for (int i = 0; i < material.Size(); i++)
    {
        of << " ";
        of << material[i];
    }

    // add how much is generated
    of << std::endl;
    of << "g";
    for (int i = 0; i < generate.Size(); i++)
    {
        of << " ";
        of << generate[i];
    }

    // saving current objective
    of << std::endl;
    if (!obj->Save(of))
        return false;
    of << std::endl;

    //save price of house
    of << price['h'][0] << " " << price['h'][1] << " " << price['h'][2] << " " << price['h'][3] << " " << price['h'][4] << std::endl;
    of.close();
    return true;
}

bool GameFiles::LoadGame(std::string &saveName, Cost &material, Cost &generate, Map *&map, Objective *&obj, std::unordered_map<char, Cost> &price)
{
    std::ifstream ifs;
    std::string line;
    std::ofstream of;
    int level, questNumber, difficulty, x, y, arr[5];
    char c;
    std::string name;

    // try to open file
    ifs.open("examples/saves/" + saveName);
    if (ifs.fail() || saveName == "")
        return false;
    if (!getline(ifs, line))
        return false;

    // get rid of newline
    line[line.length()] = 0;
    saveName = line;

    if (!getline(ifs, line))
        return false;

    // load size of map
    std::istringstream iss(line);
    iss >> x >> y;

    if (iss.fail())
        return false;

    // write loaded data into tmp
    of.open("examples/maps/tmp");
    of << x << " " << y << std::endl;

    for (int i = 0; i < x; i++)
    {
        getline(ifs, line);
        of << line;
        if (i != x - 1)
            of << std::endl;
    }
    of.close();
    // try to load tmp
    if (!map->Load("tmp"))
    {
        ifs.close();
        return false;
    }
    // load material
    if (!getline(ifs, line))
        return false;

    iss.str("");
    iss.clear();
    iss.str(line);

    iss >> c >> arr[0] >> arr[1] >> arr[2] >> arr[3] >> arr[4];
    if (iss.fail())
        return false;
    material.Set(arr[0], arr[1], arr[2], arr[3], arr[4]);

    // load generating
    if (!getline(ifs, line))
        return false;
    iss.str("");
    iss.clear();
    iss.str(line);

    iss >> c >> arr[0] >> arr[1] >> arr[2] >> arr[3] >> arr[4];
    if (iss.fail())
        return false;

    generate.Set(arr[0], arr[1], arr[2], arr[3], arr[4]);

    if (!getline(ifs, line))
        return false;
    iss.str("");
    iss.clear();
    iss.str(line);

    // load objective
    iss >> name >> level >> questNumber >> difficulty;
    if (iss.fail())
        return false;

    obj = new Objective(level, questNumber, difficulty, name);
    if (!obj->LoadObjective())
        return false;

    if (!getline(ifs, line))
        return false;
    iss.str("");
    iss.clear();
    iss.str(line);

    iss >> arr[0] >> arr[1] >> arr[2] >> arr[3] >> arr[4];

    if (iss.fail())
        return false;
    price['h'].Set(arr[0], arr[1], arr[2], arr[3], arr[4]);

    ifs.close();
    return true;
}