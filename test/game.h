#pragma once

#include <ginkgo.h>

using namespace ginkgo;

GameConfig readConfiguration(const char* filepath);

class TestScene :public Scene
{
public:
	TestScene();
	virtual ~TestScene();
	virtual void update(float dt);
    Texture logoImg;
};

class TestGame :public Game
{
public:
	TestGame(GameConfig c = GameConfig());
};