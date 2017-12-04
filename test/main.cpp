#include <iostream>
#include <Windows.h>
#include "game.h"
#include <stdio.h>
using namespace std;

int main()
{
    GameConfig c = readConfiguration("res/config.json");
    TestGame test(c);
    return test.run();
}

