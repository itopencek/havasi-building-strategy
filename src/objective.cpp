#include "objective.h"
#include <fstream>
#include <sstream>

bool Objective::Check(const Cost &material, const char building) const
{
    if (type == 0)
    {
        if (material >= cost)
            return true;
        else
            return false;
    }
    else if (type == 1)
    {
        if (building == Objective::building)
            return true;
        else
            return false;
    }

    return false;
}

bool Objective::LoadObjective()
{
    std::ifstream ifs;
    std::string line;

    ifs.open("examples/objectives/" + name);
    if (ifs.fail())
    {
        ifs.close();
        std::cout << "Error while loading objective file" << std::endl;
        return false;
    }
    if (!getline(ifs, line))
    {
        ifs.close();
        std::cout << "Error while loading objective file" << std::endl;
        return false;
    }
    type = line[0] - 48;
    switch (type)
    {
    case 0:
        if (!Objective::TypeGetResources(ifs))
        {
            ifs.close();
            return false;
        }
        break;
    case 1:
        if (!Objective::TypeBuildBuilding(ifs))
        {
            ifs.close();
            return false;
        }
        break;
    default:
        ifs.close();
        return false;
    }

    ifs.close();
    return true;
}

bool Objective::TypeGetResources(std::ifstream &ifs)
{
    std::string line;
    int w, s, f, t;

    if (!getline(ifs, line) && line != "\n")
        return false;
    desc = "Objective: " + line;

    // empty line
    if (!getline(ifs, line) && line != "\n")
        return false;

    if (!getline(ifs, line))
        return false;

    std::stringstream ss = std::stringstream(line);
    ss >> w >> s >> f >> t;
    if (ss.fail())
    {
        std::cout << "Error while loading objective file" << std::endl;
        return false;
    }
    cost.Set(w, s, f, t);

    return true;
}

bool Objective::Save(std::ofstream &ofs)
{
    ofs << name << " " << level << " " << questNumber << " " << difficulty;
    return true;
}

bool Objective::TypeBuildBuilding(std::ifstream &ifs)
{
    std::string line;

    if (!getline(ifs, line) && line != "\n")
        return false;
    desc = "Objective: " + line;

    if (!getline(ifs, line) && line != "\n")
        return false;

    if (!getline(ifs, line))
        return false;

    std::stringstream ss = std::stringstream(line);
    ss >> building;
    if (ss.fail())
    {
        std::cout << "Error while loading objective file" << std::endl;
        return false;
    }

    return true;
}