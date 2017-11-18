#include <iostream>
#include <Windows.h>
#include "game.h"

int main()
{
	TestGame* test = new TestGame(readConfiguration("res/config.json"));
	test->run();
	delete(test);
	return 0;
}