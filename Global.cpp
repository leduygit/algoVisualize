#include "Global.hpp"

std::string toString(int x)
{
    std::string num = "";
    if (x == 0)
        num += '0';
    while (x)
    {
        num += ('0' + x % 10);
        x /= 10;
    }
    reverse(num.begin(), num.end());
    return num;
}

int stringToInt(std::string t)
{
    int x = 0;
    for (char c : t)
        x = x * 10 + (c - '0');
    return x;
}

int randInt(int l, int r)
{
    if (l > r)
        return r;
    return l + rand() % (r - l + 1);
}