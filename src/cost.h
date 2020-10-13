#include <string>

#ifndef _COST
#define _COST

/**
 * @class Cost
 * @brief custom type
 * @details used to store data about in-game prices
 * has operator>=,-=,+=,[] overloaded
 * has maximum value of any in-game resource
 * 
 * @var wood, stone, food, troops, people - stores cost in in-game resources
 * @var size - number of in-game resources
 * @var max - maximum value of any in-game resource
 */
class Cost
{
public:
    Cost(int w = 0, int s = 0, int f = 0, int t = 0, int p = 0) : wood(w), stone(s), food(f), troops(t), people(p){};
    Cost(const Cost &second) = default;
    ~Cost(){};
    Cost &operator=(const Cost &second) = default;

    /**
     * @brief sets new value to every resource
     */
    void Set(int w = 0, int s = 0, int f = 0, int t = 0, int p = 0);
    /**
     * @brief increases one resource by given amount
     * @param[in] amount - number to increase it by
     * @param[in] a - resource
     */
    void Increase(const int amount, const char a);
    int Size() const { return size; };
    /**
     * @brief returns formated string with current cost
     */
    std::string PrintCost();

    friend bool operator>=(const Cost &first, const Cost &second);
    friend bool operator-=(Cost &first, const Cost &second);
    friend bool operator+=(Cost &first, const Cost &second);
    int operator[](const int idx) const;

private:
    int wood;
    int stone;
    int food;
    int troops;
    int people;
    const int size = 5;
    const int max = 9999999;
};

#endif