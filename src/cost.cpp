#include "cost.h"

bool operator>=(const Cost &first, const Cost &second)
{
    return (first.wood >= second.wood) &&
           (first.stone >= second.stone) &&
           (first.food >= second.food) &&
           (first.troops >= second.troops) &&
           (first.people >= second.people);
}

void Cost::Set(int w, int s, int f, int t, int p)
{
    wood = w;
    stone = s;
    food = f;
    troops = t;
    people = p;
}

int Cost::operator[](int idx) const
{
    switch (idx)
    {
    case 0:
        return wood;
        break;
    case 1:
        return stone;
        break;
    case 2:
        return food;
        break;
    case 3:
        return troops;
        break;
    case 4:
        return people;
        break;
    default:
        throw "error [] bad index";
        break;
    }
    return 0;
}

void Cost::Increase(const int amount, const char a)
{

    switch (a)
    {
    case 'w':
        if (wood + amount < max)
            wood += amount;
        break;
    case 'q':
        if (wood + amount < max)
            stone += amount;
        break;
    case 's':
        if (wood + amount < max)
            stone += amount;
        break;
    case 'f':
        if (wood + amount < max)
            food += amount;
        break;
    case 't':
        if (wood + amount < max)
            troops += amount;
        break;
    case 'p':
        if (wood + amount < max)
            people += amount;
        break;
    default:
        throw "wrong char";
        break;
    }
}

bool operator-=(Cost &first, const Cost &second)
{
    first.wood -= second.wood;
    first.stone -= second.stone;
    first.food -= second.food;
    first.troops -= second.troops;
    first.people -= second.people;
    return true;
}

bool operator+=(Cost &first, const Cost &second)
{
    if (first.wood + second.wood < first.max)
        first.wood += second.wood;
    if (first.stone + second.stone < first.max)
        first.stone += second.stone;
    if (first.food + second.food < first.max)
        first.food += second.food;
    if (first.troops + second.troops < first.max)
        first.troops += second.troops;
    if (first.people + second.people < first.max)
        first.people += second.people;
    return true;
}

std::string Cost::PrintCost()
{
    return std::to_string(wood) + " wood, " + std::to_string(stone) + " stones, " + std::to_string(food) + " food, " + std::to_string(troops) + " troops, " + std::to_string(people) + " people";
}