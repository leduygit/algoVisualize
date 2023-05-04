#ifndef _Global_H
#define _Global_H
#include <iostream>
#include <string.h>
#include <algorithm>
#include <chrono>
#include <thread>
std::string toString(int x);

int stringToInt(std::string t);

int randInt(int l, int r);

void pause_for(int pauseTime);
#endif